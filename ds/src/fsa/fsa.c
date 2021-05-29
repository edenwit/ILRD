/*  Developer: Eden Wittenberg;									*
 *  Status: done;												*
 *  Date Of Creation:18.05.21;									*
 *  Date Of Approval:19.05.21;									*
 *  Approved By: Eden Samama;									*
 *  Description: fixed-size blocks allocation;					*/

#include <assert.h> /* assert */
#include "fsa.h"

#define WORD_SIZE (sizeof(size_t))

static size_t RoundUpToWordSize(size_t num);

struct fsa
{
	size_t next_free;
};

typedef struct fsa_block_header
{
	size_t next_free;
} fsa_block_header_t;

fsa_t *FSAInit(void *mem_pool, size_t pool_size, size_t inner_block_size)
{
	fsa_t *fsa_head = NULL;
	size_t counter = 0;
	size_t round_up_struct_size = RoundUpToWordSize(sizeof(fsa_t));
	size_t num_of_possible_blocks = 0;
	size_t align_diff = 0;
	
	assert(mem_pool);
	assert(pool_size > inner_block_size);
	assert(0 < inner_block_size);
		
	inner_block_size = RoundUpToWordSize(inner_block_size);		/* round up block size to word size multiple */
	align_diff = ((size_t)mem_pool % WORD_SIZE); 				/* how many bytes are missing for alignment */
	mem_pool = (char *)mem_pool + align_diff;					/* steps to take until alignment */
	pool_size -= align_diff;									/* decrease alignment from available pool size */
	fsa_head = ((fsa_t *)mem_pool);								/* point to beginning of pool */
	
	if (pool_size < (inner_block_size + round_up_struct_size))	/* check if there's enough space for atleast one block + struct */
	{
		return (NULL);
	}
	
	((fsa_t *)(mem_pool))->next_free = round_up_struct_size;	/* mark the next available block as the first block */
	mem_pool = (char *)mem_pool + round_up_struct_size;			/* step to the first block */
	num_of_possible_blocks = (pool_size - WORD_SIZE) / inner_block_size;		/* calculate how many blocks can i have*/
		
	while (1 < num_of_possible_blocks)
	{
		++counter;
		/* mark the next available block as the next block */
		((fsa_block_header_t *)(mem_pool))->next_free = (inner_block_size * counter) + round_up_struct_size; 

		mem_pool = (char *)mem_pool + inner_block_size;  		/* step to the next block */
		--num_of_possible_blocks;
	}
	
	((fsa_block_header_t *)(mem_pool))->next_free = 0;			/* mark the end of available blocks */

	return (fsa_head);
}

void *FSAAlloc(fsa_t *fsa)
{
	fsa_block_header_t *temp = NULL;
	
	assert(fsa);	
	
	if (0 == fsa->next_free)										/* check if there are free blocks */
	{
		return (NULL);
	}
	
	temp = (fsa_block_header_t *)((char *)fsa + fsa->next_free);	/* save location of current block */
	fsa->next_free = ((fsa_t *)temp)->next_free;					/* mark next free block as the one current block pointed to */

	return ((void *)temp); 											/* return saved location of current block */
}

void FSAFree(fsa_t *fsa, void *mem_block)
{
	assert(fsa);	
	assert(mem_block);

	((fsa_block_header_t *)mem_block)->next_free = fsa->next_free; /* the newly freed block points to the next free fsa pointed to */
	fsa->next_free = (size_t)((char *)mem_block - (char *)fsa);		/* mark next free block as the one i just freed */
	
	return;
}


size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	assert(0 < num_of_blocks);
	assert(0 < block_size);
	
	/* calculate size needed for all rounded sizes of struct and block size */
	return ((RoundUpToWordSize(block_size) * num_of_blocks) + RoundUpToWordSize(sizeof(fsa_t)));
}

size_t FSACountFree(const fsa_t *fsa)
{
	size_t counter = 0;
	fsa_block_header_t *fsa_ptr = NULL;
	
	assert(fsa);

	fsa_ptr = (fsa_block_header_t *)fsa; /* point to head struct */
	
	while (0 != fsa_ptr->next_free)
	{
		++counter;
		fsa_ptr = (fsa_block_header_t *)((char *)fsa + fsa_ptr->next_free); /* point to next block */
	}
	
	return (counter);
}

/* gets a number and returns the closest round-up to word size */
static size_t RoundUpToWordSize(size_t num)
{
	return (num + ((WORD_SIZE - (num % WORD_SIZE)) % WORD_SIZE));
}
