#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include <typeinfo>

using namespace std;

class Base
{
public:
    virtual ~Base() {}
    inline virtual void DoIt() { cout << "In Base::DoIt()" << endl; }
};

class Derived : public Base
{
public:
    inline virtual void DoIt() { cout << "In Derived::DoIt()" << endl; }
};

int main()
{

    Base *basePtr = new Derived;
    Base *DerivedPtr = new Derived;
    Derived Derivedd;
    
    
    DerivedPtr->DoIt();    // Calls Derived::DoIt() through virtual function call
    basePtr->Base::DoIt(); // Explicitly calls Base::DoIt() using normal function call
    Derivedd.DoIt();

    delete basePtr;

    return (0);
}