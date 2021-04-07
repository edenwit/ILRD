#include <stddef.h>  /*size_t*/
#include <assert.h> /* assert */

#include "bit_array.h"

#define CHAR_BIT 8
#define UNUSED(X) ((void) X)
#define BITS_IN_ARR (sizeof(bit_arr_t) * CHAR_BIT)


bit_arr_t SetOn		(bit_arr_t bit_array, size_t index)
{	
	assert(index < BITS_IN_ARR);
	
	return (bit_array | ((bit_arr_t)1 << index));
}

bit_arr_t SetOff	(bit_arr_t bit_array, size_t index)
{
	assert(index < BITS_IN_ARR);  
	
	return (bit_array & (~((bit_arr_t)1 << index)));
}

bit_arr_t SetAll	(bit_arr_t bit_array)
{
	bit_arr_t sizet_max = 0;
		
	UNUSED(bit_array);
	
	sizet_max = ~sizet_max;
	
	return sizet_max;
}

bit_arr_t ResetAll	(bit_arr_t bit_array)
{
	UNUSED(bit_array);
	
	return (bit_arr_t)0;
}

bit_arr_t SetBit	(bit_arr_t bit_array, size_t index, int value)
{
	bit_arr_t off_mask = ~((bit_arr_t)1 << index);
	
	assert(index < BITS_IN_ARR);
	assert((value == 0) || (value == 1));
	
	
	bit_array = bit_array & off_mask;
	
	return (bit_array | ((bit_arr_t)value << index));
}

int 	  GetVal	(bit_arr_t bit_array, size_t index)
{
	assert(index < BITS_IN_ARR);
	
	return (1 & (bit_array >> index));
}


char *ToString		(bit_arr_t bit_array, char *dest)
{
	size_t i = 0;
	char *temp_dest = NULL;
	char bit = 0;

	assert(dest);
	
	temp_dest = dest;
	
	for (i = BITS_IN_ARR; i > 0; --i)
	{

		bit = (1 & (bit_array >> (i - 1))) ? '1' : '0';
		*temp_dest = (bit);
		++temp_dest;
	}
	temp_dest = '\0';
	
	return dest;
}


bit_arr_t FlipBit	(bit_arr_t bit_array, size_t index)
{
	assert(index < BITS_IN_ARR);
	
	return (bit_array ^ ((bit_arr_t)1 << index));
}

bit_arr_t RotR		(bit_arr_t bit_array, size_t shifts)
{
    bit_arr_t shifted = bit_array >> shifts;
    bit_arr_t temp = bit_array << (BITS_IN_ARR - shifts);

    return shifted | temp;
}

bit_arr_t RotL		(bit_arr_t bit_array, size_t shifts)
{
    bit_arr_t shifted = bit_array << shifts;
    bit_arr_t temp = bit_array >> (BITS_IN_ARR - shifts);

    return shifted | temp;	
}
bit_arr_t Mirror	(bit_arr_t bit_array)
{
	bit_arr_t mirror = 0;
	size_t i = 0;
	int right_bit = 0;

	for (i = 0; i < BITS_IN_ARR; ++i)
	{
		mirror = mirror << 1;
		right_bit = (bit_array & 1);
		mirror = mirror | right_bit;	
		bit_array = bit_array >> 1; 	
	}
	
	return mirror;
}

size_t CountOn		(bit_arr_t bit_array)
{
	size_t counter = 0;
	
	while (0 != bit_array)
	{
		bit_array &= (bit_array - 1);
		++counter;
	}
	
	return counter;
}

size_t CountOff		(bit_arr_t bit_array)
{
	size_t counter = 0;
	bit_arr_t sizet_max = 0;

	sizet_max = ~sizet_max;
	
	while (sizet_max != bit_array)
	{
		bit_array |= (bit_array + 1);
		++counter;
	}
	
	return counter;
}

