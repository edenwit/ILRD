#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc */
#include <unistd.h>
#include "../../include/circular_buffer.h"

#define ARROFFSET OFFSETOF(struct circular_buffer, arr)
#define OFFSETOF(s, f) ((size_t)&(((s *)0)->f))
#define MIN(a,b) (((a)<(b))?(a):(b))

struct circular_buffer
{
	size_t read_index;
	size_t current_size;
	size_t capacity;
	char arr[1];
};

/* Approved by Roman */
c_buffer_t *CBufferCreate(size_t capacity)
{
	c_buffer_t *c_buffer = (c_buffer_t *)malloc(OFFSETOF(c_buffer_t, arr) + capacity);
	
	if (NULL == c_buffer)
	{
		return NULL;
	}
	
	c_buffer->read_index = 0;
	c_buffer->current_size = 0;
	c_buffer->capacity = capacity;

	return c_buffer;

}

/* Approved by Roman */
void CBufferDestroy(c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	c_buffer->read_index = 0xFFFFFFFFFFFFFFFF;
	c_buffer->current_size = 0xFFFFFFFFFFFFFFFF;
	c_buffer->capacity = 0xFFFFFFFFFFFFFFFF;	
	
	free(c_buffer);
	
	return;
}

/* Approved by Roman */
ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count)
{
	size_t steps_from_end = 0; 
	size_t copy_count = count;
	
	assert(dest);
	assert(c_buffer);
	
	steps_from_end = CBufferSiz(c_buffer) - c_buffer->read_index;
	
	if (count > c_buffer->current_size)
	{
		count = c_buffer->current_size;
		copy_count = count;	
	}
	
	if (steps_from_end < count)
	{
		memcpy(dest, c_buffer->arr + c_buffer->read_index , steps_from_end);
					  
		c_buffer->current_size -= steps_from_end;
		c_buffer->read_index = 0;
		count -= steps_from_end;
		dest = (char *)dest + steps_from_end;							      					   	
	}
	
	memcpy(dest, c_buffer->arr + c_buffer->read_index, count);
	c_buffer->read_index = (c_buffer->read_index + count) % CBufferSiz(c_buffer);
	c_buffer->current_size -= count;
								      
	return copy_count;
}

/* Approved by Roman */
ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count)
{
	size_t original_count = count;
	size_t write_index = 0;
	size_t steps_from_end = 0;
	
	assert(src);
	assert(c_buffer);
	
	write_index = (c_buffer->read_index + c_buffer->current_size) 
	         % CBufferSiz(c_buffer);
			 
	steps_from_end = CBufferSiz(c_buffer) - write_index;
	
	if (count > CBufferFreeSpace(c_buffer)) 
	{
		count = CBufferFreeSpace(c_buffer);
		original_count = count;	
	}
	
	if (steps_from_end < count) 
	{
		memcpy(c_buffer->arr + write_index, src, steps_from_end);
					  
		write_index = 0;
		c_buffer->current_size += steps_from_end;
		src = (char *) + steps_from_end;
		count -= steps_from_end;						      					   	
	}
	
	memcpy(c_buffer->arr + write_index, src, count);
	c_buffer->current_size += count;
								      
	return original_count;
}

/* Approved by Roman */
int CBufferIsEmpty(const c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	return (0 == c_buffer->current_size);
}

/* Approved by Roman */
size_t CBufferSiz(const c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	return (c_buffer->capacity);
}

/* Approved by Roman */
size_t CBufferFreeSpace(const c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	return (c_buffer->capacity - c_buffer->current_size);
}
