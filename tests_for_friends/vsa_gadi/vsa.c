#include <assert.h>

#include "vsa.h"

#define WORD_SIZE sizeof(word)

/* allinged(x) = x + padding */ 
#define ALLIGNED(x) (((x) + ((WORD_SIZE) - (1))) & - (WORD_SIZE))
#define PADDING(x) ((-x) & ((WORD_SIZE) - (1)))

#define HEADER_SIZE (sizeof(vsa_block_header_t))
#define CHUNK_SIZE(x) (((vsa_block_header_t*)((char*)vsa + x))->chunk_size)
#define ABS(x) ((0) < (x) ? (x) : (-x))

static void *InnerAlloc(vsa_t *vsa, size_t n_bytes);
static void VSADefragment(vsa_t *vsa);

typedef size_t word;

typedef struct vsa_chunk_header
{
	long int chunk_size;
} vsa_block_header_t;

struct vsa
{
	size_t pool_size;
};

vsa_t *VSAInit(void *mem_pool, size_t pool_size)
{
	vsa_t *vsa = NULL;
		
	assert(NULL != mem_pool);
	
	vsa = (vsa_t*)((char*)mem_pool + PADDING((size_t)mem_pool));
	
	pool_size = pool_size - PADDING((size_t)mem_pool);
	pool_size -= pool_size % WORD_SIZE;
	
	if (!(HEADER_SIZE + WORD_SIZE + sizeof(vsa_t) <= pool_size)) 
	{
		return NULL;
	}
	
	vsa->pool_size = pool_size;
	
	CHUNK_SIZE(sizeof(vsa_t)) =
	(long int)(vsa->pool_size - HEADER_SIZE - sizeof(vsa_t));

	return (vsa);
}

void *VSAAlloc(vsa_t *vsa, size_t n_bytes)
{
	void *alloc = NULL;
	
	assert(NULL != vsa);
	
	alloc = InnerAlloc(vsa, n_bytes);
	
	if (NULL == alloc)
	{
		VSADefragment(vsa);
		alloc = InnerAlloc(vsa ,n_bytes);
	} 
	
	return (alloc);
}


static void *InnerAlloc(vsa_t *vsa, size_t n_bytes)
{
	long int free_chunk_size = 0;
	long int offset = sizeof(vsa_t);
	long int tot_bytes = (long int)ALLIGNED(n_bytes);
	
	assert(NULL != vsa);

	while (((size_t)offset < vsa->pool_size) && (CHUNK_SIZE(offset) < tot_bytes))
	{
		offset += HEADER_SIZE + ABS(CHUNK_SIZE(offset));
	}
	
	if ((size_t)offset >= vsa->pool_size)
	{
		return NULL;
	}
	
	/* perfect fit, no header needed */
	if (CHUNK_SIZE(offset) == tot_bytes)
	{
		CHUNK_SIZE(offset) *= -1;

		return ((void*)((char*)vsa + offset + HEADER_SIZE));
	}
	
	/* space left, new header needed, chunk size might be 0 */
	else if ((tot_bytes + (long int)HEADER_SIZE) <= CHUNK_SIZE(offset))
	{
		free_chunk_size = CHUNK_SIZE(offset);
		CHUNK_SIZE(offset) = -tot_bytes;
		
		/* add header for remaining free space */
		CHUNK_SIZE(offset + (long int)HEADER_SIZE + tot_bytes) =
		free_chunk_size - HEADER_SIZE - tot_bytes;
		
		return ((void*)((char*)vsa + offset + HEADER_SIZE));
	}
	
	return (NULL);
}
	
void VSAFree(void *mem_chunk)
{
	assert(NULL != mem_chunk);
	
	((vsa_block_header_t*)((char*)mem_chunk - HEADER_SIZE))->chunk_size *= -1;
	
	return;
}

size_t VSALargestChunkAvailable(vsa_t *vsa)
{
	size_t chunk_location = sizeof(vsa_t);
	size_t max_chunk = 0;
	
	assert(NULL != vsa);
	
	VSADefragment(vsa);

	while (chunk_location < vsa->pool_size)
	{
		if ((long int)max_chunk < CHUNK_SIZE(chunk_location))
		{
			max_chunk = CHUNK_SIZE(chunk_location);
		}
		
		chunk_location += HEADER_SIZE + ABS(CHUNK_SIZE(chunk_location));
	}
	
	return (max_chunk);
}

static void VSADefragment(vsa_t *vsa)
{
	long int first = (long int)sizeof(vsa_t);
	long int last = 0;
	
	assert(NULL != vsa);
	
	while ((size_t)first != vsa->pool_size)
	{	
		while (((size_t)first != vsa->pool_size) && (0 > CHUNK_SIZE(first)))
		{
			first += HEADER_SIZE + ABS(CHUNK_SIZE(first));
		}
		
		last = first; 
		
		while (((size_t)last != vsa->pool_size) && (0 <= CHUNK_SIZE(last)))
		{		
			last += (long int)HEADER_SIZE + CHUNK_SIZE(last);
		}
		
		if ((size_t)first < vsa->pool_size)
		{
			CHUNK_SIZE(first) = last - first - (long int)HEADER_SIZE;
			first = last; 	
		}	
	}

	return;
}
	
	
	
	
	
	
	
	
