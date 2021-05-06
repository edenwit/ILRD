#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <limits.h> /* max_int */

#define BIG_ARR_SIZE 10000000

int FindNumInArrWithoutIfs(int *arr, size_t arr_size, int num);
static void FindNumInArrWithoutIfsTest();

int main()
{
	FindNumInArrWithoutIfsTest();

	return 0;
}

int FindNumInArrWithoutIfs(int *arr, size_t arr_size, int num)
{
	int found = 1;
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
		found = found * (!!(arr[i] ^ num));
	}	

	return (found == 0);
}

static void FindNumInArrWithoutIfsTest()
{
	int int_arr[] = {1, 5, 14, 64564, 85, 9, 15, 3, 40000, 0, -50};
	int int_arr2[BIG_ARR_SIZE] = {0};	
	size_t i = 0;
	size_t arr_size = sizeof(int_arr) / sizeof(int_arr[0]);
	int searched = 9;
	int status = 0;
	
	status = FindNumInArrWithoutIfs(int_arr, arr_size, searched);
	
	if (!status)
	{
		printf("Failed finding %d in arr. \n", searched);
	}

	searched = 200;
	status = FindNumInArrWithoutIfs(int_arr, arr_size, searched);
		
	if (status)
	{
		printf("Failed finding %d in arr. \n", searched);
	}
	
	for (i = 0; i < BIG_ARR_SIZE ; ++i)
	{
		int_arr2[i] = INT_MAX;
	}
	
	status = FindNumInArrWithoutIfs(int_arr2, BIG_ARR_SIZE, searched);
	
	if (status)
	{
		printf("Failed finding %d in arr. \n", searched);
	}
	
	searched = INT_MAX;	
	status = FindNumInArrWithoutIfs(int_arr2, BIG_ARR_SIZE, searched);
	
	if (!status)
	{
		printf("Failed finding %d in arr. \n", searched);
	}			

	searched = 15;	
	status = FindNumInArrWithoutIfs(int_arr2, BIG_ARR_SIZE, searched);
	
	if (status)
	{
		printf("Failed finding %d in arr. \n", searched);
	}
	
	searched = 0;	
	status = FindNumInArrWithoutIfs(int_arr2, BIG_ARR_SIZE, searched);
	
	if (status)
	{
		printf("Failed finding %d in arr. \n", searched);
	}
	
	searched = INT_MIN;	
	status = FindNumInArrWithoutIfs(int_arr2, BIG_ARR_SIZE, searched);
	
	if (status)
	{
		printf("Failed finding %d in arr. \n", searched);
	}
			
		
	return;
}

