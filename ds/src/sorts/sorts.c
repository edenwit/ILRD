#include <stddef.h> /* size_t */
#include <assert.h> 
#include <stdlib.h> /* malloc */
#include "sorts.h"

#define DEC_BASE (10)
#define BIN_BASE (2)
#define MAX2(a, b)  ((a) > (b) ? (a) : (b))
#define MIN2(a, b)  ((a) < (b) ? (a) : (b))

static void Swap(int *x, int *y);
static int GetDigit(int num, int n);
int CountSortByDigit(int arr[], size_t size, size_t expo, size_t base);
static int GetBit(int num, int n);
int CountSortByBit(int arr[], size_t size, size_t bit_order);



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
        
        Swap(saved_p, p1);
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
    			Swap(p1, p2);
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
   		return (1);
   	}

   	res_arr = (int *)calloc((size), sizeof(int));
   	
   	if (NULL == res_arr)
   	{
   		free(count_arr);
   		
   		return (1);
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

	return (0);
}


int CountSortByDigit(int arr[], size_t size, size_t expo, size_t base)
{
	int *count_arr = NULL;
	int *res_arr = NULL;
	size_t i = 0;
	size_t digit = 0;
	
	assert(arr);

   	count_arr = (int *)calloc((base), sizeof(int));
   	
   	if (NULL == count_arr)
   	{
   		return (1);
   	}
	
   	res_arr = (int *)calloc((size), sizeof(int));
   	
   	if (NULL == res_arr)
   	{
   		free(count_arr);
   		
   		return (1);
   	}

	for (i = 0; i < size; ++i)
	{
		/*printf("From num %d taking digit %ld: %ld.\n", arr[i], digit_order, GetDigit(arr[i], digit_order));*/
		++count_arr[(arr[i] / expo) % base];
	}

	for (i = 1; i < base; ++i)
	{
		count_arr[i] += count_arr[i - 1];
	}

    for (i = size; i > 0; --i) 
    {				    
    	digit = (arr[i - 1] / expo) % base;
        res_arr[count_arr[digit] - 1] = arr[i - 1];
        --count_arr[digit];
    }

    for (i = 0; i < size; ++i)
    {
		*(arr + i) = *(res_arr + i);   
    }
    
	free(count_arr);
	free(res_arr);

	return (0);
}


int CountSortByBit(int arr[], size_t size, size_t bit_order)
{
	int count_arr[2] = {0};
	int *res_arr = NULL;
	size_t i = 0;
	
	assert(arr);
	
   	res_arr = (int *)calloc((size), sizeof(int));
   	
   	if (NULL == res_arr)
   	{
   		return (1);
   	}

	for (i = 0; i < size; ++i)
	{
		/*printf("From num %d taking digit %ld: %ld.\n", arr[i], digit_order, GetDigit(arr[i], digit_order));*/
		++count_arr[GetBit(arr[i], bit_order)];
	}

	count_arr[1] += count_arr[0];

    for (i = size; i > 0; --i) 
    {				    
        res_arr[count_arr[GetBit(arr[i - 1], bit_order)] - 1] = arr[i - 1];
        --count_arr[GetBit(arr[i - 1], bit_order)];
    }

    for (i = 0; i < size; ++i)
    {
		*(arr + i) = *(res_arr + i);   
    }

	free(res_arr);

	return (0);
}

int RadixDigitsSort(int arr[], size_t size, size_t n_digits)
{
	int *res_arr = NULL;
	size_t i = 0;

	assert(arr);
	
   	res_arr = (int *)malloc((size) * sizeof(int));

	if (NULL == res_arr)
	{
		return (1);
	}
	
	for (i = 0; i < size; ++i)
	{
		res_arr[i] = arr[i];
	}
	
	for (i = 1; i <= n_digits; ++i)
	{
		
		if (CountSortByDigit(res_arr, size, ((i - 1) * DEC_BASE), DEC_BASE))
		{
			return (1);
		}		
	}
	
	for (i = 0; i < size; ++i)
	{
		arr[i] = res_arr[i];
	}	
	
	free(res_arr);
	
	return (0);
}

int RadixBitsSort(int arr[], size_t size, size_t n_bits)
{
	int *res_arr = NULL;
	size_t i = 0;
	
	assert(arr);
	
   	res_arr = (int *)malloc((size) * sizeof(int));

	if (NULL == res_arr)
	{
		return (1);
	}
	
	for (i = 0; i < size; ++i)
	{
		res_arr[i] = arr[i];
	}
	
	for (i = 1; i <= n_bits; ++i)
	{
		if (CountSortByBit(res_arr, size, i))
		{
			return (1);
		}		
	}
	
	for (i = 0; i < size; ++i)
	{
		arr[i] = res_arr[i];
	}	
	
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
 
static int GetDigit(int num, int n)
{
    size_t i = 0;
	int sign = 1;
	
	if (0 > num)
	{
		sign = -1;
	}
	
	for (i = 0; i < (n - 1); ++i)
	{
		num /= 10;
	}
	
	return (num % 10) * sign;
}

static int GetBit(int num, int n)
{
	return ((num >> (n - 1)) & 1);
}
