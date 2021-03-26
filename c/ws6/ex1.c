#include <stdio.h> /* printf */

#ifndef __EX1_H__
#define __EX1_H__

#define BYTE_SIZE 8
#define CHAR_VALUES 256
#define INT_BYTE_SIZE (sizeof(int))

/* approved by Avital */
long Pow2(unsigned int x, unsigned int y)
{
	return (long)(x << y);
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

int IsPow2NoLoop(int n)
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

void PrintThreeOn(unsigned int nums[], size_t length)
{
	static const int count_to_get = 3;
	unsigned int cur_num = 0;
	int counter = 0;
	size_t i = 0;
		
	for (i = 0; i < length; ++i)
	{
		counter = 0;
		cur_num = nums[i];

		while (counter < count_to_get && 0 != cur_num)
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

int IsBit2And6On(unsigned char byte)
{
	unsigned char cur_byte = byte; 

	cur_byte = cur_byte >> 2;
	if (cur_byte & 1)
	{
		cur_byte = cur_byte >> 4;
		if (cur_byte & 1)
		{
			return 1;
		}
	}
	return 0;	
}

int IsBit2Or6On(unsigned char byte)
{
	unsigned char cur_byte = byte; 

	cur_byte = cur_byte >> 2;
	if (cur_byte & 1)
	{
		return 1;
	}
	cur_byte = cur_byte >> 4;
	if (cur_byte & 1)
	{
		return 1;
	}
	return 0;	
}

unsigned char Swap3And5(unsigned char byte)
{
	/* x gets 0 if same, 1 if not */
    unsigned char x = (((byte >> 3) & 1) ^ ((byte >> 5) & 1));
 	
    x = (x << 3) | (x << 5);
 
    return (byte ^ x);
}

unsigned int DivideBy16(unsigned int num)
{
	return ((num >> 4) << 4);
}

void Swap(unsigned int *x, unsigned int *y)
{
	*x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

unsigned int CountBitsLoop(int num)
{
	size_t counter = 0;
	size_t i = 0;
	
	for (i = 0; i < BYTE_SIZE * INT_BYTE_SIZE; ++i)
	{
		if(1 & num)
		{
			++counter;
		}
		num = num >> 1; 
	}
	return counter;
}

unsigned int CountBitsNoLoop(int num)
{
	unsigned char lut[CHAR_VALUES] = {0};
	size_t i = 0;
	int  mask = (CHAR_VALUES - 1);
	unsigned int counter = 0;
	int num_and_mask = num & mask;
	
	for (i = 0; i < CHAR_VALUES; ++i)
	{
		lut[i] = CountBitsLoop(i);
	}
	
	counter = counter + lut[num_and_mask];
	mask = mask << 8;
	num_and_mask = num & mask;
	num_and_mask = num_and_mask >> 8;
	counter = counter + lut[num_and_mask];
	mask = mask << 8;
	num_and_mask = num & mask;
	num_and_mask = num_and_mask >> 16;
	counter = counter + lut[num_and_mask];
	mask = mask << 8;
	num_and_mask = num & mask;
	num_and_mask = num_and_mask >> 24;
	counter = counter + lut[num_and_mask];
	
	return counter;	
}

void PrintFloatBits(float f)
{	
    int *int_p = NULL;
    int i = BYTE_SIZE * INT_BYTE_SIZE -1;
    int bit = 0;
    
    int_p = (int *) &f;
    printf("%f -\t", f);

    for (; i >= 0; --i)
    {
		bit = *int_p & (1 << i);
		if(0 != bit)
		{
			bit = 1;
		}
		printf("%d", bit);
		
		if ((31 == i) || (23 == i))
		{
			printf(" ");
		}
    }
	printf("\n");
}

#endif /*__EX1_H__*/









