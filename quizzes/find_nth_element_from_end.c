#include <stdio.h>
#include <assert.h> /* assert */

#include "../ds/include/sll.h"

void * FindNthElementFromEnd(s_list_t *list, size_t n);
static void FindNthElementFromEndTest();

int main()
{
	FindNthElementFromEndTest();

	return 0;
}

void *FindNthElementFromEnd(s_list_t *list, size_t n)
{
	s_list_iter_t iter1 = NULL;
	s_list_iter_t iter2 = NULL;
	
 	size_t i = 0;
 	
 	assert(list);
 	assert(0 < n);
 	assert(SLLCount(list) >= n);
 	
 	iter1 = SLLBegin(list);
 	iter2 = SLLBegin(list);
 	
 	for (i = 0; i < n; ++i)
 	{
 		iter2 = SLLNext(iter2);
 	}
 	
 	while (NULL != SLLNext(iter2))
	{
 		iter1 = SLLNext(iter1);
  		iter2 = SLLNext(iter2);
	} 

	return SLLGetData(iter1);
}

static void FindNthElementFromEndTest()
{
	int int_arr[] = {1, 5, 14, 64564, 85, 9, 15, 3, 40000, 0, -50};
	size_t i = 0;
	size_t arr_size = sizeof(int_arr) / sizeof(int_arr[0]);
	
	s_list_t *list = SLLCreate();
	s_list_iter_t iter = SLLBegin(list);
	
	for (i = 0; i < arr_size ; ++i)
	{
		iter = SLLInsert(SLLEnd(list), (void *)(int_arr + i));
		if (SLLIsSameIter(iter, SLLEnd(list)))
		{
			printf("Insertion failed! at round %ld.\n", i + 1);
		}
	}
	for (i = 0; i < arr_size ; ++i)
	{
		if (int_arr[arr_size - 1 - i] != *(int *)FindNthElementFromEnd(list, i + 1))
		{
			printf("fail round %ld: %d.\n", i + 1, *(int *)FindNthElementFromEnd(list, i + 1));	
		}		
	}
	
	return;
}

