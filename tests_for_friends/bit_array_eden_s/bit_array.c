#include <limits.h>
#include <assert.h>
#include <stdio.h>
#include "bit_array.h"

#define UNUSED(X) (void)(X)
#define ARR_SIZE (sizeof(bit_arr_t) * CHAR_BIT)
#define FIRST_BIT_ON (((bit_arr_t)1) << (ARR_SIZE - 1))

/* Approved by Noga */
bit_arr_t SetOn(bit_arr_t bit_arr, size_t index)
{
	return (((bit_arr_t)1 << index) | bit_arr);
}

/* Approved by Noga */
bit_arr_t SetOff(bit_arr_t bit_arr, size_t index)
{
	return ((~((bit_arr_t)1 << index)) & bit_arr);
}

/* Approved by Noga */
bit_arr_t SetBit(bit_arr_t bit_arr, size_t index, int value)
{
	return ((~((bit_arr_t)1 << index)) & bit_arr) | ((bit_arr_t)value << index);
}

/* Approved by Noga */
bit_arr_t SetAll(bit_arr_t bit_arr)
{	
	UNUSED(bit_arr);
	
	return ~((bit_arr_t)0);
}

/* Approved by Noga */
bit_arr_t ResetAll(bit_arr_t bit_arr)
{
	UNUSED(bit_arr);
	
	return 0;
}

/* Approved by Noga */
char *ToString(bit_arr_t bit_arr, char *dest)
{
	size_t i = ARR_SIZE;
	char *dest_p = dest;
	
	assert(dest);
	
	while (0 < i)
	{
		*dest_p = ((bit_arr >> (i - 1)) & 1) + '0';
		
		++dest_p;
		--i;
	}
	
	*dest_p = '\0';
	
	return dest;
}

/* Approved by Noga */
int GetVal(bit_arr_t bit_arr, size_t index)
{
	return (bit_arr >> index) & 1;
}

/* Approved by Noga */
bit_arr_t FlipBit(bit_arr_t bit_arr, size_t index)
{
	return ((bit_arr_t)1 << index) ^ bit_arr;
}

/* Approved by Noga */
bit_arr_t Mirror(bit_arr_t bit_arr)
{
	bit_arr_t r = 0;
	size_t i = 0;
	
	while (ARR_SIZE > i)
	{
		r |= ((((bit_arr >> (ARR_SIZE - i -1)) & 1)) << i);
		
		++i;
	}
	
	return r;
}

/* Approved by Noga */
bit_arr_t RotR(bit_arr_t bit_arr, size_t shifts)
{
	bit_arr_t r = 0;
	
	shifts &= (ARR_SIZE - 1);
	
	r |= (bit_arr >> shifts);
	r |= (bit_arr << (ARR_SIZE - shifts));
	
	return r;
}

/* Approved by Noga */
bit_arr_t RotL(bit_arr_t bit_arr, size_t shifts)
{
	bit_arr_t r = 0;
	
	shifts &= (ARR_SIZE - 1);
	
	r |= (bit_arr << shifts);
	r |= bit_arr >> (ARR_SIZE - shifts);
	
	return r;
}

/* Approved by Noga */
size_t CountOn(bit_arr_t bit_arr)
{
	size_t count = 0;
	
	while (0 < bit_arr)
	{
		bit_arr &= bit_arr - 1;
		
		++count;
	}
	
	return count;
}

/* Approved by Noga */
size_t CountOff(bit_arr_t bit_arr)
{
	size_t count = 0;
	
	bit_arr = ~bit_arr;
	
	while (0 < bit_arr)
	{
		bit_arr &= bit_arr - 1;
		
		++count;
	}
	
	return count;
}







