#include <stdio.h>

int main(void)
{
    int y = 0;

    foo();
    f(y);

    return (0);
}

void foo(int x)
{
    printf("checking print %d\n", x);


    return (0);
}
  
void f(void)
{ 
   printf("hi\n");
}