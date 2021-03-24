/* developer: Eden Wittenberg
    status: Approved by Nir
    date: 18.03.2021
    description: print directly to screen by if\else / switch / lut methods
    
*/

#include "lut.h" /* StrLen, StrCmp */
#define ESC 27
#define SIZE 256

static void DoNothing();
static void PrintA();
static void PrintT();

void WwpIf()
{
	unsigned char ch = 0;
	system("stty -icanon -echo");
	while(EOF != ch && ESC != ch)
	{
		ch = toupper(getchar());
	
		if('A' == ch)
		{
			printf("A pressed.\n");
		}
		else if('T' == ch)
		{
			printf("T pressed.\n");
		}
	}
	system("stty icanon echo");
	
	return;
}

void WwpSwitch()
{
	unsigned char ch = 0;
	system("stty -icanon -echo");
	while(EOF != ch && ESC != ch)
	{
		switch(ch)
		{
			case 'A':
			{
				printf("A pressed.\n");
				break;
			}
			case 'T':
			{
				printf("T pressed.\n");
				break;
			}
			default:
			{
				break;
			}
		}
	}
	system("stty icanon echo");
	
	return;
}

void WwpLut()
{
	unsigned char ch = 0;
	size_t i = 0;
	static void (* arr[SIZE])() = {NULL};
	size_t n = sizeof(arr) / sizeof(arr[0]);
	
	for (i = 0; i < n; ++i)
	{
		arr[i] = DoNothing;
	}
	
	arr['A'] = PrintA;
	arr['T'] = PrintT;

	system("stty -icanon -echo");
	
	while(EOF != ch && ESC != ch)
	{
		ch = toupper(getchar());

		arr[ch](ch);
	}
	system("stty icanon echo");
	return;
}

static void DoNothing()
{
	return;
}

static void PrintA()
{
	printf("A pressed.\n");
	return;
}

static void PrintT()
{
	printf("T pressed.\n");
	return;
}
