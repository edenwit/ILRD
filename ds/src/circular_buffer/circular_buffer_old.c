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

ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count)
{
	size_t steps_from_end = CBufferSiz(c_buffer) - c_buffer->read_index;
	size_t write_index = (c_buffer->read_index + c_buffer->current_size) % CBufferSiz(c_buffer);			
	/*size_t count_cpy = count;*/
	
	assert(c_buffer);
	assert(src);	
/*
	if (0 == CBufferFreeSpace(c_buffer))
	{
		return 0;
	}
*/
	count = MIN(count , CBufferFreeSpace(c_buffer));
	/*count_cpy = count;*/
	
	if (c_buffer->read_index > write_index)
	{
		if (count > steps_from_end)
		{
			memcpy(c_buffer + ARROFFSET + write_index, src, steps_from_end);
			count -= steps_from_end;
			c_buffer->current_size += steps_from_end;
			src = (char *)src + steps_from_end;
		}
		memcpy(c_buffer + ARROFFSET + write_index, src, count);
		c_buffer->current_size += count;
	}
	else
	{
		memcpy(c_buffer + write_index + ARROFFSET, src, count);
		c_buffer->current_size += count;	
	}

	return (ssize_t)count_cpy;	
}

ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count)
{
	size_t steps_from_end = (CBufferSiz(c_buffer) - c_buffer->read_index);
	size_t toggle = 0;

	assert(c_buffer);
	assert(dest);	
	
	count = MIN(count , CBufferFreeSpace(c_buffer));

	if (count > steps_from_end)
	{
		memcpy((char *)dest, (char *)(c_buffer + ARROFFSET + c_buffer->read_index), steps_from_end);

		count-= steps_from_end;
		toggle = 1;
	}
	
	memcpy(dest + (steps_from_end * toggle), c_buffer + ARROFFSET + c_buffer->read_index, count);
	
	c_buffer->read_index = (((c_buffer->read_index + steps_from_end) * toggle) + count) % CBufferSiz(c_buffer);
	c_buffer->current_size = c_buffer->current_size - count - (steps_from_end * toggle);
	
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
	
	return (c_buffer->capacity - c_buffer->current_size);
}
