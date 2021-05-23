#include "vsa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WORD_SIZE (sizeof(size_t))
#define TEST_SIZE 10

static size_t AlignToUpperWS(size_t align_it)
{
	size_t aligned = 0;
	
	aligned = WORD_SIZE * (align_it/WORD_SIZE);
	
	return  (  align_it % WORD_SIZE ?  
				      aligned +  WORD_SIZE : aligned);
}


static int RandTest()
{

	int block_size_arr[TEST_SIZE];
	size_t i = 0;
	size_t tot_space_needed = WORD_SIZE;
	size_t tot_space_asked =0;
	size_t tot_space_left =0;
	size_t middle_size = 0;
	size_t middle_two_space = 0;
	size_t last_two_space = 0;
	void *rand_pool = NULL;
	void *cur_alloc = NULL;
	void *middle = NULL;
	void *next_to_middle = NULL;
	void *new_middle = NULL;
	void *last = NULL;
	void *before_last = NULL;
	void *prev_alloc = NULL;
	vsa_t* rand_vsa =NULL;
	
	printf("I randomly chose blocks of the following size:\n");	
	
	for( i = 0 ; i < TEST_SIZE ; i++ ) 
	{ /* rand nums up to 1000*/
      block_size_arr[i] =  AlignToUpperWS(1+(rand() % 10)/2);
      tot_space_needed += block_size_arr[i] + WORD_SIZE;
      tot_space_asked += block_size_arr[i] ;
      printf("|  %d  |",block_size_arr[i]);
    }
      puts("");
      puts("");
	printf("The total space you asked is:  %d ,I'm allocating %d.  %d should be for the headers. \n",tot_space_asked, tot_space_needed, TEST_SIZE * WORD_SIZE + WORD_SIZE);

	rand_pool = (void*)malloc(tot_space_needed); 	
	
	rand_vsa = VSAInit(rand_pool, tot_space_needed);

	if((tot_space_needed - 2*WORD_SIZE) != VSALargestChunkAvailable(rand_vsa))
	{	
		printf("Somthing is wrong in first Largest Chunk, you got  %d\n",VSALargestChunkAvailable(rand_vsa));
	}
	
	tot_space_left = VSALargestChunkAvailable(rand_vsa);
	
	prev_alloc = rand_vsa;
	
	for( i = 0 ; i < TEST_SIZE ; i++ ) 
	{
		cur_alloc = VSAAlloc(rand_vsa, block_size_arr[i] );
		tot_space_left -= WORD_SIZE +  block_size_arr[i] ;
		
		if(i == (TEST_SIZE/2))
		{
			middle = cur_alloc;
			middle_two_space += block_size_arr[i];
			middle_size  +=block_size_arr[i];
		}
		
		if(i == (TEST_SIZE/2) + 1)
		{
			next_to_middle = cur_alloc;
			middle_two_space += block_size_arr[i] + WORD_SIZE;			
		}
		
		if(i == TEST_SIZE -2)
		{
			before_last = cur_alloc;
			last_two_space += block_size_arr[i];			
		}
		
		if(i == TEST_SIZE -1)
		{
			last = cur_alloc;
			last_two_space += block_size_arr[i] + WORD_SIZE;			
		}

		
		if(tot_space_left != VSALargestChunkAvailable(rand_vsa) && tot_space_left != -WORD_SIZE)
		{	
			printf("Somthing is wrong in Largest Chunk, you got  %d\n",VSALargestChunkAvailable(rand_vsa));
		}

		if(i > 0 && (char*)cur_alloc - (char*)prev_alloc != (block_size_arr[i-1]  + WORD_SIZE))
		{	
			printf("Somthing is wrong in offseting the allocated areas, you got  %d\n", (char*)cur_alloc - (char*)prev_alloc );
		}

		prev_alloc = cur_alloc;

    }
	tot_space_left = 0;

		if(tot_space_left != VSALargestChunkAvailable(rand_vsa))
		{	
			printf("Something is wrong in Largest Chunk, you got  %d\n",VSALargestChunkAvailable(rand_vsa));
		}
	
		if((char*)next_to_middle - (char*)middle != middle_size + WORD_SIZE)
		{	
			printf("Something is wrong in Largest Chunk, you got  %d\n",(char*)next_to_middle - (char*)middle);
		}
	
	VSAFree(middle);
	VSAFree(next_to_middle);
	
		if(middle_two_space != VSALargestChunkAvailable(rand_vsa))
		{	
			printf("Something is wrong in Largest Chunk, you got  %d\n",VSALargestChunkAvailable(rand_vsa));
		}
	
	new_middle = VSAAlloc(rand_vsa, middle_two_space - WORD_SIZE);
	
	VSAFree(last);
	VSAFree(before_last);
	
		if(last_two_space != VSALargestChunkAvailable(rand_vsa))
		{	
			printf("Something is wrong in Largest Chunk, you got  %d\n",VSALargestChunkAvailable(rand_vsa));
		}
	
	free(rand_vsa);	
		
	return 0;
}
static void SmokeTest()
{
	void *small_pool = NULL;
	void *small_chunk1 = NULL;
	void *small_chunk2 = NULL;
	void *med_chunk = NULL;	
	void *big_chunk = NULL;
	vsa_t* small_vsa;

	small_pool = (void*)malloc(190); 
	small_pool = (char*)small_pool + 10;
	small_vsa = VSAInit(small_pool, 180);
	
	if(152 != VSALargestChunkAvailable(small_vsa))
	{	
		printf("Somthing is wrong in first Largest Chunk, line:  %d\n",VSALargestChunkAvailable(small_vsa));
	}
	
	small_chunk1 =  VSAAlloc(small_vsa, 5);
	med_chunk =  VSAAlloc(small_vsa, 20);
	big_chunk =  VSAAlloc(small_vsa, 60);	
	small_chunk2 =  VSAAlloc(small_vsa, 5);	

	VSAFree(small_chunk1);
	
	if(16 != VSALargestChunkAvailable(small_vsa))
	{	
		printf("Somthing is wrong in Largest Chunk after freeing smallest alloc, line:  %d\n",VSALargestChunkAvailable(small_vsa));
	}
/* allocating size that has just enough - without making a new header*/
	VSAFree(small_chunk1);
	small_chunk1 =  VSAAlloc(small_vsa, 16);	
	VSAFree(med_chunk);
	med_chunk =  VSAAlloc(small_vsa, 40);	
	VSAFree(big_chunk);
	
	if( 64 != VSALargestChunkAvailable(small_vsa))
	{	
		printf("Somthing is wrong in Largest Chunk: you got  %d, instead of 64\n",VSALargestChunkAvailable(small_vsa));	
	}
	
	free((char*)small_pool - 10);
}

int main()
{
	RandTest();
	 SmokeTest();
	return 0;
}
