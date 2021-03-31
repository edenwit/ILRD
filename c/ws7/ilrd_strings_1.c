#include "ilrd_strings.h" /* StrLen, StrCmp */

size_t StrLen(const char *s)
{
	size_t i = 0;

	assert (s != NULL);
	while(*(s + i) != 0)
	{
		++i;
	}
	
	return i;
}

int StrCmp(const char *s1, const char *s2)
{
	assert (NULL != s1 && NULL != s1);
	while( 0 != *s1 || 0 != *s2)	
	{
		if( *s1 - *s2 != 0)
		{
			return *s1 - *s2;
		}
		++s1;
		++s2;
	}
	
	return 0;
}
