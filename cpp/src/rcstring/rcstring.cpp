#include "iostream" // std::isstream
#include "cstring" // memcpy
#include <cstddef> // offsetof
#include <vector> // std::vector
#include <cstdio> // EOF

#include "rcstring.hpp"

namespace ilrd
{

struct StringRC
{
public:
    size_t m_ref_count;
    char m_cstr[1];
};

inline StringRC *InitRCString(const char *str)
{
    const size_t LEN = strlen(str) + 1;

    StringRC *value = static_cast<StringRC *>(::operator new (LEN 
                                                + offsetof(StringRC, m_cstr)));
    value->m_ref_count = 1;

    memcpy(value->m_cstr, str, LEN);

    return (value);
}

RCString::RCString(const char *cstr) : m_data(InitRCString(cstr))
{
    ;
}

RCString::~RCString()
{
    --m_data->m_ref_count;

    if (m_data->m_ref_count == 0)
    {
        delete (m_data);
        m_data = 0;
    }
}

RCString::RCString(const RCString &other_): m_data(other_.m_data)
{
    ++(this->m_data->m_ref_count);
}

RCString &RCString::operator=(const RCString &other)
{
    this->~RCString();

    m_data = other.m_data;
    ++(m_data->m_ref_count);

    return (*this);
}

const char *RCString::CStr() const
{
    return (m_data->m_cstr);
}

size_t RCString::Length() const
{
    return (strlen(CStr()));
}

bool operator<(const RCString &str1, const RCString &str2)
{
    return (0 > strcmp(str1.CStr(), str2.CStr()));
}

bool operator>(const RCString &str1, const RCString &str2)
{
    return (0 < strcmp(str1.CStr(), str2.CStr()));
}

bool operator==(const RCString &str1, const RCString &str2)
{
    return (0 == strcmp(str1.CStr(), str2.CStr()));
}

bool operator!=(const RCString &str1, const RCString &str2)
{
    return (!(str1 == str2));
}

char RCString::operator[] (size_t index) const
{
    return (m_data->m_cstr[index]);
}

char& RCString::operator[] (size_t index)
{
    if (1 != m_data->m_ref_count)
    {
        --(m_data->m_ref_count);
        m_data = InitRCString(m_data->m_cstr);
    }

    return (m_data->m_cstr[index]);
}

std::ostream &operator<<(std::ostream &os, const RCString &str)
{
    return (os << str.CStr());
}

std::istream &operator>>(std::istream &is, RCString &str)
{
    std::vector<char> string = std::vector<char>();

    int ch = is.get();

    while (EOF != ch && '\n' != ch)
    {
        string.push_back(ch);
        ch = is.get();
    }

    string.push_back('\0');

    str = RCString(&string[0]); 

    return (is);
}
}

