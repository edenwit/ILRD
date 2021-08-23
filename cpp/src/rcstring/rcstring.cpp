#include "iostream" //  isstream
#include "cstring" //   memcpy
#include <cstddef> //   offsetof
#include <vector> //    vector
#include <cstdio> //    EOF

#include "rcstring.hpp"

namespace ilrd
{
void ManipulateRef(RefCountStr *m_data);

struct RefCountStr
{
public:
    size_t m_r_counter;
    bool m_char_ref;
    char m_cstr[1];
};

inline RefCountStr *InitRCString(const char *str)
{
    static const size_t LEN = (strlen(str) + 1); 

    RefCountStr *value = static_cast<RefCountStr *>(operator new (LEN 
                                    + offsetof(RefCountStr, m_cstr)));
    value->m_r_counter = 1;
    value->m_char_ref = false;

    memcpy(value->m_cstr, str, LEN);

    return (value);
}

RCString::RCString(const char *cstr) : m_data(InitRCString(cstr))
{
    //"empty on purpose"
}

RCString::~RCString()
{
    ManipulateRef(m_data);
}

RCString::RCString(const RCString &other_): m_data(other_.m_data)
{
    if (other_.m_data->m_char_ref)
    {
        m_data = InitRCString(other_.CStr());
    }
    else
    {
        ++(other_.m_data->m_r_counter);
    }
}

RCString &RCString::operator=(const RCString &other)
{ 
    if (other.m_data->m_char_ref)
    {
        ManipulateRef(m_data);
        m_data = InitRCString(other.CStr());
    }
    else
    {
        ++(other.m_data->m_r_counter);
        ManipulateRef(m_data);
        m_data = other.m_data;
    }

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

char &RCString::operator[](size_t index)
{
    if (1 != (m_data->m_r_counter))
    {
        --(m_data->m_r_counter);
        m_data = InitRCString(m_data->m_cstr);
    }

    m_data->m_char_ref = true;

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

    while ((EOF != ch) && ('\n' != ch))
    {
        string.push_back(ch);
        ch = is.get();
    }

    string.push_back('\0');

    str = RCString(&string[0]); 

    return (is);
}

void ManipulateRef(RefCountStr *m_data)
{
    --(m_data->m_r_counter);
    
    if (0 == m_data->m_r_counter)
    {
        delete (m_data);
        m_data = 0;
    }

    return;
}
}

