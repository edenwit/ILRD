
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include "sll.h"

#define ARR_SIZE (100)

void *Producer(void *arg);
void *Consumer(void *arg);

int arr[ARR_SIZE] = {0};
pthread_mutex_t lock = {0};
int data = 1;

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

	SLLDestroy(list);
    pthread_mutex_destroy(&lock);

	return (0);
}

void *Producer(void *list)
{
	size_t i = 0;
	s_list_iter_t iter = NULL;

	while (i <= ARR_SIZE)
	{
		pthread_mutex_lock(&lock);

		iter = SLLInsert(SLLBegin((s_list_t *)list), &data);

		if (SLLIsSameIter(iter, SLLEnd((s_list_t *)list)))
		{
			printf("Failed to insert\n");
			return (NULL);
		}
		else
		{
			++i;
		}

    	pthread_mutex_unlock(&lock);
	}

	return (NULL);
}

void *Consumer(void *list)
{
	int temp = 0;
	size_t i = 0;

	while (i <= ARR_SIZE)
	{
		pthread_mutex_lock(&lock);
	
		if (!SLLIsEmpty((s_list_t *)list))
		{
			temp = *(int *)SLLGetData(SLLBegin((s_list_t *)list));
			SLLRemove(SLLBegin((s_list_t *)list));
			arr[i] = temp;
			++i;
		}
		
		pthread_mutex_unlock(&lock);
	}

	return (NULL);
}

