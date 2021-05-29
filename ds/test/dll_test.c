#include <stdio.h>

#include "dll.h"
#define TIMES_TO_LOOP 30
#define TIMES_TO_LOOP_2 10

static int FindMatchInt(const void * data, const void *param);
static int PrintInt(void *data,void *param);

int main()
{

	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
	11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 10000};
	
	int num_ten = 10;
	int dum_num = 541;
	size_t i = 0;
	size_t counter = 0;
	size_t status = 0;	
	void *data = NULL;
	
	d_list_t *list_test = DLLCreate();	
	d_list_t *spliced_list_test = DLLCreate();	
	
	d_list_iter_t node_test = NULL;
	d_list_iter_t node_test_2 = NULL;
	
	d_list_iter_t where_node = NULL;
	d_list_iter_t from_node = NULL;
	d_list_iter_t to_node = NULL;	
		
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
	
	for (i = 0; i < TIMES_TO_LOOP_2; ++i)
	{
		node_test_2 = DLLInsert(DLLBegin(spliced_list_test), (void *)&num_ten);
	
		if (!DLLIsSameIter(DLLBegin(spliced_list_test),node_test_2))
		{
			printf ("Insersion #%ld to list 2, failed!\n", i + 1);	
		}
	}
	
	counter = DLLSize(spliced_list_test);
	
	if(TIMES_TO_LOOP_2 != counter)
	{
		printf("Num Of members: %ld\n", counter);
	}	

	node_test_2 = DLLBegin(spliced_list_test);

	for (i = 0; i < TIMES_TO_LOOP_2; ++i)
	{
		node_test_2 = DLLRemove(DLLBegin(spliced_list_test));
	
		if (!DLLIsSameIter(DLLBegin(spliced_list_test),node_test_2))
		{
			printf ("Removal #%ld, failed!\n", i + 1);
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
	
	node_test = DLLPushFront(list_test, (void *)&dum_num);
	if (!DLLIsSameIter(DLLBegin(list_test),node_test))
	{
			printf ("DLLPushFront #%ld, failed!\n", i + 1);
	}
	node_test = DLLPushBack(list_test, (void *)&dum_num);
	if (!DLLIsSameIter(DLLPrev(DLLEnd(list_test)), node_test))
	{
			printf ("DLLPushBack #%ld, failed!\n", i + 1);
	}
	
	counter = DLLSize(spliced_list_test);
	
	if(0 != counter)
	{
		printf("Num Of members: %ld\n", counter);
	}		
	
	status = DLLMultiFind(DLLBegin(list_test), DLLEnd(list_test), FindMatchInt, (const void *)&dum_num, spliced_list_test);
	
	if(0 != status)
	{
		printf("DLLMultiFind failed!\n");
	}
	
	if(2 != DLLSize(spliced_list_test))
	{
		printf("DLLMultiFind failed! expected size: 2, actual: %ld.\n", DLLSize(spliced_list_test));
	}		
		
	if (dum_num != *(int *)DLLPopFront(list_test))
	{
			printf ("DLLPopFront #%ld, failed!\n", i + 1);
	}
	if (dum_num != *(int *)DLLPopBack(list_test))
	{
			printf ("DLLPopBack #%ld, failed!\n", i + 1);
	}	

	if (dum_num != *(int *)DLLPopFront(spliced_list_test))
	{
			printf ("DLLPopFront #%ld, failed!\n", i + 1);
	}
	if (dum_num != *(int *)DLLPopBack(spliced_list_test))
	{
			printf ("DLLPopBack #%ld, failed!\n", i + 1);
	}	

	status = DLLMultiFind(DLLBegin(list_test), DLLEnd(list_test), FindMatchInt, (const void *)&dum_num, spliced_list_test);
	
	if(0 != status)
	{
		printf("DLLMultiFind failed!\n");
	}
	
	if(!DLLIsEmpty(spliced_list_test))
	{
		printf("List2 supposed to be empty! actual: %ld.\n", DLLSize(spliced_list_test));
	}	


	for (i = 0; i < TIMES_TO_LOOP_2; ++i)
	{
		node_test = DLLInsert(DLLBegin(spliced_list_test), (arr + i));
	
		if (!DLLIsSameIter(DLLBegin(spliced_list_test),node_test))
		{
			printf ("Insersion #%ld, failed!\n", i + 1);	
		}
	}
	
	
	
	printf("list1 Num Of members before splice: %ld\n", DLLSize(list_test));
	printf("list2 Num Of members before splice: %ld\n", DLLSize(spliced_list_test));	

	DLLForEach(DLLBegin(list_test), DLLEnd(list_test), PrintInt, NULL);
	printf("\n");	
	DLLForEach(DLLBegin(spliced_list_test), DLLEnd(spliced_list_test), PrintInt, NULL);
	printf("\n");	
	
	where_node = DLLBegin(list_test);
	from_node = DLLBegin(spliced_list_test);
	to_node = DLLEnd(spliced_list_test);

	for (i = 0; i < TIMES_TO_LOOP_2 / 2; ++i)
	{
		where_node = DLLNext(where_node);
	}
	
	for (i = 0; i < TIMES_TO_LOOP_2 / 5; ++i)
	{
		from_node = DLLNext(from_node);
	}
	
	for (i = 0; i < TIMES_TO_LOOP_2 / 5	; ++i)
	{
		to_node = DLLPrev(to_node);
	}		
	
	
	node_test = DLLSplice(where_node, from_node, to_node);
	
	printf("list1 Num Of members before splice: %ld\n", DLLSize(list_test));
	printf("list2 Num Of members before splice: %ld\n", DLLSize(spliced_list_test));		
	
	DLLForEach(DLLBegin(list_test), DLLEnd(list_test), PrintInt, NULL);
	printf("\n");	
	DLLForEach(DLLBegin(spliced_list_test), DLLEnd(spliced_list_test), PrintInt, NULL);
	printf("\n");	

	DLLDestroy(list_test);
	DLLDestroy(spliced_list_test);
	
	list_test = DLLCreate();	
	spliced_list_test = DLLCreate();	
	
	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		node_test = DLLInsert(DLLBegin(list_test), (arr + i));
	
		if (!DLLIsSameIter(DLLBegin(list_test),node_test))
		{
			printf ("Insersion #%ld, failed!\n", i + 1);	
		}
	}
	
	for (i = 0; i < TIMES_TO_LOOP_2; ++i)
	{
		node_test_2 = DLLInsert(DLLBegin(spliced_list_test), (void *)&num_ten);
	
		if (!DLLIsSameIter(DLLBegin(spliced_list_test),node_test_2))
		{
			printf ("Insersion #%ld to list 2, failed!\n", i + 1);	
		}
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
	DLLDestroy(spliced_list_test);
	
	return 0;
}

static int FindMatchInt(const void * data, const void *param)
{
	return (*(int *)data == *(int *)param);
}

static int PrintInt(void *data,void *param)
{
    (void)param;

    printf("%d ", *(int *)data);

    return 0; 
}
