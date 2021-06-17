#include <stddef.h> /* size_t */
#include <stdio.h> /* printf */

#include "avl.h"

#define UNUSED(X) ((void) X)

int Cmp_Num(void *data1, void *data2);
static void AVLTest();
static int PrintData(void * data, void *param);
static void PrintTree(const avl_t *tree);

int main()
{
	AVLTest();
	
	return (0);
}

static void AVLTest()
{
	avl_t *tree_test = AVLCreate(Cmp_Num);

	/*avl_iter_t iter1 = NULL;*/
	int arr[] = {8, 3, 10, 1, 6, 14, 4, 7, 12, 15, 11, 13, 17, 19, 21, 23, 65, 69, 81, 82, 900, -517, -5, -6, -1, 0 , -99, 98, 99, 100, 101, 102, 103, 104};
	size_t arr_size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;
    int searched = 0;
    int to_remove = 0;

	if (NULL == tree_test)
	{
		printf("AVLCreate failed\n");
	}

    if (!AVLIsEmpty(tree_test))
    {
		printf("AVLIsEmpty Error\n");
    }
   	printf("empty.\n");
	printf("Size: %ld\n", AVLSize(tree_test));

   	printf("try to remove.\n");
    AVLRemove(tree_test, (arr));

   	printf("Size: %ld\n", AVLSize(tree_test));

	AVLInsert(tree_test, (arr));
   	printf("inserted 8.\n");

   	printf("Size: %ld\n", AVLSize(tree_test));
   	printf("try to remove.\n");

    AVLRemove(tree_test, (arr));
	
   	printf("Size: %ld\n", AVLSize(tree_test));


	for (i = 0; i < arr_size; ++i)
	{
		AVLInsert(tree_test, (arr + i));
		printf("inserted %d\n",*(arr + i));
   	    printf("Size: %ld\n", AVLSize(tree_test));
	   	printf("Height: %ld\n", AVLHeight(tree_test));

	}

	printf("Size: %ld\n", AVLSize(tree_test));

	printf("Height: %ld\n", AVLHeight(tree_test));


    PrintTree(tree_test);

    searched = 6;

    if (!AVLFind(tree_test, &searched))
    {
		printf("AVLFind Error\n");
    }

    searched = 5;

    if (AVLFind(tree_test, &searched))
    {
		printf("AVLFind Error\n");
    }
   
    searched = -2;

    if (AVLFind(tree_test, &searched))
    {
		printf("AVLFind Error\n");
    }
   
    searched = 8;

    if (!AVLFind(tree_test, &searched))
    {
		printf("AVLFind Error\n");
    }
   
    to_remove = 13;

    AVLRemove(tree_test, &to_remove);

    printf("hi\n");
    PrintTree(tree_test);
	printf("Size: %ld\n", AVLSize(tree_test));
    to_remove = 8;

    AVLRemove(tree_test, &to_remove);
	printf("Height: %ld\n", AVLHeight(tree_test));

    printf("hi\n");
    PrintTree(tree_test);
	printf("Size: %ld\n", AVLSize(tree_test));
    to_remove = 11;
	printf("Height: %ld\n", AVLHeight(tree_test));

    AVLRemove(tree_test, &to_remove);
	printf("Height: %ld\n", AVLHeight(tree_test));

    printf("hi\n");
    PrintTree(tree_test);
	printf("Size: %ld\n", AVLSize(tree_test));
    to_remove = 13;
	printf("Height: %ld\n", AVLHeight(tree_test));

    AVLRemove(tree_test, &to_remove);

    printf("hi\n");
    PrintTree(tree_test);
	printf("Size: %ld\n", AVLSize(tree_test));
    to_remove = 99;

    AVLRemove(tree_test, &to_remove);

    printf("hi\n");
    PrintTree(tree_test);
	printf("Size: %ld\n", AVLSize(tree_test));
	printf("Height: %ld\n", AVLHeight(tree_test));

/* 

	AVLRemove(AVLFind(tree_test, (arr + 4)));  
	AVLRemove(AVLFind(tree_test, (arr + 6)));  

	PrintTree(tree_test);
	iter1 = AVLFind(tree_test, (arr + 5));

	printf("iter1: %d, ",*((int *)(AVLGetData(iter1))));
	printf("next: %d, ",*((int *)(AVLGetData(AVLNext(iter1)))));
	printf("prev: %d, \n",*((int *)(AVLGetData(AVLPrev(iter1)))));
	
	iter1 = AVLFind(tree_test, (arr + 0));

	if (*(arr + 0) != *((int *)(AVLGetData(AVLFind(tree_test, (arr + 0))))))
	{
		printf("AVLFind Error\n");
	}

	if (*(arr + 2) != *((int *)(AVLGetData(AVLFind(tree_test, (arr + 2))))))
	{
		printf("AVLFind Error\n");
	}

	if (*(arr + 3) != *((int *)(AVLGetData(AVLFind(tree_test, (arr + 3))))))
	{
		printf("AVLFind Error\n");
	} */

	AVLDestroy(tree_test);

}

/*
avl_t *AVLCreate(cmp_func_ptr_t, void *param);
void AVLDestroy(avl_t *tree);
size_t AVLSize(const avl_t *tree);
int AVLIsEmpty(const avl_t *tree);
avl_iter_t AVLInsert(avl_t *tree, void *data);
void AVLRemove(avl_iter_t iter);
avl_iter_t AVLBegin(avl_t *tree);
avl_iter_t AVLEnd(avl_t *tree);
avl_iter_t AVLPrev(avl_iter_t iter);
avl_iter_t AVLNext(avl_iter_t iter);
int AVLIterIsEqual(const avl_iter_t iter1, const avl_iter_t iter2);
void *AVLGetData(avl_iter_t iter);
avl_iter_t AVLFind(avl_t *tree, void *data);
int AVLForEach(avl_iter_t from, avl_iter_t to, act_tunc_ptr_t, void *param);
*/

int Cmp_Num(void *data1, void *data2)
{

	return (*(int*)data1 - *(int*)data2);
}


static int PrintData(void * data, void *param)
{
	UNUSED(param);
	
	printf("%d ", *((int *)data));

	return (0);
}

static void PrintTree(const avl_t *tree)
{
	AVLForEach((avl_t *)tree, PrintData, NULL, IN_ORDER);

	printf("\n");
	
	return;
}