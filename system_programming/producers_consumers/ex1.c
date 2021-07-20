
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

#define ARR_SIZE (5)
#define UNUSED(X) ((void)X)

void *Producer(void *arg);
void *Consumer(void *arg);

int flag = 0;
int arr[ARR_SIZE] = {0};

int main()
{
	pthread_t thread1 = {0};
	pthread_t thread2 = {0};

	size_t j = 0;

	pthread_create(&thread1, NULL, Producer, NULL);
	pthread_create(&thread2, NULL, Consumer, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	for (j = 0; j < ARR_SIZE; ++j)
	{
		if (1 != arr[j])
		{
			printf("Arr in index %ld wrong value. expected: 1, actual: %d.\n", j, arr[j]);
		}
	}

	return (0);
}

void *Producer(void *arg)
{
	size_t i = 0;

	UNUSED(arg);

	while (i < ARR_SIZE)
	{
		if (0 == flag)
		{
			__sync_fetch_and_add(&flag, 1);
			++i;
		}
	}

	return (NULL);
}

void *Consumer(void *arg)
{
	int temp = 0;
	size_t i = 0;

	UNUSED(arg);

	while (i < ARR_SIZE)
	{
		if (1 == flag)
		{
			temp = __sync_fetch_and_sub(&flag, 1);
			arr[i] = temp;
			++i;
		}
	}

	return (NULL);
}