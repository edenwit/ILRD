#include <stdio.h> /* printf */
#include "ex1.h"

static void Pow2Test();
static void IsPow2LoopTest();
static void IsPow2NoLoopTest();

int main()
{
	Pow2Test();
	IsPow2LoopTest();
	IsPow2NoLoopTest();
	
	return 0;
}

static void Pow2Test()
{
	const unsigned int input1_arr[] = {1, 2, 3, 4, 10, 20};
	const unsigned int input2_arr[] = {3, 5, 6, 8, 10, 20};
	const long int exp_res_arr[] = {8, 64, 192, 1024, 10240, 15};	
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;
	long int res = 0L; 
	
	printf("\n\n-----------Pow2-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
			res = Pow2(input1_arr[i],input2_arr[i]);
			printf("X: %u, Y: %u. Exp: %ld. Actual: %ld. ", input1_arr[i], input2_arr[i], exp_res_arr[i], res);
			
			if (res == exp_res_arr[i])
			{
				printf("Success!\n");
			}
			else
			{
				printf("Failure!\n");
			}
	}
	return;
}

static void IsPow2LoopTest()
{
	const unsigned int input1_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	const int exp_res_arr[] = {1, 1, 0, 1, 1, 0, 0, 1, 0, 0};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;
	long int res = 0L; 
	
	printf("\n\n-----------IsPow2Loop-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		res = IsPow2Loop(input1_arr[i]);
		printf("Num: %u. Exp: %d. Actual: %ld. ", input1_arr[i], exp_res_arr[i], res);
		
		if (res == exp_res_arr[i])
		{
			printf("Success!\n");
		}
		else
		{
			printf("Failure!\n");
		}
	}
	
	return;	
}

static void IsPow2NoLoopTest()
{
	const unsigned int input1_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	const int exp_res_arr[] = {1, 1, 0, 1, 1, 0, 0, 1, 0, 0};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;
	long int res = 0L; 
	
	printf("\n\n-----------IsPow2NoLoop-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		res = IsPow2NoLoop(input1_arr[i]);
		printf("Num: %u. Exp: %d. Actual: %ld. ", input1_arr[i], exp_res_arr[i], res);
		
		if (res == exp_res_arr[i])
		{
			printf("Success!\n");
		}
		else
		{
			printf("Failure!\n");
		}
	}
	
	return;	
}
