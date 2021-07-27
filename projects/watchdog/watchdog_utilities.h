#ifndef __watchdog_utilities_H__
#define __watchdog_utilities_H__

#include <semaphore.h> /* sem_t */

#define BEATS_INTERVAL "BEATS_INTERVAL"
#define CHECK_RATIO "CHECK_RATIO"
#define USER_FILE_NAME "USER_FILE_NAME"
#define WATCHDOG_PID "WATCHDOG_PID"
#define WATCHDOG_EXE "./watchdog"
#define SEMOPHORE_NAME "watchdog102semo"
#define CHARS_IN_INT (10)


typedef struct watchdog
{
    scheduler_t *scheduler;
    sem_t *semophore;
    char **args;
    pid_t send_pid;
    int is_watchdog;
} watchdog_t;

enum task_status
{
    TASK_DONT_REPEAT,
    TASK_FAIL,
    TASK_REPEAT
};

/*------------------------------ funcs declarations ----------------------- */
watchdog_t *InitSchedAndHandlers(int check_ratio, int beats_interval);

void WatchdogCleanUp(watchdog_t *watchdog);

#endif /* __watchdog_utilities_H__ */
