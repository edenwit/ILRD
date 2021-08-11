#include <stdio.h>

int main(void)
{
    foo();

    return (0);
}

void foo(int x)
{
    printf("checking print: %d\n", x);
}