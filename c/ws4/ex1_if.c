/* developer: Eden Wittenberg
    status: ---
    date: 17.03.2021
    description: print directly to screen by if\else methods
    
*/

#include <stdio.h> /* printf */
#include <stdlib.h>  /* system */
#include <ctype.h> /* toupper */

void WwpIf();
void WwpSwitch();
void WwpLut();


int main()
{
	printf("Presses with IF / ELSE:\n");
	WwpIf();
	
	printf("\nPresses with SWITCH / CASE:\n");
	WwpSwitch();	

	printf("\nPresses with LOOKUP TABLE:\n");
	WwpLut();
	return 0;	
}

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
