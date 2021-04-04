#include <stdio.h>

static void test_MaxSubArray();
static void PrintArray(int *arr, size_t arr_size);
int MaxSubArray(int *arr, int arr_size, int *p1, int *p2);

int main()
{
	test_MaxSubArray();
	
	return 0;
}

static void test_MaxSubArray()
{
	int array1[] = {-2, 1, -3, 4, -1, 2, 3, -5, 4};
	size_t arr_size1 = sizeof(array1) / sizeof(array1[0]);
	int array2[] = {-2, 0, 0, 0, -1, 0, 0, -5, -10};
	size_t arr_size2 = sizeof(array2) / sizeof(array2[0]);
	int array3[] = {-2, 10, -3, 4, -1, 2, -103, -5, 4};
	size_t arr_size3 = sizeof(array3) / sizeof(array3[0]);
	int p1 = 0;
	int p2 = 0;
	int max_sum = 0;
	
	PrintArray(array1, arr_size1);
	max_sum = MaxSubArray(array1, arr_size1, &p1, &p2);
	printf("Max sum: %d, from %d to %d.\n", max_sum, p1, p2);
	
	p1 = 0;
	p2 = 0;
	
	PrintArray(array2, arr_size2);
	max_sum = MaxSubArray(array2, arr_size2, &p1, &p2);
	printf("Max sum: %d, from %d to %d.\n", max_sum, p1, p2);
	
	p1 = 0;
	p2 = 0;
	
	PrintArray(array3, arr_size3);
	max_sum = MaxSubArray(array3, arr_size3, &p1, &p2);
	printf("Max sum: %d, from %d to %d.\n", max_sum, p1, p2);
	
	return;
}

int MaxSubArray(int *arr, int arr_size, int *p1, int *p2)
{
	int total_max = 0;
	int temp_max = 0;
	int i = 0;
	int tp1 = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
		temp_max += arr[i];
		if (temp_max >= total_max)
		{
			total_max = temp_max;
			*p1 = tp1;
			*p2 = i;
		}
		else if (0 > temp_max)
		{
			temp_max = 0;
			tp1 = i + 1;
		}
	}	
	
	return total_max;	
}

static void PrintArray(int *arr, size_t arr_size)
{
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	return;
}
