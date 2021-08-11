#include <cstddef>
#include <cstring>
#include "simple_string.hpp"

/* namespace ilrd
{
class String
{
public:
	String(const char *cstr = ""); // non-explicit on purpose 
	String(const String &other);
	~String();
	String &operator=(const String &other);
	size_t Length() const;
	const char *CStr() const;

private:
	char *m_cstr;
};
} //ilrd
 */

using namespace ilrd;

String::String(const char *cstr) : m_cstr(new char[strlen(cstr) + 1])
{
	strcpy(m_cstr, cstr);
}

String::String(const String& other) : m_cstr(new char[other.Length() + 1])
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
