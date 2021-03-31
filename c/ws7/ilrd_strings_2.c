#include "ilrd_strings.h" /* StrLen, StrCmp */

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

char *StrnCpy(char *dest, const char *src, size_t n)
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
	
	while (final_dest != cur_dest)
	{
		*cur_dest = '\0';
		++cur_dest;
	}

	return dest;
}
