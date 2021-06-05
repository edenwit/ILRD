#include <stdio.h>

#include "stack.h"

#define CAPACITY 100

int main()
{
	stack_t *stack_test = StackCreate(CAPACITY);
	size_t capacity_check = 0;
	int is_empty = 0;
	size_t size_check = 0;
	void *peeked = NULL;
	
	if (NULL != stack_test)
	{
		printf("Stack created successfully! Capacity: %d.\n",CAPACITY);
	}

	StackDestroy(stack_test);

	if (NULL == stack_test)
	{
		printf("Stack destroyed successfully!\n");
	}
	
	stack_test = StackCreate(CAPACITY);

	if (NULL != stack_test)
	{
		printf("Stack created successfully! Capacity: %d.\n",CAPACITY);
	}	
	
	capacity_check = StackGetCapacity(stack_test);
	
	if (0 != capacity_check)
	{
		printf("Stack Capacity: %ld.\n",capacity_check);
	}	
	
	is_empty = StackIsEmpty(stack_test);	
	
	if (is_empty)
	{
		printf("Stack is empty.\n");
	}
	else
	{
		printf("Stack is NOT empty.\n");
	}
	
	size_check = StackSize(stack_test);	
	printf("Stack size: %ld.\n", size_check);

	StackPush(stack_test, "hi im in the stack");
	StackPush(stack_test, "me too!");
	StackPush(stack_test, "me three!");
	StackPush(stack_test, "1");
	StackPush(stack_test, "103546532");
	
	size_check = StackSize(stack_test);	
	printf("Stack size: %ld.\n", size_check);	
	
	is_empty = StackIsEmpty(stack_test);	
	
	if (is_empty)
	{
		printf("Stack is empty.\n");
	}
	else
	{
		printf("Stack is NOT empty.\n");
	}
	
	StackPop(stack_test);
	StackPop(stack_test);
	StackPop(stack_test);

	peeked = StackPeek(stack_test);
	
	printf("Peeked: %p\n", (void *)peeked);
	
	size_check = StackSize(stack_test);	
	printf("Stack size: %ld.\n", size_check);	
	
	is_empty = StackIsEmpty(stack_test);	
	
	if (is_empty)
	{
		printf("Stack is empty.\n");
	}
	else
	{
		printf("Stack is NOT empty.\n");
	}	
	
	StackDestroy(stack_test);

	return 0;
}


stack_t *StackCreate(size_t capacity);
void StackDestroy(stack_t *stack);
size_t StackGetCapacity(const stack_t *stack);
int StackIsEmpty(const stack_t *stack);
size_t StackSize(const stack_t *stack);
void StackPush(stack_t *stack, void *data);
void StackPop(stack_t *stack);
void *StackPeek(const stack_t *stack);
