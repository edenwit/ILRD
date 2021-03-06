#include <stdio.h> /* printf */


#include "queue.h"

#define TIMES_TO_LOOP 6

int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 10000};
	
	size_t i = 0;
	void *data = NULL;

	queue_t *queue = QueueCreate();	
	queue_t *queue2 = QueueCreate();
	
	if (!QueueIsEmpty(queue))
	{
		printf ("After Creation queue not empty!\n");
	}

	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		if (QueueEnqueue(queue, (void *)(arr + i)))
		{
			printf ("Insersion queue1 #%ld failed!\n", i + 1);	
		}	
	}
	
	for (i = 0; i < TIMES_TO_LOOP / 2; ++i)
	{
		if (QueueEnqueue(queue2, (void *)(arr + i)))
		{
			printf ("Insersion queue2 #%ld failed!\n", i + 1);	
		}
	}
	
	if (TIMES_TO_LOOP != QueueSize(queue))
	{
		printf ("Wrong size! Actual: %ld, expected: %d.\n", QueueSize(queue), TIMES_TO_LOOP);		
	}
	
	if (TIMES_TO_LOOP / 2 != QueueSize(queue2))
	{
		printf ("Wrong size! Actual: %ld, expected: %d.\n", QueueSize(queue2), TIMES_TO_LOOP / 2);		
	}

	QueueAppend(queue, queue2);

		
	if (!QueueIsEmpty(queue2))	
	{
		printf ("Queue2 supposed to be empty after append with queue1. actual size: %ld.\n", QueueSize(queue2));			
	}

	if (TIMES_TO_LOOP * 1.5 != QueueSize(queue))
	{
		printf ("Wrong size after appending! Actual: %ld, expected: %f.\n", QueueSize(queue), TIMES_TO_LOOP * 1.5);		
	}
	
	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		data = QueuePeek(queue);
		
		if (*(int *)data != (arr[i]))
		{
			printf("Current Member: %d\t, in arr: %d\n", *(int *)data, (arr[i] ));
		}
		QueueDequeue(queue);
	}
	
	if (TIMES_TO_LOOP / 2 != QueueSize(queue))
	{
		printf ("Wrong size! Actual: %ld, expected: %d.\n", QueueSize(queue), TIMES_TO_LOOP / 2);			
	}
	
	if (!QueueIsEmpty(queue2))
	{
		printf ("Wrong size! Actual: %ld, expected: %d.\n", QueueSize(queue2), 0);		
	}

	QueueDestroy(queue);
	QueueDestroy(queue2);

	return 0;
}

