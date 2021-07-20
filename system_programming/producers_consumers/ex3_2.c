#include <sys/types.h> /* sem_t */
#include <semaphore.h> /* sem_open, sem_close */
#include <fcntl.h> /* O_CREAT */
#include <stdio.h>
#include <pthread.h>
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */ 
#include <stdatomic.h>

#define ARR_SIZE (100)

#define QSIZE (50)

size_t read_idx = 0;
size_t write_idx = 0;

int buffer[QSIZE] = {0};

void *Producer(void *arg);
void *Consumer(void *arg);

int arr[ARR_SIZE] = {0};

pthread_mutex_t lock_producer = {0};
pthread_mutex_t lock_consumer = {0};

sem_t sem1 = {0};
sem_t sem2 = {0};

int main()
{
	pthread_t Producer1 = {0};
	pthread_t Producer2 = {0};
	pthread_t Consumer1 = {0};
	pthread_t Consumer2 = {0};	
	
	size_t i = 0;

	if (-1 == sem_init(&sem1, 0, ARR_SIZE))
	{	
		return (1);
	}
	
	if (-1 == sem_init(&sem2, 0, 0))
	{	
		sem_destroy(&sem1);

		return (1);
	}

	if ((0 != pthread_create(&Producer1, NULL, Producer, NULL))
	  ||(0 != pthread_create(&Producer2, NULL, Producer, NULL))
	  ||(0 != pthread_create(&Consumer1, NULL, Consumer, 0))
	  ||(0 != pthread_create(&Consumer2, NULL, Consumer, (void *)(ARR_SIZE / 2))))
	{
		return (1);
	}

	pthread_join(Producer1, NULL);
	pthread_join(Producer2, NULL);
	pthread_join(Consumer1, NULL);
	pthread_join(Consumer2, NULL);	

	for (i = 0; i < ARR_SIZE; ++i)
	{
		printf("Arr in index %ld wrong value. actual: %d.\n", i, arr[i]);
	}

	sem_destroy(&sem1);
	sem_destroy(&sem2);
    pthread_mutex_destroy(&lock_producer);
	pthread_mutex_destroy(&lock_consumer);

	return (0);
}

void *Producer(void *arg)
{
	int i = 0;

	(void)arg;

	while (i < ARR_SIZE)
	{
		if (-1 == sem_wait(&sem1))
		{
			return (NULL);
		}
		/*-------------------------critical section -------------------------*/
		pthread_mutex_lock(&lock_producer);

		buffer[write_idx] = i;
		write_idx = (write_idx + 1)% QSIZE;
		++i;

    	pthread_mutex_unlock(&lock_producer);
		/*-------------------------critical section -------------------------*/

		if (-1 == sem_post(&sem2))
		{
			return (NULL);
		}
	}

	return (NULL);
}

void *Consumer(void *arg)
{
	int i = (int)(long)arg;

	while (i < ARR_SIZE)
	{
		if (-1 == sem_wait(&sem2))
		{
			return (NULL);
		}
		/*-------------------------critical section -------------------------*/
		pthread_mutex_lock(&lock_consumer);

		arr[i] = buffer[read_idx];
		buffer[read_idx] = 0;
		read_idx = (read_idx + 1)% QSIZE;
		++i;

		pthread_mutex_unlock(&lock_consumer);
		/*-------------------------critical section -------------------------*/
	
		if (-1 == sem_post(&sem1))
		{
			return (NULL);
		}
	}

	return (NULL);
}