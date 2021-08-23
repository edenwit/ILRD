#include <string.h>
#include <iostream>

#include "rcstring.hpp"
#include "tools.h"

using namespace ilrd;
using namespace std;

static void TestGetter();
static void TestEqvalNoteqvalOperators();
static void TestOperators();
static void TestStream();

int main()
{
    TestGetter();
    TestEqvalNoteqvalOperators();
    TestOperators();
    TestStream();

    TotalErrors();

    return (0);
}

static void TestGetter()
{
    RCString str1("just pray this works...");

    Validate(strcmp("just pray this works..." ,str1.CStr()), "Cstr_test function", __LINE__);
    Validate(23 != str1.Length(), "str Lenght test", __LINE__);
    Validate(26 == str1.Length(), "str Lenght test", __LINE__);
    Validate(!strcmp("just spray this works..." ,str1.CStr()), "Cstr_test function", __LINE__);

    return;
}

static void TestEqvalNoteqvalOperators()
{
    RCString str1;
    RCString str2("covid19");
    RCString str3("covid 20");
    RCString str4("all you need is dmall");


    Validate(false != (str1 == str2), "Eqval", __LINE__);
    Validate(true != (str2 == str2), "Eqval", __LINE__);
    Validate(false != (str2 == str3), "Eqval", __LINE__);

    Validate(true != (str1 != str2), "Eqval", __LINE__);
    Validate(false != (str2 != str2), "Eqval", __LINE__);
    Validate(true != (str2 != str3), "Eqval", __LINE__);

    Validate(true != (str1 < str2), "Eqval", __LINE__);
    Validate(false != (str2 > str2), "Eqval", __LINE__);
    Validate(true != (str2 > str3), "Eqval", __LINE__);

    str1 = str2;
    str4 = str2;

    
    Validate(true != (str1 == str2), "Eqval", __LINE__);
    Validate(true != (str4 == str2), "Eqval", __LINE__);


    return;
}

static void TestOperators()
{
    RCString str1("testings");
    RCString str2(str1);

    Validate(true != ('e' == str1[1]), "[]", __LINE__);
    Validate(true != ('e' == str2[1]), "[]", __LINE__);

    str2[1] = 'x';

    Validate(true != ('e' == str1[1]), "[]", __LINE__);
    Validate(true != ('x' == str2[1]), "[]", __LINE__);

    return;
}

static void TestStream()
{
    cout << RCString("covid19 free!") << " " << RCString("back to dmol please!") << endl;

    RCString str;

    cin >> str; 

    cout << str << endl;

    return;
}