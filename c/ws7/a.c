#include "g.h"

void Foo()
{
	printf("foo: %d\n", g_s);
	++g_s;
	printf("foo: %d\n", g_s);
	return;
}
