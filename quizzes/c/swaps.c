#include <stddef.h>  /* size_t */
#include <assert.h>
#include <stdio.h> /* printf */

void Swap1(int *x, int *y);
void Swap2(int *x, int *y);
void Swap3(int *x, int *y);
static void Swap1Test();
static void Swap2Test();
static void Swap3Test();

int main()
{
	Swap1Test();
	Swap2Test();
	Swap3Test();	

	return (0);
}


void Swap1(int *x, int *y)
{
	int temp = 0;

	assert(x);
	assert(y);
	
	temp = *x;
	*x = *y;
	*y = temp;
	
	return;	
}

void Swap2(int *x, int *y)
{
	assert(x);
	assert(y);
	
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
	
	return;
}

void Swap3(int *x, int *y)
{
	assert(x);
	assert(y);
	
	*x = *x - *y;
	*y = *x + *y;
	*x = *y - *x;
	
	return;
}

static void Swap1Test()
{	
	int ex_test_arr1[] = {0, 15, -110100, 124, 126};
	int ex_test_arr2[] = {-1, 0, 50, 165128, 0};	
	int temp_x = 0;
	int temp_y = 0;	
	size_t arr_size = sizeof(ex_test_arr1) / sizeof(ex_test_arr1[0]);
	size_t i = 0;


	for (i = 0; i < arr_size; ++i)
	{
		temp_x = ex_test_arr1[i];
		temp_y = ex_test_arr2[i];	
		
		Swap1(&ex_test_arr1[i], &ex_test_arr2[i]);
			
		if (temp_x != ex_test_arr2[i] || temp_y != ex_test_arr1[i])
		{
			printf("Swap1 Test #%ld failed. test1: %d, test2: %d. temp1: %d, temp2: %d\n", i + 1, ex_test_arr1[i], ex_test_arr2[i], temp_x, temp_y);
		}
	}	
}

static void Swap2Test()
{	
	int ex_test_arr1[] = {0, 15, -110100, 124, 126};
	int ex_test_arr2[] = {-1, 0, 50, 165128, 0};	
	int temp_x = 0;
	int temp_y = 0;	
	size_t arr_size = sizeof(ex_test_arr1) / sizeof(ex_test_arr1[0]);
	size_t i = 0;


	for (i = 0; i < arr_size; ++i)
	{
		temp_x = ex_test_arr1[i];
		temp_y = ex_test_arr2[i];	
		
		Swap2(&ex_test_arr1[i], &ex_test_arr2[i]);
			
		if (temp_x != ex_test_arr2[i] || temp_y != ex_test_arr1[i])
		{
			printf("Swap1 Test #%ld failed. test1: %d, test2: %d. temp1: %d, temp2: %d\n", i + 1, ex_test_arr1[i], ex_test_arr2[i], temp_x, temp_y);
		}
	}	
}

static void Swap3Test()
{	
	int ex_test_arr1[] = {0, 15, -110100, 124, 126};
	int ex_test_arr2[] = {-1, 0, 50, 165128, 0};	
	int temp_x = 0;
	int temp_y = 0;	
	size_t arr_size = sizeof(ex_test_arr1) / sizeof(ex_test_arr1[0]);
	size_t i = 0;


	for (i = 0; i < arr_size; ++i)
	{
		temp_x = ex_test_arr1[i];
		temp_y = ex_test_arr2[i];	
		
		Swap3(&ex_test_arr1[i], &ex_test_arr2[i]);
			
		if (temp_x != ex_test_arr2[i] || temp_y != ex_test_arr1[i])
		{
			printf("Swap1 Test #%ld failed. test1: %d, test2: %d. temp1: %d, temp2: %d\n", i + 1, ex_test_arr1[i], ex_test_arr2[i], temp_x, temp_y);
		}
	}	
}
