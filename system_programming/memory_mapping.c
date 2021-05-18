#include <stdio.h>
#include <stdlib.h>
#include "mem_shared_lib.h"

const int const_global = 1; /* Global constant (code area) */
static const int static_cons_global = 3; /*Global static constants (code area) */
int init_global = 2; /*Global variables (data area) */
int not_init;/*Uninitialized global variables (BBS area)*/

int main(int argc, char *argv[], char *evms[]) { /*Function (code area)*/
    static const int static_const = 1; /*Static local constant (code area)*/
    static int static_ = 2;/*Static local variables (data area)*/
    static int static_not_init;/*Uninitialized static local variables (BBS)*/
    const int const_ = 3;/*Local constant (stack area)*/
    int local_ = 4;/*Local variables (stack area)*/
    char *cstr = "abc";/*Literal (code area)*/
    int *m = malloc(sizeof(int));/*Dynamic allocation of memory (heap area)*/
    extern char **environ;

    printf("------------------Command line, environment variable table------------------\n");
    printf("Command line environment variable table: %16p\n", evms);
    printf("Environment Variable Table: %16p\n", environ);

    printf("------------------Stack area------------------\n");
    printf("Local constant: %16p\n", &const_);
    printf("Local variable: %16p\n", &local_);

    printf("------------------Heap Area------------------\n");
    printf("Dynamic allocation of memory: %16p\n", m);

    printf("------------------BBS area------------------\n");
    printf("Uninitialized global variable: %16p\n", &not_init);
    printf("Uninitialized static local variable: %16p\n", &static_not_init);

    printf("------------------Data area------------------\n");
    printf("Global Variables: %16p\n", &init_global);
    printf("Static local variable: %16p\n", &static_);

	PrintWhoIAm();

    printf("------------------Code area------------------\n");
    printf("Global constant: %16p\n", &const_global);
    printf("Global static constant: %16p\n", &static_cons_global);
    printf("Function: %16p\n", &main);
    printf("Literal:%16p\n", cstr);
    return 0;
}

