#ifndef VEC_CPP
#define VEC_CPP
#pragma warning(disable : 4996)
#include "Vector.h"
template<typename T>
void Vector<T>::CheckSise(int len1, int len2, int line) const
{
    time_t cur_time = time(NULL);
    if (len1 != len2)
        throw DifferLen(ctime(&cur_time), __FILE__, line, "CheckSize");
}

template<typename T>
void Vector<T>::CheckLen(int len1, int len2, int line, std::string oper) const
{
    time_t cur_time = time(NULL);
    if (len1 <= 0 || len2 <= 0)
        throw NullElemError(ctime(&cur_time), __FILE__,line, oper);
}

template<typename T>
void Vector<T>::CheckLen(int len1, int line, std::string oper) const
{
    time_t cur_time = time(NULL);
    if (len1 <= 0)
        throw NullElemError(ctime(&cur_time), __FILE__, line, oper);
}


inline int maxim(int num1, int num2)
{
    if (num1 >= num2)
        return num1;
    else
        return num2;
}
//Done
#pragma region Iterators
template <typename T>
Iterator<T> Vector<T>::begin() noexcept
{
    return Iterator<T>(*this);
}

template <typename T>
Iterator<T> Vector<T>::end() noexcept
{
    if (is_empty)
        return begin();

    return Iterator<T>(*this) + size;
}

template <typename T>
ConstIterator<T> Vector<T>::cbegin() const noexcept
{
    return ConstIterator<T>(*this);
}

template <typename T>
ConstIterator<T> Vector<T>::cend() const noexcept
{
    if (is_empty())
        return cbegin();

    return ConstIterator<T>(*this) + elem_count;
}

template <typename T>
ConstIterator<T> Vector<T>::begin() const noexcept
{
    return ConstIterator<T>(*this);
}

template <typename T>
ConstIterator<T> Vector<T>::end() const noexcept
{
    if (is_empty())
        return cbegin();

    return ConstIterator<T>(*this) + elem_count;
}

template <typename T>
ReversIterator<T> Vector<T>::rbegin() noexcept
{
    if (is_empty())
        return rend();

    return ReversIterator<T>(*this) - (elem_count- 1);
}

template <typename T>
ReversIterator<T> Vector<T>::rend() noexcept
{
    return ReversIterator<T>(*this) - 1;
}

template <typename T>
ConstReversIterator<T> Vector<T>::rbegin() const noexcept
{
    if (is_empty())
        return crend();

    return ConstReversIterator<T>(*this) - (elem_count - 1);
}

template <typename T>
ConstReversIterator<T> Vector<T>::rend() const noexcept
{
    return ConstReversIterator<T>(*this) - 1;
}

template <typename T>
ConstReversIterator<T> Vector<T>::crbegin() const noexcept
{
    if (is_empty())
        return crend();

    return ConstReversIterator<T>(*this) - (elem_count - 1);
}

template <typename T>
ConstReversIterator<T> Vector<T>::crend() const noexcept
{
    return ConstReversIterator<T>(*this) - 1;
}
#pragma endregion

//Done
#pragma region Constructors

template<typename T>
Vector<T>::~Vector<T>() = default;

template<typename T>
Vector<T>::Vector() : BaseVector(), data_list() {}

template<typename T>
Vector<T>::Vector(int num_elements) : BaseVector(num_elements)
{
    CheckLen(num_elements, __LINE__, "Construct");

    AllocMem(num_elements);

    time_t cur_time = time(NULL);
    if (!data_list)
        throw MemError(ctime(&cur_time), __FILE__, __LINE__, "Construct");

    for (Iterator<T> iter = begin(); iter; iter++)
        *iter = 0;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> elements) : BaseVector(elements.size())
{
    AllocMem(elements.size());

    Iterator<T> iter = begin();

    for (auto elem : elements)
    {
        *(iter) = elem;
        iter++;
    }
}

template<typename T>
Vector<T>::Vector(int num_elements, T vec, ...) : BaseVector(num_elements)
{
    CheckLen(num_elements, __LINE__, "Construct");

    AllocMem(num_elements);

    time_t cur_time = time(NULL);
    if (!data_list)
        throw MemError(ctime(&cur_time), __FILE__, __LINE__, "Construct");

    va_list ap;
    va_start(ap, vec);
    for (Iterator<T> iter = begin(); iter; iter++)
    {
        *iter = vec;
        vec = va_arg(ap, T);
    }
    va_end(ap);
}

template<typename T>
Vector<T>::Vector(int num_elements, const T* vec) : BaseVector(num_elements)
{
    CheckLen(num_elements, __LINE__, "Construct");

    AllocMem(num_elements);

    Iterator<T> iter = begin();
    for (int i = 0; iter; i++, iter++)
        *iter = vec[i];
}

template<typename T>
Vector<T>::Vector(const Vector<T>& vec) : BaseVector(vec.elem_count)
{
    AllocMem(elem_count);

    ConstIterator<T> iter = vec.begin();
    for (Iterator<T> iter_new = begin(); iter_new; iter++, iter_new++)
        *iter_new = *iter;
}

template<typename T>
Vector<T>::Vector(Vector<T>&& vec) noexcept : BaseVector(vec.elem_count)
{
    data_list = vec.data_list;
    vec.data_list.reset();
}

template <typename T>
template <typename IT>
Vector<T>::Vector(IT begin, IT end) : BaseVector()
{
    int len = 0;
    for (auto iter = begin; iter < end; iter++, len++);

    elem_count = len;
    AllocMem(elem_count);
    len = 0;
    for (auto iter = begin; iter < end; iter++, len++)
        data_list[len] = *iter;
}

#pragma endregion

#pragma region IndexOperators
template<typename T>
T& Vector<T>::GetElement(int index)
{
    time_t cur_time = time(NULL);
    if (index < 0 || index >= elem_count)
        throw IndexError(ctime(&cur_time), __FILE__, __LINE__, "GetElement");

    Iterator<T> iter = begin();
    for (int i = 0; i < index; i++, iter++);

    return *iter;
}

template<typename T>
const T& Vector<T>::GetElement(int index) const
{
    time_t cur_time = time(NULL);
    if (index < 0 || index >= elem_count)
        throw  IndexError(ctime(&cur_time), __FILE__, __LINE__, "GetElement");

    //AllocMem(elem_count);
    ConstIterator<T> iter = begin();
    for (int i = 0; i <= index; i++, iter++);

    return *iter;
}

template<typename T>
T& Vector<T>::operator[](int index)
{
    return GetElement(index);
}

template<typename T>
const T& Vector<T>::operator[](int index) const
{
    return GetElement(index);
}

template<typename T>
bool Vector<T>::SetElement(int index, const T& num)
{
    if (index < 0 || index >= elem_count)
        return false;

    GetElement(index) = num;
    return true;
}

#pragma endregion

//Done
#pragma region MathOperators

#pragma region SummOper
template <typename T>
Vector<T> Vector<T>::operator +(const Vector<T>& vec) const
{
    CheckSise(*this.elem_count, vec.elem_count, __LINE__);
    CheckLen(elem_count, vec.elem_count, __LINE__, "+");

    int max_len = maxim(elem_count, vec.elem_count);
    Vector<T> new_vec(max_len);
    sum_vecs(new_vec, *this, vec);

    return new_vec;
}

template <typename T>
template <typename T2>
decltype(auto) Vector<T>::operator+(const Vector<T2>& vec) const
{
    CheckSise(*this.elem_count, vec.elem_count, __LINE__);
    CheckLen(elem_count, vec.elem_count, __LINE__, "+");

    Vector<decltype((*this)[0] + vec[0])> res(maxim(elem_count, vec.elem_count));

    Iterator<decltype((*this)[0] + vec[0])> iter_result = res.begin();
    Iterator<T> iter_vec1 = begin();
    Iterator<T2> iter_vec2 = vec.begin();
    for (int i = 0; iter_result; i++, iter_result++, iter_vec1++, iter_vec2++)
    {
        if (i >= elem_count)
            *iter_result = *iter_vec2;
        else
        {
            if (i >= vec.elem_count)
                *iter_result = *iter_vec1;
            else
                *iter_result = *iter_vec1 + *iter_vec2;
        }
    }
    return res;
}

template <typename T>
Vector<T>& Vector<T>::operator +=(const Vector<T>& vec)
{
    CheckSise(*this.elem_count, vec.elem_count, __LINE__);
    CheckLen(elem_count, vec.elem_count, __LINE__, "+");

    sum_vecs(*this, *this, vec);

    return *this;
}

template <typename T>
template <typename T2>
Vector<T>& Vector<T>::operator +=(const Vector<T2>& vec)
{
    CheckSise(*this.elem_count, vec.elem_count, __LINE__);
    CheckLen(elem_count, vec.elem_count, __LINE__, "+");

    sum_vecs(*this, *this, vec);

    return *this;
}

template <typename T>
Vector<T> Vector<T>::operator+(const T& num) const
{
    CheckSise(elem_count, __LINE__);
    CheckLen(elem_count, __LINE__, "+");

    Vector<T> res(*this);
    Iterator<T> res_iter = res.begin();

    for (; res_iter; res_iter++)
        *res_iter += num;

    return res;
}

template <typename T>
template <typename T2>
decltype(auto) Vector<T>::operator+(const T2& num) const
{
    
    CheckLen(elem_count, __LINE__, "+");

    Vector<decltype((*this)[0] + num)> res(elem_count);
    Iterator<decltype((*this)[0] + num)> res_iter = res.begin();
    Iterator<T> it = begin();
    for (; res_iter; res_iter++)
        *res_iter = num + (*it);

    return res;
}

template <typename T>
Vector<T>& Vector<T>::operator+=(const T& num)
{
   
    CheckLen(elem_count, __LINE__, "+");

    Iterator<T> res_iter = begin();

    for (; res_iter; ++res_iter)
        *res_iter += num;

    return *this;
}

template <typename T>
template <typename T2>
Vector<T>& Vector<T>::operator+=(const T2& num)
{
   
    CheckLen(elem_count, __LINE__, "+");

    Iterator<T> res_iter = begin();

    for (; res_iter; ++res_iter)
        *res_iter += num;

    return *this;
}
#pragma endregion
#pragma region SummFunc
template <typename T>
Vector<T> Vector<T>::VecSum(const Vector<T>& vec) const
{
    return *(this) + vec;
}

template <typename T>
Vector<T> Vector<T>::ByNumSum(const T& num) const
{
    return *(this) + num;
}

template <typename T>
template <typename T2>
decltype(auto) Vector<T>::VecSum(const Vector<T2>& vec) const
{
    return *(this) + vec;
}

template <typename T>
template <typename T2>
decltype(auto) Vector<T>::ByNumSum(const T2& num) const
{
    return *(this) + num;
}

template <typename T>
Vector<T>& Vector<T>::EqVecSum(const Vector<T>& vec)
{
    return *(this) += vec;
}

template <typename T>
Vector<T>& Vector<T>::EqByNumSum(const T& num)
{
    return *(this) += num;
}

template <typename T>
template <typename T2>
Vector<T>& Vector<T>::EqVecSum(const Vector<T2>& vec)
{
    return *(this) += vec;
}

template <typename T>
template <typename T2>
Vector<T>& Vector<T>::EqByNumSum(const T2& num)
{
    return *(this) += num;
}
#pragma endregion

#pragma region DiffOper
template <typename T>
Vector<T> Vector<T>::operator -(const Vector<T>& vec) const
{
    CheckSise(*this.elem_count, vec.elem_count, __LINE__);
    CheckLen(elem_count, vec.elem_count, __LINE__, "-");

    int max_len = maxim(elem_count, vec.elem_count);
    Vector<T> new_vec(max_len);
    difference_vecs(new_vec, *this, vec);

    return new_vec;
}

template <typename T>
template <typename T2>
decltype(auto) Vector<T>::operator-(const Vector<T2>& vec) const
{
    CheckSise(*this.elem_count, vec.elem_count, __LINE__);
    CheckLen(elem_count, vec.elem_count, __LINE__, "-");

    Vector<decltype((*this)[0] + vec[0])> res(maxim(elem_count, vec.elem_count));

    Iterator<decltype((*this)[0] + vec[0])> iter_result = res.begin();
    Iterator<T> iter_vec1 = begin();
    Iterator<T2> iter_vec2 = vec.begin();
    for (int i = 0; iter_result; i++, iter_result++, iter_vec1++, iter_vec2++)
    {
        if (i >= elem_count)
            *iter_result = -*iter_vec2;
        else
        {
            if (i >= vec.elem_count)
                *iter_result = *iter_vec1;
            else
                *iter_result = *iter_vec1 - *iter_vec2;
        }
    }
    return res;
}

template <typename T>
Vector<T>& Vector<T>::operator -=(const Vector<T>& vec)
{
    CheckSise(elem_count, vec.elem_count, __LINE__);
    CheckLen(elem_count, vec.elem_count, __LINE__, "-");

    difference_vectors(*this, *this, vec);

    return *this;
}

template <typename T>
template <typename T2>
Vector<T>& Vector<T>::operator -=(const Vector<T2>& vec)
{
    CheckSise(*this.elem_count, vec.elem_count, __LINE__);
    CheckLen(elem_count, vec.elem_count, __LINE__, "-");

    difference_vecs(*this, *this, vec);

    return *this;
}

template <typename T>
Vector<T> Vector<T>::operator-(const T& num) const
{
    CheckSise(elem_count, elem_count, __LINE__);
    CheckLen(elem_count, __LINE__, "-");

    Vector<T> res(*this);
    Iterator<T> res_iter = res.begin();

    for (; res_iter; ++res_iter)
        *res_iter -= num;

    return res;
}

template <typename T>
template <typename T2>
decltype(auto) Vector<T>::operator-(const T2& num) const
{

    CheckLen(elem_count, __LINE__, "-");

    Vector<decltype((*this)[0] + num)> res(elem_count);
    Iterator<decltype((*this)[0] + num)> res_iter = res.begin();
    Iterator<T> it = begin();
    for (; res_iter; res_iter++)
        *res_iter =  (*it) - num ;

    return res;
}


template <typename T>
Vector<T>& Vector<T>::operator-=(const T& num)
{

    CheckLen(elem_count, __LINE__, "-");

    Iterator<T> res_iter = begin();

    for (; res_iter; ++res_iter)
        *res_iter -= num;

    return *this;
}

template <typename T>
template <typename T2>
Vector<T>& Vector<T>::operator-=(const T2& num)
{
 
    CheckLen(elem_count, __LINE__, "-");

    Iterator<T> res_iter = begin();

    for (; res_iter; ++res_iter)
        *res_iter -= num;

    return *this;
}
#pragma endregion
#pragma region DiffFunc
template <typename T>
Vector<T> Vector<T>::VecDiff(const Vector<T>& vec) const
{
    return *(this) - vec;
}

template <typename T>
Vector<T> Vector<T>::ByNumDiff(const T& num) const
{
    return *(this) - num;
}

template <typename T>
template <typename T2>
decltype(auto) Vector<T>::VecDiff(const Vector<T2>& vec) const
{
    return *(this) - vec;
}

template <typename T>
template <typename T2>
decltype(auto) Vector<T>::ByNumDiff(const T2& num) const
{
    return *(this) - num;
}

template <typename T>
Vector<T>& Vector<T>::EqVecDiff(const Vector<T>& vec)
{
    return *(this) -= vec;
}

template <typename T>
Vector<T>& Vector<T>::EqByNumDiff(const T& num)
{
    return *(this) -= num;
}

template <typename T>
template <typename T2>
Vector<T>& Vector<T>::EqVecDiff(const Vector<T2>& vec)
{
    return *(this) -= vec;
}

template <typename T>
template <typename T2>
Vector<T>& Vector<T>::EqByNumDiff(const T2& num)
{
    return *(this) -= num;
}
#pragma endregion

#pragma region MulOper
template <typename T>
Vector<T> Vector<T>::operator*(const T& num) const
{
    CheckLen(elem_count, __LINE__, "*");

    Vector<T> res(*this);
    Iterator<T> res_iter = res.begin();

    for (; res_iter; ++res_iter)
        *res_iter *= num;

    return res;
}

template<typename T>
Vector<T>& Vector<T>::operator *=(const T& mult)
{
    CheckLen(elem_count, __LINE__, "*");

    Iterator<T> iter = begin();
    for (; iter; iter++)
        *iter *= mult;

    return *this;
}

template <typename T>
template <typename T2>
decltype(auto) Vector<T>::operator*(const T2& num) const
{
    Vector<decltype((*this)[0] * num)> res(elem_count);

    for (int i = 0; i < elem_count; ++i)
        res[i] = (*this)[i] * num;

    return res;
}

template <typename T>
template <typename T2>
Vector<T>& Vector<T>::operator*=(const T2& num)
{
    for (int i = 0; i < elem_count; ++i)
        (*this)[i] *= num;

    return *this;
}
#pragma endregion
#pragma region MulFunc
template <typename T>
Vector<T> Vector<T>::ByNumMul(const T& num) const
{
    return *(this) * num;
}
template <typename T>
Vector<T>& Vector<T>::EqByNumMul(const T& num)
{
    return *(this) *= num;
}
template <typename T>
template <typename T2>
decltype(auto) Vector<T>::ByNumMul(const T2& num) const
{
    return *(this) * num;
}
template <typename T>
template <typename T2>
Vector<T>& Vector<T>::EqByNumMul(const T2& num)
{
    return *(this) *= num;
}
#pragma endregion

#pragma region DivOper
template<typename T>
Vector<T>& Vector<T>::operator /=(const T& div)
{
    time_t cur_time = time(NULL);
    if (!div)
        throw ZerroDivisionError(ctime(&cur_time), __FILE__, __LINE__, "/=");

    T div_new = 1 / div;
    *this *= div_new;

    return *this;
}

template <typename T>
Vector<T> Vector<T>::operator/(const T& div) const
{

    time_t cur_time = time(NULL);
    if (!div)
        throw ZerroDivisionError(ctime(&cur_time), __FILE__, __LINE__, "/");

    Vector<T> res(*this);
    Iterator<T> res_iter = res.begin();

    for (; res_iter; ++res_iter)
        *res_iter /= div;

    return res;
}

template <typename T>
template <typename T2>
decltype(auto) Vector<T>::operator/(const T2& num) const
{
    time_t cur_time = time(NULL);
    if (!num)
        throw ZerroDivisionError(ctime(&cur_time), __FILE__, __LINE__, "/");
    Vector<decltype((*this)[0] * num)> res(elem_count);

    for (int i = 0; i < elem_count; ++i)
        res[i] = (*this)[i] / num;

    return res;
}

template <typename T>
template <typename T2>
Vector<T>& Vector<T>::operator/=(const T2& num)
{

    time_t cur_time = time(NULL);
    if (!num)
        throw ZerroDivisionError(ctime(&cur_time), __FILE__, __LINE__, "/=");

    for (int i = 0; i < elem_count; ++i)
        (*this)[i] /= num;

    return *this;
}

#pragma endregion 
#pragma region DivFunc
template <typename T>
Vector<T> Vector<T>::ByNumDiv(const T& num) const
{
    return *(this) / num;
}
template <typename T>
Vector<T>& Vector<T>::EqByNumDiv(const T& num)
{
    return *(this) /= num;
}
template <typename T>
template <typename T2>
decltype(auto) Vector<T>::ByNumDiv(const T2& num) const
{
    return *(this) / num;
}
template <typename T>
template <typename T2>
Vector<T>& Vector<T>::EqByNumDiv(const T2& num)
{
    return *(this) /= num;
}
#pragma endregion

#pragma region Scalar
template <typename T>
T Vector<T>::operator *(const Vector<T>& vec) const
{
    CheckSise(elem_count, vec.elem_count, __LINE__);
    CheckLen(elem_count,vec.elem_count, __LINE__, "*");

    int max_len = maxim(elem_count, vec.elem_count);
    Vector<T> new_vec(max_len);
    mult_vectors(new_vec, *this, vec);

    return new_vec.SumElements();
}

template <typename T>
template <typename T2>
decltype(auto) Vector<T>::operator *(const Vector<T2>& vec) const
{
    CheckSise(*this.elem_count, vec.elem_count, __LINE__);


    decltype((*this)[0] * vec[0]) sum = 0;

    for (int i = 0; i < elem_count; ++i)
        sum += (*this)[i] * vec[i];

    return sum;
}

template <typename T>
T Vector<T>::scalarProd(const Vector<T>& vec) const
{
    return *(this) * vec;
}

template <typename T>
template <typename T2>
decltype(auto) Vector<T>::scalarProd(const Vector<T2>& vec) const
{
    return *(this) * vec;
}

#pragma endregion

#pragma region VectorProdOper
template <typename T>
Vector<T> Vector<T>::operator^(const Vector<T>& vec) const
{
    CheckSise(elem_count, vec.elem_count, __LINE__);
    CheckLen(elem_count, vec.elem_count, __LINE__, "^");

    Vector<T> res(elem_count);

    for (int i = 0; i < elem_count; ++i)
        res[i] = (*this)[(i + 1) % elem_count] * vec[(i + 2) % elem_count] -
        (*this)[(i + 2) % elem_count] * vec[(i + 1) % elem_count];

    return res;
}

template <typename T>
Vector<T>& Vector<T>::operator^=(const Vector<T>& vec)
{
    CheckSise(elem_count, vec.elem_count, __LINE__);
    CheckLen(elem_count, vec.elem_count, __LINE__, "^");

    Vector<T> tmp(*this);

    for (int i = 0; i < elem_count; ++i)
        (*this)[i] = tmp[(i + 1) % elem_count] * vec[(i + 2) % elem_count] -
        tmp[(i + 2) % elem_count] * vec[(i + 1) % elem_count];

    return *this;
}

template <typename T>
template <typename T2>
decltype(auto) Vector<T>::operator^(const Vector<T2>& vec) const
{
    CheckSise(*this.elem_count, vec.elem_count, __LINE__);
    CheckLen(elem_count, vec.elem_count, __LINE__, "^");

    Vector<decltype((*this)[0] + vec[0])> tmp(elem_count);

    for (int i = 0; i < elem_count; ++i)
        (*this)[i] = tmp[(i + 1) % elem_count] * vec[(i + 2) % elem_count] -
        tmp[(i + 2) % elem_count] * vec[(i + 1) % elem_count];

    return tmp;
}

template <typename T>
template <typename T2>
Vector<T>& Vector<T>::operator^=(const Vector<T2>& vec)
{
    CheckSise(*this.elem_count, vec.elem_count, __LINE__);
    CheckLen(elem_count, vec.elem_count, __LINE__, "^");

    Vector<T> tmp(*this);

    for (int i = 0; i < elem_count; ++i)
        (*this)[i] = tmp[(i + 1) % elem_count] * vec[(i + 2) % elem_count] -
        tmp[(i + 2) % elem_count] * vec[(i + 1) % elem_count];

    return *this;
}
#pragma endregion
#pragma region VectorProdFunc
template <typename T>
Vector<T> Vector<T>::vectorProd(const Vector<T>& vec) const
{
    return *(this) ^ vec;
}
template <typename T>
Vector<T>& Vector<T>::eqVectorProd(const Vector<T>& vec)
{
    return *(this) ^= vec;
}
template <typename T>
template <typename T2>
decltype(auto) Vector<T>::vectorProd(const Vector<T2>& vec) const
{
    return *(this) ^ vec;
}
template <typename T>
template <typename T2>
Vector<T>& Vector<T>::eqVectorProd(const Vector<T2>& vec)
{
    return *(this) ^= vec;
}
#pragma endregion

template <typename T>
Vector<T> Vector<T>::operator -() const
{
    Vector<T> res(*this);
    Iterator<T> iter = res.begin();
    for (; iter; iter++)
        *iter = -(*iter);

    return res;
}

template <typename T>
Vector<T> Vector<T>::neg() const
{
    return -(*this);
}
#pragma endregion

//Done
#pragma region Logical
template <typename T>
template <typename T2>
bool Vector<T>::operator ==(const Vector<T2>& vec) const
{
    int equal = 1;
    if (elem_count != vec.Size())
        return false;
    else
    {
        ConstIterator<T> iter1 = begin();
        ConstIterator<T> iter2 = vec.begin();

        for (; iter1 && equal; iter1++, iter2++)
            if (fabs(*iter1 - *iter2) > EPS)
                equal = 0;
    }
    return equal;
}

template <typename T>
template <typename T2>
bool Vector<T>::operator !=(const Vector<T2>& vec) const
{
    if (*this == vec)
        return false;
    else
        return true;
}

template <typename T>
template <typename T2>
bool Vector<T>::IsEqual(const Vector<T2>& vec) const
{
    return *(this) == vec;
}

template <typename T>
template <typename T2>
bool Vector<T>::IsNotEqual(const Vector<T2>& vec) const
{
    return *(this) != vec;
}

template<typename T>
bool Vector<T>::IsCollinearity(const Vector<T>& vec) const
{
    if (this->Angle(vec) < EPS)
        return true;
    else
        return false;
}

template<typename T>
template<typename T2>
bool Vector<T>::IsCollinearity(const Vector<T2>& vec) const
{
    if (this->Angle(vec) < EPS)
        return true;
    else
        return false;
}

template<typename T>
bool Vector<T>::IsOrthogonality(const Vector<T>& vec) const
{
    if (abs(this->Angle(vec) - 90) < EPS)
        return true;
    else
        return false;
}

template<typename T>
template<typename T2>
bool Vector<T>::IsOrthogonality(const Vector<T2>& vec) const
{
    if (abs(this->Angle(vec) - 90) < EPS)
        return true;
    else
        return false;
}

template<typename T>
bool Vector<T>::IsSingle() const
{
    if (abs(this->Len() - 1) < EPS)
        return true;
    else
        return false;
}

template<typename T>
bool Vector<T>::IsZero() const
{
    if (this->Len() == 0)
        return true;
    else
        return false;
}
#pragma endregion

#pragma region Math
template<typename T>
T Vector<T>::Len(void) const
{
    CheckLen(elem_count, __LINE__, "Len");

    ConstIterator<T> iter = begin();
    double sum = 0;
    for (; iter; iter++)
        sum += (*iter) * (*iter);

    return sqrt(sum);
}

template<typename T>
double Vector<T>::Angle(const Vector<T>& vec) const
{
    time_t cur_time = time(NULL);
    if (!this->Len() || !vec.Len())
        throw ZerroDivisionError(ctime(&cur_time), __FILE__, __LINE__, "Angle");

    double angle = (*this * vec) / (this->Len() * vec.Len());
    return acos(angle) * 180 / M_PI;
}

template<typename T>
template<typename T2>
double Vector<T>::Angle(const Vector<T2>& vec) const
{
    time_t cur_time = time(NULL);
    if (!this->Len() || !vec.Len())
        throw ZerroDivisionError(ctime(&cur_time), __FILE__, __LINE__, "AngleOther");

    double angle = (*this * vec) / (this->Len() * vec.Len());
    return acos(angle) * 180 / M_PI;
}

template<typename T>
Vector<T> Vector<T>::GetSingle() const
{
    Vector<T> new_vec(*this);
    T len = this->Len();

    Iterator<T> iter= new_vec.begin();
    for (; iter; iter++)
        *iter /= len;

    return new_vec;
}
#pragma endregion

template<typename T>
Vector<T>& Vector<T>::operator =(const Vector<T>& vec)
{
    elem_count = vec.elem_count;
    AllocMem(elem_count);

    Iterator<T> iter_new = begin();
    Iterator<T> iter = vec.begin();
    for (; iter_new; iter_new++, iter++)
        *iter_new = *iter;

    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator =(std::initializer_list<T> args)
{
    elem_count = int(args.size());
    AllocMem(elem_count);
    
    Iterator<T> iter = begin();
    for (auto &element : args)
    {
        *iter = element;
        iter++;
    }
    
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& vec) noexcept
{
    elem_count = vec.elem_count;
    data_list = vec.data_list;
    vec.data_list.reset();

    return *this;
}

template <typename T>
void Vector<T>::AllocMem(int num_elements)
{
    data_list.reset();
    std::shared_ptr<T[]> sp_temp(new T[num_elements], std::default_delete<T[]>());
    data_list = sp_temp;
}

template <typename T>
void Vector<T>::difference_vectors(Vector<T>& result, const Vector<T>& vec1, const Vector<T>& vec2) const
{
    Iterator<T> iter_result = result.begin();
    ConstIterator<T> iter_vec1 = vec1.begin();
    ConstIterator<T> iter_vec2 = vec2.begin();
    for (int i = 0; iter_result; i++, iter_result++, iter_vec1++, iter_vec2++)
    {
        if (i >= vec1.elem_count)
            *iter_result = -*iter_vec2;
        else 
        {
            if (i >= vec2.elem_count)
                *iter_result = *iter_vec1;
            else
                *iter_result = *iter_vec1 - *iter_vec2;
        }
    }
}

template <typename T>
void Vector<T>::sum_vectors(Vector<T>& result, const Vector<T>& vec1, const Vector<T>& vec2) const
{
    Iterator<T> iter_result = result.begin();
    Iterator<T> iter_vec1 = vec1.begin();
    Iterator<T> iter_vec2 = vec2.begin();
    for (int i = 0; iter_result; i++, iter_result++, iter_vec1++, iter_vec2++)
    {
        if (i >= vec1.elem_count)
            *iter_result = *iter_vec2;
        else
        {
            if (i >= vec2.elem_count)
                *iter_result = *iter_vec1;
            else
                *iter_result = *iter_vec1 + *iter_vec2;
        }
    }
}

template <typename T>
void Vector<T>::mult_vectors(Vector<T>& result, const Vector<T>& vec1, const Vector<T>& vec2) const
{
    Iterator<T> iter_result = result.begin();
    ConstIterator<T> iter_vec1 = vec1.begin();
    ConstIterator<T> iter_vec2 = vec2.begin();
    for (int i = 0; iter_result; i++, iter_result++, iter_vec1++, iter_vec2++)
    {
        if (i >= vec1.elem_count || i >= vec2.elem_count)
            *iter_result = 0;
        else
            *iter_result = *iter_vec1 * *iter_vec2;
    }
}

template<typename T>
T Vector<T>::SumElements()
{
    CheckLen(elem_count, __LINE__, "SummElem");

    Iterator<T> iter = begin();
    T sum = 0;
    for (; iter; iter++)
        sum += *iter;

    return sum;
}

template<typename T>
int Vector<T>::Size() const
{
    return elem_count;
} 

#endif