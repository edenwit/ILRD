#include <string.h>
#include <iostream>

#include "complex.hpp"
#include "tools.h"

using namespace ilrd;
using namespace std;

static void TestGetterSetter();
static void TestEqvalNoteqvalOperators();
static void TestSimpleOperators();
static void TestOperators();
static void TestStream();

int main()
{
    TestGetterSetter();
    TestEqvalNoteqvalOperators();
    TestSimpleOperators();
    TestOperators();
    TestStream();
    TotalErrors();

    return (0);
}

static void TestGetterSetter()
{
    Complex comp1;

    Validate(0.0 != comp1.GetReal(), "Getter_Real function", __LINE__);
    Validate(0.0 != comp1.GetImagenary(), "Getter_Image function", __LINE__);

    comp1.SetReal(1.0);
    comp1.SetImagenary(3.0);

    Validate(1.0 != comp1.GetReal(), "Getter_Real function", __LINE__);
    Validate(3.0 != comp1.GetImagenary(), "Getter_Image function", __LINE__);

    Complex comp2(2.0, 3.0);

    Validate(2.0 != comp2.GetReal(), "Getter_Real function", __LINE__);
    Validate(3.0 != comp2.GetImagenary(), "Getter_Image function", __LINE__);

    comp2.SetReal(9.0);
    comp2.SetImagenary(10.0);

    Validate(9.0 != comp2.GetReal(), "Getter_Real function", __LINE__);
    Validate(10.0 != comp2.GetImagenary(), "Getter_Image function", __LINE__);

    return;
}

static void TestEqvalNoteqvalOperators()
{
    Complex comp1;
    Complex comp2(2.0, 3.0);
    Complex comp3(1.0, 3.0);

    Validate(false != (comp1 == comp2), "Eqval", __LINE__);
    Validate(true != (comp2 == comp2), "Eqval", __LINE__);
    Validate(false != (comp2 == comp3), "Eqval", __LINE__);

    Validate(true != (comp1 != comp2), "Eqval", __LINE__);
    Validate(false != (comp2 != comp2), "Eqval", __LINE__);
    Validate(true != (comp2 != comp3), "Eqval", __LINE__);

    return;
}

static void TestOperators()
{
    double real = 2.0;
    double imag = 3.0;
    Complex comp1;
    Complex comp2(real, imag);
    Complex empty;
    double num1 = 1.0;
    double num2 = 5.0;

    comp1 += num1;

    Validate(true != (comp1 == Complex(num1, 0.0)), "+=", __LINE__);

    comp1 += Complex(num1, num2);

    Validate(true != (comp1 == Complex(num1 + num1, num2)), "+=", __LINE__);

    comp2 -= Complex(num1, num2);

    Validate(true != (comp2 == Complex((real - num1), (imag - num2))), "-=", __LINE__);

    Validate(true != (Complex((real - num1), (imag - num2)) == Complex((real - num1), (imag - num2))), "-=", __LINE__);

    Complex multiple_result(7.0, 7.0);
    Complex multiple(2.0, -2.0);
    comp1 = Complex(2.0, 2.0);
    comp1 *= multiple;

    Validate(true != (multiple_result == comp1), "*=", __LINE__);

    Complex division_result(7, 7);
    Complex division(-2.0, -2.0);
    comp1 = Complex(-3.0, -3.0);
    comp1 /= division;

    Validate(true != (division_result == comp1), "/=", __LINE__);

    return;
}

static void TestSimpleOperators()
{   

    Complex complex1[] = {Complex(), Complex(2.0, 0.0), Complex(-3.0, -3.0)};
    Complex complex2[] = {Complex(), Complex(1.0, 1.0), Complex(-2.0, -2.0)};
    const size_t SIZE = 3;

    Complex plus_result[] = {Complex(0.0, 0.0), Complex(3.0, 1.0), Complex(-5.0, -5.0)};
    for (size_t i = 0; i < SIZE; ++i)
    {
         Validate(true != (plus_result[i] == complex1[i] + complex2[i]), "+", __LINE__);   
    }

    Complex minus_result[] = {Complex(0.0, 0.0), Complex(1.0, -1.0), Complex(-1.0, -1.0)};
    for (size_t i = 0; i < SIZE; ++i)
    {
         Validate(true != (minus_result[i] == complex1[i] - complex2[i]), "-", __LINE__);   
    }

    Complex multiple_result[] = {Complex(7, 7), Complex(7, 7), Complex(7, 7)};
    for (size_t i = 0; i < SIZE; ++i)
    {
         Validate(true != (multiple_result[i] == complex1[i] * complex2[i]), "*", __LINE__);   
    }

    Complex division_result[] = {Complex(7, 7), Complex(7, 7), Complex(7 ,7)};
    for (size_t i = 0; i < SIZE; ++i)
    {             
         Validate(true != (division_result[i] == complex1[i] / complex2[i]), "/", __LINE__); 
         //cout << division_result[i].GetReal() << division_result[i].GetImagenary() << endl;  
    }

    return;
}

static void TestStream()
{
    cout << Complex(0.0, 1.0) << " " << Complex(3.0, 2.0) << endl;

    Complex comp;

    cin >> comp; 

    cout << comp << endl;

    return;
}