#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */
#include <assert.h>

#include "heap_scheduler.h"

#define LOOPS (3)
#define SECONDS_TO_WAIT (2)

static void SchedulerTest();
int ActionPrint(void *param);
int ActionPrint2(void *param);
static void PrintUid(ilrd_uid_t uid);
int StopTheRun(void *scheduler);
int PrintCat(void *param);
int AddPrintCatToScheduler(void *scheduler);
int CommitSuicide(void *scheduler);

typedef struct sched_and_uid
{
	scheduler_t *scheduler;
	ilrd_uid_t uid;
}suicide_kit;

int main()
{
	SchedulerTest();
	
	return 0;
}

static void SchedulerTest()
{
	suicide_kit sui = {0};
	size_t interval = 2;
	size_t interval2 = 20;	
	size_t interval3 = 1;
	size_t interval4 = 8;		
	ilrd_uid_t uid = {0};
	int repeat = 0; /* 0 - no, 2- yes */
	int repeat2 = 2; /* 0 - no, 2- yes */
	int run_status = 0;
	scheduler_t *scheduler_test = SchedulerCreate();
	
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

	uid = SchedulerAdd(scheduler_test, ActionPrint2, interval3, (void *)&repeat2);
	
	if (UidIsSame(uid, GetBadUid()))
	{
			printf("GetBadUid failed! pair checked: \n");
			PrintUid(uid);
			PrintUid(GetBadUid());				
	}	

	uid = SchedulerAdd(scheduler_test, StopTheRun, interval2, (void *)scheduler_test);
	
	if (UidIsSame(uid, GetBadUid()))
	{
			printf("GetBadUid failed! pair checked: \n");
			PrintUid(uid);
			PrintUid(GetBadUid());				
	}	
	
	if (3 != SchedulerSize(scheduler_test))
	{
		printf("SchedulerSize Failed. Supposed to have 2 tasks, has %ld.\n", SchedulerSize(scheduler_test));			
	}
	
	
	uid = SchedulerAdd(scheduler_test, AddPrintCatToScheduler, 0, (void *)scheduler_test);
	
	if (UidIsSame(uid, GetBadUid()))
	{
			printf("GetBadUid failed! pair checked: \n");
			PrintUid(uid);
			PrintUid(GetBadUid());				
	}	
	
	sui.scheduler = scheduler_test;

	sui.uid = SchedulerAdd(scheduler_test, CommitSuicide, interval4, (void *)&sui);

	/*
	printf("sui.uid:\n");
	PrintUid(*(ilrd_uid_t *)sui.uid);	*/
	
	if (UidIsSame(uid, GetBadUid()))
	{
			printf("GetBadUid failed! pair checked: \n");
			PrintUid(uid);
			PrintUid(GetBadUid());				
	}		
	
	/*sleep(10);*/
		
	run_status = SchedulerRun(scheduler_test);
	
	printf("Run stopped at status %d\n", run_status);
	
	if (2 != SchedulerSize(scheduler_test))
	{
		printf("SchedulerSize Failed. Supposed to have 2 tasks, has %ld.\n", SchedulerSize(scheduler_test));			
	}

	return;
}

int ActionPrint(void *param)
{
	printf("Action Print!1 param receieved: %d.\n", *(int *)param);
	
	return (*(int *)param);
}

int ActionPrint2(void *param)
{
	printf("Action Print!2 param receieved: %d.\n", *(int *)param);
	
	return (*(int *)param);
}

int CommitSuicide(void *sui)
{
	int status = 0;
	/*suicide_kit su_kit = (suicide_kit *)sui;*/
	printf("Im dying!\n");
	status = SchedulerRemove((((suicide_kit *)sui)->scheduler), (((suicide_kit *)sui)->uid));
	
	return status;	
}

int StopTheRun(void *scheduler)
{
	printf("Stopping run!\n");
	
	SchedulerStop((scheduler_t *)scheduler);
	
	return 0;
}

int PrintCat(void *param)
{
	printf("    *               MMM8&&&            * \n");
	printf("                  MMMM88&&&&&    .		 \n");
	printf("                 MMMM88&&&&&&&			 \n");
	printf("     *           MMM88&&&&&&&&			\n");
	printf("                 MMM88&&&&&&&&			\n");
	printf("                  MMM88&&&&&&		\n");
	printf("                    MMM8&&&      *\n");
	printf("          |\\___/| \n");
	printf("         =) ^Y^ (=            .              ' \n");
	printf("          \\ ^  / \n");
	printf("           )=*=(       * \n");
	printf("          /     \\ \n");
	printf("          |     |\\ \n");
	printf("         /| | | |\\ \n");
	printf("         \\| | |_|/\\ \n");
	printf("  _/\\_//_// ___/\\_/\\_/\\_/\\_/\\_/\\_/\\_\\ \n");
	printf("  |  |  |  | \\_) |  |  |  |  |  |  | \n");
	printf("  |  |  |  |  |  |  |  |  |  |  |  | \n");
	printf("  |  |  |  |  |  |  |  |  |  |  |  |  \n");
	printf("  |  |  |  |  |  |  |  |  |  |  |  |  \n");

	return (*(int *)param);
}

int AddPrintCatToScheduler(void *scheduler)
{
	int repeat = 0;
	ilrd_uid_t uid = SchedulerAdd((scheduler_t *)scheduler, PrintCat, 1, (void *)&repeat);
	
	if (UidIsSame(uid, GetBadUid()))
	{
			printf("GetBadUid failed! pair checked: \n");
			PrintUid(uid);
			PrintUid(GetBadUid());	
			
			return (1);			
	}	
	
	return (0);
}

static void PrintUid(ilrd_uid_t uid)
{
	printf("Uid:\ncount:%ld\nprocess_id: %d\ntime_stamp: %ld\n", uid.count, uid.process_ID, uid.time_stamp);
	
	return;
}
