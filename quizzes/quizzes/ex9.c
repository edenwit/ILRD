#include <assert.h>
#include <stdio.h>


/* ex1 */
size_t CountBitCouples(char byte);

/* ex2 */
void Swap1(int *x, int *y);
void Swap2(int *x, int *y);
void Swap3(int *x, int *y);

/* ex3 */ 
size_t CountBits(long num);

int main()
{
	char ex1_test_arr[] = {0, 25, -125, -1, 126};
	size_t ex1_exp_arr[] = {0, 1, 1, 7, 5};
	
	int ex2_test_arr1[] = {0, 15, 100, 124, 126};
	int ex2_test_arr2[] = {1, 9, 50, 128, 0};	
	char temp_x = 0;
	char temp_y = 0;	
	
	size_t i = 0;
	
	printf("-------- ex1 ----------\n");
	for (i = 0; i < 5; ++i)
	{
		if (CountBitCouples(ex1_test_arr[i]) != ex1_exp_arr[i])
		{
			printf ("Test with %d and exp %ld failed. returned: %ld. \n", ex1_test_arr[i], ex1_exp_arr[i], CountBitCouples(ex1_test_arr[i]));
		}
	}
	
	printf("-------- ex2 ----------\n\n");
	printf("-------- ver1 ----------\n");
	
	for (i = 0; i < 5; ++i)
	{
		temp_x = ex2_test_arr1[i];
		temp_y = ex2_test_arr2[i];	
		
		Swap1(&ex2_test_arr1[i], &ex2_test_arr2[i]);
			
		if (temp_x != ex2_test_arr2[i] || temp_y != ex2_test_arr1[i])
		{
				printf ("Test with %d and %d failed.\n", ex2_test_arr2[i], ex2_test_arr1[i]);
		}
	}	
	printf("-------- ver2 ----------\n");
	
	for (i = 0; i < 5; ++i)
	{
		temp_x = ex2_test_arr2[i];
		temp_y = ex2_test_arr1[i];	
		
		Swap2(&ex2_test_arr1[i], &ex2_test_arr2[i]);
			
		if (temp_x != ex2_test_arr1[i] || temp_y != ex2_test_arr2[i])
		{
				printf ("Test with %d and %d failed.\n", ex2_test_arr1[i], ex2_test_arr2[i]);
		}
	}	
	printf("-------- ver3 ----------\n");
	for (i = 0; i < 5; ++i)
	{
		temp_x = ex2_test_arr1[i];
		temp_y = ex2_test_arr2[i];	
		
		Swap3(&ex2_test_arr1[i], &ex2_test_arr2[i]);
			
		if (temp_x != ex2_test_arr2[i] || temp_y != ex2_test_arr1[i])
		{
				printf ("Test with %d and %d failed.\n", ex2_test_arr2[i], ex2_test_arr1[i]);
		}
	}


	return 0;
}


/* ex1 */
size_t CountBitCouples(char byte)
{
	size_t i = 0;
	int counter = 0;
	
	for (i = 1; i < 8; ++i)
	{
		if ((byte & (1 << i)) && (byte & (1 << (i - 1))))
		{
			++counter;
		}
	}
	return counter;
}

/* ex2 */ 
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
	*x = *x ^ *y;
	*x = *x ^ *y;
	
	return;
}

void Swap3(int *x, int *y)
{
	assert(x);
	assert(y);
	
	*x = *x + *y;
	*x = *x - *y;
	*x = *x - *y;
	
	return;
}

/* ex3 */ 
size_t CountBits(long num)
{
	size_t counter = 0;
	
	while (0 != num)
	{
		num = num & (num - 1);
		++counter;
	}
	
	return counter;
}
