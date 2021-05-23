#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#include "../../ds/src/priority_queue/priority_queue.h"
#include "../../ds/src/uid/uid.h"
#include "../../ds/src/task/task.h"
#include "scheduler.h"


#define UNUSED(x) void(x)

struct scheduler
{
	pq_t *pq;
	int is_run; 
	task_t * task;
};


int cmp_func(const void *time1, const void *time2)
{
	return (TaskGetExecutionTime((task_t*)time1)  - TaskGetExecutionTime((task_t*)time2));
}


int is_match_func(const void *data, const void *param)
{
	return ( UidIsSame(TaskGetUid((task_t*)data) ,*(ilrd_uid_t*)param));
}
 
 
scheduler_t *SchedulerCreate(void)
{
	scheduler_t *scheduler = (scheduler_t*)malloc(sizeof(scheduler_t));

	if (scheduler == NULL)
	{
		return (NULL);
	}
	
	scheduler->pq = PQueueCreate(cmp_func);
	
	if (scheduler->pq == NULL)
	{
		free(scheduler);
		
		return (NULL);
	}
	scheduler->is_run = 0;
	scheduler->task = NULL;
	
	return (scheduler);
}


void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(scheduler);	
	assert(scheduler->pq);
	
	SchedulerClear(scheduler);
	PQueueDestroy(scheduler->pq);
	free(scheduler);
	
	return;	
}


ilrd_uid_t SchedulerAdd(scheduler_t *scheduler, int (*action_func)(void *param), size_t interval_in_sec, void *param)
{
	task_t *task = NULL;
	
	assert(scheduler);	
	assert(scheduler->pq);
	assert(action_func);	
	
	task =  TaskCreate(action_func, interval_in_sec, param);

	if (task == NULL)
	{
		return GetBadUid();
	}
	
	if (PQueueEnqueue(scheduler->pq, (void*)task))
	{
		TaskDestroy(task);
		scheduler->task = NULL;
		
		return (GetBadUid());
	}
	
	return (TaskGetUid(task));	
}

	   
int SchedulerRemove(scheduler_t *scheduler,ilrd_uid_t task_id)
{
	task_t *temp = NULL;
	
	assert(scheduler);	
	assert(scheduler->pq);
	
	if ((NULL != scheduler->task) && (UidIsSame(TaskGetUid(scheduler->task), task_id)))
	{
		TaskDestroy(scheduler->task);
		scheduler->task = NULL;
		
		return (0);
	
	}
	
	temp = PQueueErase(scheduler->pq, is_match_func, (void*)&task_id);
	
	if (NULL == temp)
	{
		return (1);
	}
	
	TaskDestroy(temp); 
	
	return (0);
}


size_t SchedulerSize(const scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->pq);
	
	return (PQueueSize(scheduler->pq));
}


int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->pq);
	
	return (PQueueIsEmpty(scheduler->pq));
}


int SchedulerRun(scheduler_t *scheduler)
{
	time_t remain = 0;
	time_t ttime = 0;
	int status = 0;
	
	assert(scheduler);
	
	scheduler->is_run = 1;
	
	while ((1 == scheduler->is_run) && (!SchedulerIsEmpty(scheduler)))
	{	
		ttime = time(NULL);
		if (ttime == (time_t)(-1))
		{
			SchedulerStop(scheduler);
			return 1;
		}
		
		scheduler->task = PQueueDequeue(scheduler->pq);
		
		remain = TaskGetExecutionTime(scheduler->task) - ttime;

		while ( 0  < remain)
		{
			remain = sleep((unsigned int)remain);
		}
		
		status = TaskExecute(scheduler->task);

		switch (status)
		{
			case 0: 
			{
				if (scheduler->task != NULL)
				{
					TaskDestroy(scheduler->task);
					scheduler->task = NULL;
				}
				break;
			} 
			case 1:
			{
				TaskDestroy(scheduler->task);
				scheduler->task = NULL;
				SchedulerStop(scheduler);
				return (1);
			}
			case 2:
			{
				if (TaskUpdateExecutionTime(scheduler->task) )
				{
					TaskDestroy(scheduler->task);
					scheduler->task = NULL;
					SchedulerStop(scheduler);
					return (1);
				}
				
				if(PQueueEnqueue(scheduler->pq, (void*)scheduler->task))
				{
					TaskDestroy(scheduler->task);
					scheduler->task = NULL;
					SchedulerStop(scheduler);
					return (1);
				}
				break;
			}
			default:
			{
				break;
			}	
		}		
	}
	
	if (scheduler->is_run == 0)
	{
		return (3);
	}
	
	SchedulerStop(scheduler);
	
	return (0);
}


void SchedulerStop(scheduler_t *scheduler)
{
	assert(scheduler);

	scheduler->is_run = 0;
	
	return;
}
																	 
																	
void SchedulerClear(scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->pq);
	
	while (!SchedulerIsEmpty(scheduler))
	{
		TaskDestroy(PQueueDequeue(scheduler->pq));
	}
	
	return;
}


