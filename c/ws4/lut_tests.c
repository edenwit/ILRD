#include <stdio.h> /* printf */
#include "lut.h" /* WwpIf, WwpSwitch, WwpLut */

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
