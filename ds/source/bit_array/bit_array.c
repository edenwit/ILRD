#include <stddef.h>  /*size_t*/
#include <assert.h> /* assert */

#include "bit_array.h"

#define CHAR_BIT 8
#define UNUSED(X) ((void) X)
#define BITS_IN_ARR (sizeof(bit_arr_t) * CHAR_BIT)

/*Approved by Eden girl  */
bit_arr_t SetOn(bit_arr_t bit_array, size_t index)
{	
	assert(index < BITS_IN_ARR);
	
	return (bit_array | ((bit_arr_t)1 << index));
}

bit_arr_t SetOff(bit_arr_t bit_array, size_t index)
{
	assert(index < BITS_IN_ARR);  
	
	return (bit_array & (~((bit_arr_t)1 << index)));
}

/*Approved by Eden girl  */
bit_arr_t SetAll(bit_arr_t bit_array)
{
	bit_arr_t sizet_max = 0;
		
	UNUSED(bit_array);
	
	sizet_max = ~sizet_max;
	
	return sizet_max;
}

/*Approved by Eden girl  */
bit_arr_t ResetAll(bit_arr_t bit_array)
{
	UNUSED(bit_array);
	
	return (bit_arr_t)0;
}

/*Approved by Eden girl  */
bit_arr_t SetBit(bit_arr_t bit_array, size_t index, int value)
{
	bit_arr_t off_mask = ~((bit_arr_t)1 << index);
	
	assert(index < BITS_IN_ARR);
	assert((value == 0) || (value == 1));
	
	
	bit_array = bit_array & off_mask;
	
	return (bit_array | ((bit_arr_t)value << index));
}

/*Approved by Eden girl  */
int GetVal(bit_arr_t bit_array, size_t index)
{
	assert(index < BITS_IN_ARR);
	
	return (1 & (bit_array >> index));
}

/*Approved by Eden girl  */
char *ToString(bit_arr_t bit_array, char *dest)
{
	size_t i = 0;
	char *temp_dest = NULL;

	assert(dest);
	
	temp_dest = dest;
	
	for (i = BITS_IN_ARR; i > 0; --i)
	{

		*temp_dest = (1 & (bit_array >> (i - 1))) ? '1' : '0';
		++temp_dest;
	}
	temp_dest = '\0';
	
	return dest;
}

/*Approved by Eden girl  */
bit_arr_t FlipBit(bit_arr_t bit_array, size_t index)
{
	assert(index < BITS_IN_ARR);
	
	return (bit_array ^ ((bit_arr_t)1 << index));
}

/*Approved by Eden girl  */
bit_arr_t RotR(bit_arr_t bit_array, size_t shifts)
{
	shifts &= (BITS_IN_ARR - 1);

    return (bit_array >> shifts) | (bit_array << (BITS_IN_ARR - shifts));
}

/*Approved by Eden girl  */
bit_arr_t RotL(bit_arr_t bit_array, size_t shifts)
{
	shifts &= (BITS_IN_ARR - 1);

    return (bit_array << shifts) | (bit_array >> (BITS_IN_ARR - shifts));	
}

/*Approved by Eden girl  */
bit_arr_t Mirror(bit_arr_t bit_array)
{
	bit_arr_t mirror = 0;
	size_t i = 0;

	for (i = 0; i < BITS_IN_ARR; ++i)
	{
		mirror <<= 1;
		mirror |= (bit_array & 1);	
		bit_array >>= 1; 	
	}
	
	return mirror;
}

/*Approved by Eden girl  */
size_t CountOn(bit_arr_t bit_array)
{
	size_t counter = 0;
	
	while (0 != bit_array)
	{
		bit_array &= (bit_array - 1);
		++counter;
	}
	
	return counter;
}

/*Approved by Eden girl  */
size_t CountOff(bit_arr_t bit_array)
{
	size_t counter = 0;

	bit_array = ~bit_array;

	while (0 != bit_array)
	{
		bit_array &= (bit_array - 1);
		++counter;
	}
	
	return counter;
}

