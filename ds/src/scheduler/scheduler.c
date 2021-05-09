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
		scheduler->current_task = NULL;					
	
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
	task_t *task = NULL;

	assert(scheduler);
	assert(scheduler->pq);	

	if ((NULL != scheduler->current_task) && (UidIsSame(TaskGetUid(scheduler->current_task), task_id)))
	{
		TaskDestroy(scheduler->current_task);	
		scheduler->current_task = NULL;
		
		return (0);	
	}
	
	task = (task_t *)PQueueErase(scheduler->pq, IsMatch, (void *)&task_id);
	
	if (NULL == task)
	{
		return (1);
	}
	
	
	TaskDestroy(task);
	task = NULL;	
	
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
	int remain = 0;
	
	assert(scheduler);
	assert(scheduler->pq);
	
	scheduler->is_run = 1;
	
	while ((1 == scheduler->is_run) && (!SchedulerIsEmpty(scheduler)))
	{
		current_time = time(NULL);

		if ((time_t)-1 == current_time)
		{
			SchedulerStop(scheduler);
			return (1); /* fail */
		}

		scheduler->current_task = PQueueDequeue(scheduler->pq);
		
		remain = TaskGetExecutionTime(scheduler->current_task) - current_time;
		
		while (0 < remain)
		{
			remain = sleep((unsigned int)remain);
		}
		
		/* 0- success, 1- fail, 2- repeat*/

		switch (TaskExecute(scheduler->current_task))
		{
			case 0:
			{
				if (NULL != scheduler->current_task)
				{
					TaskDestroy(scheduler->current_task);
					scheduler->current_task = NULL;
				}

				break;
			}
			case 1:
			{
				
				TaskDestroy(scheduler->current_task);
				scheduler->current_task = NULL;
				
				SchedulerStop(scheduler);
				return (2); /* fail action function */
			}
			case 2:
			{
				if (NULL == scheduler->current_task)
				{
					break;
				}
							
				if (1 == TaskUpdateExecutionTime(scheduler->current_task))
				{
					TaskDestroy(scheduler->current_task);
					scheduler->current_task = NULL;					
					SchedulerStop(scheduler);	

					return (1); /* fail */			
				}
				
				if (1 == PQueueEnqueue(scheduler->pq, (void *)scheduler->current_task))
				{
					TaskDestroy(scheduler->current_task);
					scheduler->current_task = NULL;					
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
		return (3); /* stop */
	}
	SchedulerStop(scheduler);	
	
	return (0); /* success */
	
}

void SchedulerStop(scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->pq);
	
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
	scheduler->current_task = NULL;						
	
	return;
}

int CmpExeTime(const void *data1, const void *data2)
{
	return (TaskGetExecutionTime((task_t *)data1) - TaskGetExecutionTime((task_t *)data2));
}
/*
static int IsBigger(const void *task1, const void *task2)
{
	return (TaskGetExecutionTime((task_t)task1) > TaskGetExecutionTime((task_t)task2));
}
}*/
static int IsMatch(const void *data, const void *param)
{
    return (UidIsSame(TaskGetUid((task_t *)data), (*(ilrd_uid_t *)param)));
}
