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
	assert (s1 != NULL && s1 != NULL);
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

char *StrCpy(char *dest, const char *src)
{
	char *cur_dest = dest;
	
	while ('\0' != *src)
	{
		*cur_dest = *src;
		++src;
		++cur_dest;
	}
	
	*cur_dest = '\0';
	
	return dest;
}

char *StrNCpy(char *dest, const char *src, size_t n)
{
	char *cur_dest = dest;
	const char *final_dest = dest + n;

	while ('\0' != *src && final_dest != cur_dest)
	{
		*cur_dest = *src;
		++src;
		++cur_dest;
	}
	
	if ('\0' == *src)
	{
		*cur_dest = '\0';
	}
	
	while (final_dest != cur_dest)
	{
		*cur_dest = '\0';
		++cur_dest;
	}

	return dest;
}
