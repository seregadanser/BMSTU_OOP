#pragma once
#include <iostream>
#include <cstdarg>
#include <cstdlib>
#include <stdarg.h>
#include <cmath>
#include <corecrt_math_defines.h>
#include <memory>
#include <stdexcept>

#include "BaseVector.h"
#include "Iterator.h"
#include "ConstIterator.h"
#include "ReversIterator.h"
#include "ConstReversIterator.h"
#include "errors.h"

#define EPS 1e-5

template<typename T>
class Vector : public BaseVector
{
public:
    friend class Iterator<T>;
    friend class ConstIterator<T>;
    friend class ReversIterator<T>;
    friend class ConstReversIterator<T>;

    #pragma region Constructors
    Vector();
    explicit Vector(int num_elements);
    Vector(int num_elements, const T* vec);
    Vector(int num_elements, T vec, ...);
    explicit Vector(const Vector<T>& vec);
    Vector(std::initializer_list<T> args);
    Vector(Vector<T>&& vector) noexcept;
    template <typename IT>
    Vector(IT begin, IT end);
    ~Vector();
    #pragma endregion

    #pragma region IndexOperators
    T& operator[](int index);
    const T& operator[](int index) const;
    bool SetElement(int index, const T& vec);
    T& GetElement(int index);
    const T& GetElement(int index) const;
    #pragma endregion

    #pragma region MathOperators
    #pragma region Operators
        #pragma region Summ
        Vector<T> operator +(const Vector<T>&) const;
        Vector<T>& operator +=(const Vector<T>&);
        Vector<T> operator+(const T&) const;
        Vector<T>& operator+=(const T&);
        template <typename T2>
        decltype(auto) operator+(const Vector<T2>&) const;
        template <typename T2>
        Vector<T>& operator+=(const Vector<T2>&);
        template <typename T2>
        decltype(auto) operator+(const T2&) const;
        template <typename T2>
        Vector<T>& operator+=(const T2&);
        #pragma endregion
        #pragma region Diff
        Vector<T> operator -(const Vector<T>&) const;
        Vector<T>& operator -=(const Vector<T>&);
        Vector<T> operator-(const T& num) const;
        Vector<T>& operator-=(const T& num);
        template <typename T2>
        decltype(auto) operator-(const Vector<T2>&) const;
        template <typename T2>
        Vector<T>& operator-=(const Vector<T2>&);
        template <typename T2>
        decltype(auto) operator-(const T2&) const;
        template <typename T2>
        Vector<T>& operator-=(const T2&);
        #pragma endregion 
        #pragma region Mul
        Vector<T>& operator *=(const T& mult);
        Vector<T> operator*(const T& num) const;
        template <typename T2>
        Vector<T>& operator*=(const T2& num);
        template <typename T2>
        decltype(auto) operator*(const T2& num) const;
        #pragma endregion
        #pragma region Div
        Vector<T>& operator /=(const T& div);
        Vector<T> operator/(const T& num) const;
        template <typename T2>
        Vector<T>& operator/=(const T2& num);
        template <typename T2>
        decltype(auto) operator/(const T2& num) const;
        #pragma endregion
        T operator *(const Vector<T>& vec) const;//скал€рное 
        template <typename T2>
        decltype(auto) operator*(const Vector<T2>& vector) const;
        #pragma region VecProd
        Vector<T> operator^(const Vector<T>& vec) const;//векторное
        Vector<T>& operator^=(const Vector<T>& vector);
        template <typename T2>
        decltype(auto) operator^(const Vector<T2>& vector) const;
        template <typename T2>
        Vector<T>& operator^=(const Vector<T2>& vector);
        #pragma endregion
        Vector<T> operator -() const;
    #pragma endregion
    #pragma region Functions
        #pragma region Summ
        Vector<T> VecSum(const Vector<T>& vector) const;
        Vector<T>& EqVecSum(const Vector<T>& vector);
        Vector<T> ByNumSum(const T& num) const;
        Vector<T>& EqByNumSum(const T& num);
        template <typename T2>
        decltype(auto) VecSum(const Vector<T2>& vector) const;
        template <typename T2>
        Vector<T>& EqVecSum(const Vector<T2>& vector);
        template <typename T2>
        decltype(auto) ByNumSum(const T2& num) const;
        template <typename T2>
        Vector<T>& EqByNumSum(const T2& num);
        #pragma endregion
        #pragma region Diff
        Vector<T> VecDiff(const Vector<T>& vector) const;
        Vector<T>& EqVecDiff(const Vector<T>& vector);
        Vector<T> ByNumDiff(const T& num) const;
        Vector<T>& EqByNumDiff(const T& num);
        template <typename T2>
        decltype(auto) VecDiff(const Vector<T2>& vector) const;
        template <typename T2>
        Vector<T>& EqVecDiff(const Vector<T2>& vector);
        template <typename T2>
        decltype(auto) ByNumDiff(const T2& num) const;
        template <typename T2>
        Vector<T>& EqByNumDiff(const T2& num);
        #pragma endregion 
        #pragma region Mul
        Vector<T> ByNumMul(const T& num) const;
        Vector<T>& EqByNumMul(const T& num);
        template <typename T2>
        decltype(auto) ByNumMul(const T2& num) const;
        template <typename T2>
        Vector<T>& EqByNumMul(const T2& num);
        #pragma endregion
        #pragma region Div
        Vector<T> ByNumDiv(const T& num) const;
        Vector<T>& EqByNumDiv(const T& num);
        template <typename T2>
        decltype(auto) ByNumDiv(const T2& num) const;
        template <typename T2>
        Vector<T>& EqByNumDiv(const T2& num);
        #pragma endregion
        T scalarProd(const Vector<T>& vector) const;
        template <typename T2>
        decltype(auto) scalarProd(const Vector<T2>& vector) const;
        #pragma region VecProd
        Vector<T> vectorProd(const Vector<T>& vector) const;
        Vector<T>& eqVectorProd(const Vector<T>& vector);
        template <typename T2>
        decltype(auto) vectorProd(const Vector<T2>& vector) const;
        template <typename T2>
        Vector<T>& eqVectorProd(const Vector<T2>& vector);
        #pragma endregion
        Vector<T> neg() const;
    #pragma endregion
    #pragma endregion

    #pragma region Logical
    bool IsCollinearity(const Vector<T>&) const;
    bool IsOrthogonality(const Vector<T>&) const;
    template <typename T2>
    bool IsCollinearity(const Vector<T2>&) const;
    template <typename T2>
    bool IsOrthogonality(const Vector<T2>&) const;
    template <typename T2>
    bool operator ==(const Vector<T2>&) const;
    template <typename T2>
    bool IsEqual(const Vector<T2>& vector) const;
    template <typename T2>
    bool operator !=(const Vector<T2>&) const;
    template <typename T2>
    bool IsNotEqual(const Vector<T2>& vector) const;
    bool IsZero() const;
    bool IsSingle() const;
    #pragma endregion

    #pragma region Math
    T Len() const;
    double Angle(const Vector<T>&) const;
    template <typename T2>
    double Angle(const Vector<T2>&) const;
    Vector<T> GetSingle() const;
    #pragma endregion

    #pragma region Iterators
    Iterator<T> begin() noexcept;
    Iterator<T> end() noexcept;
    ConstIterator<T> begin() const noexcept;
    ConstIterator<T> end() const noexcept;
    ConstIterator<T> cbegin() const noexcept;
    ConstIterator<T> cend() const noexcept;

    ReversIterator<T> rbegin() noexcept;
    ReversIterator<T> rend() noexcept;
    ConstReversIterator<T> rbegin() const noexcept;
    ConstReversIterator<T> rend() const noexcept;
    ConstReversIterator<T> crbegin() const noexcept;
    ConstReversIterator<T> crend() const noexcept;
    #pragma endregion

    int Size() const;

    Vector<T>& operator =(const Vector<T>& vec);
    Vector<T>& operator =(Vector<T>&& vec) noexcept;
    Vector<T>& operator =(std::initializer_list<T> args);

private:
    std::shared_ptr<T[]> data_list;

protected:
    void AllocMem(int);
    T SumElements();
    void difference_vectors(Vector<T>& result, const Vector<T>& vec1, const Vector<T>& vec2) const;
    void sum_vectors(Vector<T>& result, const Vector<T>& vec1, const Vector<T>& vec2) const;
    void mult_vectors(Vector<T>& result, const Vector<T>& vec1, const Vector<T>& vec2) const;
    void CheckSise(int len1, int len2, int line) const;
    void CheckLen(int len1, int line, std::string oper) const;
    void CheckLen(int len1,int len2, int line, std::string oper) const;
};

template<typename Type>
std::ostream& operator <<(std::ostream& os, const Vector<Type>& vec)
{
    ConstIterator<Type> iter = vec.begin();

    if (!iter.CheckIter())
    {
        os << "Empty vec";
        return os;
    }

    os << '(';
    for (; iter; iter++)
        os << *iter << ' ';
    os << ')';

    return os;
}


#include "Vector.cpp"
