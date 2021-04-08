#include <stddef.h> /* size_t */

typedef struct stack stack_t;

struct stack
{
    size_t top;
    void **elements;
    size_t capacity;
};
 

stack_t *StackCreate(size_t capacity)
{
	(void *)malloc(len * sizeof(int));
}
void StackDestroy(stack_t *stack);
size_t StackGetCapacity(const stack_t *stack);
int StackIsEmpty(const stack_t *stack);
size_t StackSize(const stack_t *stack);
void StackPush(stack_t *stack, void *data);
void StackPop(stack_t *stack);
void *StackPeek(const stack_t *stack);

