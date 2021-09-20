#ifndef __ILRD_RU102_SHARED_POINTER_HPP__
#define __ILRD_RD102_SHARED_POINTER_HPP__

#include <cstddef> // size_t

namespace ilrd
{

template <class T>
class SharedPointer
{

public:
    explicit inline SharedPointer(T *ptr_ = 0);
    inline SharedPointer(const SharedPointer &other_);
    template <class U> inline SharedPointer(const SharedPointer<U> &other_);
    inline SharedPointer &operator=(const SharedPointer &other_);
    template <class U> inline SharedPointer &operator=(const SharedPointer<U> &other_);
    inline ~SharedPointer();

    inline T *GetPtr() const;
    inline T &operator*() const;
    inline T *operator->() const;

private:
    template<class U> friend class SharedPointer;

    T *m_ptr;
    size_t *m_counter;

}; // SharedPointer

template<class T>
SharedPointer<T>::SharedPointer(T *ptr_) : m_ptr(ptr_), m_counter(new size_t(1))
{
    //empty
}

template<class T>
SharedPointer<T>::SharedPointer(const SharedPointer &other_) :
m_ptr(other_.m_ptr), m_counter(other_.m_counter)
{
    ++(*m_counter);
}

template<class T>
SharedPointer<T>::~SharedPointer()
{
    if (1 == *m_counter)
    {
        delete m_counter;
        delete m_ptr;
    }
    else
    {
        --(*m_counter);
    }
}

template<class T>
SharedPointer<T> &SharedPointer<T>::operator=(const SharedPointer &other_)
{
    ++(*other_.m_counter);
    --(*m_counter);

    if (0 == m_counter)
    {
        delete m_ptr;
        delete m_counter;
    }

    m_ptr = other_.m_ptr;
    m_counter = other_.m_counter;

    return (*this);
}

template<class T>
T *SharedPointer<T>::GetPtr() const
{
    return (m_ptr);
}

template<class T>
T &SharedPointer<T>::operator*() const
{
    return (*m_ptr);
}

template<class T>
T *SharedPointer<T>::operator->() const
{
    return (m_ptr);
}

template<class T>
template<class U>
SharedPointer<T>::SharedPointer(const SharedPointer<U> &upcast) :
m_ptr((upcast.m_ptr)), m_counter(upcast.m_counter)
{
    ++(*m_counter);
}

template<class T>
template<class U>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<U> &other_)
{
    *this = SharedPointer<T>(other_);
    return (*this);
}
} // ilrd

#endif //__ILRD_RD102_SHARED_POINTER_HPP__