#include <stdio.h> /* printf */
#include "ilrd_strings.h" /* StrLen, StrCmp */

static void StrCpyTest();
static void StrNCpyTest();

int main()
{
	char str_test_1[] = "Eden";
	char str_test_2[] = "eden";	
	char str_test_3[] = ""	  ;		
	char str_test_4[] = "E";		
	char str_test_5[] = "0";
	char str_test_6[] = "Eden W";
	int size_res_test[] = {-32, -69, -21, 100, -48, -32};
	int cmp_result = 0;
	
	printf("Str1: \"%s\"\t | Str1 len: %lu\t, Str2: \"%s\"\t | Str2 len:  %lu\n",str_test_1,StrLen(str_test_1),str_test_2,StrLen(str_test_2));
	cmp_result = StrCmp(str_test_1, str_test_2);
	printf("Compare result: %d. Expected: %d.",cmp_result, size_res_test[0]);
	if(cmp_result == size_res_test[0])
	{
		printf("Success!\n");
	}
	else
	{
		printf("Failure!\n");
	}
	printf("Str1: \"%s\"\t | Str1 len: %lu\t, Str2: \"%s\"\t | Str2 len: %lu\n",str_test_3,StrLen(str_test_3),str_test_4,StrLen(str_test_4));
	cmp_result = StrCmp(str_test_3, str_test_4);
	printf("Compare result: %d. Expected: %d.",cmp_result, size_res_test[1]);
	if(cmp_result == size_res_test[1])
	{
		printf("Success!\n");
	}
	else
	{
		printf("Failure!\n");
	}	
	printf("Str1: \"%s\"\t | Str1 len: %lu\t, Str2: \"%s\"\t | Str2 len: %lu\n",str_test_5,StrLen(str_test_5),str_test_6,StrLen(str_test_6));
	cmp_result = StrCmp(str_test_5, str_test_6);
	printf("Compare result: %d. Expected: %d.",cmp_result, size_res_test[2]);
	if(cmp_result == size_res_test[2])
	{
		printf("Success!\n");
	}
	else
	{
		printf("Failure!\n");
	}	
	printf("Str1: \"%s\"\t | Str1 len: %lu\t, Str2: \"%s\"\t | Str2 len: %lu\n",str_test_1,StrLen(str_test_1),str_test_4,StrLen(str_test_4));
	cmp_result = StrCmp(str_test_1, str_test_4);
	printf("Compare result: %d. Expected: %d.",cmp_result, size_res_test[3]);
	if(cmp_result == size_res_test[3])
	{
		printf("Success!\n");
	}
	else
	{
		printf("Failure!\n");
	}	
	printf("Str1: \"%s\"\t | Str1 len: %lu\t, Str2: \"%s\"\t | Str2 len: %lu\n",str_test_3,StrLen(str_test_3),str_test_5,StrLen(str_test_5));
	cmp_result = StrCmp(str_test_3, str_test_5);
	printf("Compare result: %d. Expected: %d.",cmp_result, size_res_test[4]);
	if(cmp_result == size_res_test[4])
	{
		printf("Success!\n");
	}
	else
	{
		printf("Failure!\n");
	}	
	printf("Str1: \"%s\"\t | Str1 len: %lu\t, Str2: \"%s\"\t | Str2 len: %lu\n",str_test_1,StrLen(str_test_1),str_test_6,StrLen(str_test_6));
	cmp_result = StrCmp(str_test_1, str_test_6);
	printf("Compare result: %d. Expected: %d.",cmp_result, size_res_test[5]);
	if(cmp_result == size_res_test[5])
	{
		printf("Success!\n");
	}
	else
	{
		printf("Failure!\n");
	}
	/*printf("Test For NULL value: len: %lu\t, Str2: \"%s\"\t | Str2 len: %lu\n",StrLen(NULL),str_test_6,StrLen(str_test_6));
	cmp_result = StrCmp(NULL, str_test_6);
	printf("Compare result: %d. Expected: %d.",cmp_result, size_res_test[5]);
	if(cmp_result == size_res_test[5])
	{
		printf("Success!\n");
	}
	else
	{
		printf("Failure!\n");
	}*/
	
	StrCpyTest();
	StrNCpyTest();
	return 0;
	
}

static void StrCpyTest()
{
	const char *test_strs[] = {"check","","0"};
	size_t arr_size = sizeof(test_strs) / sizeof(test_strs[0]);
	size_t i = 0;
	char arr_to_cpy[6] = {0};
	char *cpy_str_p = NULL;
	
	printf("\n\n-----------StrCpy-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		printf("Input  str: \"%s\"\n", test_strs[i]);
	
		cpy_str_p = StrCpy(arr_to_cpy, test_strs[i]);
	
		printf("Output str: \"%s\" , from pointer: \"%s\"\n", arr_to_cpy, cpy_str_p);
	
		if (cpy_str_p == arr_to_cpy && 0 == StrCmp(arr_to_cpy, test_strs[i]))
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

static void StrNCpyTest()
{
	const char *test_strs[] = {"abcd", "abcde", "", "0", "abcdef"};
	const size_t test_n[] = {2, 7, 10, 8, 6};
	const char *exp_res[] = {"ab", "abcde\0", "\0\0\0\0\0\0\0\0\0", "0\0\0\0\0\0\0", "abcdef"};
	size_t arr_size = sizeof(test_strs) / sizeof(test_strs[0]);
	size_t i = 0;
	char buff[10] = {0};
	char *cpy_str_p = NULL;
	
	printf("\n\n-----------StrNCpy-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
			printf("Input  str: \"%s\"\n", test_strs[i]);
	
			cpy_str_p = StrNCpy(buff, test_strs[i], test_n[i]);
	
			printf("Output str: \"%s\" , n: \"%lu\"\n", buff, test_n[i]);
	
			if (cpy_str_p == buff && 0 == StrCmp(buff, exp_res[i]))
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
