#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <math.h>

#include "trie.h"

#define BITS_IN_IP (32)

typedef enum nodes
{
    LEFT,
    RIGHT,
    PARENT,
    NUM_OF_NODES
} nodes_t;

typedef struct trie_node trie_node_t;

static void InnerDestroy(trie_node_t *node);

static trie_status_t GetFullPath(trie_node_t *node, unsigned long *output_ip);

static void InnerRemoveNodes(trie_node_t *node);
static int IsRightChild(trie_node_t *node);

static void UpdateToNotFull(trie_node_t *node);
static void UpdateIsFull(trie_node_t *node);

static trie_node_t *AllocatePath(trie_node_t *node, size_t bits_left, nodes_t direction);
static trie_status_t AllocateByArr(trie_node_t *node, size_t bits_left, unsigned long requested_ip, unsigned long *output_ip);

static void InitTrieNode(trie_node_t *node);
static void FreeNode(trie_node_t *node);

static size_t RecTrieSize(trie_node_t *node, size_t height);

static trie_status_t FindNext(trie_node_t *node, size_t bits_left, unsigned long *output_ip);

#define HAS_RIGHT_CHILD(X) ((X)->nodes[RIGHT])
#define HAS_LEFT_CHILD(X) ((X)->nodes[LEFT])
#define IS_RIGHT_CHILD_FULL(X) ((X)->nodes[RIGHT]->is_full)
#define IS_LEFT_CHILD_FULL(X) ((X)->nodes[LEFT]->is_full)
#define IS_FULL(X) ((X)->is_full)
#define IS_ROOT(X) (!(X)->nodes[PARENT])

struct trie
{
    trie_node_t *root;
    size_t branch_depth;
};

struct trie_node
{
    int is_full;
    struct trie_node *nodes[NUM_OF_NODES];
};

trie_t *TrieCreate(size_t bits_lefts)
{
    trie_t *trie = NULL;

    assert(0 < bits_lefts);

    trie = (trie_t *)malloc(sizeof(trie_t));

    if (NULL == trie)
    {
        return (trie);
    }

    trie->root = (trie_node_t *)malloc(sizeof(trie_node_t));

    if (NULL == trie->root)
    {
        free(trie);
        return (NULL);
    }

    InitTrieNode(trie->root);

    trie->branch_depth = bits_lefts;

    return (trie);
}

void TrieDestroy(trie_t *trie)
{
    assert(trie);

    InnerDestroy(trie->root);

    free(trie);

    return;
}

static void InnerDestroy(trie_node_t *node)
{
    if (NULL == node)
    {
        return;
    }

    InnerDestroy(node->nodes[LEFT]);
    InnerDestroy(node->nodes[RIGHT]);

    FreeNode(node);

    return;
}

static trie_status_t AllocateByArr(trie_node_t *node, size_t bits_left, unsigned long requested_ip, unsigned long *output_ip)
{
    trie_node_t *new_node = NULL;

    assert(node);
    assert(0 < bits_left);
    assert(output_ip);

    while (0 < bits_left)
    {
        new_node = (trie_node_t *)malloc(sizeof(trie_node_t));

        if (NULL == new_node)
        {
            InnerRemoveNodes(node);

            return (TRIE_MALLOC_FAILED);
        }

        InitTrieNode(new_node);
        node->nodes[(requested_ip >> (bits_left - 1)) & 1] = new_node;
        new_node->nodes[PARENT] = node;
        node = new_node;
        --bits_left;
    }

    node->is_full = 1;

    UpdateIsFull(node->nodes[PARENT]);

    return (GetFullPath(node, output_ip));
}

trie_status_t TrieInsert(trie_t *trie, unsigned long requested_ip, unsigned long *output_ip)
{
    trie_node_t *cur_node = NULL;
    size_t bits_left = 0;

    assert(trie);
    assert(output_ip);

    cur_node = (trie_node_t *)trie->root;

    bits_left = trie->branch_depth;

    while (0 < bits_left && !IS_FULL(cur_node) && cur_node->nodes[(requested_ip >> (bits_left - 1)) & 1])
    {
        cur_node = cur_node->nodes[(requested_ip >> (bits_left - 1)) & 1];
        --bits_left;
    }

    if (0 < bits_left && NULL == cur_node->nodes[(requested_ip >> (bits_left - 1)) & 1])
    {
        return (AllocateByArr(cur_node, bits_left, requested_ip, output_ip));
    }

    return (FindNext(cur_node, bits_left, output_ip));
}

static trie_status_t FindNext(trie_node_t *node, size_t bits_left, unsigned long *output_ip)
{
    while (!IS_ROOT(node) && (IsRightChild(node) || (node->nodes[PARENT]->nodes[RIGHT] && IS_FULL(node->nodes[PARENT]->nodes[RIGHT]))))
    {
        node = node->nodes[PARENT];
        ++bits_left;
    }

    if (IS_ROOT(node))
    {
        return (TRIE_FULL_FAIL);
    }

    node = node->nodes[PARENT];
    ++bits_left;

    while (HAS_RIGHT_CHILD(node))
    {
        node = node->nodes[RIGHT];
        --bits_left;

        while (HAS_LEFT_CHILD(node) && !IS_LEFT_CHILD_FULL(node))
        {
            node = node->nodes[LEFT];
            --bits_left;
        }

        if (!HAS_LEFT_CHILD(node))
        {
            node = AllocatePath(node, bits_left, LEFT);

            return (GetFullPath(node, output_ip));
        }
    }

    node = AllocatePath(node, bits_left, RIGHT);

    return (GetFullPath(node, output_ip));
}

int TrieRemove(trie_t *trie, unsigned long data_to_remove)
{
    size_t bits_left = 0;
    trie_node_t *cur_node = NULL;

    assert(trie);

    cur_node = (trie_node_t *)trie->root;
    bits_left = trie->branch_depth;

    while ((0 < bits_left) && (cur_node->nodes[(data_to_remove >> (bits_left - 1)) & 1]))
    {
        cur_node = cur_node->nodes[(data_to_remove >> ((bits_left - 1)) & 1)];
        --bits_left;
    }

    if (0 != bits_left)
    {
        return (TRIE_BRANCH_FREE);
    }

    InnerRemoveNodes(cur_node);

    return (TRIE_SUCCESS);
}

static void InnerRemoveNodes(trie_node_t *node)
{
    trie_node_t *parent = NULL;

    assert(node);

    while (!node->nodes[RIGHT] && !node->nodes[LEFT] && !IS_ROOT(node))
    {
        parent = node->nodes[PARENT];

        node->nodes[PARENT]->nodes[IsRightChild(node)] = NULL;

        FreeNode(node);

        node = parent;
    }

    UpdateToNotFull(node);

    return;
}

static void UpdateToNotFull(trie_node_t *node)
{
    while (!IS_ROOT(node) && IS_FULL(node))
    {
        node->is_full = 0;
        node = node->nodes[PARENT];
    }

    node->is_full = 0;

    return;
}

static void UpdateIsFull(trie_node_t *node)
{

    while (!IS_ROOT(node))
    {
        if (HAS_LEFT_CHILD(node) && HAS_RIGHT_CHILD(node))
        {
            node->is_full = (IS_LEFT_CHILD_FULL(node) & IS_RIGHT_CHILD_FULL(node));
        }
        else
        {
            node->is_full = 0;
        }

        node = node->nodes[PARENT];
    }

    if (HAS_LEFT_CHILD(node) && HAS_RIGHT_CHILD(node))
    {
        node->is_full = (IS_LEFT_CHILD_FULL(node) & IS_RIGHT_CHILD_FULL(node));
    }

    return;
}

static int IsRightChild(trie_node_t *node)
{
    return (node == node->nodes[PARENT]->nodes[RIGHT]);
}

static trie_node_t *AllocatePath(trie_node_t *node, size_t bits_left, nodes_t direction)
{
    trie_node_t *new_node = NULL;

    if (RIGHT == direction)
    {
        new_node = (trie_node_t *)malloc(sizeof(trie_node_t));

        if (NULL == new_node)
        {
            return (NULL);
        }

        InitTrieNode(new_node);

        node->nodes[RIGHT] = new_node;
        new_node->nodes[PARENT] = node;
        --bits_left;

        node = new_node;
    }

    while (0 < bits_left)
    {
        new_node = (trie_node_t *)malloc(sizeof(trie_node_t));

        if (NULL == new_node)
        {
            InnerRemoveNodes(node);

            return (NULL);
        }

        InitTrieNode(new_node);
        node->nodes[LEFT] = new_node;
        new_node->nodes[PARENT] = node;

        --bits_left;

        node = new_node;
    }

    node->is_full = 1;

    UpdateIsFull(node->nodes[PARENT]);

    return (node);
}

static trie_status_t GetFullPath(trie_node_t *node, unsigned long *output_ip)
{
    size_t i = 0;

    assert(node);
    assert(output_ip);

    for (i = 0; !IS_ROOT(node); ++i)
    {
        *output_ip = *output_ip | (IsRightChild(node) << i);

        node = node->nodes[PARENT];
    }

    return (TRIE_SUCCESS);
}

static void InitTrieNode(trie_node_t *node)
{
    assert(node);

    node->nodes[PARENT] = NULL;
    node->nodes[LEFT] = NULL;
    node->nodes[RIGHT] = NULL;
    node->is_full = 0;

    return;
}

static void FreeNode(trie_node_t *node)
{
    assert(node);

    InitTrieNode(node);
    free(node);

    return;
}

size_t TrieSize(trie_t *trie)
{
    size_t height = 0;

    assert(trie);

    height = trie->branch_depth;

    return RecTrieSize(trie->root, height);
}

static size_t RecTrieSize(trie_node_t *node, size_t height)
{
    if (NULL == node)
    {
        return (0);
    }

    if (IS_FULL(node))
    {
        return pow(2, height);
    }

    return (RecTrieSize(node->nodes[LEFT], height - 1) + RecTrieSize(node->nodes[RIGHT], height - 1));
}