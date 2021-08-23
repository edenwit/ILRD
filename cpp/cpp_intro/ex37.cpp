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
    virtual int Getter() {return m_a;}
    virtual void Setter(int m_m_a) {m_a = m_m_a;}    

private:
    double m_a;
};

class Y: public X
{
public:
    Y() {cout << "ctor y : " << this << endl;}
    virtual ~Y() {cout << "dtor y : " << this << endl;}
    int Getter() {return m_b;}
    void Setter(int m_m_b) {m_b = m_m_b;}

private:
    int m_b;
};

void Foo(X& x)
{
    cout << "size of x is : " << x.Getter() << endl;
}

int main()
{
    Y y1;
    y1.Setter(15);

    Foo(y1);

    return 0;
}

