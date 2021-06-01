/*
 * Developer: Eden Samama
 * Status: in development
 * Date: 31.5.21
 * Version: 1
 * Group: OL102
 * Description: binary search tree
 */

#include <stdlib.h> /* malloc */
#include <assert.h>

#include "bst.h"

#define UNUSED(X) (void)(X)

struct bst
{
    struct bst_node *dummy;
    cmp_func_t cmp_func;
    void *param;
};

typedef struct bst_node
{
    void *data;
    struct bst_node *left;
    struct bst_node *right;
    struct bst_node *parent;
}bst_node_t;

static int AddOne(void *x, void *y)
{
	UNUSED(x);
	
	*(size_t *)y += 1;
	
	return 0;
}

bst_t *BstCreate(cmp_func_t func, void *param)
{
    bst_t *tree = NULL;
    
    assert(NULL != func);

    tree = (bst_t *)malloc(sizeof(bst_t));

    if (NULL == tree)
    {
        return (NULL);
    }

    tree->dummy = (bst_iter_t)malloc(sizeof(bst_node_t));

    if (NULL == tree->dummy)
    {
        free(tree);

        return (NULL);
    }

    (tree->dummy)->data = NULL;
    (tree->dummy)->left = NULL;
    (tree->dummy)->right = NULL;
    (tree->dummy)->parent = NULL;

    tree->cmp_func = func;
    tree->param = param;

    return (tree);
}

void BstDestroy(bst_t *tree)
{
    bst_iter_t iter = NULL;
    bst_iter_t iter_next = NULL;

    assert(NULL != tree);

    iter = BstBegin(tree);

    while (!BstIsEmpty(tree))
    {
        iter_next = BstNext(iter);
    
        BstRemove(iter);

        iter = iter_next;
    }
    
    free(tree->dummy);
    
    tree->dummy = NULL;
    tree->cmp_func = NULL;
    
    free(tree);

    return;
}

size_t BstSize(const bst_t *tree)
{
    size_t size = 0;

    assert(NULL != tree);
  
    BstForEach(BstBegin((bst_t *)tree), BstEnd((bst_t *)tree), AddOne, (void *)&size);
  
    return (size);
}

int BstIsEmpty(const bst_t *tree)
{
    assert(NULL != tree);

    return (NULL == (tree->dummy)->left);
}

bst_iter_t BstInsert(bst_t *tree, void *data)
{
    bst_iter_t iter = NULL;
    bst_iter_t iter_next = NULL;
    bst_iter_t new_iter = NULL;

    assert(NULL != tree);

    iter = BstEnd(tree);
    iter_next = (BstEnd(tree))->left;
    new_iter = (bst_iter_t)malloc(sizeof(bst_node_t));

    if (NULL == new_iter)
    {
        return (NULL);
    }

    new_iter->data = data;
    new_iter->left = NULL;
    new_iter->right = NULL;

    while (NULL != iter_next)
    {
        iter = iter_next;

        if (0 < tree->cmp_func(BstGetData(iter), data, tree->param))
        {
            iter_next = iter->left;
        }

        else
        {
            iter_next = iter->right;
        }
    }
    
    if (NULL == iter->parent || 0 < tree->cmp_func(BstGetData(iter), data, tree->param))
    {
        iter->left = new_iter;
    }

    else
    {
        iter->right = new_iter;
    }

    new_iter->parent = iter;
 
    return (new_iter);
}

void BstRemove(bst_iter_t iter)
{
    bst_iter_t to_remove = NULL;

    assert(NULL != iter);
    assert(NULL != iter->parent);

    if (NULL == iter->left && NULL == iter->right)
    {
        if (iter == (iter->parent)->left)
        {
            (iter->parent)->left = NULL;
        }

        else
        {
            (iter->parent)->right = NULL;
        }

        to_remove = iter;
    }

    else if (NULL == iter->left || NULL == iter->right)
    {
        if (NULL == iter->left)
        {
            if (iter == (iter->parent)->left)
            {
                (iter->parent)->left = iter->right;
            }

            else
            {
                (iter->parent)->right = iter->right;
            }

            (iter->right)->parent = iter->parent;
        }

        else
        {
            if (iter == (iter->parent)->left)
            {
                (iter->parent)->left = iter->left;
            }

            else
            {
                (iter->parent)->right = iter->left;
            }

            (iter->left)->parent = iter->parent;
        }

        to_remove = iter;
    }

    else
    {
        to_remove = iter->right;

        while (NULL != to_remove->left)
        {
            to_remove = to_remove->left;
        }

        (to_remove->parent)->left = to_remove->right;

        iter->data = BstGetData(to_remove);
    }

    to_remove->left = NULL;
    to_remove->right = NULL;
    to_remove->parent = NULL;

    free(to_remove);

    return;
}

bst_iter_t BstBegin(bst_t *tree)
{
    bst_iter_t begin = NULL;

    assert(NULL != tree);

    begin = tree->dummy;

    while (NULL != begin->left)
    {
        begin = begin->left;
    }

    return (begin);
}

bst_iter_t BstEnd(bst_t *tree)
{
    assert(NULL != tree);

    return (tree->dummy);
}

bst_iter_t BstPrev(bst_iter_t iter)
{
    assert(NULL != iter);

    if (NULL == iter->left)
    {
        while (NULL != iter->parent && iter == (iter->parent)->left)
       {
           iter = iter->parent;
       }
       
       return iter->parent;
    }

    iter = iter->left;

    while (NULL != iter->right)
    {
        iter = iter->right;
    }
    
    return (iter);
}

bst_iter_t BstNext(bst_iter_t iter)
{
    assert(NULL != iter);

    if (NULL == iter->right)
    {
       while (NULL != iter->parent && iter == (iter->parent)->right)
       {
           iter = iter->parent;
       }
       
       return iter->parent;
    }

    iter = iter->right;

    while (NULL != iter->left)
    {
        iter = iter->left;
    }
    
    return (iter);
}

int BstIterIsEqual(const bst_iter_t iter1, const bst_iter_t iter2)
{
    assert(NULL != iter1);
    assert(NULL != iter2);

    return (iter1 == iter2);
}

void *BstGetData(bst_iter_t iter)
{
    assert(NULL != iter);

    return (iter->data);
}

bst_iter_t BstFind(bst_t *tree, void *data)
{
    bst_iter_t iter = NULL;

    assert(NULL != tree);

    iter = BstBegin(tree);

    while (!BstIterIsEqual(iter, tree->dummy) && (0 != tree->cmp_func(BstGetData(iter), data, tree->param)))
    {
        iter = BstNext(iter);
    }
    
    return (iter);
}

int BstForEach(bst_iter_t from, bst_iter_t to, act_func_t func, void *param)
{
    int status = 0;

    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != func);

    while (!BstIterIsEqual(from, to))
    {
        status = func(BstGetData(from), param);
    
        if (0 != status)
		{
			return status;
		}
  
		from = BstNext(from);
    }
  
    return (status);
}






