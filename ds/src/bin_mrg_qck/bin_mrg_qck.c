#include "bin_mrg_qck.h"
#include <stddef.h> /* size_t */
#include <assert.h>
#include <stdlib.h>

static int Merge(int *arr, size_t left, size_t midean, size_t right);
static int MergeSortHelper(int *arr, size_t left, size_t right);

int IterBinSearch(int *arr_to_srch, size_t arr_size, int num, size_t *output_idx)
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
			/*printf("%d found.\n", num);*/

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
		/*printf("search %d, high: %ld, low: %ld, mid: %ld.\n", num, high, low, mid);*/

		

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

	if (0 != arr_size % 2)
	{
		extra = 1;
	}

	arr_size /= 2;
	
	if (num == arr_to_srch[arr_size])
	{
		*output_idx = arr_size;

		return (0);
	}
	if (num > arr_to_srch[arr_size])
	{
		status = RecBinSearch(arr_to_srch + arr_size + extra, arr_size, num, output_idx);
	
		*output_idx+=(arr_size + extra);
	}
	else
	{
		status = RecBinSearch(arr_to_srch, arr_size, num, output_idx);
	}

	return (status);

}

int MergeSort(int *arr_to_sort, size_t arr_size)
{
	return (MergeSortHelper(arr_to_sort, 0, arr_size - 1));
}


static int Merge(int *arr, size_t left, size_t midean, size_t right)
{
	size_t left_iter = left;
	size_t right_iter = midean + 1;
	size_t tmp_arr_iter = 0;
	int *tmp_arr = (int *)malloc(sizeof(int) * (right - left + 1));
	
	assert(arr);

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

	for (tmp_arr_iter = 0, left_iter = left; left_iter <= right; ++tmp_arr_iter, ++left_iter)
	{
		arr[left_iter] = tmp_arr[tmp_arr_iter];
	}

	free(tmp_arr);

	return (0);
}


static int MergeSortHelper(int *arr, size_t left, size_t right)
{
	size_t midean = 0;

	assert(arr);

	if (left < right)
	{
		midean = left + ((right - left) / 2);
		MergeSortHelper(arr, left, midean);
		MergeSortHelper(arr, midean + 1, right);
		Merge(arr, left, midean, right);
	}


	return (0);
}



/* O (n log n) avg*/
void RecQsort(void *base, size_t arr_size, size_t element_size, 
					  int (*compar)(const void *, const void *));
