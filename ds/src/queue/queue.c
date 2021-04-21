#include "../sll/sll.h"
#include "queue.h"

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf */
#include <assert.h> /* assert */

struct queue
{
	s_list_t *list;
};

queue_t *QueueCreate(void)
{
	queue_t *queue = (queue_t *)malloc(sizeof(struct queue));
	
	if (NULL == queue)
	{    
		return NULL;
	}

	queue->list = SLLCreate();
	
	return queue;
}

void QueueDestroy(queue_t *queue)
{
	assert(queue);
	
	SLLDestroy(queue->list);
	queue->list = NULL;
	free(queue);
	
	return;
}

size_t QueueSize(const queue_t *queue)
{
	assert(queue);
	
	return SLLCount(queue->list);
}

int  QueueIsEmpty(const queue_t *queue)
{
	assert(queue);
	
	return SLLIsEmpty(queue->list);
}

int  QueueEnqueue(queue_t *queue, void *data)
{
	assert(queue);
	
	return !SLLIsSameIter(SLLInsert(SLLEnd(queue->list), data), SLLEnd(queue->list));
}  

void *QueuePeek(const queue_t *queue)
{
	assert(queue);
	return SLLGetData(SLLBegin(queue->list));
}					

void QueueDequeue(queue_t *queue)
{
	assert(queue);
	
	if (!QueueIsEmpty(queue))
		SLLRemove(SLLBegin(queue->list));
	
	return;
}
void QueueAppend(queue_t *dest, queue_t *src)
{
	assert(dest->list);
	assert(src->list);
	
	SLLAppend(dest->list, src->list);
	
}
