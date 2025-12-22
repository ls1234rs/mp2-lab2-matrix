// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>
#include <functional>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class T>
class TVector
{
protected:
    T* pVector;
    int Size; // размер вектора

public:
    typedef function<T(size_t)> AllocatorFunc;
    TVector(int s = 1, AllocatorFunc fnAlloc = nullptr);
    TVector(const TVector& v); // конструктор копирования
    ~TVector();
    int GetSize() { return Size; } // размер вектора
    T& operator[](int pos); // доступ
    bool operator==(const TVector& v) const noexcept; // сравнение
    bool operator!=(const TVector& v) const noexcept; // сравнение
    TVector& operator=(const TVector& v); // присваивание

    // скалярные операции
    TVector  operator+(const T& val);   // прибавить скаляр
    TVector  operator-(const T& val);   // вычесть скаляр
    TVector  operator*(const T& val);   // умножить на скаляр

    // векторные операции
    TVector  operator+(const TVector& v);     // сложение
    TVector  operator-(const TVector& v);     // вычитание
    T  operator*(const TVector& v);     // скалярное произведение

    // ввод-вывод
    friend istream& operator>>(istream& in, TVector& v)
    {
        for (int i = 0; i < v.Size; i++)
            in >> v.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TVector& v)
    {
        for (int i = 0; i < v.Size; i++)
            out << v.pVector[i] << ' ';
        return out;
    }
};

template <class T>
TVector<T>::TVector(int s = 1, AllocatorFunc fnAlloc = nullptr) : Size(s)
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
TVector<T>::TVector(const TVector<T>& v) : Size(v.Size)
{
    pVector = new T[Size]();
    for (int i = 0; i < Size; i++) { pVector[i] = v.pVector[i]; }
} /*-------------------------------------------------------------------------*/

template <class T>
TVector<T>::~TVector()
{
    delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class T> // доступ
T& TVector<T>::operator[](int pos)
{
    if (pos < 0 || pos > Size) { throw exception("Invalid position"); }

    return pVector[pos];
} /*-------------------------------------------------------------------------*/

template <class T> // сравнение
bool TVector<T>::operator==(const TVector& v) const noexcept
{
    if (Size != v.Size) { return false; }

    for (int i = 0; i < Size; i++)
    {
        if (pVector[i] != v.pVector[i]) { return false; }
    }

    return true;
} /*-------------------------------------------------------------------------*/

template <class T> // сравнение
bool TVector<T>::operator!=(const TVector& v) const noexcept
{
    return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class T> // присваивание
TVector<T>& TVector<T>::operator=(const TVector& v)
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
TVector<T> TVector<T>::operator+(const T& val)
{
    TVector<T> temp(Size);

    for (int i = 0; i < Size; i++) { temp[i] = pVector[i] + val; }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class T> // вычесть скаляр
TVector<T> TVector<T>::operator-(const T& val)
{
    TVector<T> temp(Size);

    for (int i = 0; i < Size; i++) { temp[i] = pVector[i] - val; }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class T> // умножить на скаляр
TVector<T> TVector<T>::operator*(const T& val)
{
    TVector<T> temp(Size);

    for (int i = 0; i < Size; i++) { temp[i] = pVector[i] * val; }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class T> // сложение
TVector<T> TVector<T>::operator+(const TVector<T>& v)
{
    if (Size != v.Size) { throw exception("Invalid size"); }

    TVector<T> temp(Size);

    for (int i = 0; i < Size; i++) { temp.pVector[i] = pVector[i] + v.pVector[i]; }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class T> // вычитание
TVector<T> TVector<T>::operator-(const TVector<T>& v)
{
    if (Size != v.Size) { throw exception("Invalid size"); }

    TVector<T> temp(Size);

    for (int i = 0; i < Size; i++) { temp.pVector[i] = pVector[i] - v.pVector[i]; }
    return temp;
} /*-------------------------------------------------------------------------*/

template <class T> // скалярное произведение
T TVector<T>::operator*(const TVector<T>& v)
{
    if (Size != v.Size) { throw exception("Invalid size"); }

    int result = 0;
    for (int i = 0; i < Size; i++) { result += pVector[i] * v.pVector[i]; }

    return result;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class T>
class TMatrix : public TVector<TVector<T>>
{
public:
    TMatrix(int s = 5);
    TMatrix(const TMatrix& mt);                    // копирование
    TMatrix(const TVector<TVector<T> >& mt); // преобразование типа
    bool operator==(const TMatrix& mt) const;      // сравнение
    bool operator!=(const TMatrix& mt) const;      // сравнение
    TMatrix& operator= (const TMatrix& mt);        // присваивание
    TMatrix  operator+ (const TMatrix& mt);        // сложение
    TMatrix  operator- (const TMatrix& mt);        // вычитание

    // ввод / вывод
    friend istream& operator>>(istream& in, TMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            in >> mt.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            out << mt.pVector[i] << endl;
        return out;
    }
};

template <class T>
TMatrix<T>::TMatrix(int s) : TVector<TVector<T> >(s, [s](size_t i) { return TVector<T>(s); })
{
    if (s < 0 || s > MAX_MATRIX_SIZE) { throw exception("Invalid size"); }
} /*-------------------------------------------------------------------------*/

template <class T> // конструктор копирования
TMatrix<T>::TMatrix(const TMatrix<T>& mt) :
    TVector<TVector<T> >(mt) {}

template <class T> // конструктор преобразования типа
TMatrix<T>::TMatrix(const TVector<TVector<T> >& mt) :
    TVector<TVector<T> >(mt) {}

template <class T> // сравнение
bool TMatrix<T>::operator==(const TMatrix<T>& mt) const
{
    if (Size != mt.Size) { return false; }

    for (int i = 0; i < Size; i++)
    {
        if (pVector[i] != mt.pVector[i]) { return false; }
    }
    return true;
} /*-------------------------------------------------------------------------*/

template <class T> // сравнение
bool TMatrix<T>::operator!=(const TMatrix<T>& mt) const
{
    return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class T> // присваивание
TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T>& mt)
{
    if (this != &mt) { TVector<TVector<T>>::operator=(mt); }

    return *this;
} /*-------------------------------------------------------------------------*/

template <class T> // сложение
TMatrix<T> TMatrix<T>::operator+(const TMatrix<T>& mt)
{
    if (Size != mt.Size) { throw exception("Invalid size"); }

    TMatrix<T> result(Size);

    for (int i = 0; i < Size; i++) { result.pVector[i] = pVector[i] + mt.pVector[i]; }
    return result;
} /*-------------------------------------------------------------------------*/

template <class T> // вычитание
TMatrix<T> TMatrix<T>::operator-(const TMatrix<T>& mt)
{
    if (Size != mt.Size) { throw exception("Invalid size"); }

    TMatrix<T> result(Size);

    for (int i = 0; i < Size; i++) { result.pVector[i] = pVector[i] - mt.pVector[i]; }
    return result;
}

#endif

