#include <stdio.h> /* scanf, fprintf */
#include <assert.h> /* assert */

#define STR_MAX 256
#define STRUCT_STR_SIZE 8
#define ARR_SIZE 10


int main(int argc, char **argv)
{
	char str[STR_MAX] = {0};
	size_t i = 0;
	FILE *f = NULL;

	assert(NULL != argv[1]);
	
	printf ("argc: %s\n",argv[1]);
	for (i = 0; i < ARR_SIZE; ++i)
	{
		printf("Enter string (up to %d characters):\n", STR_MAX);
		f = fopen(argv[1], "a");
		assert(NULL != f);
	    fgets(str, STR_MAX, stdin);
		fprintf(f, "%s",str);
		fclose(f);
	}	

	return 0;
}
