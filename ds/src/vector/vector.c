#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "vector.h"

#define GROW_FACTOR 2

enum STATUS {
    FAIL = 0,
    SUCCESS = 1
};

struct vector
{
	void **arr;
	size_t size;
	size_t capacity;
};

/* approved by shelly */

vector_t *VectorCreate(size_t capacity)
{
	vector_t *vector = (vector_t *)malloc(sizeof(vector_t));

	if (NULL == vector)
	{    
		return NULL;
	}

	vector->capacity = capacity; 	
	vector->arr = (void **)malloc(capacity*sizeof(void*));	
	
	if (NULL == vector->arr)
	{   
		free(vector);
		return NULL;
	}

	vector->size = 0; 

	return vector;

}

/* approved by shelly */

void VectorDestroy(vector_t *vector)
{
	assert(vector);
	assert(vector->arr);
	
	free(vector->arr); 
	vector->arr = NULL;
	
	vector->capacity = 0;
	vector->size = 0;
	
	free(vector);
	
	return;
}

/* approved by shelly */

int VectorPushBack(vector_t *vector, void *data)
{
	assert(vector);
	
	if (vector->size == vector->capacity)
	{
		if (FAIL == VectorReserve(vector, GROW_FACTOR * vector->capacity))
		{
			return FAIL;
		}
	}
	++vector->size;	
	VectorSetElem(vector, (vector->size - 1), data);

	return SUCCESS;	
}

/* approved by shelly */

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	void *realloc_ptr = NULL;
	
	assert(vector);
	assert(vector->arr);

	realloc_ptr = (void *)realloc(vector->arr ,new_capacity * sizeof(void*));	
	
	if (NULL == realloc_ptr)
	{
		return FAIL;
	}
	
	vector->arr = realloc_ptr;
	
	if (new_capacity < vector->size)
	{
		vector->size = new_capacity;
	}
	
	vector->capacity = new_capacity; 
  
	return SUCCESS;	
}

/* approved by shelly */

void VectorPopBack(vector_t *vector)
{
	assert(vector);
	assert(vector->arr);
	assert(0 != vector->size);
	
	VectorSetElem(vector, vector->size - 1, NULL);
	--(vector->size);
	
	if (vector->size == (vector->capacity / (GROW_FACTOR * GROW_FACTOR)))
	{
		VectorReserve(vector, vector->capacity / GROW_FACTOR);
	}

	return ;
}

/* approved by shelly */

size_t VectorSize(const vector_t *vector)
{
	assert(vector);
	
	return vector->size;
}

/* approved by shelly */

size_t VectorCapacity(const vector_t *vector)
{
	assert(vector);
	
	return vector->capacity;
}

/* approved by shelly */

void *VectorGetElem (const vector_t *vector, size_t index)
{
	assert(vector);
	assert(vector->arr);
	assert(index < vector->size);
	
	return vector->arr[index];
}

/* approved by shelly */

void VectorSetElem(vector_t *vector, size_t index, void *data)
{
	assert(vector);
	assert(vector->arr);
	assert(index < vector->size);
	
	vector->arr[index] = data;

	return;
}

/* approved by shelly */

int VectorShrinkToFit(vector_t *vector)
{
	void *realloc_ptr = NULL;

	assert(vector);
	assert(vector->arr);
	
	realloc_ptr = (void *)realloc(vector->arr, vector->size * sizeof(void*));	
	
	if (NULL == realloc_ptr)
	{
		return FAIL;
	}
	
	vector->arr = realloc_ptr;
	vector->capacity = vector->size;
	
	return SUCCESS;		
}



