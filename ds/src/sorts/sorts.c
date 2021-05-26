
#include <stddef.h> /* size_t */
#include <assert.h> 
#include <stdlib.h> /* malloc */


#include "sorts.h"


#define MAX2(a, b)  ((a) > (b) ? (a) : (b))
#define MIN2(a, b)  ((a) < (b) ? (a) : (b))

static void swap(int *x, int *y);

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
    int min = 0;
    
    assert(arr);
       
    if (2 > size)
    {
    	return;
    }
    
    while (p1 < (arr + size))
    {
   		p2 = p1 + 1;
    	min = *p1;
		saved_p = p1;

		while ((p2 < (arr + size))) 
		{
            if (*p2 < min)
            {
            	min = *p2;
            	saved_p = p2;
            }
            ++p2;
        }
        
        swap(saved_p, p1);
        ++p1;
	}
	
    return;
}

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
    			swap(p1, p2);
    		}
    		++p1;
    		++p2;    		
    	} 
	}
	
    return;
}


int CountSort(int arr[], size_t size)
{
	int *count_arr = NULL;
	int *res_arr = NULL;
	int mini = arr[0];
	int maxi = arr[0];
	size_t i = 0;
	size_t count_arr_size = 0;
	
	assert(arr);
	
    for (i = 0; i < size; ++i)
    {  		
		mini = MIN2(mini, *(arr + i));
		maxi = MAX2(maxi, *(arr + i));    		
   	} 
   	
 	
   	count_arr_size = maxi - mini + 1;
   	
   	count_arr = (int *)calloc((count_arr_size), sizeof(int));
   	
   	if (NULL == count_arr)
   	{
   		return (0);
   	}

   	res_arr = (int *)calloc((size), sizeof(int));
   	
   	if (NULL == res_arr)
   	{
   		free(count_arr);
   		
   		return (0);
   	}
	
	for (i = 0; i < size; ++i)
	{

		++count_arr[arr[i] - mini];

	}
	

	for (i = 1; i < count_arr_size; ++i)
	{
		count_arr[i] += count_arr[i - 1];
	}


    for (i = size; i > 0; --i) 
    {
        res_arr[count_arr[arr[i - 1] - mini] - 1] = arr[i - 1];
        count_arr[arr[i - 1] - mini] -= 1;
    }

    for (i = 0; i < size; ++i)
    {
		*(arr + i) = *(res_arr + i);   
    }

	free(count_arr);
	free(res_arr);

	return (1);
}

int RadixDigitsSort(int arr[], size_t size, size_t n_digits);

int RadixBitsSort(int arr[], size_t size, size_t n_bits);

static void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
    
    return;
}
 

