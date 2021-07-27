/*
gd watchdog.c ../../ds/src/heap_scheduler/heap_scheduler.c  -I ../../ds/include/ ../../ds/src/uid/uid.c ../../ds/src/task/task.c ../../ds/src/heap/heap.c ../../ds/src/heap_priority_queue/heap_priority_queue.c ../../ds/src/vector/vector.c  -lpthread 

*/
#define _POSIX_C_SOURCE 200112L

#include <signal.h>	   /* singals */
#include <stdlib.h>	   /* set_env */
#include <semaphore.h> /* sem_t */
#include <sys/types.h> /* pid_t */
#include <unistd.h>	   /* pause, sleep */
#include <stdio.h>	   /* printf, sprintf */
#include <assert.h>	   /* assert */
#include <fcntl.h>	   /* O_CREAT */
#include <stdatomic.h> /* atomic vars */
#include <pthread.h>   /* pthread_create */
#include <sys/wait.h>  /* waitpid */

#include "heap_scheduler.h"
#include "uid.h"
#include "watchdog.h"
#include "watchdog_utilities.h"

#define UNUSED(X) ((void)(X))

/* --------------------- global vars ---------------------------------*/
static atomic_size_t counter = 0;
static atomic_int to_stop = 0;
pthread_t thread = {0};
/* -------------------- signal handlers ------------------------------*/
void Sig1Handler(int sig);
void Sig2Handler(int sig);
/* -------------------- scheduler tasks ------------------------------*/
int SendSignal(void *pid);
int CheckSignal(void *watchdog);
int WDStopSched(void *watchdog);
/* --------------------- thread funcs ------------------------------- */
static void *RunWD(void *watchdog);
/* ------------------init helper functions -------------------------- */
static int AddTasksToSched(watchdog_t *watchdog, int check_ratio,
						   int beats_interval);
static int SetEnvVars(char *user_file_name, char *check_ratio_buf,
					  char *beats_interval_buf);

/* -------------------------------------------------------------------*/
int WDStart(char **argv, int check_ratio, int beats_interval)
{
	watchdog_t *watchdog = NULL;
	pid_t pid = 0;

	char check_ratio_buf[CHARS_IN_INT] = {'\0'};
	char beats_interval_buf[CHARS_IN_INT] = {'\0'};
	char watchdog_pid_buf[CHARS_IN_INT] = {'\0'};

	sprintf(check_ratio_buf, "%d", check_ratio);
	sprintf(beats_interval_buf, "%d", beats_interval);

	watchdog = InitSchedAndHandlers(check_ratio, beats_interval);

	if (NULL == watchdog)
	{
#ifndef NDEBUG

		printf("Failed to init Watchdog parts\n");

#endif
		return (1);
	}

	watchdog->args = (char **)argv;

	if (SetEnvVars(argv[0], check_ratio_buf, beats_interval_buf))
	{
		WatchdogCleanUp(watchdog);

		return (1);
	}

	pid = fork();

	if (-1 == pid)
	{
#ifndef NDEBUG

		printf("fork failed.\n");

#endif
		WatchdogCleanUp(watchdog);

		return (1);
	}

	/* watchdog process */
	if (0 == pid)
	{
#ifndef NDEBUG

		printf("kid created\n");

#endif
		execv(WATCHDOG_EXE, argv);
	}
	/*user process*/
	sprintf(watchdog_pid_buf, "%d", pid);

	if (setenv(WATCHDOG_PID, watchdog_pid_buf, 1))
	{
		printf("Failed to setenv on watchdog_pid\n");

		WatchdogCleanUp(watchdog);

		return (1);
	}

	watchdog->send_pid = pid;
	sem_wait(watchdog->semophore);

	if (pthread_create(&thread, NULL, RunWD, watchdog))
	{
		printf("Thread creation failed.\n");

		WatchdogCleanUp(watchdog);

		return (1);
	}

	return (0);
}

void WDStop(void)
{
	kill(atoi(getenv(WATCHDOG_PID)), SIGUSR2);
	pthread_join(thread, NULL);

	return;
}

watchdog_t *InitSchedAndHandlers(int check_ratio, int beats_interval)
{
	watchdog_t *watchdog = NULL;
	struct sigaction handler1 = {0};
	struct sigaction handler2 = {0};

	to_stop = 0;

	handler1.sa_handler = Sig1Handler;
	handler2.sa_handler = Sig2Handler;

	sigaction(SIGUSR1, &handler1, NULL);
	sigaction(SIGUSR2, &handler2, NULL);

	watchdog = (watchdog_t *)malloc(sizeof(watchdog_t));

	if (NULL == watchdog)
	{
		return (NULL);
	}

	watchdog->scheduler = HeapSchedulerCreate();

	if (NULL == watchdog->scheduler)
	{
		WatchdogCleanUp(watchdog);

		return (NULL);
	}

	watchdog->semophore = sem_open(SEMOPHORE_NAME, O_CREAT, 0666, 0);
	watchdog->is_watchdog = 0;

	if (AddTasksToSched(watchdog, check_ratio, beats_interval))
	{
		WatchdogCleanUp(watchdog);

		return (NULL);
	}

	return (watchdog);
}

static int AddTasksToSched(watchdog_t *watchdog, int check_ratio,
						   int beats_interval)
{
	ilrd_uid_t uid = {0};

	assert(watchdog);
	assert(watchdog->scheduler);

	uid = HeapSchedulerAdd(watchdog->scheduler, SendSignal, beats_interval,
						   &(watchdog->send_pid));

	if (UidIsSame(uid, GetBadUid()))
	{
		printf("HeapSchedulerAdd SendSignal failed!\n");

		return (1);
	}

	uid = HeapSchedulerAdd(watchdog->scheduler, CheckSignal,
						  (beats_interval * check_ratio), (void *)watchdog);

	if (UidIsSame(uid, GetBadUid()))
	{
		printf("HeapSchedulerAdd SendSignal failed!\n");

		return (1);
	}

	uid = HeapSchedulerAdd(watchdog->scheduler, WDStopSched,
						  (beats_interval / 2), (void *)watchdog);

	if (UidIsSame(uid, GetBadUid()))
	{
		printf("HeapSchedulerAdd SendSignal failed!\n");

		return (1);
	}

	return (0);
}

static int SetEnvVars(char *user_file_name, char *check_ratio_buf,
					  char *beats_interval_buf)
{
	if (setenv(USER_FILE_NAME, user_file_name, 0))
	{
		printf("Failed to setenv on beats_interval\n");

		return (1);
	}

	if (setenv(BEATS_INTERVAL, beats_interval_buf, 0))
	{
		printf("Failed to setenv on beats_interval\n");

		return (1);
	}

	if (setenv(CHECK_RATIO, check_ratio_buf, 0))
	{
		printf("Failed to setenv on check_ratio\n");

		return (1);
	}

	return (0);
}

void Sig1Handler(int sig)
{
	UNUSED(sig);

	++counter;

#ifndef NDEBUG

	printf("%d recieved SIGUSR1. counter: %ld\n", getpid(), counter);

#endif

	return;
}

void Sig2Handler(int sig)
{
	UNUSED(sig);

	atomic_exchange(&to_stop, 1);

#ifndef NDEBUG

	printf("%d recieved SIGUSR2.\n", getpid());

#endif

	return;
}

int SendSignal(void *pid)
{
	assert(pid);

	if (to_stop)
	{
		return (TASK_DONT_REPEAT);
	}

	kill(*((pid_t *)pid), SIGUSR1);

	return (TASK_REPEAT);
}

int CheckSignal(void *watchdog)
{
	pid_t pid = 0;
	watchdog_t *watchdog_ptr = (watchdog_t *)watchdog;
	char watchdog_pid_buf[10] = {'\0'};

	assert(watchdog);

	if (to_stop)
	{
		return (TASK_DONT_REPEAT);
	}

	if (0 < counter)
	{
		counter = 0;

		return (TASK_REPEAT);
	}

#ifndef NDEBUG

	printf("counter is 0. very bad!.\n");

#endif

	if (watchdog_ptr->is_watchdog)
	{

#ifndef NDEBUG

		printf("User dead. Start over!\n");

#endif

		execv(getenv(USER_FILE_NAME), watchdog_ptr->args);
	}
	else
	{

#ifndef NDEBUG

		printf("Watchdog dead. Start over!\n");

#endif

		kill(watchdog_ptr->send_pid, SIGTERM);
		waitpid(watchdog_ptr->send_pid, NULL, 0);

		pid = fork();

		if (-1 == pid)
		{
			printf("fork failed.\n");

			WatchdogCleanUp(watchdog_ptr);

			return (1);
		}

		/* watchdog process */
		else if (0 == pid)
		{

#ifndef NDEBUG

			printf("kid created\n");

#endif

			execv(WATCHDOG_EXE, watchdog_ptr->args);
		}
		/* user process */

		counter = 1;

		watchdog_ptr->send_pid = pid;
		sem_wait(watchdog_ptr->semophore);
		sprintf(watchdog_pid_buf, "%d", pid);

		if (setenv(WATCHDOG_PID, watchdog_pid_buf, 1))
		{
			printf("Failed to setenv on watchdog_pid\n");

			return (1);
		}
	}

	return (TASK_REPEAT);
}

static void *RunWD(void *watchdog)
{
	watchdog_t *watchdog_ptr = (watchdog_t *)watchdog;

	assert(watchdog);

	HeapSchedulerRun(watchdog_ptr->scheduler);

	WatchdogCleanUp(watchdog_ptr);

	return (NULL);
}

int WDStopSched(void *watchdog)
{
	watchdog_t *watchdog_ptr = (watchdog_t *)watchdog;

	assert(watchdog);

	if (to_stop)
	{
		HeapSchedulerStop(watchdog_ptr->scheduler);

		/* in watchdog process */
		if (watchdog_ptr->is_watchdog)
		{
			kill(watchdog_ptr->send_pid, SIGUSR2);
		}
		else
		{
			waitpid(watchdog_ptr->send_pid, NULL, 0);
		}

		return (TASK_DONT_REPEAT);
	}

	return (TASK_REPEAT);
}

void WatchdogCleanUp(watchdog_t *watchdog)
{
	assert(watchdog);

	HeapSchedulerDestroy(watchdog->scheduler);
	sem_close(watchdog->semophore);
	sem_unlink(SEMOPHORE_NAME);
	watchdog->args = NULL;
	watchdog->is_watchdog = 0;
	watchdog->scheduler = NULL;
	watchdog->semophore = NULL;
	watchdog->send_pid = 0;

	free(watchdog);

	return;
}