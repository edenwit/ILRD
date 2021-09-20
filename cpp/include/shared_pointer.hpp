#ifndef __ILRD_RU102_SHARED_POINTER_HPP__
#define __ILRD_RD102_SHARED_POINTER_HPP__

#include <cstddef> // size_t

namespace ilrd
{
template <class T> class SharedPointer
{
public:
	explicit inline SharedPointer(T *ptr_ = 0); 
	inline SharedPointer(const SharedPointer &other);
	template <class U> inline SharedPointer(const SharedPointer<U> &other);
	inline SharedPointer &operator=(const SharedPointer &other);
	template <class U> inline SharedPointer &operator=
	(const SharedPointer<U> &other);
	inline ~SharedPointer();

	inline T *GetPtr() const;
	inline T &operator*() const;
	inline T *operator->() const;

private:

	template<class U> 
    friend class SharedPointer;

	struct SharedData
	{
		size_t m_counter;
		T *m_ptr;
	};

	SharedData *m_shared;

    template<class U> inline void IsDerrived(U *to_cast);

    inline SharedData *InitShared(T *ptr_);
    inline void FinitShared();

}; // SharedPointer

template <class T> SharedPointer<T>::SharedPointer(T *ptr) :
	m_shared(InitShared(ptr))
{
    // empty on purpose
}

template <class T> SharedPointer<T>::~SharedPointer()
{
    FinitShared();

    return;
}

template <class T> T *SharedPointer<T>::GetPtr() const
{
    return (m_shared->m_ptr);
}

template <class T> T *SharedPointer<T>::operator->() const
{
    return (GetPtr());
}

template <class T> T &SharedPointer<T>::operator*() const
{
    return (*(GetPtr()));
}

template <class T> SharedPointer<T>::SharedPointer(const SharedPointer &other):
		m_shared(other.m_shared)
{
    ++other.m_shared->m_counter;   

    return;
}

template<class T> template <class U> SharedPointer<T>
::SharedPointer(const SharedPointer<U> &other):
	            m_shared(reinterpret_cast<SharedData *>(other.m_shared))
{
	IsDerrived(other.GetPtr());

    ++other.m_shared->m_counter;   

    return;
}

template<class T> SharedPointer<T> &SharedPointer<T>::operator=
(const SharedPointer &other)
{
    ++other.m_shared->m_counter;   
    FinitShared();
    m_shared = other.m_shared;

    return (*this);    
}

template<class T> template <class U> SharedPointer<T> 
&SharedPointer<T>::operator=(const SharedPointer<U> &other)
{
    IsDerrived(other.GetPtr());

	*this = SharedPointer<T>(other);
    
    return (*this);
}


template <class T> class SharedPointer<T>::SharedData *SharedPointer<T>
::InitShared(T *ptr_) 
{
    SharedData *s_data = new SharedData; 

    s_data->m_counter = 1;
    s_data->m_ptr = ptr_;

    return (s_data);
}

template <class T> void SharedPointer<T>::FinitShared()
{
    --m_shared->m_counter;

    if (0 == m_shared->m_counter)
    {
        delete m_shared->m_ptr;
        delete m_shared;

        m_shared = 0;
    }

    return;
}

template<class T> template<class U> void ilrd::SharedPointer<T>
::IsDerrived(U *casted)
{
    T *casting_test = casted;
	(void )casting_test;

    return;    
}

} // ilrd

#endif //__ILRD_RD102_SHARED_POINTER_HPP__