#include <stdlib.h> /* malloc */
#include <assert.h>
#include "bst.h"
/*------------- impl elems ------------*/

struct bst_node
{
    void *data;
    struct bst_node *left;
    struct bst_node *right;
    struct bst_node *parent;
};

struct bst
{
    cmp_func_t func;
    void *param;
    struct bst_node dummy;
};

typedef enum left_right
{
    ME = 0,
    LEFT,
    RIGHT = 2,
    NONE,
    TWOCHILED,
    UNSET = -1
} side_indicator_t;

/*------------- helper funcs ------------*/

static int CountIters(void *unuesed, void *param);
static side_indicator_t SideOfMyChild(bst_iter_t iter);
static side_indicator_t MySideAsAChild(bst_iter_t iter);
static bst_iter_t BstFindParentNode(bst_t *tree, void *data, side_indicator_t *side);
static void GrandfatherAndRightChildConection(bst_iter_t iter, side_indicator_t side);
static void GrandfatherAndLefttChildConection(bst_iter_t iter, side_indicator_t side);
static void NodeConection(bst_iter_t to_iter, bst_iter_t from_iter, side_indicator_t side);
/*------------------------------ implementetion --------------------------------*/

bst_t *BstCreate(cmp_func_t func, void *param)
{
    bst_t *bst = NULL;

    assert(func);

    bst = (bst_t *)malloc(sizeof(struct bst));

    if (NULL == bst)
    {
        return (NULL);
    }

    bst->param = param;
    bst->func = func;
    bst->dummy.data = param;
    bst->dummy.left = NULL;
    bst->dummy.right = NULL;
    bst->dummy.parent = NULL;

    return (bst);
}

void BstDestroy(bst_t *tree)
{
    assert(tree);

    while (!BstIsEmpty(tree))
    {
        BstRemove(BstBegin(tree));
    }

    tree->func = NULL;
    tree->param = NULL;

    free(tree);

    return;
}

int BstIsEmpty(const bst_t *tree)
{
    assert(tree);

    return (NULL == tree->dummy.left);
}

size_t BstSize(const bst_t *tree)
{
    size_t counter = 0;

    assert(NULL != tree);

    BstForEach(BstBegin((bst_t *)tree), BstEnd((bst_t *)tree), CountIters, (void *)&counter);

    return (counter);
}

bst_iter_t BstBegin(bst_t *tree)
{
    bst_iter_t cur_iter = NULL;

    assert(tree);

    cur_iter = (bst_iter_t) & (tree->dummy);

    while (NULL != cur_iter->left)
    {
        cur_iter = cur_iter->left;
    }

    return (cur_iter);
}

bst_iter_t BstEnd(bst_t *tree)
{
    assert(tree);

    return ((bst_iter_t) & (tree->dummy));
}

bst_iter_t BstNext(bst_iter_t iter)
{
    assert(iter);

    if (NULL == iter->right)
    {
        while (iter->parent->left != iter)
        {
            iter = iter->parent;
        }

        return (iter->parent);
    }

    iter = iter->right;

    while (NULL != iter->left)
    {
        iter = iter->left;
    }

    return (iter);
}

bst_iter_t BstPrev(bst_iter_t iter)
{
    assert(iter);

    if (NULL == iter->left)
    {
        while (NULL != iter->parent && iter->parent->right != iter)
        {
            iter = iter->parent;
        }

        return (iter->parent);
    }

    iter = iter->left;

    while (NULL != iter->right)
    {
        iter = iter->right;
    }

    return (iter);
}

int BstIterIsEqual(const bst_iter_t iter1, const bst_iter_t iter2)
{

    assert(iter1);
    assert(iter2);

    return (iter1 == iter2);
}

bst_iter_t BstFind(bst_t *tree, void *data)
{
    side_indicator_t side = UNSET;
    bst_iter_t iter = NULL;

    assert(tree);
    assert(tree->func);

    iter = BstFindParentNode(tree, data, &side);

    return (iter);
}

void *BstGetData(bst_iter_t iter)
{
    assert(iter);

    return (iter->data);
}

int BstForEach(bst_iter_t from, bst_iter_t to, act_func_t func, void *param)
{
    int res = 0;

    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != func);

    while (!BstIterIsEqual(from, to) && !res)
    {
        res = func(BstGetData(from), param);
        from = BstNext(from);
    }

    return (res);
}

bst_iter_t BstInsert(bst_t *tree, void *data)
{
    bst_iter_t insert_iter = NULL;
    bst_iter_t where = NULL;
    side_indicator_t side = UNSET;

    assert(tree);
    assert(tree->func);

    insert_iter = (bst_iter_t)malloc(sizeof(struct bst_node));

    if (NULL == insert_iter)
    {
        return (BstEnd(tree));
    }

    insert_iter->data = data;
    insert_iter->left = NULL;
    insert_iter->right = NULL;

    where = BstFindParentNode(tree, data, &side);

    insert_iter->parent = where;

    NodeConection(where, insert_iter, side);

    return (insert_iter);
}

void BstRemove(bst_iter_t iter)
{
    bst_iter_t cur_iter = NULL;
    side_indicator_t iter_side_at_parent = UNSET;
    side_indicator_t iter_side_of_child = UNSET;

    assert(iter);

    iter_side_of_child = SideOfMyChild(iter);
    iter_side_at_parent = MySideAsAChild(iter);

    if (NONE == iter_side_of_child)
    {
        NodeConection(iter->parent, NULL, iter_side_at_parent);
    }
    else if (TWOCHILED == iter_side_of_child)
    {
        cur_iter = BstNext(iter);

        cur_iter->left = iter->left;

        iter->left->parent = cur_iter;

        iter->right->parent = iter->parent;
        GrandfatherAndRightChildConection(iter, iter_side_at_parent);
    }
    else if ((NULL == iter->left))
    {
        iter->right->parent = iter->parent;
        GrandfatherAndRightChildConection(iter, iter_side_at_parent);
    }
    else
    {
        iter->left->parent = iter->parent;
        GrandfatherAndLefttChildConection(iter, iter_side_at_parent);
    }

    iter->data = NULL;
    iter->left = NULL;
    iter->right = NULL;
    iter->parent = NULL;

    free(iter);
    iter = NULL;

    return;
}

/*------------------------------helper_function---------------------------------*/

static int CountIters(void *unuesed, void *param)
{
    (void)unuesed;

    *(size_t *)param = *(size_t *)param + 1;

    return EXIT_SUCCESS;
}

static side_indicator_t MySideAsAChild(bst_iter_t iter)
{
    assert(iter);

    if ((NULL != iter->parent))
    {
        if ((iter == iter->parent->right))
        {
            return RIGHT;
        }
        else if ((iter == iter->parent->left))
        {
            return LEFT;
        }
    }
    return NONE;
}

static side_indicator_t SideOfMyChild(bst_iter_t iter)
{
    assert(iter);

    if ((NULL != iter->left) && (NULL == iter->right))
    {
        return LEFT;
    }
    else if ((NULL != iter->right) && (NULL == iter->left))
    {
        return RIGHT;
    }
    else if ((NULL == iter->right) && (NULL == iter->left))
    {
        return NONE;
    }
    else if ((NULL != iter->right) && (NULL != iter->left))
    {
        return TWOCHILED;
    }

    return UNSET;
}

static void GrandfatherAndRightChildConection(bst_iter_t iter, side_indicator_t side)
{
    NodeConection(iter->parent, iter->right, side);
    return;
}

static void GrandfatherAndLefttChildConection(bst_iter_t iter, side_indicator_t side)
{
    NodeConection(iter->parent, iter->left, side);
    return;
}
static void NodeConection(bst_iter_t to_iter, bst_iter_t from_iter, side_indicator_t side)
{
    if (RIGHT == side)
    {
        to_iter->right = from_iter;
    }
    else
    {
        to_iter->left = from_iter;
    }

    return;
}
static bst_iter_t BstFindParentNode(bst_t *tree, void *data, side_indicator_t *side)
{
    bst_iter_t cur_iter = NULL;
    bst_iter_t cur_parent = NULL;

    int res = 1;
    *side = LEFT;

    assert(tree);
    assert(tree->func);

    cur_parent = (bst_iter_t) & (tree->dummy);
    cur_iter = ((bst_iter_t) & (tree->dummy))->left;

    while (NULL != cur_iter)
    {
        cur_parent = cur_iter;
        res = tree->func(BstGetData(cur_iter), data, tree->param);

        if (0 > res)
        {
            *side = RIGHT;
            cur_iter = cur_iter->right;
        }
        else if (0 < res)
        {
            *side = LEFT;
            cur_iter = cur_iter->left;
        }
        if (0 == res)
        {
            break;
        }
    }

    return (cur_parent);
}
