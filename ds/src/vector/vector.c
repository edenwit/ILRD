
#include <stddef.h> /* size_t */

#include "vector.h"

typedef struct vector_t;

typedef struct
{
	void **arr;
	size_t capacity;
	size_t size;
} vector_t; 
 
void 	  VectorPushBack	(vector_t *vector, void *data)
{
	assert(vector);
	assert((vector->arr) < (vector->capacity));
	
    vector->arr[vector->size] = data;
	++vector->size;

	return;
}

void 	  VectorPopBack		(vector_t *vector)
{
	assert(vector);
	assert((vector->size) < (vector->capacity));
	
	--vector->size;
	vector->arr[vector->size] = 0;

	return;

}

size_t 	  VectorSize		(vector_t *vector)
{
	return vector->size;
}

size_t 	  VectorCapacity	(vector_t *vector)
{
	return vector->capacity;
}

void *	  VectorGetElem		(vector_t *vector, size_t index)
{
	return vector->arr[index - 1];
}

void	  VectorSetElem		(vector_t *vector, size_t index, void *data)
{
	vector->arr[index - 1] = data;

	return;
}

vector_t *VectorCreate		(size_t capacity)
{
	vector_t *vector_case = (struct vector_t*)malloc(sizeof(struct vector_t));
	
	if (NULL == vector_case)
	{
		return NULL;
	}
	vector_case->size = 0;
	vector_case->capacity = capacity;	
	vector_case->arr = (void **)malloc(capacity * sizeof(void *));
	
	if (NULL == vector_case->arr)
	{
		free(vector_case);		
		return NULL;
	}

	return vector_case;
}

void 	  VectorDestroy		(vector_t *vector)
{
	assert(vector);
	
	free(vector_case->arr);
	free(vector_case);

	return;
}

vector_t *VectorReserve		(vector_t *vector, size_t new_capacity)
{
	assert(vector);
	
	vector->arr = (void **)realloc(new_capacity * sizeof(void *));
	
	if (NULL == vector->arr)
	{
		return NULL;
	}

	if (new_capacity < vector->capacity)
	{
		vector->size = new_capacity;
	}
	vector->capacity = new_capacity;
	
	return vector->arr;
}

int	      VectorShrinkToFit	(vector_t *vector)
{
	assert(vector);
	
	vector->arr = (void **)realloc(vector->size * sizeof(void *));
	
	if (NULL == vector->arr)
	{
		return NULL;
	}

	if (new_capacity < vector->capacity)
	{
		vector->size = new_capacity;
	}
	vector->capacity = new_capacity;
	
	return vector->arr;
}
