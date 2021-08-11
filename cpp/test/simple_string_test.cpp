#include <cstring>
#include <iostream>

#include "simple_string.hpp"

using ilrd::String;
using namespace std;

static void TestSimpleString();
static void TestStringsOperators();

int main()
{
    TestSimpleString();
    TestStringsOperators();

    return (0);
}

static void TestSimpleString()
{
    const char *cstr = "hello world";
    const char *cstr2 = "new world";
    String str = cstr;
    String str2(cstr2);
    String empty;

    cstr = cstr;
    if (*empty.CStr() != '\0')
    {
        std::cout << "Failed default ctor to empty string" << endl;
    }

    if (0 != strcmp(str.CStr(), cstr))
    {
        std::cout << "Not copied " << endl;
    }

    if (cstr == str.CStr())
    {
        std::cout << "Not create new" << endl;
    }

    if (strlen(cstr) != str.Length())
    {
        std::cout << "Incorrect length" << endl;
    }

    (str = cstr) = cstr2;
    if (0 != strcmp(str.CStr(), str2.CStr()))
    {
        std::cout << "Not assigned to assigned" << endl;
    }

    return;
}

static void TestStringsOperators()
{
    String str1 = "bca";
    String str2("abc");

    if (false == (str1 > str2))
    {
        std::cout << "Test failed at line: " << __LINE__ << endl;
    }

    if (true == (str1 < str2))
    {
        std::cout << "Test failed at line: " << __LINE__ << endl;
    }

    if (true == (str1 == str2))
    {
        std::cout << "Test failed at line: " << __LINE__ << endl;
    }

    if (false == (str1 == str1))
    {
        std::cout << "Test failed at line: " << __LINE__ << endl;
    }

    str2 = str1;

    if (false == (str2 == str1))
    {
        std::cout << "Test failed at line: " << __LINE__ << endl;
    }

    if (true == (str1 > str2))
    {
        std::cout << "Test failed at line: " << __LINE__ << endl;
    }

    if (true == (str1 < str2))
    {
        std::cout << "Test failed at line: " << __LINE__ << endl;
    }

    if (!("bca" == str1))
    {
        std::cout << "Test failed at line: " << __LINE__ << endl;
    }


    cout << str1 << endl;

    return;
}