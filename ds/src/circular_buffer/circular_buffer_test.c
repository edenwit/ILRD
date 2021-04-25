#include <stdio.h> /* printf */
#include <sys/types.h>
#include <string.h> /* strlen */
#include "../../include/circular_buffer.h"

#define CAPACITY (size_t)30

static void CBTest();

struct offset_of_test_struct
{
	size_t read_index;
	size_t current_size;
	size_t capacity;
	char arr[1];
};




int main()
{
	CBTest();

	return 0;
}

static void CBTest()
{
	c_buffer_t *circular_buffer = CBufferCreate(CAPACITY);
	ssize_t success_size = 0;
	char str[] = "shelly very noisy";
	size_t len = strlen(str) + 1;
	
	if (OFFSETOF(struct offset_of_test_struct, arr) != offsetof(struct offset_of_test_struct, arr))
	{
		printf("offset of circular_buffer failed! actual: %ld, expected: %ld\n", OFFSETOF(struct offset_of_test_struct, arr), offsetof(struct offset_of_test_struct, arr));
	}
	
	if (CAPACITY != CBufferSiz(circular_buffer))
	{
		printf("Creation failed. capacity supposed to be: %ld, actual: %ld.\n", CAPACITY, CBufferSiz(circular_buffer));
	}
	
	if (CAPACITY != CBufferSiz(circular_buffer))
	{
		printf("CBufferSiz supposed to be: %ld, actual: %ld.\n", CAPACITY, CBufferSiz(circular_buffer));
	}
	if (CAPACITY != CBufferFreeSpace(circular_buffer))
	{
		printf("CBufferFreeSpace supposed to be: %ld, actual: %ld.\n", CAPACITY, CBufferFreeSpace(circular_buffer));
	}	
	
	success_size = CBufferWrite(circular_buffer, (const void *)&str, len);
	
	if (success_size != (long)(len))
	{
		printf("CBufferWrite supposed to be: %d, actual: %l.\n", success_size, len);		
	}
			
	if (CAPACITY - success_size != CBufferFreeSpace(circular_buffer))
	{
		printf("CBufferFreeSpace supposed to be: %ld, actual: %ld.\n", CAPACITY, CBufferFreeSpace(circular_buffer));
	}		
	
	
	CBufferDestroy(circular_buffer);
	
	return;	
}
