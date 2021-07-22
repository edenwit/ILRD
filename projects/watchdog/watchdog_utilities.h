#ifndef __watchdog_utilities_H__
#define __watchdog_utilities_H__


#include <semaphore.h> /* sem_t */

#define BEATS_INTERVAL "BEATS_INTERVAL"
#define CHECK_RATIO "CHECK_RATIO"
#define USER_FILE_NAME "USER_FILE_NAME"

typedef struct watchdog
{
	scheduler_t *scheduler;
/* 	size_t counter;
 */	pid_t send_pid;
    sem_t *semophore;
    int is_watchdog;
    char **args;
	/* int flag_for_end; */
} watchdog_t;

enum task_status
{
    TASK_DONT_REPEAT,
    TASK_FAIL,
    TASK_REPEAT
};

int InitSchedAndHandlers(watchdog_t **watchdog, int check_ratio, int beats_interval);



#endif /* __watchdog_utilities_H__ */
