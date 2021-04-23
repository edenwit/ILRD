#include "sll.h"
#include "queue.h"

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf */
#include <assert.h> /* assert */

struct queue
{
	s_list_t *list;
};

/* approved  by shelly*/
queue_t *QueueCreate(void)
{
	queue_t *queue = (queue_t *)malloc(sizeof(struct queue));
	
	if (NULL == queue)
	{    
		return NULL;
	}

	queue->list = SLLCreate();
	
	if (NULL == queue->list)
	{    
		free(queue);
		
		return NULL;
	}
	
	return queue;
}

/* approved  by shelly*/
void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);
	
	SLLDestroy(queue->list);
	queue->list = NULL;
	free(queue);
	
	return;
}

/* approved  by shelly*/
size_t QueueSize(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SLLCount(queue->list);
}

/* approved  by shelly*/
int  QueueIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SLLIsEmpty(queue->list);
}


int QueueEnqueue(queue_t *queue, void *data)
{
	s_list_iter_t iter_end = NULL;
	
	assert(NULL != queue);
	
	iter_end = SLLInsert(SLLEnd(queue->list), data);
	
	return SLLIsSameIter(iter_end, SLLEnd(queue->list));
}  

/* approved  by shelly*/
void *QueuePeek(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SLLGetData(SLLBegin(queue->list));
}					

/* approved  by shelly*/
void QueueDequeue(queue_t *queue)
{
	assert(NULL != queue);

	SLLRemove(SLLBegin(queue->list));
	
	return;
}

/* approved  by shelly*/
void QueueAppend(queue_t *dest, queue_t *src)
{
	assert(dest);
	assert(src);
	
	SLLAppend(dest->list, src->list);
	
}
