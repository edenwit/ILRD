#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */
#include <assert.h>


#include "task.h"

#define LOOPS (3)
#define SECONDS_TO_WAIT (2)

static void TaskTest();
int ActionPrint(void *param);
/* static void PrintUid(ilrd_uid_t uid);
 */
int main()
{
	TaskTest();
	
	return 0;
}

static void TaskTest()
{
	time_t exec_time = 0;
	size_t interval = 5;
	int repeat = 0; /* 0 - no, 1- yes */
	int repeat2 = 1; /* 0 - no, 1- yes */
	task_t *task_test = TaskCreate(ActionPrint, interval, (void *)&repeat);
	task_t *task_test2 = TaskCreate(ActionPrint, interval, (void *)&repeat2);
	
	if (NULL == task_test)
	{
		printf("task pointer is NULL.\n");
	}

	if (UidIsSame(TaskGetUid(task_test), GetBadUid()))
	{
		printf("Task Create Failed.\n");
	}
	
	exec_time = TaskGetExecutionTime(task_test);
	
	sleep(interval);

	if (1 == TaskUpdateExecutionTime(task_test))
	{
		printf("TaskUpdateExecutionTime Failed. returned 1\n");
	}
			
	if ((unsigned long)TaskGetExecutionTime(task_test) != (exec_time + interval))
	{
		printf("TaskUpdateExecutionTime Failed. expacted: %ld, actual: %ld.\n", exec_time + interval, TaskGetExecutionTime(task_test));	
	}	

	printf("TaskUpdateExecutionTime Failed. actual: %ld.\n", TaskGetExecutionTime(task_test));	
	printf("TaskUpdateExecutionTime Failed. actual: %ld.\n", TaskGetExecutionTime(task_test2));	

	TaskExecute(task_test);
	TaskExecute(task_test2);
	
	/*
	ilrd_uid_t uids[LOOPS] = {0};
	ilrd_uid_t uid = GetBadUid();
	pid_t process_id = getpid();
	
	size_t i = 0;
	
	for (i = 0; i < LOOPS; ++i)
	{
		uids[i] = UidCreate();
		sleep(SECONDS_TO_WAIT);
	}
	
	for (i = 1; i < LOOPS; ++i)
	{
		if (uids[i].count != (uids[i - 1].count + 1))
		{
			printf("Count failed! pair checked: %ld-%ld.\n", uids[i].count, uids[i - 1].count);
		}
		if ((uids[i].process_ID != (uids[i - 1].process_ID) || (uids[i].process_ID != process_id)))
		{
			printf("PID failed! pair checked: %d-%d.\n", uids[i].process_ID, uids[i - 1].process_ID);	
		}
		if (uids[i].time_stamp != (uids[i - 1].time_stamp + SECONDS_TO_WAIT))
		{
			printf("Time Stamp failed! pair checked: %ld-%ld.\n", uids[i].time_stamp, uids[i - 1].time_stamp);	
		}		
	}
		
	for (i = 1; i < LOOPS; ++i)
	{
		if (UidIsSame(uids[i], uids[i - 1]))
		{
			printf("IsSame failed! pair checked: \n");
			PrintUid(uids[i]);
			PrintUid(uids[i - 1]);
		}	
	}
	
	if (!UidIsSame(uid, GetBadUid()))
	{
			printf("GetBadUid failed! pair checked: \n");
			PrintUid(uid);
			PrintUid(GetBadUid());				
	}	
	*/
	
	TaskDestroy(task_test);
	TaskDestroy(task_test2);
	
	return;
}

int ActionPrint(void *param)
{
	printf("Action Print! param receieved: %d.\n", *(int *)param);
	
	return (*(int *)&param);
}

/* static void PrintUid(ilrd_uid_t uid)
{
	printf("Uid:\ncount:%ld\nprocess_id: %d\ntime_stamp: %ld\n", uid.count, uid.process_ID, uid.time_stamp);
	
	return;
} */
