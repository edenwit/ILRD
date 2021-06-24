#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "heap.h"
#include "vector.h"

#define CAPACITY 50
#define LEFT_CHILD(index) ((index * 2) + 1)
#define RIGHT_CHILD(index) ((index * 2) + 2)
#define PARENT(index) ((index - 1 ) / 2)

/* 
typedef int (*cmp_func_t)(const void *cur_node_data, const void *inserted_data);
typedef int (*is_match_func_t)(const void *cur_node_data, const void *searched_data);

typedef struct heap heap_t;
 */



struct heap
{
    vector_t *vector;
    cmp_func_t cmp_func;
};

static void SwapPointers(heap_t *heap, size_t index1, size_t index2);
static void HeapifyUp(heap_t *heap);
static void HeapifyDown(heap_t *heap, size_t start_index);

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

    VectorDestroy(heap->vector);

    free(heap);

    return;
}

int HeapPush(heap_t *heap, void *data)
{
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

    VectorSetElem(heap->vector, 0, VectorGetElem(heap->vector, VectorSize(heap->vector) - 1));
 
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

    return (VectorGetElem(heap->vector, 0));
}

size_t HeapSize(const heap_t *heap)
{
    assert(heap);

    return (VectorSize(heap->vector));
}

int HeapIsEmpty(const heap_t *heap)
{
    assert(heap);

    return (0 == HeapSize(heap));
}

void HeapRemove(heap_t *heap, is_match_func_t is_match, const void *searched_data)
{
    size_t i = 0;
    size_t heap_size = 0;
    
    assert(heap);
    assert(is_match);
/*  assert(searched_data);*/

    heap_size = HeapSize(heap);

    for (i = 0; i < heap_size; ++i)
    {
        if (is_match(searched_data, VectorGetElem(heap->vector, i)))
        {
            VectorSetElem(heap->vector, i, VectorGetElem(heap->vector, heap_size - 1));
            VectorPopBack(heap->vector);
            HeapifyDown(heap, i);

            return;
        }
    }

    return;
}

static void HeapifyUp(heap_t *heap)
{
    size_t current_index = 0;

    assert(heap);

    current_index = HeapSize(heap) - 1;

    while (0 < current_index)
    {
        if (0 < heap->cmp_func(VectorGetElem(heap->vector, current_index), VectorGetElem(heap->vector, PARENT(current_index))))
        {
            SwapPointers(heap, current_index, PARENT(current_index));

            current_index = PARENT(current_index);
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

    assert(heap);

    last_index_used = HeapSize(heap);

    while (last_index_used > LEFT_CHILD(start_index))
    {
        if (LEFT_CHILD(start_index) < last_index_used)
        {
            if (RIGHT_CHILD(start_index) < last_index_used)
            { 
                if (0 < heap->cmp_func(VectorGetElem(heap->vector, LEFT_CHILD(start_index)), VectorGetElem(heap->vector, RIGHT_CHILD(start_index))))
                {
                    big_boy_index = LEFT_CHILD(start_index);
                }
                else
                {
                    big_boy_index = RIGHT_CHILD(start_index);
                }
            }
            else
            {
                big_boy_index = LEFT_CHILD(start_index);
            }
        }
        else
        {
            return;
        }

        if (0 > heap->cmp_func(VectorGetElem(heap->vector, start_index), VectorGetElem(heap->vector, big_boy_index)))
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
	void *temp = VectorGetElem(heap->vector, index1);
	
	assert (heap);
	
    VectorSetElem(heap->vector, index1, VectorGetElem(heap->vector, index2));
    VectorSetElem(heap->vector, index2, temp);

	return;
}

