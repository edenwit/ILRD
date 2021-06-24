/*  Developer: Eden Wittenberg;									*
 *  Status: done;												*
 *  Date Of Creation: 22.06.21;									*
 *  Date Of Approval:											*
 *  Approved By: ;												*
 *  Description: Hash Table;        			            	*/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h>

#include "hash_table.h"
#include "dll.h"

struct hash
{
    d_list_t **hash_table; 
    size_t total_size;
    size_t arr_size;
    hash_func_t func;
    match_func_t match;
};

static hash_t *InitHashTable(size_t size, hash_func_t func, match_func_t match);

hash_t *HashCreate(size_t size, hash_func_t func, match_func_t match)
{
    size_t i = 0;
    hash_t *hash = NULL;

    assert(func);
    assert(match);
    assert(0 < size);

    hash = InitHashTable(size, func, match);

    if (NULL == hash)
    {
        return (NULL);
    }

    for (i = 0; i < size; ++i)
    {
        hash->hash_table[i] = DLLCreate();

        if (NULL == hash->hash_table[i])
        {
            for (i = i - 1; i > 0; --i)
            {
                DLLDestroy(hash->hash_table[i]);
            }

            free(hash->hash_table);
            free(hash);

            return (NULL);
        }
    }

    return (hash);
}

void HashDestroy(hash_t *hash)
{
    size_t i = 0;
    
    assert(hash);

    for (i = 0; i < hash->arr_size; ++i)
    {
        DLLDestroy(hash->hash_table[i]);
    }

    hash->func = NULL;
    hash->match = NULL;

    free(hash->hash_table);
    free(hash);

    return;
}

int HashInsert(hash_t *hash, void *key)
{
    size_t index = 0;
    
    assert(hash);

    index = hash->func(key);

    if (DLLIsSameIter(DLLPushFront(hash->hash_table[index], key), 
        DLLEnd(hash->hash_table[index])))
    {
        return (1);
    }

    ++hash->total_size;

    return (0);
}

void HashRemove(hash_t *hash, const void *key)
{
    size_t index = 0;
    d_list_iter_t to_remove = NULL;

    assert(hash);

    index = hash->func(key);

    to_remove = DLLFind(DLLBegin(hash->hash_table[index]), 
                DLLEnd(hash->hash_table[index]), hash->match, key);

    if (DLLIsSameIter(to_remove, DLLEnd(hash->hash_table[index])))
    {
        return;
    }

    DLLRemove(to_remove);

    --hash->total_size;

    return;
}

void *HashSearch(const hash_t *hash, const void *key)
{
    size_t index = 0;
    d_list_iter_t found = 0;

    assert(hash);

    index = hash->func(key);

    found = DLLFind(DLLBegin(hash->hash_table[index]), 
            DLLEnd(hash->hash_table[index]), hash->match, key);

    if (DLLIsSameIter(found, DLLEnd(hash->hash_table[index])))
    {
        return (NULL);
    }

    return (DLLGetData(found));
}

int HashIsEmpty(const hash_t *hash)
{
    assert(hash);

    return (0 == hash->total_size);
}

size_t HashSize(const hash_t *hash)
{
    assert(hash);

    return (hash->total_size);
}

/* DO NOT change the data!!! */
int HashForEach(const hash_t *hash, action_func_t func, void *param)
{
    size_t i = 0;
    
    assert(hash);

    for (i = 0; i < hash->arr_size; ++i)
    {
        if (DLLForEach(DLLBegin(hash->hash_table[i]),
            DLLEnd(hash->hash_table[i]), func, param))
        {
            return (1);
        }
    }

    return (0);
}

static hash_t *InitHashTable(size_t size, hash_func_t func, match_func_t match)
{
    hash_t *hash = NULL;
    d_list_t **hash_table = NULL;

    hash = (hash_t *)malloc(sizeof(hash_t));

    if (NULL == hash)
    {
        return (NULL);
    }

    hash_table = (d_list_t **)malloc(size * sizeof(d_list_t *));

    if (NULL == hash_table)
    {
        free(hash);

        return (NULL);
    }

    hash->func = func;
    hash->match = match;
    hash->arr_size = size;
    hash->total_size = 0;
    hash->hash_table = hash_table;

    return (hash);
}
