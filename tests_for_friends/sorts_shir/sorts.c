#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "sorts.h"

static int GenericFunc(int *arr, size_t arr_size, size_t lut_size, 
						size_t range, int operator_base, 
						int (*action_func)(int *arr, int operator_base, 
						int i, int base_devision));
						
static int GetCountIndex(int *arr, int operator_base, int i, int base_devision);
static int GetRadixIndex(int *arr, int operator_base, int i, int base_devision);
static int GetRadixBitsIndex(int *arr, int operator_base, int i, int base_devision);

#define COUNT 1
#define BASE 10
#define UNUSED (void)

void BubbleSort(int arr[], size_t size)
{
	size_t i = 0;
	size_t counter = 1;
	int tmp = 0;
	
	while(0 != counter)
	{
		counter = 0;
		
		for(i = 0; i < size - 1; ++i)
		{
			if (arr[i] > arr[i + 1])
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				
				++counter;
			}
		}
	}
	
	return;
}


void SelectionSort(int arr[], size_t size)
{
	size_t i = 0;
	size_t j = 0;
	size_t min_index = 0;
	int min = 0;
	int tmp = 0;
	
	for(i = 0; i < size - 1; ++i)
	{
		min = INT_MAX;
		for(j = i; j < size; ++j)
		{
			if(min > arr[j])
			{
				min = arr[j];
				min_index = j;
			}
		}
		tmp = arr[i];
		arr[i] = min;
		arr[min_index] = tmp;
	}
	
	return;
}


void InsertionSort(int arr[], size_t size)
{
	size_t i = 1;
	int j = 0;
	int tmp = 0;
	
	for(i = 1; i < size; ++i)
	{
		if(arr[i - 1] > arr [i])
		{
			tmp = arr[i];
			
			for(j = i - 1; j >= 0; --j)
			{
				if(arr[j] > tmp)
				{
					arr[j + 1] = arr[j];
				}
				else
				{
					break;
				}
			}
			
			arr[j + 1] = tmp;
		}
	}
	
	return;
}


int CountSort(int arr[], size_t size)
{
	int i = 0;
	size_t lut_size = 0;
	int min = INT_MAX;
	int max = INT_MIN;
	size_t range = 1;
	
	for(i = 0; i < (int)size; ++i)
	{
		if (min > arr[i])
		{
			min = arr[i];
		}
		
		if (max < arr[i])
		{
			max = arr[i];
		}
    }
    
    lut_size = max - min + 1;
    
    if (1 == GenericFunc(arr, size, lut_size, range, min, GetCountIndex))
    {
    	return 1;
    }
    
    return 0;
}


int RadixDigitsSort(int arr[], size_t size, size_t n_digits)
{
	size_t lut_size = 10;
	size_t base = 10;
	
	if (1 == GenericFunc(arr, size, lut_size, n_digits, base, GetRadixIndex))
    {
    	return 1;
    }
	
	return 0;
}


int RadixBitsSort(int arr[], size_t size, size_t n_bits)
{
	size_t lut_size = 2;
	int operator_base = 1; /* unused in this function */
	
	if(GenericFunc(arr, size, lut_size, n_bits, operator_base, GetRadixBitsIndex))
	{
		return 1;
	}
	
	return 0;
	
}



static int GenericFunc(int *arr, size_t arr_size, size_t lut_size, 
						size_t range, int operator_base, int (*action_func)
						(int *arr, int operator_base, int i, int base_devision))
{
	int *lut = NULL;
	int *sorted_arr = NULL;
	int sorted_index = 0;
	int i = 0; 
	int base_devision = 1;
	
	lut = (int *)calloc(lut_size, sizeof(int));
    
    if(NULL == lut)
    {
    	return 1;
    }
    
    sorted_arr = (int *)malloc(sizeof(int) * arr_size);
	
	if(NULL == sorted_arr)
    {
    	return 1;
    }
    
    while(0 < range)
    {
    	for(i = 0; i < (int)lut_size; ++i)
		{
			lut[i] = 0;
		}
    	
    	/* fill lut with counter for each num in arr */
		for(i = 0; (size_t)i < arr_size; ++i)
		{
			++lut[action_func(arr, operator_base, i, base_devision)];
		}
		
		/* merge counters to form the last index of each number in lut */
		for(i = 1; (size_t)i < lut_size; ++i)
		{
			lut[i] = lut[i] + lut [i - 1];
		}
		
		/* Get the index from lut and put val in new array */
		for(i = arr_size - 1; i >= 0; --i)
		{
			sorted_index = lut[action_func(arr, operator_base, i, 
								 base_devision)] - 1;
			sorted_arr[sorted_index] = arr[i];
			--lut[action_func(arr, operator_base, i, base_devision)];
		}
		
		/* Copy sorted array to original array */
		for(i = 0; (size_t)i < arr_size; ++i)
		{
			arr[i] = sorted_arr[i];
		}
		
		operator_base *= lut_size;
		base_devision *= lut_size;
		--range;
    }
    	
	free(lut);
	free(sorted_arr);
	
	return 0;
}

static int GetCountIndex(int *arr, int operator_base, int i, int base_devision)
{
	UNUSED base_devision;
	
	return(arr[i] - operator_base);
}


static int GetRadixIndex(int *arr, int operator_base, int i, int base_devision)
{
	return((arr[i] % operator_base)/base_devision);
}


static int GetRadixBitsIndex(int *arr, int operator_base, int i, int base_devision)
{
	UNUSED operator_base;
	UNUSED base_devision;
	
	return !!(arr[i] & operator_base);
}










