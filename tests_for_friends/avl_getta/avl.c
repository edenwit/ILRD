#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#define UNUSED(X) (void)(X)
#include "avl.h"     /* size_t */

typedef enum children
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
}children_t;

typedef struct avl_node avl_node_t; 

struct avl_node
{
    void *data;
    struct avl_node *children[NUM_OF_CHILDREN];
    int balance_factor;
};

struct avl
{
    cmp_func_t func;
    struct avl_node *root;
};

avl_t *AVLCreate(cmp_func_t func)
{
    avl_t *new_avl = NULL;

    assert(func);

    new_avl = (avl_t*)malloc(sizeof(avl_t));
    
    if(!new_avl)
    {
        return NULL;
    }

    new_avl->func = func;
    new_avl->root = NULL;

    return new_avl;
}

static void *AVLNodeFind(avl_node_t *node, const void *data, cmp_func_t func)
{
    if (node == NULL)
    {
        return NULL;
    }

    if(!func(node->data,(void*) data))
    {
        return node->data;
    }

    if(func(node->data,(void*) data) > 0)
    {
        return AVLNodeFind(node->children[LEFT],  data, func);
    }

    else
    {
        return AVLNodeFind(node->children[RIGHT], data, func);
    }

}

void *AVLFind(const avl_t *tree, const void *data)
{
   return AVLNodeFind(tree->root, data, tree->func);
}

int AVLIsEmpty(const avl_t *tree)
{
    return !(tree->root);
}


static int PreOrderTraverse(avl_node_t *node, act_func_t func, void *param)
{
    int status = 0;

    if (node == NULL)
    {
        return status;
    }

    status = func(node->data, param);

    if(status)
    {
        return status;
    }

    status = PreOrderTraverse(node->children[LEFT], func, param);
    status = PreOrderTraverse(node->children[RIGHT],func, param);

    return status;
}

static int InOrderTraverse(avl_node_t *node, act_func_t func, void *param)
{
    int status = 0;

    if (node == NULL)
    {
        return status;
    }
   
    status = InOrderTraverse(node->children[LEFT], func, param);

    status = func(node->data, param);

    if(status)
    {
        return status;
    }

    return InOrderTraverse(node->children[RIGHT], func, param);
}

static int PostOrderTraverse(avl_node_t *node, act_func_t func, void *param)
{
    int status = 0;

    if (node == NULL)
    {
        return status;
    }
   
    status = PostOrderTraverse(node->children[LEFT], func, param);

    if(status)
    {
        return status;
    }   

    status = PostOrderTraverse(node->children[RIGHT], func, param);    

    if(status)
    {
        return status;
    }    

    return func(node->data, param);

}

int AVLForEach(avl_t *tree, act_func_t func, void *param, order_t order)
{
    int status = 0;

    switch (order)
    {
        case PRE_ORDER:
        {
           status = PreOrderTraverse(tree->root ,func, param);    
           break;
        }

        case IN_ORDER:
        {
           status = InOrderTraverse(tree->root ,func, param);    
           break;
        }

        case POST_ORDER:
        {
           status = PostOrderTraverse(tree->root ,func, param);              
           break;  
        }

    }
    return status;
}
    

avl_node_t **AVLFindInsertLocation(avl_node_t *walker, cmp_func_t func, void *data)
{
    avl_node_t **place = NULL;

    if (0 < func(walker->data, data)) 
    {
        if(!walker->children[LEFT])
        {
            place = (&walker->children[LEFT]);
            return place;
        }
        
        place = AVLFindInsertLocation(walker->children[LEFT],func,data);
    }

    else if (0 > func(walker->data, data)) 
    {
        if(!walker->children[RIGHT])
        {
            place = (&walker->children[RIGHT]);
            return place;

        }
        
        place = AVLFindInsertLocation(walker->children[RIGHT],func,data);
    }
    
    return place;
}    

int AVLInsert(avl_t *tree, void *data)
{
    avl_node_t *new_node = NULL;
    avl_node_t **where_to = NULL;

    assert(tree);
    
    new_node = (avl_node_t*)malloc(sizeof(avl_node_t));

    if(!new_node)
    {
        return 1;
    }

    new_node->children[RIGHT] = NULL;
    new_node->children [LEFT] = NULL;
    new_node->data = data;

    if(!AVLIsEmpty(tree))
    {
        where_to = AVLFindInsertLocation(tree->root, tree->func, data);
        *where_to = new_node;
    }

    else
    {
        tree->root = new_node;
    }

    return 0;
}

int AddCount(void* unused, void* count)
{
    (++*(size_t*)count);
    UNUSED(unused);
    return 0;
}


size_t AVLSize(const avl_t *tree)
{
    size_t size = 0;

    assert(tree);

    AVLForEach((avl_t*) tree, AddCount, (void *)&size, POST_ORDER);

    return (size);
}


static size_t NodeHeight(avl_node_t *node)
{
    if (!node)
    {
        return 0;
    }

    return (NodeHeight(node->children[RIGHT])   >   NodeHeight(node->children[LEFT]) ?
            NodeHeight(node->children[RIGHT]) + 1 : NodeHeight(node->children[LEFT]) + 1);
}

size_t AVLHeight(const avl_t *tree)
{
    return NodeHeight(tree->root);
}

static avl_node_t *RetrieveLeftmost(avl_node_t *node)
{
    if(!(node->children[LEFT]))
    {
        return node;
    }

    return RetrieveLeftmost(node->children[LEFT]);
}

static void DestroyNode(avl_node_t *dustpan)
{
    ((avl_node_t*)dustpan)->children[LEFT] = NULL;
    ((avl_node_t*)dustpan)->children[RIGHT] = NULL;    
    ((avl_node_t*)dustpan)->data = NULL;
    free((avl_node_t*)dustpan);

    return;
}

static avl_node_t *AVLNodeRemove(avl_node_t *node, const void *data, cmp_func_t func)
{
    avl_node_t *tmp = NULL;

    if(!node)
    {
        return node;
    }    

    if(!func(node->data, (void*)data))
    {
        if(node->children[RIGHT])
        {
            tmp = RetrieveLeftmost(node->children[RIGHT]);
            node->data = tmp->data;
            node->children[RIGHT] = AVLNodeRemove(node->children[RIGHT],node->data, func);
        }
        else
        {
            tmp = node->children[LEFT];
            DestroyNode(node);
            return tmp;
        }
    }

    else if(func(node->data, (void*)data) > 0)
    {
        node->children[LEFT] = AVLNodeRemove(node->children[LEFT], data, func);
    }

    else
    {
        node->children[RIGHT] = AVLNodeRemove(node->children[RIGHT], data, func);
    }

    return node;
}

void AVLRemove(avl_t *tree, const void *data)
{
    
    tree->root = AVLNodeRemove(tree->root, data, tree->func);

    return;
}


static void PostOrderDestroy(avl_node_t *node)
{

    if (!node)
    {
        return;
    }
   
    PostOrderDestroy(node->children[LEFT]);
    PostOrderDestroy(node->children[RIGHT]);    
    DestroyNode(node);

    return;

}
void AVLDestroy(avl_t *tree)
{
    PostOrderDestroy(tree->root);
    free(tree);

    return;
}