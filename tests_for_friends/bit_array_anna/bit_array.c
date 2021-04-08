/* Developer: Anna Pest
   Status: in development
   Date: 07.04.21
   Description: Implementation of bits array */
#include <limits.h>		/* CHAR_BIT */
#include <assert.h>		/*  assert  */
#include "bit_array.h"

#define MAX_BIT_NUM sizeof(bit_arr_t)*CHAR_BIT
#define MAX_VAL_CHAR 256
#define UNUSED(X) (void)X

static unsigned char ByteMirror(unsigned char byte);
static size_t CountOnBit(unsigned char byte);
static void initMirrorLut(char *lut_arr);
static void initCountBitLut(char *lut_arr);

/* Approved by Shir */
/* Time complexity O(1) */
/* Space complexity O(1) */
bit_arr_t SetOn(bit_arr_t bit_array, size_t index)
{
	assert(MAX_BIT_NUM > index);
	
	return(bit_array | ((bit_arr_t)1 << index));
}

/* Approved by Shir */
/* Time complexity O(1) */
/* Space complexity O(1) */
bit_arr_t SetOff(bit_arr_t bit_array, size_t index)
{
	assert(MAX_BIT_NUM > index);
	
	return(bit_array & ~((bit_arr_t)1 << index));
}

/* Approved by Shir */
/* Time complexity O(1) */
/* Space complexity O(1) */
bit_arr_t SetBit(bit_arr_t bit_array, size_t index, int value)
{
	assert(MAX_BIT_NUM > index);
	assert((0 == value) | (1 == value));
	
	return ((~((bit_arr_t)1 << index) & bit_array) | (bit_arr_t)value << index);
}

/* Approved by Shir */
/* Time complexity O(1) */
/* Space complexity O(1) */
bit_arr_t SetAll(bit_arr_t bit_array)
{
	UNUSED(bit_array);
	
	return ~0;
}

/* Approved by Shir */
/* Time complexity O(1) */
/* Space complexity O(1) */
bit_arr_t ResetAll(bit_arr_t bit_array)
{
	UNUSED(bit_array);
	
	return 0;
}

/* aprroved by Roman */
/* Time complexity O(n) - n number of bits */
/* Space complexity O(1) */
char *ToString(bit_arr_t bit_array, char *dest)
{
	char *head = dest;
	assert(NULL != dest);
	
	dest += (MAX_BIT_NUM);
	*dest = '\0';
	
	while (dest > head)
	{	
		--dest;
		*dest = (bit_array & 1) + '0';
		bit_array >>= 1;
	}
	
	return dest;
}

/* aprroved by Ohad*/
/* Time complexity O(1)*/
/* Space complexity O(1) */
int GetVal(bit_arr_t bit_array, size_t index)
{
	assert(MAX_BIT_NUM > index);
	
	return (bit_array >> index) & 1;
}

/* aprroved by Roman */
/* Time complexity O(1) */
/* Space complexity O(1) */
bit_arr_t RotR(bit_arr_t bit_array, size_t shifts)
{
	shifts = shifts & (MAX_BIT_NUM - 1);
	
	return bit_array >> shifts | bit_array << (MAX_BIT_NUM - shifts);
}

/* aprroved by Roman */
/* Time complexity O(1) */
/* Space complexity O(1) */
bit_arr_t RotL(bit_arr_t bit_array, size_t shifts)
{
	shifts = shifts & (MAX_BIT_NUM - 1);
	
	return bit_array << shifts | bit_array >> (MAX_BIT_NUM - shifts);
}

/* aprroved by Roman */
/* Time complexity O(1)*/
/* Space complexity O(1) */
bit_arr_t FlipBit(bit_arr_t bit_array, size_t index)
{
	assert(MAX_BIT_NUM > index);
	
	return(bit_array ^ ((bit_arr_t)1 << index));
}

/* aprroved by Roman */
/* Time complexity O(1)*/
/* Space complexity O(1) */
bit_arr_t Mirror(bit_arr_t bit_array)
{	
	unsigned char byte_mirror = 0;	
	unsigned int mask = 0xFF;

	static char mirror_LUT[MAX_VAL_CHAR] = {0};
	static int init = 0;

	size_t i = 0;
	size_t num_of_bytes = sizeof(bit_arr_t);
	int num_of_shifts = 0;
	bit_arr_t bit_array_res = 0;
	
	if (!init)
	{
		initMirrorLut(mirror_LUT);
		init = 1;
	}
	
	for (i = 0; i < num_of_bytes; i++)
	{
		byte_mirror = mirror_LUT[bit_array & mask];
		num_of_shifts = (num_of_bytes-1-i)*(num_of_bytes);
		bit_array_res = bit_array_res | ((bit_arr_t)byte_mirror) << num_of_shifts;	
		bit_array >>= CHAR_BIT;			
	}
	
	return bit_array_res;
}

static void initMirrorLut(char *lut_arr)
{
	size_t i = 0;
	
	for (i = 0; i < MAX_VAL_CHAR; i++)
	{
		lut_arr[i] = ByteMirror((unsigned char)i);
	}
}


static unsigned char ByteMirror(unsigned char byte)
{	
	byte = ((byte & 0xF0) >> 4 | (byte & 0x0F) << 4);	/* swap nibbles */
	byte = ((byte & 0xCC) >> 2 | (byte & 0x33) << 2);	/* swap half nibbles */
	byte = ((byte & 0xAA) >> 1 | (byte & 0x55) << 1);	/* swap each pair of bits   */

	return byte;
}

/* aprroved by Roman */
/* Time complexity O(1) */
/* Space complexity O(1) */
size_t CountOn(bit_arr_t bit_array)
{
	static char count_bits_LUT[MAX_VAL_CHAR] = {0};
	unsigned int mask = 0xFF;
	static int init = 0;
	size_t counter = 0;
	
	if (!init)
	{
		initCountBitLut(count_bits_LUT);
		init = 1;
	}
	
	while (0 < bit_array)
	{
		counter += count_bits_LUT[bit_array & mask];
		bit_array >>= sizeof(bit_arr_t);
	} 
	
	return counter;
}

static void initCountBitLut(char *lut_arr)
{
	size_t i = 0;
	
	for (i = 0; i < MAX_VAL_CHAR; i++)
	{
		lut_arr[i] = CountOnBit((unsigned char)i);
	}
}


static size_t CountOnBit(unsigned char byte)
{	
	size_t counter = 0;
	
	while (0 < byte)
	{
		counter += byte & 1;
		byte >>= 1;
	}
	
	return counter;
}

/* aprroved by Roman */
/* Time complexity O(n) - n number of bits */
/* Space complexity O(1) */
size_t CountOff(bit_arr_t bit_array)
{
	size_t counter = 0;
	
	bit_array = ~bit_array;
	
	while (0 != bit_array)
	{
		bit_array = (bit_array & (bit_array-1));
		counter++;
	} 
	
	return counter;
}


