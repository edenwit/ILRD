#include<assert.h> /* assert */
#include "recursion.h"

struct node
{
    void *data;
    struct node *next;
};

static void StackInsertToSortedStack(stack_t *stack, int *number);

int RecursiveFibonacci(int element_index)
{
    assert (0 <= element_index);

    if (0 == element_index || 1 == element_index)
    {
        return element_index;
    }

    return RecursiveFibonacci(element_index - 2) + RecursiveFibonacci(element_index - 1);
}

int IterativeFibonacci(int element_index)
{
    size_t i = 0;
    int prev = 0;
    int curr = 1;

    assert(0 <= element_index);

    if (0 == element_index || 1 == element_index)
    {
        return element_index;
    }

    for (i = 1; (int)i < element_index; ++i)
    {
        curr = prev + curr;
        prev = curr - prev;
    }

    return curr;
}

node_t *FlipList(node_t *node)
{
    node_t *head = NULL;
    if (NULL == node || NULL == node->next)
    {
        return node;
    }

    head = FlipList(node->next);
    node->next->next = node;
    node->next = NULL;

    return head;
}

void StackSort(stack_t *stack)
{
    int *stack_top = NULL;

    assert(NULL != stack);

    if (StackIsEmpty(stack))
    {
        return;
    }

    stack_top = (int *)StackPeek(stack);
    StackPop(stack);
    StackSort(stack);
    StackInsertToSortedStack(stack, stack_top);

    return;
}

static void StackInsertToSortedStack(stack_t *stack, int *number)
{
    int *stack_top = NULL;

    assert(NULL != stack);
    assert(NULL != number);

    if (StackIsEmpty(stack) || (*(int *)StackPeek(stack) <= *number))
    {
        StackPush(stack, (void *)number);
        return;
    }

    stack_top = (int *)StackPeek(stack);
    StackPop(stack);

    StackInsertToSortedStack(stack, number);

    StackPush(stack, stack_top);
    return;
}


size_t StrLen(const char *s)
{
    assert(NULL != s);

    if ('\0' == *s)
    {
        return 0;
    }

    return 1 + StrLen(++s);
}

int StrCmp(const char *s1, const char *s2)
{
    assert(NULL != s1);
    assert(NULL != s2);
    
    if (*s1 != *s2 || (*s1 == '\0' && *s2 == '\0'))
    {
        return *s1 - *s2;
    }

    return StrCmp(++s1, ++s2);
}

char *StrCpy(char *dest, const char *src)
{
    *dest = *src;

    assert(NULL != dest);
    assert(NULL != src);

    if ('\0' == *src)
    {
        return dest;
    }

    return StrCpy(dest + 1, src + 1) - 1;
}

char *StrCat(char *dest, const char *src)
{
    assert(NULL != dest);
    assert(NULL != src);

    if ('\0' == *src)
    {
        return dest;
    }

    if ('\0' == *dest)
    {
        *dest = *src;
        *(dest + 1) = '\0';
        return StrCat(dest + 1, src + 1) - 1;
    }

    return StrCat(dest + 1, src) - 1;
}


char *StrStr(const char *haystack, const char *needle)
{
    assert(NULL != haystack);
    assert(NULL != needle);

   if ('\0' == *needle)
   {
       return (char *)haystack;
   }

   if ('\0' == *haystack)
   {
       return NULL;
   }

   if (*haystack == *needle)
   {
       if ((haystack + 1) == StrStr(haystack + 1, needle + 1))
       {
           return (char *)haystack;
       }
   }

   return StrStr(haystack + 1, needle);
}

