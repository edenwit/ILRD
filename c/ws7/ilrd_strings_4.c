
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
 
		while ('\0' != *p1 && '\0' != *p2 && 0 == (*p1 - *p2))
		{
			++p1;
			++p2;
		}
 
		if ('\0' == *p2)
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
	
	assert (NULL != s);
	assert (NULL != s);
	
	while ('\0' != *s && NULL != StrChr(accept, *s))
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
