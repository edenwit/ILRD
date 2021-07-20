#include <sys/types.h> /* sem_t */
#include <semaphore.h> /* sem_open, sem_close */
#include <fcntl.h>	   /* O_CREAT */
#include <stdio.h>
#include <pthread.h>
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdatomic.h>

#define ARR_SIZE (100)

#define QSIZE (50)
#define UNUSED(X) ((void)X)

void *Producer(void *arg);
void *Consumer(void *arg);

int arr[ARR_SIZE] = {0};

pthread_mutex_t lock = {0};

atomic_size_t read_idx = 0;
atomic_size_t write_idx = 0;

int buffer[QSIZE] = {0};

int main()
{
	pthread_t Producer1 = {0};
	pthread_t Producer2 = {0};
	pthread_t Consumer1 = {0};
	pthread_t Consumer2 = {0};

	size_t i = 0;

	if ((0 != pthread_create(&Producer1, NULL, Producer, NULL)) || (0 != pthread_create(&Producer2, NULL, Producer, NULL)) || (0 != pthread_create(&Consumer1, NULL, Consumer, 0)) || (0 != pthread_create(&Consumer2, NULL, Consumer, (void *)(ARR_SIZE / 2))))
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

	return (0);
}

void *Producer(void *arg)
{
	int i = 0;

	UNUSED(arg);

	while (i < ARR_SIZE)
	{
		pthread_mutex_lock(&lock);
		if (QSIZE == write_idx - read_idx)
		{
			pthread_mutex_unlock(&lock);
			sched_yield();
		}
		else
		{
			__sync_fetch_and_add(buffer + (write_idx % QSIZE), i);
			__sync_fetch_and_add(&write_idx, 1);
			++i;

			pthread_mutex_unlock(&lock);
		}
	}

	return (NULL);
}

void *Consumer(void *arg)
{
	int i = (int)arg;
	int temp = 0;

	while (i < ARR_SIZE)
	{
		pthread_mutex_lock(&lock);
		if (0 == write_idx - read_idx)
		{
			pthread_mutex_unlock(&lock);

			sched_yield();
		}
		else
		{
			temp = __sync_fetch_and_and(buffer + (read_idx % QSIZE), 0);
			arr[i] = temp;
			++i;
			__sync_fetch_and_add(&read_idx, 1);

			pthread_mutex_unlock(&lock);
		}
	}

	return (NULL);
}
