#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "priority_queue.h"
/*
typedef struct pq pq_t;
*/

struct pq
{
	sorted_list_t *p_queue;
};

pq_t 	  *PQueueCreate (int (*cmp_func)(const void *data1, const void *data2))
{
	pq_t *priority_queue = NULL;

	assert(cmp_func);	

	priority_queue = (pq_t *)malloc(sizeof(pq_t));

	if (NULL == priority_queue)
	{
		return NULL;
	}
	
	priority_queue->p_queue = SortedLLCreate(cmp_func);
	
	if (NULL == priority_queue->p_queue)
	{
		free(priority_queue);
		
		return NULL;
	}	
	
	return (priority_queue);	
}

void       PQueueDestroy(pq_t *p_queue)			         	            		/* O(n) */	
{
	assert(p_queue);
	assert(p_queue->p_queue);	
	
	SortedLLDestroy(p_queue->p_queue);
	
	p_queue->p_queue = NULL;
	
	free(p_queue);
	
	return;	
}
size_t     PQueueSize   (const pq_t *p_queue) /* O(n) */ 
{
	assert(p_queue);
	assert(p_queue->p_queue);	

	return SortedLLSize(p_queue->p_queue);
}      			        			
int        PQueueIsEmpty(const pq_t *p_queue)
{
	assert(p_queue);
	assert(p_queue->p_queue);	

	return (SortedLLIsEmpty(p_queue->p_queue));
}  	   			        			/* O(1) */

int        PQueueEnqueue(pq_t *p_queue, void *data)
{
	assert(p_queue);
	assert(p_queue->p_queue);
	
	return (!SortedLLIsSameIter(SortedLLInsert(p_queue->p_queue, data),SortedLLEnd(p_queue->p_queue)));		
}   	 				    	  
void      *PQueueDequeue(pq_t *p_queue)
{
	assert(p_queue);
	assert(p_queue->p_queue);
	
	return (SortedLLPopFront(p_queue->p_queue));
}		    		 	   				    /* O(1) */
void      *PQueuePeek   (const pq_t *p_queue)
{
	assert(p_queue);
	assert(p_queue->p_queue);
	
	return (SortedLLGetData(SortedLLBegin(p_queue->p_queue)));
}		      	    		    /* O(1) */
  
void 	   PQueueClear  (pq_t *p_queue)
{
	assert(p_queue);
	assert(p_queue->p_queue);
	
	while (!PQueueIsEmpty(p_queue))
	{
		PQueueDequeue(p_queue);
	}	
}					            			/* O(n) */
void 	  *PQueueErase  (pq_t *p_queue, 
						 int (*is_match_func)(const void *data, const void *param),
						 void *param)
{
	sorted_list_iter_t iter = {0};
	void *data = NULL;
	
	assert(p_queue);
	assert(p_queue->p_queue);
	assert(is_match_func);
	
	iter = SortedLLFindIf(SortedLLBegin(p_queue->p_queue), SortedLLEnd(p_queue->p_queue), is_match_func, param);	
	data = SortedLLGetData(iter);
	
	if (SortedIsSameIter(SortedLLEnd(p_queue->p_queue), iter))
	{
		return NULL;
	}

	SortedLLRemove(iter);
		
	return data;
	
	
	
	
}			     					  

