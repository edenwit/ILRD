#include <stddef.h> /* size_t */
#include <stdio.h> /* printf */

#include "avl.h"

#define UNUSED(X) ((void) X)

int Cmp_Num(void *data1, void *data2);
static void AVLTest();
static int PrintData(void * data, void *param);
static void PrintTree(const avl_t *tree);
static void TestRemove();

static int Cmp(void *data1, void *data2);
static int PrintArray(void *tree_data, void *user_param);


int main()
{
	AVLTest();
	TestRemove();
	
	return (0);
}

static void AVLTest()
{
	avl_t *tree_test = AVLCreate(Cmp_Num);

	/*avl_iter_t iter1 = NULL;*/
	int arr[] = {8, 3, 10, 1, 6, 15, 14, 4, 7, 12, 11, 13};
	/* int arr[] = {8, 3, 10, 1, 6, 15, 14, 4, 7, 12, 11, 13, 17, 19, 21, 23, 65, 69, 82, 81, 900, -517, -5, -6, -1, 0 , -99, 98, 104, 103, 101, 102, 100}; */
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
		printf("inserted %d, ",*(arr + i));
   	    printf("Size: %ld, ", AVLSize(tree_test));
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

	AVLDestroy(tree_test);

}

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

static void TestRemove()
{
    avl_t *tree = AVLCreate(Cmp); 
    size_t hights[] = {3,3,3,3,3,2,2,2,2,1};
    int arr[] = {10,8,15,17,16,7,2,100,45,18,20,0,89};
    int remove[] = {8,100,20,0,10,17,16,7,2,45};

    size_t arr_size = sizeof(arr) / sizeof(int);
    size_t remove_size = sizeof(remove) / sizeof(int);
    size_t i = 0;

    while (i < arr_size)
    {
        printf("Insert: %d\n", arr[i]);
        AVLInsert(tree, arr+i);
        AVLForEach(tree, PrintArray , NULL , IN_ORDER);
        printf("\n");
        ++i;
    }


    if (4 != AVLHeight(tree))
    {
        printf("LINE:%d error.\n", __LINE__);
        printf("Expected hight: %d.\n", 6);
        printf("Actual hight: %ld.\n\n",AVLHeight(tree));
    }

    i = 0;

     printf("\n\n");
    while (i < remove_size)
    {
        printf("Remove: %d\n", remove[i]);
        AVLRemove(tree, remove+i);
        AVLForEach(tree, PrintArray , NULL , IN_ORDER);
        printf("\n");
        
        if (hights[i] != AVLHeight(tree))
        {   
            printf("LINE:%d error.\n", __LINE__);
            printf("Expected hight: %ld.\n", hights[i]);
            printf("Actual hight: %ld.\n\n",AVLHeight(tree));
        }
        
        ++i;
    }

    AVLDestroy(tree);

    return;
}
static int PrintArray(void *tree_data, void *user_param)
{
	UNUSED(user_param);

    printf("%d ", *(int *)tree_data);

    return 0;
}
static int Cmp(void *data1, void *data2)
{
    return (*(int *)data1 - *(int *)data2);
}