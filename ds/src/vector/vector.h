#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h> /* size_t */

typedef struct vector_t;
 
void 	  VectorPushBack	(vector_t *vector, void *data);
void 	  VectorPopBack		(vector_t *vector);
size_t 	  VectorSize		(vector_t *vector);
size_t 	  VectorCapacity	(vector_t *vector);
void *	  VectorGetElem		(vector_t *vector, size_t index);
void	  VectorSetElem		(vector_t *vector, size_t index, void *data);
vector_t *VectorCreate		(size_t capacity);
void 	  VectorDestroy		(vector_t *vector);
vector_t *VectorReserve		(vector_t *vector, size_t new_capacity);
int	      VectorShrinkToFit	(vector_t *vector);

#endif /*  __VECTOR_H__ */
