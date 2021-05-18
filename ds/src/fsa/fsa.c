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
	
	inner_block_size = RoundUpToWordSize(inner_block_size);
	align_diff = ((size_t)mem_pool % WORD_SIZE);
	mem_pool = (char *)mem_pool + align_diff;
	pool_size -= align_diff;
	
	fsa_head = ((fsa_t *)mem_pool);
	
	if (pool_size < (inner_block_size + round_up_struct_size))
	{
		return NULL;
	}
	
	((fsa_t *)(mem_pool))->next_free = round_up_struct_size;
	printf("first current block address: %p.\n", ((fsa_t *)(mem_pool)));
	mem_pool = (char *)mem_pool + round_up_struct_size;
	num_of_possible_blocks = pool_size / inner_block_size;
		
	while ((num_of_possible_blocks - 1) > 0)
	{
		++counter;
		((fsa_block_header_t *)(mem_pool))->next_free = (inner_block_size * counter) + round_up_struct_size;
		printf("current block address: %p.\n", ((fsa_t *)(mem_pool)));	
		mem_pool = (char *)mem_pool + inner_block_size;
		--num_of_possible_blocks;
	}
	
	((fsa_block_header_t *)(mem_pool))->next_free = 0;
	printf("current block address: %p.\n", ((fsa_t *)(mem_pool)));
	return (fsa_head);
}

void *FSAAlloc(fsa_t *fsa)
{
	fsa_block_header_t *temp = NULL;
	
	assert(fsa);	
	
	if (0 == fsa->next_free)
	{
		return (NULL);
	}
	
	temp = (fsa_block_header_t *)((char *)fsa + fsa->next_free);
	fsa->next_free = ((fsa_t *)temp)->next_free;

	return (temp); 
}

void FSAFree(fsa_t *fsa, void *mem_block)
{
	assert(fsa);	
	assert(mem_block);
/*	
	mem_block = (size_t *)fsa;
	fsa = (fsa_t *)mem_block;
*/
	((fsa_block_header_t *)mem_block)->next_free = fsa->next_free;
	fsa->next_free = (size_t)((char *)mem_block - (char *)fsa);
	
	return;
}

size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	return ((RoundUpToWordSize(block_size) * num_of_blocks) + RoundUpToWordSize(sizeof(fsa_t)));
}

size_t FSACountFree(const fsa_t *fsa)
{
	size_t counter = 0;
	fsa_block_header_t *fsa_ptr = NULL;
	
	assert(fsa);

	fsa_ptr = (fsa_block_header_t *)fsa;
	
	while (0 != fsa_ptr->next_free)
	{
		++counter;
		fsa_ptr = (fsa_block_header_t *)((char *)fsa + fsa_ptr->next_free);
	}
	
	return (counter);
}

static size_t RoundUpToWordSize(size_t num)
{
	while (0 != (num % WORD_SIZE))
	{
		++num;
	}
	
	return (num);
}
