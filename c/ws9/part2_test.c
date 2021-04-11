#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */

#include "part2.h"

static void ItoATest();	

int main()
{
	ItoATest();
	
	return 0;
}

static void ItoATest()
{
	char *str = malloc(12);
	int nums[] = {1, 0, -1, 20000000, -20000000};
	size_t size_of_arr = sizeof(nums) / sizeof(nums[0]); 
	size_t i = 0;
	int base = 10;
	
	for (i = 0; i < size_of_arr; ++i)
	{
		str = ItoA(nums[i], str, 10);
		printf("string #%ld from number %d base %d: '%s'\n",i ,nums[i], base, str);	
	}
	return;
}
