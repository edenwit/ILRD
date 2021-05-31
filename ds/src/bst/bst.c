#include <stddef.h> /* size_t */
#include <assert.h>
#include <stdlib.h>  /* malloc */

#include "bst.h"

#define UNUSED(X) ((void) X)

static int Add1(void * data, void *param);
static bst_iter_t *GenericFind(bst_t *tree, void *data);

typedef struct bst_node
{
    void *data;
    struct bst_node *left;
    struct bst_node *right;
    struct bst_node *parent;

} bst_node_t;

struct bst
{
    bst_node_t dummy;
    int (*cmp_func)(void *data1, void *data2, void *param);
    void *param;
};


/* O(1) */
bst_t *BstCreate(cmp_func_ptr_t cmp_func, void *param)
{
    bst_t *bst = NULL;

    assert(param);
    assert(cmp_func);

    bst = (bst_t *)malloc(sizeof(bst_t));

    if (NULL == bst)
    {
        return (NULL);
    }

    bst->cmp_func = cmp_func;
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
		
	BstForEach(BstBegin((bst_t *)tree), BstEnd((bst_t *)tree), Add1, (void *)&counter);
	
	return (counter);
}

/* O(1) */
int BstIsEmpty(const bst_t *tree)
{
 	assert(tree);	

    return (NULL == tree->dummy.left);   
}

/* Avg - O(log n), worst - O(n) */
bst_iter_t BstInsert(bst_t *tree, void *data)
{
    bst_iter_t iter = NULL;
	bst_iter_t node = NULL;
	
	assert(tree);
	
	node = (bst_iter_t)malloc(sizeof(bst_node_t));
	
	if (NULL == node)
	{
	    return (BstEnd(tree)); 
	}
	
	node->data = data;
    node->left = NULL;
    node->right = NULL;
	
    iter = GenericFind(tree, data);

    if (NULL == iter)
    {
        tree->dummy->left = node;
    }
    
    if (0 > tree->cmp_func(BstGetData(iter), data, NULL))
    {
    	iter.left = node;
    }
    else
    {
    	iter.right = node;
    }
    
    node->parent = iter;
    
    return (*((bst_iter_t)(&(tree->dummy))));
	
}

/* Avg - O(log n), worst - O(n) */
void BstRemove(bst_iter_t iter)
{
	bst_iter_t next_iter = NULL;
	
	assert(iter);

	int is_left_child = IsLeftChild(iter);
	
	if (NULL == iter->left)
	{
		if (NULL == iter->right)
		{
			if (is_left_child)
			{
				iter->parent->left = NULL;
			}
			else
			{
				iter->parent->right = NULL;			
			}
		}
		else
		{
			if (is_left_child)
			{
				iter->parent->left = iter->right;
			}
			else
			{
				iter->parent->right = iter->right;
			}	
			
			iter->right->parent = iter;
		}
	}
	else if (NULL == iter->right)
	{
		if (is_left_child)
		{
			iter->parent->left = iter->left;
		}
		else
		{
			iter->parent->right = iter->left;
		}	
			
		iter->left->parent = iter;		
	}
	else
	{
		next_iter = BstNext(iter);
		
		if (is_left_child)
		{
			iter->parent->left = iter->right;
		}
		else
		{
			iter->parent->right = iter->right;
		}	
		
		next_iter->left = iter-left;
	}
	
	iter->left = NULL;
	iter->right = NULL;
	iter->parent = NULL;
	iter->data = NULL;
	
	free(iter);
	
	
	
}

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

    return(*((bst_iter_t)&tree->dummy));
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

    while (NULL != iter->right)
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

    while (NULL != iter->left)
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

    iter = GenericFind(tree, data);

	if (NULL == iter)
	{
		return (BstEnd(tree));
	}
	
	if (0 == tree->cmp_func(BstGetData(iter), data))
	{
		return (iter);
	}
	
	return (BstEnd(tree));
}

/* O(n log n) */
int BstForEach(bst_iter_t from, bst_iter_t to, act_tunc_ptr_t t, void *param)
{
    int status = 0;

    assert(from);
    assert(to);
    assert(t);

     while (!BstIterIsEqual(from, to) && !status)
     {
         status = t(BstGetData(from), param);
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

static bst_iter_t GenericFind(bst_t *tree, void *data)
{
    bst_iter_t iter = tree->dummy.left;
    bst_iter_t parent_iter = tree->dummy;
       
    int cmp_res = 1;

    assert(tree);
    assert(data);


	while ((NULL != iter) && (!cmp_res))
	{
	    cmp_res = tree->cmp_func(BstGetData(iter), data, NULL);

        parent_iter = iter;

        if (0 > cmp_res)
        {   
            iter = iter->left;
        }
        else if (0 < cmp_res)
        {
            iter = iter->right;
        }
	}

    return (0 == cmp_res ? iter : parent_iter);
}

static IsLeftChild(bst_iter_t iter)
{
	assert(iter);
	
	return (iter->parent->left == iter);
}
