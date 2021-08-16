#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "../../ds/include/stack.h"

#define STACK_IS_FULL(X) (StackGetCapacity(X) == StackSize(X))

typedef struct stack_queue
{
	stack_t *stack1;
	stack_t *stack2;

} s_queue_t;

int SQueueEnqueue(s_queue_t *queue, void *data);
void *SQueueDequeue(s_queue_t *queue);
s_queue_t *SQueueCreate(size_t capacity);
void SQDestroy(s_queue_t *queue);

int main()
{
	s_queue_t *queue = SQueueCreate(5000);
	int arr[4998] = {0};
	size_t arr_size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;
	int extra_thing = 100000;
	
	for (i = 0; i < arr_size; ++i)
	{
		arr[i] = i;
		printf("Inserting %d\n", arr[i]);
		SQueueEnqueue(queue, (arr + i));
	}

	printf("Inserting %d\n", extra_thing);	
	SQueueEnqueue(queue, &extra_thing);	

	for (i = 0; i < arr_size + 1; ++i)
	{
		printf("Removing %d\n", *((int *)SQueueDequeue(queue)));
	}

	SQDestroy(queue);

	return (0);
}


int SQueueEnqueue(s_queue_t *queue, void *data)
{
	assert(queue);
	
	if (STACK_IS_FULL(queue->stack1))
	{
		return (1);
	}	
	
	while (!StackIsEmpty(queue->stack1))
	{
		StackPush(queue->stack2, StackPeek(queue->stack1));
		StackPop(queue->stack1);
	}
	
	StackPush(queue->stack1, data);
	
	while (!StackIsEmpty(queue->stack2))
	{
		StackPush(queue->stack1, StackPeek(queue->stack2));
		StackPop(queue->stack2);
	}		
	
	return (0);
}

void *SQueueDequeue(s_queue_t *queue)
{
	void *data = NULL;
	assert(queue);
	
	if (StackIsEmpty(queue->stack1))
	{
		return (NULL);
	}	

	data = StackPeek(queue->stack1);
	
	StackPop(queue->stack1);
	
	return (data);
}

s_queue_t *SQueueCreate(size_t capacity)
{
	s_queue_t *queue = (s_queue_t *)malloc(sizeof(s_queue_t));
	
	if (NULL == queue)
	{
		return (NULL);
	}
	
	queue->stack1 = StackCreate(capacity);
	
	if (NULL == queue->stack1)
	{
		free (queue);
		
		return (NULL);
	}

	queue->stack2 = StackCreate(capacity);
	
	if (NULL == queue->stack2)
	{
		StackDestroy(stack1);
		queue->stack1 = NULL;
		
		free (queue);
		
		return (NULL);
	}
			
	return (queue);	
}

void SQDestroy(s_queue_t *queue)
{
	assert(queue);

	StackDestroy(queue->stack1);
	StackDestroy(queue->stack2);
	
	queue->stack1 = NULL;
	queue->stack2 = NULL;
	
	free(queue);
}


