#include <cstddef>

const size_t ARR_SIZE = 100;
const int B_INIT = -1;

class f 
{
public:
    f() :b(B_INIT)
    {
        //empty
    }
    void h(int d)
    {
        ++b;
        a[b] = d;
    }
    int e()
    {
        --b;

        return (a[b]);
    }
private:
    int b;
    int a[ARR_SIZE];
};