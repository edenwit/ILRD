#include "fsa.h"
#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf */


#define HUGU_BLOCK 500

static void FSATests();

int main()
{
	FSATests();
	
	return (0);
}

static void FSATests()
{
	fsa_t *fsa = NULL;
	char *huge_block = (char *)malloc(sizeof(char) * HUGU_BLOCK);
	size_t num_of_blocks[] =	{10, 20, 1, 5, 8, 9, 15, 0, 50};
	size_t block_size[] =		{10, 20, 1, 5, 8, 9, 15, 0, 50};
	size_t exp_res[] =			{168, 488, 16, 48, 72, 152, 248, 8, 2808};	
	size_t arr_size = sizeof(num_of_blocks) / sizeof(num_of_blocks[0]);
	size_t i = 0;
	size_t free_blocks = 0;
	size_t block_exm = 50;
	size_t *aloc_ptr = NULL;
	size_t *aloc_ptr2 = NULL;	
	size_t *aloc_ptr_to_free = NULL;	
	
	if (NULL == huge_block)
	{
		printf("malloc failed.\n");

		return;
	}
	
	for (i = 0; i < arr_size; ++i)
	{
		if (FSASuggestSize(num_of_blocks[i], block_size[i]) != exp_res[i])
		{
			printf("Struct size: %ld, block size: %ld, num of blocks: %ld. Suggested: %ld\n", sizeof(size_t), block_size[i], num_of_blocks[i], 				FSASuggestSize(num_of_blocks[i], block_size[i]));
		}
	}
	
	fsa = FSAInit((void *)huge_block, HUGU_BLOCK, block_exm);

	if (NULL == fsa)
	{
		printf("FSAInit failed! line %d.\n", __LINE__);
	}
	
/*	suggested_size = FSASuggestSize(); */	
	
	free_blocks = FSACountFree(fsa);

	if (free_blocks != ((HUGU_BLOCK - 8) / (block_exm + 6)))
	{
		printf("FSACountFree fail! exp: %ld, actual: %ld.\n", free_blocks, ((HUGU_BLOCK - 8) / block_exm));	
	}
	
	aloc_ptr = FSAAlloc(fsa);
	
	printf("Alloc address: %p.\n", aloc_ptr);		
	aloc_ptr = FSAAlloc(fsa);
	
	printf("Alloc address: %p.\n", aloc_ptr);		
		aloc_ptr2 = FSAAlloc(fsa);
	
	printf("Alloc address: %p.\n", aloc_ptr2);		
		aloc_ptr = FSAAlloc(fsa);
	
	printf("Alloc2 address: %p.\n", aloc_ptr);		
		aloc_ptr = FSAAlloc(fsa);
	
	printf("Alloc address to free: %p.\n", aloc_ptr);		
		aloc_ptr_to_free = FSAAlloc(fsa);
	
	printf("Alloc address: %p.\n", aloc_ptr_to_free);		
		aloc_ptr = FSAAlloc(fsa);
	
	printf("Alloc address: %p.\n", aloc_ptr);		
		
		aloc_ptr = FSAAlloc(fsa);
	
	printf("Alloc address: %p.\n", aloc_ptr);		
		aloc_ptr = FSAAlloc(fsa);
	
	printf("Alloc address: %p.\n", aloc_ptr);		
				
	free_blocks = FSACountFree(fsa);

	if (0 != free_blocks)
	{
		printf("FSACountFree fail! exp: %ld, actual: %ld.\n", 0, free_blocks);	
	}

	FSAFree(fsa, aloc_ptr_to_free);

	free_blocks = FSACountFree(fsa);
	
	if (1 != free_blocks)	
	{
		printf("FSACountFree fail! exp: %ld, actual: %ld.\n", 1, free_blocks);	
	}			
	
	aloc_ptr = FSAAlloc(fsa);
	
	if (aloc_ptr != aloc_ptr_to_free)
	{
		printf("FSAFree failed.\n");
	}
	
	free_blocks = FSACountFree(fsa);

	if (0 != free_blocks)
	{
		printf("FSACountFree fail! exp: %ld, actual: %ld.\n", 0, free_blocks);	
	}
		
	FSAFree(fsa, aloc_ptr2);
	
	free_blocks = FSACountFree(fsa);	
	
	if (1 != free_blocks)
	{
		printf("FSACountFree fail! exp: %ld, actual: %ld.\n", 1, free_blocks);	
	}
		
	aloc_ptr = FSAAlloc(fsa);

	if (aloc_ptr != aloc_ptr2)
	{
		printf("FSAFree failed.\n");
	}
	
	return;
}

/*
fsa_t *FSAInit(void *mem_pool, size_t pool_size, size_t inner_block_size)
{
	fsa_t *fsa_head = NULL;
	size_t counter = 0;
	size_t round_up_struct_size = RoundUpToWordSize(sizeof(fsa_t));
	size_t num_of_possible_blocks = 0;
	
	assert(mem_pool);
	
	inner_block_size = RoundUpToWordSize(inner_block_size);

	while (0 != ((*(size_t *)&mem_pool) % WORD_SIZE))
	{
		mem_pool = (size_t *)mem_pool + 1;
		--pool_size;		
	}
	
	fsa_head = ((fsa_t *)mem_pool);
	
	if (pool_size < (inner_block_size + round_up_struct_size))
	{
		return NULL;
	}
	
	(*(size_t *)&mem_pool) = round_up_struct_size;
	mem_pool = (size_t *)mem_pool + round_up_struct_size;
	num_of_possible_blocks = pool_size / inner_block_size;
	
	while ((num_of_possible_blocks - 1) > 0)
	{
		++counter;
		(*(size_t *)&mem_pool) = inner_block_size * counter;
		mem_pool = (size_t *)mem_pool + inner_block_size;
		--num_of_possible_blocks;
	}
	
	(*(size_t *)&mem_pool) = 0;
	
	return (fsa_head);
}

void *FSAAlloc(fsa_t *fsa)
{
	size_t *temp = NULL;
	
	assert(fsa);	
	
	if (0 == *(size_t *)&fsa)
	{
		return (NULL);
	}
	
	temp = (size_t *)fsa;
	*(size_t *)&fsa = *(size_t *)&temp;
	
	return (temp); 
}

void FSAFree(fsa_t *fsa, void *mem_block)
{
	assert(fsa);	
	assert(mem_block);
	
	mem_block = (size_t *)fsa;
	fsa = (fsa_t *)mem_block;
	
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
	
	if (0 == *(size_t *)&fsa)
	{
		return (0);
	}
	
	fsa_ptr = (fsa_block_header_t *)fsa;
	
	while (0 != *(size_t *)&fsa_ptr)
	{
		fsa_ptr += *(size_t *)&fsa_ptr;
		++counter;
	}
	
	return (counter);
}

*/
