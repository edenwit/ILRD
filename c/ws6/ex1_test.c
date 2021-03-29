#include <stdio.h> /* printf */
#include "ex1.h"

static void Pow2Test();

static void IsPow2LoopTest();
static void IsPow2NoLoopTest();

static void Add1Test();

static void ByteMirrorLoopTest();
static void ByteMirrorNoLoopTest();

static void PrintThreeOnTest();

static void IsBit2And6OnTest();
static void IsBit2Or6OnTest();
static void Swap3And5Test();

static void  DivideBy16Test();

static void  SwapTest();

static void  CountBitsLoopTest();
static void  CountBitsNoLoopTest();

static void  PrintFloatBitsTest();

int main()
{
	Pow2Test();
	
	IsPow2LoopTest();
	IsPow2NoLoopTest();
	
	Add1Test();
	
	ByteMirrorLoopTest();
	ByteMirrorNoLoopTest();
		
	PrintThreeOnTest();
	
	IsBit2And6OnTest();
	IsBit2Or6OnTest();
	Swap3And5Test();
	DivideBy16Test();

	SwapTest();

	CountBitsLoopTest();
	CountBitsNoLoopTest();

	PrintFloatBitsTest();
		
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

static void Add1Test()
{
	const int input1_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;
	int res = 0; 

	printf("\n\n-----------Add1-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		res = Add1(input1_arr[i]);
		printf("Num: %d. Exp: %d. Actual: %d. ", input1_arr[i], input1_arr[i] + 1, res);
		
		if (res == input1_arr[i] + 1)
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

static void PrintThreeOnTest()
{
	unsigned int input1_arr[] = {0, 236, 3, 4, 15, 191, 7, 39, 50, 63};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	
	printf("\n\n-----------PrintThreeOn-------------: \n\n");
	
	PrintThreeOn(input1_arr, arr_size);
	return;	
}

static void ByteMirrorLoopTest()
{
	const int input1_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 68, 0};
	const int exp_res_arr[] = {128, 64, 192, 32, 160, 96, 223, 16, 144, 34, 0};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;
	int res = 0; 

	printf("\n\n-----------ByteMirrorLoop-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		res = ByteMirrorLoop(input1_arr[i]);
		printf("Num: %d. \t Exp: %d.\tActual: %d. \t", input1_arr[i], exp_res_arr[i], res);
		
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

static void ByteMirrorNoLoopTest()
{
	const int input1_arr[] = {1, 15, 56, 74, 100, 151, 200, 255, 256, 0};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;
	int res = 0; 
	
	printf("\n\n-----------ByteMirrorNoLoop-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		res = ByteMirrorNoLoop(input1_arr[i]);
		printf("Num: %d. \t Exp: %d.\tActual: %d. \t", input1_arr[i], ByteMirrorLoop(input1_arr[i]), res);
		
		if (res == ByteMirrorLoop(input1_arr[i]))
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

static void IsBit2And6OnTest()
{
	const int input1_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 68, 255};
	const int exp_res_arr[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;
	int res = 0; 

	printf("\n\n-----------IsBit2And6On-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		res = IsBit2And6On(input1_arr[i]);
		printf("Num: %d. Exp: %d. Actual: %d. ", input1_arr[i], exp_res_arr[i], res);
		
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

static void IsBit2Or6OnTest()
{
	const int input1_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 68, 255};
	const int exp_res_arr[] = {0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;
	int res = 0; 

	printf("\n\n-----------IsBit2Or6On-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		res = IsBit2Or6On(input1_arr[i]);
		printf("Num: %d. Exp: %d. Actual: %d. ", input1_arr[i], exp_res_arr[i], res);
		
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

static void  Swap3And5Test()
{
	const int input1_arr[] = {0, 1, 15, 16, 31, 32, 63, 64, 120, 240, 1000};
	const int exp_res_arr[] = {0, 1, 39, 16, 55, 8, 63, 64, 120, 216, 232};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;
	int res = 0; 

	printf("\n\n-----------Swap3And5-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		res = Swap3And5(input1_arr[i]);
		printf("Num: %d.\t Exp: %d.\t Actual: %d. ", input1_arr[i], exp_res_arr[i], res);
		
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
static void  DivideBy16Test()
{
	const int input1_arr[] = {8, 3, 16, 18, 31, 32, 33, 63, 64, 65, 0};
	const int exp_res_arr[] = {0, 0, 16, 16, 16, 32, 32, 48, 64, 64, 0};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;
	int res = 0; 

	printf("\n\n-----------DivideBy16-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		res = DivideBy16(input1_arr[i]);
		printf("Num: %d. Exp: %d. Actual: %d. ", input1_arr[i], exp_res_arr[i], res);
		
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

static void  SwapTest()
{
	unsigned int input1_arr[] = {11111, 2, 3, 4, 10, 204520};
	unsigned int input2_arr[] = {3, 5, 6, 8, 10, 20};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;
	unsigned int temp_x = 0;
	unsigned int temp_y = 0;
	 
	
	printf("\n\n-----------Swap-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
			temp_x = input1_arr[i];
			temp_y = input2_arr[i];
			Swap(&input1_arr[i],&input2_arr[i]);
			printf("X: %u\t, Y: %u\t. X: %u\t. Y: %u\t. ", temp_x, temp_y, input1_arr[i], input2_arr[i]);
			
			if (temp_x == input2_arr[i] && temp_y == input1_arr[i])
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

static void  CountBitsLoopTest()
{
	const int input1_arr[] = {8, 3, 16000, 154648, 2147483647, 2147483646, 255, 64213, 100, 1, 0};
	const int exp_res_arr[] = {1, 2, 6, 7, 31, 30, 8, 11, 3, 1, 0};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;
	int res = 0; 

	printf("\n\n-----------CountBitsLoop-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		res = CountBitsLoop(input1_arr[i]);
		printf("Num: %d.\t Exp: %d.\t Actual: %d. ", input1_arr[i], exp_res_arr[i], res);
		
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

static void  CountBitsNoLoopTest()
{
	const int input1_arr[] = {8, 3, 16000, 154648, 16, 2147483647, 255, 64213, 100, 1, 0};
	const int exp_res_arr[] = {1, 2, 6, 6, 1, 16, 8, 11, 3, 1, 0};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;
	int res = 0; 

	printf("\n\n-----------CountBitsNoLoop-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		res = CountBitsNoLoop(input1_arr[i]);
		printf("Num: \t%d.\t Exp: \t%d.\t Actual: %d. ", input1_arr[i], exp_res_arr[i], res);
		
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

static void  PrintFloatBitsTest()
{
	float input_f = 0.0;
		
	printf("\n\n-----------PrintFloatBits-------------: \n\n");
	printf("Please enter a float value: \n");
	scanf("%f", &input_f);
		
	PrintFloatBits(input_f);
	
	return;	
}
