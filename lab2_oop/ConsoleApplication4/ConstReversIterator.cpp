#ifndef CRITER_CPP
#define CRITER_CPP

#include "ConstReversIterator.h"

template<typename T>
void ConstReversIterator<T>::CheckPtr(int line) const
{
    time_t cur_time = time(NULL);
    if (index >= elem_count || index < 0)
        throw IndexError(ctime(&cur_time), __FILE__, line, "CheckPtr");

    if (ptr.expired())
        throw NoPtr(ctime(&cur_time), __FILE__, line, "CheckPtr");
}

template<typename T>
bool ConstReversIterator<T>::CheckIter() const
{
    if (index >= elem_count || index < 0 || (elem_count == 0))
        return false;
    else
        return true;
}

template<typename T>
T* ConstReversIterator<T>::GetCurPtr() const
{
    std::shared_ptr<T[]> copy_ptr = ptr.lock();
    return copy_ptr.get() + index;
}

#pragma region Constructurs
template<typename T>
ConstReversIterator<T>::ConstReversIterator(const Vector<T>& vec) noexcept : BaseIter()
{
    elem_count = vec.elem_count;
    ptr = vec.data_list;
}

template<typename T>
ConstReversIterator<T>::ConstReversIterator(const ConstReversIterator<T>& iter) noexcept : BaseIter(iter)
{
    ptr = iter.ptr;
}

template <typename T>
ConstReversIterator<T>::~ConstReversIterator() = default;
#pragma endregion

#pragma region PointerOperators

template<typename T>
const T& ConstReversIterator<T>::operator*() const
{
    CheckPtr(__LINE__);

    //std::shared_ptr<T> copy_ptr = ptr.lock();
    return *GetCurPtr();
}


template<typename T>
const T* ConstReversIterator<T>::operator->() const
{
    CheckPtr(__LINE__);

    return GetCurPtr();
}


template<typename T>
const T& ConstReversIterator<T>::operator[](const int offset) const
{
    CheckPtr(__LINE__);
    return *(GetCurPtr() + offset);
}

#pragma endregion

#pragma region LogicalOperators
template<typename T>
bool ConstReversIterator<T>::operator<=(const ConstReversIterator<T>&b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() <= b.GetCurPtr();
}

template<typename T>
bool ConstReversIterator<T>::operator<(const ConstReversIterator<T>&b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() < b.GetCurPtr();
}

template<typename T>
bool ConstReversIterator<T>::operator>=(const ConstReversIterator<T>&b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() >= b.GetCurPtr();
}

template<typename T>
bool ConstReversIterator<T>::operator>(const ConstReversIterator<T>&b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() > b.GetCurPtr();
}

template<typename T>
bool ConstReversIterator<T>::operator==(const ConstReversIterator<T>&b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() == b.GetCurPtr();
}

template<typename T>
bool ConstReversIterator<T>::operator!=(const ConstReversIterator<T>&b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() != b.GetCurPtr();
}
#pragma endregion

#pragma region UnaryOperators
template<typename T>
ConstReversIterator<T> ConstReversIterator<T>::operator++(int)
{
    CheckPtr(__LINE__);
    ConstReversIterator<T> tmp(*this);
    --(*this);

    return tmp;
}

template<typename T>
ConstReversIterator<T>& ConstReversIterator<T>::operator++()
{
    CheckPtr(__LINE__);
    --index;

    return *this;
}

template<typename T>
ConstReversIterator<T> ConstReversIterator<T>::operator--(int)
{
    CheckPtr(__LINE__);
    ConstReversIterator<T> tmp(*this);
    ++(*this);

    return tmp;
}

template<typename T>
ConstReversIterator<T>& ConstReversIterator<T>::operator--()
{
    CheckPtr(__LINE__);
    ++index;

    return *this;
}
#pragma endregion 

#pragma region MathOperators
template<typename T>
template <typename T2>
ConstReversIterator<T>& ConstReversIterator<T>::operator+=(const T2 n)
{
    CheckPtr(__LINE__);
    ptr -= n;

    return *this;
}

template<typename T>
template <typename T2>
ConstReversIterator<T> ConstReversIterator<T>::operator+(const T2 n) const
{
    CheckPtr(__LINE__);
    ConstReversIterator<T> iter(*this);
    iter.index -= n;

    return iter;
}

template<typename T>
template <typename T2>
ConstReversIterator<T>& ConstReversIterator<T>::operator-=(const T2 n)
{
    CheckPtr(__LINE__);
    index += n;

    return *this;
}

template<typename T>
template <typename T2>
ConstReversIterator<T> ConstReversIterator<T>::operator-(const T2 n) const
{
    CheckPtr(__LINE__);

    ConstReversIterator<T> iter(*this);
    iter.index += n;

    return iter;
}

#pragma endregion

template<typename T>
ConstReversIterator<T>& ConstReversIterator<T>::operator=(const ConstReversIterator<T>&iter) noexcept
{
    CheckPtr(__LINE__);

    ptr.reset(iter.ptr);
    elem_count = iter.elem_count;
    index = iter.index;
    return *this;
}

template<typename T>
ConstReversIterator<T>::operator bool() const
{
    CheckPtr(__LINE__);

    if (index >= elem_count || index < 0 || (elem_count == 0))
        return false;
    else
        return true;
}


#endif