#include <assert.h> /* assert */
#include <limits.h> /* CHAR_BIT */

#include "bit_array.h"

#define BIT_ARRAY_LEN (sizeof(bit_arr_t) * CHAR_BIT)
#define BIT_ARRAY_SIZE (sizeof(bit_arr_t))
#define UNUSED(x) ((void)x)

/* Approved by Roman */
/* Time complexity: O(1) */
bit_arr_t SetOn(bit_arr_t bit_array, size_t index)
{
	assert(BIT_ARRAY_LEN > index);

	return bit_array | ((bit_arr_t)1 << index);
}

/* Approved by Roman */
/* Time complexity: O(1) */
bit_arr_t SetOff(bit_arr_t bit_array, size_t index)
{
	assert(BIT_ARRAY_LEN > index);

	return bit_array & (~((bit_arr_t)1 << index));
}

/* Approved by Roman */
/* Time complexity: O(1) */
bit_arr_t SetAll(bit_arr_t bit_array)
{
	UNUSED(bit_array);

	return ~(bit_arr_t)0;
}

/* Approved by Roman */
/* Time complexity: O(1) */
bit_arr_t ResetAll(bit_arr_t bit_array)
{
	UNUSED(bit_array);

	return 0;
}

/* Approved by Roman */
/* Time complexity: O(1) */
bit_arr_t SetBit(bit_arr_t bit_array, size_t index, int value)
{
	assert(BIT_ARRAY_LEN > index);
	assert((0 == value) || (1 == value));

	return (bit_array & (~((bit_arr_t)1 << index))) | ((bit_arr_t)value << index);
}

/* Approved by Roman */
/* Time complexity: O(1) */
int GetVal(bit_arr_t bit_array, size_t index)
{
	assert(BIT_ARRAY_LEN > index);

	return ((bit_arr_t)(bit_array & ((bit_arr_t)1 << index))) >> index;
}

/* Approved by Eden S */
/* Time complexity: O(1) */
bit_arr_t FlipBit	(bit_arr_t bit_array, size_t index)
{
	assert(BIT_ARRAY_LEN > index);

	return bit_array ^ ((bit_arr_t)1 << index);
}

/* Approved by Roman */
/* Time complexity: O(1) */
bit_arr_t RotR(bit_arr_t bit_array, size_t shifts)
{
	shifts = shifts & ((BIT_ARRAY_LEN) - 1);
	return bit_array >> shifts | bit_array << (BIT_ARRAY_LEN - shifts);
}

/* Approved by Roman */
/* Time complexity: O(1) */
bit_arr_t RotL(bit_arr_t bit_array, size_t shifts)
{
	shifts = shifts & ((BIT_ARRAY_LEN) - 1);
	return bit_array << shifts | bit_array >> (BIT_ARRAY_LEN - shifts);
}

/* Approved by Shir */
/* Time complexity: O(1) */
bit_arr_t Mirror(bit_arr_t bit_array)
{
	size_t i = 0;
	bit_arr_t mirror = 0;

	for (i = 0; i < BIT_ARRAY_LEN; ++i)
	{
		mirror <<= 1;
		mirror |= bit_array & 1;
		bit_array >>= 1;
	}

	return mirror;
}

/* Approved by Shir */
/* Time complexity: O(log(n)) */
size_t CountOn(bit_arr_t bit_array)
{
	size_t counter = 0;

	while (0 != bit_array)
	{
		bit_array = bit_array & (bit_array - 1);
		++counter;
	}

	return counter;
}

/* Approved by Shir */
/* Time complexity: O(log(n)) */
size_t CountOff(bit_arr_t bit_array)
{
	size_t counter = 0;
	bit_array = ~bit_array;

	while (0 != bit_array)
	{
		bit_array = bit_array & (bit_array - 1);
		++counter;
	}

	return counter;
}

/* Approved by Shir */
/* Time complexity: O(1) */
char *ToString(bit_arr_t bit_array, char *dest)
{
	size_t i = 0;

	assert(NULL != dest);

	dest += BIT_ARRAY_LEN;
	*dest = '\0';

	for (i = 0; i < BIT_ARRAY_LEN; ++i)
	{
		--dest;
		*dest = '0' + (bit_array & 1);
		bit_array >>= 1;
	}

	return dest;
}