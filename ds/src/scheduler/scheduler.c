#include <time.h> 		/* struct tm */
#include <stddef.h> 	/* size_t */
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "scheduler.h"
#include "../task/task.h"

/*typedef struct scheduler scheduler_t;*/

struct scheduler
{
	int is_run; 
	pq_t *pq;
	task_t *current_task;
};

/*static int IsBigger(const void *task1, const void *task2);*/
int CmpExeTime(const void *cur, const void *par);
static int IsMatch(const void *data, const void *param);

scheduler_t *SchedulerCreate	(void)
{
	scheduler_t *scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	
	if (NULL == scheduler)
	{
		return (NULL);
	}
	
	scheduler->pq = PQueueCreate(CmpExeTime);
	
	if (NULL == scheduler->pq)
	{
		free(scheduler);

		return (NULL);	
	}
	
	scheduler->is_run = 0;
	scheduler->current_task = NULL;
	
	return (scheduler);
}

void  SchedulerDestroy(scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->pq);
	
	SchedulerClear(scheduler);
	PQueueDestroy(scheduler->pq);
	free(scheduler);	
	
	return;	
}

ilrd_uid_t SchedulerAdd(scheduler_t *scheduler, 
			int (*action_func)(void *param), 
			size_t interval_in_sec, void *param)
{
	task_t *task = NULL;
	
	assert(scheduler);
	assert(scheduler->pq);
	
	task = TaskCreate(action_func, interval_in_sec, param);

	if (NULL == task)
	{
		return GetBadUid();
	}
	
	if (1 == PQueueEnqueue(scheduler->pq, (void *)task))
	{
		TaskDestroy(task);
	
		return GetBadUid();		
	}
	
	return TaskGetUid(task);	
}
/*																	  *	periodical and run each x
																	  *	seconds, or a single 
																	  * instance to be executed
																	  * in x seconds. time complexity: O(n) 
																	  */	   
int SchedulerRemove(scheduler_t *scheduler, ilrd_uid_t task_id)
{
	void *task = NULL;

	assert(scheduler);
	assert(scheduler->pq);	

	task = PQueueErase(scheduler->pq, IsMatch, (void *)&task_id);
	
	if (NULL == task)
	{
		return (1);
	}
	
	if (UidIsSame(TaskGetUid(scheduler->current_task), task_id))
	{
		TaskDestroy(scheduler->current_task);	
		scheduler->current_task = NULL;
		
		return (0);	
	}
	
	TaskDestroy(task);
	
	return (0);
}

size_t SchedulerSize(const scheduler_t *scheduler) 	 /* time complexity: O(n) */
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

/* 0- success, 1- fail, 2- action_function_fail, 3- stopped*/
int SchedulerRun(scheduler_t *scheduler)
{
	time_t current_time = (time_t)-1; 
	int status = 0;	
	int remain = 0;
	
	assert(scheduler);
	assert(scheduler->pq);
	
	scheduler->is_run = 1;
	
	while ((1 == scheduler->is_run) && (!SchedulerIsEmpty(scheduler)))
	{
		current_time = time(NULL);

		if ((time_t)-1 == current_time)
		{
			return (1); /* fail */
		}

		scheduler->current_task = PQueueDequeue(scheduler->pq);
		
		remain = TaskGetExecutionTime(scheduler->current_task) - (unsigned int)current_time;
		
		while (0 != remain)
		{
			remain = sleep(remain);
		}
		
		/* 0- success, 1- fail, 2- repeat*/
		status = TaskExecute(scheduler->current_task);
		printf("status: %d\n", status);
		switch (status)
		{
			case 0:
			{
				TaskDestroy(scheduler->current_task);
				break;
			}
			case 1:
			{
				TaskDestroy(scheduler->current_task);
				
				SchedulerStop(scheduler);
				return (2); /* fail action function */
			}
			case 2:
			{
				printf("pick me!\n");
				if (1 == TaskUpdateExecutionTime(scheduler->current_task))
				{
					TaskDestroy(scheduler->current_task);
					SchedulerStop(scheduler);	

					return (1); /* fail */			
				}
				
				if (1 == PQueueEnqueue(scheduler->pq, (void *)scheduler->current_task))
				{
					TaskDestroy(scheduler->current_task);
					SchedulerStop(scheduler);		
								
					return (1); /* fail */
				}				
				break;
			}
			default:
			{
				break;
			}
		}
	}
	if (0 == scheduler->is_run)
	{
		SchedulerStop(scheduler);
		return (3); /* stop */
	}
	SchedulerStop(scheduler);	
	
	return (0); /* success */
	
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

int CmpExeTime(const void *cur, const void *par)
{
	return (*(time_t*)cur - *(time_t*)par);
}
/*
static int IsBigger(const void *task1, const void *task2)
{
	return (TaskGetExecutionTime((task_t)task1) > TaskGetExecutionTime((task_t)task2));
}
}*/
static int IsMatch(const void *data, const void *param)
{
    return (UidIsSame(TaskGetUid((task_t *)data), (*(ilrd_uid_t *)&param)));
}


