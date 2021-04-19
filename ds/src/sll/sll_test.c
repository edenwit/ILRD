#include <stdio.h>

#include "sll.h"
#define TIMES_TO_LOOP 30

int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
	11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 10000};
	
	size_t i = 0;
	void *data = NULL;
	
	s_list_t *list_test = SLLCreate();	
	
	s_list_iter_t node_test = NULL;
	
	if (!SLLIsEmpty(list_test))
	{
		printf ("After Creation list not empty!\n");
	}
	
	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		node_test = SLLInsert(SLLBegin(list_test), (arr + i));
	
		if (!SLLIsSameIter(SLLBegin(list_test),node_test))
		{
			printf ("Insersion #%ld, failed!\n", i + 1);	
		}
	}
	
	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		data = SLLGetData(node_test);
		printf("Current node: %d\n", *(int *)data);
		node_test = SLLNext(node_test);
	}	
	
	data = SLLGetData(SLLBegin(list_test));
	printf("Data in first before set:  %d\n", *(int *)data);
	SLLSetData(SLLBegin(list_test), (arr + 30));
	data = SLLGetData(SLLBegin(list_test));
	printf("Data in first after set:  %d\n", *(int *)data);
	
	node_test = SLLBegin(list_test);

	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		node_test = SLLRemove(SLLBegin(list_test));
	
		if (!SLLIsSameIter(SLLBegin(list_test),node_test))
		{
			printf ("Removal #%ld, failed!\n", i + 1);	
		}
	}	
	
	SLLDestroy(list_test);
	
	return 0;
}

