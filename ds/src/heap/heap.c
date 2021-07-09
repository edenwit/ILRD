#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "heap.h"
#include "vector.h"

#define CAPACITY 50

#define LEFT_CHILD_IDX(index) ((index * 2) + 1)
#define RIGHT_CHILD_IDX(index) ((index * 2) + 2)
#define PARENT_IDX(index) ((index - 1 ) / 2)

struct heap
{
    vector_t *vector;
    cmp_func_t cmp_func;
};

static void SwapPointers(heap_t *heap, size_t index1, size_t index2);
static void HeapifyUp(heap_t *heap);
static void HeapifyDown(heap_t *heap, size_t start_index);

/* approved by shir */
heap_t *HeapCreate(cmp_func_t cmp_func)
{
    heap_t *heap = NULL;
    
    assert(cmp_func);

    heap = (heap_t *)malloc(sizeof(heap_t));

    if (NULL == heap)
    {
        return (NULL);
    }

    heap->vector = VectorCreate(CAPACITY);

    if (NULL == heap->vector)
    {
        free(heap);

        return (NULL);
    }

    heap->cmp_func = cmp_func;

    return (heap);
}

void HeapDestroy(heap_t *heap)
{
    assert(heap);
    assert(heap->vector);

    VectorDestroy(heap->vector);

    heap->vector = NULL;
    heap->cmp_func = NULL;

    free(heap);

    return;
}

int HeapPush(heap_t *heap, void *data)
{
    assert(heap);
    assert(heap->vector);

    if (VectorPushBack(heap->vector, data))
    {
        return (1);
    }

    HeapifyUp(heap);

    return (0);
}

void HeapPop(heap_t *heap)
{
    assert(heap);
    assert(heap->vector);

    VectorSetElem(heap->vector, 0, VectorGetElem(heap->vector, 
                                   VectorSize(heap->vector) - 1));
 
    VectorPopBack(heap->vector);

    if (1 < VectorSize(heap->vector))
    {
        HeapifyDown(heap, 0);
    }

    return;
}

void *HeapPeek(const heap_t *heap)
{
    assert(heap);
    assert(heap->vector);

    return (VectorGetElem(heap->vector, 0));
}

size_t HeapSize(const heap_t *heap)
{
    assert(heap);
    assert(heap->vector);

    return (VectorSize(heap->vector));
}

/* approved by shir */
int HeapIsEmpty(const heap_t *heap)
{
    assert(heap);

    return (0 == HeapSize(heap));
}

void *HeapRemove(heap_t *heap, is_match_func_t is_match,
                 const void *searched_data)
{
    size_t i = 0;
    size_t heap_size = 0;
    void *retrieved_data = NULL;
    size_t size = 0;

    assert(heap);
    assert(heap->vector);
    assert(is_match);

    heap_size = HeapSize(heap);

    for (i = 0; i < heap_size; ++i)
    {
        retrieved_data = VectorGetElem(heap->vector, i);

        if (is_match(retrieved_data, searched_data))
        {
            
            VectorSetElem(heap->vector, i, VectorGetElem(heap->vector, 
                        heap_size - 1));
            VectorPopBack(heap->vector);

            size = HeapSize(heap);

            if (1 < size && i < size)
            {
                HeapifyDown(heap, i);
            }

            return (retrieved_data);
        }
    }

    return (NULL);
}

 /*---------------------------- static functions ----------------------------*/

/* approved by shir */
static void HeapifyUp(heap_t *heap)
{
    size_t current_index = 0;
    void *element_value = NULL;

    assert(heap);
    assert(heap->vector);

    current_index = HeapSize(heap) - 1;
    element_value = VectorGetElem(heap->vector, current_index);

    while (0 < current_index)
    {
        if (0 > heap->cmp_func(element_value,
                        VectorGetElem(heap->vector, PARENT_IDX(current_index))))
        {
            SwapPointers(heap, current_index, PARENT_IDX(current_index));

            current_index = PARENT_IDX(current_index);
        }
        else
        {
            return;
        }
    }

    return;
}

static void HeapifyDown(heap_t *heap, size_t start_index)
{
    size_t big_boy_index = 0;
    size_t last_index_used = 0;
    void *element_value = NULL;

    assert(heap);
    assert(heap->vector);

    last_index_used = HeapSize(heap);
    element_value = VectorGetElem(heap->vector, start_index);

    while (last_index_used > LEFT_CHILD_IDX(start_index))
    {
        /* Check if element has a right child */
        if (RIGHT_CHILD_IDX(start_index) < last_index_used)
        { 
            if (0 > heap->cmp_func(
                VectorGetElem(heap->vector, LEFT_CHILD_IDX(start_index)), 
                VectorGetElem(heap->vector, RIGHT_CHILD_IDX(start_index))))
            {
                big_boy_index = LEFT_CHILD_IDX(start_index);
            }
            else
            {
                big_boy_index = RIGHT_CHILD_IDX(start_index);
            }
        }
        else
        {
            big_boy_index = LEFT_CHILD_IDX(start_index);
        }
        if (0 < heap->cmp_func(element_value, 
                               VectorGetElem(heap->vector, big_boy_index)))
        {
            SwapPointers(heap, start_index, big_boy_index);

            start_index = big_boy_index;
        }
        else
        {
            return;
        }
    }

    return;
}

static void SwapPointers(heap_t *heap, size_t index1, size_t index2)
{
	void *temp = NULL;
	
	assert (heap);
    assert(heap->vector);

    temp = VectorGetElem(heap->vector, index1);

    VectorSetElem(heap->vector, index1, VectorGetElem(heap->vector, index2));
    VectorSetElem(heap->vector, index2, temp);

	return;
}