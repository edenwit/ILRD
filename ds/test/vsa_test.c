#include "vsa.h"
#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf */

#define HUGH_BLOCK 50000

static void VSATests();

int main()
{
	VSATests();
	
	return (0);
}

static void VSATests()
{
	vsa_t *vsa = NULL;
	char *huge_block = (char *)malloc(sizeof(char) * HUGH_BLOCK);
	size_t *aloc_ptr = NULL;
	size_t *aloc_ptr2 = NULL;	
	size_t *aloc_ptr3 = NULL;				
	size_t *aloc_ptr4 = NULL;					
	size_t *aloc_ptr5 = NULL;
	size_t *aloc_ptr6 = NULL;					
	size_t *aloc_ptr7 = NULL;					
	size_t *aloc_ptr8 = NULL;													
	size_t *aloc_ptr9 = NULL;													
	size_t *aloc_ptr10 = NULL;		
													
	if (NULL == huge_block)
	{
		printf("malloc failed.\n");

		return;
	}

	vsa = VSAInit((void *)(huge_block + 1), HUGH_BLOCK -1);

	if (NULL == vsa)
	{
		printf("VSAInit failed! line %d.\n", __LINE__);
	}	


	printf("Alloc address: \t\t%p\nHead struct address: \t%p\nFirst chunk address: \t%p\nPool size given: \t%ld\nPool size written: \t%ld\nChunk size written: \t%ld\n",
	 (void *)huge_block, (void *)vsa, (void *)((char *)vsa + 8), (size_t)HUGH_BLOCK, *(size_t *)(vsa), *(size_t *)((char *)vsa + 8));
	
	printf("Size before alloc: \t%ld\n", *(size_t *)((char *)vsa + 8));
	
	aloc_ptr = VSAAlloc(vsa, 100);
	
	printf("Allocated address 1: \t%p\n", (void *)aloc_ptr);
	
	aloc_ptr2 = VSAAlloc(vsa, 200);
	
	printf("Allocated address 2: \t%p\n", (void *)aloc_ptr2);
	
	printf("Addresses diff:    \t%ld\n", (char *)aloc_ptr2 - (char *)aloc_ptr);
	
	aloc_ptr3 = VSAAlloc(vsa, 100);
	
	printf("Allocated address 3: \t%p\n", (void *)aloc_ptr3);
	printf("Size written in chunk: %ld\n", *(size_t *)((char *)aloc_ptr3 + 104));
	printf("Addresses diff:    \t%ld\n", (char *)aloc_ptr3 - (char *)aloc_ptr2);

	aloc_ptr4 = VSAAlloc(vsa, 200);
	
	printf("Allocated address 4: \t%p\n", (void *)aloc_ptr4);
	
	printf("Addresses diff:    \t%ld\n", (char *)aloc_ptr4 - (char *)aloc_ptr3);
	
	aloc_ptr4 = VSAAlloc(vsa, 48);
	
	printf("Allocated address 4: \t%p\n", (void *)aloc_ptr4);
	
	printf("Addresses diff:    \t%ld\n", (char *)aloc_ptr4 - (char *)aloc_ptr3);
	
	printf("VSALargestChunkAvailable: %ld\n", VSALargestChunkAvailable(vsa));
	
	VSAFree(aloc_ptr2);
	
	aloc_ptr5 = VSAAlloc(vsa, 250);
	
	printf("Allocated address 5: \t%p\n", (void *)aloc_ptr5);
	
	printf("VSALargestChunkAvailable: %ld\n", VSALargestChunkAvailable(vsa));	
	
	VSAFree(aloc_ptr3);	

	aloc_ptr5 = VSAAlloc(vsa, 250);

	printf("Allocated address 5: \t%p\n", (void *)aloc_ptr5);
	printf("VSALargestChunkAvailable: %ld\n", VSALargestChunkAvailable(vsa));	
	
	aloc_ptr6 = VSAAlloc(vsa, 48);
	
	printf("Allocated address 6: \t%p\n", (void *)aloc_ptr6);
	
	printf("VSALargestChunkAvailable: %ld\n", VSALargestChunkAvailable(vsa));	
	
	aloc_ptr3 = VSAAlloc(vsa, 7851);
	
	printf("Allocated address 3: \t%p\n", (void *)aloc_ptr3);
	printf("Size written in chunk: \t%ld\n", *(size_t *)((char *)aloc_ptr3 + 7856));

	aloc_ptr7 = VSAAlloc(vsa, 7851);
	
	printf("Allocated address 7: \t%p\n", (void *)aloc_ptr7);
	printf("Size written in chunk: \t%ld\n", *(size_t *)((char *)aloc_ptr7 + 7856));
	
	aloc_ptr8 = VSAAlloc(vsa, 30000);
	
	printf("Allocated address 8: \t%p\n", (void *)aloc_ptr8);
	printf("Size written in chunk: \t%ld\n", *(size_t *)((char *)aloc_ptr8 + 30000));
	
	aloc_ptr9 = VSAAlloc(vsa, 4000);
	
	printf("Allocated address 9: \t%p\n", (void *)aloc_ptr9);
	
	VSAFree(aloc_ptr3);	
	VSAFree(aloc_ptr7);	
	
	aloc_ptr10 = VSAAlloc(vsa, 9000);
	
	printf("Allocated address 10: \t%p\n", (void *)aloc_ptr10);
	printf("Size written in chunk: \t%ld\n", *(size_t *)((char *)aloc_ptr10 + 9000));
	
	aloc_ptr9 = VSAAlloc(vsa, 6704);
	
	printf("Allocated address 9: \t%p\n", (void *)aloc_ptr9);
	printf("Size written in chunk: \t%ld\n", *(size_t *)((char *)aloc_ptr9 + 6720));			
	
	free(huge_block);
	
	return;
}
