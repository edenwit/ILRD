#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */

#include "uid.h"

#define LOOPS (3)
#define SECONDS_TO_WAIT (2)

static void UidTest();
static void PrintUid(ilrd_uid_t uid);

int main()
{
	UidTest();
	
	return 0;
}

static void UidTest()
{
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
	
	return;
}

static void PrintUid(ilrd_uid_t uid)
{
	printf("Uid:\ncount:%ld\nprocess_id: %d\ntime_stamp: %ld\n", uid.count, uid.process_ID, uid.time_stamp);
	
	return;
}
