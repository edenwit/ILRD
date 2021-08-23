#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
#include  <typeinfo>

using namespace std;


class X
{
public:
    X(double d_) :m_a(d_) {}
    virtual ~X() {}
    double m_a;
    
private:
};

class Y: public X
{
public:
    Y(double d_, int i_): X(d_), m_b(i_) {}
    int m_b;
private:
};

int main()
{
    Y y1(0.0, 0), y2(14.2, 5);
    Y y3(0.0, 0), y4(14.2, 5);

    cout << "start" << endl;
    cout << y1.m_a << " " << y1.m_b << endl;
    cout << y3.m_a << " " << y3.m_b << endl;

    X &x1 = y1;

    cout << "X &x1 = y1" << endl;
    cout << y1.m_a << " " << y1.m_b << endl;
    cout << y3.m_a << " " << y3.m_b << endl;

    X &x2 = y2;

    cout << "X &x2 = y2" << endl;
    cout << y1.m_a << " " << y1.m_b << endl;
    cout << y3.m_a << " " << y3.m_b << endl;

    x1 = x2;

    cout << "x1 = x2" << endl;
    cout << y1.m_a << " " << y1.m_b << endl;
    cout << y3.m_a << " " << y3.m_b << endl;

    y3 = y4;

    cout << "y3 = y4" << endl;
    cout << y1.m_a << " " << y1.m_b << endl;
    cout << y3.m_a << " " << y3.m_b << endl;


    return 0;
}