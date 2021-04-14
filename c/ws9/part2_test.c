#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, strtol */
#include <stdint.h> /* uint16_t */

#include "part2.h"

/* approved by eden girl */
#define IS_LITTLE_ENDIAN (*(uint16_t *)"\0\1" >> 8)


static void ItoaBaseTil36Test();	
static void AtoITest();
static void IsLittleEndianTest();
static void IsLittleEndianMacroTest();
static void AtoiBaseTil36Test();
static void PrintFirstAndSecondTest();
static void PrintCharArray(char *arr, size_t size);

int main()
{
	ItoaBaseTil36Test();
	AtoITest();
	AtoiBaseTil36Test();
	PrintFirstAndSecondTest();
	IsLittleEndianTest();
	IsLittleEndianMacroTest();
	
	return 0;
}

static void ItoaBaseTil36Test()
{
	char *str = malloc(15);
	int nums[] = {1, 0, -1, 20000001, -2000001};
	size_t size_of_arr = sizeof(nums) / sizeof(nums[0]); 
	size_t i = 0;
	int base = 30;
	
	printf("\n----------Test for ItoaBaseTil36Test---------------- \n\n");
	
	for (i = 0; i < size_of_arr; ++i)
	{
		str = ItoaBaseTil36(nums[i], str, 16);
		printf("string #%ld from number %d base %d: '%s'\n",i ,nums[i], base, str);	
	}
	return;
}

static void AtoITest()
{
	char *str_tests[] = {"1", "0", "-1", "20000001", "-2000001", "200g13031"};
	int exp_nums[] = {1, 0, -1, 20000001, -2000001, 200};
	int num_test = 0;
	size_t size_of_arr = sizeof(exp_nums) / sizeof(exp_nums[0]); 
	size_t i = 0;
	int base = 10;
	
	printf("\n----------Test for AtoITest---------------- \n\n");	
	for (i = 0; i < size_of_arr; ++i)
	{
		num_test = AtoiBase10(str_tests[i]);
		printf("number #%ld from string '%s' base %d: %d, expected: %d.\n",i ,str_tests[i], base, num_test, exp_nums[i]);	
	}
	return;
}

static void AtoiBaseTil36Test()
{
	char *str_tests[] = {"1", "0", "-1", "20$000001", "-2000001", "ABCDEFG"};
	size_t size_of_arr = sizeof(str_tests) / sizeof(str_tests[0]); 
	size_t i = 0;
	int base = 36;
	
	printf("\n----------Test for AtoiBaseTil36Test---------------- \n\n");	
	for (i = 0; i < size_of_arr; ++i)
	{
		printf("test #%ld for string '%s' base %d: my result:%d, original func result: %d.\n",i ,str_tests[i], base, AtoiBaseTil36(str_tests[i], base) ,(int)(strtol(str_tests[i], NULL, base)));	
	}
	return;
}


static void IsLittleEndianTest()
{
	printf("\n----------Test for IsLittleEndian---------------- \n\n");	
	printf ("Little endian: %d!\n", IsLittleEndian());
	
	return;
}

static void IsLittleEndianMacroTest()
{
	printf("\n----------Test for IsLittleEndianMacro---------------- \n\n");	
	printf ("Little endian: %d!\n", IS_LITTLE_ENDIAN);
	
	return;
}

static void PrintFirstAndSecondTest()
{
		char chr_arr_test_1[][6] = {{'a','b','c','d','e','f'},{'a','b','0','d','e','f'},{'a','b','c','d','4','f'},{'0','1','T','d','e','f'}};
		char chr_arr_test_2[][6] = {{'a','b','c','d','e','f'},{'a','0','c','d','e','f'},{'1','2','3','4','e','f'},{'1','0','T','d','e','f'}};
		char chr_arr_test_3[][6] = {{'a','x','c','d','e','f'},{'a','f','0','0','0','\0'},{'0','0','0','1','1','1'},{'1','0','c','d','e','f'}};
		size_t i = 0;
		size_t size_of_arr = sizeof(chr_arr_test_1) / sizeof(chr_arr_test_1[0]); 
		
		printf("\n----------Test for PrintFirstAndSecond---------------- \n\n");	
		for (i = 0; i < size_of_arr; ++i)
		{
			printf("test #%ld for arrays: \n", i + 1);
			PrintCharArray(chr_arr_test_1[i], 6);
			printf("\n");
			PrintCharArray(chr_arr_test_2[i], 6);
			printf("\n");
			PrintCharArray(chr_arr_test_3[i], 6);
			printf("\n printed: \n");
			PrintFirstAndSecond(chr_arr_test_1[i], 6, chr_arr_test_2[i], 6, chr_arr_test_3[i], 6);
		}
		return;
		
}

static void PrintCharArray(char *arr, size_t size)
{
	while (0 < size)
	{
		printf("%c", *arr);
		++arr;
		--size;
	}
	
	return;
}

