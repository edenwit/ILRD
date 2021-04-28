#include <stddef.h> /*size_t*/
#include <stdlib.h> /* malloc */
#include <assert.h>

#include "dll.h"

#define UNUSED(X) ((void) X)

typedef struct d_list_node d_list_node_t;
typedef struct d_list dll_t;

struct d_list_node
{
	void *data;
	d_list_node_t *next;
	d_list_node_t *prev;
	
};

struct d_list
{
	d_list_node_t head_dummy;
	d_list_node_t tail_dummy;
};

static int Add1(void * data, void *param);


/* complexity time O(1) */
d_list_t *DLLCreate(void)
{
	/* create the list manager */
	dll_t *list = (dll_t *)malloc(sizeof(dll_t));
	
	if (NULL == list)
	{
		return NULL;
	}

	list->head_dummy.data = NULL;
	list->head_dummy.prev = NULL;	
	list->head_dummy.next = &list->tail_dummy;
	
	list->tail_dummy.data = NULL;
	list->tail_dummy.prev = &list->head_dummy;
	list->tail_dummy.next = NULL;	
	
	return list;
}

/* complexity time O(n) */       
             
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
	
}     

/* complexity time O(1) */  
int DLLIsEmpty (const d_list_t *list)
{
	assert(list);	
	
	return DLLIsSameIter(DLLBegin(list), DLLEnd(list));	
}

/* complexity time O(n) */              
size_t DLLSize(const d_list_t *list)
{
	size_t counter = 0;

	assert(list);	
		
	DLLForEach(DLLBegin(list), DLLEnd(list), Add1, (void *)&counter);
	
	return counter;
}                        

/* complexity time O(1); on failure return end_dummy*/    
d_list_iter_t DLLBegin(const d_list_t *list)
{
	assert(list);	
	
	return list->head_dummy.next;
}

/* complexity time O(1) */                               
d_list_iter_t DLLEnd(const d_list_t *list)
{
	assert(list);	
	
	return (d_list_iter_t)&list->tail_dummy;
}

/* complexity time O(1) */                        
d_list_iter_t DLLNext(const d_list_iter_t iter)
{
	assert(iter);
	
	return iter->next;
}
   
/* complexity time O(1) */     
d_list_iter_t DLLPrev(const d_list_iter_t iter)
{
	assert(iter);
	assert(NULL != iter->prev->prev);	
	
	return iter->prev;
} 

/* complexity time O(1) */ 
int DLLIsSameIter(const d_list_iter_t iter1, const d_list_iter_t iter2)
{
	assert(iter1);
	assert(iter2);
	
	return iter1 == iter2;
}

/* complexity time O(1) */     
void *DLLGetData(d_list_iter_t iter)
{
	assert(iter);
	
	return iter->data;
}

/* complexity time O(1) */     
d_list_iter_t DLLRemove(d_list_iter_t iter)
{
	d_list_iter_t temp = iter->next;
	
	/*assert(iter->prev->prev);*/
	assert(iter);
	
	iter->prev->next = iter->next;
	iter->next->prev = iter->prev;
	iter->next = NULL;	
	iter->prev = NULL;
	iter->data = NULL;
	
	free(iter);
	
	return temp;
}

/* on success: O(1); */
d_list_iter_t DLLInsert(d_list_iter_t where, void *data)
{
	d_list_iter_t node = NULL;
	
	assert(where);	
	
	node = (d_list_iter_t)malloc(sizeof(d_list_node_t));
	
	if (NULL == node)
	{   
		while (NULL != DLLNext(where))
		{
			where = DLLNext(where);
		}
		
		return where;
	}
	
	node->data = data;
	where->prev->next = node;
	node->prev = where->prev;
	where->prev = node;
	node->next = where;
	
	return node;
}

/* on success: O(1); */
d_list_iter_t DLLPushFront(d_list_t *list, void *data)
{
	assert(list);
	
	return DLLInsert(DLLBegin(list), data);
}                             
 
/* on success: O(1) */
d_list_iter_t DLLPushBack(d_list_t *list, void *data)
{
	assert(list);
	
	return DLLInsert(DLLEnd(list), data);
}

/* on success: O(1); */
void *DLLPopFront(d_list_t *list)
{
	void *temp = NULL;
	
	assert(list);
	
	temp = DLLGetData(DLLBegin(list));
	
	DLLRemove(DLLBegin(list));
	
	return temp;	
}                         

/* on success: O(1) */
void *DLLPopBack(d_list_t *list)
{
	void *temp = NULL;
	
	assert(list);
	
	temp = DLLGetData(DLLEnd(list)->prev);
	
	DLLRemove(DLLEnd(list)->prev);
	
	return temp;
}

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
			return from;
		}
		from = DLLNext(from);
	}
	
		return to;
}

/* complexity time O(n) */                        
int DLLForEach	(d_list_iter_t from, 
              	 d_list_iter_t to,
              	 int (*action_func)(void *data,void *param),
              	 void *param)
{
	int status = 0;

	assert(from);
	
	while (!DLLIsSameIter(from,to) && (0 == status))
	{
		status = action_func(DLLGetData(from), param);
		from = DLLNext(from);
	}
	
	return status;
}


/* return 0 on success and non zero value on failure */
/* space O(n) time O(n) */


int DLLMultiFind(d_list_iter_t from, 
                 d_list_iter_t to,
                 int (*match_func)(const void *data,const void *param),    
                 const void *param,
                 d_list_t *dest_list)
{

	assert(from);
	assert(dest_list);	

	from = DLLFind(from, to, match_func, param);
	
	while (!DLLIsSameIter(from,to))
	{
		if (DLLIsSameIter(DLLPushBack(dest_list, DLLGetData(from)),DLLEnd(dest_list)))
		{
			return 1;
		}
		
		from = DLLFind(DLLNext(from), to, match_func, param);
	}
	
	return 0;
}              
                 
/*return to -  the lest elem that was insert to the new list*/
d_list_iter_t DLLSplice(d_list_iter_t where, 
              			d_list_iter_t from,
         	  			d_list_iter_t to)
{
	d_list_iter_t temp = NULL;
	
	assert(from);
	assert(where);	

	temp = from->prev;
	where->prev->next 	 = from;
	from->prev->next	 = to;
	from->prev			 = where->prev;
	to->prev->next		 = where;
	where->prev			 = to->prev;
	to->prev			 = temp;
	
	return where->prev;
}

  
static int Add1(void * data, void *param)
{
	UNUSED(data);
	
	++*(size_t *)param;
		
	return 0;
}

