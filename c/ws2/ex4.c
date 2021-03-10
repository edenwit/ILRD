#include <stdio.h> /* size_t, printf */
#include <assert.h> /* assert */

void SwapSizetVars(size_t *ptr_x, size_t *ptr_y);
void SwapSizetPointers(size_t **ptr_x, size_t **ptr_y);

int main()
{
	size_t arr_test_x[] = {1, 12, 0, 1000, 547, 3}; /* test array for x values.*/
	size_t arr_test_y[] = {7, 8, 12, 1, 1234, 31}; /* test array for y values. */
	size_t array_size = sizeof(arr_test_x) / sizeof(arr_test_x[0]);
	size_t temp_x = 0; /* temp values for comparassion. */
	size_t temp_y = 0; /* temp values for comparassion. */
	size_t *temp_x_p = 0; /* temp values for comparassion. */
	size_t *temp_y_p = 0; /* temp values for comparassion. */
	size_t i; /* index for loop*/
	size_t x1[] =  {1, 12, 0, 1000, 5647, 3}; /* test array for x1 values.*/
	size_t x2[] =  {7, 8, 12, 1, 1234, 13}; /* test array for x2 values. */
	size_t arr_test_size = sizeof(arr_test_x) / sizeof(arr_test_x[0]);
	size_t *pt1 = NULL;
	size_t *pt2 = NULL;
	
	for (i = 0; i < array_size; i++)
	{
		printf("Test #%lu: ", i);
		printf("Values before : x: %lu\t\t, y: %lu\t\t.", arr_test_x[i], arr_test_y[i]);
		
		temp_x = arr_test_x[i];
		temp_y = arr_test_y[i];
		
		SwapSizetVars(&arr_test_x[i], &arr_test_y[i]);
		
		printf("Values after : x: %lu, y: %lu.\t\t", arr_test_x[i], arr_test_y[i]);
		
		if (arr_test_x[i] == temp_y && arr_test_y[i] == temp_x)
		{
			printf("Success!\n\n");
		}
		else
		{
			printf("Failure!\n\n");
		}
	}

	printf("\n------------------------------------------\n");
	for ( i = 0; i < arr_test_size; i++ )
	{
		pt1 = &x1[i];
		pt2 = &x2[i];
		
		printf("Test #%lu: ", i);
		printf("\nx1  , x2   adress  : %p, %p\n", (void *)pt1, (void *)pt2);
		printf("x1  , x2   values  : %lu, %lu\n", *pt1, *pt2);
		
		temp_x_p = (void *)pt1;
		temp_y_p = (void *)pt2;
		
		SwapSizetPointers(&pt1,&pt2);
		
		printf("x1  , x2   adress  : %p, %p\n", (void *)pt1, (void *)pt2);
		printf("x1  , x2   values  : %lu, %lu\n", *pt1, *pt2);
		
		if ((void *)pt1 == temp_y_p && (void *)pt2 == temp_x_p)
		{
			printf("Success!\n\n");
		}
		else
		{
			printf("Failure!\n\n");
		}
	}
	
	return 0;
}

void SwapSizetVars(size_t *ptr_x, size_t *ptr_y)
{
	size_t temp = 0;
	
	assert ( NULL != ptr_x && NULL != ptr_y);
	
	temp = *ptr_x;
	*ptr_x = *ptr_y;
	*ptr_y = temp;

	return;
}

void SwapSizetPointers(size_t **ptr_x, size_t **ptr_y)
{
	assert ( NULL != ptr_x && NULL != ptr_y);
	
	SwapSizetVars((size_t *)ptr_x, (size_t *)ptr_y);

	return;
}
