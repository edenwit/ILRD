#include <stdio.h>

int main(void)
{
    int y = 0;

    foo();
    f(y);

    return (0);
}

void foo(void)
{
    printf("checking print\n");


    return (0);
}
  
void f(void)
{ 
   printf("hi\n");
}