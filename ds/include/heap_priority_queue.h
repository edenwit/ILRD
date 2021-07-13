/* Version 1 - 23.06.2021 16:00 */

#ifndef __HEAP_PRIORITY_QUEUE_H__
#define __HEAP_PRIORITY_QUEUE_H__

#include <stddef.h> /* size_t */

typedef struct pq pq_t;

/*
in c file:

struct pq
{
	sorted_list_t *p_queue;
};

*/

pq_t 	  *HeapPQueueCreate (int (*cmp_func)(const void *data1, const void *data2)); 	/* O(1) */
void       HeapPQueueDestroy(pq_t *p_queue);			         	            		/* O(n) */	

size_t     HeapPQueueSize   (const pq_t *p_queue);       			        			/* O(n) */ 
int        HeapPQueueIsEmpty(const pq_t *p_queue);		   			        			/* O(1) */

int        HeapPQueueEnqueue(pq_t *p_queue, void *data);   	 				    	    /* O(n) */
void      *HeapPQueueDequeue(pq_t *p_queue);		    		 	   				    /* O(1) */
void      *HeapPQueuePeek   (const pq_t *p_queue);				      	    		    /* O(1) */
  
void 	   HeapPQueueClear  (pq_t *p_queue);					            			/* O(n) */
void 	  *HeapPQueueErase  (pq_t *p_queue, 
						 int (*is_match_func)(const void *data, const void *param),
						 void *param); 			     					  		    /* O(n) */

#endif /* HEAP_PRIORITY_QUEUE_H__ */

