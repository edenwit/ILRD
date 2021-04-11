#include <assert.h> /* assert */
#include <stddef.h> /* size_t */

#include "part2.h"

char *ItoA(int num, char *s, int base)
{
	int rev_num = 0;
	int sign = 1;
	char *s_original = NULL;
	int remain = 0;
	
	assert(s);
	
	s_original = s;
	
	if (0 == num)
	{
		*s = '0';
		++s;
		*s = '\0';
		return s_original;
	}
	if (0 > num)
	{
		sign = -1;
		rev_num *= -1;
	}
	while (0 < num)
	{
		rev_num = (rev_num * 10) + (num % 10);
		num /= 10;
	}
	if (-1 == sign)
	{
		*s = '-';
		++s;
	}
	while (0 != rev_num)
	{
		remain = rev_num % base;
        *s = (remain > 9)? (remain - 10) + 'a' : remain + '0';
        ++s;
		rev_num = rev_num / base;		
	}
	s = '\0';
	
	return s_original;
}
