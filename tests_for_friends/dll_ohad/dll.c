#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */


#include "dll.h"

#define UNUSED(x) (void)(x) 

static int CountIters(void *data, void *param);

typedef struct d_list_node d_list_node_t;

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

/* Approved by Anna */
d_list_t *DLLCreate(void)
{
	d_list_t *list = (d_list_t *)malloc(sizeof(d_list_t));
		
	if (NULL == list)
	{
		return NULL;
	}
	
	list->tail_dummy.next = NULL;
	list->tail_dummy.data = NULL;
	list->tail_dummy.prev = &list->head_dummy;
	
	list->head_dummy.prev = NULL;
	list->head_dummy.data = NULL;
	list->head_dummy.next = &list->tail_dummy;
		
	return (list); 
}

void DLLDestroy(d_list_t *list)
{
	assert(NULL != list);
		
	while (!DLLIsEmpty(list))
	{
		DLLRemove(DLLBegin(list));			
	}
	
	DLLBegin(list)->next = NULL;
	DLLEnd(list)->prev = NULL;
	
	free(list);
	
	return;
}

d_list_iter_t DLLBegin(const d_list_t *list)
{
	assert(NULL != list);

	return (list->head_dummy.next);
}           

d_list_iter_t DLLEnd(const d_list_t *list)
{
	assert(NULL != list);
		
	return ((d_list_iter_t)&list->tail_dummy);
}               

int DLLIsEmpty(const d_list_t *list)
{
	assert(NULL != list);
	
	return (DLLIsSameIter(DLLBegin(list), DLLEnd(list)));
}    

d_list_iter_t DLLPrev(const d_list_iter_t iter)    
{
	assert(NULL != iter);
	
	return (iter->prev);
}

d_list_iter_t DLLNext(const d_list_iter_t iter)
{
	assert(NULL != iter);
	
	return (iter->next);
}

int DLLIsSameIter(const d_list_iter_t iter1, const d_list_iter_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return (iter1 == iter2);
}
 
void *DLLGetData(d_list_iter_t iter)
{
	assert(NULL != iter);
	 
	return (iter->data);
}
  
d_list_iter_t DLLInsert(d_list_iter_t where, void *data)
{
	d_list_node_t *new_node = NULL;
	
	assert(NULL != where);

	new_node = (d_list_node_t *)malloc(sizeof(d_list_node_t));
	
	if (NULL == new_node)
	{
		while (NULL != DLLNext(where))
		{
			where = DLLNext(where);			
		}
		
		return (where);
	}
	
	new_node->data = data;
	new_node->next = where;
	new_node->prev = where->prev;
	
	where->prev->next = new_node; 	
	where->prev = new_node;
	
	return (new_node);
}  

d_list_iter_t DLLRemove(d_list_iter_t iter)
{
	d_list_iter_t temp_node = NULL; 	
	
	assert(NULL != iter);
	
	temp_node = DLLNext(iter);
	
	iter->next->prev = iter->prev;
	iter->prev->next = iter->next;
	
	iter->prev = NULL;
	iter->next = NULL;
	iter->data = NULL;
	
	free(iter);
	
	return (temp_node); 
}

d_list_iter_t DLLPushFront(d_list_t *list, void *data)
{
	assert(NULL != list);
	
	return (DLLInsert(DLLBegin(list), data));
}

d_list_iter_t DLLPushBack(d_list_t *list, void *data)
{
	assert(NULL != list);

	return (DLLInsert(DLLEnd(list), data));
}                               

void *DLLPopBack(d_list_t *list)
{
	void *data = NULL;	
	
	assert(NULL != list);
	assert(!DLLIsEmpty(list));
	
	data = DLLGetData(DLLPrev(DLLEnd(list)));
	
	DLLRemove(DLLPrev(DLLEnd(list)));
	
	return (data); 
}

void *DLLPopFront(d_list_t *list)
{
	void *data = NULL;
	
	assert(NULL != list);
    assert(!DLLIsEmpty(list));	
    
	data = DLLGetData(DLLBegin(list));

	DLLRemove(DLLBegin(list)); 
	
	return (data);
}                              

d_list_iter_t DLLFind(d_list_iter_t from, 
                      d_list_iter_t to,
                      int (*match_func)(const void *data, const void *param),    
                      const void *param)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != match_func);
			
	while (!DLLIsSameIter(from, to))
	{
		
 		if (1 == (match_func(DLLGetData(from), param)))			
		{
			return from;
		}
		
		from = DLLNext(from);
	}
	
	return (to);	
}

int DLLForEach(d_list_iter_t from, 
               d_list_iter_t to,
               int (*action_func)(void *data,void *param),
               void *param)
{
	int status = 0;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action_func);
	
 	while (!DLLIsSameIter(from, to) && !status)
 	{
 		status = action_func(DLLGetData(from), param);
 		from = DLLNext(from);
 	}
 	
 	return (status);
}              	                     

int DLLMultiFind(d_list_iter_t from, 
                 d_list_iter_t to,
                 int (*match_func)(const void *data,const void *param),    
                 const void *param,
                 d_list_t *dest_list)
{
	
	assert(NULL != dest_list);
	assert(NULL != to);
	assert(NULL != from);
	assert(NULL != match_func);
	
	from = DLLFind(from, to, match_func, param);

	while (!DLLIsSameIter(from, to))
	{
		
		if (DLLIsSameIter(	DLLEnd(dest_list),
			              	DLLPushBack(dest_list, DLLGetData(from))
			             ))
		{
			return 1;
		}	
		
		from = DLLFind(DLLNext(from), to, match_func, param);
	}
	
	return 0;
}                 

d_list_iter_t DLLSplice(d_list_iter_t where, 
              			d_list_iter_t from,
         	  			d_list_iter_t to)
{
	d_list_iter_t temp_node = NULL; 	
	
	assert(NULL != where);
	assert(NULL != from);
	assert(NULL != to);
	
	temp_node = DLLPrev(to);
	
	where->prev->next = from;
	from->prev->next = to;
	to->prev->next = where;
	to->prev = from->prev;
	from->prev = where->prev;
	where->prev = temp_node;
	
	return (temp_node);
}
                                  
size_t DLLSize(const d_list_t *list)
{
	size_t count = 0;
	
	assert(NULL != list);
	
	DLLForEach(DLLBegin(list), DLLEnd(list), CountIters, (void *)&count); 
		   
	return (count);	
}                               

         	  			         	  	        	  			
static int CountIters(void *data, void *param)
{		
		UNUSED(data);  
		
		++(*(size_t *)param);
		
		return 0;
}     

 	  			
