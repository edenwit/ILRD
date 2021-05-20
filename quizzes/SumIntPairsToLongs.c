#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <limits.h> /* INT_MAX */

long *SumIntPairsToLongs(int ints[], size_t num_of_elements);
static void SumIntPairsToLongsTest();

static void PrintIntArr(int * arr, size_t arr_size);
static void PrintLongArr(long * arr, size_t arr_size);

int main()
{
	SumIntPairsToLongsTest();

	return 0;
}

long *SumIntPairsToLongs(int ints[], size_t num_of_elements)
{
	long *longs = (long *)ints;
	size_t i = 0;
	
	assert(ints);
	
	num_of_elements /= 2;
	
	for (i = 0; i < num_of_elements; ++i)
	{
		*((long *)ints) = (long)(*ints) + (long)(*(ints + 1));
		ints += 2;
	}
	
	return (longs);
}

static void SumIntPairsToLongsTest()
{
	int ints[] = {1, 6, 456, -3, 8, 12};
	int max_ints[] = {INT_MAX, INT_MAX, INT_MIN, INT_MIN, INT_MAX, INT_MIN};
	size_t arr_size = sizeof(ints) / sizeof(ints[0]);
	long *long_arr = NULL;
	
	PrintIntArr(ints, arr_size);
	
	long_arr = SumIntPairsToLongs(ints, arr_size);
	
	arr_size /= 2;
	
	PrintLongArr(long_arr, arr_size);
	
	arr_size = sizeof(max_ints) / sizeof(max_ints[0]);
	
	PrintIntArr(max_ints, arr_size);	
	
	long_arr = SumIntPairsToLongs(max_ints, arr_size);	
	
	arr_size /= 2;
	
	PrintLongArr(long_arr, arr_size);	
	
	return;
}

static void PrintIntArr(int * arr, size_t arr_size)
{
	size_t i = 0;
	for (i = 0; i < arr_size; ++i)
	{
		printf("%d ", arr[i]);

	}
	printf("\n");
		
	return;
}

static void PrintLongArr(long * arr, size_t arr_size)
{
	size_t i = 0;
	for (i = 0; i < arr_size; ++i)
	{
		printf("%ld ", arr[i]);

	}
	printf("\n");
		
	return;
}
