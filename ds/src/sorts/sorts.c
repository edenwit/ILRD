/*  Developer: Eden Wittenberg;									*
 *  Status: done;												*
 *  Date Of Creation: 26.05.21;									*
 *  Date Of Approval:											*
 *  Approved By: ;												*
 *  Description: Sorts							;				*/


#include <stddef.h> /* size_t */
#include <assert.h>  /* assert */
#include <stdlib.h> /* malloc */
#include "sorts.h" /* qsort */
#include <string.h> /* memcpy */

#define DEC_BASE (10)
#define BIN_BASE (2)
#define MAX2(a, b)  ((a) > (b) ? (a) : (b))
#define MIN2(a, b)  ((a) < (b) ? (a) : (b))
#define UNUSED(X) (void)(X)

static void Swap(int *x, int *y);

static int GenericCountSort(int arr[], size_t size, size_t range, size_t base, int min, int (*index_func)(int num, size_t base));

static int IndexForCount(int num, size_t base);
static int IndexForRadixDigit(int num, size_t base);
static int IndexForRadixBit(int num, size_t base);

void BubbleSort(int arr[], size_t size)
{
    int *p1 = NULL;
    int *p2 = NULL;
    int run_again = 1;
    size_t i = 0;
    
    assert(arr);
       
    if (2 > size)
    {
    	return;
    }
    
    while (1 == run_again)
    {
    	run_again = 0;
    	
   		p1 = arr;
   		p2 = p1 + 1;
    	
    	for (i = 0; i < (size - 1); ++i)
    	{  		
    		if (*p1 > *p2)
    		{
    			run_again = 1;
    			Swap(p1, p2);
    		}
    		
    		++p1;
    		++p2;    		
    	} 
	}
	
    return;
}

void InsertionSort(int arr[], size_t size)
{
    int *p1 = arr + 1;
    int *p2 = NULL;
    int value = 0;
    
    assert(arr);
       
    if (2 > size)
    {
    	return;
    }
    
    while (p1 < (arr + size))
    {
   		p2 = p1 - 1;
   		value = *p1;   		
    	
		while ((*p2 > value) && (p2 >= arr)) 
		{
            *(p2 + 1) = *p2;
            --p2;
        }
        
        *(p2 + 1) = value;
        ++p1;
	}
	
    return;
}

void SelectionSort(int arr[], size_t size)
{
    int *p1 = arr;
    int *p2 = NULL;
    int *saved_p = NULL;
    
    assert(arr);
       
    if (2 > size)
    {
    	return;
    }
    
    while (p1 < (arr + size))
    {
   		p2 = p1 + 1;
		saved_p = p1;

		while ((p2 < (arr + size))) 
		{
            if (*p2 < *saved_p)
            {
            	saved_p = p2;
            }
            ++p2;
        }
        
        Swap(saved_p, p1);
        ++p1;
	}
	
    return;
}

static int GenericCountSort(int arr[], size_t size, size_t range, size_t base, int min, int (*index_func)(int num, size_t base))
{
	int *count_arr = NULL;
	int *res_arr = NULL;
	size_t i = 0;
	size_t digit = 0;
	
	assert(arr);

   	count_arr = (int *)calloc((range), sizeof(int));
   	
   	if (NULL == count_arr)
   	{
   		return (1);
   	}
	
   	res_arr = (int *)malloc((size) * sizeof(int));
   	
   	if (NULL == res_arr)
   	{
   		free(count_arr);
   		
   		return (1);
   	}

	for (i = 0; i < size; ++i)
	{
		++count_arr[index_func(arr[i], base) - min];
	}

	for (i = 1; i < range; ++i)
	{
		count_arr[i] += count_arr[i - 1];
	}

    for (i = size; i > 0; --i) 
    {				    
    	digit = index_func(arr[i - 1], base);
        res_arr[count_arr[digit - min] - 1] = arr[i - 1];
        --count_arr[digit - min];
    }

    memcpy(arr, res_arr, size * sizeof(int)); 		  
    
	free(count_arr);
	free(res_arr);

	return (0);
}

int CountSort(int arr[], size_t size)
{
	int min = arr[0];
	int max = arr[0];
	size_t i = 0;
	size_t range = 0;
	
	assert(arr);
		
    for (i = 0; i < size; ++i)
    {  		
		min = MIN2(min, *(arr + i));
		max = MAX2(max, *(arr + i));    		
   	} 
 
 	range = (max - min + 1);
 
 	return (GenericCountSort(arr, size, range, 1, min, IndexForCount));
}

int RadixDigitsSort(int arr[], size_t size, size_t n_digits)
{
	int *res_arr = NULL;
	size_t base = 1;
	size_t i = 0;
			
	assert(arr);

   	res_arr = (int *)malloc((size) * sizeof(int));

	if (NULL == res_arr)
	{
		return (1);
	}
	/* allocate copy arr, if fails do not damage original */	
    memcpy(res_arr, arr, size * sizeof(int)); 		
    
	for (i = 1; i <= n_digits; ++i)
    {  		
  		if (GenericCountSort(res_arr, size, DEC_BASE, base, 0, IndexForRadixDigit))
  		{
  			return (1);
  		}
  		
  		base *= DEC_BASE;	
   	} 
 	/* copy back to original arr */	
    memcpy(arr, res_arr, size * sizeof(int)); 		
    
	free(res_arr);
	
	return (0);
}

int RadixBitsSort(int arr[], size_t size, size_t n_bits)
{
	size_t i = 0;
	int *res_arr = NULL;
		
	assert(arr);

   	res_arr = (int *)malloc((size) * sizeof(int));

	if (NULL == res_arr)
	{
		return (1);
	}
		
	/* allocate copy arr, if fails do not damage original */	
    memcpy(res_arr, arr, size * sizeof(int)); 		
		
	for (i = 0; i < n_bits; ++i)
    {  	
  		if (GenericCountSort(res_arr, size, BIN_BASE, i, 0, IndexForRadixBit))
  		{
  			return (1);
  		}
   	} 
 	
	/* copy back to original arr */
    memcpy(arr, res_arr, size * sizeof(int));
    
	free(res_arr);
	
	return (0);
}

static void Swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
    
    return;
}

static int IndexForCount(int num, size_t base)
{
	UNUSED(base);

	return (num);
}

static int IndexForRadixDigit(int num, size_t base)
{
	return ((num / base) % DEC_BASE);
}

static int IndexForRadixBit(int num, size_t base)
{
	return ((num >> base) & 1);
}
