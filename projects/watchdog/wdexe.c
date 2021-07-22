#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include "heap_scheduler.h"
#include "watchdog.h"
#include "watchdog_utilities.h"
#include <semaphore.h>

#define UNUSED(X) ((void)(X))

int main(int argc, char **argv)
{
	watchdog_t *watchdog = NULL;
	int check_ratio = 0;
	int beats_interval = 0;;

	UNUSED(argc);

	printf("watchdog begin\n");


	watchdog = (watchdog_t *)malloc(sizeof(watchdog_t));

	if (NULL == watchdog)
	{
		return (1);
	}

/* 	check_ratio = atoi(argv[1]);
	beats_interval = atoi(argv[2]); */
	printf("watchdog exe say hello\n");

/* 	if(InitSchedAndHandlers(&watchdog, check_ratio, beats_interval))
 */	if(InitSchedAndHandlers(&watchdog, 5, 1))

	{
		printf("Failed to init Watchdog parts\n");
		free(watchdog);
		return(1);
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