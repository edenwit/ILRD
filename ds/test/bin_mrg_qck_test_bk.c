#include "bin_mrg_qck.h"
#include <stddef.h> /* size_t */
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define RANGE_FROM (-5000)
#define RANGE_TO   (100000)
#define ARR_SIZE (1000000)

static void IterBinSearchTest();
static void RecBinSearchTest();

static void MergeSortTest();

static void PrintIntArr(int * arr, size_t arr_size);
static int CompareArrs(int * arr1, int *arr2, size_t arr_size);
static void CopyArr(int *dest, int *src, size_t arr_size);
static int cmpfunc(const void * a, const void * b);

int main()
{
	IterBinSearchTest();

	RecBinSearchTest();

	MergeSortTest();

	return (0);
}

static void IterBinSearchTest()
{
	int test_arr[] = 		{1, 2, 4, 7, 9, 11, 20, 31, 42, 50, 67, 71, 80, 100, 201};
	int num_to_search[] = 	{-85, 1, 2, 3, 7, 11, 20, 32, 41, 51, 66, 67, 100, 201};
	int exp_res[] =			{1, 0, 0, 1, 0, 0,  0,  1,  1,  1,  1,  0,   0,   0};
	size_t index_ptr = 0;
	size_t exp_arr[] = 	{0, 0, 1, 0, 3, 5, 	 5,  0,  0,  0, 10,  0,  13,  14};
	size_t arr_size = sizeof(test_arr) / sizeof(test_arr[0]);
	size_t exp_arr_size = sizeof(exp_arr) / sizeof(exp_arr[0]);
	size_t i = 0;
	int res = 0;

	for (i = 0; i < exp_arr_size; ++i)
	{
		res = IterBinSearch(test_arr, arr_size, num_to_search[i], &index_ptr);

		if (exp_res[i] != res)
		{
			printf("#%ld: failed send %d, int val. expected: %d, actual: %d!\n", i + 1, num_to_search[i], exp_res[i], res);

			if (exp_arr[i] != index_ptr)
			{
				printf("failed at index val!\n");
			}

		}

	}

	return;
}

static void RecBinSearchTest()
{
	int test_arr[] = 		{1, 2, 4, 7, 9, 11, 20, 31, 42, 50, 67, 71, 80, 100, 201};
	int num_to_search[] = 	{-85, 1, 2, 3, 7, 11, 20, 32, 41, 51, 66, 67, 100, 201};
	int exp_res[] =			{1, 0, 0, 1, 0, 0,   0,  1,  1,  1,  1,  0,   0,   0};
	size_t index_ptr = 0;
	size_t exp_arr[] = 	{0, 0, 1, 0, 3, 5, 	 5,  0,  0,  0, 10,  0,  13,  14};
	size_t arr_size = sizeof(test_arr) / sizeof(test_arr[0]);
	size_t exp_arr_size = sizeof(exp_arr) / sizeof(exp_arr[0]);
	size_t i = 0;

	int res = 0;

	for (i = 0; i < exp_arr_size; ++i)
	{
		res = RecBinSearch(test_arr, arr_size, num_to_search[i], &index_ptr);

		if (exp_res[i] != res)
		{
			printf("#%ld: failed send %d, int val. expected: %d, actual: %d!\n", i + 1, num_to_search[i], exp_res[i], res);

			if (exp_arr[i] != index_ptr)
			{
				printf("failed at index val!\n");
			}

		}

	}

	return;
}

static void MergeSortTest()
{
	int arr[ARR_SIZE] = {0};
	int res_arr[ARR_SIZE] = {0};
	int exp_arr[ARR_SIZE] = {0};	
	size_t i = 0;
	clock_t start_time = 0;
	clock_t time_duration = 0;
	
	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = (rand() % (RANGE_TO - RANGE_FROM + 1)) + RANGE_FROM;
	}
	/*
	qsort(arr, ARR_SIZE, sizeof(int), cmpfunc);		
*/
	printf("Testing Sorts with array size %d:\n", ARR_SIZE);
	
	CopyArr(res_arr, arr, ARR_SIZE);
	CopyArr(exp_arr, arr, ARR_SIZE);

	start_time = clock();				
	MergeSort(res_arr, ARR_SIZE);
	time_duration = clock() - start_time;	
	
	qsort(exp_arr, ARR_SIZE, sizeof(int), cmpfunc);

	if (CompareArrs(res_arr, exp_arr, ARR_SIZE))
	{
		printf("MergeSort Comparing failed!.\n");
		PrintIntArr(arr, ARR_SIZE);				
		PrintIntArr(res_arr, ARR_SIZE);
		PrintIntArr(exp_arr, ARR_SIZE);
	}
	else
	{
		printf("MergeSort Time:    %ld\n", time_duration);
	}
		
	return;
}


static void PrintIntArr(int * arr, size_t arr_size)
{
	size_t i = 0;

	printf("\n");

	for (i = 0; i < arr_size; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n\n");
		
	return;
}

static void CopyArr(int * dest, int *src, size_t arr_size)
{
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		dest[i] = src[i];
	}
		
	return;
}

static int CompareArrs(int * arr1, int *arr2, size_t arr_size)
{
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		if (arr1[i] != arr2[i])
		{
			return (1);
		}
	}
		
	return (0);
}


static int cmpfunc(const void * a, const void * b)
{
   return ( *(int *)a - *(int *)b );
}

