/*  developer: Ohad Ezra
    status: Reviewed bu Shelly 
    date: 2.5.2021
    description: Implementation of sorted list with DLL 
*/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "sorted_ll.h"

static int BiggerOrEqual(const void *data1, const void *data2);
static int IsBigger(const void *data1, const void *data2);									   
static d_list_iter_t ToDListIter(sorted_list_iter_t iter);
static sorted_list_iter_t ToSortedIter(d_list_iter_t iter_dll,
									   sorted_list_t *list);

struct sorted_list
{
	d_list_t *sorted_ll;
	int (*cmp_func)(const void *data, const void *param);
};

typedef struct compare
{
	const void *param; 
	int (*cmp_func)(const void *data, const void *param);
}compare_t;

sorted_list_t *SortedLLCreate(int (*cmp_func)(const void *data1, const void *data2))
{
	sorted_list_t *Sorted_list = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	
	if (NULL == Sorted_list)
	{
		return NULL;
	}  
	
	Sorted_list->sorted_ll = DLLCreate();
	
	if (NULL == Sorted_list->sorted_ll)
	{
		free(Sorted_list);
		
		return NULL;
	}
	
	Sorted_list->cmp_func = cmp_func; 
	
	return Sorted_list;
}

void SortedLLDestroy(sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_ll);
	
	DLLDestroy(list->sorted_ll);
	
	list->sorted_ll = NULL;
	list->cmp_func = NULL;
		
	free(list);
	
	return;	
}

int SortedLLIsEmpty(const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_ll);

	return (DLLIsEmpty(list->sorted_ll));	
}

size_t SortedLLSize(const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_ll);

	return (DLLSize(list->sorted_ll));
}

sorted_list_iter_t SortedLLBegin(const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_ll);

	return (ToSortedIter(DLLBegin(list->sorted_ll), (sorted_list_t *)list));
}

sorted_list_iter_t SortedLLEnd(const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_ll);

	return (ToSortedIter(DLLEnd(list->sorted_ll), (sorted_list_t *)list));
}

sorted_list_iter_t SortedLLNext(const sorted_list_iter_t iter)
{
	sorted_list_iter_t temp_iter = {NULL};
	
	assert(NULL != iter.d_iter);
	assert(NULL != iter.sorted_list);
	
	temp_iter = iter;
	
	*((d_list_iter_t *)&(temp_iter)) = DLLNext(ToDListIter(iter)); 
	
	return (temp_iter);
}

sorted_list_iter_t SortedLLPrev(const sorted_list_iter_t iter)
{
	sorted_list_iter_t temp_iter = {NULL};
	
	assert(NULL != iter.d_iter);
	assert(NULL != iter.sorted_list);
	
	temp_iter = iter;
	
	*((d_list_iter_t *)&(temp_iter)) = DLLPrev(ToDListIter(iter)); 
	
	return (temp_iter);
}

int SortedLLIsSameIter(const sorted_list_iter_t iter1, const sorted_list_iter_t iter2)
{
	assert(NULL != iter1.d_iter);
	assert(NULL != iter1.sorted_list);
	assert(NULL != iter2.d_iter);
	assert(NULL != iter2.sorted_list);
	
	return (DLLIsSameIter(ToDListIter(iter1), ToDListIter(iter2)));
}

void *SortedLLGetData(sorted_list_iter_t iter)
{
	assert(NULL != iter.d_iter);
	assert(NULL != iter.sorted_list);
	
	return (DLLGetData(ToDListIter(iter)));
}

sorted_list_iter_t SortedLLRemove(sorted_list_iter_t iter)
{
	sorted_list_iter_t temp_iter = {NULL};
	
	assert(NULL != iter.d_iter);
	assert(NULL != iter.sorted_list);
	
	temp_iter = iter;
	
	*((d_list_iter_t *)&(temp_iter)) = DLLRemove(ToDListIter(iter));
	
	return (temp_iter);
}

sorted_list_iter_t SortedLLInsert(sorted_list_t *list, void *data)
{
	sorted_list_iter_t temp_iter = {NULL};
	compare_t compare_struct = {NULL};
	
	assert(NULL != list);
	assert(NULL != list->cmp_func);
	
	compare_struct.param = data;
	compare_struct.cmp_func = list->cmp_func;
	
	temp_iter = SortedLLFindIf(SortedLLBegin(list), 
							   SortedLLEnd(list), 
							   IsBigger, 
							   &compare_struct);
	
	temp_iter = ToSortedIter(DLLInsert(ToDListIter(temp_iter), data), list);
	
	return (temp_iter);
}

sorted_list_iter_t SortedLLFind(sorted_list_iter_t from,
								sorted_list_iter_t to, 
								const void *data, 
								sorted_list_t *list)
{
	sorted_list_iter_t temp_iter = from;
	compare_t compare_struct = {NULL};
	
	assert(from.sorted_list == to.sorted_list);
	assert(from.sorted_list == list);
	
	assert(NULL != from.d_iter);
	assert(NULL != to.d_iter);
	
	assert(NULL != from.sorted_list);
	assert(NULL != to.sorted_list);
	
	assert(NULL != list->cmp_func);
		
	compare_struct.param = data;
	compare_struct.cmp_func = list->cmp_func;
	
	*((d_list_iter_t *)&(temp_iter)) = DLLFind(ToDListIter(from), 
									           ToDListIter(to),
									           BiggerOrEqual,
									           &compare_struct);
									            
	if ((!SortedLLIsSameIter(temp_iter, to)) && 
		(0 == list->cmp_func(SortedLLGetData(temp_iter), data)))
	{
		return (temp_iter); 
	}
	
	return (to);	
}								

sorted_list_iter_t SortedLLFindIf(sorted_list_iter_t from,
								  sorted_list_iter_t to,
								  int (*match_func)(const void *data,
								  				    const void *param),
								  const void *param)		
{
	sorted_list_iter_t temp_iter = from;
	
	assert(from.sorted_list == to.sorted_list);	
	assert(NULL != match_func);

	assert(NULL != from.d_iter);
	assert(NULL != to.d_iter);

	assert(NULL != from.sorted_list);
	assert(NULL != to.sorted_list);	
	
	*((d_list_iter_t *)&(temp_iter)) = DLLFind(ToDListIter(from), 
									           ToDListIter(to),
									           match_func,
									           param);										        
	return (temp_iter);
}

void *SortedLLPopFront(sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_ll);

	return (DLLPopFront(list->sorted_ll));
}

void *SortedLLPopBack(sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_ll);

	return (DLLPopBack(list->sorted_ll));
}


int SortedLLForEach(sorted_list_iter_t from,
					sorted_list_iter_t to,
					int (*action_func)(void *data, void *param),
					void *param)
{
	assert(NULL != action_func);
	assert(NULL != from.d_iter);
	assert(NULL != from.sorted_list);
	assert(NULL != to.d_iter);
	assert(NULL != to.sorted_list);
	
	assert(from.sorted_list == to.sorted_list);
		
	return (DLLForEach(ToDListIter(from), ToDListIter(to), action_func, param));   
}


void SortedLLMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{
	sorted_list_iter_t where_dest = SortedLLBegin(dest_list);
	sorted_list_iter_t to_src = {NULL};
	compare_t compare_struct = {NULL};
   
	assert(NULL != dest_list);
	assert(NULL != src_list);
	assert(NULL != dest_list->cmp_func);
	assert(dest_list != src_list);
	
	compare_struct.cmp_func = dest_list->cmp_func;
	
	while (!SortedLLIsEmpty(src_list))  
	{
		compare_struct.param = SortedLLGetData(SortedLLBegin(src_list));
		
		where_dest = SortedLLFindIf(where_dest,
								    SortedLLEnd(dest_list),
								    IsBigger,
								    &compare_struct); /* begin src data  */
								  
		if (SortedLLIsSameIter(where_dest, SortedLLEnd(dest_list)))
		{
			DLLSplice(ToDListIter(where_dest), 
								  ToDListIter(SortedLLBegin(src_list)), 
								  ToDListIter(SortedLLEnd(src_list)));
								  
			break;			
		}
		
		compare_struct.param = SortedLLGetData(where_dest);
					
 		to_src = SortedLLFindIf(SortedLLBegin(src_list),
 						      SortedLLEnd(src_list),
 						      BiggerOrEqual,
 						      &compare_struct); /* where_dest data */  
 		
		DLLSplice(ToDListIter(where_dest),
							  ToDListIter(SortedLLBegin(src_list)),
							  ToDListIter(to_src));
	}
	
	return;	
}
					
static d_list_iter_t ToDListIter(sorted_list_iter_t iter)
{
	
	#ifdef NDEBUG
	
	return ((d_list_iter_t)iter);	
	
	#else
	
	return((d_list_iter_t)iter.d_iter);
	
	#endif
} 


static sorted_list_iter_t ToSortedIter(d_list_iter_t iter_dll, sorted_list_t *list)
{
	sorted_list_iter_t iter;
	
	assert(NULL != iter_dll);
	assert(NULL != list);
	
	#ifdef NDEBUG
	
	(void)list;
	(void)iter;
	
	return ((sorted_list_iter_t)iter_dll);	 
	
	#else
	
	iter.d_iter = iter_dll;
	iter.sorted_list = list;
	
	return(iter);
	
	#endif
} 

static int IsBigger(const void *data1, const void *data2)
{      	
	return (0 < ((compare_t *)data2)->cmp_func(data1, ((compare_t *)data2)->param)); 
}

static int BiggerOrEqual(const void *data1, const void *data2)
{      
	return (0 <= ((compare_t *)data2)->cmp_func(data1, ((compare_t *)data2)->param)); 
}





