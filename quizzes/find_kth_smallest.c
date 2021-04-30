#include <limits.h>
#include <stdio.h>


#include "../ds/src/dll/dll.h"

#define CHARS 256

int FindKthSmallest(int *arr, size_t arr_size, size_t kth_smallest);
static void FindKthSmallestTest();

static int FindMatchInt(const void * data, const void *param);
static int PrintInt(void *data,void *param);

int main()
{
	FindKthSmallestTest();

	return 0;
}

int FindKthSmallest(int *arr, size_t arr_size, size_t kth_smallest)
{
	d_list_t *list = DLLCreate();
	d_list_iter_t iter = NULL;
	
 	size_t i = 0;
 	int min_num = INT_MAX;
 	
 	if (kth_smallest > arr_size)
 	{
 		kth_smallest = arr_size - 1;
 	}
 	
    for (i = 0; i < arr_size; ++i)
    {
		iter = DLLInsert(DLLEnd(list), (arr + i));
    } 
    
	printf("\n");	

	iter = DLLBegin(list);       		 
	i = 0;
	
	printf("k at start: %ld\n", kth_smallest);
	
   	DLLForEach(DLLBegin(list), DLLEnd(list), PrintInt, NULL);	
    printf("\n");    

    while(kth_smallest > 0)
    {
   		min_num = INT_MAX;
        for (iter = DLLBegin(list); !DLLIsSameIter(iter, DLLEnd(list)); iter = DLLNext(iter))
    	{
			if (*(int *)DLLGetData(iter) < min_num)
			{
				min_num = *(int *)DLLGetData(iter);		
			}		
			++i;
   		}
   		DLLRemove(DLLFind(DLLBegin(list), DLLEnd(list), FindMatchInt, (const void *)&min_num));
  		i = 0;
    	--kth_smallest;
		iter = DLLBegin(list);       	
    }
    
    return min_num;
}

static void FindKthSmallestTest()
{
	int int_arr[] = {1, 5, 14, 64564, 85, 9, 15, 3, 40000, 0, -50};
	size_t arr_size = sizeof(int_arr) / sizeof(int_arr[0]);
	
	printf("round 1: %d.\n", FindKthSmallest(int_arr, arr_size, 5));
	printf("round 2: %d.\n", FindKthSmallest(int_arr, arr_size, 4));	
	printf("round 3: %d.\n", FindKthSmallest(int_arr, arr_size, 1));		
	printf("round 4: %d.\n", FindKthSmallest(int_arr, arr_size, 8));
			
	return;
}

void PrintArr(char * arr, size_t arr_size)
{
	size_t i = 0;
	for (i = 0; i < arr_size; ++i)
	{
		printf("%c ", arr[i]);

	}
	printf("\n");
		
	return;
}

static int PrintInt(void *data,void *param)
{
    (void)param;

    printf("%d ", *(int *)data);

    return 0; 
}

static int FindMatchInt(const void * data, const void *param)
{
	return (*(int *)data == *(int *)param);
}
