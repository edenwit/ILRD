#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"
#define GROW_FACTOR 2

enum STATUS {
    FAIL = 0,
    SUCCESS
};

struct vector
{
	void **arr;
	size_t size;
	size_t capacity;

};

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

int VectorPushBack(vector_t *vector, void *data)
{
	assert(vector);
	assert(data);
	
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

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	void **realloc_ptr = NULL;
	
	assert(vector);
	assert(vector->arr);

	realloc_ptr = (void **)realloc(vector->arr ,new_capacity * sizeof(void*));	
	
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

void VectorPopBack(vector_t *vector)
{
	assert(vector);
	assert(vector->arr);

	VectorSetElem(vector, (vector->size - 1), NULL);
	--vector->size; 	
	
	return;
}

size_t VectorSize(const vector_t *vector)
{
	assert(vector);
	
	return vector->size;
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(vector);
	
	return vector->capacity;
}

void *VectorGetElem (const vector_t *vector, size_t index)
{
	assert(vector);
	assert(vector->arr);
	assert(index < vector->size);
	
	return vector->arr[index];
}

void VectorSetElem(vector_t *vector, size_t index, void *data)
{
	assert(vector);
	assert(vector->arr);
	assert(index < vector->size);
	
	vector->arr[index] = data;

	return;
}

int VectorShrinkToFit(vector_t *vector)
{
	void ** realloc_ptr = NULL;

	assert(vector);
	assert(vector->arr);
	
	realloc_ptr = (void **)realloc(vector->arr, vector->size * sizeof(void*));	
	
	if (NULL == realloc_ptr)
	{
		return FAIL;
	}
	
	vector->arr = realloc_ptr;
	vector->capacity = vector->size;
	
	return SUCCESS;		
}
