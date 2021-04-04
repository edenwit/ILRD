#include <stdio.h> 
#include <limits.h>
#include "ex1.h"

#define WORD_SIZE (sizeof(size_t))

void *MemSet(void *s, int c, size_t n)
{
	unsigned char *temp_s = (unsigned char *)s;
	size_t i = 0;
	unsigned char char_c = (CHAR_MAX & c);
	size_t mask = 0;
	
	for (i = 0; i < WORD_SIZE; ++i)
	{
			mask <<= 8;
			mask = mask | char_c;
	}
	
	printf("res of mod: %ld\n",(size_t)temp_s % WORD_SIZE);
	while (0 != ((size_t)temp_s % WORD_SIZE))
	{
		*temp_s = char_c;
		++temp_s;
		n -= 1;
		printf("1 loop n left: %ld\n", n);
	}

	while (n > WORD_SIZE)
	{
		*(size_t *)temp_s = mask;
		temp_s += WORD_SIZE;
		n -= WORD_SIZE;
		printf("2 loop n left: %ld\n", n);
	}

	while (0 < n)
	{
		*temp_s = char_c;
		++temp_s;
		n -= 1;
		printf("3 loop n left: %ld\n", n);
	}
	return s;
}
