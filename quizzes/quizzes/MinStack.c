#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <time.h>

#include "../../ds/src/stack/stack.h"

#define STACK_IS_FULL(X) (StackGetCapacity(X) == StackSize(X))
#define MIN2(a, b)  ((*((int *)(a))) < (*((int *)(b))) ? (a) : (b))

typedef struct min_stack
{
	stack_t *stack;
	stack_t *min_stack;

} min_stack_t;

int MinStackPush(min_stack_t *m_stack, void *data);
void MinStackPop(min_stack_t *m_stack);

min_stack_t *MinStackCreate(size_t capacity);
void MinStackDestroy(min_stack_t *m_stack);

void *GetMinVal(min_stack_t *m_stack);

int main()
{
	min_stack_t *min_stack = MinStackCreate(10);
	int arr[9] = {0};
	size_t arr_size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;

	srand (time(NULL));

	for (i = 0; i < arr_size; ++i)
	{
		arr[i] = (rand() % 100) - 50;;
		MinStackPush(min_stack, (arr + i));

		printf("#%ld: Inserting %d, ", i + 1 , arr[i]);
		printf("Min val %d\n", *((int *)GetMinVal(min_stack)));
	}

	for (i = 0; i < arr_size; ++i)
	{
		printf("#%ld: Removing %d, ", i + 1 , *((int *)StackPeek(min_stack->stack)));
		printf("Min val %d\n", *((int *)GetMinVal(min_stack)));

		MinStackPop(min_stack);
	}

	MinStackDestroy(min_stack);

	return (0);
}


int MinStackPush(min_stack_t *m_stack, void *data)
{
	void *min_val = NULL;
	
	assert(m_stack);
	
	if (STACK_IS_FULL(m_stack->stack))
	{
		return (1);
	}	
	
	if (!StackIsEmpty(m_stack->stack))
	{
		min_val = MIN2(StackPeek(m_stack->min_stack), data);
	}
	else
	{
		min_val = data;
	}
	
	StackPush(m_stack->stack, data);
	StackPush(m_stack->min_stack, min_val);
	
	return (0);
}

void MinStackPop(min_stack_t *m_stack)
{
	void *data = NULL;
	
	assert(m_stack);
	assert(!StackIsEmpty(m_stack->stack));
		
	StackPop(m_stack->stack);
	StackPop(m_stack->min_stack);
	
	return;
}

min_stack_t *MinStackCreate(size_t capacity)
{
	min_stack_t *m_stack = (min_stack_t *)malloc(sizeof(m_stack));
	
	if (NULL == m_stack)
	{
		return (NULL);
	}
	
	m_stack->stack = StackCreate(capacity);
	
	if (NULL == m_stack->stack)
	{
		free (m_stack);
		
		return (NULL);
	}

	m_stack->min_stack = StackCreate(capacity);
	
	if (NULL == m_stack->min_stack)
	{
		StackDestroy(m_stack->stack);
		m_stack->stack = NULL;
		
		free (m_stack);
		
		return (NULL);
	}
			
	return (m_stack);	
}

void MinStackDestroy(min_stack_t *m_stack)
{
	assert(m_stack);

	StackDestroy(m_stack->stack);
	StackDestroy(m_stack->min_stack);
	
	m_stack->stack = NULL;
	m_stack->min_stack= NULL;
	
	free(m_stack);
}

void *GetMinVal(min_stack_t *m_stack)
{
	assert(m_stack);
	assert(!StackIsEmpty(m_stack->min_stack));
	
	return (StackPeek(m_stack->min_stack));
}
