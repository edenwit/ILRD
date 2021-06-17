#include <stdio.h>	/* printf */
#include <assert.h> /* assert */

#include "../../ds/include/avl.h"

#define UNUSED(X) ((void)X)

typedef struct avl_node avl_node_t;

typedef enum childrens
{
	LEFT,
	RIGHT,
	NUM_OF_CHILDRENS
} childrens_t;

struct avl_node
{
	void *data;
	struct avl_node *children[NUM_OF_CHILDRENS];
	int balance_factor;
};

struct avl
{
    cmp_func_t func;
    avl_node_t *root;
};


int Cmp_Num(void *data1, void *data2);

static int PrintData(void *data, void *param);
static void PrintTree(const avl_t *tree);

static void InnerMirrorTree(avl_node_t *node);
static void SwapNodes(avl_node_t **left_node, avl_node_t **right_node);

static void TestMirrorTree();
void MirrorTree(avl_t *tree);

int main()
{
	TestMirrorTree();

	return (0);
}

static void TestMirrorTree()
{
	avl_t *tree_test = AVLCreate(Cmp_Num);

	/*avl_iter_t iter1 = NULL;*/
	int arr[] = {8, 3, 10, 1, 6, 14, 4, 7, 12, 15, 11, 13, 17, 19, 21, 23, 65, 69, 81, 82, 900, -517, -5, -6, -1, 0, -99, 98, 99, 100, 101, 102, 103, 104};
	size_t arr_size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;

	if (NULL == tree_test)
	{
		printf("AVLCreate failed\n");
	}

	for (i = 0; i < arr_size; ++i)
	{
		AVLInsert(tree_test, (arr + i));
		printf("inserted %d\n", *(arr + i));
		printf("Size: %ld\n", AVLSize(tree_test));
		printf("Height: %ld\n", AVLHeight(tree_test));
	}

	PrintTree(tree_test);

	MirrorTree(tree_test);

	PrintTree(tree_test);

	AVLDestroy(tree_test);

	return;
}

void MirrorTree(avl_t *tree)
{
	InnerMirrorTree(tree->root);

	return;
}

static void InnerMirrorTree(avl_node_t *node)
{
	if (NULL == node)
	{
		return;
	}

	SwapNodes(&(node->children[LEFT]), &(node->children[RIGHT]));

	InnerMirrorTree(node->children[LEFT]);
	InnerMirrorTree(node->children[RIGHT]);

	return;
}

static void SwapNodes(avl_node_t **left_node, avl_node_t **right_node)
{
	avl_node_t *tmp_node = NULL;

	assert(left_node);
	assert(right_node);

	tmp_node = *left_node;
	*left_node = *right_node;
	*right_node = tmp_node;

	return;
}

static int PrintData(void *data, void *param)
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

int Cmp_Num(void *data1, void *data2)
{

	return (*(int *)data1 - *(int *)data2);
}
