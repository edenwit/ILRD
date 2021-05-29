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
	size_t num_of_blocks[] =	{10, 20, 1, 5, 8, 9, 15, 30, 50};
	size_t block_size[] =		{10, 20, 1, 5, 8, 9, 15, 30, 50};
	size_t exp_res[] =			{168, 488, 16, 48, 72, 152, 248, 8, 2808};	
	size_t arr_size = sizeof(num_of_blocks) / sizeof(num_of_blocks[0]);
	size_t i = 0;
	size_t free_blocks = 0;
	size_t block_exm = 36;
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
	fsa = FSAInit((void *)huge_block, 100, 90);

	if (NULL != fsa)
	{
		printf("FSAInit failed! line %d.\n", __LINE__);
		free_blocks = FSACountFree(fsa);
		
		if (0 != free_blocks)
		{
		printf("FSACountFree fail! exp: %ld, actual: %ld.\n", free_blocks, FSACountFree(fsa));	
		}
			
	}
	

	fsa = FSAInit((void *)huge_block, 100, block_exm);

	if (NULL == fsa)
	{
		printf("FSAInit failed! line %d.\n", __LINE__);
	}
	
	free_blocks = FSACountFree(fsa);
	
	if (1 != free_blocks)
	{
		printf("FSACountFree fail! exp: %ld, actual: %ld.\n", free_blocks, FSACountFree(fsa));	
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
	
	printf("Alloc address: %p.\n", (void *)aloc_ptr);		
	aloc_ptr = FSAAlloc(fsa);
	
	printf("Alloc address: %p.\n", (void *)aloc_ptr);		
		aloc_ptr2 = FSAAlloc(fsa);
	
	printf("Alloc address: %p.\n", (void *)aloc_ptr2);		
		aloc_ptr = FSAAlloc(fsa);
	
	printf("Alloc2 address: %p.\n", (void *)aloc_ptr);		
		aloc_ptr = FSAAlloc(fsa);
	
	printf("Alloc address to free: %p.\n", (void *)aloc_ptr);		
		aloc_ptr_to_free = FSAAlloc(fsa);
	
	printf("Alloc address: %p.\n", (void *)aloc_ptr_to_free);		
		aloc_ptr = FSAAlloc(fsa);
	
	printf("Alloc address: %p.\n", (void *)aloc_ptr);		
		
		aloc_ptr = FSAAlloc(fsa);
	
	printf("Alloc address: %p.\n", (void *)aloc_ptr);		
		aloc_ptr = FSAAlloc(fsa);
	
	printf("Alloc address: %p.\n", (void *)aloc_ptr);		
				
	free_blocks = FSACountFree(fsa);

	if (0 != free_blocks)
	{
		printf("FSACountFree fail! exp: %d, actual: %ld.\n", 0, free_blocks);	
	}

	FSAFree(fsa, aloc_ptr_to_free);

	free_blocks = FSACountFree(fsa);
	
	if (1 != free_blocks)	
	{
		printf("FSACountFree fail! exp: %d, actual: %ld.\n", 1, free_blocks);	
	}			
	
	aloc_ptr = FSAAlloc(fsa);
	
	if (aloc_ptr != aloc_ptr_to_free)
	{
		printf("FSAFree failed.\n");
	}
	
	free_blocks = FSACountFree(fsa);

	if (0 != free_blocks)
	{
		printf("FSACountFree fail! exp: %d, actual: %ld.\n", 0, free_blocks);	
	}
		
	FSAFree(fsa, aloc_ptr2);
	
	free_blocks = FSACountFree(fsa);	
	
	if (1 != free_blocks)
	{
		printf("FSACountFree fail! exp: %d, actual: %ld.\n", 1, free_blocks);	
	}
		
	aloc_ptr = FSAAlloc(fsa);

	if (aloc_ptr != aloc_ptr2)
	{
		printf("FSAFree failed.\n");
	}
	
	free(huge_block);
	
	return;
}
