#include <stdio.h>

#include "sll.h"
#define TIMES_TO_LOOP 30

static int FindMatchInt(const void * data, void *param);


int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
	11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 10000};
	
	int dum_num = 541;
	size_t i = 0;
	size_t counter = 0;
		
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
		if (*(int *)data != (TIMES_TO_LOOP - arr[i] + 1))
		{
			printf("Current node: %d, in arr: %d\n", *(int *)data, (TIMES_TO_LOOP - arr[i] + 1));
		}
		node_test = SLLNext(node_test);
	}	
	
	data = SLLGetData(SLLBegin(list_test));
	if (*(int *)data != arr[TIMES_TO_LOOP - 1])
	{
		printf("Data in first before set:  %d, in arr: %d\n", *(int *)data, arr[TIMES_TO_LOOP - 1]);
	}	

	SLLSetData(SLLBegin(list_test), (arr + 30));
	data = SLLGetData(SLLBegin(list_test));
	if (*(int *)data != arr[30])
	{
		printf("Data in first after set:  %d\n", *(int *)data);
	}	
	
	node_test = SLLBegin(list_test);

	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		node_test = SLLRemove(SLLBegin(list_test));
	
		if (!SLLIsSameIter(SLLBegin(list_test),node_test))
		{
			printf ("Removal #%ld, failed!\n", i + 1);
		}
	}	
	
	counter = SLLCount(list_test);
	
	if(0 != counter)
	{
		printf("Num Of members: %ld\n", counter);
	}

	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		node_test = SLLInsert(SLLEnd(list_test), (arr + i));

	}
	
	node_test = SLLFind(SLLBegin(list_test), SLLEnd(list_test), FindMatchInt, (void *)&(arr[2]));
	
	if (3 != *(int *)SLLGetData(node_test))
	{
		printf("Find Failed. value searched: %d, actual value: %d.\n", *(int *)(arr + 2), *(int *)SLLGetData(node_test));
	}
	
	node_test = SLLFind(SLLBegin(list_test), SLLEnd(list_test), FindMatchInt, (void *)&dum_num);

	if (!SLLIsSameIter(SLLEnd(list_test),node_test))
	{
		printf("find fail test didnt go to end!\n");	
	}


	SLLDestroy(list_test);
	
	return 0;
}

static int FindMatchInt(const void * data, void *param)
{
	return (*(int *)data == *(int *)param);
}

