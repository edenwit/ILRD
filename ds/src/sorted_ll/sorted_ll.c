#include <stddef.h> /*size_t*/

#include "dll.h"
#include "sorted_ll.h"

in c file:

struct sorted_list
{
	d_list_t *list;
	int (*cmp_func)(const void *data, const void *param);
};

/*
#ifdef NDEBUG

typedef d_list_iter_t sorted_list_iter_t;

#else

typedef struct sorted_list_iter
{
	d_list_iter_t node;
	struct sorted_list *list;
}sorted_list_iter_t;

#endif /* NDEBUG */
*/
/* O(1) */
sorted_list_t *    SortedLLCreate    (int (*cmp_func)(const void *data1, const void *data2))
{
	sorted_list_t *sorted_list = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	
	if (NULL == sorted_list)
	{    
		return NULL;
	}

	sorted_list->list = DLLCreate();
	
	if (NULL == sorted_list->list)
	{    
		free(sorted_list);
		
		return NULL;
	}
	
	sorted_list->cmp_func = cmp_func;
	
	return sorted_list;
}


/* O(n) */
void 			 SortedLLDestroy     (sorted_list_t *list)
{
	assert(NULL != list);
	
	SLLDestroy(list->list);
	list->list = NULL;
	list->cmp_func = NULL;
	free(list);
	
	return;
}                

/* O(1) */
int 			 SotedLLIsEmpty      (const sorted_list_t *list)
{
	assert(NULL != list);
	
	return DLLIsEmpty(list->list);
}

/* O(n) */        
size_t           SortedLLSize	     (const sorted_list_t *list)
{
	assert(NULL != list);
	
	return DLLSize(list->list);
}


/* O(1) */
sorted_list_iter_t SortedLLBegin     (const sorted_list_t *list)
{
	assert(NULL != list);
	
	return DLLBegin(list->list);
}

/* O(1) */                        
sorted_list_iter_t SortedLLEnd	     (const sorted_list_t *list)
{
	assert(NULL != list);
	
	return DLLEnd(list->list);
} 

/* O(1) */               
sorted_list_iter_t SortedLLNext      (const sorted_list_iter_t iter);

/* O(1) */
sorted_list_iter_t SortedLLPrev	     (const sorted_list_iter_t iter);

/* O(1) */
int 			   SortedLLIsSameIter(const sorted_list_iter_t iter1, const sorted_list_iter_t iter2);

/* O(1) */
void *             SortedLLGetData   (sorted_list_iter_t iter);

/* O(1) */
sorted_list_iter_t SortedLLRemove    (sorted_list_iter_t iter);

/* O(n) */
sorted_list_iter_t SortedLLInsert    (sorted_list_t *list, void *data);

/* O(1) */				                   		                   
void *		       SortedLLPopFront  (sorted_list_t *list)
{
	assert(NULL != list);
	
	return DLLPopFront(list->list);
}                           

/* O(1) */
void *             SortedLLPopBack   (sorted_list_t *list)
{
	assert(NULL != list);
	
	return DLLPopBack(list->list);
} 

/* O(n) */
sorted_list_iter_t SortedLLFind      (sorted_list_iter_t from, sorted_list_iter_t to, const void *data);

/* O(n) */
sorted_list_iter_t SortedLLFindIf    (sorted_list_iter_t from, 
				                      sorted_list_iter_t to,
				                      int (*match_func)(const void *data, const void *param),    
				                      const void *param);
				                   		                   
/* O(n) */
int                SortedLLForEach   (sorted_list_iter_t from, 
				      	              sorted_list_iter_t to,
				                      int (*action_func)(void *data,void *param),
				      	  		      void *param);

/* O(n + m) */				           
void 			   SortedLLMerge	 (sorted_list_t *dest_list, sorted_list_t *src_list);

sorted_list_iter_t ToDListIter(sorted_list_iter_t iter)
{
	#ifdef NDEBUG
	
	return (d_list_iter_t)(iter);
	
	#else

	return (d_list_iter_t)(iter->node);

	#endif /* NDEBUG */
}

sorted_list_iter_t ToSortedIter(d_list_iter_t iter, param)
{
	#ifdef NDEBUG
	
	return (sorted_list_iter_t)(iter);
	
	#else
	
	unused(param);
	param->node = (sorted_list_iter_t)(iter);
	
	return param;

	#endif /* NDEBUG */
}

