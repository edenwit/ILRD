/*  Developer: Eden Wittenberg;									*
 *  Status: done;												*
 *  Date Of Creation: 20.05.21;									*
 *  Date Of Approval:											*
 *  Approved By: ;												*
 *  Description: variable-size blocks allocation;				*/

#include <assert.h> /* assert */
#include "vsa.h"

#define WORD_SIZE (sizeof(size_t))
#define VSA_T_SIZE (sizeof(vsa_t))
#define BLOCK_T_SIZE (sizeof(vsa_block_header_t))

static void VSADefragment(vsa_t *vsa);
static size_t RoundUpToWordSize(size_t num);
static size_t RoundDownToWordSize(size_t num);
static size_t AbsoluteValue(long num);
static void *Alloc(vsa_t *vsa, size_t n_bytes);

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
	
	assert(mem_pool);
	
	/* how many bytes are missing for alignment */
	align_diff = RoundUpToWordSize((size_t)mem_pool) - (size_t)mem_pool; 
	/* steps to take until alignment */
	mem_pool = (char *)mem_pool + align_diff;					
	/* decrease alignment from available pool size */	
	pool_size -= align_diff;									
	/* point to beginning of pool */
	vsa_head = ((vsa_t *)mem_pool);								
	
	/* check if there's enough space for atleast one block + struct */
	if (pool_size < (VSA_T_SIZE + BLOCK_T_SIZE + WORD_SIZE))    
	{
		return (NULL);
	}
	
	/* make sure pool size is aligned from both ends. */
	pool_size = RoundDownToWordSize(pool_size) - VSA_T_SIZE;  
	/* write the pool_size left after alignments and struct size */
	((vsa_t *)(mem_pool))->pool_size = pool_size;			 
	/* step to the first block */ 
	mem_pool = (char *)mem_pool + VSA_T_SIZE;				 
	((vsa_block_header_t *)(mem_pool))->chunk_size = pool_size - BLOCK_T_SIZE; 
	
	return (vsa_head);		
}

void *VSAAlloc(vsa_t *vsa, size_t n_bytes)
{
	void * alloced_ptr = NULL;
			
	assert(vsa);
	
	n_bytes = RoundUpToWordSize(n_bytes);
	/* call static alloc func */
	alloced_ptr = Alloc(vsa, n_bytes);
	
	if (NULL != alloced_ptr)
	{
		return (alloced_ptr);							
	}
	
	/* check if there is space after defragment */	
	if ((n_bytes) <= VSALargestChunkAvailable(vsa)) 
	{
		alloced_ptr = Alloc(vsa, n_bytes);	
	}	
	/* return pointer to space if found, else return NULL */
	return (alloced_ptr ? alloced_ptr : NULL);							
}

void VSAFree(void *mem_chunck)
{
	vsa_block_header_t *chunk_header = NULL;
	
	assert(mem_chunck);
	/* step back to chunk's head */
	chunk_header = (vsa_block_header_t *)((char *)mem_chunck - BLOCK_T_SIZE);
	/* check if chunk occupied */
	if ((chunk_header->chunk_size) < 0) 
	{
		/* release occupied land */
		(chunk_header->chunk_size) *= (-1); 
	}
	
	return;
}

size_t VSALargestChunkAvailable(vsa_t *vsa) 
{
	vsa_block_header_t *chunk_ptr = (vsa_block_header_t *)((char *)vsa + VSA_T_SIZE);
	size_t max_chunk = 0;
	size_t total_count = 0;
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
		total_count += (BLOCK_T_SIZE + absolute_chunk_size);
		/* step to next chunk */
		chunk_ptr = (vsa_block_header_t *)((char *)
					chunk_ptr + absolute_chunk_size + BLOCK_T_SIZE); 
	}
	
	return (max_chunk);
}

static void VSADefragment(vsa_t *vsa)
{
	vsa_block_header_t *chunk_ptr = (vsa_block_header_t *)((char *)vsa 
									+ VSA_T_SIZE);
	vsa_block_header_t *saved_chunk_ptr = NULL;
	size_t count = 0;
	size_t total_count = 0;

	assert(vsa);
	
	while (total_count < vsa->pool_size)
	{
		/* check if occupied */
		if (0 > chunk_ptr->chunk_size) 
		{
			total_count = total_count + BLOCK_T_SIZE + (chunk_ptr->chunk_size * (-1));
			chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr 
						+ (chunk_ptr->chunk_size * (-1)) + BLOCK_T_SIZE);
		}	
		
		else
		{
			saved_chunk_ptr = chunk_ptr;
			count = 0;
			
			while ((total_count < vsa->pool_size) && (0 < chunk_ptr->chunk_size))
			{
				count += (BLOCK_T_SIZE + chunk_ptr->chunk_size);
				total_count += (BLOCK_T_SIZE + chunk_ptr->chunk_size);
				chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr
				 			+ chunk_ptr->chunk_size + BLOCK_T_SIZE);
			}
			
			saved_chunk_ptr->chunk_size = count - BLOCK_T_SIZE;
		}
	}
		
	return;
}

static void *Alloc(vsa_t *vsa, size_t n_bytes)
{
	vsa_block_header_t *chunk_ptr = NULL;
	size_t total_count = 0;	
	size_t keep_size = 0;
	size_t absolute_chunk_size = 0;

	assert(vsa);

	/* point to first chunk head */
	chunk_ptr = (vsa_block_header_t *)((char *)vsa + VSA_T_SIZE); 

	while ((total_count + n_bytes) < vsa->pool_size)
	{
		if (chunk_ptr->chunk_size > (long)(n_bytes + BLOCK_T_SIZE))
		{
			keep_size = chunk_ptr->chunk_size;
			/* make space occupied */
			chunk_ptr->chunk_size = n_bytes * (-1);
			/* step to next chunk head */								
			chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + BLOCK_T_SIZE);	
			((vsa_block_header_t *)((char *)chunk_ptr + n_bytes))->chunk_size 
				= (long)(keep_size - n_bytes - BLOCK_T_SIZE);
						
			return ((void *)chunk_ptr);
		}
		
		else if ((chunk_ptr->chunk_size == (long)(n_bytes + BLOCK_T_SIZE)) ||
				 (chunk_ptr->chunk_size == (long)(n_bytes)))
		{
			/* make space occupied */
			chunk_ptr->chunk_size *= /*n_bytes*/ (-1); 		
			/* step to next chunk head */						
			chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + BLOCK_T_SIZE);
			
			return ((void *)chunk_ptr);	
		}

		absolute_chunk_size = AbsoluteValue(chunk_ptr->chunk_size);
		total_count = total_count + BLOCK_T_SIZE + absolute_chunk_size;		
		chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr
					 + absolute_chunk_size + BLOCK_T_SIZE);		
	}
	
	return (NULL);
}
/* gets a number and returns the closest round-up to word size */
static size_t RoundUpToWordSize(size_t num) 
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
