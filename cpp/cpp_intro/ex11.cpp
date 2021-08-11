#include <cstdio>

void Foo();
void Foo(int i);
void Foo(char c);

void Foo()
{
    printf("normal Foo\n");
}
void Foo(int i)
{

    printf("int Foo\n");

}
void Foo(char c)
{
    printf("char Foo\n");
}
