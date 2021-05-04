#include <stdio.h> /* printf */


#include "priority_p_queue.h"

#define TIMES_TO_LOOP 6

int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 10000};
	
	size_t i = 0;
	void *data = NULL;

	pq_t *p_queue = PPQueueCreate();	
	pq_t *p_queue2 = PPQueueCreate();
	
	if (!PPQueueIsEmpty(p_queue))
	{
		printf ("After Creation p_queue not empty!\n");
	}

	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		if (PQueueEnp_queue(p_queue, (void *)(arr + i)))
		{
			printf ("Insersion p_queue1 #%ld failed!\n", i + 1);	
		}	
	}
	
	for (i = 0; i < TIMES_TO_LOOP / 2; ++i)
	{
		if (PQueueEnp_queue(p_queue2, (void *)(arr + i)))
		{
			printf ("Insersion p_queue2 #%ld failed!\n", i + 1);	
		}
	}
	
	if (TIMES_TO_LOOP != PQueueSize(p_queue))
	{
		printf ("Wrong size! Actual: %ld, expected: %d.\n", PQueueSize(p_queue), TIMES_TO_LOOP);		
	}
	
	if (TIMES_TO_LOOP / 2 != PQueueSize(p_queue2))
	{
		printf ("Wrong size! Actual: %ld, expected: %d.\n", PQueueSize(p_queue2), TIMES_TO_LOOP / 2);		
	}

	PQueueAppend(p_queue, p_queue2);

		
	if (!PQueueIsEmpty(p_queue2))	
	{
		printf ("PQueue2 supposed to be empty after append with p_queue1. actual size: %ld.\n", PQueueSize(p_queue2));			
	}

	if (TIMES_TO_LOOP * 1.5 != PQueueSize(p_queue))
	{
		printf ("Wrong size after appending! Actual: %ld, expected: %f.\n", PQueueSize(p_queue), TIMES_TO_LOOP * 1.5);		
	}
	
	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		data = PQueuePeek(p_queue);
		
		if (*(int *)data != (arr[i]))
		{
			printf("Current Member: %d\t, in arr: %d\n", *(int *)data, (arr[i] ));
		}
		PQueueDep_queue(p_queue);
	}
	
	if (TIMES_TO_LOOP / 2 != PQueueSize(p_queue))
	{
		printf ("Wrong size! Actual: %ld, expected: %d.\n", PQueueSize(p_queue), TIMES_TO_LOOP / 2);			
	}
	
	if (!PQueueIsEmpty(p_queue2))
	{
		printf ("Wrong size! Actual: %ld, expected: %d.\n", PQueueSize(p_queue2), 0);		
	}

	PQueueDestroy(p_queue);
	PQueueDestroy(p_queue2);

	return 0;
}

