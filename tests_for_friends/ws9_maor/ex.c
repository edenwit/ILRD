#include <string.h> /*strncpy*/
#include <assert.h> /*  assert */

#include "ex.h"

#define WORD_SIZE (sizeof(size_t))
#define BYTE_SIZE (8)
#define MOD_WORD_SIZE(x) (x & 7)

static void *ReveredMemCpy(void *dest, const void *src, size_t n);

/*Approved by Eden W*/
void *MemSet(void *s, int c, size_t n)
{
	char *p = s;
	const unsigned char c_char = (unsigned char)c;
	size_t c_word = 0;
	size_t i = 0;

	assert(s);

	/* create a word of c */
	for (i = 0; i < WORD_SIZE; ++i)
	{
		c_word <<= BYTE_SIZE;
		c_word |= c_char;
	}

	while ((0 != MOD_WORD_SIZE((size_t)p)) && (0 < n))
	{
		*p = c_char;
		++p;
		--n;
	}

	while (0 < (n / WORD_SIZE))
	{
		*(size_t *)p = c_word;
		p += WORD_SIZE;
		n -= WORD_SIZE;
	}

	while (0 < n)
	{
		*p = c_char;
		++p;
		--n;
	}

	return s;
}


void *MemCpy(void *dest, const void *src, size_t n)
{
	char *p_dest = (char *)dest;
	char *p_src = (char *)src;

	assert(src);
	assert(dest);
	
	while ((0 != (MOD_WORD_SIZE((size_t)p_dest))) && (0 < n))
	{
		*p_dest = *p_src;
		++p_src;
		++p_dest;
		--n;
	}

	while (0 < (n / WORD_SIZE))
	{
		*(size_t *)p_dest = *(size_t *)p_src;
		p_dest += WORD_SIZE;
		p_src += WORD_SIZE;
		n -= WORD_SIZE;
	}

	while (0 < n)
	{
		*p_dest = *p_src;
		++p_dest;
		++p_src;
		--n;
	}

	return dest;
}

static void *ReveredMemCpy(void *dest, const void *src, size_t n)
{
	char *p_dest = NULL; 
	char *p_src = NULL;

	assert(src);
	assert(dest);

	p_src = (char *)src + n;
	p_dest = (char *)dest + n;

	while ((0 != MOD_WORD_SIZE((size_t)p_dest)) && (0 < n))
	{
		--p_src;
		--p_dest;
		*p_dest = *p_src;
		--n;
	}

	while(WORD_SIZE < n)
	{
		p_dest -= WORD_SIZE;
		p_src -= WORD_SIZE;
		n -= WORD_SIZE;
		*(size_t *)p_dest = *(size_t *)p_src;
	}

	while (0 < n)
	{
		--p_dest;
		--p_src;
		*p_dest = *p_src;
		--n;
	}

	return dest;
}

void *MemMove(void *dest, const void *src, size_t n)
{
	if ((size_t)dest < (size_t)src )
	{
		return MemCpy(dest, src, n);
	}
	else if ((size_t)src < (size_t)dest)
	{
		return ReveredMemCpy(dest, src, n);
	}

	return dest;
}