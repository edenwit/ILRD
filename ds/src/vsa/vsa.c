#include <assert.h> /* assert */
#include "vsa.h"

#define WORD_SIZE (sizeof(size_t))

static void VSADefragment(vsa_t *vsa);
static size_t RoundUpToWordSize(size_t num);
static size_t RoundDownToWordSize(size_t num);
static size_t AbsoluteValue(long num);

struct vsa
{
	size_t pool_size;
};

typedef struct vsa_chunk_header
{
	long int chunk_size;
} vsa_block_header_t;

vsa_t *VSAInit(void *mem_pool, size_t pool_size)
{
	vsa_t *vsa_head = NULL;
	size_t align_diff = 0;
	size_t round_up_struct_size = RoundUpToWordSize(sizeof(vsa_t));
	
	assert(mem_pool);
	
	align_diff = ((size_t)mem_pool % WORD_SIZE); 				/* how many bytes are missing for alignment */
	mem_pool = (char *)mem_pool + align_diff;					/* steps to take until alignment */
	pool_size -= align_diff;									/* decrease alignment from available pool size */	
	vsa_head = ((vsa_t *)mem_pool);								/* point to beginning of pool */
	
	if (pool_size < (round_up_struct_size + sizeof(vsa_block_header_t) + WORD_SIZE))/* check if there's enough space for atleast one block + struct */
	{
		return (NULL);
	}
	
	pool_size = RoundDownToWordSize(pool_size) - round_up_struct_size;
	((vsa_t *)(mem_pool))->pool_size = pool_size;	/* write the pool_size left after alignments and struct size */
	mem_pool = (char *)mem_pool + round_up_struct_size;			/* step to the first block */
	((vsa_block_header_t *)(mem_pool))->chunk_size = pool_size - RoundUpToWordSize(sizeof(vsa_block_header_t));
	
	return vsa_head;		
}

void *VSAAlloc(vsa_t *vsa, size_t n_bytes)
{
	vsa_block_header_t *chunk_ptr = NULL;
	size_t total_count = 0;	
	size_t keep_size = 0;
	size_t absolute_chunk_size = 0;
	size_t round_up_struct_size = RoundUpToWordSize(sizeof(vsa_t));	
	size_t chunk_srtuct_size = RoundUpToWordSize(sizeof(vsa_block_header_t));

	assert(vsa);
	
	n_bytes = RoundUpToWordSize(n_bytes);
	
	chunk_ptr = (vsa_block_header_t *)((char *)vsa + round_up_struct_size);

	while ((total_count + n_bytes) < vsa->pool_size)
	{
		if (chunk_ptr->chunk_size >= (long)n_bytes)
		{
			keep_size = chunk_ptr->chunk_size;
			chunk_ptr->chunk_size = n_bytes * (-1);
			chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + chunk_srtuct_size);						
	
			if (keep_size > n_bytes)
			{

				((vsa_block_header_t *)((char *)chunk_ptr + n_bytes))->chunk_size = (long)(keep_size - n_bytes - chunk_srtuct_size);

			}

			return (void *)chunk_ptr;
		}

		absolute_chunk_size = AbsoluteValue(chunk_ptr->chunk_size);
		total_count = total_count + chunk_srtuct_size + absolute_chunk_size;		
		chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + absolute_chunk_size + chunk_srtuct_size);		
	}
		
	if ((n_bytes + chunk_srtuct_size) < VSALargestChunkAvailable(vsa))
	{
		total_count = 0;
		chunk_ptr = (vsa_block_header_t *)((char *)vsa + round_up_struct_size);
	
		while ((total_count + n_bytes) < vsa->pool_size)
		{
			if (chunk_ptr->chunk_size >= (long)n_bytes)
			{
				keep_size = chunk_ptr->chunk_size;
				chunk_ptr->chunk_size = n_bytes * (-1);
				chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + chunk_srtuct_size);						
				
				if (keep_size > n_bytes)
				{
					((vsa_block_header_t *)((char *)chunk_ptr + n_bytes))->chunk_size = (long)(keep_size - n_bytes - chunk_srtuct_size);
				}

				return (void *)chunk_ptr;
			}
			
			absolute_chunk_size = AbsoluteValue(chunk_ptr->chunk_size);
			total_count += (chunk_srtuct_size + absolute_chunk_size);		
			chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + absolute_chunk_size + chunk_srtuct_size);		
		}
	}
	
	return (NULL);	
}

void VSAFree(void *mem_chunck)
{
	assert(mem_chunck);
	
	mem_chunck = (vsa_block_header_t *)((char *)mem_chunck - sizeof(vsa_block_header_t));	
	
	if ((((vsa_block_header_t *)(mem_chunck))->chunk_size) < 0)
	{
		(((vsa_block_header_t *)(mem_chunck))->chunk_size) *= (-1);
	}
	
	return;
}

size_t VSALargestChunkAvailable(vsa_t *vsa) /* -> here we call VSADefragment */
{
	vsa_block_header_t *chunk_ptr = (vsa_block_header_t *)((char *)vsa + RoundUpToWordSize(sizeof(vsa_t)));
	size_t max_chunk = 0;
	size_t total_count = 0;
	size_t chunk_srtuct_size = RoundUpToWordSize(sizeof(vsa_block_header_t));
	size_t absolute_chunk_size = 0;
	assert(vsa);
	
	VSADefragment(vsa);
	
	while (total_count < vsa->pool_size)
	{
		if (chunk_ptr->chunk_size > (long)max_chunk)
		{
			max_chunk = (size_t)chunk_ptr->chunk_size;
		}
		absolute_chunk_size = AbsoluteValue(chunk_ptr->chunk_size);
		total_count += (chunk_srtuct_size + absolute_chunk_size);
		chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + absolute_chunk_size + chunk_srtuct_size);		
	}
	
	return (max_chunk);
}

static void VSADefragment(vsa_t *vsa)
{
	vsa_block_header_t *chunk_ptr = (vsa_block_header_t *)((char *)vsa + RoundUpToWordSize(sizeof(vsa_t)));
	vsa_block_header_t *saved_chunk_ptr = NULL;
	size_t count = 0;
	size_t total_count = 0;
	size_t chunk_srtuct_size = RoundUpToWordSize(sizeof(vsa_block_header_t));
	size_t absolute_chunk_size = 0;

	assert(vsa);
	
	while (total_count < vsa->pool_size)
	{
		if (0 > chunk_ptr->chunk_size)
		{
			absolute_chunk_size = AbsoluteValue(chunk_ptr->chunk_size);
			total_count = total_count + chunk_srtuct_size + absolute_chunk_size;		
			chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + absolute_chunk_size + chunk_srtuct_size);
		}	
		
		else
		{
			saved_chunk_ptr = chunk_ptr;
			count = 0;
			
			while ((total_count < vsa->pool_size) && (0 < chunk_ptr->chunk_size))
			{
				count += (chunk_srtuct_size + chunk_ptr->chunk_size);
				total_count += (chunk_srtuct_size + chunk_ptr->chunk_size);
				chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + chunk_ptr->chunk_size + chunk_srtuct_size);
			}
			
			saved_chunk_ptr->chunk_size = count - chunk_srtuct_size;
		}
	}
		
	return;
}

static size_t RoundUpToWordSize(size_t num) /* gets a number and returns the closest round-up to word size */
{
	return (num + ((WORD_SIZE - (num % WORD_SIZE)) % WORD_SIZE));
}

static size_t RoundDownToWordSize(size_t num)
{
	return (num - ((num % WORD_SIZE) % WORD_SIZE));
}

static size_t AbsoluteValue(long num)
{
	return ((0 > num) ? (num * (-1)) : (num));
}
