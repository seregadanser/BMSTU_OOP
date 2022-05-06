#pragma once
#include <iostream>

#include "BaseIter.h"
#include "errors.h"

template<typename T>
class Vector;

template<typename T>
class ConstIterator : BaseIter
{
public:

	#pragma region Constructurs
	ConstIterator(const ConstIterator<T>& iter) noexcept;
	ConstIterator(const Vector<T>& vec) noexcept;
	~ConstIterator();
	#pragma endregion

	const T& operator[](const int offset) const;
	const T* operator->() const;
	const T& operator*() const;

#pragma region LogicalOperators
    bool operator<=(const ConstIterator<T>& b) const;
    bool operator<(const ConstIterator<T>& b) const;
    bool operator>=(const ConstIterator<T>& b) const;
    bool operator>(const ConstIterator<T>& b) const;
    bool operator==(const ConstIterator<T>& b) const;
    bool operator!=(const ConstIterator<T>& b) const;
#pragma endregion
#pragma region UnaryOperators
    ConstIterator<T>& operator++();
    ConstIterator<T> operator++(int);
    ConstIterator<T>& operator--();
    ConstIterator<T> operator--(int);
#pragma endregion 
#pragma region MathOperators
    template <typename T2>
    ConstIterator<T>& operator+=(const T2 n);
    template <typename T2>
    ConstIterator<T> operator+(const T2 n) const;
    template <typename T2>
    ConstIterator<T>& operator-=(const T2 n);
    template <typename T2>
    ConstIterator<T> operator-(const T2 n) const;
#pragma endregion

    ConstIterator<T>& operator=(const ConstIterator<T>& iter) noexcept;

    void CheckPtr(int line) const;
    bool CheckIter() const;
    operator bool() const;

private:
    std::weak_ptr<T[]> ptr;
protected:
    T* GetCurPtr() const;
};


#include "ConstIterator.cpp"

