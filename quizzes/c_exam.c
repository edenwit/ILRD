#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdio.h> /* sprintf */

#include "c_exam.h"
#define BYTE_SIZE 8

/* question 1 */
int FlipDigitsInNum(int num)
{
	int rev_num = 0;
	int sign = 1;
	
	if (0 > num)
	{
		sign = -1;
		num *= -1;
	}
	while (0 != num)
	{
		rev_num = (rev_num * 10) + (num % 10);
		num = num / 10;
	}
	
	return rev_num * sign;
}

/* question 4 */
unsigned char ByteMirror(unsigned char byte)
{
	unsigned char mirror = 0;
	size_t i = 0;
	int right_bit = 0;
	
	for (i = 0; i < BYTE_SIZE; ++i)
	{
		mirror = mirror << 1;
		right_bit = byte & 1;
		mirror = mirror | right_bit;
		byte = byte >> 1;
	}
	
	return mirror;
}

/* question 5 */
int FlipBit(int val, unsigned int n)
{
	assert(n < 32);
	
	return (val ^ (unsigned int)(1) << n);
}

/* question 6 */
size_t CountBitsInByte(unsigned char byte)
{
	size_t counter = 0;
	
	while (0 != byte)
	{
		if (byte & (unsigned char)(1))
		{
			++counter;
		}
		byte = byte >> 1;
	}
	
	return counter;
}

/* question 8 */
char RotateLeft(char byte, unsigned int nbits)
{
	nbits = nbits & (BYTE_SIZE - 1);

	return (byte << nbits) | (byte >> (BYTE_SIZE - nbits));
}

/* question 10 */
void SwapPointers(int **p1, int **p2)
{
	int *temp = NULL;
	
	assert (p1);
	assert (p2);
	
	temp = *p1;
	*p1 = *p2;
	*p2 = temp;	
	
	return;	
}

/* question 11 */
size_t Strlen(const char *s)
{
	size_t len = 0;

	assert (s);
	
	while ('\0' != *s)
	{
		++len;
		++s;
	}
	
	return len;
}

int Strcmp(const char *s1, const char *s2)
{
	assert (s1);
	assert (s2);

	while ('\0' != *s1 || '\0' != *s2)	
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		++s1;
		++s2;
	}
	
	return 0;
}

char *Strcpy(char *dest, const char *src)
{
	char *cur_dest = dest;
	
	assert (src);
	assert (dest);
		
	while ('\0' != *src)
	{
		*cur_dest = *src;
		++src;
		++cur_dest;
	}
	*cur_dest = '\0';
	
	return dest;
}

char *Strncpy(char *dest, const char *src, size_t n)
{
	char *cur_dest = dest;

	assert (src);
	assert (dest);
	
	while ('\0' != *src && 0 < n)
	{
		*cur_dest = *src;
		++src;
		++cur_dest;
		--n;
	}
	
	while (0 < n)
	{
		*cur_dest = '\0';
		++cur_dest;
		--n;
	}

	return dest;
}

char *Strcat(char *dest, const char *src)
{	
    char *cpy_dest = dest + Strlen(dest);

	assert (src);
	assert (dest);
	
	while ('\0' != *src)
    {
    	*cpy_dest = *src;
		++cpy_dest;
		++src;
    }
    *cpy_dest = '\0';
    
    return dest;
}

/* question 12 */
unsigned long GetNFibonacciElement(unsigned int n)
{
	unsigned long num = 1;
	unsigned long prev_num = 0;
	size_t i = 0;

	assert(0 < n);
	
	for (i = 1; i < n; ++i)
	{
		num += prev_num;
		prev_num = num - prev_num;
	}
	
	return num;
}

/* question 13 */
char *IntToString (int value, char *str)
{
	assert(str);

	sprintf(str,"%d",value);

	return str;
}

/* question 14 */
long MultiPlyBy8(int num)
{
	int sign = 1;
	
	if (0 > num)
	{
		num *= -1;
		sign = -1;
	}
	num <<= 3;
	
	return (num * sign);
}

/* question 15 */
void Swap1(int *x, int *y)
{
	int temp = 0;

	assert(x);
	assert(y);
	
	temp = *x;
	*x = *y;
	*y = temp;
	
	return;	
}


void Swap2(int *x, int *y)
{
	assert(x);
	assert(y);
	
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
	
	return;
}

void Swap3(int *x, int *y)
{
	assert(x);
	assert(y);
	
	*x = *x - *y;
	*y = *x + *y;
	*x = *y - *x;
	
	return;
}
