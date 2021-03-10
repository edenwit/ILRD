#include <stdio.h> /* size_t */
#include <assert.h> /* assert */

size_t StrLen(const char *s)
{
	assert (s != NULL);
	size_t i = 0;
	
	while(*(s + i) != 0)
	{
		++i;
	}
	
	return i;
}

int StrCmp(const char *s1, const char *s2)
{
	assert (s1 != NULL && s1 != NULL);
	while( 0 != *s1 || 0 != *s2)	
	{
		if( *s1 - *s2 != 0)
		{
			return *s1 - *s2;
		}
		++s1; ++s2;
	}
	
	return 0;
}
