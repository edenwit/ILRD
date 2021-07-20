#include <stdio.h>     /*           printf             */
#include <pthread.h>   /*           thread             */
#include <semaphore.h> /*          semaphore           */
#include <fcntl.h>     /*      For O_* constants       */
#include <stdatomic.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <signal.h>

#define NUM_OF_THREADS (11)
#define QSIZE (7)
#define SIZE (700)
#define STRING_SIZE (4)

static void *Producer();
static void *Consumer(void *data);

static int CreatThreads(pthread_t threads_arr[]);
static int Manager();

pthread_mutex_t *lock = NULL;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
sem_t *sem = NULL;
sig_atomic_t counter = 0;

char queue[QSIZE];

sig_atomic_t write = 0; /* index to write to */
sig_atomic_t read = 0;  /* index to read from */

char buf[SIZE];

int main()
{
    int status = Manager();

    if (1 == status)
	{
		printf("func fail\n");
	}


    return (0);
}

static int Manager()
{
    pthread_t threads_arr[NUM_OF_THREADS] = {0};
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    size_t k = 0;
    lock = &mutex;

    for (k = 0; k < SIZE; ++k)
    {
        printf("%c", buf[k]);
    }    
    printf("\n");

    sem = sem_open("sem", O_CREAT, 0660, 0);
    if (SEM_FAILED == sem)
    {
        return (1);
    }

    if (CreatThreads(threads_arr))
    {
        return (1);
    }

    pthread_mutex_destroy(lock);
    sem_close(sem);
    sem_unlink("sem");
    pthread_cond_destroy(&cond);

    for (k = 0; k < SIZE; ++k)
    {
        printf("%c", buf[k]);
    }
    printf("\n");

    return (0);
}

static int CreatThreads(pthread_t threads_arr[])
{
    size_t k = 0;

    assert(threads_arr);

    if (pthread_create(threads_arr + k, NULL, Producer, NULL))
    {
        return (1);
    }

    for (k = 1; k < NUM_OF_THREADS; ++k)
    {
        if (pthread_create(threads_arr + k, NULL, Consumer, 
                                        (void *)(k * STRING_SIZE * QSIZE)))
        {
            return (1);
        }
    }

    for (k = 0; k < NUM_OF_THREADS; ++k)
    {
        pthread_join(threads_arr[k], NULL);
    }

    return (0);
}

static void *Producer()
{
    size_t i = 0;
    size_t j = 0;
    char *strs[] = {"tommarrow ", "is ", "watchdog ", "day! "};

    while (j < STRING_SIZE)
    {
        /*-------------------critical section---------------------*/
        pthread_mutex_lock(lock);

        memcpy(queue, strs[j], QSIZE);

        for (i = 0; i < NUM_OF_THREADS - 1; i++)
        {
            sem_post(sem);
        }

        pthread_cond_wait(&cond, lock);
        pthread_mutex_unlock(lock);

        ++j;
        /*-------------------critical section---------------------*/
    }

    return (NULL);
}

static void *Consumer(void *data)
{
    size_t j = 0;

    while (j < STRING_SIZE)
    {

        sem_wait(sem);

        /*-------------------critical section---------------------*/
        pthread_mutex_lock(lock);

        memcpy(buf + (size_t)data + (j * QSIZE), queue, QSIZE);
        ++counter;

        if ((NUM_OF_THREADS - 1) == counter)
        {
            counter = 0;
            pthread_cond_broadcast(&cond);
        }
        else
        {
            pthread_cond_wait(&cond, lock);
        }
        pthread_mutex_unlock(lock);
        ++j;
        /*-------------------critical section---------------------*/
    }

    return (NULL);
}