#include <stdio.h> /* printf */
#include "ilrd_strings.h" /* StrLen, StrCmp */


int main()
{
	char str_test_1[] = "Eden";
	char str_test_2[] = "eden";	
	char str_test_3[] = ""	  ;		
	char str_test_4[] = "E";		
	char str_test_5[] = "0";
	char str_test_6[] = "Eden W";
	int size_res_test[]={-32,-69,-21,100,-48,-32};
	int cmp_result = 0;
	
	printf("Str1: \"%s\"\t | Str1 len: %zu\t, Str2: \"%s\"\t | Str2 len:  %zu\n",str_test_1,StrLen(str_test_1),str_test_2,StrLen(str_test_2));
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
	printf("Str1: \"%s\"\t | Str1 len: %zu\t, Str2: \"%s\"\t | Str2 len: %zu\n",str_test_3,StrLen(str_test_3),str_test_4,StrLen(str_test_4));
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
	printf("Str1: \"%s\"\t | Str1 len: %zu\t, Str2: \"%s\"\t | Str2 len: %zu\n",str_test_5,StrLen(str_test_5),str_test_6,StrLen(str_test_6));
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
	printf("Str1: \"%s\"\t | Str1 len: %zu\t, Str2: \"%s\"\t | Str2 len: %zu\n",str_test_1,StrLen(str_test_1),str_test_4,StrLen(str_test_4));
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
	printf("Str1: \"%s\"\t | Str1 len: %zu\t, Str2: \"%s\"\t | Str2 len: %zu\n",str_test_3,StrLen(str_test_3),str_test_5,StrLen(str_test_5));
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
	printf("Str1: \"%s\"\t | Str1 len: %zu\t, Str2: \"%s\"\t | Str2 len: %zu\n",str_test_1,StrLen(str_test_1),str_test_6,StrLen(str_test_6));
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
	printf("Test For NULL value: len: %zu\t, Str2: \"%s\"\t | Str2 len: %zu\n",StrLen(NULL),str_test_6,StrLen(str_test_6));
	cmp_result = StrCmp(NULL, str_test_6);
	printf("Compare result: %d. Expected: %d.",cmp_result, size_res_test[5]);
	if(cmp_result == size_res_test[5])
	{
		printf("Success!\n");
	}
	else
	{
		printf("Failure!\n");
	}
	return 0;
}

