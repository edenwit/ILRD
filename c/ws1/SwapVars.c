#include <stdio.h>

void SwapVars(int *ptr_x, int *ptr_y);

int main()
{
	int arr_test_x[6] = {1, (-5), 0, 1000, -7, 3}; // test array for x values.
	int arr_test_y[6] = {7, 8, (-15), 1, -9, 3}; // test array for y values.
	int temp_x,temp_y; // temp values for comparassion.
	int i; // index for loop/
	
	for ( i = 0; i < 6; i++ )
	{
		printf("Values before swap: x: %d, y: %d. ", arr_test_x[i], arr_test_y[i]);
		temp_x = arr_test_x[i];
		temp_y = arr_test_y[i];
		SwapVars(&arr_test_x[i], &arr_test_y[i]);
		printf("Values after swap: x: %d, y: %d.\n", arr_test_x[i], arr_test_y[i]);
		if(arr_test_x[i] == temp_y && arr_test_y[i] == temp_x)
		{
			printf("Success!\n");
		}
		else
		{
			printf("Failure!\n");
		}
	}
	
	printf("Values before swap: x: NULL, y: %d. ",arr_test_y[i]);
	SwapVars(NULL, &arr_test_y[i]);
	printf("Values after swap: x: %d, y: %d.\n",arr_test_x[i],arr_test_y[i]);
		
	return 0;
}

void SwapVars(int *ptr_x, int *ptr_y)
{
	if(ptr_x != NULL && ptr_y != NULL)
	{
		int temp = *ptr_x;
		*ptr_x = *ptr_y;
		*ptr_y = temp;
	}
	else
	{
		printf("Fail! one of the pointers is NULL!\n");
	}
	
	return;
}
