#include <stdio.h>

void HelloHex();

int main ()
{
	HelloHex();
	
	return 0;
}

void HelloHex()
{
	char hello_world[] = {0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 			0x64, 0x21, 0x22, 0x00};

	printf("%s\n", hello_world);

	return;
}
