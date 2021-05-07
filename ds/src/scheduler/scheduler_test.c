#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */
#include <assert.h>


#include "scheduler.h"

#define LOOPS (3)
#define SECONDS_TO_WAIT (2)

static void SchedulerTest();
int ActionPrint(void *param);
static void PrintUid(ilrd_uid_t uid);

int main()
{
	SchedulerTest();
	
	return 0;
}

static void SchedulerTest()
{
	time_t exec_time = 0;
	size_t interval = 1;
	ilrd_uid_t uid = {0};
	int repeat = 0; /* 0 - no, 1- yes */
	int repeat2 = 2; /* 0 - no, 1- yes */
	int run_status = 0;
	scheduler_t *scheduler_test = SchedulerCreate();
	scheduler_t *scheduler_test2 = SchedulerCreate();
	
	
	if (NULL == scheduler_test)
	{
		printf("scheduler pointer is NULL.\n");
	}



	if (!SchedulerIsEmpty(scheduler_test))
	{
		printf("SchedulerIsEmpty Failed.\n");	
	}
	
	uid = SchedulerAdd(scheduler_test, ActionPrint, interval, (void *)&repeat);
	
	if (UidIsSame(uid, GetBadUid()))
	{
			printf("GetBadUid failed! pair checked: \n");
			PrintUid(uid);
			PrintUid(GetBadUid());				
	}	
	
	if (SchedulerIsEmpty(scheduler_test))
	{
		printf("SchedulerAdd Failed scheduler still empty.\n");	
	}
	
	if (1 != SchedulerSize(scheduler_test))
	{
		printf("SchedulerSize Failed scheduler still empty.\n");			
	}
	
	run_status = SchedulerRun(scheduler_test);
	
	printf("Run stopped at status %d\n", run_status);
	
	if (!SchedulerIsEmpty(scheduler_test))
	{
		printf("SchedulerIsEmpty Failed.\n");	
	}	

	uid = SchedulerAdd(scheduler_test, ActionPrint, interval, (void *)&repeat2);
	
	if (UidIsSame(uid, GetBadUid()))
	{
			printf("GetBadUid failed! pair checked: \n");
			PrintUid(uid);
			PrintUid(GetBadUid());				
	}	
		
	run_status = SchedulerRun(scheduler_test);
	
	printf("Run stopped at status %d\n", run_status);
	
			
/*	
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
			
	if (TaskGetExecutionTime(task_test) != exec_time + interval)
	{
		printf("TaskUpdateExecutionTime Failed. expacted: %ld, actual: %ld.\n", exec_time + interval, TaskGetExecutionTime(task_test));	
	}	

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
	
	SchedulerDestroy(scheduler_test);
	SchedulerDestroy(scheduler_test2);
	
	return;
}




int ActionPrint(void *param)
{
	printf("Action Print! param receieved: %d.\n", *(int *)param);
	
	return (*(int *)param);
}

static void PrintUid(ilrd_uid_t uid)
{
	printf("Uid:\ncount:%ld\nprocess_id: %d\ntime_stamp: %ld\n", uid.count, uid.process_ID, uid.time_stamp);
	
	return;
}
