#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

using namespace std;

int Foo(int) throw(bad_alloc);

class X
{
public:
    X() { cout << "in ctor" << endl; };
    ~X() { cout << "bad alloc" << endl;  cerr << Foo(m_a) << endl; };

private:
    int m_a;
};

int Foo(int) throw(bad_alloc)
{
    throw(bad_alloc());
    
    return(0);
}

void Bar() throw(bad_cast)
{
    int i = 5;
    
    throw (bad_cast());
}


void Fishi()
{

    X x1;

    try
    {
        Bar();
    }

    catch(...)
    {
        cerr << "hello" << endl;
    }

}

int main()
{
    // try
    // {
        Fishi();
    // }
    // catch(...)
    // {
    //     cerr << "hello" << endl;
    // }
    
    return (0);
}
