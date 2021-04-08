#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "stack.h"

struct stack
{
    size_t top;
    void **elements;
    size_t capacity;
};
 

stack_t *StackCreate(size_t capacity)
{
	stack_t *stackush = (struct stack*)malloc(sizeof(struct stack));
	
	if (NULL == stackush)
	{
		return NULL;
	}
	stackush->top = 0;
	stackush->capacity = capacity;	
	stackush->elements = (void **)malloc(capacity * sizeof(void *));
	
	if (NULL == stackush->elements)
	{
		free(stackush);		
		return NULL;
	}

	return stackush;
}

void StackDestroy(stack_t *stack)
{
	assert(stack);
	
	free(stack->elements);
	free(stack);

	return;
}
size_t StackGetCapacity(const stack_t *stack)
{
	assert(stack);
	
	return stack->capacity;
}

int StackIsEmpty(const stack_t *stack)
{
	assert(stack);
	
	return (0 == stack->top);
}
size_t StackSize(const stack_t *stack)
{
	assert(stack);
	
	return stack->top;
}

void StackPush(stack_t *stack, void *data)
{
	assert(stack);
	assert((stack->top) < (stack->capacity));
	
    stack->elements[stack->top] = data;
	++stack->top;

	return;
}

void StackPop(stack_t *stack)
{
	assert(stack);
	assert((stack->top) < (stack->capacity));
	
	--stack->top;
	stack->elements[stack->top] = 0;

	return;

}

void *StackPeek(const stack_t *stack)
{
	assert(stack);

	return stack->elements[(stack->top) - 1];
}

