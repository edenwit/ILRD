#include <iostream>

template <typename T>

void foo(T t)
{
    std::cout << t << " Generic foo for " << typeid(t).name() << std::endl;
}

template <>
void foo(int t)
{
    std::cout << t << " Specialized foo for (for int param)\n";
}

int main ()
{
    foo (4.2);
    foo (5);
    foo<int>(5);

    return (0);
}
