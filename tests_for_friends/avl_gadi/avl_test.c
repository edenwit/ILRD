#include <stdio.h>

#include "avl.h"

#define UNUSED(x) ((void)x)

static int Compare(void *data1, void *data2);
/* static int PrintAvl(void *data, void *param); */
static void TestAvl();

int main()
{
    TestAvl();

    return 0;
}

static void TestAvl()
{
    int array[] = {20, 30, 10, 16, 18, 19, 17, 14, 1, 6, 40, 35, 50, 25, 26, -15, -20, -30};
    int remove_arr[] = {40, 10, 14, 1, 6, 26, 25, 20, 17, 35, 50, 19, 18, 16};
    int result_arr[] = {-30, -20, -15, 30};
    size_t tree_hight = 5;
    int num_to_find = 14;
    int not_exist = -2;

    size_t size = sizeof(array) / sizeof(array[0]);
    size_t size2 = sizeof(remove_arr) / sizeof(remove_arr[0]);
    size_t size3 = sizeof(result_arr) / sizeof(result_arr[0]);
    size_t i = 0;

    avl_t *tree = AVLCreate(Compare);

    if (NULL == tree)
    {
        printf("malloc failed at line: %d\n", __LINE__);
    }

    if (1 != AVLIsEmpty(tree))
    {
        printf("test avlIsEmpty failed at line: %d\n", __LINE__);
    }

    if (0 != AVLHeight(tree))
    {
        printf("test AVLHeight failed at line: %d\n", __LINE__);
    }

    if (0 != AVLSize(tree))
    {
        printf("test AvlSize failed at line: %d\n", __LINE__);
    }

    for (i = 0; i < size; ++i)
    {
        if (0 != AVLInsert(tree, (void *)(array + i)))
        {
            printf("test AvlInsert failed at line: %d at index: %lu\n", __LINE__, i);
        }
    }

    if (size != AVLSize(tree))
    {
        printf("test avlSize failed at line: %d\n", __LINE__);
    }

    if (0 != AVLIsEmpty(tree))
    {
        printf("test avlIsEmpty failed at line: %d\n", __LINE__);
    }

    if (num_to_find != *(int *)AVLFind(tree, (void *)&num_to_find))
    {
        printf("test AVLFind failed at line: %d\n", __LINE__);
    }

    if (NULL != AVLFind(tree, (void *)&not_exist))
    {
        printf("test AVLFind failed at line: %d\n", __LINE__);
    }

    if (tree_hight != AVLHeight(tree))
    {
        printf("test AVLHeight failed at line: %d\n", __LINE__);
    }

    AVLRemove(tree, (void *)&not_exist);

    if (size != AVLSize(tree))
    {
        printf("test avlSize failed at line: %d\n", __LINE__);
    }

    for (i = 0; i < size2; ++i)
    {
        AVLRemove(tree, (void *)(remove_arr + i));
    }

    if (size3 != AVLSize(tree))
    {
        printf("test avlSize failed at line: %d\n", __LINE__);
    }

    for (i = 0; i < size3; ++i)
    {
        if (*(result_arr + i) != *(int *)AVLFind(tree, (void *)(result_arr + i)))
        {
            printf("test AVLFind failed at line: %d at index: %lu\n", __LINE__, i);
        }
    }

    AVLDestroy(tree);

    return;
}

static int Compare(void *data1, void *data2)
{
    return (*(int *)data1 - *(int *)data2);
}

/* static int PrintAvl(void *data, void *param)
{
    UNUSED(param);

    printf("%d ", *(int *)data);

    return 0;
} */