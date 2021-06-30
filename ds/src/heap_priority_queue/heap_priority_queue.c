#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "heap_priority_queue.h"
#include "heap.h"

struct pq
{
	heap_t *heap;
};

pq_t *PQueueCreate (int (*cmp_func)(const void *data1, const void *data2))
{
	pq_t *priority_queue = NULL;

	assert(cmp_func);	

	priority_queue = (pq_t *)malloc(sizeof(pq_t));

	if (NULL == priority_queue)
	{
		return NULL;
	}
	
	priority_queue->heap = HeapCreate(cmp_func);
	
	if (NULL == priority_queue->heap)
	{
		free(priority_queue);
		
		return NULL;
	}	
	
	return (priority_queue);	
}

void PQueueDestroy(pq_t *p_queue)
{
	assert(p_queue);
	assert(p_queue->heap);	
	
	HeapDestroy(p_queue->heap);
	
	p_queue->heap = NULL;
	
	free(p_queue);
	
	return;	
}

size_t PQueueSize(const pq_t *p_queue)
{
	assert(p_queue);
	assert(p_queue->heap);	

	return (HeapSize(p_queue->heap));
}     

int PQueueIsEmpty(const pq_t *p_queue)
{
	assert(p_queue);
	assert(p_queue->heap);	

	return (HeapIsEmpty(p_queue->heap));
}  	   	

int PQueueEnqueue(pq_t *p_queue, void *data)
{
	assert(p_queue);
	assert(p_queue->heap);
	
	return (HeapPush(p_queue->heap, data));		
}   	

void *PQueueDequeue(pq_t *p_queue)
{
	void *data = NULL;

	assert(p_queue);
	assert(p_queue->heap);
	assert(!PQueueIsEmpty(p_queue));
	
	data = HeapPeek(p_queue->heap);
	HeapPop(p_queue->heap);

	return (data);
}		

void      *PQueuePeek   (const pq_t *p_queue)
{
	assert(p_queue);
	assert(p_queue->heap);
	assert(!PQueueIsEmpty(p_queue));

	return (HeapPeek(p_queue->heap));
}		      	    		  
  
void PQueueClear(pq_t *p_queue)
{
	assert(p_queue);
	assert(p_queue->heap);
	
	while (!HeapIsEmpty(p_queue->heap))
	{
		HeapPop(p_queue->heap);
	}
	
	return ;
}

 void *PQueueErase(	pq_t *p_queue, 
					int (*is_match_func)(const void *data, const void *param),
					void *param													)
{
	assert(p_queue);
	assert(p_queue->heap);
	assert(is_match_func);
	assert(!HeapIsEmpty(p_queue->heap));
	
	return (HeapRemove(p_queue->heap, is_match_func, param));
		
}