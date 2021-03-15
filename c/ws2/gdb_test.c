#include <stdio.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int IsPalindrome(const char *str)
{
	char * rev_p = (char *)(str + strlen(str) - 1);
	
	assert (NULL != str);
	
	while (str < rev_p)
	{
		while (isspace(*str))
		{
			++str;
		}
		while (isspace(*rev_p))
		{
			--rev_p;
		}
		if (*str != *rev_p)
		{
			printf("\nFall in %c - %c\n",*str, *rev_p);
			return 0;
		}
		++str;
		--rev_p;
	}
	
	return 1;
}

int main()
{
	char string[40] = "I love checking for palindromes";
	printf ("Palindrome? : %d\n",IsPalindrome(string));
	
	return 0;
}
