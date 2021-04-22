/*
  Status : Approved except unit testing 
  Reviewer : Maor
  Date : 22/04/2021
  Description: Queue Implemented using singly linked list 
*/
#include <stdlib.h>
#include <assert.h>

#include "queue.h"
#include "sll.h"

struct queue
{
	s_list_t *list;
};

/* Approved Maor */
queue_t *QueueCreate(void)
{
	s_list_t *list = NULL;
	queue_t *que = (queue_t *)malloc(sizeof(queue_t));

	if (NULL == que)
	{
		return NULL;
	}

	list = SLLCreate();
	
	if (NULL == list)
	{
		free(que);
		return NULL;
	}

	que->list = list;

	return que;
}


/* Approved Maor */
void QueueDestroy(queue_t *queue)
{
	assert(queue);
	assert(queue->list);

	SLLDestroy(queue->list);	

	queue->list = NULL;
	free(queue);

	return;
}

/* Approved Maor */
int  QueueIsEmpty(const queue_t *queue)
{
	assert(queue);
	assert(queue->list);

	return (SLLIsEmpty(queue->list));
}

/* Approved Maor */
size_t QueueSize(const queue_t *queue)
{
	assert(queue);
	return SLLCount(queue->list);
}

/* Approved Maor */
int  QueueEnqueue(queue_t *queue, void *data)
{
	assert(queue);
	assert(queue->list);

	/* If returned end of list failed */
	return SLLIsSameIter(SLLEnd(queue->list), SLLInsert(SLLEnd(queue->list), data));
}

int QueueEnqueue(queue_t *queue, void *data)
{
	assert(NULL != queue);
	
	return SLLIsSameIter(SLLInsert(SLLEnd(queue->list), data), SLLEnd(queue->list));
}  


/* Approved Maor */
void *QueuePeek(const queue_t *queue)   
{
	assert(queue);
	assert(queue->list);

	return SLLGetData(SLLBegin(queue->list));
}

/* Approved Maor */
void QueueDequeue(queue_t *queue)
{
	assert(queue);
	assert(queue->list);

	SLLRemove(SLLBegin(queue->list));

	return;
}

/* Approved Maor */
void QueueAppend(queue_t *dest, queue_t *src) 
{
	assert(dest);
	assert(src);
	assert(dest->list);
	assert(src->list);

	SLLAppend(dest->list, src->list);

	return;
}
