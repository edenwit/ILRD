/*
gd watchdog.c ../../ds/src/heap_scheduler/heap_scheduler.c  -I ../../ds/include/ ../../ds/src/uid/uid.c ../../ds/src/task/task.c ../../ds/src/heap/heap.c ../../ds/src/heap_priority_queue/heap_priority_queue.c ../../ds/src/vector/vector.c  -lpthread 

*/


#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 199309L

#include <signal.h> /* singals */
#include <stdlib.h>
#include <semaphore.h> /* sem_t */
#include <sys/types.h> /* pid_t */
#include <unistd.h>	   /* pause, sleep */
#include <stdio.h> /* printf, sprintf */
#include <assert.h> /* assert */
#include <fcntl.h> /* O_CREAT */
#include <stdatomic.h> /* O_CREAT */
#include <pthread.h> /* pthread_create */


#include "heap_scheduler.h"
#include "uid.h"
#include "watchdog.h"
#include "watchdog_utilities.h"


#define UNUSED(X) ((void)(X))

static atomic_size_t counter = 0;


void Sig1Handler(int sig, siginfo_t *siginfo, void *data);
void Sig2Handler(int sig, siginfo_t *siginfo, void *data);

int SendSignal(void *pid);
int CheckSignal(void *watchdog);

void *RunWD(void *scehduler);

int WDStart(char *const argv[], int check_ratio, int beats_interval)
{
	watchdog_t *watchdog = (watchdog_t *)malloc(sizeof(watchdog_t));
	pid_t pid = 0;
	pthread_t thread = {0};

	char *myargs [] = {NULL};
    char *myenv [] = { NULL };
	char *args[3] = {NULL};

	int value = 0;

	if (NULL == watchdog)
	{
		printf("Failed to malloc Watchdog pointer\n");
		return (1);
	}

	if(InitSchedAndHandlers(&watchdog, check_ratio, beats_interval))
	{
		printf("Failed to init Watchdog parts\n");
		free(watchdog);
		return(1);
	}

	pid = fork();

	if (-1 == pid)
	{
		printf("fork failed.\n");
		sem_post(watchdog->semophore);

		return (1);
	}

	/* child process */
	else if (0 == pid)
	{
		printf("kid created\n");
/* 		args[0] = argv[0];
		sprintf(args[1], "%d", check_ratio);
		sprintf(args[2], "%d", beats_interval); */

		execve ("./watchdog", myargs, myenv);
	}

	else
	{
		watchdog->send_pid = pid;
		printf("parent waiting\n");
		sem_getvalue(watchdog->semophore, &value);
		printf("sem value before wait: %d\n", value);
		
		sem_wait(watchdog->semophore);
		printf("sem value after wait: %d\n", value);

		if (pthread_create(&thread, NULL, RunWD, watchdog->scheduler))
		{
			/* take care of failure */;
		}

		pthread_detach(thread);
	}

	return (0);
}

void WDStop(void)
{
}

int InitSchedAndHandlers(watchdog_t **watchdog, int check_ratio, int beats_interval)
{
	ilrd_uid_t uid = {0};
	struct sigaction handler1 = {0};
	struct sigaction handler2 = {0};

	int repeat_arr[3] = {0, 1, 2}; /* 0 - no, 1- fail,  2- yes */

	assert(watchdog);

	if (NULL == watchdog)
	{
		return (1);
	}

	(*watchdog)->scheduler = HeapSchedulerCreate();

	if (NULL == (*watchdog)->scheduler)
	{
		free((*watchdog));
		return (1);
	}

	handler1.sa_sigaction = Sig1Handler;
	handler1.sa_flags = SA_SIGINFO;

	handler2.sa_sigaction = Sig2Handler;
	handler2.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &handler1, NULL);
 	sigaction(SIGUSR2, &handler2, NULL);

    (*watchdog)->semophore = sem_open("dog_semo", O_CREAT, 0666, 0);
	(*watchdog)->is_watchdog = 0;

	uid = HeapSchedulerAdd((*watchdog)->scheduler, SendSignal, beats_interval, &((*watchdog)->send_pid));

	if (UidIsSame(uid, GetBadUid()))
	{
			printf("HeapSchedulerAdd SendSignal failed!\n");
			return (1);
	}

	uid = HeapSchedulerAdd((*watchdog)->scheduler, CheckSignal, beats_interval * check_ratio, watchdog);

	if (UidIsSame(uid, GetBadUid()))
	{
			printf("HeapSchedulerAdd SendSignal failed!\n");
			return (1);
	}

	return (0);

}

void Sig1Handler(int sig, siginfo_t *siginfo, void *data)
{
	UNUSED(siginfo);

	++counter;

	printf("%d recieved SIGUSR1. counter: %ld\n", getpid(), counter);

	return;
}

void Sig2Handler(int sig, siginfo_t *siginfo, void *data)
{
	UNUSED(sig);
	UNUSED(siginfo);

	/* TODO change this!! */
	UNUSED(data);


/* 	++*(size_t *)data;
 */
	printf("%d recieved SIGUSR2. counter: %ld\n", getpid(), counter);

	return;
}

/* 
int ActionPrint2(void *param)
{
	printf("Action Print!2 param receieved: %d.\n", *(int *)param);
	
	return (*(int *)param);
} */

int SendSignal(void *pid)
{
	kill(*((pid_t *)pid), SIGUSR1);
		
	return (2);
}

int CheckSignal(void *watchdog)
{
	pid_t pid = 0;
	int value = 0;

 	if (counter)
	{
		counter = 0;

		return (2);
	}
	
	printf("counter is 0. very bad!.\n",counter);

	if ((*((watchdog_t **)watchdog))->is_watchdog)
	{
		printf("User dead. Start over!\n");
		sem_unlink("dog_semo");
		sem_close((*((watchdog_t **)watchdog))->semophore);

		execve ("./wd_user", NULL, NULL);
	}
	else
	{
		printf("Watchdog dead. Start over!\n");
		pid = fork();

		if (-1 == pid)
		{
			printf("fork failed.\n");
			sem_post((*((watchdog_t **)watchdog))->semophore);

			return (1);
		}

		/* child process */
		else if (0 == pid)
		{
			printf("kid created\n");
	/* 		args[0] = argv[0];
			sprintf(args[1], "%d", check_ratio);
			sprintf(args[2], "%d", beats_interval); */

			execve ("./watchdog", NULL, NULL);
		}
		/* parent process */
		else
		{
			(*((watchdog_t **)watchdog))->send_pid = pid;
			printf("parent waiting\n");
/* 			sem_getvalue((*((watchdog_t **)watchdog))->semophore, &value);
			printf("sem value before wait: %d\n", value); */
			
			sem_wait((*((watchdog_t **)watchdog))->semophore);
			printf("parent done waiting\n");
		}

	}
	
	return (2);
}

void *RunWD(void *scehduler)
{
	return ((void *)(long)(HeapSchedulerRun(scehduler)));
}

