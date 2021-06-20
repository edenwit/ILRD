#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "dll.h"

#define UNUSED(X) ((void) X)
/*
typedef struct d_list d_list_t;
typedef struct d_list_node *d_list_iter_t;
*/

struct d_list_node
{
	void *data;
	struct d_list_node *next;
	struct d_list_node *prev;
	
};

struct d_list
{
	struct d_list_node head_dummy;
	struct d_list_node tail_dummy;
};

static int Add1(void * data, void *param);


/* complexity time O(1) */

/* Approved by Maor */
d_list_t *DLLCreate(void)
{
	/* create the list manager */
	d_list_t *list = (d_list_t *)malloc(sizeof(d_list_t));
	
	if (NULL == list)
	{
		return NULL;
	}

	list->head_dummy.data = NULL;
	list->head_dummy.next = &list->tail_dummy;
	list->head_dummy.prev = NULL;	
	
	list->tail_dummy.data = NULL;
	list->tail_dummy.next = NULL;	
	list->tail_dummy.prev = &list->head_dummy;
	
	return (list);
}

/* complexity time O(n) */       
            
/* Approved by Maor */ 
void DLLDestroy(d_list_t *list) 
{
	assert(list);
	
	while (!DLLIsEmpty(list))
	{
		DLLRemove(DLLBegin(list));
	}
	
	list->tail_dummy.prev = NULL;
	list->head_dummy.next = NULL;

	free(list);

	return;	
}     

/* Approved by Maor */ 
/* complexity time O(1) */  
int DLLIsEmpty (const d_list_t *list)
{
	assert(list);	
	
	return (DLLIsSameIter(DLLBegin(list), DLLEnd(list)));	
}

/* Approved by Maor */ 
/* complexity time O(n) */              
size_t DLLSize(const d_list_t *list)
{
	size_t counter = 0;

	assert(list);	
		
	DLLForEach(DLLBegin(list), DLLEnd(list), Add1, (void *)&counter);
	
	return (counter);
}                        

/* Approved by Maor */ 
/* complexity time O(1); on failure return end_dummy*/    
d_list_iter_t DLLBegin(const d_list_t *list)
{
	assert(list);	
	
	return (list->head_dummy.next);
}

/* Approved by Maor */ 
/* complexity time O(1) */                               
d_list_iter_t DLLEnd(const d_list_t *list)
{
	assert(list);	
	
	return ((d_list_iter_t)&list->tail_dummy);
}

/* Approved by Maor */ 
/* complexity time O(1) */                        
d_list_iter_t DLLNext(const d_list_iter_t iter)
{
	assert(iter);
	
	return (iter->next);
}
   
/* Approved by Maor */ 
/* complexity time O(1) */     
d_list_iter_t DLLPrev(const d_list_iter_t iter)
{
	assert(iter);
	assert(NULL != iter->prev->prev);	
	
	return (iter->prev);
} 

/* Approved by Maor */ 
/* complexity time O(1) */ 
int DLLIsSameIter(const d_list_iter_t iter1, const d_list_iter_t iter2)
{
	assert(iter1);
	assert(iter2);
	
	return (iter1 == iter2);
}

/* Approved by Maor */ 
/* complexity time O(1) */     
void *DLLGetData(d_list_iter_t iter)
{
	assert(iter);
	
	return (iter->data);
}

/* Approved by Maor */ 
/* complexity time O(1) */     

d_list_iter_t DLLRemove(d_list_iter_t iter)
{
	d_list_iter_t temp = NULL;
	
	assert(iter);
	
	temp = iter->next;
	
	iter->prev->next = iter->next;
	iter->next->prev = iter->prev;
	iter->next = NULL;	
	iter->prev = NULL;
	iter->data = NULL;
	
	free(iter);
	
	return (temp);
}

/* Approved by Maor */ 
/* on success: O(1); */

d_list_iter_t DLLInsert(d_list_iter_t where, void *data)
{
	d_list_iter_t node = NULL;
	
	assert(where);	
	
	node = (d_list_iter_t)malloc(sizeof(struct d_list_node));
	
	if (NULL == node)
	{   
		while (NULL != DLLNext(where))
		{
			where = DLLNext(where);
		}
		
		return (where);
	}
	
	node->data = data;
	where->prev->next = node;
	node->prev = where->prev;
	where->prev = node;
	node->next = where;
	
	return (node);
}

/* Approved by Maor */ 
/* on success: O(1); */
d_list_iter_t DLLPushFront(d_list_t *list, void *data)
{
	assert(list);
	
	return (DLLInsert(DLLBegin(list), data));
}                             
 
 /* Approved by Maor */ 
/* on success: O(1) */
d_list_iter_t DLLPushBack(d_list_t *list, void *data)
{
	assert(list);
	
	return (DLLInsert(DLLEnd(list), data));
}

/* Approved by Maor */ 
/* on success: O(1); */
void *DLLPopFront(d_list_t *list)
{
	void *temp = NULL;
	
	assert(list);
	
	temp = DLLGetData(DLLBegin(list));
	
	DLLRemove(DLLBegin(list));
	
	return (temp);	
}                         

/* Approved by Maor */ 
/* on success: O(1) */
void *DLLPopBack(d_list_t *list)
{
	void *temp = NULL;
	
	assert(list);
	
	temp = DLLGetData(DLLEnd(list)->prev);
	
	DLLRemove(DLLEnd(list)->prev);
	
	return (temp);
}

/* Approved by Maor */ 
/* complexity time O(n) */
d_list_iter_t DLLFind(d_list_iter_t from, 
                      d_list_iter_t to,
                      int (*match_func)(const void *data, const void *param),    
                      const void *param)
{
	assert(from);

	while (!DLLIsSameIter(from,to))
	{
		if (match_func(DLLGetData(from), param))
		{
			return (from);
		}
		from = DLLNext(from);
	}
	
	return (to);
}

/* Approved by Maor */ 
/* complexity time O(n) */                        
int DLLForEach	(d_list_iter_t from, 
              	 d_list_iter_t to,
              	 int (*action_func)(void *data, void *param),
              	 void *param)
{
	int status = 0;

	assert(from);
	assert(action_func);
	
	while (!DLLIsSameIter(from, to) && (0 == status))
	{
		status = action_func(DLLGetData(from), param);
		from = DLLNext(from);
	}
	
	return (status);
}


/* return 0 on success and non zero value on failure */
/* space O(n) time O(n) */
/* Approved by Roman */                   
int DLLMultiFind(d_list_iter_t from, 
                 d_list_iter_t to,
                 int (*match_func)(const void *data,const void *param),    
                 const void *param,
                 d_list_t *dest_list)
{

	assert(from);
	assert(match_func);		
	assert(dest_list);	

	from = DLLFind(from, to, match_func, param);
	
	while (!DLLIsSameIter(from, to))
	{
		if (DLLIsSameIter(DLLPushBack(dest_list, DLLGetData(from)), DLLEnd(dest_list)))
		{
			return (1);
		}
		
		from = DLLFind(DLLNext(from), to, match_func, param);
	}
	
	return (0);
}              
               
               
/* Approved by Roman */                   
/*return to -  the lest elem that was insert to the new list*/
d_list_iter_t DLLSplice(d_list_iter_t where, 
              			d_list_iter_t from,
         	  			d_list_iter_t to)
{
	d_list_iter_t temp = NULL;
	
	assert(from);
	assert(to);		
	assert(where);	

	temp				 = from->prev;
	where->prev->next 	 = from;
	from->prev->next	 = to;
	from->prev			 = where->prev;
	to->prev->next		 = where;
	where->prev			 = to->prev;
	to->prev			 = temp;
	
	return where->prev;
}

/* Approved by Maor */   
static int Add1(void * data, void *param)
{
	UNUSED(data);
	
	++*(size_t *)param;
		
	return (0);
}

