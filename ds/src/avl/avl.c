#include <stddef.h>     /* size_t */

#include "avl.h"

typedef enum childrens
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDRENS
}childrens_t;

typedef struct avl_node
{
    void *data;
    struct avl_node *children[NUM_OF_CHILDRENS];
    int balance_factor;
} avl_node_t;

struct avl
{
    cmp_func_t func;
    struct avl_node_t *root;
};

/*
typedef struct avl avl_t;

typedef int (*cmp_func_t)(void *data1, void *data2);
typedef int (*act_func_t)(void *tree_data, void *user_param);

typedef enum order
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
}order_t;
*/

typedef int (*travese_func)(avl_node_t *node, act_func_t func, void *param);

static int InnerForEach(avl_node_t *node, act_func_t func, void *param, order_t order);
static int ForEachPreOrder(avl_node_t *node, act_func_t func, void *param);
static int ForEachInOrder(avl_node_t *node, act_func_t func, void *param);
static int ForEachPostOrder(avl_node_t *node, act_func_t func, void *param);

static void *InnerFind(avl_node_t *node, cmp_func_t func, void *data);

static size_t Add1(void *data, void *param);
static void ActionRemove(avl_node_t *node, void *param);

static void InnerRemove();

avl_t *AVLCreate(cmp_func_t func)
{
    assert(func);

    avl_t *tree = (avl_t *)malloc(sizeof(avl_t));

    if (NULL == tree)
    {
        return (NULL);
    }

    tree->root = NULL;
    tree->func = func;

    return(tree);
}

void AVLDestroy(avl_t *tree)
{
    assert(tree);

    ForEachPostOrder(tree->root, ActionRemove, NULL);
}

size_t AVLSize(const avl_t *tree)
{
    size_t counter = 0;

    assert(tree);
    assert(tree->root);

    ForEachPostOrder(tree->root, Add1, &counter);

    return (counter);
}

int AVLIsEmpty(const avl_t *tree)
{
    assert(tree);

    return (NULL == tree->root);
}

size_t AVLHeight(const avl_t *tree);

int AVLInsert(avl_t *tree, void *data);

void AVLRemove(avl_t *tree, const void *data);

void *AVLFind(const avl_t *tree, const void *data)
{
    return (InnerFind(tree->root, tree->func, data));
}

int AVLForEach(avl_t *tree, act_func_t func, void *param, order_t order)
{
    return (InnerForEach(tree->root, func, param, order));
}

static int InnerForEach(avl_node_t *node, act_func_t func, void *param, order_t order)
{
    static travese_func func_arr[] = {ForEachPreOrder, ForEachInOrder, ForEachPostOrder};

    return (func_arr[order](node, func, param));
}

static int ForEachPreOrder(avl_node_t *node, act_func_t func, void *param)
{
    assert(node);

    if (NULL == node)
    {
        return (0);
    }

    if (func(node->data, param))
    {
        return (1);
    }

    if (ForEachPreOrder(node->children[LEFT], func, param))
    {
        return (1);
    }
    
    return (ForEachPreOrder(node->children[RIGHT], func, param));
}

static int ForEachInOrder(avl_node_t *node, act_func_t func, void *param)
{
    assert(node);

    if (NULL == node)
    {
        return (0);
    }

    if (ForEachInOrder(node->children[LEFT], func, param))
    {
        return (1);
    }
    
    if (func(node->data, param))
    {
        return (1);
    }

    return (ForEachInOrder(node->children[RIGHT], func, param));
}

static int ForEachPostOrder(avl_node_t *node, act_func_t func, void *param)
{
    assert(node);

    if (NULL == node)
    {
        return (0);
    }

    if (ForEachPostOrder(node->children[LEFT], func, param))
    {
        return (1);
    }

    if (ForEachPostOrder(node->children[RIGHT], func, param))
    {
        return (1);
    }

    return (func(node->data, param));
}

static void *InnerFind(avl_node_t *node, cmp_func_t func, void *data)
{
    int cmp_res = 0;
 
    if (NULL == node)
    {
        return (1);
    }

    cmp_res = func(node->data, data);

    if (0 == cmp_res)
    {
        return (node->data);
    }

    else if (0 > cmp_res)
    {
        return (InnerFind(node->children[RIGHT], func, data));
    }
    
    return (InnerFind(node->children[LEFT], func, data));
}


static size_t Add1(void *data, void *param)
{
    UNUSED(data);

    ++(*(size_t *)param);

    return (0);
}

static void ActionRemove(avl_node_t *node, void *param)
{
    UNUSED(param);

    assert(node);

    node->children[LEFT] = NULL;
    node->children[RIGHT] = NULL;

    free(node);

    return;
}
