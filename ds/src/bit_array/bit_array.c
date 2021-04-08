#include <stddef.h>  /*size_t*/
#include <assert.h> /* assert */

#include "bit_array.h"

#define CHAR_BIT 8
#define UNUSED(X) ((void) X)
#define BITS_IN_ARR (sizeof(bit_arr_t) * CHAR_BIT)
#define CHAR_VALUES 256

static unsigned int *LutCountBits();
static unsigned char ByteMirrorLoop(unsigned char byte);
static void initMirrorLut(char *lut_arr);

/*Approved by Eden girl  */
bit_arr_t BitArrSetOn(bit_arr_t bit_array, size_t index)
{	
	assert(index < BITS_IN_ARR);
	
	return (bit_array | ((bit_arr_t)1 << index));
}

bit_arr_t BitArrSetOff(bit_arr_t bit_array, size_t index)
{
	assert(index < BITS_IN_ARR);  
	
	return (bit_array & (~((bit_arr_t)1 << index)));
}

/*Approved by Eden girl  */
bit_arr_t BitArrSetAll(bit_arr_t bit_array)
{
	bit_arr_t sizet_max = 0;
		
	UNUSED(bit_array);
	
	sizet_max = ~sizet_max;
	
	return sizet_max;
}

/*Approved by Eden girl  */
bit_arr_t BitArrResetAll(bit_arr_t bit_array)
{
	UNUSED(bit_array);
	
	return (bit_arr_t)0;
}

/*Approved by Eden girl  */
bit_arr_t BitArrSetBit(bit_arr_t bit_array, size_t index, int value)
{
	bit_arr_t off_mask = ~((bit_arr_t)1 << index);
	
	assert(index < BITS_IN_ARR);
	assert((value == 0) || (value == 1));
	
	
	bit_array = bit_array & off_mask;
	
	return (bit_array | ((bit_arr_t)value << index));
}

/*Approved by Eden girl  */
int BitArrGetVal(bit_arr_t bit_array, size_t index)
{
	assert(index < BITS_IN_ARR);
	
	return (1 & (bit_array >> index));
}

/*Approved by Eden girl  */
char *BitArrToString(bit_arr_t bit_array, char *dest)
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
bit_arr_t BitArrFlipBit(bit_arr_t bit_array, size_t index)
{
	assert(index < BITS_IN_ARR);
	
	return (bit_array ^ ((bit_arr_t)1 << index));
}

/*Approved by Eden girl  */
bit_arr_t BitArrRotR(bit_arr_t bit_array, size_t shifts)
{
	shifts &= (BITS_IN_ARR - 1);

    return (bit_array >> shifts) | (bit_array << (BITS_IN_ARR - shifts));
}

/*Approved by Eden girl  */
bit_arr_t BitArrRotL(bit_arr_t bit_array, size_t shifts)
{
	shifts &= (BITS_IN_ARR - 1);

    return (bit_array << shifts) | (bit_array >> (BITS_IN_ARR - shifts));	
}

/*Approved by Eden girl  */
bit_arr_t BitArrMirror(bit_arr_t bit_array)
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
size_t BitArrCountOn(bit_arr_t bit_array)
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
size_t BitArrCountOff(bit_arr_t bit_array)
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

/* question 9 LUT */

size_t CountBitsNoLoop(bit_arr_t num)
{
	bit_arr_t  mask = (CHAR_VALUES - 1);
	size_t counter = 0;
	size_t i = 0;
	
	for (i = 0; i < BITS_IN_ARR / CHAR_BIT; ++i)
	{
		counter = counter + LutCountBits()[num & mask];
		num = num >> 8;
	}
	return counter;
}




static unsigned int *LutCountBits()
{
    static unsigned int arr_byte[CHAR_VALUES] = {0}; 
    static int init = 0;
    size_t i = 0;

    if (!init)
    {
        for (i = 0; i < CHAR_VALUES; ++i)
        {
            arr_byte[i] = BitArrCountOn(i);
        }

        init = 1;
    }

    return arr_byte;
}

static unsigned char ByteMirrorLoop(unsigned char byte)
{
	unsigned char mirror = 0;
	size_t i = 0;
	int right_bit = 0;
	
	for (i = 0; i < CHAR_BIT; ++i)
	{
		mirror = mirror << 1;
		right_bit = byte & 1;
		mirror = mirror | right_bit;
		byte = byte >> 1; 
	}
	
	return mirror;
}

bit_arr_t BitArrMirrorLut(bit_arr_t bit_array)
{	
	bit_arr_t mirror = 0;
	unsigned char byte_mirror = 0;	
	unsigned int mask = 0xFF;
	size_t bytes = BITS_IN_ARR / CHAR_BIT;
	static char mirror_lut[CHAR_BIT] = {0};
	static int init = 0;

	size_t i = 0;

	int num_of_shifts = 0;

	
	if (!init)
	{
		initMirrorLut(mirror_lut);
		init = 1;
	}
	
	for (i = 0; i <  bytes; i++)
	{
		byte_mirror = mirror_lut[bit_array & mask];
		num_of_shifts = (bytes-1-i)*(bytes);
		mirror |= ((bit_arr_t)byte_mirror) << num_of_shifts;	
		bit_array >>= CHAR_BIT;			
	}
	
	return mirror;
}

static void initMirrorLut(char *lut_arr)
{
	size_t i = 0;
	
	for (i = 0; i < CHAR_BIT; i++)
	{
		lut_arr[i] = ByteMirrorLoop((unsigned char)i);
	}
}
