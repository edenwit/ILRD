#include <stdio.h> /* printf */
#include <sys/types.h>
#include <string.h> /* strlen */
#include "../../include/circular_buffer.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define CAPACITY (size_t)30
#define MIN(a,b) (((a)<(b))?(a):(b))
#define OFFSETOF(s, f) ((size_t)&(((s *)0)->f))

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
	size_t success_size = 0;
	size_t size_before_action = 0;	
	char str[] = "shelly very noisy";
	char str2[] = "but is nice";	
	char str3[CAPACITY] = {"the sentance starts like this"};	
	char str4[CAPACITY] = {"|                           |"};	
	
	/* test offsetof */
	if (OFFSETOF(struct offset_of_test_struct, arr) != offsetof(struct offset_of_test_struct, arr))
	{
		printf("offset of circular_buffer failed! actual: %ld, expected: %ld\n", OFFSETOF(struct offset_of_test_struct, arr), offsetof(struct offset_of_test_struct, arr));
	}
	/* test IsEmpty */	
	if (!CBufferIsEmpty(circular_buffer))
	{
		printf("Supposed to be empty.\n");
	}
	/* test CBufferRead from empty buffer */	
	success_size = CBufferRead(circular_buffer, (void *)&str3, strlen(str) + 1);
	if (success_size != 0)
	{
		printf("CBufferRead supposed to be: %d, actual: %ld.\n", 0, success_size);		
	}
	/* test CBufferSiz */	
	if (CAPACITY != CBufferSiz(circular_buffer))
	{
		printf("CBufferSiz supposed to be: %ld, actual: %ld.\n", CAPACITY, CBufferSiz(circular_buffer));
	}
	/* test CBufferFreeSpace */		
	if (CAPACITY != CBufferFreeSpace(circular_buffer))
	{
		printf("CBufferFreeSpace supposed to be: %ld, actual: %ld.\n", CAPACITY, CBufferFreeSpace(circular_buffer));
	}	
	/* test CBufferWrite */			
	success_size = CBufferWrite(circular_buffer, (const void *)&str, strlen(str) + 1);
	
	if (success_size != (strlen(str) + 1))
	{
		printf("%d CBufferWrite supposed to be: %ld, actual: %ld.\n", __LINE__, success_size, strlen(str) + 1);		
	}
	/* test CBufferFreeSpace */					
	if (CAPACITY - success_size != CBufferFreeSpace(circular_buffer))
	{
		printf("CBufferFreeSpace supposed to be: %ld, actual: %ld.\n", CAPACITY - success_size, CBufferFreeSpace(circular_buffer));
	}		
	/* test CBufferWrite */			
	success_size += CBufferWrite(circular_buffer, (const void *)&str2, strlen(str2) + 1);
	
	if (success_size != MIN(strlen(str2) + 1 + (strlen(str)) + 1, CAPACITY))
	{
		printf("%d CBufferWrite supposed to be: %ld, actual: %ld.\n", __LINE__, success_size,  strlen(str2) + (strlen(str)));		
	}
	/* test CBufferFreeSpace */					
	if (CAPACITY - success_size != CBufferFreeSpace(circular_buffer))
	{
		printf("CBufferFreeSpace supposed to be: %ld, actual: %ld.\n", CAPACITY - success_size, CBufferFreeSpace(circular_buffer));
	}	

	size_before_action = CBufferSiz(circular_buffer) - CBufferFreeSpace(circular_buffer);

	success_size = CBufferRead(circular_buffer, (void *)&str3, strlen(str) + 1);
	
	if (success_size != strlen(str) + 1)
	{
		printf("%d CBufferRead supposed to be: %ld, actual: %ld.\n", __LINE__, strlen(str) + 1, success_size);		
	}	
	
	if (0 != strncmp(str, str3, strlen(str)))
	{
		printf("str3 after read supposed to be: %s, actual: %s.\n", str, str3);		
	}	

	if (strlen(str) + 1 != CBufferFreeSpace(circular_buffer))
	{
		printf("CBufferFreeSpace supposed to be: %ld, actual: %ld.\n", strlen(str) + 1, CBufferFreeSpace(circular_buffer));
	}	

	size_before_action = CBufferSiz(circular_buffer) - CBufferFreeSpace(circular_buffer);

	success_size = CBufferRead(circular_buffer, (void *)&str4, strlen(str2) + 1);
	
	if (success_size != size_before_action)
	{
		printf("CBufferRead supposed to be: %ld, actual: %ld.\n", size_before_action, success_size);		
	}	
	
	if (0 != strncmp(str2, str4, strlen(str2) + 1))
	{
		printf("str4 after read supposed to be: '%s', actual: '%s'.\n", str2, str4);		
	}	

	if (strlen(str) + 1 + strlen(str2) + 1!= CBufferFreeSpace(circular_buffer))
	{
		printf("CBufferFreeSpace supposed to be: %ld, actual: %ld.\n", strlen(str) + 1 + strlen(str2) + 1, CBufferFreeSpace(circular_buffer));
	}		
	
	CBufferDestroy(circular_buffer);
	
	return;	
}
