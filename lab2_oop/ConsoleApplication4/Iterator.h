#pragma once
#include <iostream>

#include "BaseIter.h"
#include "errors.h"

template<typename T>
class Vector;

template<typename T>
class Iterator : public BaseIter
{
public:
    #pragma region Constructurs
    Iterator(const Iterator<T>& iter) noexcept;
    Iterator(const Vector<T>& vec) noexcept;
    ~Iterator();
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
    bool operator<=(const Iterator<T>& b) const;
    bool operator<(const Iterator<T>& b) const;
    bool operator>=(const Iterator<T>& b) const;
    bool operator>(const Iterator<T>& b) const;
    bool operator==(const Iterator<T>& b) const;
    bool operator!=(const Iterator<T>& b) const;
    #pragma endregion
    #pragma region UnaryOperators
    Iterator<T>& operator++();
    Iterator<T> operator++(int);
    Iterator<T>& operator--();
    Iterator<T> operator--(int);
    #pragma endregion 
    #pragma region MathOperators
    template <typename T2>
    Iterator<T>& operator+=(const T2 n);
    template <typename T2>
    Iterator<T> operator+(const T2 n) const;
    template <typename T2>
    Iterator<T>& operator-=(const T2 n);
    template <typename T2>
    Iterator<T> operator-(const T2 n) const;
    #pragma endregion

    Iterator<T>& operator=(const Iterator<T>& iter) noexcept;

    void CheckPtr(int line) const;
    bool CheckIter() const;
    operator bool() const;


private:
    std::weak_ptr<T[]> ptr;
protected:
    T* GetCurPtr() const;
};

#include "Iterator.cpp"