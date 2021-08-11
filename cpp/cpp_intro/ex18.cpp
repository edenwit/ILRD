#include <iostream>

void Foo(const double &x);
void Bar(double &x);

int main()
{
    double num = 9;

    Foo(num);
    Bar(*(reinterpret_cast<double *>(&num)));

    return (0);
}


void Foo(const double &x)
{
    printf("var value: %f, var pointer: %p\n", x, &x);
}

void Bar(double &x)
{
    printf("var value: %f, var pointer: %p\n", x, &x);
}
