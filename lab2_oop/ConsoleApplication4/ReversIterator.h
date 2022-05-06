#pragma once
#include "BaseIter.h"

#include "BaseIter.h"
#include "errors.h"

template<typename T>
class Vector;

template<typename T>
class ReversIterator : public BaseIter
{
public:
#pragma region Constructurs
    ReversIterator(const ReversIterator<T>& iter) noexcept;
    ReversIterator(const Vector<T>& vec) noexcept;
    ~ReversIterator();
#pragma endregion
#pragma region PointerOperators
    T& operator*();
    const T& operator*() const;
    T* operator->();
    const T* operator->() const;
    T& operator[](const int offset);
    const T& operator[](const int offset) const;
#pragma endregion

#pragma region LogicalOperators
    bool operator<=(const ReversIterator<T>& b) const;
    bool operator<(const ReversIterator<T>& b) const;
    bool operator>=(const ReversIterator<T>& b) const;
    bool operator>(const ReversIterator<T>& b) const;
    bool operator==(const ReversIterator<T>& b) const;
    bool operator!=(const ReversIterator<T>& b) const;
#pragma endregion
#pragma region UnaryOperators
    ReversIterator<T>& operator++();
    ReversIterator<T> operator++(int);
    ReversIterator<T>& operator--();
    ReversIterator<T> operator--(int);
#pragma endregion 
#pragma region MathOperators
    template <typename T2>
    ReversIterator<T>& operator+=(const T2 n);
    template <typename T2>
    ReversIterator<T> operator+(const T2 n) const;
    template <typename T2>
    ReversIterator<T>& operator-=(const T2 n);
    template <typename T2>
    ReversIterator<T> operator-(const T2 n) const;
#pragma endregion

    ReversIterator<T>& operator=(const ReversIterator<T>& iter) noexcept;

    void CheckPtr(int line) const;
    bool CheckIter() const;
    operator bool() const;


private:
    std::weak_ptr<T[]> ptr;
protected:
    T* GetCurPtr() const;
};

#include "ReversIterator.cpp"
