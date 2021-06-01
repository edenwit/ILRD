#include <stddef.h> /* size_t */
#include <stdio.h> /* printf */

#include "bst.h"

#define UNUSED(X) ((void) X)

int Cmp_Num(void *data1, void *data2, void *param);
static void BSTTest();
static int PrintData(void * data, void *param);
static void PrintTree(const bst_t *tree);

int main()
{
	BSTTest();
	
	return (0);
}

static void BSTTest()
{
	bst_t *tree_test = BstCreate(Cmp_Num, NULL);
	bst_iter_t iter1 = NULL;
	int arr[] = {8, 3, 10, 1, 6, 14, 4, 7, 12, 15, 11, 13};
	size_t arr_size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;

	if (NULL == tree_test)
	{
		printf("BstCreate failed\n");
	}

	for (i = 0; i < arr_size; ++i)
	{
		BstInsert(tree_test, (void *)(arr + i));
		printf("inserted\n");
	}

	printf("Size: %ld\n", BstSize(tree_test));

	iter1 = BstBegin(tree_test);

	PrintTree(tree_test);

	BstRemove(BstFind(tree_test, (arr + 4)));  
	BstRemove(BstFind(tree_test, (arr + 6)));  

	PrintTree(tree_test);
	iter1 = BstFind(tree_test, (arr + 5));

	printf("iter1: %d, ",*((int *)(BstGetData(iter1))));
	printf("next: %d, ",*((int *)(BstGetData(BstNext(iter1)))));
	printf("prev: %d, \n",*((int *)(BstGetData(BstPrev(iter1)))));
	
	iter1 = BstFind(tree_test, (arr + 0));

	if (*(arr + 0) != *((int *)(BstGetData(BstFind(tree_test, (arr + 0))))))
	{
		printf("BstFind Error\n");
	}

	if (*(arr + 2) != *((int *)(BstGetData(BstFind(tree_test, (arr + 2))))))
	{
		printf("BstFind Error\n");
	}

	if (*(arr + 3) != *((int *)(BstGetData(BstFind(tree_test, (arr + 3))))))
	{
		printf("BstFind Error\n");
	}

	BstDestroy(tree_test);

}

/*
bst_t *BstCreate(cmp_func_ptr_t, void *param);
void BstDestroy(bst_t *tree);
size_t BstSize(const bst_t *tree);
int BstIsEmpty(const bst_t *tree);
bst_iter_t BstInsert(bst_t *tree, void *data);
void BstRemove(bst_iter_t iter);
bst_iter_t BstBegin(bst_t *tree);
bst_iter_t BstEnd(bst_t *tree);
bst_iter_t BstPrev(bst_iter_t iter);
bst_iter_t BstNext(bst_iter_t iter);
int BstIterIsEqual(const bst_iter_t iter1, const bst_iter_t iter2);
void *BstGetData(bst_iter_t iter);
bst_iter_t BstFind(bst_t *tree, void *data);
int BstForEach(bst_iter_t from, bst_iter_t to, act_tunc_ptr_t, void *param);
*/

int Cmp_Num(void *data1, void *data2, void *param)
{
	UNUSED(param);

	return (*(int*)data1 - *(int*)data2);
}


static int PrintData(void * data, void *param)
{
	UNUSED(param);
	
	printf("%d ", *((int *)data));

	return (0);
}

static void PrintTree(const bst_t *tree)
{
	BstForEach(BstBegin((bst_t *)tree), BstEnd((bst_t *)tree), PrintData, NULL);

	printf("\n");
	
	return;
}