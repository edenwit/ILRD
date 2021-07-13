#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "heap_priority_queue.h"
#include "heap.h"

struct pq
{
	heap_t *heap;
};

pq_t *HeapPQueueCreate (int (*cmp_func)(const void *data1, const void *data2))
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

void HeapPQueueDestroy(pq_t *p_queue)
{
	assert(p_queue);
	assert(p_queue->heap);	
	
	HeapDestroy(p_queue->heap);
	
	p_queue->heap = NULL;
	
	free(p_queue);
	
	return;	
}

size_t HeapPQueueSize(const pq_t *p_queue)
{
	assert(p_queue);
	assert(p_queue->heap);	

	return (HeapSize(p_queue->heap));
}     

int HeapPQueueIsEmpty(const pq_t *p_queue)
{
	assert(p_queue);
	assert(p_queue->heap);	

	return (HeapIsEmpty(p_queue->heap));
}  	   	

int HeapPQueueEnqueue(pq_t *p_queue, void *data)
{
	assert(p_queue);
	assert(p_queue->heap);
	
	return (HeapPush(p_queue->heap, data));		
}   	

void *HeapPQueueDequeue(pq_t *p_queue)
{
	void *data = NULL;

	assert(p_queue);
	assert(p_queue->heap);
	assert(!HeapPQueueIsEmpty(p_queue));
	
	data = HeapPeek(p_queue->heap);
	HeapPop(p_queue->heap);

	return (data);
}		

void      *HeapPQueuePeek   (const pq_t *p_queue)
{
	assert(p_queue);
	assert(p_queue->heap);
	assert(!HeapPQueueIsEmpty(p_queue));

	return (HeapPeek(p_queue->heap));
}		      	    		  
  
void HeapPQueueClear(pq_t *p_queue)
{
	assert(p_queue);
	assert(p_queue->heap);
	
	while (!HeapIsEmpty(p_queue->heap))
	{
		HeapPop(p_queue->heap);
	}
	
	return ;
}

 void *HeapPQueueErase(	pq_t *p_queue, 
					int (*is_match_func)(const void *data, const void *param),
					void *param													)
{
	assert(p_queue);
	assert(p_queue->heap);
	assert(is_match_func);
	assert(!HeapIsEmpty(p_queue->heap));
	
	return (HeapRemove(p_queue->heap, is_match_func, param));
		
}