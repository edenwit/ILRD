#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <semaphore.h>

#include "heap_scheduler.h"
#include "watchdog.h"
#include "watchdog_utilities.h"

#define UNUSED(X) ((void)(X))

int main()
{
	watchdog_t *watchdog = NULL;
	int check_ratio = 0;
	int beats_interval = 0;

	printf("watchdog begin\n");

	watchdog = (watchdog_t *)malloc(sizeof(watchdog_t));

	if (NULL == watchdog)
	{
		return (1);
	}

	printf("wtf man\n");
	check_ratio = atoi(getenv(CHECK_RATIO));
	beats_interval = atoi(getenv(BEATS_INTERVAL)); 
	printf("watchdog exe say hello\n");

	/* 	if(InitSchedAndHandlers(&watchdog, check_ratio, beats_interval))
 */
	if (InitSchedAndHandlers(&watchdog, check_ratio, beats_interval))

	{
		printf("Failed to init Watchdog parts\n");
		free(watchdog);
		return (1);
	}
	else
	{
		printf("houdy\n");
	}
	watchdog->send_pid = getppid();
	watchdog->is_watchdog = 1;
	printf("after watchdog init\n");

	sem_post(watchdog->semophore);

	HeapSchedulerRun(watchdog->scheduler);

	return (0);
}