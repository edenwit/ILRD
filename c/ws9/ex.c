#include <stdio.h> 
#include <assert.h>
#include <limits.h>

#include "ex.h"

#define WORD_SIZE (sizeof(size_t))

static void *MemcpyRev(void *dest, const void *src, size_t n);

/* Approved by Maor */
void *MemSet(void *s, int c, size_t n)
{
	unsigned char *temp_s = NULL;
	size_t i = 0;
	unsigned char char_c = (CHAR_MAX & c);
	size_t mask = 0;
	
	assert(s);
	
	temp_s = (unsigned char *)s;

	for (i = 0; i < WORD_SIZE; ++i)
	{
		mask <<= 8;
		mask = mask | char_c;
	}
	
	while ((0 != ((size_t)temp_s % WORD_SIZE)) && (0 < n))
	{
		*temp_s = char_c;
		++temp_s;
		n -= 1;
	}

	while (n > WORD_SIZE)
	{
		*(size_t *)temp_s = mask;
		temp_s += WORD_SIZE;
		n -= WORD_SIZE;
	}

	while (0 < n)
	{
		*temp_s = char_c;
		++temp_s;
		n -= 1;
	}
	
	return s;
}

/* Approved by Maor */
void *MemCpy(void *dest, const void *src, size_t n)
{
	unsigned char  *temp_src = NULL;
	unsigned char *temp_dest = NULL;
	
	assert(dest);
	assert(src);
	
	temp_src = (unsigned char *)src;
	temp_dest = (unsigned char *)dest;
	
	while ((0 != ((size_t)temp_dest % WORD_SIZE)) && (0 < n))
	{
		*temp_dest = *temp_src;
		++temp_dest;
		++temp_src;
		n -= 1;
	}

	while (n > WORD_SIZE)
	{
		*(size_t *)temp_dest = *(size_t *)temp_src;
		temp_dest += WORD_SIZE;
		temp_src += WORD_SIZE;
		n -= WORD_SIZE;
	}

	while (0 < n)
	{
		*temp_dest = *temp_src;
		++temp_dest;
		++temp_src;
		n -= 1;
	}
	
	return dest;
}

void *MemMove(void *dest, const void *src, size_t n)
{

	assert(dest);
	assert(src);
	
	if ((size_t)dest == (size_t)src)
	{
		return dest;
	}
	else if ((size_t)src < (size_t)dest)
	{	
		return MemcpyRev(dest, src, n);

	}
	else
	{
		return MemCpy(dest, src, n);
	}
}

static void *MemcpyRev(void *dest, const void *src, size_t n)
{
	unsigned char  *temp_src = NULL;
	unsigned char *temp_dest = NULL;
	
	assert(dest);
	assert(src);
	
	temp_src = (unsigned char *)src + n;
	temp_dest = (unsigned char *)dest + n;
	
	while ((0 != ((size_t)temp_dest % WORD_SIZE)) && (0 < n))
	{
		--temp_dest;
		--temp_src;
		*temp_dest = *temp_src;
		n -= 1;
	}

	while (WORD_SIZE < n)
	{
		temp_dest -= WORD_SIZE;
		temp_src -= WORD_SIZE;
		*(size_t *)temp_dest = *(size_t *)temp_src;
		n -= WORD_SIZE;
	}

	while (0 < n)
	{
		--temp_dest;
		--temp_src;
		*temp_dest = *temp_src;
		n -= 1;
	}
	
	return dest;
}
