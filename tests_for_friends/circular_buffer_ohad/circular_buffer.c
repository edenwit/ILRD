/*  developer: Ohad Ezra
    status: In procces 
    date: 26.4.2021
    description: Implementation of circular buffer  
*/

#include <assert.h> /* assert */
#include <stdlib.h> /*malloc */
#include <string.h> /* memcpy */

#include "circular_buffer.h"

/* Approved by Shir */
#define OFFSETOF(s, m) ((size_t)&(((s *)0)->m)) 
#define STRUCT_SIZE sizeof(c_buffer_t)

struct circular_buffer
{
	size_t read_index;
	size_t current_size;
	size_t capacity;
	char arr[1];
};

/* Approved by Shir */
c_buffer_t *CBufferCreate(size_t capacity)
{
	c_buffer_t *c_buffer = (c_buffer_t *)malloc(capacity + 
							OFFSETOF(c_buffer_t , arr));
	            			 		
	if (NULL ==	c_buffer)
	{
		return NULL;
	}
	
	c_buffer->capacity = capacity;
	c_buffer->read_index = 0;
	c_buffer->current_size = 0;
	
	return c_buffer;         
}

/* Approved by Shir */
void CBufferDestroy(c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);
	
	c_buffer->capacity = -1;
	c_buffer->read_index = -1;
	c_buffer->capacity = 0;
	
	free(c_buffer);
	
	return;
}

/* Approved by Nir */
size_t CBufferSiz(const c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);
	
	return (c_buffer->capacity);
}

/* Approved by Nir */
int CBufferIsEmpty(const c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);
	
	return (c_buffer->current_size == 0); 
}

/* Approved by Nir */
size_t CBufferFreeSpace(const c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);
	
	return (CBufferSiz(c_buffer) - c_buffer->current_size);
}


ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count)
{
	size_t copy_count = count;
	char *copy_dest = dest;
	size_t offset = 0; 
	
	assert(NULL != dest);
	assert(NULL != c_buffer);
	
	offset = CBufferSiz(c_buffer) - c_buffer->read_index;
	
	if (count > c_buffer->current_size)
	{
		count = c_buffer->current_size;
		copy_count = count;	
	}
	
	/* if count > offset there is no space to read all the elements at one time */
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


/* Approved by Nir */
ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count)
{
	size_t copy_count = count;
	size_t write = 0;
	const char *copy_src = src;				
	size_t offset = 0;
	
	assert(NULL != src);
	assert(NULL != c_buffer);
	
	write = (c_buffer->read_index + c_buffer->current_size) 
	         % CBufferSiz(c_buffer);
			 
	offset = CBufferSiz(c_buffer) - write;
	
	if (count > CBufferFreeSpace(c_buffer)) 
	{
		count = CBufferFreeSpace(c_buffer);
		copy_count = count;	
	}
	
	/* if count > offset there is no space to write all the elements at one time */
	if (offset < count) 
	{
		memcpy(c_buffer->arr + write, copy_src, offset);
					  
		write = 0;
		c_buffer->current_size += offset;
		copy_src += offset;
		count -= offset;						      					   	
	}
	
	memcpy(c_buffer->arr + write, copy_src, count);
	c_buffer->current_size += count;
								      
	return copy_count;
}




