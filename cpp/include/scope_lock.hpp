#ifndef __ILRD_RD102_SCOPE_LOCK_HPP__
#define __ILRD_RD102_SCOPE_LOCK_HPP__

#include <boost/core/noncopyable.hpp> // boost::noncopyable

namespace ilrd
{
template <class T>
class ScopeLock: private boost::noncopyable
{
public:
    explicit ScopeLock(T *lock_);
    ~ScopeLock();

private:
    T *m_lock;
}; // ScopeLock

template<class T> inline ScopeLock<T>::ScopeLock(T *lock_) : m_lock(lock_)
{
    m_lock->lock();
}
template<class T> inline ScopeLock<T>::~ScopeLock()
{
    m_lock->unlock();
}


} // ilrd

#endif //__ILRD_RD102_SCOPE_LOCK_HPP__