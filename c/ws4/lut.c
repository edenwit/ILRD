/* developer: Eden Wittenberg
    status: Approved by Nir
    date: 18.03.2021
    description: print directly to screen by if\else / switch / lut methods
    
*/

#include "lut.h" /* StrLen, StrCmp */

void WwpIf()
{
	int ch = 0;
	system("stty -icanon -echo");
	while (27 != ch)	
	{
		ch = toupper(getchar());
	
		if('A' == ch)
		{
			printf("A was pressed.\n");
		}
		else if('T' == ch)
		{
			printf("T was pressed.\n");
		}
	}
	system("stty icanon echo");
	
	return;
}

void WwpSwitch()
{
	int ch = 0;
	system("stty -icanon -echo");
	while (27 != ch)	
	{
		ch = toupper(getchar());
	
		switch(ch)
		{
			case 'A':
				printf("A was pressed.\n");
				break;
			case 'T':
				printf("T was pressed.\n");
				break;
		}
	}
	system("stty icanon echo");
	
	return;
}

void WwpLut()
{
	int ch = 0;
	size_t i = 0;
	void (* arr[256])(int);
	size_t n = sizeof(arr) / sizeof(arr[0]);
	for (i = 0; i < n; ++i)
	{
		arr[i] = DoNothing;
	}
	arr['A'] = PrintAT;
	arr['T'] = PrintAT;

	system("stty -icanon -echo");
	
	while (27 != ch)	
	{
		ch = toupper(getchar());
		arr[ch](ch);
	}
	system("stty icanon echo");
	return;
}

void DoNothing()
{
	return;
}

void PrintAT(int ch)
{
	printf("%c was pressed.\n",ch);
	return;
}
