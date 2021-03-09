#include <stdio.h>
#include "ilrd_strings.h"

int main()
{
	char str_test_1[]  = "Eden";	char str_cmp_2[] = "eden";	
	char str_test_3[]  = ""	  ;		char str_cmp_4[] = "eden";
	char str_test_5[]  = "E";		char str_cmp_6[] = "eden";
	char str_test_7[]  = "Eden";	char str_cmp_8[] = "";
	char str_test_9[]  = ""	  ;		char str_cmp_10[] = "";
	char str_test_11[] = "Eden";	char str_cmp_12[] = "Edenwittenberg";
	
	printf("Str1: \"%s\"\t\t\t\t | Str1 len: %zu\n",str1,StrLen(str1));
	printf("Str2: \"%s\"\t\t\t\t | Str2 len: %zu\n",str2,StrLen(str2));
	printf("Compare result: %d\n", StrCmp(str1, str2));
	return 0;
}

