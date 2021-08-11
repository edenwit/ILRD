#include <string.h>
#include <iostream>

#include "simple_string.hpp"

using ilrd::String;
using namespace std;

int main()
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


	return (0);
}