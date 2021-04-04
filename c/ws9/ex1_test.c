#include <stdio.h>
#include <string.h>

#include "ex1.h"

/*static void printArr(char *arr, size_t arr_size);*/

static void TestMemSet();

int main()
{
	TestMemSet();
	
	return 0;
}

static void TestMemSet()
{
	char str[] = "testing the str and expacting good things\n";
	char *p_char = str;
	size_t str_size = strlen(str);
	int c_to_pass = 'c';
	
	printf("str size: %ld\n", str_size);
	printf("%s\n", p_char);
	p_char = MemSet(p_char, c_to_pass, 3);
	printf("%s\n", p_char);
	
	return;
}

/*static void printArr(char *arr, size_t arr_size)
{
	while (0 < arr_size)
	{
		printf("%c", (arr));
		--arr_size;
		++arr;
	}

	return;
}
*/
