#include <stdlib.h> /* malloc free */
#include <assert.h> /*assert */
#include "../../include/stack.h"

struct stack
{
    size_t top;
    void **elements;
    size_t capacity;
};

stack_t *StackCreate(size_t capacity)
{
	stack_t *new_stack = NULL;
	void *memmory = malloc(sizeof(stack_t) + (capacity * sizeof(void *)));

	if(NULL == memmory)
	{
		return NULL;
	}

	new_stack = (stack_t *)memmory;
	new_stack->top = 0;
	new_stack->elements = (void **)(new_stack + 1);
	new_stack->capacity = capacity;

	return new_stack;
}

void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);

	free(stack);

	return;
}

size_t StackGetCapacity(const stack_t *stack)
{
	assert(NULL != stack);

	return stack->capacity;
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);

	return !(stack->top);
}

size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);

	return stack->top;
}

void StackPush(stack_t *stack, void *data)
{
	assert(NULL != stack);
	assert(NULL != data);
	assert((stack->top) < (stack->capacity));

	stack->elements[stack->top] = data;
	++(stack->top);

	return;
}

void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	assert(0 != (stack->top));

	--(stack->top);

	return;
}

void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	assert(0 != (stack -> top));

	return stack->elements[stack->top - 1];
}