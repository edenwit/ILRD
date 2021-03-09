#include <stdio.h>
#include <assert.h> /* assert */

void SwapSizetVars(size_t *ptr_x, size_t *ptr_y);

int main()
{
	size_t arr_test_x[] = {1, (-5), 0, 1000, -7, 3}; // test array for x values.
	size_t arr_test_y[] = {7, 8, (-15), 1, -9, 3}; // test array for y values.
	size_t array_size = sizeof(arr_test_x) / sizeof(arr_test_x[0]);
	size_t temp_x,temp_y; // temp values for comparassion.
	size_t i; // index for loop/
	
	for ( i = 0; i < 6; i++ )
	{
		printf("Values before swap: x: %zu, y: %zu. ", arr_test_x[i], arr_test_y[i]);
		temp_x = arr_test_x[i];
		temp_y = arr_test_y[i];
		SwapSizetVars(&arr_test_x[i], &arr_test_y[i]);
		printf("Values after swap: x: %zu, y: %zu.\t", arr_test_x[i], arr_test_y[i]);
		if(arr_test_x[i] == temp_y && arr_test_y[i] == temp_x)
		{
			printf("Success!\n");
		}
		else
		{
			printf("Failure!\n");
		}
	}
	
	printf("Values before swap: x: NULL, y: %zu. ",arr_test_y[i]);
	SwapSizetVars(NULL, &arr_test_y[i]);
	printf("Values after swap: x: %zu, y: %zu.\n",arr_test_x[i],arr_test_y[i]);
		
	return 0;
}

void SwapSizetVars(size_t *ptr_x, size_t *ptr_y)
{
	int temp = 0;
	
	assert (ptr_x != NULL && ptr_y != NULL);
	temp = *ptr_x;
	*ptr_x = *ptr_y;
	*ptr_y = temp;

	return;
}
