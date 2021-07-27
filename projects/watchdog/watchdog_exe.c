/*
gd wdexe.c watchdog.c ../../ds/src/heap_scheduler/heap_scheduler.c  -I ../../ds/include/ ../../ds/src/uid/uid.c ../../ds/src/task/task.c ../../ds/src/heap/heap.c ../../ds/src/heap_priority_queue/heap_priority_queue.c ../../ds/src/vector/vector.c  -pthread watchdog.h -o watchdog
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <semaphore.h>

#include "heap_scheduler.h"
#include "watchdog.h"
#include "watchdog_utilities.h"

#define UNUSED(X) ((void)(X))

#ifndef NDEBUG

static void PrintTheDog();

#endif

int main(int argc, char **argv)
{
	watchdog_t *watchdog = NULL;
	int check_ratio = 0;
	int beats_interval = 0;

	UNUSED(argc);

#ifndef NDEBUG

	PrintTheDog();

#endif

	check_ratio = atoi(getenv(CHECK_RATIO));
	beats_interval = atoi(getenv(BEATS_INTERVAL));

	watchdog = InitSchedAndHandlers(check_ratio, beats_interval);

	watchdog->args = argv;

	if (NULL == watchdog)
	{
		printf("Failed to init Watchdog parts\n");
		return (1);
	}

	watchdog->send_pid = getppid();
	watchdog->is_watchdog = 1;

	sem_post(watchdog->semophore);

	HeapSchedulerRun(watchdog->scheduler);

	WatchdogCleanUp(watchdog);

#ifndef NDEBUG

	printf("WD sched destroyed\n");

#endif

	return (0);
}

#ifndef NDEBUG

static void PrintTheDog()
{
	puts("         ,--._______,-.\n \
       ,','  ,    .  ,_`-.\n \
      / /  ,' , _` ``. |  )       `-..\n \
     (,';''''`/ '''`-._ ` \\/ ______    \\ \n \
       : ,o.-`- ,o.  )\\` -'      `---.))\n \
       : , d8b ^-.   '|   `.      `    `.\n \
       |/ __:_     `. |  ,  `       `    \\ \n \
       | ( ,-.`-.    ;'  ;   `       :    ;\n \
       | |  ,   `.      /     ;      :    \\ \n \
       ;-'`:::._,`.__),'             :     ;\n \
      / ,  `-   `--                  ;     |");
	puts("     /  \\                   `       ,      |\n \
    (    `     :              :    ,\\      |\n \
     \\   `.    :     :        :  ,'  \\    :\n \
      \\    `|-- `     \\ ,'    ,-'     :-.-';\n \
      :     |`--.______;     |        :    :\n \
       :    /           |    |         |   \\ \n \
       |    ;           ;    ;        /     ;\n \
     _/--' |           :`-- /         \\_:_:_|\n \
   ,',','  |           |___ \\ \n \
   `^._,--'           / , , .)\n \
                      `-._,-''\n");

	return;
}

#endif