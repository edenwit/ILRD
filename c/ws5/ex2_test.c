#include <stdio.h> /* printf */
#include "ex2.h"

int main(int argc, char **argv)
{
	if (2 != argc)
	{
		printf("Please add 1 argument only, containing the file name.\n");
		return 1;
	}	
	printf("File name: %s.\n", argv[1]);
	
	Log(argv[1]);
	
	return 0;
}
