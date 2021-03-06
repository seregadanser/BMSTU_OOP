#ifndef RITER_CPP
#define RITER_CPP

#include "ReversIterator.h"

template<typename T>
void ReversIterator<T>::CheckPtr(int line) const
{
    time_t cur_time = time(NULL);
    if (index >= elem_count || index < 0)
        throw IndexError(ctime(&cur_time), __FILE__, line, "CheckPtr");

    if (ptr.expired())
        throw NoPtr(ctime(&cur_time), __FILE__, line, "CheckPtr");
}

template<typename T>
bool ReversIterator<T>::CheckIter() const
{
    if (index >= elem_count || index < 0 || (elem_count == 0))
        return false;
    else
        return true;
}

template<typename T>
T* ReversIterator<T>::GetCurPtr() const
{
    std::shared_ptr<T[]> copy_ptr = ptr.lock();
    return copy_ptr.get() + index;
}

#pragma region Constructurs
template<typename T>
ReversIterator<T>::ReversIterator(const Vector<T>& vec) noexcept : BaseIter()
{
    elem_count = vec.elem_count;
    ptr = vec.data_list;
}

template<typename T>
ReversIterator<T>::ReversIterator(const ReversIterator<T>& iter) noexcept : BaseIter(iter)
{
    ptr = iter.ptr;
}

template <typename T>
ReversIterator<T>::~ReversIterator() = default;
#pragma endregion

#pragma region PointerOperators
template<typename T>
T& ReversIterator<T>::operator*()
{
    CheckPtr(__LINE__);

    // std::shared_ptr<T> copy_ptr = ptr.lock();
    return *GetCurPtr();
}

template<typename T>
const T& ReversIterator<T>::operator*() const
{
    CheckPtr(__LINE__);

    //std::shared_ptr<T> copy_ptr = ptr.lock();
    return *GetCurPtr();
}

template<typename T>
T* ReversIterator<T>::operator->()
{
    CheckPtr(__LINE__);

    return GetCurPtr();
}

template<typename T>
const T* ReversIterator<T>::operator->() const
{
    CheckPtr(__LINE__);

    return GetCurPtr();
}

template<typename T>
T& ReversIterator<T>::operator[](const int offset)
{
    CheckPtr(__LINE__);
    return *(GetCurPtr() + offset);
}

template<typename T>
const T& ReversIterator<T>::operator[](const int offset) const
{
    CheckPtr(__LINE__);
    return *(GetCurPtr() + offset);
}

#pragma endregion

#pragma region LogicalOperators
template<typename T>
bool ReversIterator<T>::operator<=(const ReversIterator<T>&b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() <= b.GetCurPtr();
}

template<typename T>
bool ReversIterator<T>::operator<(const ReversIterator<T>&b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() < b.GetCurPtr();
}

template<typename T>
bool ReversIterator<T>::operator>=(const ReversIterator<T>&b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() >= b.GetCurPtr();
}

template<typename T>
bool ReversIterator<T>::operator>(const ReversIterator<T>&b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() > b.GetCurPtr();
}

template<typename T>
bool ReversIterator<T>::operator==(const ReversIterator<T>&b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() == b.GetCurPtr();
}

template<typename T>
bool ReversIterator<T>::operator!=(const ReversIterator<T>&b) const
{
    CheckPtr(__LINE__);
    b.CheckPtr(__LINE__);

    return GetCurPtr() != b.GetCurPtr();
}
#pragma endregion

#pragma region UnaryOperators
template<typename T>
ReversIterator<T> ReversIterator<T>::operator++(int)
{
    CheckPtr(__LINE__);
    ReversIterator<T> tmp(*this);
    --(*this);

    return tmp;
}

template<typename T>
ReversIterator<T>& ReversIterator<T>::operator++()
{
    CheckPtr(__LINE__);
    --index;

    return *this;
}

template<typename T>
ReversIterator<T> ReversIterator<T>::operator--(int)
{
    CheckPtr(__LINE__);
    ReversIterator<T> tmp(*this);
    ++(*this);

    return tmp;
}

template<typename T>
ReversIterator<T>& ReversIterator<T>::operator--()
{
    CheckPtr(__LINE__);
    ++index;

    return *this;
}
#pragma endregion 

#pragma region MathOperators
template<typename T>
template <typename T2>
ReversIterator<T>& ReversIterator<T>::operator+=(const T2 n)
{
    CheckPtr(__LINE__);
    ptr -= n;

    return *this;
}

template<typename T>
template <typename T2>
ReversIterator<T> ReversIterator<T>::operator+(const T2 n) const
{
    CheckPtr(__LINE__);
    ReversIterator<T> iter(*this);
    iter.index -= n;

    return iter;
}

template<typename T>
template <typename T2>
ReversIterator<T>& ReversIterator<T>::operator-=(const T2 n)
{
    CheckPtr(__LINE__);
    index += n;

    return *this;
}

template<typename T>
template <typename T2>
ReversIterator<T> ReversIterator<T>::operator-(const T2 n) const
{
    CheckPtr(__LINE__);

    ReversIterator<T> iter(*this);
    iter.index += n;

    return iter;
}

#pragma endregion

template<typename T>
ReversIterator<T>& ReversIterator<T>::operator=(const ReversIterator<T>&iter) noexcept
{
    CheckPtr(__LINE__);

    ptr.reset(iter.ptr);
    elem_count = iter.elem_count;
    index = iter.index;
    return *this;
}

template<typename T>
ReversIterator<T>::operator bool() const
{
    CheckPtr(__LINE__);

    if (index >= elem_count || index < 0 || (elem_count == 0))
        return false;
    else
        return true;
}


#endif