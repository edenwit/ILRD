#include <stdio.h> /* printf */

#include "sorted_ll.h"

#define TIMES_TO_LOOP 30



static void sorted_ll_test();
int Cmp_Num(const void *cur, const void *par);
static int PrintInt(void *data,void *param);
static int FindMatchInt(const void * data, const void *param);

int main()
{
	sorted_ll_test();

	return 0;
}

static void sorted_ll_test()
{
	int arr[] = {8, 2, 3, 4, 5, 6, 7, 8, 9, 10,
	11, 12, 13, 14, 15, 16, 49, 18, 19, 20,
	21, 22, 23, 24, 25, 26, 27, 28, 6, 5, 5};

	/*int arr2[] = {10000000, 10000000, 10000000, 10000000, 10000000, 10000000, 10000000, 10000000, 10000000};*/
	int arr2[] = {415613, 415613, -1, 415613, -2, 415613, 415613, 415613, 415613};
	int dum_num = 111541;
	/*
	int num_ten = 10;
	size_t counter = 0;
	*/size_t status = 0;/*	
	void *data = NULL;
	*/

	sorted_list_iter_t iter1 = {0};
	sorted_list_iter_t iter2 = {0};	
	size_t i = 0;
	sorted_list_t *sorted_list = SortedLLCreate(Cmp_Num);
	sorted_list_t *sorted_list2 = SortedLLCreate(Cmp_Num);	
	
	if (!SortedLLIsEmpty(sorted_list))
	{
		printf("Test failed at SortedLLIsEmpty!\n");
	}

	if (0 != SortedLLSize(sorted_list))
	{
		printf("Test failed at SotedLLSize!\n");
	}
	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		iter1 = SortedLLInsert(sorted_list, (arr + i));
		
		if (SortedLLIsSameIter(SortedLLEnd(sorted_list), iter1))
		{
			printf("Insertion failed at iteretion #%ld!\n", i + 1);
		}
	}



	/*SortedLLForEach(SortedLLBegin(sorted_list), SortedLLEnd(sorted_list), PrintInt, NULL);	
	printf("\n");
*/
	iter2 = SortedLLFindIf(SortedLLBegin(sorted_list), SortedLLEnd(sorted_list), FindMatchInt, (const void *)&dum_num);
	
	if (!SortedLLIsSameIter(SortedLLEnd(sorted_list), iter2))
	{
		printf("findif fail test didnt go to end!\n");	
	}

	iter1 = SortedLLInsert(sorted_list, &dum_num);
	
	iter2 = SortedLLFindIf(SortedLLBegin(sorted_list), SortedLLEnd(sorted_list), FindMatchInt, (const void *)&dum_num);
	
	if (SortedLLIsSameIter(SortedLLEnd(sorted_list), iter2))
	{
		printf("findif fail test go to end!\n");	
	}


	for (i = 0; i < TIMES_TO_LOOP; ++i)
	{
		iter1 = SortedLLInsert(sorted_list2, (arr2 + i));
	}

	if (TIMES_TO_LOOP + 1 != SortedLLSize(sorted_list))
	{
		printf("sorted_list Test failed at SotedLLSize! actual: %ld.\n", SortedLLSize(sorted_list));
		SortedLLForEach(SortedLLBegin(sorted_list), SortedLLEnd(sorted_list), PrintInt, NULL);
	}	

	if (TIMES_TO_LOOP != SortedLLSize(sorted_list2))
	{
		printf("sorted_list2 Test failed at SotedLLSize! actual: %ld.\n", SortedLLSize(sorted_list));
		SortedLLForEach(SortedLLBegin(sorted_list2), SortedLLEnd(sorted_list2), PrintInt, NULL);		
	}	
	/*SortedLLForEach(SortedLLBegin(sorted_list), SortedLLEnd(sorted_list), PrintInt, NULL);
	printf("\n");
	SortedLLForEach(SortedLLBegin(sorted_list2), SortedLLEnd(sorted_list2), PrintInt, NULL);	
	printf("\n");	
	printf("list1 Num Of members before splice: %ld\n", SortedLLSize(sorted_list));
	printf("list2 Num Of members before splice: %ld\n", SortedLLSize(sorted_list2));
	*/
	status = SortedLLSize(sorted_list) + SortedLLSize(sorted_list2);
	
	SortedLLMerge(sorted_list, sorted_list2);
	/*
	printf("list1 Num Of members before splice: %ld\n", SortedLLSize(sorted_list));
	printf("list2 Num Of members before splice: %ld\n", SortedLLSize(sorted_list2));
	SortedLLForEach(SortedLLBegin(sorted_list), SortedLLEnd(sorted_list), PrintInt, NULL);
	printf("\n");
	SortedLLForEach(SortedLLBegin(sorted_list2), SortedLLEnd(sorted_list2), PrintInt, NULL);	
	printf("\n");		
	*/
	
	if (SortedLLSize(sorted_list) + SortedLLSize(sorted_list2) != status)
	{
		printf("SortedLLMerge didn't move all elements! old size: %ld, new size: %ld.\n", status, SortedLLSize(sorted_list) + SortedLLSize(sorted_list2));
	}
	
	SortedLLDestroy(sorted_list);
	SortedLLDestroy(sorted_list2);
	
	return;
}

int Cmp_Num(const void *cur, const void *par)
{
	return (*(int*)cur - *(int*)par);
}


static int PrintInt(void *data,void *param)
{
    (void)param;

    printf("%d ", *(int *)data);

    return 0; 
}

static int FindMatchInt(const void * data, const void *param)
{
	return (*(int *)data >= *(int *)param);
}
