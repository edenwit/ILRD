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
	
	if (pool_size < (round_up_struct_size + sizeof(vsa_block_header_t) + WORD_SIZE))	/* check if there's enough space for atleast one block + struct */
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
	
	assert(vsa);
	
	n_bytes = RoundUpToWordSize(n_bytes);
	
	/*printf("Inside alloc vsa address: %p\n",(void *)vsa);*/
	chunk_ptr = (vsa_block_header_t *)((char *)vsa + RoundUpToWordSize(sizeof(vsa_t)));
	/*printf("Struct size after round up: %ld\n",RoundUpToWordSize(sizeof(vsa_t)));*/
/*	printf("Inside alloc first chunk address: %p\n",(void *)chunk_ptr);	*/
	while ((total_count + n_bytes) < vsa->pool_size)
	{
		if (chunk_ptr->chunk_size >= (long)n_bytes)
		{
			/*printf("Chunk size now: %ld\n", chunk_ptr->chunk_size);*/
			/*printf("Found address large enough on first try!\n");*/
			keep_size = chunk_ptr->chunk_size;
			/*printf("Keep size: \t\t%ld\n", keep_size);*/
			chunk_ptr->chunk_size = n_bytes * (-1);
			/*printf("chunk_ptr->chunk_size: \t%ld\n", n_bytes * (-1));		*/
			chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + RoundUpToWordSize(sizeof(vsa_block_header_t)));						
			/*printf("chunk_ptr: \t\t%p\n", (void *)chunk_ptr);	
			printf("n_bytes in dec: %d\n", n_bytes);							
			printf("n_bytes in hex: %0x\n", n_bytes);		
			printf("next struct supposed to be at: %p\n", (char *)chunk_ptr + n_bytes);			*/		
			if (keep_size > n_bytes)
			{
				chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + n_bytes);
				((vsa_block_header_t *)(char *)chunk_ptr)->chunk_size = (long)(keep_size - n_bytes - RoundUpToWordSize(sizeof(vsa_block_header_t)));
		/*	printf("put next struct at: \t%p\n", (void *)chunk_ptr);
			printf("chunk size: \t\t%ld\n", ((vsa_block_header_t *)(char *)chunk_ptr)->chunk_size);	*/
				chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr - n_bytes);
			}
/*			printf("Returned address: \t%p\n", (void *)chunk_ptr);	*/
			return (void *)chunk_ptr;
		}

		absolute_chunk_size = AbsoluteValue(chunk_ptr->chunk_size);
		total_count = total_count + RoundUpToWordSize(sizeof(vsa_block_header_t)) + absolute_chunk_size;		
			chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + absolute_chunk_size + RoundUpToWordSize(sizeof(vsa_block_header_t)));		
		/*printf("Skipped to next chunk. address: %p\n chunk value: \t%ld\n", (void *)chunk_ptr, chunk_ptr->chunk_size);						*/
	}
	
/*	printf("Counldn't find large enough space. Calling VSALargestChunkAvailable!\n");	
	printf("Available space: %ld\n", VSALargestChunkAvailable(vsa));		*/
	
	if ((n_bytes + sizeof(vsa_block_header_t)) < VSALargestChunkAvailable(vsa))
	{

		/*printf("Called VSALargestChunkAvailable and Found address large enough!\n");*/
		total_count = 0;
		chunk_ptr = (vsa_block_header_t *)((char *)vsa + RoundUpToWordSize(sizeof(vsa_t)));
	
			while ((total_count + n_bytes) < vsa->pool_size)
			{
				if (chunk_ptr->chunk_size >= (long)n_bytes)
				{
					/*printf("Chunk size now: %ld\n", chunk_ptr->chunk_size);*/
					/*printf("Found address large enough on first try!\n");*/
					keep_size = chunk_ptr->chunk_size;
/*					printf("Keep size: \t\t%ld\n", keep_size);*/
					chunk_ptr->chunk_size = n_bytes * (-1);
/*					printf("chunk_ptr->chunk_size: \t%ld\n", n_bytes * (-1));		*/
					chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + RoundUpToWordSize(sizeof(vsa_block_header_t)));						
/*					printf("chunk_ptr: \t\t%p\n", (void *)chunk_ptr);	
					printf("n_bytes in dec: %d\n", n_bytes);							
					printf("n_bytes in hex: %0x\n", n_bytes);		
					printf("next struct supposed to be at: %p\n", (char *)chunk_ptr + n_bytes);					*/
					if (keep_size > n_bytes)
					{
						chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + n_bytes);
						((vsa_block_header_t *)(char *)chunk_ptr)->chunk_size = (long)(keep_size - n_bytes - RoundUpToWordSize(sizeof(vsa_block_header_t)));
						/*printf("put next struct at: \t%p\n", (void *)chunk_ptr);
						printf("chunk size: \t\t%ld\n", ((vsa_block_header_t *)(char *)chunk_ptr)->chunk_size);	*/
						chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr - n_bytes);
					}
					
/*					printf("Returned address: \t%p\n", (void *)chunk_ptr);	*/
					return (void *)chunk_ptr;
				}

				absolute_chunk_size = AbsoluteValue(chunk_ptr->chunk_size);
				total_count = total_count + RoundUpToWordSize(sizeof(vsa_block_header_t)) + absolute_chunk_size;		
				chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + absolute_chunk_size + RoundUpToWordSize(sizeof(vsa_block_header_t)));		
/*				printf("Skipped to next chunk. address: %p\n chunk value: \t%ld\n", (void *)chunk_ptr, chunk_ptr->chunk_size);						*/
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
	size_t absolute_chunk_size = 0;
	assert(vsa);
	
	VSADefragment(vsa);
	
	while (total_count < vsa->pool_size)
	{
		/*printf("chunk size: %ld\n", chunk_ptr->chunk_size);		*/
		if (chunk_ptr->chunk_size > (long)max_chunk)
		{
			max_chunk = (size_t)chunk_ptr->chunk_size;
			/*printf("max in long: %ld, max in size_t: %ld\n", (long)max_chunk, max_chunk);		*/
		}
		absolute_chunk_size = AbsoluteValue(chunk_ptr->chunk_size);
		total_count = total_count + RoundUpToWordSize(sizeof(vsa_block_header_t)) + absolute_chunk_size;		
		chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + absolute_chunk_size + RoundUpToWordSize(sizeof(vsa_block_header_t)));		
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

	printf("Inside VSADefragment\n");

	assert(vsa);
	
	while (total_count < vsa->pool_size)
	{
		if (0 > chunk_ptr->chunk_size)
		{
			absolute_chunk_size = AbsoluteValue(chunk_ptr->chunk_size);
			total_count = total_count + RoundUpToWordSize(sizeof(vsa_block_header_t)) + absolute_chunk_size;		
			chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + absolute_chunk_size + RoundUpToWordSize(sizeof(vsa_block_header_t)));
		}	
		
		else
		{
			printf("found positive space: %ld\n", chunk_ptr->chunk_size);
			saved_chunk_ptr = chunk_ptr;
			count = 0;
			
			printf("for next round: chunk size: %ld\n",chunk_ptr->chunk_size);
			while ((total_count < vsa->pool_size) && (0 < chunk_ptr->chunk_size))
			{
				printf("In with count %ld\n", count);
				count = count + chunk_srtuct_size + chunk_ptr->chunk_size;
				printf("added %ld to count. total: %ld\n", chunk_srtuct_size + chunk_ptr->chunk_size, count);
				total_count = total_count + chunk_srtuct_size + chunk_ptr->chunk_size;
				printf("Taking %ld steps\n", chunk_ptr->chunk_size + chunk_srtuct_size);		
				chunk_ptr = (vsa_block_header_t *)((char *)chunk_ptr + chunk_ptr->chunk_size + chunk_srtuct_size);
				printf("for next round: chunk size: %ld\n",chunk_ptr->chunk_size);
			}

			
			saved_chunk_ptr->chunk_size = count - chunk_srtuct_size;
			printf("Chunk size written as: %ld\n", saved_chunk_ptr->chunk_size);
		}
	}
		
	return;
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
	if (0 > num)
	{
		return (num * (-1));
	}
	
	return ((size_t)num);
}
