#include <stdio.h>

#include "dll.h"
#define TIMES_TO_LOOP 30

static int FindMatchInt(const void * data, const void *param);


int main()
{

	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
	11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 10000};
	
	int dum_num = 541;
	size_t i = 0;
	size_t counter = 0;
		
	void *data = NULL;
	
	d_list_t *list_test = DLLCreate();	
	d_list_iter_t node_test = NULL;
	
	if (NULL == list_test)
	{
		printf("List not created!\n");
	}

	if (!DLLIsEmpty(list_test))
	{
		printf ("After Creation list not empty!\n");
	}

	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		node_test = DLLInsert(DLLBegin(list_test), (arr + i));
	
		if (!DLLIsSameIter(DLLBegin(list_test),node_test))
		{
			printf ("Insersion #%ld, failed!\n", i + 1);	
		}
	}
	
	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		data = DLLGetData(node_test);
		if (*(int *)data != (TIMES_TO_LOOP - arr[i] + 1))
		{
			printf("Current node: %d, in arr: %d\n", *(int *)data, (TIMES_TO_LOOP - arr[i] + 1));
		}
		node_test = DLLNext(node_test);
	}	
	
	data = DLLGetData(DLLBegin(list_test));
	if (*(int *)data != arr[TIMES_TO_LOOP - 1])
	{
		printf("Data in first before set:  %d, in arr: %d\n", *(int *)data, arr[TIMES_TO_LOOP - 1]);
	}	

	data = DLLGetData(DLLFind(DLLBegin(list_test), DLLEnd(list_test), FindMatchInt, (const void *)(arr + 16)));
	if (*(int *)data != arr[16])
	{
		printf("Data in first before set:  %d, in arr: %d\n", *(int *)data, arr[TIMES_TO_LOOP - 1]);
	}	
	
	node_test = DLLBegin(list_test);

	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		node_test = DLLRemove(DLLBegin(list_test));
	
		if (!DLLIsSameIter(DLLBegin(list_test),node_test))
		{
			printf ("Removal #%ld, failed!\n", i + 1);
		}
	}	
	
	counter = DLLSize(list_test);
	
	if(0 != counter)
	{
		printf("Num Of members: %ld\n", counter);
	}

	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		node_test = DLLInsert(DLLEnd(list_test), (arr + i));

	}
	
	node_test = DLLFind(DLLBegin(list_test), DLLEnd(list_test), FindMatchInt, (const void *)&(arr[2]));
	
	if (3 != *(int *)DLLGetData(node_test))
	{
		printf("Find Failed. value searched: %d, actual value: %d.\n", *(int *)(arr + 2), *(int *)DLLGetData(node_test));
	}
	
	node_test = DLLFind(DLLBegin(list_test), DLLEnd(list_test), FindMatchInt, (const void *)&dum_num);

	if (!DLLIsSameIter(DLLEnd(list_test),node_test))
	{
		printf("find fail test didnt go to end!\n");	
	}


	DLLDestroy(list_test);
	
	return 0;
}

static int FindMatchInt(const void * data, const void *param)
{
	return (*(int *)data == *(int *)param);
}

