#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <time.h> 		/* time_t */

#include "task.h"

struct task
{
	ilrd_uid_t uid;
	int (*action_func)(void *param);
/*	void (*cleanup_func)(void *param);*/
	void *param;
	size_t interval;
	time_t execution_time;
};



task_t *TaskCreate(int (*action_func)(void *param), 
					size_t interval_in_sec,
					void *param)
{
	ilrd_uid_t uid = UidCreate();
	time_t ttime = time(NULL);
	task_t *task = NULL;
	
	assert(action_func);	

	if ((time_t)-1 == ttime)
	{
		return NULL;
	}
		
	if (UidIsSame(uid, GetBadUid()))
	{
		return (NULL);
	}
	
	task = (task_t *)malloc(sizeof(task_t));
	
	if (NULL == task)
	{
		return (NULL);
	}
	
	task->execution_time = (ttime + interval_in_sec);
	task->uid = uid;
	task->action_func = action_func;
	task->interval = interval_in_sec;
	task->param = param;	
	
	return (task);
}					

void TaskDestroy(task_t *task)
{
	assert(task);
	
	task->param = NULL;
	task->action_func = NULL;
	task->execution_time = (time_t)-1;
	task->uid = GetBadUid();
	task->interval = 0;
	
	free(task);
	
	return;
}

ilrd_uid_t TaskGetUid(const task_t *task)
{
	assert(task);
	
	return (task->uid);	
}

int TaskUpdateExecutionTime(task_t *task)
{
	time_t ttime = 0;
	
	assert(task);

	ttime = time(NULL);
	
	if ((time_t)-1 == ttime)
	{
		return (1);
	}
	
	task->execution_time = (ttime + task->interval);
	
	return (0);
}

time_t TaskGetExecutionTime(task_t *task)
{
	assert(task);
	
	return (task->execution_time);	
}

/* 0- success, 1- fail, 2- repeat*/
int TaskExecute(task_t *task)
{
	assert(task);

	return (task->action_func(task->param));
}
