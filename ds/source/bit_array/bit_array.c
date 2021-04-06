#include <stddef.h>  /*size_t*/
#include <climits.h> /* CHAR_BIT */

#define UNUSED(X) void(X)
#define BITS_IN_ARR (sizeof(bit_arr_t) * CHAR_BIT)

typedef size_t bit_arr_t;

bit_arr_t SetOn		(bit_arr_t bit_array, size_t index)
{
	return (bit_array | (1 << index));
}

bit_arr_t SetOff	(bit_arr_t bit_array, size_t index)
{
	return (bit_array & (~(1 << index)));
}

bit_arr_t SetAll	(bit_arr_t bit_array)
{
	bit_arr_t sizet_max = 0;
		
	UNUSED(bit_array);
	
	sizet_max ~= sizet_max;
	
	return sizet_max;
}

bit_arr_t ResetAll	(bit_arr_t bit_array)
{
	UNUSED(bit_array);
	
	return 0;
}

bit_arr_t SetBit	(bit_arr_t bit_array, size_t index, int value);

int 	  GetVal	(bit_arr_t bit_array, size_t index)
{
	return (bit_array & (1 << index));
}

bit_arr_t FlipBit	(bit_arr_t bit_array, size_t index)
{
	return (bit_array ^ (1 << index));
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
	for (i = BITS_IN_ARR - 1; i > 0; ++i)
	{
		*dest = ((1 << i) & bit_array);
		++dest;
	}	
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

	sizet_max ~= sizet_max;
	
	while (sizet_max != bit_array)
	{
		bit_array |= (bit_array - 1);
		++counter;
	}
	
	return counter;
}

char *ToString		(bit_arr_t bit_array, char *dest)
{
	size_t i = 0;
	
	for (i = BITS_IN_ARR - 1; i > 0; ++i)
	{
		*dest = ((1 << i) & bit_array);
		++dest;
	}
	
	return (dest - BITS_IN_ARR);
}


