#include <stdio.h> /* printf */
#include <string.h>
#include <strings.h>
#include <ctype.h> /* isspace*/
#include "ilrd_strings.h" /* StrLen, StrCmp */

static void StrLenTest();
static void StrCmpTest();
static void StrCpyTest();
static void StrNCpyTest();
static void StrCaseCmpTest();
static void StrChrTest();
static void StrDupTest();
static void StrCatTest();
static void StrNCatTest();
static void StrStrTest();
static void StrSpnTest();
static void IsPalindromeTest();

int main()
{
	StrLenTest();
	StrCmpTest();
	StrCpyTest();
	StrNCpyTest();
	StrCaseCmpTest();
	StrChrTest();
	StrDupTest();
	StrCatTest();
	StrNCatTest();
	StrStrTest();
	StrSpnTest();
	IsPalindromeTest();
	
	return 0;
	
}


static void StrLenTest()
{
	const char *test_strs[] = {"abcd", "abcde", "", "0", "abcdef"};
	size_t arr_size = sizeof(test_strs) / sizeof(test_strs[0]);
	size_t i = 0;
	
	printf("\n\n-----------StrLen-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
			printf("Input  str: \"%s\". Length: %lu\n", test_strs[i],StrLen(test_strs[i]));
			
			if (StrLen(test_strs[i]) == strlen(test_strs[i]))
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


static void StrCmpTest()
{
	const char *test_strs_1[] = {"abcd", "aBc", "AbCDE", ""};
	const char *test_strs_2[] = {"Abcd", "abc", "ABC", "0"};
	size_t arr_size = sizeof(test_strs_1) / sizeof(test_strs_1[0]);
	size_t i = 0;
	int cmp_result = 0;
	
	printf("\n\n-----------StrCaseCmp-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		printf("Str1: \"%s\"\t | Str1 len: %lu\t, Str2: \"%s\"\t | Str2 len: %lu\n",test_strs_1[i], StrLen(test_strs_1[i]), test_strs_2[i], StrLen(test_strs_2[i]));
		
		cmp_result = StrCmp(test_strs_1[i], test_strs_2[i]);
		
		printf("Compare result: %d. Expected: %d. ",cmp_result, strcmp(test_strs_1[i], test_strs_2[i]));
		
		if(cmp_result < 0 && strcmp(test_strs_1[i], test_strs_2[i]) < 0)
		{
			printf("Success!\n");
		}
		else if(cmp_result > 0 && strcmp(test_strs_1[i], test_strs_2[i]) > 0)
		{
			printf("Success!\n");
		}
		else if(cmp_result == 0 && strcmp(test_strs_1[i], test_strs_2[i]) == 0)
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
	size_t arr_size = sizeof(test_strs_1) / sizeof(test_strs_1[0]);
	size_t i = 0;
	int cmp_result = 0;
	
	printf("\n\n-----------StrCaseCmp-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
		printf("Str1: \"%s\"\t | Str1 len: %lu\t, Str2: \"%s\"\t | Str2 len: %lu\n",test_strs_1[i], StrLen(test_strs_1[i]), test_strs_2[i], StrLen(test_strs_2[i]));
		
		cmp_result = StrCaseCmp(test_strs_1[i], test_strs_2[i]);
		
		printf("Compare result: %d. Expected: %d. ",cmp_result, strcasecmp(test_strs_1[i], test_strs_2[i]));
		
		if(cmp_result < 0 && strcasecmp(test_strs_1[i], test_strs_2[i]) < 0)
		{
			printf("Success!\n");
		}
		else if(cmp_result > 0 && strcasecmp(test_strs_1[i], test_strs_2[i]) > 0)
		{
			printf("Success!\n");
		}
		else if(cmp_result == 0 && strcasecmp(test_strs_1[i], test_strs_2[i]) == 0)
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
	
			cpy_str_p = StrnCat(test_strs1[i], test_strs2[i], test_n[i]);
	
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

static void StrStrTest()
{
	char test_strs1[][40] = {"abcd", "", "hello_g", "ABC", "xyz", "fshkl4hl,AbcdEb"};
	char test_strs2[][40] = {"bc", "b", "llop", "C", "xyz", "fshkl4hlp,b"};
	const size_t test_n[] = 	{1, -1, -1, 2, 0, -1, 1};
	size_t arr_size = sizeof(test_strs1) / sizeof(test_strs1[0]);
	size_t i = 0;
	char *cpy_str_p = NULL;
	
	printf("\n\n-----------StrStr-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
			printf("Haystack: \"%s\", needle: \"%s\"\n", test_strs1[i],test_strs2[i]);
	
			cpy_str_p = StrStr(test_strs1[i], test_strs2[i]);
	
			printf("Compare result: \"%p\". Expected: \"%p"". ", cpy_str_p, test_strs1[i] + test_n[i]);
		
			if (test_n[i] == (size_t)-1 && NULL == cpy_str_p)
			{
				printf("Success!\n\n");
			}
			else if (cpy_str_p == test_strs1[i] + test_n[i])
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

static void StrSpnTest()
{
	char test_strs1[][40] = {"babcd"	, ""	, "hello_g"	, "ABC"	, "xyz"	, "fshkl4hl,AbcdEb", "hey friend"};
	char test_strs2[][40] = {"bc"	, "b "	, "hlp"		, "ABC"	, ""	, "fshkl4hlp,b", "he you"};
	size_t arr_size = sizeof(test_strs1) / sizeof(test_strs1[0]);
	size_t i = 0;
	size_t result = 0;
	
	printf("\n\n-----------StrSpn-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
			printf("Str: \"%s\", chars: \"%s\"\n", test_strs1[i],test_strs2[i]);
	
			result = StrSpn(test_strs1[i], test_strs2[i]);
	
			printf("Compare result: \"%lu\". Expected: \"%lu"". ", result, strspn(test_strs1[i], test_strs2[i]));
		
			if (result == strspn(test_strs1[i], test_strs2[i]))
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

static void IsPalindromeTest()
{
	char test_strs1[][40] = {"babcd"	, ""	, "abanibi"	, "ABCCBA"	, "ABCBA"	, "abc c ba", "32546543"};
	const size_t test_n[] = 	{0, 1, 0, 1, 1, 1, 0};
	size_t arr_size = sizeof(test_strs1) / sizeof(test_strs1[0]);
	size_t i = 0;
	size_t result = 0;
	
	printf("\n\n-----------IsPalindrome-------------: \n\n");
	
	for (i = 0; i < arr_size; ++i)
	{
			printf("Str: \"%s\"\n", test_strs1[i]);
	
			result = IsPalindrome(test_strs1[i]);
	
			printf("Compare result: \"%lu\". Expected: \"%lu"". ", result, test_n[i]);
		
			if (result == test_n[i])
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

