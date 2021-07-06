/*  Developer: Eden Wittenberg;									*
 *  Status: done;												*
 *  Date Of Creation: 14.06.21;									*
 *  Date Of Approval: 23.06.21;									*
 *  Review By: Avital Moses;									*
 *  Description: AVL tree;			                    		*/

#include <assert.h> /* assert */
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
    int height;
};

struct avl
{
    cmp_func_t func;
    avl_node_t *root;
};

typedef int (*travese_func)(avl_node_t *node, act_func_t func, void *param);

static int RecForEach(avl_node_t *node, act_func_t func,
                        void *param, order_t order);
static int ForEachPreOrder(avl_node_t *node, act_func_t func, void *param);
static int ForEachInOrder(avl_node_t *node, act_func_t func, void *param);
static int ForEachPostOrder(avl_node_t *node, act_func_t func, void *param);

static void *RecFind(avl_node_t *node, cmp_func_t func, const void *data);
static avl_node_t *RecInsert(avl_node_t *root,
                               avl_node_t *node, cmp_func_t cmp_func);


static void RecDestroy(avl_node_t *node);
static avl_node_t *RecRemove(avl_node_t *node, void *data, cmp_func_t func);

static int IncreaseByOne(void *data, void *param);
static int FreeNode(void *node);
static void *NextData(avl_node_t *node);

static void UpdateHeight(avl_node_t *node);
static int GetBalanceDiff(avl_node_t *node);

static avl_node_t *LeftRotation(avl_node_t *node);
static avl_node_t *RightRotation(avl_node_t *node);
static avl_node_t *BalanceTree(avl_node_t *node);


avl_t *AVLCreate(cmp_func_t func)
{
    avl_t *tree = NULL;
    
    assert(func);

    tree = (avl_t *)malloc(sizeof(avl_t));

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

    RecDestroy(tree->root);

    free(tree);

    return;
}

size_t AVLSize(const avl_t *tree)
{
    size_t counter = 0;

    assert(tree);

    if (!AVLIsEmpty(tree))
    {
        AVLForEach((avl_t *)tree, IncreaseByOne, &counter, PRE_ORDER);
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
    assert(tree);

    if (AVLIsEmpty(tree))
    {
        return (0);
    }

    return (tree->root->height);
}

int AVLInsert(avl_t *tree, void *data)
{
    avl_node_t *node = NULL;

    assert(tree);
    assert(tree->func);

    node = (avl_node_t *)malloc(sizeof(avl_node_t));

    if (NULL == node)
    {
        return (1);
    }

    node->data = data;
    node->children[LEFT] = NULL;
    node->children[RIGHT] = NULL;
    node->height = 0;

    if (AVLIsEmpty(tree))
    {
        tree->root = node;

        return (0);
    }

    tree->root = RecInsert(tree->root, node, tree->func);

    return (0);
}

void AVLRemove(avl_t *tree, const void *data)
{
    assert(tree);
    assert(tree->func);

    tree->root = RecRemove(tree->root, (void *)data, tree->func);
}


void *AVLFind(const avl_t *tree, const void *data)
{
    assert(tree);

    return (RecFind(tree->root, tree->func, data));
}

int AVLForEach(avl_t *tree, act_func_t func, void *param, order_t order)
{
    assert(tree);
    assert(func);

    return (RecForEach(tree->root, func, param, order));
}

/* ---------------------- Rec Functions ---------------------------------- */

static avl_node_t *RecRemove(avl_node_t *node, void *data, cmp_func_t func)
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
        /* if current node has a right child - assign node with the next data 
        and remove that next using recursion */
        if (node->children[RIGHT])
        {
            node->data = NextData(node->children[RIGHT]);
            node->children[RIGHT] 
            = RecRemove(node->children[RIGHT], node->data, func);
        }
        /* if current node does not have a right child - keep my left child as tmp,
         remove me and return my left child */
        else
        {
            tmp_node = node->children[LEFT];

            FreeNode(node);

            return (tmp_node);
        }
    }

    else if (0 > cmp_res)
    {
        node->children[RIGHT] = RecRemove(node->children[RIGHT], data, func);
    }
    
    else
    {
        node->children[LEFT] = RecRemove(node->children[LEFT], data, func);
    }

    UpdateHeight(node);

    node = BalanceTree(node);

    return (node); 
}

static avl_node_t *RecInsert(avl_node_t *root, avl_node_t *node,
                               cmp_func_t cmp_func)
{
    if (NULL == root)
    {
        return (node);
    }

    if (0 > cmp_func(root->data, node->data))
    {
        root->children[RIGHT] = RecInsert(root->children[RIGHT], node, cmp_func);
    }
    
    else
    {
        root->children[LEFT] = RecInsert(root->children[LEFT], node, cmp_func);
    }
    
    UpdateHeight(root);

    root = BalanceTree(root);

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

static int RecForEach(avl_node_t *node, act_func_t func,
                        void *param, order_t order)
{

    static travese_func func_arr[] = 
                        {ForEachPreOrder, ForEachInOrder, ForEachPostOrder};

    assert(node);
    assert(func);

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

static void *RecFind(avl_node_t *node, cmp_func_t func, const void *data)
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
        return (RecFind(node->children[RIGHT], func, data));
    }
    
    return (RecFind(node->children[LEFT], func, data));
}

static void RecDestroy(avl_node_t *node)
{
    if (NULL == node)
    {
        return;
    }

    RecDestroy(node->children[LEFT]);

    RecDestroy(node->children[RIGHT]);

    FreeNode(node);

    return;
}

static int IncreaseByOne(void *data, void *param)
{
    UNUSED(data);

    ++(*(size_t *)param);

    return (0);
}

static int FreeNode(void *node)
{
    assert(node);

    ((avl_node_t *)node)->children[LEFT] = NULL;
    ((avl_node_t *)node)->children[RIGHT] = NULL;

    free(node);

    return (0);
}

static void UpdateHeight(avl_node_t *node)
{
    assert(node);

    if (NULL == node->children[LEFT] && NULL == node->children[RIGHT])
    {
        node->height = 0;
    }

    else if (NULL != node->children[LEFT] && NULL != node->children[RIGHT])
    {
        node->height = MAX2(node->children[LEFT]->height, node->children[RIGHT]->height) + 1;
    }

    else if (NULL != node->children[LEFT])
    {
        node->height = node->children[LEFT]->height + 1;
    }

    else
    {
        node->height = node->children[RIGHT]->height + 1;
    }

    return;
}

static avl_node_t *LeftRotation(avl_node_t *node)
{
    avl_node_t *right_child = node->children[RIGHT];
    avl_node_t *temp = right_child->children[LEFT];

    right_child->children[LEFT] = node;
    node->children[RIGHT] = temp;

    UpdateHeight(node);
    UpdateHeight(right_child);

    return(right_child);
}

static avl_node_t *RightRotation(avl_node_t *node)
{
    avl_node_t *left_child = node->children[LEFT];
    avl_node_t *temp = left_child->children[RIGHT];

    left_child->children[RIGHT] = node;
    node->children[LEFT] = temp;

    UpdateHeight(node);
    UpdateHeight(left_child);

    return(left_child);
}

static int GetBalanceDiff(avl_node_t *node)
{
    size_t left_child_height = 0;
    size_t right_child_height = 0;

    assert(node);

    if (NULL != node->children[RIGHT])
    {
        right_child_height = node->children[RIGHT]->height + 1;
    }
    if (NULL != node->children[LEFT])
    {
        left_child_height = node->children[LEFT]->height + 1;
    }

    return (right_child_height - left_child_height);
}

static avl_node_t *BalanceTree(avl_node_t *node)
{
    int balance_diff = 0;
    int balance_diff_child = 0;

    assert(node);

    balance_diff = GetBalanceDiff(node);

    if (1 < balance_diff)
    {
        balance_diff_child = GetBalanceDiff(node->children[RIGHT]);
        
        if (0 > balance_diff_child)
        {
            node->children[RIGHT] = RightRotation(node->children[RIGHT]);      
        }

        node = LeftRotation(node);
    }

    else if (-1 > balance_diff)
    {
        balance_diff_child = GetBalanceDiff(node->children[LEFT]);
        
        if (0 < balance_diff_child)
        {
            node->children[LEFT] = LeftRotation(node->children[LEFT]);      
        }

        node = RightRotation(node);
    }

    return(node);
}
