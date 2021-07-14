#include <sys/types.h> /* sem_t */
#include <semaphore.h> /* sem_open, sem_close */
#include <fcntl.h> /* O_CREAT */
#include <stdio.h>
#include <pthread.h>

#include "circular_buffer.h"

#define VAR_SIZE (8)
#define ARR_SIZE (100)
#define CAPACITY (ARR_SIZE * VAR_SIZE / 2)

void *Producer(void *arg);
void *Consumer(void *arg);

int arr[ARR_SIZE] = {0};
pthread_mutex_t lock = {0};
sem_t sem1 = {0};
sem_t sem2 = {0};
int data = 1;

int main()
{
	pthread_t Producer1 = {0};
	pthread_t Producer2 = {0};
	pthread_t Consumer1 = {0};
	pthread_t Consumer2 = {0};	
	
	c_buffer_t *queue = CBufferCreate(CAPACITY);

	size_t i = 0;

	if (NULL == queue)
	{
		return(1);
	}

	if (-1 == sem_init(&sem1, 0, ARR_SIZE))
	{	
		CBufferDestroy(queue);

		return (1);
	}
	
	if (-1 == sem_init(&sem2, 0, 0))
	{	
		sem_destroy(&sem1);
		CBufferDestroy(queue);

		return (1);
	}

	if ((0 != pthread_create(&Producer1, NULL, Producer, (void *)queue))
	  ||(0 != pthread_create(&Producer2, NULL, Producer, (void *)queue))
	  ||(0 != pthread_create(&Consumer1, NULL, Consumer, (void *)queue))
	  ||(0 != pthread_create(&Consumer2, NULL, Consumer, (void *)queue)))
	{
		return (1);
	}

	pthread_join(Producer1, NULL);
	pthread_join(Producer2, NULL);
	pthread_join(Consumer1, NULL);
	pthread_join(Consumer2, NULL);	

	for (i = 0; i < ARR_SIZE; ++i)
	{
 		if (1 != arr[i])
		{
			printf("Arr in index %ld wrong value. expected: 1, actual: %d.\n", i, arr[i]);
		} 
	}

	sem_destroy(&sem1);
	sem_destroy(&sem2);
	CBufferDestroy(queue);
    pthread_mutex_destroy(&lock);

	return (0);
}

void *Producer(void *queue)
{
	size_t i = 0;

	while (i < ARR_SIZE)
	{
		if (-1 == sem_wait(&sem1))
		{
			return (NULL);
		}

		pthread_mutex_lock(&lock);

		CBufferWrite((c_buffer_t *)queue, (void *)&i, VAR_SIZE);

		++i;

		if (-1 == sem_post(&sem2))
		{
			return (NULL);
		}

    	pthread_mutex_unlock(&lock);
	}

	return (NULL);
}

void *Consumer(void *queue)
{
	size_t i = 0;

	while (i < ARR_SIZE)
	{
		if (-1 == sem_wait(&sem2))
		{
			return (NULL);
		}
		
		pthread_mutex_lock(&lock);

		CBufferRead((c_buffer_t *)queue, (void *)(arr + i), VAR_SIZE);

		++i;

		if (-1 == sem_post(&sem1))
		{
			return (NULL);
		}

		pthread_mutex_unlock(&lock);
	}

	return (NULL);
}

