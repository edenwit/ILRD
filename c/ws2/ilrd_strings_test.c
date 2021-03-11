#include <stdio.h> /* printf */
#include <string.h>
#include "ilrd_strings.h" /* StrLen, StrCmp */

static void StrCpyTest();
static void StrNCpyTest();
static void StrCaseCmpTest();
static void StrChrTest();
static void StrDupTest();
static void StrCatTest();
static void StrNCatTest();

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
	StrCaseCmpTest();
	StrChrTest();
	StrDupTest();
	StrCatTest();
	StrNCatTest();
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

static void StrCaseCmpTest()
{
	const char *test_strs_1[] = {"abcd", "aBc", "AbCDE", ""};
	const char *test_strs_2[] = {"Abcd", "abc", "ABC", "0"};
	const int exp_res[] = {0, 0, 68, 111};
	size_t arr_size = sizeof(test_strs_1) / sizeof(test_strs_1[0]);
	size_t i = 0;
	int cmp_result = 0;
	
	printf("\n\n-----------StrCaseCmp-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		printf("Str1: \"%s\"\t | Str1 len: %lu\t, Str2: \"%s\"\t | Str2 len: %lu\n",test_strs_1[i], StrLen(test_strs_1[i]), test_strs_2[i], StrLen(test_strs_2[i]));
		cmp_result = StrCaseCmp(test_strs_1[i], test_strs_2[i]);
		printf("Compare result: %d. Expected: %d. ",cmp_result, exp_res[i]);
		if(0 == cmp_result)
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

static void StrChrTest()
{
	const char *test_strs[] = {"abc", "", "hello_g", "ABC", "xyz"};
	const char chs[] = {'b', 'a', '_', '\0', 'n'};
	const int exp_res[] = {1, -1, 5, 3, -1};
	size_t arr_size = sizeof(test_strs) / sizeof(test_strs[0]);
	size_t i = 0;
	const char *res = NULL;
	
	printf("\n\n-----------StrChr-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		printf("Str: \"%s\"\t | ch: %c\n",test_strs[i], chs[i]);
		res = StrChr(test_strs[i], chs[i]);
		printf("Compare result: %p. Expected: %p. ",res, test_strs[i] + exp_res[i]);
		if(res == test_strs[i] + exp_res[i])
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

static void StrDupTest()
{
	const char *test_strs[] = {"abc", "", "hello_g", "ABC", "xyz", "fshkl467ufhl", "\0"};
	const size_t arr_size = sizeof(test_strs) / sizeof(test_strs[0]);
	size_t i = 0;
	char *cpy_str_p = NULL;

	printf("\n\n-----------StrDup-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		printf("Str: \"%s\"\n",test_strs[i]);
		
		cpy_str_p = StrDup(test_strs[i]);
		
		printf("Compare result: \"%s\". Expected: \"%s\". ", cpy_str_p, test_strs[i]);
		
		if(0 == StrCmp(test_strs[i], cpy_str_p))
		{
			printf("Success!\n\n");
		}
		else
		{
			printf("Failure!\n\n");
		}
	}
	
	return;
}

static void StrCatTest()
{
	char test_strs1[][20] = {"abc", "", "hello_g", "ABC", "xyz", "fshkl467ufhl", "", ""};
	char test_strs1_bk[][20] = {"abc", "", "hello_g", "ABC", "xyz", "fshkl467ufhl", "", ""};
	const char *test_strs2[] = {"defg", "", "hello_g", "ABC", "xyz", "fshkl467ufhl", "", ""};
	const size_t arr_size = sizeof(test_strs1) / sizeof(test_strs1[0]);
	size_t i = 0;
	char *cpy_str_p = NULL;
	
	printf("\n\n-----------StrCat-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		printf("Str1: \"%s\", Str2: \"%s\"\n",test_strs1[i], test_strs2[i]);
		
		cpy_str_p = StrCat(test_strs1[i], test_strs2[i]);
		
		printf("Compare result: \"%s\". Expected: \"%s%s\". ", cpy_str_p, test_strs1_bk[i], test_strs2[i]);
		
		if(0 == StrCmp(cpy_str_p, strcat(test_strs1[i], test_strs2[i])))
		{
			printf("Success!\n\n");
		}
		else
		{
			printf("Failure!\n\n");
		}
	}
	
	return;
}

static void StrNCatTest()
{
	char test_strs1[][40] = {"abc", "", "hello_g", "ABC", "xyz", "fshkl4hl"};
	char test_strs1_bk[][40] = {"abc", "", "hello_g", "ABC", "xyz", "fshkl4hl"};
	const char *test_strs2[] = {"defg", "", "hello_g", "ABC", "xyz", "fshkl467ufhl"};
	const size_t test_n[] = {2, 7, 10, 8, 6, 0};
	size_t arr_size = sizeof(test_strs1) / sizeof(test_strs1[0]);
	size_t i = 0;
	char *cpy_str_p = NULL;
	
	printf("\n\n-----------StrNCat-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
			printf("Input  str1: \"%s\", Str2: \"%s\", n: %lu\n", test_strs1[i],test_strs2[i], test_n[i]);
	
			cpy_str_p = StrNCat(test_strs1[i], test_strs2[i], test_n[i]);
	
			printf("Compare result: \"%s\". Expected: \"%s"". ", cpy_str_p, strncat(test_strs1_bk[i], test_strs2[i], test_n[i]));
		
			if(0 == StrCmp(cpy_str_p, test_strs1_bk[i]))
			{
				printf("Success!\n\n");
			}
			else
			{
				printf("Failure!\n\n");
			}
	}
	return;
}