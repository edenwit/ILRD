
/* typedef int (*cmp_func_t)(const void *cur_node_data, const void *inserted_data);
typedef int (*is_match_func_t)(const void *cur_node_data, const void *searched_data);

typedef struct heap heap_t; */

#include <stdio.h> /* printf */

#include "heap.h"
#include "vector.h"

static void HeapTest();
static int Cmp(const void *data1, const void *data2);

int main()
{
    HeapTest();

    return (0);
}

static void HeapTest()
{
    heap_t *heap = HeapCreate(Cmp);
    int test_arr[] = {5, 4, 13, 15, 8, 21, 22, 41, 65, 0, 100, 43, 40, 30, -12,35, 33, -1, -100, 48, 1, 17};

    size_t i = 0;
    size_t arr_size = sizeof(test_arr) / sizeof(test_arr[0]);

    if (NULL == heap)
    {
        printf("Heap Create Failed\n");
        
        return;
    }

    for (i = 0; i < arr_size; ++i)
    {
        if (HeapPush(heap, (test_arr + i)))
        {
            printf("Insertion from index #%ld failed\n", i);
        }

        printf("peek: %d - ", *(int *)HeapPeek(heap));
        printf("size: %ld\n", HeapSize(heap));
    }
 
    printf("-------------------------------------\n");

    while (!HeapIsEmpty(heap))
    {
        printf("peek: %d - ", *(int *)HeapPeek(heap));
        printf("size: %ld\n", HeapSize(heap));
        HeapPop(heap);
    }   

    HeapDestroy(heap);

    return;
}

static int Cmp(const void *data1, const void *data2)
{
    return (*(int *)data1 - *(int *)data2);
}
