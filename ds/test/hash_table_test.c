#include <stdio.h>
#include <assert.h>
#include <stdlib.h> /* malloc */
#include <string.h>

#include "hash_table.h"

#define WORDS_IN_DICT (102400)
#define MAX_WORD_SIZE (50)
#define ESC (27)

static size_t HashFunctionForDict(const void *key);
static char *LoadLinuxDict(hash_t *hash);
static int MatchFunc(const void *str1, const void *str2);
static void SpellCheck(hash_t *hash);
/* 
static int PrintElement(void *data, void *param);
 */
int main()
{
    hash_t *hash = HashCreate(WORDS_IN_DICT, HashFunctionForDict, MatchFunc);
    char *dict_ptr_to_free = '\0';
    char *str_add = "ede\n";

    if (NULL == hash)
    {
        return (1);
    }

    dict_ptr_to_free = LoadLinuxDict(hash);

    /* cehck if 'ede' in the dicitonary */
    SpellCheck(hash);

    if (HashInsert(hash, str_add))
    {
        printf("Insertion of %s failed.\n", str_add);
    }

    /*  HashForEach(hash, PrintElement, NULL);  */

    /* cehck if 'ede' in the dicitonary */

    SpellCheck(hash);

    HashRemove(hash, (void *)str_add);

    /* cehck if 'ede' in the dicitonary */

    SpellCheck(hash);

    HashDestroy(hash);

    free(dict_ptr_to_free);

    return (0);
}

static char *LoadLinuxDict(hash_t *hash)
{
    FILE *file_ptr = NULL;
    char *whole_dict = NULL;
    char *ptr = NULL;

    assert(hash);

    whole_dict = (char *)malloc(WORDS_IN_DICT * MAX_WORD_SIZE);

    if (NULL == whole_dict)
    {
        printf("Failed to alloc space for dict!\n");

        return (NULL);
    }

    ptr = whole_dict;

    file_ptr = fopen("/usr/share/dict/words", "r");

    if (NULL == file_ptr)
    {
        free(whole_dict);

        return (NULL);
    }

    while (NULL != fgets(whole_dict, WORDS_IN_DICT, file_ptr))
    {
        if (HashInsert(hash, whole_dict))
        {
            printf("HashInsert error at line: %d\n", __LINE__);
        }

        whole_dict = (whole_dict + 1 + strlen(whole_dict));
    }

    fclose(file_ptr);

    return (ptr);
}

static size_t HashFunctionForDict(const void *key)
{
    size_t i = 0;

    while ('\0' != *((char *)key))
    {
        i += *((char *)key);

        key = (char *)key + 1;
    }

    return (i % WORDS_IN_DICT);
}

static void SpellCheck(hash_t *hash)
{
    char buffer[MAX_WORD_SIZE + 1] = {'\0'};

    printf("Insert words for spellcheck. hit ESC to quit\n");

    while ((NULL != fgets(buffer, MAX_WORD_SIZE + 1, stdin)) && (ESC != *buffer))
    {
        if (NULL == HashSearch(hash, buffer))
        {
            printf("Not found in the dictionary!\n");
        }
        else
        {
            printf("Found in the dictionary!\n");
        }
    }

    return;
}

static int MatchFunc(const void *str1, const void *str2)
{
    return (!strcmp((char *)str1, (char *)str2));
}
/* 
static int PrintElement(void *data, void *param)
{
    (void)(param);

    printf("%s\n", (char *)data);

    return (0);
} */