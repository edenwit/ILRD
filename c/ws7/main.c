#include <stdio.h>
#include "g.h"

int main()
{
	printf("main: %d\n", g_s);
	Foo();
	printf("main: %d\n", g_s);
	return 0;
}

