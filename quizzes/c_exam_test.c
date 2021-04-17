#include <stddef.h> /* size_t */
#include <stdio.h> /* printf */
#include <string.h> /* strlen, strcpy, strcmp, strncpy, strcat */

#include "c_exam.h"

static void FlipDigitsInNumTest();
static void ByteMirrorTest();
static void FlipBitTest();
static void CountBitsInByteTest();
static void RotateLeftTest();
static void SwapPointersTest();
static void StrlenTest();
static void StrcmpTest();
static void StrcpyTest();
static void StrncpyTest();
static void StrcatTest();
static void GetNFibonacciElementTest();
static void IntToStringTest();
static void MultiPlyBy8Test();
static void Swap1Test();
static void Swap2Test();
static void Swap3Test();


int main()
{
	FlipDigitsInNumTest();
	ByteMirrorTest();
	FlipBitTest();
	CountBitsInByteTest();
	RotateLeftTest();
	SwapPointersTest();
	
	StrlenTest();
	StrcmpTest();
	StrcpyTest();
	StrncpyTest();
	StrcatTest();
	
	GetNFibonacciElementTest();
	IntToStringTest();
	MultiPlyBy8Test();

	Swap1Test();
	Swap2Test();
	Swap3Test();

	return 0;
}




static void FlipDigitsInNumTest()
{
	int test_arr[] = {1234, -123, 0, 987654321, 123456789, 11000, -211};
	int exp_arr_[] = {4321, -321, 0, 123456789, 987654321, 11, -112};
	size_t arr_size = sizeof(test_arr) / sizeof(test_arr[0]);
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
		if (FlipDigitsInNum(test_arr[i]) != exp_arr_[i])
		{
			printf("FlipDigitsInNum Test #%ld failed. tested: %d,\t\t actual: %d,\t\t expected: %d.\n", i + 1, test_arr[i], FlipDigitsInNum(test_arr[i]), exp_arr_[i]);
		}
	}
	
}

static void ByteMirrorTest()
{
	const int input1_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 68, 0};
	const int exp_res_arr[] = {128, 64, 192, 32, 160, 96, 224, 16, 144, 34, 0};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		if (ByteMirror(input1_arr[i]) != exp_res_arr[i])
		{
			printf("ByteMirror Test #%ld failed. tested: %d,\t\t actual: %d,\t\t expected: %d.\n", i + 1, input1_arr[i], ByteMirror(input1_arr[i]), exp_res_arr[i]);
		}
	}
	
	return;		
}

static void FlipBitTest()
{
	const int input1_arr[] = {0x00000001, 0x00000001, 0x00000001, 0x00000001, 0xFFFFFFFF, 0xD0000001};
	const int input2_arr[] = {1, 31, 15, 0, 31, 18};
	const int exp_res_arr[] = {0x00000003, 0x80000001, 0x00008001, 0x00000000, 0x7FFFFFFF, 0xD0040001};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		if (FlipBit(input1_arr[i], input2_arr[i]) != exp_res_arr[i])
		{
			printf("FlipBit Test #%ld failed. tested: %x, with n %d, actual: %x,\t expected: %x.\n", i + 1, input1_arr[i], input2_arr[i], FlipBit(input1_arr[i], input2_arr[i]), exp_res_arr[i]);
		}
	}
	
	return;		
}

static void  CountBitsInByteTest()
{
	unsigned char input1_arr[] = {0x0F, 0x8F, 0xF8, 0x00, 0x10, 0xDF, 0x44, 0x95};
	size_t exp_res_arr[] = {4, 5, 5, 0, 1, 7, 2, 4};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		if (CountBitsInByte(input1_arr[i]) != exp_res_arr[i])
		{
			printf("CountBits Test #%ld failed. tested: %x, actual: %ld,\t expected: %ld.\n", i + 1, input1_arr[i], CountBitsInByte(input1_arr[i]), exp_res_arr[i]);
		}
	}
	
	return;		
}

static void RotateLeftTest()
{
	const char input1_arr[] = {0x01, 0x00, 0x71, 0x01, 0x2F, 0x01,};
	const unsigned int input2_arr[] = {1, 31, 15, 0, 31, 3};
	const char exp_res_arr[] = {0x02, 0x00, -0x48, 0x01, -0x69, 0x08,};
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		if (RotateLeft(input1_arr[i], input2_arr[i]) == exp_res_arr[i])
		{
			printf("RotateLeft Test #%ld failed. tested: %x, with n %d, actual: %d,\t expected: %d.\n", i + 1, input1_arr[i], input2_arr[i], RotateLeft(input1_arr[i], input2_arr[i]), exp_res_arr[i]);
		}
	}
	
	return;	
}

static void SwapPointersTest()
{
	int input1_arr[] = {0, 5243, -1532143, 1, 15, -100,};
	int input2_arr[] = {1, -3, 17, 0, 10, 9, -2011056};
	int *p1 = NULL;
	int *p2 = NULL;
	int *tp1 = NULL;
	int *tp2 = NULL;
	size_t arr_size = sizeof(input1_arr) / sizeof(input1_arr[0]);
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		p1 = &input1_arr[i];
		p2 = &input2_arr[i];
		
		tp1 = p1;
		tp2 = p2;
		
		SwapPointers(&p1, &p2);
		
		if (tp2 != p1 || tp1 != p2)
		{
			printf("SwapPointers Test #%ld failed. \nValue 1: %d, p1: %p, pp1: %p\nValue 2: %d, p2: %p, pp2: %p\n", i + 1, input1_arr[i], (void *)p1, (void *)&p1, input2_arr[i], (void *)p2, (void *)&p2);
		}
	}
	
	return;		
}

static void StrlenTest()
{
	const char *test_strs[] = {"abcdaaaaaaaa", "abcde", "", "0", "abcdef"};
	size_t arr_size = sizeof(test_strs) / sizeof(test_strs[0]);
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		if (Strlen(test_strs[i]) != strlen(test_strs[i]))
		{
			printf("Strlen Test #%ld failed. tested: '%s', actual: %ld, expacted: %ld.\n", i + 1, test_strs[i], Strlen(test_strs[i]), strlen(test_strs[i]));
		}
	}
	
	return;	
}

static void StrcmpTest()
{
	const char *test_strs1[] = {"abcdaaaaaaaa", "abcde", "", "0", "abcdef", "abcDe"};
	const char *test_strs2[] = {"gdabcdaaaaazaa", "Abcde", "", "0", "abcAdef", "abcD"};
	size_t arr_size = sizeof(test_strs1) / sizeof(test_strs1[0]);
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		if (Strcmp(test_strs1[i], test_strs2[i]) != strcmp(test_strs1[i], test_strs2[i]))
		{
			printf("Strcmp Test #%ld failed. tested: '%s' = '%s', actual: %d, expacted: %d.\n", i + 1, test_strs1[i], test_strs2[i],  Strcmp(test_strs1[i], test_strs2[i]), strcmp(test_strs1[i], test_strs2[i]));
		}
	}
	
	return;	
}


static void StrcpyTest()
{
	const char *test_strs[] = {"abcdaaaaaaaa", "abcde", "", "0", "abcdef"};
	size_t arr_size = sizeof(test_strs) / sizeof(test_strs[0]);
	size_t i = 0;
	char arr_to_cpy[50] = {0};
	char *cpy_str_p = NULL;

	for (i = 0; i < arr_size; ++i)
	{
		cpy_str_p = Strcpy(arr_to_cpy, test_strs[i]);
		if (cpy_str_p != arr_to_cpy || 0 != Strcmp(arr_to_cpy, test_strs[i]))
		{
			printf("Strcpy Test #%ld failed.\n", i + 1);
		}
	}
	return;
}

static void StrncpyTest()
{
	const char *test_strs[] = {"abcd", "abcde", "", "0", "abcdef"};
	const char *test_strs_bk[] = {"abcd", "abcde", "", "0", "abcdef"};
	const size_t test_n[] = {2, 7, 10, 8, 6};
	size_t arr_size = sizeof(test_strs) / sizeof(test_strs[0]);
	size_t i = 0;
	char buff[100] = {0};
	char *cpy_str_p = NULL;
	char *cpy_str_p_bk = NULL;
	
	for (i = 0; i < arr_size; ++i)
	{
			cpy_str_p = Strncpy(buff, test_strs[i], test_n[i]);
			cpy_str_p_bk = strncpy(buff, test_strs_bk[i], test_n[i]);

			if (cpy_str_p != cpy_str_p_bk)
			{
				printf("Strncpy Test #%ld failed.\n", i + 1);
			}
	}
	return;
}

static void StrcatTest()
{
	char test_strs1[][20] = {"abc", "", "hello_g", "ABC", "xyz", "fshkl467ufhl", "", ""};
	const char *test_strs2[] = {"defg", "", "hello_g", "ABC", "xyz", "fshkl467ufhl", "", ""};
	const size_t arr_size = sizeof(test_strs1) / sizeof(test_strs1[0]);
	size_t i = 0;
	char *cpy_str_p = NULL;

	for (i = 0; i < arr_size; ++i)
	{
		cpy_str_p = Strcat(test_strs1[i], test_strs2[i]);
		
		if(0 != Strcmp(cpy_str_p, strcat(test_strs1[i], test_strs2[i])))
		{
			printf("Strncpy Test #%ld failed.\n", i + 1);
		}
	}
	
	return;
}

static void GetNFibonacciElementTest()
{
	unsigned int test_arr[] = {1, 2, 3, 4, 5, 6, 10, 20, 30, 40, 90};
	unsigned long exp_arr[] = {1, 1, 2, 3, 5, 8, 55, 6765, 832040, 102334155, 2880067194370816120};
	size_t arr_size = sizeof(test_arr) / sizeof(test_arr[0]);
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		if (GetNFibonacciElement(test_arr[i]) != exp_arr[i])
		{
			printf("GetNFibonacciElement Test #%ld failed. n: %d, actual: %ld, expacted: %ld.\n", i + 1, test_arr[i], GetNFibonacciElement(test_arr[i]), exp_arr[i]);
		}
	}
	
	return;	
}

static void IntToStringTest()
{
	const int test_arr[] = {0, -4567, -12343, -1, 1, 1006, 546110};
	char *exp_arr[] = {"0", "-4567", "-12343", "-1", "1", "1006", "546110"}; 
	size_t arr_size = sizeof(test_arr) / sizeof(test_arr[0]);
	size_t i = 0;
	char str_test[12] = {0};

	for (i = 0; i < arr_size; ++i)
	{
		if (0 != Strcmp(IntToString(test_arr[i], str_test), exp_arr[i]))
		{
			printf("IntToString Test #%ld failed. int: %d, actual: '%s', expacted: '%s'.\n", i + 1, test_arr[i], IntToString(test_arr[i], str_test), exp_arr[i]);
		}
	}
	
	return;	
}

static void MultiPlyBy8Test()
{
	const int test_arr[] = {0, -4567, -12343, -1, 1, 1006, 546110};
	const long exp_arr[] = {0, -36536, -98744, -8, 8, 8048, 4368880}; 
	size_t arr_size = sizeof(test_arr) / sizeof(test_arr[0]);
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		if (MultiPlyBy8(test_arr[i]) != exp_arr[i])
		{
			printf("MultiPlyBy8 Test #%ld failed. test: %d, actual: %ld, expacted: %ld.\n", i + 1, test_arr[i], MultiPlyBy8(test_arr[i]), exp_arr[i]);
		}
	}
	
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
