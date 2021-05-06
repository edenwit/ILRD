#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../task/task.h"

struct task
{
	ilrd_uid_t uid;
	int (*action_func)(void *param);
	void *param;
	size_t interval;
	time_t execution_time;
};

task_t *TaskCreate(int (*action_func)(void *param), 
					size_t interval_in_sec,
					void *param)
{
	ilrd_uid_t uid = UidCreate();
	
	task_t *task = (task_t *)malloc(sizeof(task_t));
	
	if (NULL != task)
	{
		return (NULL);
	}
	
	task->uid = uid;
	task->action_func = action_func;
	task->interval = interval_in_sec;
	task->execution_time = time(NULL) + interval_in_sec;
	task->param = param;	
	
	return (task);						
}					

void TaskDestroy(task_t *task)
{
	assert(task);
	free(task);
	
	return;
}

ilrd_uid_t TaskGetUid(const task_t *task)
{
	assert(task);
	
	return (task->uid);	
}

void TaskUpdateExecutionTime(task_t *task)
{
	assert(task);
	
	task->execution_time += task->interval;
	
	return;	
}

time_t TaskGetExecutionTime(task_t *task)
{
	assert(task);
	
	return (task->execution_time);	
}

int TaskExecute(task_t *task)
{
	return task->action_func(task->param);
}
