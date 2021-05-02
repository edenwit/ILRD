#include <stddef.h> /*size_t*/
#include <stdlib.h> /* free */
#include <assert.h> /* assert */


#include "../dll/dll.h"
#include "sorted_ll.h"

#define UNUSED(X) ((void) X)

struct sorted_list
{
	d_list_t *list;
	int (*cmp_func)(const void *data, const void *param);
};

typedef struct for_find
{
	const void* param; /* what we look for*/
	int (*cmp_func)(const void *data, const void *param);
} finder_t;

static d_list_iter_t ToDListIter(sorted_list_iter_t iter);
static sorted_list_iter_t ToSortedIter(d_list_iter_t iter_dll, sorted_list_t *list);

static int IsBigger(const void *data, const void * finder); /*data is what the user gives*/
static int IsBiggerEqual(const void *data, const void * finder); /*data is what the user gives*/


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
	
	return (sorted_list);
}


/* O(n) */
void 			 SortedLLDestroy     (sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->list);	
	
	DLLDestroy(list->list);
	
	list->list = NULL;
	list->cmp_func = NULL;
	
	free(list);
	
	return;
}                

/* O(1) */
int 			   SortedLLIsEmpty    (const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->list);	
		
	return (DLLIsEmpty(list->list));
}

/* O(n) */        
size_t           SortedLLSize	     (const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->list);	
		
	return (DLLSize(list->list));
}


/* O(1) */
sorted_list_iter_t SortedLLBegin     (const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->list);	
		
	return (ToSortedIter(DLLBegin(list->list), (sorted_list_t *)list));
}

/* O(1) */                        
sorted_list_iter_t SortedLLEnd	     (const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->list);	
		
	return (ToSortedIter(DLLEnd(list->list), (sorted_list_t *)list));
} 

/* O(1) */               
sorted_list_iter_t SortedLLNext      (const sorted_list_iter_t iter)
{
	
	sorted_list_iter_t temp_iter = {0};

	assert(NULL != iter.d_iter);
	assert(NULL != iter.sorted_list);

	temp_iter = iter;
	
	*((d_list_iter_t *)&(temp_iter)) = DLLNext(ToDListIter(iter));
	
	return (temp_iter);
}

/* O(1) */
sorted_list_iter_t SortedLLPrev	     (const sorted_list_iter_t iter)
{
	sorted_list_iter_t temp_iter = {0};
	
	assert(NULL != iter.d_iter);
	assert(NULL != iter.sorted_list);
	
	temp_iter = iter;

	*((d_list_iter_t *)&(temp_iter)) = DLLPrev(ToDListIter(iter));
	
	return (iter);	
}
/* O(1) */
int 			   SortedLLIsSameIter(const sorted_list_iter_t iter1, const sorted_list_iter_t iter2)
{
	assert(NULL != iter1.d_iter);
	assert(NULL != iter1.sorted_list);
	assert(NULL != iter2.d_iter);
	assert(NULL != iter2.sorted_list);
	
	return 	(DLLIsSameIter(ToDListIter(iter1), ToDListIter(iter2)));
}

/* O(1) */
void *             SortedLLGetData   (sorted_list_iter_t iter)
{
	assert(NULL != iter.d_iter);		
	assert(NULL != iter.sorted_list);
		
	return (DLLGetData(ToDListIter(iter)));
}

/* O(1) */
sorted_list_iter_t SortedLLRemove    (sorted_list_iter_t iter)
{
	sorted_list_iter_t temp_iter = {0};
	
	assert(NULL != iter.d_iter);		
	assert(NULL != iter.sorted_list);
	
	temp_iter = iter;
	
	*((d_list_iter_t *)&(temp_iter)) = DLLRemove(ToDListIter(iter));
	
	return (temp_iter);
}

/* O(n) */


sorted_list_iter_t SortedLLInsert    (sorted_list_t *list, void *data)
{
	sorted_list_iter_t iter = {0};
	finder_t finder = {0};
	
	assert(NULL != list);
	assert(NULL != list->list);	

	finder.cmp_func = list->cmp_func;
	finder.param = data;
	
	iter = SortedLLFindIf(SortedLLBegin(list), SortedLLEnd(list), IsBigger, &finder);
	
	iter = ToSortedIter(DLLInsert(ToDListIter(iter), data), list);
	
	return (iter);	
}


/* O(1) */				                   		                   
void *		       SortedLLPopFront  (sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->list);		
	
	return (DLLPopFront(list->list));
}

/* O(1) */
void *             SortedLLPopBack   (sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->list);	
	
	return (DLLPopBack(list->list));
}

/* O(n) */
sorted_list_iter_t SortedLLFind      (sorted_list_iter_t from, sorted_list_iter_t to, const void *data,	sorted_list_t *list)
 /* FInd next iter with higher value */
{
	sorted_list_iter_t temp_iter = {0};	
	finder_t finder = {0};

    assert(from.sorted_list == to.sorted_list);	
	assert(NULL != from.d_iter);		
	assert(NULL != from.sorted_list);
	assert(NULL != to.d_iter);		
	assert(NULL != to.sorted_list);	
	assert(NULL != list);
	assert(NULL != list->list);		

	finder.cmp_func = list->cmp_func;
	finder.param = data;
	
	temp_iter = (ToSortedIter(DLLFind(ToDListIter(from), ToDListIter(to), IsBiggerEqual, &finder), list));
	
	if (!SortedLLIsSameIter(temp_iter, to))
	{
		if (0 == list->cmp_func(SortedLLGetData(temp_iter), &finder))
		{
			return (temp_iter);
		}
	}

	return (to);
} 

/* O(n) */

sorted_list_iter_t SortedLLFindIf    (sorted_list_iter_t from, 
				                      sorted_list_iter_t to,
				                      int (*match_func)(const void *data, const void *param),    
				                      const void *param)
{
	sorted_list_iter_t temp_iter = from;

    assert(from.sorted_list == to.sorted_list);
	assert(NULL != from.d_iter);		
	assert(NULL != from.sorted_list);
	assert(NULL != to.d_iter);		
	assert(NULL != to.sorted_list);	 
	
    *((d_list_iter_t *)&(temp_iter)) = DLLFind(ToDListIter(from), ToDListIter(to), match_func, param);
    
    return temp_iter;
}
			                   		                   
/* O(n) */
int                SortedLLForEach   (sorted_list_iter_t from, 
				      	              sorted_list_iter_t to,
				                      int (*action_func)(void *data,void *param),
				      	  		      void *param)
{
    assert(from.sorted_list == to.sorted_list);
	assert(NULL != from.d_iter);		
	assert(NULL != from.sorted_list);
	assert(NULL != to.d_iter);		
	assert(NULL != to.sorted_list);	    
	
    return DLLForEach(ToDListIter(from), ToDListIter(to), action_func, param);
}

/* O(n + m) */	
		           
void SortedLLMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{

    sorted_list_iter_t where = SortedLLBegin(dest_list);
    sorted_list_iter_t to = {0};
	finder_t finder = {0};

	assert(NULL != src_list);
    assert(NULL != src_list->list);    
    assert(NULL != dest_list);
    assert(NULL != dest_list->list);

	finder.cmp_func = dest_list->cmp_func;
			
    while(!SortedLLIsEmpty(src_list))
    {
       	finder.param = SortedLLGetData(SortedLLBegin(src_list));
       	
        where = SortedLLFindIf(where, SortedLLEnd(dest_list), IsBigger, &finder);

        if(SortedLLIsSameIter(where, SortedLLEnd(dest_list)))
        {
            DLLSplice(ToDListIter(where), ToDListIter(SortedLLBegin(src_list)), ToDListIter(SortedLLEnd(src_list)));
            
            return;
        }
       	finder.param = SortedLLGetData(where);            
        to = SortedLLFindIf(SortedLLBegin(src_list), SortedLLEnd(src_list), IsBiggerEqual, &finder);
        
        DLLSplice(ToDListIter(where), ToDListIter(SortedLLBegin(src_list)), ToDListIter(to));
    }

    return;
}

static d_list_iter_t ToDListIter(sorted_list_iter_t iter)
{
    assert(NULL != iter.d_iter);

    #ifdef NDEBUG

    return ((d_list_iter_t)iter);

    #else

    return((d_list_iter_t)iter.d_iter);

    #endif
} 

static sorted_list_iter_t ToSortedIter(d_list_iter_t iter_dll, sorted_list_t *list)
{
    sorted_list_iter_t iter = {0};

    assert(NULL != iter_dll);
    assert(NULL != list);

    #ifdef NDEBUG
    UNUSED(iter);
    UNUSED(list);
    return ((sorted_list_iter_t)iter_dll);

    #else
    iter.d_iter = iter_dll;
    iter.sorted_list = (sorted_list_t *)list;

    return(iter);

    #endif
}

static int IsBigger(const void *data, const void *finder) /*data is what the user gives*/
{
	finder_t *finder_ptr = (finder_t *)finder;

	return (0 < finder_ptr->cmp_func(data, finder_ptr->param));
}

static int IsBiggerEqual(const void *data, const void *finder) /*data is what the user gives*/
{
	finder_t *finder_ptr = (finder_t *)finder;

	return (0 <= finder_ptr->cmp_func(data, finder_ptr->param));
}


