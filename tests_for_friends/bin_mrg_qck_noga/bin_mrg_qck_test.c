#include <stdio.h> /* printf */
#include <stdlib.h> /* time_t, rand */
#include <assert.h> /* assert */
#include <time.h> /* clock */

#include "bin_mrg_qck.h"

#define SIZE (1000000)
#define RANGE_RANDOM (100000)
#define NEGETIVE_RANGE_RANDOM (-50000)

#define RANGE_FROM (NEGETIVE_RANGE_RANDOM)
#define RANGE_TO (NEGETIVE_RANGE_RANDOM + RANGE_RANDOM)


static int Compare(const void * data1, const void * data2);
static int *CreateRandomArray(size_t size, int range);
static int *CopyArray(int *arr, size_t size);
static int IsEqual(int *arr, int *other, size_t size);
static void PrintArray(int *arr, size_t size);

static void TestIterBinSearch();
static void TestRecBinSearch();
static void TestIterBinSearch1();
static void TestRecBinSearch1();
static void TestMergeSort();
static void TestRecQsort();


int main()
{
    TestIterBinSearch();
    TestIterBinSearch1(); 
    TestRecBinSearch();
    TestRecBinSearch1();
    TestMergeSort();
    TestRecQsort();

    return (0);
}

static void TestIterBinSearch()
{
    int arr[] = {-4, 6, 7, 10, 12, 13};
    int arr_val[] = {10, 15, 2, 3, 6, -4, -5, 13};
    int arr_index_exp[] = {3, -1, -1, -1, 1, 0, -1, 5};
    int status[] = {0, 1, 1, 1, 0, 0, 1, 0};
    int status_returned = -1;

    size_t size_to_send = sizeof(arr) / sizeof(arr[0]);

    size_t size = sizeof(arr_val) / sizeof(arr_val[0]);
    size_t return_index = 0;
    size_t i = 0;

    while (0 < size)
    {
        status_returned = IterBinSearch(arr, size_to_send, arr_val[i], &return_index);
        if ((status_returned != status[i] && return_index != (size_t)arr_index_exp[i]))
        {
            printf("Test RecBinSearch failed at line %d and at index %lu\n", __LINE__, i);
            printf("expected status %d\n", status[i]);
            printf("returned status %d\n", status_returned);

            printf("index returned %ld\n", return_index);
            printf("index expected %d\n", arr_index_exp[i]);
        }
        --size;
        ++i;
    }

    return;
}

static void TestIterBinSearch1()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 9, 10, 15, 20, 54, 56, 57, 80, 100, 108};
    int to_search[] = {6, 3, 2, 15, 56, 80, 10, 54, 108};
    size_t exp[] = {5, 2, 1, 9, 12, 14, 8, 11, 16};

    size_t size_to_send = sizeof(arr) / sizeof(arr[0]);

    size_t size = sizeof(to_search) / sizeof(to_search[0]);
    size_t return_index = 0;
    size_t i = 0;

    while (0 < size)
    {
        IterBinSearch(arr, size_to_send, to_search[i], &return_index);
        if (return_index != (size_t)exp[i])
        {
            printf("Test TestIterBinSearch1 failed at line %d and at index %lu\n", __LINE__, i);
            printf("TestIterBinSearch1 index returned %ld\n", return_index);
            printf("index expected %ld\n", exp[i]);
        }
        --size;
        ++i;
    }

    return;

    return;
}

static void TestRecBinSearch()
{
    int arr[] = {-4, 6, 7, 10, 12, 13};
    int arr_val[] = {10, 15, 2, 3, 6, -4, -5, 13};
    int arr_index_exp[] = {3, -1, -1, -1, 1, 0, -1, 5};
    int status[] = {0, 1, 1, 1, 0, 0, 1, 0};
    int status_returned = -1;

    size_t size_to_send = sizeof(arr) / sizeof(arr[0]);

    size_t size = sizeof(arr_val) / sizeof(arr_val[0]);
    size_t return_index = 0;
    size_t i = 0;

    while (0 < size)
    {
        status_returned = RecBinSearch(arr, size_to_send, arr_val[i], &return_index);
        if ((status_returned != status[i] && return_index != (size_t)arr_index_exp[i]))
        {
            printf("Test RecBinSearch failed at line %d and at index %lu\n", __LINE__, i);
            printf("expected status %d\n", status[i]);
            printf("returned status %d\n", status_returned);

            printf("index returned %ld\n", return_index);
            printf("index expected %d\n", arr_index_exp[i]);
        }
        --size;
        ++i;
    }

    return;
}

static void TestRecBinSearch1()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 9, 10, 15, 20, 54, 56, 57, 80, 100, 108};
    int to_search[] = {6, 3, 2, 15, 56, 80, 10, 54, 108};
    size_t exp[] = {5, 2, 1, 9, 12, 14, 8, 11, 16};
    size_t size_to_send = sizeof(arr) / sizeof(arr[0]);

    size_t size = sizeof(to_search) / sizeof(to_search[0]);
    size_t return_index = 0;
    size_t i = 0;

    while (0 < size)
    {
        RecBinSearch(arr, size_to_send, to_search[i], &return_index);
        if (return_index != (size_t)exp[i])
        {
            printf("Test TestRecBinSearch1 failed at line %d and at index %lu\n", __LINE__, i);
            printf("TestRecBinSearch1 index returned %ld\n", return_index);
            printf("index expected %ld\n", exp[i]);
        }
        --size;
        ++i;
    }

    return;
}

static void TestMergeSort()
{
	clock_t start = 0;
	clock_t end = 0;
	double cpu_time = 0;
	
	int *actual = NULL;
	int *expected = NULL;
	
	size_t size = SIZE;
	
	actual = CreateRandomArray(size, RANGE_RANDOM);
	expected = CopyArray(actual, size);
	

	start = clock();
	
	MergeSort(actual, size);
	
	end = clock();
	
	cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
	
	printf("cpu time for sorted MergeSort algorithm: %f\n",cpu_time);
	
	qsort (expected, size, sizeof(int), Compare); 
	
	if (!IsEqual(actual, expected, size))
	{
		printf("MergeSort func failed at line: %d\n", __LINE__);
		printf("Actual result:\n");
		PrintArray(actual, size);
		printf("---------------------------------\n");
		printf("Expected result:\n");
		PrintArray(expected, size); 
	}
	
	free(actual);
	free(expected);
	
	return;	
}

static void TestRecQsort()
{
	clock_t start = 0;
	clock_t end = 0;
	double cpu_time = 0;
	
	int *actual = NULL;
	int *expected = NULL;
	
	size_t size = SIZE;
	
	actual = CreateRandomArray(size, RANGE_RANDOM);
	expected = CopyArray(actual, size);
	
	start = clock();
	
	RecQsort((void *)actual, size, sizeof(int), Compare);
	
	end = clock();
	
	cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
	
	printf("cpu time for sorted RecQsort algorithm: %f\n",cpu_time);
	
	qsort (expected, size, sizeof(int), Compare); 
	
	if (!IsEqual(actual, expected, size))
	{
		printf("RecQsort func failed at line: %d\n", __LINE__);
		printf("Actual result:\n");
		PrintArray(actual, size);
		printf("---------------------------------\n");
		printf("Expected result:\n");
		PrintArray(expected, size); 
	}
	
	free(actual);
	free(expected);
	
	return;	
}
/*
static void TestRecQsort()
{
	clock_t start = 0;
	clock_t end = 0;
	double cpu_time = 0;
	
	int *actual = NULL;
	int *expected = NULL;
	
	size_t size = SIZE;
	
	actual = CreateRandomArray(size, RANGE_RANDOM);
	expected = CopyArray(actual, size);
	
	qsort (expected, size, sizeof(int), Compare); 
	
	start = clock();
	
	RecQsort((void *)actual, size, sizeof(int), Compare);
	
	end = clock();
	
	cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
	
	printf("cpu time for sorted MergeSort algorithm: %f\n",cpu_time);
	
	qsort (expected, size, sizeof(int), Compare); 
	
	if (!IsEqual(actual, expected, size))
	{
		printf("RecQsort func failed at line: %d\n", __LINE__);
		printf("Actual result:\n");
		PrintArray(actual, size);
		printf("---------------------------------\n");
		printf("Expected result:\n");
		PrintArray(expected, size); 
	}
	
	free(actual);
	free(expected);
	
	return;	
}
*/

static int Compare(const void * data1, const void * data2)
{
	return (*(int*)data1 - *(int*)data2);
}

static int *CreateRandomArray(size_t size, int range)
{
	size_t i = 0;
   	time_t t = 0;

	int *new_arr = (int *)malloc(sizeof(int) * size);

	t =time(NULL);
	srand (time(&t));
	
	if (NULL == new_arr)
	{
		return NULL;
	}


	for (i = 0; i < size; i++)
	{	
    	new_arr[i] = (rand() % range - NEGETIVE_RANGE_RANDOM);
	}
	
	return new_arr;
}

static int IsEqual(int *arr1, int *arr2, size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (arr1[i] != arr2[i])
		{
			printf("arrays not eqval at line %d in index %lu\n", __LINE__, i);
						
			return (0);
		}
	}
	
	return (1);
}

static int *CopyArray(int *arr, size_t size)
{
	size_t i = 0;
	
	int *arr_copy = (int *)malloc(sizeof(int) * size);
	
	if (NULL == arr_copy)
	{
		return NULL;
	}
	
	for (i = 0; i < size; ++i)
	{
		arr_copy[i] = arr[i];
	}
	
	return (arr_copy);
}

static void PrintArray(int *arr, size_t size)
{	
	size_t i = 0;

	assert(NULL != arr);
	
	for (i = 0; i < size; ++i)
    {
    	printf ("%d\t",arr[i]);
    	
    	if (i % 20 == 0 && (i > 0))
    	{
    		printf("\n");
    	}
    }
    
    printf("\n");
    
    return;
}

