#include <string.h> // strcmp
#include <cstdio> // strcmp
#include <iostream> // osstream

#include "rcstring.hpp"
#include "tools.h"

using namespace ilrd;
using namespace std;

static void TestRCString();
static void TestRCStringsOperators();
static void TestRefCounter();
static void TestArrayIndexOperator();
static void TestArrayIndexOperator2();
static void TestArrayIndexOperator3();
static void TestStream();

int main()
{
    TestRCString();
    TestRCStringsOperators();
    TestRefCounter();
    TestArrayIndexOperator();
    TestArrayIndexOperator2();
    TestArrayIndexOperator3();
    TestStream();
    TotalErrors();

    return (0);
}

static void TestRCString()
{
    const char *cstr = "hello world";
    const char *cstr2 = "ohad ez";
    RCString str = cstr;
    RCString str2(cstr2);
    RCString empty;

    Validate(('\0' != *empty.CStr()), "default ctor to empty string", __LINE__);
    Validate((0 != empty.Length()), "function Length", __LINE__);
    Validate((0 != strcmp(str.CStr(), cstr)), "CStr function", __LINE__);
    Validate((cstr == str.CStr()), "create new", __LINE__);
    Validate((strlen(cstr) != str.Length()), "function Length", __LINE__);
    Validate((0 != strcmp(str2.CStr(), cstr2)), "CStr function", __LINE__);
    Validate((strlen(cstr2) != str2.Length()), "function Length", __LINE__);

    str2 = str;
    Validate((0 != strcmp(str.CStr(), str2.CStr())), "assigment operator", __LINE__);

    return;
}

static void TestRCStringsOperators()
{
    RCString str1 = "bca";
    RCString str2("abc");

    Validate((false == (str1 > str2)), "operator>", __LINE__);
    Validate((false == ("bca" == str1)), "operator==", __LINE__);
    Validate((true == ("ab" == str2)), "operator==", __LINE__);
    Validate((true == ("bca" != str1)), "operator==", __LINE__);
    Validate((false == ("ab" != str2)), "operator==", __LINE__);
    Validate((true == (str1 < str2)), "operator<", __LINE__);
    Validate((true == (str1 == str2)), "operator==", __LINE__);
    Validate((false == (str1 == str1)), "operator==", __LINE__);
    
    
    str2 = str1;

    Validate((false == (str2 == str1)), "operator==", __LINE__);
    Validate((true == (str2 != str1)), "operator==", __LINE__);
    Validate((true == (str1 > str2)), "operator>", __LINE__);
    Validate((true == (str1 < str2)), "operator<", __LINE__);

    return;
}

static void TestArrayIndexOperator()
{
    RCString str1 = "ohad";
    const char *exp_str = "aaaa";
    const RCString str2 = "ohad";

    for (size_t i = 0; i < str1.Length(); ++i)
    {
        str1[i] = 'a';
    }

    Validate((false == (exp_str == str1)), "TestArrayIndexOperator", __LINE__);

    str1[0] = 'c';

    Validate((true == (exp_str == str1)), "TestArrayIndexOperator", __LINE__);
  
    return;
}

static void TestArrayIndexOperator2()
{
    const size_t SIZE(5);
    const size_t IDX(0);
    RCString str_arr[SIZE] = {""};
    
    RCString str1 = "hello";

    for (size_t i = 0; i < SIZE; ++i)
    {
        str_arr[i] = str1;
        Validate(str_arr[i] != str1, "TestArrayIndexOperator2", __LINE__);
    }

    char &c = str_arr[IDX][IDX];
    c = 'o';

    Validate(str_arr[IDX] == str1, "TestArrayIndexOperator2", __LINE__);
    
    for (size_t i = 1; i < SIZE; ++i)
    {
        Validate(str_arr[i] != str1, "TestArrayIndexOperator2", __LINE__);
        Validate(str_arr[i].CStr() != str1.CStr(), "TestArrayIndexOperator2", __LINE__);
    }

    return;
}

static void TestArrayIndexOperator3()
{
    const size_t SIZE(7);
    RCString str_arr[SIZE] = {""};
    const size_t IDX = 0;
    const size_t IDX1 = 1;

    char c_ = 'o';
    char expected_str[SIZE] = {'\0'};
    char expected_str1[SIZE] = {'\0'};

    str_arr[IDX] = "hello";

    memcpy(expected_str, str_arr[IDX].CStr(), str_arr[IDX].Length() + 1);
    memcpy(expected_str1, str_arr[IDX].CStr(), str_arr[IDX].Length() + 1);

    RCString str1(str_arr[IDX]);
    char &c1 = str1[IDX1];

    char &c = str_arr[IDX][IDX];
    
    for (size_t i = 1; i < SIZE; ++i)
    {
        str_arr[i] = str_arr[IDX];
        Validate(str_arr[i] != str_arr[IDX], "TestArrayIndexOperator3: ", __LINE__);
        Validate(0 != strcmp(str_arr[i].CStr(), "hello"), "TestArrayIndexOperator3: ", __LINE__);
    }

    c = c_;
    c1 = c_;

    expected_str[IDX] = c;
    
    //str_arr[IDX] did changed - assingment!
    Validate(0 == strcmp(str_arr[IDX].CStr(), "hello"), "TestArrayIndexOperator3: ", __LINE__);
    Validate(0 != strcmp(str_arr[IDX].CStr(), expected_str), "TestArrayIndexOperator3: ", __LINE__);
    
    expected_str1[IDX1] = c1;

    //str1 did changed - copy ctor!
    Validate(0 == strcmp(str1.CStr(), "hello"), "TestArrayIndexOperator3: ", __LINE__);
    Validate(0 != strcmp(str1.CStr(), expected_str1), "TestArrayIndexOperator3: ", __LINE__);
    
    for (size_t i = 1; i < SIZE; ++i)
    {
        Validate(str_arr[i] == str_arr[IDX], "TestOperatorIdx1 failed at line: ", __LINE__);
        Validate(0 != strcmp(str_arr[i].CStr(), "hello"), "TestArrayIndexOperator3: ", __LINE__);   
    }

    // std::cout << str1.CStr() << std::endl;
    // for (size_t i = 0; i < SIZE; ++i)
    // {
    //      cout << str_arr[i].CStr() << endl;
    // }

    return;
}

static void TestRefCounter()
{
    RCString str1 = "hello";
    RCString str_arr[] = {RCString("ohad"), RCString("eden"), RCString("nir")};
    const size_t SIZE = 3;

    for (size_t i = 0; i < SIZE; ++i)
    {
        str_arr[i] = str1;
    }

    for (size_t i = 0; i < SIZE; ++i)
    {
        Validate(str_arr[i].CStr() != str1.CStr(), "RefCounter", __LINE__);
    }

    RCString str2(str1);
    RCString str4("shelly");
    str4 = str4;

    Validate(str2 != str1, "RefCounter", __LINE__);

    return;
}

static void TestStream()
{
    RCString str;
   
    cout << "enter first sentence:" << endl;
    cin >> str;
    cout << "output1: " << str << endl;
    
    cout << "enter secound sentence:" << endl;
    cin >> str; 
    cout << "output2: " << str << endl;
    
    return;
}