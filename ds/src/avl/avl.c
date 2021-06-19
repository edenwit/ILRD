/*  Developer: Eden Wittenberg;									*
 *  Status: done;												*
 *  Date Of Creation:14.06.21;									*
 *  Date Of Approval:16.06.21;									*
 *  Review By: Avital Moses;									*
 *  Description: AVL tree;			                    		*/

#include <stddef.h>     /* size_t */
#include <assert.h>
#include <stdlib.h> /* malloc */
#include "avl.h"

#define UNUSED(X) ((void)X)
#define MAX2(X, Y) ((X) > (Y) ? (X) : (Y))

typedef enum childrens
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDRENS
} childrens_t;

typedef struct avl_node avl_node_t;

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

typedef int (*travese_func)(avl_node_t *node, act_func_t func, void *param);

static int InnerForEach(avl_node_t *node, act_func_t func,
                        void *param, order_t order);
static int ForEachPreOrder(avl_node_t *node, act_func_t func, void *param);
static int ForEachInOrder(avl_node_t *node, act_func_t func, void *param);
static int ForEachPostOrder(avl_node_t *node, act_func_t func, void *param);

static int Add1(void *data, void *param);
static int FreeNode(void *node);

static void *InnerFind(avl_node_t *node, cmp_func_t func, const void *data);
static avl_node_t *InnerInsert(avl_node_t *root,
                               avl_node_t *node, cmp_func_t cmp_func);
static size_t InnerHeight(avl_node_t *root);
static void InnerDestroy(avl_node_t *node);
static avl_node_t *InnerRemove(avl_node_t *node, void *data, cmp_func_t func);

static void *NextData(avl_node_t *node);

avl_t *AVLCreate(cmp_func_t func)
{
    avl_t *tree = (avl_t *)malloc(sizeof(avl_t));
    
    assert(func);

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

    InnerDestroy(tree->root);

    free(tree);

    return;
}

size_t AVLSize(const avl_t *tree)
{
    size_t counter = 0;

    assert(tree);

    if (!AVLIsEmpty(tree))
    {
        AVLForEach((avl_t *)tree, Add1, &counter, PRE_ORDER);
    }

    return (counter);
}

int AVLIsEmpty(const avl_t *tree)
{
    assert(tree);

    return (NULL == tree->root);
}

size_t AVLHeight(const avl_t *tree)
{
    if (AVLIsEmpty(tree))
    {
        return (0);
    }

    return (InnerHeight(((avl_t *)tree)->root) - 1);
}

int AVLInsert(avl_t *tree, void *data)
{
    avl_node_t *node = (avl_node_t *)malloc(sizeof(avl_node_t));

    if (NULL == node)
    {
        return (1);
    }

    node->data = data;
    node->children[LEFT] = NULL;
    node->children[RIGHT] = NULL;
    node->balance_factor = 0;

    if (AVLIsEmpty(tree))
    {
        tree->root = node;

        return (0);
    }

    InnerInsert(tree->root, node, tree->func);

    return (0);
}

void AVLRemove(avl_t *tree, const void *data)
{
    tree->root = InnerRemove(tree->root, (void *)data, tree->func);
}

/* ---------------------- Inner Functions ---------------------------------- */

static avl_node_t *InnerRemove(avl_node_t *node, void *data, cmp_func_t func)
{
    int cmp_res = 0;
    avl_node_t *tmp_node = NULL;

    if (NULL == node)
    {
        return (NULL);
    }

    cmp_res = func(node->data, data);

    if (0 == cmp_res)
    {
        if (node->children[RIGHT])
        {
            node->data = NextData(node->children[RIGHT]);
            node->children[RIGHT] 
            = InnerRemove(node->children[RIGHT], node->data, func);
        }

        else
        {
            tmp_node = node->children[LEFT];

            FreeNode(node);

            return (tmp_node);
        }
    }

    else if (0 > cmp_res)
    {
        node->children[RIGHT] = InnerRemove(node->children[RIGHT], data, func);

        return (node);
    }
    
    node->children[LEFT] = InnerRemove(node->children[LEFT], data, func);

    return (node); 
}


static avl_node_t *InnerInsert(avl_node_t *root, avl_node_t *node,
                               cmp_func_t cmp_func)
{
    if (NULL == root)
    {
        return (node);
    }

    if (0 > cmp_func(root->data, node->data))
    {
        root->children[RIGHT] = InnerInsert(root->children[RIGHT],
                                            node, cmp_func);

        return (root);
    }
    
    root->children[LEFT] = InnerInsert(root->children[LEFT], node, cmp_func);

    return (root);
}

static void *NextData(avl_node_t *node)
{
    assert(node);

    if (!node->children[LEFT])
    {
        return (node->data);
    }

    return (NextData(node->children[LEFT]));
}

void *AVLFind(const avl_t *tree, const void *data)
{
    return (InnerFind(tree->root, tree->func, data));
}

int AVLForEach(avl_t *tree, act_func_t func, void *param, order_t order)
{
    return (InnerForEach(tree->root, func, param, order));
}

static int InnerForEach(avl_node_t *node, act_func_t func,
                        void *param, order_t order)
{
    static travese_func func_arr[] = 
                        {ForEachPreOrder, ForEachInOrder, ForEachPostOrder};

    return (func_arr[order](node, func, param));
}

static int ForEachPreOrder(avl_node_t *node, act_func_t func, void *param)
{
    int status = 0;

    if (NULL == node)
    {
        return (status);
    }

    status = func(node->data, param);

    if (status)
    {
        return (status);
    }

    status = ForEachPreOrder(node->children[LEFT], func, param);

    if (status)
    {
        return (status);
    }
    
    return (ForEachPreOrder(node->children[RIGHT], func, param));
}

static int ForEachInOrder(avl_node_t *node, act_func_t func, void *param)
{
    int status = 0;

    if (NULL == node)
    {
        return (status);
    }

    status = ForEachInOrder(node->children[LEFT], func, param);

    if (status)
    {
        return (status);
    }
    
    status = func(node->data, param);

    if (status)
    {
        return (status);
    }

    return (ForEachInOrder(node->children[RIGHT], func, param));
}

static int ForEachPostOrder(avl_node_t *node, act_func_t func, void *param)
{
    int status = 0;

    if (NULL == node)
    {
        return (status);
    }

    status = ForEachPostOrder(node->children[LEFT], func, param);

    if (status)
    {
        return (status);
    }

    status = ForEachPostOrder(node->children[RIGHT], func, param);

    if (status)
    {
        return (status);
    }

    return (func(node->data, param));
}

static void *InnerFind(avl_node_t *node, cmp_func_t func, const void *data)
{
    int cmp_res = 0;
 
    if (NULL == node)
    {
        return (NULL);
    }

    cmp_res = func(node->data, (void *)data);

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


static int Add1(void *data, void *param)
{
    UNUSED(data);

    ++(*(size_t *)param);

    return (0);
}

static int FreeNode(void *node)
{
    assert(node);

    (avl_node_t *)node->children[LEFT] = NULL;
    (avl_node_t *)node->children[RIGHT] = NULL;

    free(node);

    return (0);
}

static size_t InnerHeight(avl_node_t *root)
{
    if (NULL == root)
    {
        return (0);
    }

    return (MAX2(InnerHeight(root->children[LEFT]),
                 InnerHeight(root->children[RIGHT])) + 1);
}

static void InnerDestroy(avl_node_t *node)
{
    if (NULL == node)
    {
        return;
    }

    InnerDestroy(node->children[LEFT]);

    InnerDestroy(node->children[RIGHT]);

    FreeNode(node);

    return;
}