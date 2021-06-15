#include <stddef.h> /* size_t */
#include <assert.h>
#include <stdlib.h>  /* malloc  */

#include "bin_mrg_qck.h"

static int Merge(int *arr, size_t left, size_t midean, size_t right);
static int MergeSortHelper(int *arr, size_t left, size_t right);

static void Swap(void *a, void *b, size_t element_size);

static void QuickSortHelper(void *arr_start, long int left, long int right,
 							size_t element_size, 
							int (*compar)(const void *, const void *));
static size_t Pivot(void *arr, long int left, long int right,
					size_t element_size, 
					int (*compar)(const void *, const void *));

int IterBinSearch(int *arr_to_srch, size_t arr_size, int num, 
				  size_t *output_idx)
{
	size_t low = 1;
	size_t high = arr_size;
	size_t mid = 0;

	assert(arr_to_srch);

	while (low <= high)
	{
		mid = low + ((high - low) / 2) - 1;

		if (num == arr_to_srch[mid])
		{
			*output_idx = mid;

			return (0);
		}
		else if (num < arr_to_srch[mid])
		{
			high = mid;
		}
		else
		{
			low = mid + 2;
		}
	}

	return (1);
}

int RecBinSearch(int *arr_to_srch, size_t arr_size, int num, size_t *output_idx)
{
	int status = 0;
	size_t extra = 0;

	assert(arr_to_srch);

	if (0 == arr_size)
	{
		return (1);
	}

	extra = (arr_size & 1);

	arr_size /= 2;

	if (num == arr_to_srch[arr_size])
	{
		*output_idx = arr_size;

		return (0);
	} 
	
	if (num > arr_to_srch[arr_size])
	{
		status = RecBinSearch(arr_to_srch + arr_size + extra, arr_size, num, 
							  output_idx);

		*output_idx += (arr_size + extra);
	}

	else
	{
		status = RecBinSearch(arr_to_srch, arr_size, num, output_idx);
	}

	return (status);
}

int MergeSort(int *arr_to_sort, size_t arr_size)
{
	assert(arr_to_sort);

	return (MergeSortHelper(arr_to_sort, 0, arr_size - 1));
}

static int Merge(int *arr, size_t left, size_t midean, size_t right)
{
	size_t left_iter = left;
	size_t right_iter = midean + 1;
	size_t tmp_arr_iter = 0;
	int *tmp_arr = NULL;

	assert(arr);

	tmp_arr = (int *)malloc(sizeof(int) * (right - left + 1));

	if (NULL == tmp_arr)
	{
		return (1);
	}

	while (left_iter <= midean && right_iter <= right)
	{
		if (arr[left_iter] < arr[right_iter])
		{
			tmp_arr[tmp_arr_iter] = arr[left_iter];
			++tmp_arr_iter;
			++left_iter;
		}
		else
		{
			tmp_arr[tmp_arr_iter] = arr[right_iter];
			++tmp_arr_iter;
			++right_iter;
		}
	}

	while (left_iter <= midean)
	{
		tmp_arr[tmp_arr_iter] = arr[left_iter];
		++tmp_arr_iter;
		++left_iter;
	}

	while (right_iter <= right)
	{
		tmp_arr[tmp_arr_iter] = arr[right_iter];
		++tmp_arr_iter;
		++right_iter;
	}

	for (tmp_arr_iter = 0, left_iter = left; left_iter <= right; 
		 ++tmp_arr_iter, ++left_iter)
	{
		arr[left_iter] = tmp_arr[tmp_arr_iter];
	}

	free(tmp_arr);

	return (0);
}

static int MergeSortHelper(int *arr, size_t left, size_t right)
{
	size_t midean = 0;
	int status = 0;

	assert(arr);

	if (left < right)
	{
		midean = left + ((right - left) / 2);
		MergeSortHelper(arr, left, midean);
		MergeSortHelper(arr, midean + 1, right);
		status = Merge(arr, left, midean, right);
	}

	return (status);
}

void RecQsort(void *base, size_t arr_size, size_t element_size,
			  int (*compar)(const void *data1, const void *data2))
{	
	assert(base);
	assert(compar);

	QuickSortHelper(base, 0, arr_size - 1, element_size, compar);

	return;
}

static void QuickSortHelper(void *arr_start, long int left, long int right,
							size_t element_size, 
							int (*compar)(const void *data1, const void *data2))
{
	long int piv = 0;

	assert(arr_start);
	assert(compar);

	if (left < right)
	{
		piv = Pivot(arr_start, left, right, element_size, compar);

		QuickSortHelper(arr_start, left, piv - 1, element_size, compar);
		QuickSortHelper(arr_start, piv + 1, right, element_size, compar);
	}

	return;
}

static size_t Pivot(void *arr, long int left, long int right, 
					size_t element_size,
					int (*compar)(const void *data1, const void *data2))
{
	long int i = (left - 1);

	assert(arr);
	assert(compar);

	while (left < right)
	{
		if (0 > compar(((char *)arr + (left * element_size)),
			(char *)arr + (right * element_size)))
		{
			++i;

			Swap((char *)arr + (i * element_size),
				 (char *)arr + (left * element_size), element_size);
		}

		++left;
	}

	Swap((char *)arr + (i + 1) * element_size, (char *)arr 
		+ right * element_size, element_size);

	return ((size_t)(i + 1));
}

static void Swap(void *a, void *b, size_t element_size)
{
	char t = 0;
	char *a_ptr = (char *)a;
	char *b_ptr = (char *)b;

	assert(a);
	assert(b);

	while (0 < element_size)
	{
		t = *a_ptr;
		*a_ptr = *b_ptr;
		*b_ptr = t;

		++a_ptr;
		++b_ptr;
		--element_size;
	}

	return;
}