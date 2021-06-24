#include <stdio.h>
#include <stdlib.h>
#include "bin_mrg_qck.h"


int IterBinSearch(int *arr_to_srch, size_t arr_size, int num, size_t *output_idx)
{
    size_t middle = 0;
    int end = arr_size - 1;
    int start = 0;
    
    while (start <= end)
    {
        middle = ((start + end)/2);

        if (num == arr_to_srch[middle])
        {
            *output_idx = middle  ;
            
            return (0);
        }

        else if (num < arr_to_srch[middle])
        {
            end = middle - 1;
        }
        else 
        {
            start = middle + 1;
        }
    }
    return (1);
}

int RecBinSearch(int *arr_to_srch, size_t arr_size, int num, size_t *output_idx)
{   
    
    int middle = (arr_size - 1) / 2;
    int status = 1;

    if (num == arr_to_srch[middle])
    {
        *output_idx = middle;  
        return (0);
    }

    else if (num < arr_to_srch[middle] && 0 < arr_size)
    {
        return (RecBinSearch(arr_to_srch, middle, num, output_idx));    
        
    }
    else if(num > arr_to_srch[middle] && 0 < arr_size)
    {
        status = RecBinSearch(arr_to_srch + middle + 1, arr_size - middle - 1  , num, output_idx);

        *output_idx += middle + 1;

        return (status);
    }

    return (status); 
}

int FunMerge(int *arr1,size_t size1, int *arr2 ,size_t size2)
{
   
    int *merged_arr = NULL;
    size_t i =0;
    size_t j = 0;
    size_t t = 0;

    merged_arr = (int*)malloc(sizeof(int)*(size1 + size2));
    if (merged_arr == NULL)
    {
        return 0;
    }

    while (i < size1 &&  j < size2)
    {
        if (arr1[i] < arr2[j])
        {
            merged_arr[t] = arr1[i];
            i++;

        }
        else
        {
            merged_arr[t] = arr2[j];
            j++;
        }   
        t++;
    }

    while (i < size1)
    {
        merged_arr[t] = arr1[i];
        t++;
        i++;
    }

    while (j < size2)
    {
        merged_arr[t] = arr2[j];
        t++;
        j++;
    }

    for (i = 0 ; i < size1+ size2; i++)
    {
        arr1[i] = merged_arr[i];
    }
    
    free(merged_arr);

    return (1);
}


int MergeSort(int *arr_to_sort, size_t arr_size)
{
    if (arr_size == 1)
    {    
        return (1);
    }
    
    if (arr_size % 2 == 0)
    {
        MergeSort(arr_to_sort, arr_size/2);
        MergeSort(arr_to_sort + arr_size/2, arr_size/2);
        FunMerge(arr_to_sort, arr_size/2, arr_to_sort + arr_size/2 ,arr_size/2);
    }
    else
    {
        MergeSort(arr_to_sort, arr_size/2 + 1);
        MergeSort(arr_to_sort + ((arr_size/2) + 1), arr_size/2 );
        FunMerge(arr_to_sort, arr_size/2 +1, arr_to_sort + arr_size/2 +1 ,arr_size/2);  
    }

    return (1);
}

void SwapChar(char *data1 , char *data2)
{
    char temp = *data1;
    *data1 = *data2;
    *data2 = temp; 
}


void Swap(char *data1, char *data2, size_t element_size)
{
    
    while (0 < element_size)
    {
        SwapChar(data1, data2);
        data1++;
        data2++;
        element_size--;
    }
    return;
}


void *partition(void *base, size_t arr_size, size_t element_size, int (*compar)(const void *, const void *))
{
    char *start = base;
    void *pivot = (char*)base + (arr_size - 1)*element_size;
    size_t i = 0;
    size_t j = 0;

    for (j = 0; j < (arr_size-1)*element_size ; j = j + element_size)
    {   
        if (compar(start + j, pivot) < 0)
        {
            Swap(start + i, start + j, element_size);
            i = i + element_size;
        }
    }
    Swap(start + i, pivot, element_size);

    return (start + i);
}

void RecQsort(void *base, size_t arr_size, size_t element_size, int (*compar)(const void *, const void *))
{
    char *pivot = NULL;
    
    if (arr_size < 2)
    {
        return;
    }
    
    pivot = partition(base, arr_size, element_size, compar); 

    RecQsort(base, ((char*)pivot - (char*)base)/element_size, element_size, compar);

    RecQsort(pivot +  element_size, arr_size - 1 - ((char*)pivot - (char*)base)/element_size, element_size, compar);

}


