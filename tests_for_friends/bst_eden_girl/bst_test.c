#include <stdio.h> /* standard input output */

#include "bst.h"

#define UNUSED(x) (void)x

/* static void ElementaryTestBst(); */
static void TestBstOneSided();
static void TestBstGeneral();
static int NumsAscending(void *curr_data, void *to_add_data, void *param);

int main()
{
    /*
    ElementaryTestBst();
    */
/*
   TestBstOneSided();
*/ 
   TestBstGeneral();

    return 0;
}

static void TestBstGeneral()
{
    bst_t *tree_1 = NULL;
    bst_iter_t iter = NULL;
    int data[] = {91, 121, 17, 150, 109, 22, -1, -10, 1, 7,
		  15, 20, 23, 18, 107, 111, 120, 100, 98, 96};
    int data_size = sizeof(data) / sizeof(data[0]);
    int i = 0;
    int data_to_find = 0;
    
    /* Initlialize tree */
    tree_1 = BstCreate(NumsAscending, NULL);
    if (NULL == tree_1)
    {
	printf("Tree initialization failed (code line #%d)\n", __LINE__);
    }

    /* Enter data to tree */
    for (i = 0; i < data_size; i++)
    {
	iter = BstInsert(tree_1, &data[i]);

	if (*(int *)BstGetData(iter) != data[i])
	{
	    printf("Insert test failed - index #%d (code line #%d)\n", i, __LINE__);
	}
    }

    if (0 != BstIsEmpty(tree_1))
    {
	printf("IsEmpty test failed (code line #%d)\n", __LINE__);
    }
    if ((size_t)data_size != BstSize(tree_1))
    {
	printf("Size test failed (code line #%d)\n", __LINE__);
    }

    /* Test to find few existing data */
    data_to_find = 23;
    iter = BstFind(tree_1, &data_to_find);
    if (data_to_find != *(int *)BstGetData(iter))
    {
	printf("Search in existing data failed (code line #%d)\n", __LINE__);

    }
    data_to_find = -1;
    iter = BstFind(tree_1, &data_to_find);
    if (data_to_find != *(int *)BstGetData(iter))
    {
	printf("Search in existing data failed (code line #%d)\n", __LINE__);
    }
    
    data_to_find = 109;
    iter = BstFind(tree_1, &data_to_find);
    if (data_to_find != *(int *)BstGetData(iter))
    {
	printf("Search in existing data failed (code line #%d)\n", __LINE__);
    }

    /* Test to search non-existing data */
    data_to_find = -2;
    iter = BstFind(tree_1, &data_to_find);
    if (!BstIterIsEqual(BstEnd(tree_1), iter))
    {
	printf("Search for non-existing data failed (code line #%d)\n", __LINE__);

    }
    
    data_to_find = 7950;
    iter = BstFind(tree_1, &data_to_find);
    if (!BstIterIsEqual(BstEnd(tree_1), iter))
    {
	printf("Search for non-existing data failed (code line #%d)\n", __LINE__);

    }
        data_to_find = 94;
    iter = BstFind(tree_1, &data_to_find);
    if (!BstIterIsEqual(BstEnd(tree_1), iter))
    {
	printf("Search for non-existing data failed (code line #%d)\n", __LINE__);

    }

    /* Remove test */
    /* Remove node with no children: */
    data_to_find = 150;
    iter = BstFind(tree_1, &data_to_find);
    BstRemove(iter);

    /* Test integrity of test of tree by parsing back and forth
     * and at the same time check if number was removed */

    /* Iterate forward */
    iter = BstBegin(tree_1);
    while (!BstIterIsEqual(BstEnd(tree_1), iter))
    {
	if (*(int *)BstGetData(iter) == data_to_find)
	{
	    printf("Remove test failed (code line #%d)\n", __LINE__);
	}
	
	iter = BstNext(iter);
    }

    /* Iterate backward */
    iter = BstEnd(tree_1);
    while (!BstIterIsEqual(BstBegin(tree_1), iter))
    {
	iter = BstPrev(iter);
	
	if (*(int *)BstGetData(iter) == data_to_find)
	{
	    printf("Remove test failed (code line #%d)\n", __LINE__);
	}
    }

    /* Remove node with 1 child (left): */
    data_to_find = 111;
    iter = BstFind(tree_1, &data_to_find);
    BstRemove(iter);

    /* Test integrity of test of tree by parsing back and forth
     * and at the same time check if number was removed */

    /* Iterate forward */
    iter = BstBegin(tree_1);
    while (!BstIterIsEqual(BstEnd(tree_1), iter))
    {
	if (*(int *)BstGetData(iter) == data_to_find)
	{
	    printf("Remove test failed (code line #%d)\n", __LINE__);
	}
	
	iter = BstNext(iter);
    }

    /* Iterate backward */
    iter = BstEnd(tree_1);
    while (!BstIterIsEqual(BstBegin(tree_1), iter))
    {
	iter = BstPrev(iter);
	
	if (*(int *)BstGetData(iter) == data_to_find)
	{
	    printf("Remove test failed (code line #%d)\n", __LINE__);
	}
    }

    /* Remove node with 1 child (right): */
    data_to_find = 98;
    iter = BstFind(tree_1, &data_to_find);
    BstRemove(iter);

    /* Test integrity of test of tree by parsing back and forth
     * and at the same time check if number was removed */

    /* Iterate forward */
    iter = BstBegin(tree_1);
    while (!BstIterIsEqual(BstEnd(tree_1), iter))
    {
	if (*(int *)BstGetData(iter) == data_to_find)
	{
	    printf("Remove test failed (code line #%d)\n", __LINE__);
	}
	
	iter = BstNext(iter);
    }

    /* Iterate backward */
    iter = BstEnd(tree_1);
    while (!BstIterIsEqual(BstBegin(tree_1), iter))
    {
	iter = BstPrev(iter);
	
	if (*(int *)BstGetData(iter) == data_to_find)
	{
	    printf("Remove test failed (code line #%d)\n", __LINE__);
	}
    }

    /* Remove node with 2 children (test 1): */
    data_to_find = 17;
    iter = BstFind(tree_1, &data_to_find);
    BstRemove(iter);

    /* Test integrity of test of tree by parsing back and forth
     * and at the same time check if number was removed */

    /* Iterate forward */
    iter = BstBegin(tree_1);
    while (!BstIterIsEqual(BstEnd(tree_1), iter))
    {
	if (*(int *)BstGetData(iter) == data_to_find)
	{
	    printf("Remove test failed (code line #%d)\n", __LINE__);
	}
	
	iter = BstNext(iter);
    }

    /* Iterate backward */
    iter = BstEnd(tree_1);
    while (!BstIterIsEqual(BstBegin(tree_1), iter))
    {
	iter = BstPrev(iter);
	
	if (*(int *)BstGetData(iter) == data_to_find)
	{
	    printf("Remove test failed (code line #%d)\n", __LINE__);
	}
    }

    
    BstDestroy(tree_1);

    return;
}

static void TestBstOneSided()
{
    bst_t *r_sided_tree = NULL;
    bst_t *l_sided_tree = NULL;
    bst_iter_t iter = NULL;
    int data[] = {-700, -20, -9, -1, 0, 7, 95, 167, 169, 500, 3988, 887766, 999999};
    int data_size = sizeof(data) / sizeof(data[0]);
    int i = 0;

    /* Initlialize trees */
    /* Right sided tree: */
    r_sided_tree = BstCreate(NumsAscending, NULL);
    if (NULL == r_sided_tree)
    {
	printf("Tree initialization failed (code line #%d)\n", __LINE__);
    }
    
    /* Left sided tree: */
    l_sided_tree = BstCreate(NumsAscending, NULL);
    if (NULL == l_sided_tree)
    {
	printf("Tree initialization failed (code line #%d)\n", __LINE__);
    }

    /* Size and IsEmpty test */
    /* Right tree: */
    if (1 != BstIsEmpty(r_sided_tree))
    {
	printf("IsEmpty test failed (code line #%d)\n", __LINE__);
    }
    if (0 != BstSize(r_sided_tree))
    {
	printf("Size test failed (code line #%d)\n", __LINE__);
    }
    /* Left tree: */
    if (1 != BstIsEmpty(l_sided_tree))
    {
	printf("IsEmpty test failed (code line #%d)\n", __LINE__);
    }
    if (0 != BstSize(l_sided_tree))
    {
	printf("Size test failed (code line #%d)\n", __LINE__);
    }
    
    /* Enter data to trees */
    /* Right sided tree: */
    for (i = 0; i < data_size; i++)
    {
	iter = BstInsert(r_sided_tree, &data[i]);

	if (*(int *)BstGetData(iter) != data[i])
	{
	    printf("Insert test failed - index #%d (code line #%d)\n", i, __LINE__);
	}
    }

    /* Left sided tree: */
    for (i = data_size -1; i >= 0; i--)
    {
	iter = BstInsert(l_sided_tree, &data[i]);

	if (*(int *)BstGetData(iter) != data[i])
	{
	    printf("Insert test failed - index #%d (code line #%d)\n", i, __LINE__);
	}
    }

    /* Size and IsEmpty test */
    /* Right tree: */
    if (0 != BstIsEmpty(r_sided_tree))
    {
	printf("IsEmpty test failed (code line #%d)\n", __LINE__);
    }
    if ((size_t)data_size != BstSize(r_sided_tree))
    {
	printf("Size test failed (code line #%d)\n", __LINE__);
    }
    /* Left tree: */
    if (0 != BstIsEmpty(l_sided_tree))
    {
	printf("IsEmpty test failed (code line #%d)\n", __LINE__);
    }
    if ((size_t)data_size != BstSize(l_sided_tree))
    {
	printf("Size test failed (code line #%d)\n", __LINE__);
    }

    
    /* Verify data and test next and prev */
    /* Right sided tree - Next test:*/
    iter = BstBegin(r_sided_tree);
    for (i = 0; i < data_size; i++)
    {
	if (*(int *)BstGetData(iter) != data[i])
	{
	    printf("BstNext test failed at index #%d (code line #%d)\n", i, __LINE__);
	}

	iter = BstNext(iter);
    }

    /* Prev test */
    iter = BstEnd(r_sided_tree);
    while (0 < i)
    {
	iter = BstPrev(iter);
	
	if (*(int *)BstGetData(iter) != data[i - 1])
	{
	    printf("BstPrev test failed at index #%d (code line #%d)\n", i, __LINE__);
	}

	--i;
    }
    /* Left sided tree - Next test:*/
    iter = BstBegin(l_sided_tree);
    for (i = 0; i < data_size; i++)
    {
	if (*(int *)BstGetData(iter) != data[i])
	{
	    printf("BstNext test failed at index #%d (code line #%d)\n", i, __LINE__);
	}

	iter = BstNext(iter);
    }
    
    /* Prev test */
    iter = BstEnd(l_sided_tree);
    while (0 < i)
    {
	iter = BstPrev(iter);
	
	if (*(int *)BstGetData(iter) != data[i - 1])
	{
	    printf("BstPrev test failed at index #%d (code line #%d)\n", i, __LINE__);
	}

	--i;
    }

    BstDestroy(r_sided_tree);
    BstDestroy(l_sided_tree);
    
    return;
}
/*
static void ElementaryTestBst()
{
    bst_t *my_tree;
    bst_iter_t my_iter = NULL;
    int data = 3;
    int data2 = 6;
    int data3 = 9;
    int data4 = 16;
    int data5 = 7;
    int data6 = 15;
    int data7 = 1;
    int data8 = 2;
    int data9 = 0;

    int to_find = 15;
    
    my_tree = BstCreate(&NumsAscending, NULL);
    
    if (1 != BstIsEmpty(my_tree))
    {
	printf("Is empty test failed (code line #%d)\n", __LINE__); 
    }
    printf("my_tree size = %lu\n", BstSize(my_tree));
    
    BstInsert(my_tree, &data);
    BstInsert(my_tree, &data2);
    BstInsert(my_tree, &data3);
    printf("my_tree size = %lu\n", BstSize(my_tree));
    BstInsert(my_tree, &data4);
    BstInsert(my_tree, &data5);
    BstInsert(my_tree, &data6);
    BstInsert(my_tree, &data7);
    printf("my_tree size = %lu\n", BstSize(my_tree));
    BstInsert(my_tree, &data8);
    BstInsert(my_tree, &data9);

    my_iter = BstBegin(my_tree);

    my_iter = BstFind(my_tree, &to_find);

    printf("Same iter result = %d\n", BstIterIsEqual(my_iter, BstEnd(my_tree)));

    printf("my_iter data = %d\n", *(int *)BstGetData(my_iter));

    printf("my_tree size = %lu\n", BstSize(my_tree));

    my_iter = BstBegin(my_tree);
    printf("my_iter begin data = %d\n", *(int *)BstGetData(my_iter));
    my_iter = BstNext(my_iter);
    printf("my_iter data = %d\n", *(int *)BstGetData(my_iter));
    my_iter = BstNext(my_iter);
    printf("my_iter data = %d\n", *(int *)BstGetData(my_iter));
    my_iter = BstNext(my_iter);
    printf("my_iter data = %d\n", *(int *)BstGetData(my_iter));
    
    printf("\n");

    BstRemove(my_iter);

    
    
    printf("my_tree size = %lu\n", BstSize(my_tree));    

    my_iter = BstBegin(my_tree);
    printf("my_iter begin data = %d\n", *(int *)BstGetData(my_iter));
    my_iter = BstNext(my_iter);
    printf("my_iter data = %d\n", *(int *)BstGetData(my_iter));
    my_iter = BstNext(my_iter);
    printf("my_iter data = %d\n", *(int *)BstGetData(my_iter));
    my_iter = BstNext(my_iter);
    printf("my_iter data = %d\n", *(int *)BstGetData(my_iter));
    my_iter = BstNext(my_iter);
    printf("my_iter data = %d\n", *(int *)BstGetData(my_iter));
    my_iter = BstNext(my_iter);
    printf("my_iter data = %d\n", *(int *)BstGetData(my_iter));
    my_iter = BstNext(my_iter);
    printf("my_iter data = %d\n", *(int *)BstGetData(my_iter));
    my_iter = BstNext(my_iter);
    printf("my_iter data = %d\n", *(int *)BstGetData(my_iter));
    my_iter = BstNext(my_iter);
    
    printf("Same iter result = %d\n", BstIterIsEqual(my_iter, BstEnd(my_tree)));

    my_iter = BstPrev(BstEnd(my_tree));
    printf("data of end prev = %d\n", *(int *)BstGetData(my_iter));

    BstDestroy(my_tree);
    }*/

static int NumsAscending(void *curr_data, void *to_add_data, void *param)
{
    UNUSED(param);

    return (*(int *)curr_data - *(int *)to_add_data);
}
