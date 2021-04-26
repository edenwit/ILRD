#include <stdlib.h> /*  malloc  */
#include <stddef.h> /*  size_t  */
#include <assert.h> /*  assert  */
#include <string.h> /*  memcpy  */
#include <unistd.h> /* ssize_t */ 


#include "circular_buffer.h" 

#define OFFSETOF(type, member) ((size_t )&(((type *)0)->member))

struct circular_buffer
{
	size_t read_index;
	size_t current_size;
	size_t capacity;
	char arr[1];
};

c_buffer_t *CBufferCreate(size_t capacity)
{
	c_buffer_t *c_buffer = NULL;
	
	assert(capacity != 0);
	
	c_buffer = (c_buffer_t *)malloc(OFFSETOF(struct circular_buffer, arr) + capacity);
	
	if(NULL == c_buffer)
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
	assert(NULL != c_buffer);	
	
	c_buffer->read_index = 0xffffffffffffffff;
	c_buffer->current_size = 0xffffffffffffffff;
	c_buffer->capacity = 0;
	
	free(c_buffer);
	return;
}

int CBufferIsEmpty(const c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);	
	
	return (!c_buffer->current_size);
}

size_t CBufferSiz(const c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);	
	
	return (c_buffer->capacity);
}

size_t CBufferFreeSpace(const c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);	
	
	return(CBufferSiz(c_buffer) - c_buffer->current_size);
}

ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count)
{
	char *dest_cpy = (char *)dest;
	size_t cpy_count = count;
	size_t offset = 0;
	
	assert(NULL != dest);	
	assert(NULL != c_buffer);	
	
	offset = CBufferSiz(c_buffer) - c_buffer->read_index;
	
	if(CBufferIsEmpty(c_buffer))
	{
		return (0); 
	}
	
	/* adjust count to the free space */
	if(c_buffer->current_size < count)
	{
		count = c_buffer->current_size;
		cpy_count = count;
	}
	
	/* split the copied area to two chunks */
	if(offset < count)
	{
		memcpy(dest_cpy, c_buffer->arr + c_buffer->read_index, offset);
		dest_cpy += offset;
		c_buffer->read_index = 0;
		count -= offset;		
	}
	
	memcpy(dest_cpy, c_buffer->arr + c_buffer->read_index, count);
	c_buffer->current_size -= cpy_count;
	c_buffer->read_index = (c_buffer->read_index + count) % CBufferSiz(c_buffer);
	
	return cpy_count;
}

ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count)
{
	size_t write_index = 0;
	size_t cpy_count = count;
	char *src_cpy = (char *)src;
	size_t offset = 0;
	
	assert(NULL != src);	
	assert(NULL != c_buffer);	
	
	write_index = (c_buffer->read_index + c_buffer->current_size) % CBufferSiz(c_buffer);
	offset = CBufferSiz(c_buffer) - write_index;
	
	if(0 == CBufferFreeSpace(c_buffer))
	{
		return (0);
	}
	
	/* adjust count to the free space */
	if(count > CBufferFreeSpace(c_buffer))
	{
		count = CBufferFreeSpace(c_buffer);
		cpy_count = count;
	}
	
	/* split the copied area to two chunks */
	if(count > offset)
	{
		memcpy(c_buffer->arr + write_index, src_cpy, offset);
		src_cpy += offset;
		count -= offset;
		write_index = 0;
	}
	
	memcpy(c_buffer->arr + write_index, src_cpy, count);
	c_buffer->current_size += cpy_count;
	
	return cpy_count;
}
