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
	assert (NULL != s1 && NULL != s2);
	
	while ( '\0' != *s1 || '\0' != *s2)	
	{
		if (tolower(*s1) != tolower(*s2))
		{
			return (tolower(*s1) - tolower(*s2));
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
	return NULL;
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
    
    free(new_str - (length - 1));
    
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

char *StrnCat(char *dest, const char *src, size_t n)
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

char *StrStr(const char *haystack, const char *needle)
{
	char *temp_hay = (char *)haystack;
	char *p1 = NULL;
	char *p2 = NULL;
 
 	assert (NULL != haystack && NULL != needle);
 	
	if ('\0' == *needle)
	{
		return temp_hay;
	}
 
	while ('\0' != *temp_hay)
	{
		p1 = temp_hay;
		p2 = (char *)needle;
 
		while ('\0' != *p1 && '\0' != *p2 && 0 != (*p1 - *p2))
		{
			++p1;
			++p2;
		}
 
		if ('\0' != *p2)
		{
			return temp_hay;
		}
		++temp_hay;
	}
 
	return NULL;
}

size_t StrSpn(const char *s, const char *accept)
{
	char *start_s = (char *)s;
	
	assert (NULL != s && NULL != accept);
	
	while ('\0' != *s && StrChr(accept, *s) != NULL)
	{
		++s;
	}
	
	return (s - start_s);
}

int IsPalindrome(const char *str)
{
	const char *rev_p = (str + StrLen(str) - 1);
	
	assert (NULL != str);
	
	while (str < rev_p)
	{
		if (*str != *rev_p)
		{
			return 0;
		}
		++str;
		--rev_p;
	}
	
	return 1;
}
