#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <ctype.h>
#include <stdio.h> /* printf */

#include "part2.h"

#define DEC_DIGITS 10
#define CHAR_VALUES 256



/* approved by nir */
char *ItoaBaseTil36       (int value, char *str, int base )
{
	int temp_num = value;
	char *s_original = str;
	int remain = 0;
	size_t counter = 0;
	
	assert(str);
		
	if (0 == value)
	{
		*str = '0';
		++str;
		*str = '\0';
		return s_original;
	}
	if (0 > value)
	{
		*str = '-';
		++str;
		value *= -1;
	}
	while (0 != temp_num)
	{
		temp_num /= base;
		++counter;
	}
	str += counter;
	*str = '\0';
	--str;

	while (0 < counter)
	{
		remain = value % base;
        *str = (remain > 9) ? ((remain - DEC_DIGITS) + 'a') : (remain + '0');
        --str;
		value = value / base;
		--counter;
	}

	return s_original;
}

int AtoiBase10(const char *s)
{
    int to_num = 0;
	int sign = 1;

	while (' ' == *s)
	{
		++s;
	}
	if ('-' == *s)
	{
		sign = -1;
		++s;
	}
	
    while (('\0' != *s) && ('0' <= *s && '9' >= *s))
    {
        to_num = (to_num * DEC_DIGITS) + *s - '0';
		++s;
    }
 
    return to_num * sign;
}

/* approved by nir */
int   AtoiBaseTil36		  (const char *str, int base)
{
    int sign = 1;
    int num = 0;
    int status = 0;

    assert(str);

    while (isspace(*str))
    {
        ++str;
    } 

    if ('-' == *str)
    {
        ++str;
        sign = -1;
    }

    while (isalnum(*str))
    {
        num *= base;
        status = isdigit(*str); 
		/* if char is digit and base smaller then value*/
        if (status && base < (*str - '0'))
        {
            break;
        }
   		/* if char is alpha and base smaller then value*/
        else if (base < (toupper(*str) - 'A' + DEC_DIGITS))
        {
            break;
        }

        num = num + (status ? (*str - '0') : (toupper(*str) -'A' + DEC_DIGITS));
        ++str; 
    }

    return (num * sign);
}


/* approved by nir */

int   IsLittleEndian      ()
{
	int n = 1;
	
	return (*(char *)&n == 1);
}

/* approved by nir */

void  PrintFirstAndSecond (const char *arr1, size_t len1, const char *arr2, size_t len2, const char *arr3, size_t len3)

{
	unsigned char chars_lut[CHAR_VALUES -1] = {0};
	size_t i = 0;
		
	for (i = 0; i < len1; ++i)
	{
		chars_lut[(size_t)*arr1] = 1;
		++arr1;
	}
	for (i = 0; i < len2; ++i)
	{
		if (1 == chars_lut[(size_t)*arr2] )
		{
			chars_lut[(size_t)*arr2] = 2;
		}
		++arr2;
	}
	for (i = 0; i < len3; ++i)
	{
		chars_lut[(size_t)*arr3] = 0;
		++arr3;
	}
	for (i = 0; i < CHAR_VALUES; ++i)
	{
		if (2 == chars_lut[i])
		{
			printf("%c", (char)i);
		}
	}
	printf("\n");
	
	return;	
	
}

