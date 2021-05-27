#include <stdio.h>
#include <stddef.h> /* size_t */
#include "sorts.h"
#include <stdlib.h>
#include <time.h>

#define RANGE_FROM (0)
#define RANGE_TO   (1000)
#define ARR_SIZE (5000)

static int cmpfunc(const void * a, const void * b);
static void PrintIntArr(int * arr, size_t arr_size);
static int CompareArrs(int * arr1, int *arr2, size_t arr_size);
static void CopyArr(int * dest, int *src, size_t arr_size);
static unsigned int GetLeftMostBit(int num);
static unsigned int GetNDigits(int num);
static void SortsTest(int from, int to, int is_rand);

int main()
{
	printf("Unsorted Array:\n");
	SortsTest(RANGE_FROM, RANGE_TO, 1);
	printf("\nSorted Array:\n");
	SortsTest(RANGE_FROM, RANGE_TO, 0);
	
	return (0);
}

static void SortsTest(int from, int to, int is_rand)
{
	int arr[ARR_SIZE] = {0};
	int res_arr[ARR_SIZE] = {0};
	int exp_arr[ARR_SIZE] = {0};	
	size_t i = 0;
	clock_t start_time = 0;
	clock_t time_duration = 0;
	
	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = (rand() % (to - from + 1)) + from;
	}
	if (!is_rand)
	{
		qsort(arr, ARR_SIZE, sizeof(int), cmpfunc);
	}

	printf("Testing Sorts with array size %d:\n", ARR_SIZE);
	
	CopyArr(res_arr, arr, ARR_SIZE);
	CopyArr(exp_arr, arr, ARR_SIZE);

	start_time = clock();				
	BubbleSort(res_arr, ARR_SIZE);
	time_duration = clock() - start_time;	
	
	qsort(exp_arr, ARR_SIZE, sizeof(int), cmpfunc);

	if (CompareArrs(res_arr, exp_arr, ARR_SIZE))
	{
		printf("BubbleSort Comparing failed!.\n");
		PrintIntArr(arr, ARR_SIZE);				
		PrintIntArr(res_arr, ARR_SIZE);
		PrintIntArr(exp_arr, ARR_SIZE);
	}
	else
	{
		printf("BubbleSort Time:    %ld\n", time_duration);
	}
	
	CopyArr(res_arr, arr, ARR_SIZE);
	CopyArr(exp_arr, arr, ARR_SIZE);

	start_time = clock();				
	InsertionSort(res_arr, ARR_SIZE);
	time_duration = clock() - start_time;
		
	qsort(exp_arr, ARR_SIZE, sizeof(int), cmpfunc);

	if (CompareArrs(res_arr, exp_arr, ARR_SIZE))
	{
		printf("InsertionSort Comparing failed!.\n");
		PrintIntArr(arr, ARR_SIZE);				
		PrintIntArr(res_arr, ARR_SIZE);
		PrintIntArr(exp_arr, ARR_SIZE);
	}
	else
	{
		printf("InsertionSort Time: %ld\n", time_duration);
	}
		
	CopyArr(res_arr, arr, ARR_SIZE);
	CopyArr(exp_arr, arr, ARR_SIZE);
		
	start_time = clock();				
	SelectionSort(res_arr, ARR_SIZE);
	time_duration = clock() - start_time;
		
	qsort(exp_arr, ARR_SIZE, sizeof(int), cmpfunc);

	if (CompareArrs(res_arr, exp_arr, ARR_SIZE))
	{
		printf("SelectionSort Comparing failed!.\n");
		PrintIntArr(arr, ARR_SIZE);				
		PrintIntArr(res_arr, ARR_SIZE);
		PrintIntArr(exp_arr, ARR_SIZE);
	}
	else
	{
		printf("SelectionSort Time: %ld\n", time_duration);
	}	

	CopyArr(res_arr, arr, ARR_SIZE);
	CopyArr(exp_arr, arr, ARR_SIZE);

	start_time = clock();		
	CountSort(res_arr, ARR_SIZE);
	time_duration = clock() - start_time;	
		
	qsort(exp_arr, ARR_SIZE, sizeof(int), cmpfunc);

	if (CompareArrs(res_arr, exp_arr, ARR_SIZE))
	{
		printf("CountSort Comparing failed!.\n");
		PrintIntArr(arr, ARR_SIZE);				
		PrintIntArr(res_arr, ARR_SIZE);
		PrintIntArr(exp_arr, ARR_SIZE);
	}
	else
	{
		printf("CountSort Time:     %ld\n", time_duration);
	}
	
	CopyArr(res_arr, arr, ARR_SIZE);
	CopyArr(exp_arr, arr, ARR_SIZE);
		
	start_time = clock();
	RadixDigitsSort(res_arr, ARR_SIZE, GetNDigits((int)RANGE_TO));
	time_duration = clock() - start_time;
		
	qsort(exp_arr, ARR_SIZE, sizeof(int), cmpfunc);

	if (CompareArrs(res_arr, exp_arr, ARR_SIZE))
	{
		printf("RadixDigitsSort Comparing failed!.\n");
		PrintIntArr(arr, ARR_SIZE);				
		PrintIntArr(res_arr, ARR_SIZE);
		PrintIntArr(exp_arr, ARR_SIZE);
	}
	else
	{
		printf("RadixDigitsSort Time: %ld\n", time_duration);
	}
		
	CopyArr(res_arr, arr, ARR_SIZE);
	CopyArr(exp_arr, arr, ARR_SIZE);
	start_time = clock();
	RadixBitsSort(res_arr, ARR_SIZE, GetLeftMostBit((int)RANGE_TO));
	time_duration = clock() - start_time;

	qsort(exp_arr, ARR_SIZE, sizeof(int), cmpfunc);

	if (CompareArrs(res_arr, exp_arr, ARR_SIZE))
	{
		printf("RadixBitsSort Comparing failed!.\n");
		PrintIntArr(arr, ARR_SIZE);				
		PrintIntArr(res_arr, ARR_SIZE);
		PrintIntArr(exp_arr, ARR_SIZE);
	}
	else
	{
		printf("RadixBitsSort Time: %ld\n", time_duration);
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

static unsigned int GetLeftMostBit(int num)
{
	size_t max_left = 0;
	
	while (0 != num)
	{	
		++max_left;
		num >>= 1;
	}
	
	return (max_left);
}

static unsigned int GetNDigits(int num)
{
	size_t num_of_digits = 0;
	
	while (0 != num)
	{
		++num_of_digits;
		num /= 10;
	}
	
	return (num_of_digits);
}


