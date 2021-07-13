#ifndef __HEAP_SCHEDULER_H__
#define __HEAP_SCHEDULER_H__

#include <time.h> 		/* struct tm */
#include <stddef.h> 	/* size_t */
#include "uid.h" 
#include "heap_priority_queue.h" 

typedef struct scheduler scheduler_t;

/* this goes to the src:
struct scheduler
{
	int is_run; 
	pq_t *pq;
};*/

scheduler_t *HeapSchedulerCreate	(void); 						 	 /* time complexity:  O(1) */
void 		 HeapSchedulerDestroy	(scheduler_t *scheduler); 			 /* time complexity:  O(n) */
ilrd_uid_t 	 HeapSchedulerAdd	(scheduler_t *scheduler, 
								int (*action_func)(void *param), 
								size_t interval_in_sec, void *param);/* action can be either
																	  *	periodical and run each x
																	  *	seconds, or a single 
																	  *    instance to be executed
																	  *    in x seconds. time complexity: O(n) 
																	  */	   
int 		 HeapSchedulerRemove	(scheduler_t *scheduler,            
								ilrd_uid_t task_id);	  				 /* time complexity: O(n) */
size_t 	 	 HeapSchedulerSize		(const scheduler_t *scheduler); 	 /* time complexity: O(n) */
int 		 HeapSchedulerIsEmpty	(const scheduler_t *scheduler); 	 /* time complexity: O(1) */
int 		 HeapSchedulerRun		(scheduler_t *scheduler); 			 /* time complexity: O(1) */
void    	 HeapSchedulerStop		(scheduler_t *scheduler);			 /* stops the scheduler, should be
																	 *	should be wrapped by the user in some sort of a stop action func
																	 *	 time complexity: O(1) 
																	 */
void 		 HeapSchedulerClear		(scheduler_t *scheduler);			 /* time complexity: O(n) */

#endif /* __HEAP_SCHEDULER_H__ */



