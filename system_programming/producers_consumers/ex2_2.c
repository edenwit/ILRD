#include <sys/types.h> /* sem_t */
#include <semaphore.h> /* sem_open, sem_close */
#include <fcntl.h> /* O_CREAT */
#include <stdio.h>
#include <pthread.h>

#include "sll.h"

#define ARR_SIZE (100)
#define SEM_NAME "semophore_ex2_2"

void *Producer(void *arg);
void *Consumer(void *arg);

int arr[ARR_SIZE] = {0};
pthread_mutex_t lock = {0};
int data = 1;
sem_t sem = {0};


int main()
{
	pthread_t Producer1 = {0};
	pthread_t Producer2 = {0};
	pthread_t Consumer1 = {0};
	pthread_t Consumer2 = {0};	
	
	s_list_t *list = SLLCreate();

	size_t i = 0;

	if (NULL == list)
	{
		return(1);
	}

	if (-1 == sem_init(&sem, 0, 0))
	{	
		SLLDestroy(list);
		return (1);
	}

	if ((0 != pthread_create(&Producer1, NULL, Producer, (void *)list))
	  ||(0 != pthread_create(&Producer2, NULL, Producer, (void *)list))
	  ||(0 != pthread_create(&Consumer1, NULL, Consumer, (void *)list))
	  ||(0 != pthread_create(&Consumer2, NULL, Consumer, (void *)list)))
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

	sem_destroy(&sem);
	SLLDestroy(list);
    pthread_mutex_destroy(&lock);

	return (0);
}

void *Producer(void *list)
{
	size_t i = 0;
	s_list_iter_t iter = NULL;

	while (i < ARR_SIZE)
	{
		pthread_mutex_lock(&lock);

		iter = SLLInsert(SLLBegin((s_list_t *)list), &data);

		if (SLLIsSameIter(iter, SLLEnd((s_list_t *)list)))
		{
			printf("Failed to insert\n");
			return (NULL);
		}
		if (-1 == sem_post(&sem))
		{
			return (NULL);
		}

		++i;

    	pthread_mutex_unlock(&lock);
	}

	return (NULL);
}

void *Consumer(void *list)
{
	int temp = 0;
	size_t i = 0;

	while (i < ARR_SIZE)
	{
		if (-1 == sem_wait(&sem))
		{
			return (NULL);
		}
		pthread_mutex_lock(&lock);

		temp = *(int *)SLLGetData(SLLBegin((s_list_t *)list));
		SLLRemove(SLLBegin((s_list_t *)list));
		arr[i] = temp;

		++i;
		pthread_mutex_unlock(&lock);
	}

	return (NULL);
}

