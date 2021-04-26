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
void CBufferDestroy(c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	c_buffer->read_index = 0;
	c_buffer->current_size = 0;
	c_buffer->capacity = 0;	
	
	free(c_buffer);
	
	return;
}

ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count)
{
	size_t copy_count = count;
	char *copy_dest = dest;
	size_t offset = 0; 
	
	assert(dest);
	assert(c_buffer);
	
	offset = CBufferSiz(c_buffer) - c_buffer->read_index;
	
	if (count > c_buffer->current_size)
	{
		count = c_buffer->current_size;
		copy_count = count;	
	}
	
	if (offset < count)
	{
		memcpy(copy_dest, c_buffer->arr + c_buffer->read_index , offset);
					  
		c_buffer->current_size -= offset;
		c_buffer->read_index = 0;
		count -= offset;
		copy_dest += offset;							      					   	
	}
	
	memcpy(copy_dest, c_buffer->arr + c_buffer->read_index, count);
	c_buffer->read_index = (c_buffer->read_index + count)
							%  c_buffer->capacity;
	c_buffer->current_size -= count;
								      
	return copy_count;
}


ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count)
{
	size_t copy_count = count;
	size_t write_index = (c_buffer->read_index + c_buffer->current_size) % CBufferSiz(c_buffer);
	size_t steps_from_end = 0;
	
	assert(src);
	assert(c_buffer);
	
	steps_from_end = CBufferSiz(c_buffer) - write;
	
	if (count > CBufferFreeSpace(c_buffer)) 
	{
		count = CBufferFreeSpace(c_buffer);
		copy_count = count;	
	}
	
	if (steps_from_end < count) 
	{
		memcpy(c_buffer->arr + write, src, steps_from_end);
					  
		write = 0;
		c_buffer->current_size += steps_from_end;
		src += steps_from_end;
		count -= steps_from_end;						      					   	
	}
	
	memcpy(c_buffer->arr + write, src, count);
	c_buffer->current_size += count;
								      
	return copy_count;
}


int CBufferIsEmpty(const c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	return (0 == c_buffer->current_size);
}

size_t CBufferSiz(const c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	return c_buffer->capacity;
}

size_t CBufferFreeSpace(const c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	return (c_buffer->capacity - c_buffer->current_size);
}
