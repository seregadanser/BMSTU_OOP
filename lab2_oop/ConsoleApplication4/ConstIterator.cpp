#ifndef CITER_CPP
#define CITER_CPP

#include "ConstIterator.h"

template<typename T>
void ConstIterator<T>::CheckPtr(int line) const
{
    time_t cur_time = time(NULL);
    /*if (index >= elem_count || index < 0)
        throw IndexError(ctime(&cur_time), __FILE__, line, "CheckPtr");*/

    if (ptr.expired())
        throw NoPtr(ctime(&cur_time), __FILE__, line, "CheckPtr");
}

template<typename T>
bool ConstIterator<T>::CheckIter() const
{
    if (index >= elem_count || index < 0 || (elem_count == 0))
        return false;
    else
        return true;
}

template<typename T>
T* ConstIterator<T>::GetCurPtr() const
{
    std::shared_ptr<T[]> copy_ptr = ptr.lock();
    return copy_ptr.get() + index;
}

template<typename T>
ConstIterator<T>::ConstIterator(const ConstIterator<T>& iter) noexcept : BaseIter(iter)
{
    ptr = iter.ptr;
}

template<typename T>
ConstIterator<T>::ConstIterator(const Vector<T>& vec) noexcept : BaseIter()
{
    elem_count = vec.elem_count;
    ptr = vec.data_list;
}

template <typename T>
ConstIterator<T>::~ConstIterator() = default;


template<typename T>
const T& ConstIterator<T>::operator*() const
{
    CheckPtr(__LINE__);

    return  *GetCurPtr();
}

template<typename T>
const T* ConstIterator<T>::operator->() const
{
    CheckPtr(__LINE__);

    return  GetCurPtr();
}

template<typename T>
const T& ConstIterator<T>::operator[](const int offset) const
{
    CheckPtr(__LINE__);
    return *GetCurPtr() + offset;
}


#pragma region LogicalOperators
template<typename T>
bool ConstIterator<T>::operator<=(const ConstIterator<T>& b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() <= b.GetCurPtr();
}

template<typename T>
bool ConstIterator<T>::operator<(const ConstIterator<T>& b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() < b.GetCurPtr();
}

template<typename T>
bool ConstIterator<T>::operator>=(const ConstIterator<T>& b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() >= b.GetCurPtr();
}

template<typename T>
bool ConstIterator<T>::operator>(const ConstIterator<T>& b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() > b.GetCurPtr();
}

template<typename T>
bool ConstIterator<T>::operator==(const ConstIterator<T>& b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() == b.GetCurPtr();
}

template<typename T>
bool ConstIterator<T>::operator!=(const ConstIterator<T>& b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() != b.GetCurPtr();
}
#pragma endregion

#pragma region UnaryOperators
template<typename T>
ConstIterator<T> ConstIterator<T>::operator++(int)
{
    CheckPtr(__LINE__);
    ConstIterator<T> tmp(*this);
    ++(*this);

    return tmp;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator++()
{
    CheckPtr(__LINE__);
    ++index;

    return *this;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator--(int)
{
    CheckPtr(__LINE__);
    ConstIterator<T> tmp(*this);
    --(*this);

    return tmp;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator--()
{
    CheckPtr(__LINE__);
    --index;

    return *this;
}
#pragma endregion 

#pragma region MathOperators
template<typename T>
template <typename T2>
ConstIterator<T>& ConstIterator<T>::operator+=(const T2 n)
{
    CheckPtr(__LINE__);
    ptr += n;

    return *this;
}

template<typename T>
template <typename T2>
ConstIterator<T> ConstIterator<T>::operator+(const T2 n) const
{
    CheckPtr(__LINE__);
    ConstIterator<T> iter(*this);
    iter.index += n;

    return iter;
}

template<typename T>
template <typename T2>
ConstIterator<T>& ConstIterator<T>::operator-=(const T2 n)
{
    CheckPtr(__LINE__);
    index -= n;

    return *this;
}

template<typename T>
template <typename T2>
ConstIterator<T> ConstIterator<T>::operator-(const T2 n) const
{
    CheckPtr(__LINE__);

    ConstIterator<T> iter(*this);
    iter.index -= n;

    return iter;
}

#pragma endregion

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator=(const ConstIterator<T>& iter) noexcept
{
    CheckPtr(__LINE__);

    ptr.reset(iter.ptr);
    elem_count = iter.elem_count;
    index = iter.index;
    return *this;
}

template<typename T>
ConstIterator<T>::operator bool() const
{
    CheckPtr(__LINE__);

    if (index >= elem_count || index < 0 || (elem_count == 0))
        return false;
    else
        return true;
}

#endif