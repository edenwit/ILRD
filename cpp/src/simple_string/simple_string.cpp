#include <cstddef>
#include <cstring>
#include <iostream>
#include <cassert>

#include "simple_string.hpp"

using namespace ilrd;

String::String(const char *cstr) : m_cstr(new char[strlen(cstr) + 1])
{
	strcpy(m_cstr, cstr);
}

String::String(const String &other) : m_cstr(new char[other.Length() + 1])
{
	strcpy(m_cstr, other.m_cstr);
}

String::~String()
{
	delete[] m_cstr;
	m_cstr = NULL;
}

String &String::operator=(const String &other)
{
	if (Length() != other.Length())
	{
		delete[] m_cstr;
		m_cstr = new char[other.Length() + 1];
	}

	strcpy(m_cstr, other.CStr());

	return (*this);
}

size_t String::Length() const
{
	return (strlen(m_cstr));
}

const char *String::CStr() const
{
	return (m_cstr);
}

bool ilrd::operator<(const String &lhs, const String &rhs)
{
	assert(lhs.CStr());
	assert(rhs.CStr());

	return (0 > strcmp(lhs.CStr(), rhs.CStr()));
}

bool ilrd::operator>(const String &lhs, const String &rhs)
{
	assert(lhs.CStr());
	assert(rhs.CStr());

	return (0 < strcmp(lhs.CStr(), rhs.CStr()));
}

bool ilrd::operator==(const String &lhs, const String &rhs)
{
	assert(lhs.CStr());
	assert(rhs.CStr());

	return (0 == strcmp(lhs.CStr(), rhs.CStr()));
}

std::ostream &ilrd::operator<<(std::ostream &os, const String &str)
{
	assert(str.CStr());

	return (os << str.CStr());
}
