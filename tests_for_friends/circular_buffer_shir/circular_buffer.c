#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */

#include "circular_buffer.h"

#define OFFSETOF(type, member) ((size_t )&(((type *)0)->member))

 struct circular_buffer
{
	size_t read_index;
	size_t current_size;
	size_t capacity;
	char arr[1];
};




/* Approved by Eden S. */
c_buffer_t *CBufferCreate(size_t capacity)
{
	c_buffer_t *buff_arr = (c_buffer_t *)malloc(capacity +
											(OFFSETOF(c_buffer_t, arr)));
	
	if (NULL == buff_arr)
	{
		return NULL;
	}
	
	buff_arr->read_index = 0;
	buff_arr->current_size = 0;
	buff_arr->capacity = capacity;
	
	return buff_arr;
}

/* Approved by Eden S. */
void CBufferDestroy(c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	c_buffer->read_index = -1;
	c_buffer->current_size = -1;
	c_buffer->capacity = -1;
	
	free(c_buffer);	
}

/* Approved by Eden S. */
int CBufferIsEmpty(const c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	return (0 == c_buffer->current_size);
}

/* Approved by Eden S. */
size_t CBufferSiz(const c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	return c_buffer->capacity;
}

/* Approved by Eden S. */
size_t CBufferFreeSpace(const c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	return c_buffer->capacity - c_buffer->current_size;
}


ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count)
{
	size_t write_index =  (c_buffer->read_index + c_buffer->current_size) % c_buffer->capacity;
	size_t offset = c_buffer->capacity - write_index;
	const char *copy_src = src;
	size_t cpy_count = count;
	
	assert(c_buffer);
	assert(src);
	
	if (count > CBufferFreeSpace(c_buffer))
	{
		count = CBufferFreeSpace(c_buffer);
		cpy_count = count;
	}	
	
	if (count > offset)
	{
		memcpy(c_buffer->arr + write_index, src, offset);
		count -= offset;
		write_index = 0;
		copy_src += offset;
		c_buffer->current_size += offset; 
	}
	
	memcpy(c_buffer->arr + write_index, copy_src, count);
	c_buffer->current_size += count;
	
	return cpy_count;
}




ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count)
{
	size_t copy_count = 0;
	size_t offset = c_buffer->capacity - c_buffer->read_index % c_buffer->capacity;
	char *copy_dest = (char *)dest;
	
	assert(c_buffer);
	assert(dest);
	
	if (0 == c_buffer->current_size)
	{
		return 0;
	}
	
	if (count > c_buffer->current_size)
	{
		count = c_buffer->current_size;
	}
	
	copy_count = count;
	
	if (offset < count)
	{
		dest = memcpy(dest, c_buffer->arr + c_buffer->read_index, offset);
		count -= offset;
		c_buffer->current_size -= offset;
		copy_dest += offset;
		c_buffer->read_index = 0;
	}
	
	memcpy(copy_dest, c_buffer->arr + c_buffer->read_index, count);
	c_buffer->current_size -= count;
	c_buffer->read_index += count;
	c_buffer->read_index %= c_buffer->capacity;
	
	return copy_count;
}



