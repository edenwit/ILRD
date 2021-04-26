#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
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
	c_buffer_t *buffer = (c_buffer_t*)malloc(capacity + offsetof(struct circular_buffer,arr));
	if (buffer == NULL)
	{
		return NULL;
	} 

	buffer->read_index = 0;
	buffer->current_size = 0;
	buffer->capacity = capacity;
	
	return buffer;
	
	
}

/*Approved by Eden*/
void CBufferDestroy(c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	c_buffer->read_index = -1;
	c_buffer->current_size=-1;
	c_buffer->capacity=0;
	
	
	free(c_buffer);
	
}
/*Approved by Nir*/

ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count)
{
	ssize_t bytes_to_copy = 0;
	const char *src_p = src;
	size_t write_index = 0;
	
	assert(c_buffer);
	assert(src);
	
	if (count > CBufferFreeSpace(c_buffer))
	{
		count = CBufferFreeSpace(c_buffer);
		
	}
	
	write_index = (c_buffer->read_index + c_buffer->current_size) % c_buffer->capacity;
	
	if ((write_index + count) < c_buffer->capacity)
	{
		memcpy (c_buffer->arr + write_index ,src, count);
		
	}
	
	else
	{
		bytes_to_copy = CBufferFreeSpace(c_buffer) - c_buffer->read_index;

		memcpy(c_buffer->arr + write_index ,src, bytes_to_copy);
	
		src_p = src_p + bytes_to_copy;
		
		bytes_to_copy = count - bytes_to_copy;

		memcpy(c_buffer->arr ,src_p, bytes_to_copy);	
	}
	
	c_buffer->current_size = (c_buffer->current_size + count);
	
	return count;
}


/*Approved by Nir*/
ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count)
{
	ssize_t bytes_to_read = 0;
	char *dest_p = dest;
	
	
	assert(c_buffer);
	assert(dest);
	
	if (count > c_buffer->current_size)
	{
		count = c_buffer->current_size;
	}
	
	if (c_buffer->read_index + count < c_buffer->capacity)
	{
		memcpy(dest ,c_buffer->arr + c_buffer->read_index, count);
	}
	
	else
	{
		bytes_to_read = c_buffer->capacity - c_buffer->read_index;
		
		memcpy(dest ,c_buffer->arr + c_buffer->read_index, bytes_to_read);
		
		dest_p = dest_p + bytes_to_read;
		
		bytes_to_read = count - bytes_to_read;

		memcpy(dest_p ,c_buffer->arr, bytes_to_read);
	}
	
	c_buffer->read_index = (c_buffer->read_index + count) % c_buffer->capacity;
	
	c_buffer->current_size = c_buffer->current_size - count;
		
	return count;
	
}



int CBufferIsEmpty(const c_buffer_t *c_buffer)
{
	assert(c_buffer);
	
	if (c_buffer->current_size == 0)
	{
	
		return 1;
	}	
	return 0;
}

size_t CBufferSiz(const c_buffer_t *c_buffer)
{

	assert(c_buffer);
	
	return c_buffer->capacity;
}


size_t CBufferFreeSpace(const c_buffer_t *c_buffer)
{
	
	return (c_buffer->capacity - c_buffer->current_size) ;

}



