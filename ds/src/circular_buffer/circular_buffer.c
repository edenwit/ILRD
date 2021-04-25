#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc */
#include <unistd.h>


#include "../../include/circular_buffer.h"

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

ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count)
{
	size_t steps_from_end = CBufferSiz(c_buffer) - c_buffer->read_index;
	ssize_t write_index = (c_buffer->read_index + c_buffer->current_size) % CBufferSiz(c_buffer);			
	size_t count_cpy = count;
	
	assert(c_buffer);
	assert(src);	
	printf("counter :%ld, size: %ld, capacity: %ld.\n", count_cpy, c_buffer->current_size, c_buffer->capacity);
	if (0 == CBufferFreeSpace(c_buffer))
	{
		return 0;
	}
	if (count > CBufferFreeSpace(c_buffer))
	{
		count = CBufferFreeSpace(c_buffer);
		count_cpy = count;
	}
	if (c_buffer->read_index > (c_buffer->read_index + c_buffer->current_size) % c_buffer->capacity)
	{
		if (count > steps_from_end)
		{
			memcpy(c_buffer + write_index, src, steps_from_end);
			count -= steps_from_end;
			c_buffer->current_size += steps_from_end;
			src = (char *)src + steps_from_end;
		}
		memcpy(c_buffer + write_index, src, count);
		c_buffer->current_size += count;
	}
	else
	{
			memcpy(c_buffer + write_index, src, count);
			c_buffer->current_size += count;	
	}
	printf("counter :%ld, size: %ld, capacity: %ld.\n", count_cpy, c_buffer->current_size, c_buffer->capacity);
	return count_cpy;	
}

ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count)
{
	size_t steps_from_end = CBufferSiz(c_buffer) - c_buffer->read_index;

	assert(c_buffer);
	assert(dest);	
	
	if (CBufferIsEmpty(c_buffer))
	{
		return 0;
	}
	
	if (count > c_buffer->current_size)
	{
		count = c_buffer->current_size;
	}
	
	if (count > steps_from_end)
	{
		memcpy(dest, (char *)(c_buffer + c_buffer->read_index), steps_from_end);
		c_buffer->read_index = (c_buffer->read_index + steps_from_end) % c_buffer->capacity;
		memcpy((char *)dest + steps_from_end, (char *)c_buffer, (count - steps_from_end));
	}
	else
	{
		memcpy(dest, c_buffer + c_buffer->read_index, steps_from_end);
		c_buffer->read_index += steps_from_end;
	}
	
	c_buffer->current_size -= count;
	
	return count;
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
	
	return c_buffer->capacity - c_buffer->current_size;
}
