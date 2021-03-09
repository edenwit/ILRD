#include <stdio.h> 						

void CopyArr(int *input_arr, int *output_arr, size_t arr_len);

int main()
{
	int arr_1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	size_t arr_size = sizeof(arr_1) / sizeof(arr_1[0]);
	int arr_2[arr_size];
	int i=0;
	printf("Original array:\n");
	for( i = 0; i < arr_size; ++i)
	{
		printf("%d ",arr_1[i]);
	}

	printf("\nNew array:\n");
	for( i = 0; i < arr_size; ++i)
	{
		printf("%d ",arr_2[i]);
	}
	printf("\n-------------------------\n");

	CopyArr(arr_1, arr_2, arr_size);

	printf("Original array:\n");
	for( i = 0; i < arr_size; ++i)
	{
		printf("%d ",arr_1[i]);
	}

	printf("\nNew array:\n");
	for( i = 0; i < arr_size; ++i)
	{
		printf("%d ",arr_2[i]);
	}
	printf("\n");

}

void CopyArr(int *input_arr, int *output_arr, size_t arr_len)
{
	int i = 0;
	
	for( i = 0; i < arr_len; ++i )
	{
		*(output_arr + i) = *(input_arr + i);
	}
	
	return;
}
