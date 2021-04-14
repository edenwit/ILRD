#include <stddef.h> /* size_t */

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
