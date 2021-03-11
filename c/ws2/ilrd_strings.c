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

char *StrCpy(char *dest, const char *src)
{
	char *cur_dest = dest;
	
	assert (NULL != dest && NULL != src);
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

	assert (NULL != dest && NULL != src);
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

int StrCaseCmp(const char *s1, const char *s2)
{
	assert (NULL != s1 && NULL != s1);
	while ( 0 != *s1 || 0 != *s2)	
	{
		if (((90 >= *s1 && 65 <= *s1) && (*s1 - *s2 != 0) && (*s1 - *s2 != -32)) || ((90 >= *s2 && 65 <= *s2) && (*s1 - *s2 != 0) && (*s1 - *s2 != 32)))
		{
			return *s1 - *s2;
		}
		++s1;
		++s2;
	}
	return 0;
}

char *StrChr(const char *s, int c)
{
	assert (NULL != s);
	while ( '\0' != *s)	
	{
		if (c == *s)
		{
			return (char *)s;
		}
		++s;
	}
	if ('\0' == c)
	{
		return (char *)s;
	}
	return '\0';
}

char *StrDup(const char *s)
{	
	size_t length = StrLen(s) + 1;
    char *new_str = (char *)malloc(length * sizeof(char));
	assert(NULL != s && NULL != new_str);
	
	while( '\0' != *s)
    {
    	*new_str = *s;
		++new_str;
		++s;
    }
    *new_str = '\0';
    
    return new_str - (length - 1) ;
}

char *StrCat(char *dest, const char *src)
{	
    char *p = dest + StrLen(dest);

	assert(NULL != dest && NULL != src);
	
	while( '\0' != *src)
    {
    	*p = *src;
		++p;
		++src;

    }
    *p = '\0';
    
    return dest;
}

char *StrNCat(char *dest, const char *src, size_t n)
{
	char *cur_dest = dest + StrLen(dest) ;
	const char *final_dest = cur_dest + n ;

	assert (NULL != dest && NULL != src);
	
	while ('\0' != *src && final_dest != cur_dest)
	{
		*cur_dest = *src;
		++src;
		++cur_dest;
	}
	*cur_dest = '\0';

	return dest;
}
