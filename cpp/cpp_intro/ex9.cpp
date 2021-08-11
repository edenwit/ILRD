#include <iostream>

namespace A
{
    char xl;
};


namespace B
{
    using namespace A;
    int x;
};
int foo(int runs, int sub_runs = 3);


int main()
{
    std::cout << sizeof(B::x) << std::endl;
    foo(5);

    return (0);
}

int foo(int runs, int sub_runs)
{
    for (int i = 0; i < runs; ++i)
    {   
        std::cout << "run %d\n" << i << std::endl;
        for (int j = 0; j < sub_runs; ++j)
        {
            std::cout << "sub_run %d" << j << std::endl;
        }
    }

    return (0);
}