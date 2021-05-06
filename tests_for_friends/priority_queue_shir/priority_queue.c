#include <stdlib.h> /* malloc */
#include <stddef.h> /* size_f */
#include <assert.h> /* assert.h */

#include "priority_queue.h"
#include "../../ds/src/sorted_ll/sorted_ll.h"

struct pq
{
	sorted_list_t *p_queue;
};


pq_t *PQueueCreate (int (*cmp_func)(const void *data1, const void *data2))
{
	pq_t *p_list = NULL;
	
	assert(NULL != cmp_func);
	
	p_list = (pq_t *)malloc(sizeof(pq_t));
	
	if (NULL == p_list)
	{
		return NULL;
	}
	
	p_list->p_queue = SortedLLCreate(cmp_func);
	
	if (NULL == p_list)
	{
		free(p_list);
		
		return NULL;
	}
	
	return (p_list);
}


void PQueueDestroy(pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->p_queue);
	
	SortedLLDestroy(p_queue->p_queue);
	
	p_queue->p_queue = NULL;
	free(p_queue);
	
	return;
}


size_t PQueueSize(const pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->p_queue);
	
	return (SortedLLSize(p_queue->p_queue));
}


int PQueueIsEmpty(const pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->p_queue);
	
	return (SortedLLIsEmpty(p_queue->p_queue));
}


int PQueueEnqueue(pq_t *p_queue, void *data)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->p_queue);
	
	return (SortedLLIsSameIter(SortedLLEnd(p_queue->p_queue),
			 (SortedLLInsert(p_queue->p_queue, data))));
}


void *PQueueDequeue(pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->p_queue);
	assert(!PQueueIsEmpty(p_queue));
	
	return (SortedLLPopFront(p_queue->p_queue));
}


void *PQueuePeek(const pq_t *p_queue)
{
	assert(NULL != p_queue);
	assert(NULL != p_queue->p_queue);
	assert(!PQueueIsEmpty(p_queue));
	
	return (SortedLLGetData(SortedLLBegin(p_queue->p_queue)));
}


void PQueueClear(pq_t *p_queue)
{
	assert(NULL != p_queue);
	
	while(!PQueueIsEmpty(p_queue))
	{
		PQueueDequeue(p_queue);
	}
	
	return;
}


void *PQueueErase(pq_t *p_queue, 
						 int (*is_match_func)(const void *data, const void *param),
						 void *param)
{
	void *tmp = 0;
	sorted_list_iter_t find_res = {NULL};
	
	assert(NULL != p_queue);
	assert(NULL != p_queue->p_queue);
	assert(!PQueueIsEmpty(p_queue));
	assert(NULL != is_match_func);
	
	find_res = SortedLLFindIf(SortedLLBegin(p_queue->p_queue),
				 SortedLLEnd(p_queue->p_queue), is_match_func, param);
	
	if (SortedLLIsSameIter(SortedLLEnd(p_queue->p_queue), find_res))
	{
		return NULL;		 
	}
	
	tmp = SortedLLGetData(find_res);
	
	SortedLLRemove(find_res);
	
	return (tmp);
}











