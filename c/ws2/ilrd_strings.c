#include <stdio.h>

size_t StrLen(char *s)
{
	size_t i = 0;
	
	while(*(s + i) != 0)
	{
		++i;
	}
	
	return i;
}

int StrCmp(char *s1, char *s2)
{
	size_t i = 0;
	
	while(*(s1 + i) != 0 || *(s2 + i) != 0)	
	{
		if( *(s1 + i) - *(s2 + i) !=0)
		{
			return *(s1 + i) - *(s2 + i);
		}
		++i;
	}
	
	return 0;
}
