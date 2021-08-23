#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include  <typeinfo>

using namespace std;

class X
{
public:
    X() {cout << "ctor x : " << this << endl;}
    virtual ~X() {cout << "dtor x : " << this << endl;}

private:
    int m_a;
};

class Y: public X
{
public:
    Y() {cout << "ctor y : " << this << endl;}
    virtual ~Y() {cout << "dtor y : " << this << endl;}
private:
    int m_b;
};

int main()
{
    X* xp = new Y[5];

    delete[] xp;

    return 0;
}