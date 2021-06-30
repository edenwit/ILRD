#include <stdio.h>
#include "trie.h"

static void Test();

int main()
{
    Test();
    return 0;
}

static void Test()
{

    size_t num_of_bit = 8;
    size_t size = 256;
    unsigned long output_ip = 0;
    unsigned long ip_to_remove = 0;
    size_t test_size = 0;

    trie_t *trie = NULL;
    size_t i = 0;
    int status = 0;

    trie = TrieCreate(num_of_bit);

    if (NULL == trie)
    {
        printf("TrieCreate failed at line: %d\n", __LINE__);
    }

    for (i = 0; i < size; ++i)
    {
        output_ip = 0;

        if (TRIE_SUCCESS == TrieInsert(trie, i, &output_ip))
        {
            ++test_size;
            if (i != output_ip)
            {
                printf("TrieInsert failed at line: %d ip: %ld exp ip %lu\n", __LINE__, output_ip, i);
            }
            if (test_size != TrieSize(trie))
            {
                printf("Wrong size. exp: %ld, actual: %ld\n", TrieSize(trie), test_size);
            }

        }
        else
        {
            printf("TrieInsert failed at line: %d ip: %ld exp ip %lu\n", __LINE__, output_ip, i);
        }

    }

    for (i = 0; i < size; ++i)
    {
        output_ip = 0;
        status = TrieInsert(trie, i, &output_ip);
        
        if (TRIE_FULL_FAIL != status)
        {
            printf("TrieInsert failed at line: %d in index: %lu. status: %d\n", __LINE__, i, status);
        }
    }
 
    for (ip_to_remove = test_size; 0 < ip_to_remove; --ip_to_remove)
    {
        TrieRemove(trie, ip_to_remove);
        
        if (TRIE_FULL_FAIL != status)
        {
            printf("TrieRemove failed at line: %d in index: %lu. status: %d\n", __LINE__, i, status);
        } 
    } 
    
    for (i = 0; i < size; ++i)
    {
        output_ip = 0;
        status = TrieInsert(trie, 0, &output_ip);
        if (status)
        {
            printf("TrieInsert failed at line: %d in index: %lu. status: %d\n", __LINE__, i, status);
        }

        if (i + 1 != TrieSize(trie))
        {
            printf("size: %ld\n", TrieSize(trie));
            printf("%ld\n",output_ip);
        }
    }
 
    TrieDestroy(trie);

    return;
}