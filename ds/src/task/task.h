#ifndef __TASK_H__
#define __TASK_H__

#include <stddef.h>
#include <time.h>
#include "../uid/uid.h"

typedef struct task task_t;

task_t *TaskCreate(int (*action_func)(void *param), 
					size_t interval_in_sec,
					void *param);

void TaskDestroy(task_t *task);

ilrd_uid_t TaskGetUid(const task_t *task);

void TaskUpdateExecutionTime(task_t *task);

time_t TaskGetExecutionTime(task_t *task);

int TaskExecute(task_t *task);

#endif /* __TASK_H__ */
