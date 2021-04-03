
#include <stdio.h> /* printf */

#include "ex1.h"

#define BYTE_SIZE 8
#define CHAR_VALUES 256
#define BITS_IN_BYTE (sizeof(int))

static unsigned int *LutCountBits();

/* approved by Avital */
long Pow2(unsigned int x, unsigned int y)
{
	return ((long)x << y);
}

/* approved by Avital */
int IsPow2Loop(unsigned int n)
{
	unsigned int i = 1;
	
	while (i < n)
	{
		i = i << 1;
	}
	
	if (i == n)
	{
		return 1;
	}
	
	return 0;
}

/* approved by Avital */
int IsPow2NoLoop(unsigned int n)
{
    return (n & (n - 1)) == 0;
}

/* approved by Avital */
int Add1(int n)
{
    int x = 1;
        
    while (n & x)
    {
        n = n ^ x;
        x = x << 1;
    }
    n = n ^ x;
    
    return n;
}

/* approved by Avital */
void PrintThreeOn(unsigned int nums[], size_t length)
{
	static const int count_to_get = 3;
	unsigned int cur_num = 0;
	int counter = 0;
	size_t i = 0;
		
	assert(nums);
		
	for (i = 0; i < length; ++i)
	{
		counter = 0;
		cur_num = nums[i];

		while (counter <= count_to_get && 0 != cur_num)
		{
			if (cur_num & 1)
			{
				++counter;
			}
			cur_num = cur_num >> 1;
		}

		if (counter == count_to_get)
		{
			printf("%d ", nums[i]);
		}

	}
	printf("\n");
	
	return;
}

/* Approved by Maor */
unsigned char ByteMirrorLoop(unsigned char byte)
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

/* Approved by Maor */
unsigned char ByteMirrorNoLoop(unsigned char byte)
{
	unsigned char lut[CHAR_VALUES] = {'\0'};
	size_t i = 0;
	
	for (i = 0; i < CHAR_VALUES; ++i)
	{
		lut[i] = ByteMirrorLoop(i);
	}
	
	return lut[byte];
}

/* Approved by Ohad */
int IsBit2And6On(unsigned char byte)
{
	return ((byte & (1 << 2)) && (byte & (1 << 6)));
}

/* Approved by Ohad */
int IsBit2Or6On(unsigned char byte)
{
	return ((byte & (1 << 2)) || (byte & (1 << 6)));
}

/* Approved by Shelly && Ohad */
unsigned char Swap3And5(unsigned char byte)
{
	/* x gets 0 if same, 1 if not */
    unsigned char x = (((byte >> 3) & 1) ^ ((byte >> 5) & 1));
 	
    x = (x << 3) | (x << 5);
 
    return (byte ^ x);
}


/* Approved by Ohad */
unsigned int DivideBy16(unsigned int num)
{
	return ((num >> 4) << 4);
}

/* Approved by Shelly */
void Swap(unsigned int *x, unsigned int *y)
{
	*x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

/* Approved by Shelly && Ohad */
unsigned int CountBitsLoop(int num)
{
	unsigned int counter = 0;
	size_t i = 0;
	
	for (i = 0; i < BYTE_SIZE * BITS_IN_BYTE; ++i)
	{
		if (1 & num)
		{
			++counter;
		}
		num = num >> 1; 
	}
	
	return counter;
}

/* Approved by Ohad */
unsigned int CountBitsNoLoop(int num)
{
	int  mask = (CHAR_VALUES - 1);
	unsigned int counter = 0;

	counter = counter + LutCountBits()[num & mask];
	num = num >> 8;
	counter = counter + LutCountBits()[num & mask];
	num = num >> 8;
	counter = counter + LutCountBits()[num & mask];
	num = num >> 8;
	counter = counter + LutCountBits()[num & mask];
	
	return counter;
}

/* Approved by Ohad */
void PrintFloatBits(float f)
{	
    int *int_p = (int *) &f;
    int i = 0;
    unsigned int bit = 0;
    
    printf("%f \t", f);

    for (i = BYTE_SIZE * BITS_IN_BYTE -1; i >= 0; --i)
    {
		bit = *int_p & (1 << i);

		printf("%u", bit >> i);
		
		if ((31 == i) || (23 == i))
		{
			printf(" ");
		}
    }
	printf("\n");
}

/* Approved by Shelly */
static unsigned int *LutCountBits()
{
    static unsigned int arr_byte[CHAR_VALUES] = {0}; 
    static int init = 0;
    size_t i = 0;

    if (!init)
    {
        for (i = 0; i < CHAR_VALUES; ++i)
        {
            arr_byte[i] = CountBitsLoop(i);
        }

        init = 1;
    }

    return arr_byte;
}









