#ifndef ILRD_RD102_SIMPLE_STRING_HPP
#define ILRD_RD102_SIMPLE_STRING_HPP

#include <cstddef>

namespace ilrd
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


#endif /* ILRD_RD102_SIMPLE_STRING_HPP */
