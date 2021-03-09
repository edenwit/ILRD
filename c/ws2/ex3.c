#include <stdio.h> 						
#include <stdlib.h>

int main ()
{
	static int s_i = 7;
	printf("static s_i: %p\n", &s_i);
	int i = 7;
	printf("i: %p\n", &i);
	int *ptr = &i;
	printf("ptr: %p\n", &ptr);
	int *ptr2 = (int *)malloc(sizeof(int));
	printf("ptr2: %p\n", &ptr2);
	if(ptr)
	{
		&ptr;
		printf("ptr: %p\n", &ptr);
	}
	
	free(ptr2);
	printf("ptr2: %p\n", &ptr2);
	
	return 0;
}
