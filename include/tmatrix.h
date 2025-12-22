// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDYNAMICMATRIX_H__
#define __TDYNAMICMATRIX_H__

#include <iostream>
#include <functional>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class T>
class TDynamicVector
{
protected:
    T* pVector;
    int Size; // размер вектора

public:
    typedef function<T(size_t)> AllocatorFunc;
    TDynamicVector(int s = 1, AllocatorFunc fnAlloc = nullptr);
    TDynamicVector(const TDynamicVector& v); // конструктор копирования
    ~TDynamicVector();
    int GetSize() { return Size; } // размер вектора
    T& operator[](int pos); // доступ
    bool operator==(const TDynamicVector& v) const noexcept; // сравнение
    bool operator!=(const TDynamicVector& v) const noexcept; // сравнение
    TDynamicVector& operator=(const TDynamicVector& v); // присваивание

    // скалярные операции
    TDynamicVector  operator+(const T& val);   // прибавить скаляр
    TDynamicVector  operator-(const T& val);   // вычесть скаляр
    TDynamicVector  operator*(const T& val);   // умножить на скаляр

    // векторные операции
    TDynamicVector  operator+(const TDynamicVector& v);     // сложение
    TDynamicVector  operator-(const TDynamicVector& v);     // вычитание
    T  operator*(const TDynamicVector& v);     // скалярное произведение

    // ввод-вывод
    friend istream& operator>>(istream& in, TDynamicVector& v)
    {
        for (int i = 0; i < v.Size; i++)
            in >> v.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TDynamicVector& v)
    {
        for (int i = 0; i < v.Size; i++)
            out << v.pVector[i] << ' ';
        return out;
    }
};

template <class T>
TDynamicVector<T>::TDynamicVector(int s = 1, AllocatorFunc fnAlloc = nullptr) : Size(s)
{
    if (s < 0 || s > MAX_VECTOR_SIZE) { throw exception("Invalid size"); }

    pVector = new T[Size]();
    if (fnAlloc)
    {
        for (size_t i = 0; i < Size; i++)
        {
            pVector[i] = fnAlloc(i);
        }
    }
} /*-------------------------------------------------------------------------*/

template <class T> //конструктор копирования
TDynamicVector<T>::TDynamicVector(const TDynamicVector<T>& v) : Size(v.Size)
{
    pVector = new T[Size]();
    for (int i = 0; i < Size; i++) { pVector[i] = v.pVector[i]; }
} /*-------------------------------------------------------------------------*/

template <class T>
TDynamicVector<T>::~TDynamicVector()
{
    delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class T> // доступ
T& TDynamicVector<T>::operator[](int pos)
{
    if (pos < 0 || pos > Size) { throw exception("Invalid position"); }

    return pVector[pos];
} /*-------------------------------------------------------------------------*/

template <class T> // сравнение
bool TDynamicVector<T>::operator==(const TDynamicVector& v) const noexcept
{
    if (Size != v.Size) { return false; }

    for (int i = 0; i < Size; i++)
    {
        if (pVector[i] != v.pVector[i]) { return false; }
    }

    return true;
} /*-------------------------------------------------------------------------*/

template <class T> // сравнение
bool TDynamicVector<T>::operator!=(const TDynamicVector& v) const noexcept
{
    return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class T> // присваивание
TDynamicVector<T>& TDynamicVector<T>::operator=(const TDynamicVector& v)
{
    if (this != &v)
    {
        if (Size != v.Size)
        {
            Size = v.Size;
            delete[] pVector;
            pVector = new T[Size];
        }
        copy(v.pVector, v.pVector + Size, pVector);
    }
    return *this;
} /*-------------------------------------------------------------------------*/

template <class T> // прибавить скаляр
TDynamicVector<T> TDynamicVector<T>::operator+(const T& val)
{
    TDynamicVector<T> temp(Size);

    for (int i = 0; i < Size; i++) { temp[i] = pVector[i] + val; }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class T> // вычесть скаляр
TDynamicVector<T> TDynamicVector<T>::operator-(const T& val)
{
    TDynamicVector<T> temp(Size);

    for (int i = 0; i < Size; i++) { temp[i] = pVector[i] - val; }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class T> // умножить на скаляр
TDynamicVector<T> TDynamicVector<T>::operator*(const T& val)
{
    TDynamicVector<T> temp(Size);

    for (int i = 0; i < Size; i++) { temp[i] = pVector[i] * val; }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class T> // сложение
TDynamicVector<T> TDynamicVector<T>::operator+(const TDynamicVector<T>& v)
{
    if (Size != v.Size) { throw exception("Invalid size"); }

    TDynamicVector<T> temp(Size);

    for (int i = 0; i < Size; i++) { temp.pVector[i] = pVector[i] + v.pVector[i]; }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class T> // вычитание
TDynamicVector<T> TDynamicVector<T>::operator-(const TDynamicVector<T>& v)
{
    if (Size != v.Size) { throw exception("Invalid size"); }

    TDynamicVector<T> temp(Size);

    for (int i = 0; i < Size; i++) { temp.pVector[i] = pVector[i] - v.pVector[i]; }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class T> // скалярное произведение
T TDynamicVector<T>::operator*(const TDynamicVector<T>& v)
{
    if (Size != v.Size) { throw exception("Invalid size"); }

    int result = 0;
    for (int i = 0; i < Size; i++) { result += pVector[i] * v.pVector[i]; }

    return result;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
public:
    TDynamicMatrix(int s = 5);
    TDynamicMatrix(const TDynamicMatrix& mt);                    // копирование
    TDynamicMatrix(const TDynamicVector<TDynamicVector<T> >& mt); // преобразование типа
    bool operator==(const TDynamicMatrix& mt) const;      // сравнение
    bool operator!=(const TDynamicMatrix& mt) const;      // сравнение
    TDynamicMatrix& operator= (const TDynamicMatrix& mt);        // присваивание
    TDynamicMatrix  operator+ (const TDynamicMatrix& mt);        // сложение
    TDynamicMatrix  operator- (const TDynamicMatrix& mt);        // вычитание

    // ввод / вывод
    friend istream& operator>>(istream& in, TDynamicMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            in >> mt.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TDynamicMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            out << mt.pVector[i] << endl;
        return out;
    }
};

template <class T>
TDynamicMatrix<T>::TDynamicMatrix(int s) : TDynamicVector<TDynamicVector<T> >(s, [s](size_t i) { return TDynamicVector<T>(s); })
{
    if (s < 0 || s > MAX_MATRIX_SIZE) { throw exception("Invalid size"); }
} /*-------------------------------------------------------------------------*/

template <class T> // конструктор копирования
TDynamicMatrix<T>::TDynamicMatrix(const TDynamicMatrix<T>& mt) :
    TDynamicVector<TDynamicVector<T> >(mt) {}

template <class T> // конструктор преобразования типа
TDynamicMatrix<T>::TDynamicMatrix(const TDynamicVector<TDynamicVector<T> >& mt) :
    TDynamicVector<TDynamicVector<T> >(mt) {}

template <class T> // сравнение
bool TDynamicMatrix<T>::operator==(const TDynamicMatrix<T>& mt) const
{
    if (Size != mt.Size) { return false; }

    for (int i = 0; i < Size; i++)
    {
        if (pVector[i] != mt.pVector[i]) { return false; }
    }
    return true;
} /*-------------------------------------------------------------------------*/

template <class T> // сравнение
bool TDynamicMatrix<T>::operator!=(const TDynamicMatrix<T>& mt) const
{
    return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class T> // присваивание
TDynamicMatrix<T>& TDynamicMatrix<T>::operator=(const TDynamicMatrix<T>& mt)
{
    if (this != &mt) { TDynamicVector<TDynamicVector<T>>::operator=(mt); }

    return *this;
} /*-------------------------------------------------------------------------*/

template <class T> // сложение
TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicMatrix<T>& mt)
{
    if (Size != mt.Size) { throw exception("Invalid size"); }

    TDynamicMatrix<T> result(Size);

    for (int i = 0; i < Size; i++) { result.pVector[i] = pVector[i] + mt.pVector[i]; }
    return result;
} /*-------------------------------------------------------------------------*/

template <class T> // вычитание
TDynamicMatrix<T> TDynamicMatrix<T>::operator-(const TDynamicMatrix<T>& mt)
{
    if (Size != mt.Size) { throw exception("Invalid size"); }

    TDynamicMatrix<T> result(Size);

    for (int i = 0; i < Size; i++) { result.pVector[i] = pVector[i] - mt.pVector[i]; }
    return result;
}

#endif