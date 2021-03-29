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
    
    /*free(new_str - (length - 1));*/
    
    return new_str - (length - 1) ;
}
