#ifndef __watchdog_utilities_H__
#define __watchdog_utilities_H__

#include <semaphore.h> /* sem_t */

typedef struct watchdog
{
	scheduler_t *scheduler;
/* 	size_t counter;
 */	pid_t send_pid;
    sem_t *semophore;
    int is_watchdog;
	/* int flag_for_end; */
} watchdog_t;

int InitSchedAndHandlers(watchdog_t **watchdog, int check_ratio, int beats_interval);



#endif /* __watchdog_utilities_H__ */
