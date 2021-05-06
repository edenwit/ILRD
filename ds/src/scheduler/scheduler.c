#include <time.h> 		/* struct tm */
#include <stddef.h> 	/* size_t */

/*#include "uid.h"*/ 
#include "task.h"
#include "priority_queue.h" 

/*
typedef struct scheduler scheduler_t
{
	p_queue *pq;
	int run_status; 0 - off, 1 - on
};
*/

scheduler_t *SchedulerCreate	(void)
{
	scheduler_t *scheduler = (scheduler_t)malloc(sizeof(scheduler_t));
	
	if (NULL == scheduler)
	{
		return (NULL);
	}
	
	scheduler->pq = PQCreate(Cmp_Num);
	
	if (NULL == scheduler->pq)
	{
		free(scheduler);

		return (NULL);	
	}
	
	scheduler->run_status = 0;
	
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
	
	if (!PQueueEnqueue(scheduler->pq, (void *)task))
	{
		TaskDestroy(task);
	
		return GetBadUid();		
	}
	
	return TaskGetUid(task);	
}
																	  *	periodical and run each x
																	  *	seconds, or a single 
																	  * instance to be executed
																	  * in x seconds. time complexity: O(n) 
																	  */	   
int 		 SchedulerRemove	(scheduler_t *scheduler,            
								ilrd_uid_t task)
{
	void *task = NULL;

	assert(scheduler);
	assert(scheduler->pq);	

	data = PQueueErase(scheduler->pq);
	
	if (NULL == data)
	{
		return (1);
	}
	
	TaskDestroy(task);
	
	return (0);
}

size_t 	 	 SchedulerSize		(const scheduler_t *scheduler) 	 /* time complexity: O(n) */
{
	assert(scheduler);
	assert(scheduler->pq);
	
	return (PQueueSize(scheduler->pq));	
}

int SchedulerIsEmpty	(const scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->pq);
	
	return (PQueueIsEmpty(scheduler->pq));		
}

/* 0- success, 1- fail, 2- action_function_fail, 3- stopped*/
int SchedulerRun(scheduler_t *scheduler)
{
	time_t ttime = (time_t)-1; 
	task_t *current_task = NULL;
	int status = 0;
	int run_status = 0;
	
	assert(scheduler);
	assert(scheduler->pq);
	
	while ((1 == scheduler->run_status) && (!SchedulerIsEmpty(scheduler)))
	{
		current_task = PQueueDequeue(scheduler->pq);
		
		ttime = time(NULL);
		
		if ((time_t)-1 == ttime)
		{
			return (1);
		}
		remain = TaskGetExecutionTime(current_task) - ttime;
		
		while (0 != remain)
		{
			remain = sleep(remain);
		}
		
		/* 0- success, 1- fail, 2- repeat*/
		status = TaskExecute(current_task);
		
		switch (status)
		{
			case 0:
			{
				TaskDestroy(current_task);
				
				break;
			}
			case 1:
			{
				TaskDestroy(current_task);
				run_status = 2;
				
				break;
			}
			
		
		}
		{
			return (2);
		}
		
		if (2 == TaskExecute(current_task))
		{
			
		}

		
		
	}
}
void    	 SchedulerStop		(scheduler_t *scheduler)
{
	assert(scheduler);
	
	scheduler->run_status = 0;
	
	return;	
}

void 		 SchedulerClear		(scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->pq);
	
	while (!PQueueIsEmpty(scheduler))
	{
		TaskDestroy(PQueueDequeue(scheduler->pq));
	}
	
	return;
}
static int IsBigger(const void *task1, const void *task2) /*data is what the user gives*/
{
	return (TaskGetExecutionTime((task_t)task1) > TaskGetExecutionTime((task_t)task2));
}

int Cmp_Num(const void *cur, const void *par)
{
	return (*(int*)cur - *(int*)par);
}

