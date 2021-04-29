#include <stdio.h> /* printf */

#include "sorted_ll.h"

#define TIMES_TO_LOOP 30



static void sorted_ll_test();
int Cmp_Num(const void *cur, const void *par);
static int PrintInt(void *data,void *param);

int main()
{
	sorted_ll_test();

	return 0;
}

static void sorted_ll_test()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
	11, 12, 13, 14, 15, 16, 49, 18, 19, 20,
	21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 10000};
	/*
	int num_ten = 10;
	int dum_num = 541;
	size_t counter = 0;
	size_t status = 0;	
	void *data = NULL;
*/
	sorted_list_iter_t iter1 = {0};
	size_t i = 0;
	sorted_list_t *sorted_list = SortedLLCreate(Cmp_Num);
	
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
	}
	if (30 != SortedLLSize(sorted_list))
	{
		printf("Test failed at SotedLLSize!\n");
	}	

	SortedLLForEach(SortedLLBegin(sorted_list), SortedLLEnd(sorted_list), PrintInt, NULL);
	
	SortedLLDestroy(sorted_list);
	
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
