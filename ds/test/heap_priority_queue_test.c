#include <stdio.h> /* printf */

#include "heap_priority_queue.h"

#define TIMES_TO_LOOP 6

int Cmp_Num(const void *cur, const void *par);
static int FindMatchInt(const void * data, const void *param);

int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 10000};
	
	size_t i = 0;
	void *data = NULL;

	pq_t *p_queue = HeapPQueueCreate(Cmp_Num);	
	pq_t *p_queue2 = HeapPQueueCreate(Cmp_Num);
	
	if (!HeapPQueueIsEmpty(p_queue))
	{
		printf ("After Creation p_queue not empty!\n");
	}

	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		if (HeapPQueueEnqueue(p_queue, (void *)(arr + i)))
		{
			printf ("Insersion p_queue1 #%ld failed!\n", i + 1);	
		}	
	}
	
	for (i = 0; i < TIMES_TO_LOOP / 2; ++i)
	{
		if (HeapPQueueEnqueue(p_queue2, (void *)(arr + i)))
		{
			printf ("Insersion p_queue2 #%ld failed!\n", i + 1);	
		}
	}
	
	if (TIMES_TO_LOOP != HeapPQueueSize(p_queue))
	{
		printf ("Wrong size! Actual: %ld, expected: %d.\n", HeapPQueueSize(p_queue), TIMES_TO_LOOP);		
	}
	
	if (TIMES_TO_LOOP / 2 != HeapPQueueSize(p_queue2))
	{
		printf ("Wrong size! Actual: %ld, expected: %d.\n", HeapPQueueSize(p_queue2), TIMES_TO_LOOP / 2);		
	}
	
	for (i = 0; i < TIMES_TO_LOOP / 2; ++i)
	{
		HeapPQueueDequeue(p_queue2);
	}	

	if (!HeapPQueueIsEmpty(p_queue2))	
	{
		printf ("HeapPQueue2 supposed to be empty after append with p_queue1. actual size: %ld.\n", HeapPQueueSize(p_queue2));			
	}

	if (TIMES_TO_LOOP != HeapPQueueSize(p_queue))
	{
		printf ("Wrong size after appending! Actual: %ld, expected: %f.\n", HeapPQueueSize(p_queue), TIMES_TO_LOOP * 1.5);		
	}
	
	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		data = HeapPQueuePeek(p_queue);
		
		if (*(int *)data != (arr[i]))
		{
			printf("Current Member: %d\t, in arr: %d\n", *(int *)data, (arr[i] ));
		}
		HeapPQueueDequeue(p_queue);
	}
	
	if (!HeapPQueueIsEmpty(p_queue2))
	{
		printf ("Wrong size! Actual: %ld, expected: %d.\n", HeapPQueueSize(p_queue2), 0);		
	}

	HeapPQueueDestroy(p_queue);
	HeapPQueueDestroy(p_queue2);

	p_queue = HeapPQueueCreate(Cmp_Num);	

	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		if (HeapPQueueEnqueue(p_queue, (void *)(arr + i)))
		{
			printf ("Insersion p_queue1 #%ld failed!\n", i + 1);	
		}	
	}
	
	if (TIMES_TO_LOOP != HeapPQueueSize(p_queue))
	{
		printf ("Wrong size! Actual: %ld, expected: %d.\n", HeapPQueueSize(p_queue), TIMES_TO_LOOP);		
	}
	
	HeapPQueueClear(p_queue);
	
	if (!HeapPQueueIsEmpty(p_queue))	
	{
		printf ("HeapPQueue supposed to be empty after append with p_queue1. actual size: %ld.\n", HeapPQueueSize(p_queue2));			
	}	
	
	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		if (HeapPQueueEnqueue(p_queue, (void *)(arr + i)))
		{
			printf ("Insersion p_queue1 #%ld failed!\n", i + 1);	
		}	
	}
	
	data = HeapPQueueErase(p_queue, FindMatchInt, (arr + TIMES_TO_LOOP -1));
	
	if (*(int *)data != *(int *)(arr + TIMES_TO_LOOP -1))
	{
		printf ("HeapPQueueErase failed! Actual: %d, expected: %d.\n", *(int *)data, *(int *)(arr + TIMES_TO_LOOP -1));	
	}
	
	if (TIMES_TO_LOOP - 1 != HeapPQueueSize(p_queue))
	{
		printf ("Wrong size! Actual: %ld, expected: %d.\n", HeapPQueueSize(p_queue), TIMES_TO_LOOP);		
	}		
	data = HeapPQueueErase(p_queue, FindMatchInt, (arr + TIMES_TO_LOOP -1));
	
	if (data != NULL)
	{
		printf ("HeapPQueueErase failed! Actual: %d, expected: NULL.\n", *(int *)data);	
	}	

	HeapPQueueDestroy(p_queue);
		
	return 0;
	
}

int Cmp_Num(const void *cur, const void *par)
{
	return (*(int*)cur - *(int*)par);
}

static int FindMatchInt(const void * data, const void *param)
{
	return (*(int *)data >= *(int *)param);
}
