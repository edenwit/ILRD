#ifndef _OL_102_TRIE_H_
#define _OL_102_TRIE_H_

#include <stddef.h>

typedef struct trie trie_t;

typedef enum status_t
{
    TRIE_SUCCESS,
    TRIE_MALLOC_FAILED,
    TRIE_BRANCH_FREE,
    TRIE_FULL_FAIL
} trie_status_t;

/*
enum nodes
{
    LEFT,
    RIGHT,
    PARENT,
    NUM_OF_NODES
};

typedef struct trie_node trie_node_t;

struct trie
{
    trie_node_t *root;
    size_t branch_depth;
}; 

struct trie_node
{
    int is_full;
    trie_node_t *nodes[NUM_OF_NODES];
}; */

trie_t *TrieCreate(size_t num_of_bits);

void TrieDestroy(trie_t *trie);

trie_status_t TrieInsert(trie_t *trie, unsigned long requested_ip, unsigned long *output_ip);

int TrieRemove(trie_t *trie, unsigned long data_to_remove);

size_t TrieSize(trie_t *trie);

#endif /* _OL_102_TRIE_H_ */