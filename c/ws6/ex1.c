#include <stdio.h> /* printf */

long Pow2(unsigned int x, unsigned int y)
{
	return (long)(x << y);
}

int IsPow2Loop(unsigned int num)
{
	unsigned int i = 1;
	
	while (i < num)
	{
		i = i << 1;
	}
	
	if (i == num)
	{
		return 1;
	}
	
	return 0;
}

int IsPow2NoLoop(unsigned int num)
{
	printf("Res: %d",(num & -num) == num);
    return (num & -num) == num;
}

int Increment(int x);
void PrintThreeOn(unsigned int nums[]);
unsigned char ByteMirrorLoop(unsigned char byte);
unsigned char ByteMirrorNoLoop(unsigned char byte);
int IsBit2And6On(unsigned char byte);
int IsBit2Or6On(unsigned char byte);
unsigned char Swap3And5(unsigned char byte);
unsigned int DivideBy16(unsigned int num);
void Swap(int *x, int *y);
unsigned int CountBitsLoop(int num);
unsigned int CountBitsNoLoop(int num);
void PrintFloatBits(float f);
