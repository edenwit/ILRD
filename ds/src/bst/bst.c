#include <stddef.h> /* size_t */
#include "bst.h"

/*
typedef struct bst bst_t;
typedef struct bst_node *bst_iter_t; 

typedef int (*cmp_func_ptr_t)(void *, void *, void *);
typedef int (*act_tunc_ptr_t)(void *, void *);
*/
static int Add1(void * data, void *param);


typedef struct bst
{
    struct bst_node dummy;
    int (*cmp_func)(const void *data1, const void *data2);
    void *param;
};

typedef struct bst_node
{
    void *data;
    struct bst_node *left;
    struct bst_node *right;
    struct bst_node *parent;

} bst_node_t;

/* O(1) */
bst_t *BstCreate(cmp_func_ptr_t, void *param)
{
    bst_t *bst = NULL;

    assert(param);

    bst = (bst_t *)malloc(sizeof(bst_t));

    if (NULL == bst)
    {
        return (NULL);
    }

    bst->cmp_func = cmp_func_ptr_t;
    bst->param = param;

    bst->dummy.right = NULL;
    bst->dummy.left = NULL;
    bst->dummy.parent = NULL;
    bst->dummy.data = NULL;

    return (bst);
}

/* O(n) - n numbert of nodes in tree */
void BstDestroy(bst_t *tree);

/* O(n log n) - n numbert of nodes in tree  ? */
size_t BstSize(const bst_t *tree)
{
	size_t counter = 0;

	assert(tree);	
		
	SLLForEach(BstBegin(tree), BstEnd(tree), Add1, (void *)&counter);
	
	return (counter);
}

/* O(1) */
int BstIsEmpty(const bst_t *tree)
{
 	assert(tree);	

    return (NULL == tree->dummy.left);   
}

/* Avg - O(log n), worst - O(n) */
bst_iter_t BstInsert(bst_t *tree, void *data);

/* Avg - O(log n), worst - O(n) */
void BstRemove(bst_iter_t iter);

/* O(1) */
bst_iter_t BstBegin(bst_t *tree)
{
    bst_iter_t iter = NULL;

    assert(tree); 

    iter = tree->dummy.left;

    while (NULL != iter->left)
    {
        iter = iter->left;
    }

    return (iter);
}

/* Avg - O(log n), worst - O(n) */
bst_iter_t BstEnd(bst_t *tree)
{
    assert(tree);

    return(tree->dummy);
}

/* Avg - O(log n), worst - O(n) */
bst_iter_t BstPrev(bst_iter_t iter)
{
    assert(iter);

    if (NULL != iter->left)
    {
        while (iter != iter->parent->right)
        {
            iter = iter->parent;
        }

        return (iter->parent);
    }
    
    iter = iter->left;

    while (NULL != iter-right)
    {
        iter = iter->right;
    }

    return (iter);
}

/* Avg - O(log n), worst - O(n) */
bst_iter_t BstNext(bst_iter_t iter)
{
    assert(iter);

    if (NULL != iter->right)
    {
        while (iter != iter->parent->left)
        {
            iter = iter->parent;
        }

        return (iter->parent);
    }

    iter = iter->right;

    while (NULL != iter-left)
    {
        iter = iter->left;
    }

    return (iter);
}

/* O(1) */
int BstIterIsEqual(const bst_iter_t iter1, const bst_iter_t iter2)
{
    assert(iter1);
    assert(iter2);

    return (iter1 == iter2);
}

/* O(1) */
void *BstGetData(bst_iter_t iter)
{
    assert(iter);

    return (iter->data);
}

/* Avg - O(log n), worst - O(n) */
bst_iter_t BstFind(bst_t *tree, void *data)
{
    bst_iter_t iter = NULL;
    
    assert(tree);
    assert(data);

    iter = GenericFind(tree, data);

    if (BstGetData(iter))
    {

    }
    
}

/* O(n log n) */
int BstForEach(bst_iter_t from, bst_iter_t to, act_tunc_ptr_t, void *param)
{
    int status = 0;

    assert(from);
    assert(to);
    assert(act_tunc_ptr);

     while (!BstIterIsEqual(from, to) && !status)
     {
         status = act_tunc_ptr(BstGetData(from), param);
         from = BstNext(from);
     }

     return (status);
}

static int Add1(void * data, void *param)
{
	UNUSED(data);
	
	++*(size_t *)param;
		
	return (0);
}

static bst_iter_t *GenericFind(bst_t *tree, void *data)
{
    bst_iter_t iter = NULL;
    bst_iter_t parent_iter = iter;
       
    int cmp_res = 0;

    assert(tree);
    assert(data);

    iter = tree->dummy.left;
    cmp_res = tree->cmp_func(BstGetData(iter), data);

	while ((NULL != iter) && (!cmp_res))
	{
        parent_iter = iter;

        if (0 > cmp_res)
        {   
            iter = iter->left;
        }
        else
        {
            iter = iter->right;
        }

        cmp_res = tree->cmp_func(BstGetData(iter), data);
	}

    if (0 == cmp_res)
    {
        return (iter);
    }

	return (parent_iter);
}