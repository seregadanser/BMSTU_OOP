#pragma once
#include "BaseIter.h"

#include "errors.h"

template<typename T>
class Vector;

template<typename T>
class ConstReversIterator : public BaseIter
{
public:
#pragma region Constructurs
    ConstReversIterator(const ConstReversIterator<T>& iter) noexcept;
    ConstReversIterator(const Vector<T>& vec) noexcept;
    ~ConstReversIterator();
#pragma endregion
#pragma region PointerOperators
    const T& operator*() const;
    const T* operator->() const;
    const T& operator[](const int offset) const;
#pragma endregion

#pragma region LogicalOperators
    bool operator<=(const ConstReversIterator<T>& b) const;
    bool operator<(const ConstReversIterator<T>& b) const;
    bool operator>=(const ConstReversIterator<T>& b) const;
    bool operator>(const ConstReversIterator<T>& b) const;
    bool operator==(const ConstReversIterator<T>& b) const;
    bool operator!=(const ConstReversIterator<T>& b) const;
#pragma endregion
#pragma region UnaryOperators
    ConstReversIterator<T>& operator++();
    ConstReversIterator<T> operator++(int);
    ConstReversIterator<T>& operator--();
    ConstReversIterator<T> operator--(int);
#pragma endregion 
#pragma region MathOperators
    template <typename T2>
    ConstReversIterator<T>& operator+=(const T2 n);
    template <typename T2>
    ConstReversIterator<T> operator+(const T2 n) const;
    template <typename T2>
    ConstReversIterator<T>& operator-=(const T2 n);
    template <typename T2>
    ConstReversIterator<T> operator-(const T2 n) const;
#pragma endregion

    ConstReversIterator<T>& operator=(const ConstReversIterator<T>& iter) noexcept;

    void CheckPtr(int line) const;
    bool CheckIter() const;
    operator bool() const;


private:
    std::weak_ptr<T[]> ptr;
protected:
    T* GetCurPtr() const;
};

#include "ConstReversIterator.cpp"
