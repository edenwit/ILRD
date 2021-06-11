/*  Developer: Eden Wittenberg;									*
 *  Status: done;												*
 *  Date Of Creation:09.06.21;									*
 *  Date Of Approval:10.06.21;									*
 *  Approved By: ;							            		*
 *  Description: Recursion - first ex       					*/

#include <assert.h>
#include "recursion.h"

static void InsertSmallest(stack_t *stack, int *num);

struct node
{
    void *data;
    struct node *next;
};

/*--------------------------Fibonacci -------------------------*/

int RecursiveFibonacci(int element_index)
{
    assert(0 <= element_index);


    if (element_index <= 1)
    {
        return (element_index);
    }

    return (RecursiveFibonacci(element_index - 1) + RecursiveFibonacci(element_index - 2));
}

int IterativeFibonacci(int element_index)
{
    unsigned long num = 1;
    unsigned long prev_num = 0;
    int i = 0;


    assert(0 <= element_index);

    if (2 > element_index)
    {
        return (element_index);
    }

    for (i = 1; i < element_index; ++i)
    {
        num += prev_num;
        prev_num = num - prev_num;
    }

    return (num);
}

/*--------------------------Flip List -------------------------*/

node_t *FlipList(node_t *head)
{
    node_t *node = NULL;

    assert(head);

    if (!head || !head->next)
    {
        return (head);
    }

    node = FlipList(head->next);

    head->next->next = head;
    head->next = NULL;

    return (node);
}

/*--------------------------Stack Sort -------------------------*/

void StackSort(stack_t *stack)
{
    int *num = NULL;

    assert(stack);

    if (1 >= StackSize(stack))
    {
        return;
    }

    num = (int *)StackPeek(stack);

    StackPop(stack);
    StackSort(stack);

    InsertSmallest(stack, num);

    return;
}

static void InsertSmallest(stack_t *stack, int *num)
{
    int *peek = NULL;

    assert(stack);
    assert(num);

    if (StackIsEmpty(stack) || *(int *)StackPeek(stack) < *num)
    {
        StackPush(stack, (void *)num);

        return;
    }

    peek = (int *)StackPeek(stack);

    StackPop(stack);

    InsertSmallest(stack, num);

    StackPush(stack, (void *)peek);

    return;
}

/*--------------------------Strings -------------------------*/


size_t StrLen(const char *s)
{
    assert(s);

    if ('\0' == *s)
    {
        return (0);
    }

    return (StrLen(s + 1) + 1);
}

int StrCmp(const char *s1, const char *s2)
{
    assert(s1);
    assert(s2);

    if (*s1 != *s2 || '\0' == *s1)
    {
        return (*s1 - *s2);
    }

    return (StrCmp(s1 + 1, s2 + 1));
}

char *StrCpy(char *dest, const char *src)
{
    assert(src);
    assert(dest);

    *dest = *src;

    if ('\0' == *src)
    {
        return (dest);
    }

    return (StrCpy(dest + 1, src + 1) - 1);
}

char *StrCat(char *dest, const char *src)
{
    assert(src);
    assert(dest);

    if ('\0' != *dest)
    {
        return (StrCat(dest + 1, src) - 1);
    }

    if ('\0' == *src)
    {
        return (dest);
    }

    *dest = *src;
    *(dest + 1) = '\0';

    return (StrCat(dest + 1, src + 1) - 1);
}

char *StrStr(const char *haystack, const char *needle)
{
    assert(haystack);
    assert(needle);

    if ('\0' == *needle)
    {
        return ((char *)haystack);
    }

    if ('\0' == *haystack)
    {
        return (NULL);
    }

    if ((*haystack == *needle) && (haystack + 1) == (StrStr(haystack + 1, needle + 1)))
    {
        return ((char *)haystack);
    }

    return (StrStr(haystack + 1, needle));
}