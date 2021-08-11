#include <stdio.h>

typedef struct Person Person_t;

typedef struct List List_t;

struct List
{
    int a;
    char *b;
    Person_t *person;
};

struct Person
{
    char *str;
    int age;
};


void *ll_find(List_t *ll,int key)
{
    return NULL;
}

void foo(List_t *ll, int key, int age)
{
    void *vv = ll_find(ll, key);

    Person_t *p = static_cast<Person_t *>(ll);

    p->age = age;

}



int main(void)
{
    bool b1 = true;
    bool b2;
    int i = b1;

    i = 7;

    b2 = i; 

    printf("%ld\n", sizeof(bool));


    return (0);
}