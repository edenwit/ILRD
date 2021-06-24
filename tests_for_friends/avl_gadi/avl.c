/*	Developer:         Gad Chevah
 *	Status:            Sent
 *	Reviewer:          Eden W
 *	Date of approval:  -
 *	Description:       Recursive binary search tree
 */

#include "assert.h" /* assert       */
#include <stdlib.h> /* malloc, free */
#include <limits.h> /* INT_MAX      */

#define FAIL 1
#define SUCCESS 0

#define BALANCED 0

#define UNUSED(x) ((void)(x))
#define MAX(x,y) (((x) > (y)) ? (x) : (y))

#include "avl.h"

typedef enum childrens
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDRENS
} childrens_t;

typedef struct avl_node avl_node_t; 

struct avl
{
    cmp_func_t func;
    struct avl_node *root;
};

struct avl_node
{
    void *data;
    struct avl_node *children[NUM_OF_CHILDRENS];
    int balance_factor;
};


/* Inner recursive functions */
static void InnerInsert(avl_node_t *to_insret, avl_node_t *cur_node,
                        cmp_func_t func);
static void *InnerFind(avl_node_t *cur_node, void *data, cmp_func_t func);
static size_t InnerHeight(avl_node_t *cur_node);
static void TraverseNodesDestroy(avl_node_t *cur_node);
static void DestroyNode(avl_node_t *cur_node);

/* remove functions */
static avl_node_t *Next(avl_node_t *node);
static void FreeNode(avl_node_t *node);
static avl_node_t *InnerRemove(avl_node_t *node, const void *data, cmp_func_t func);


/* for each functions */
static int PreOrderAVLForEach(avl_node_t *cur_node, act_func_t func, void *param);
static int InOrderAVLForEach(avl_node_t *cur_node, act_func_t func, void *param);
static int PostOrderAVLForEach(avl_node_t *cur_node, act_func_t func, void *param);

/* size static func */
static int IncreaseCount(void *unused_param, void *count_address);


/* h-file:
            typedef int (*cmp_func_t)(void *data1, void *data2);
            typedef int (*act_func_t)(void *tree_data, void *user_param); */

avl_t *AVLCreate(cmp_func_t func)
{
    avl_t *avl = NULL;

    assert(NULL != func);

    avl = (avl_t *)malloc(sizeof(avl_t));

    if (NULL == avl)
    {
        return (NULL);
    }

    avl->func = func;
    avl->root = NULL;

    return (avl);
}

int AVLIsEmpty(const avl_t *tree)
{
    assert(NULL != tree);

    return (NULL == tree->root);
}

void *AVLFind(const avl_t *tree, const void *data)
{
    assert(NULL != tree);

    if (NULL == tree->root)
    {
        return (NULL);
    }

    return (InnerFind(tree->root, (void *)data, tree->func));
}

int AVLForEach(avl_t *tree, act_func_t func, void *param, order_t order)
{
    assert(NULL != tree);
    assert(NULL != func);
    
    switch (order)
    {
        case PRE_ORDER:
        {
            return (PreOrderAVLForEach(tree->root, func, param));
            break;
        }

        case IN_ORDER:
        {
            return (InOrderAVLForEach(tree->root, func, param));
            break;
        }

        case POST_ORDER:
        {
            return (PostOrderAVLForEach(tree->root, func, param));
            break;   
        }
    }

    return (SUCCESS);
}

size_t AVLSize(const avl_t *tree)
{
    size_t count = 0;

    AVLForEach((avl_t *)tree, IncreaseCount, (void *)&count, PRE_ORDER);

    return (count);
}

void AVLDestroy(avl_t *tree)
{
    assert(NULL != tree);

    TraverseNodesDestroy(tree->root);

    tree->func = NULL;

    free(tree);

    return;
}

size_t AVLHeight(const avl_t *tree)
{
    assert(NULL != tree);
    
    if (AVLIsEmpty(tree))
    {
        return (0);
    }

    return (InnerHeight(tree->root) - 1);
}

int AVLInsert(avl_t *tree, void *data)
{
    avl_node_t *to_insert = NULL;

    assert(NULL != tree);

    to_insert = (avl_node_t *)malloc(sizeof(avl_node_t));

    if (NULL == to_insert)
    {
        return (FAIL);
    }

    to_insert->data = data;
    to_insert->balance_factor = 0;
    to_insert->children[LEFT] = NULL;
    to_insert->children[RIGHT] = NULL;

    if (AVLIsEmpty(tree))
    {
        tree->root = to_insert;

        return (SUCCESS);
    }

    InnerInsert(to_insert, tree->root, tree->func);

    return (SUCCESS);
}

/*-------------------------------- static func ------------------------------*/
static void TraverseNodesDestroy(avl_node_t *cur_node)
{
    if (NULL == cur_node)
    {
        return;;
    }

    TraverseNodesDestroy(cur_node->children[LEFT]);

    TraverseNodesDestroy(cur_node->children[RIGHT]);

    DestroyNode(cur_node);

    return;
}

static void DestroyNode(avl_node_t *cur_node)
{
    assert(NULL != cur_node);

    cur_node->balance_factor = INT_MAX;
    cur_node->data = NULL;
    cur_node->children[RIGHT] = NULL;
    cur_node->children[LEFT] = NULL;

    free(cur_node);

    return;
}

static size_t InnerHeight(avl_node_t *cur_node)
{
    size_t left = 0;
    size_t right = 0;

    if (NULL == cur_node)
    {
        return (0);
    }

    left = InnerHeight(cur_node->children[LEFT]) + 1;
    right = InnerHeight(cur_node->children[RIGHT]) + 1;

    return (MAX(left, right));
} 

static int PreOrderAVLForEach(avl_node_t *cur_node, act_func_t func, void *param)
{
    int func_status = 0;

    assert(NULL != func);

    if (NULL == cur_node)
    {
        return (SUCCESS);
    }

    if (FAIL == func(cur_node->data, param))
    {
        return (FAIL);
    }

    func_status = PreOrderAVLForEach(cur_node->children[LEFT], func, param);

    if (FAIL == func_status)
    {
        return (FAIL);
    }

    func_status = PreOrderAVLForEach(cur_node->children[RIGHT], func, param);

    return (func_status);
}

static int PostOrderAVLForEach(avl_node_t *cur_node, act_func_t func, void *param)
{
    int func_status = 0;

    assert(NULL != func);

    if (NULL == cur_node)
    {
        return (SUCCESS);
    }

    func_status = PostOrderAVLForEach(cur_node->children[LEFT], func, param);

    if (FAIL == func_status)
    {
        return (FAIL);
    }

    func_status = PostOrderAVLForEach(cur_node->children[RIGHT], func, param);

    if (FAIL == func(cur_node->data, param))
    {
        return (FAIL);
    }

    return (func_status);
}

static int InOrderAVLForEach(avl_node_t *cur_node, act_func_t func, void *param)
{
    int func_status = 0;

    assert(NULL != func);

    if (NULL == cur_node)
    {
        return (SUCCESS);
    }

    func_status = InOrderAVLForEach(cur_node->children[LEFT], func, param);

    if (FAIL == func_status)
    {
        return (FAIL);
    }

    if (FAIL == func(cur_node->data, param))
    {
        return (FAIL);
    }

    func_status = InOrderAVLForEach(cur_node->children[RIGHT], func, param);

    return (func_status);
}

static int IncreaseCount(void *unused_param, void *count_address)
{
    assert(NULL != count_address);

    UNUSED(unused_param);

    ++(*((size_t *)count_address));

    return (SUCCESS);
}

static void *InnerFind(avl_node_t *cur_node, void *data, cmp_func_t func)
{
    avl_node_t *next = NULL;
    int cmp_func_status = 0;

    assert(NULL != cur_node);
    assert(NULL != func);

    cmp_func_status = func(data, cur_node->data);

    if  (BALANCED == cmp_func_status)
    {
        return (cur_node->data);
    }

    else if (0 < cmp_func_status)
    {
        next = cur_node->children[RIGHT]; 
    }

    else 
    {
        next = cur_node->children[LEFT]; 
    }

    if (NULL == next)
    {
        return (NULL);
    }

    return (InnerFind(next, data, func));
}

static void InnerInsert(avl_node_t *to_insret, avl_node_t *cur_node,
                        cmp_func_t func)
{
    avl_node_t *next = NULL;
    int cmp_func_status = 0;

    assert(NULL != func);
    assert(NULL != to_insret);
    assert(NULL != cur_node);

    cmp_func_status = func(to_insret->data, cur_node->data);

    /* data > cur data */
    if (0 < cmp_func_status)
    {
        next = cur_node->children[RIGHT];
    }

    else
    {
        next = cur_node->children[LEFT];
    }

    if (next == NULL)
    {
        if (0 < cmp_func_status)
        {
            cur_node->children[RIGHT] = to_insret;
        }

        else
        {
            cur_node->children[LEFT] = to_insret;
        }

        return;
    }

    InnerInsert(to_insret, next, func);

    return;
}

static avl_node_t *InnerRemove(avl_node_t *node, const void *data, cmp_func_t func)
{
    avl_node_t *tmp = NULL;
    int cmp_func_status = 0;
    
    if (NULL == node)
    {
        return (NULL);
    }

    cmp_func_status = func(node->data, (void *)data);

    if (BALANCED == cmp_func_status)
    {
        if(NULL != node->children[RIGHT])
        {
            tmp = Next(node->children[RIGHT]);
            node->data = tmp->data;
            node->children[RIGHT] = InnerRemove(node->children[RIGHT],node->data, func);
        }

        else
        {
            tmp = node->children[LEFT];
            FreeNode(node);
            return (tmp);
        }
    }

    else if (BALANCED < cmp_func_status)
    {
        node->children[LEFT] = InnerRemove(node->children[LEFT], data, func);
    }

    else
    {
        node->children[RIGHT] = InnerRemove(node->children[RIGHT], data, func);
    }

    return (node);
}

void AVLRemove(avl_t *tree, const void *data)
{
    assert(tree);
    assert(tree->func);

    tree->root = InnerRemove(tree->root, (void *)data, tree->func);

    return;
}

static avl_node_t *Next(avl_node_t *node)
{
    if (node->children[LEFT] == NULL)
    {
        return node;
    }

    return (Next(node->children[LEFT]));
}

static void FreeNode(avl_node_t *node)
{
    assert(NULL != node);

    node->children[LEFT] = NULL;
    node->children[RIGHT] = NULL;    
    node->data = NULL;
    free(node);

    return;
}
