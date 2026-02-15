// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//

#ifndef TMATRIX_DYNAMIC_CONTAINERS_H
#define TMATRIX_DYNAMIC_CONTAINERS_H

// Заголовок с шаблонными классами: динамический вектор и квадратная матрица.
// Вектор — массив T в куче; матрица — вектор векторов (наследование).

#include <iostream>
#include <cassert>

using namespace std;

// Ограничения на размеры (защита от переполнения памяти)
const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Вектор переменной длины в куче (шаблон по типу элемента)
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;   // количество элементов
    T* pMem;     // указатель на массив в куче

public:
    // Конструктор по размеру (элементы инициализируются по умолчанию)
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size exceeds MAX_VECTOR_SIZE");
        pMem = new T[sz]();
    }
    // Конструктор из готового массива (копирование)
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "array pointer must not be null");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    // Копирующий конструктор
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        for (size_t i = 0; i < sz; i++) {
            pMem[i] = v.pMem[i];
        }
    }
    // Перемещающий конструктор (забирает память у v)
    TDynamicVector(TDynamicVector&& v) noexcept
        : sz(v.sz), pMem(v.pMem)
    {
        v.sz = 0;
        v.pMem = nullptr;
    }
    // Деструктор — освобождаем массив
    ~TDynamicVector()
    {
        delete[] pMem;
    }
    // Копирующее присваивание
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v) {
            delete[] pMem;
            sz = v.sz;
            pMem = new T[sz];
            for (size_t i = 0; i < sz; i++) {
                pMem[i] = v.pMem[i];
            }
        }
        return *this;
    }
    // Перемещающее присваивание
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v) {
            delete[] pMem;
            pMem = v.pMem;
            sz = v.sz;
            v.sz = 0;
            v.pMem = nullptr;
        }
        return *this;
    }

    // Размер вектора и прямой доступ к данным
    size_t size() const noexcept { return sz; }
    T* data() const noexcept { return pMem; }

    // Индексация без проверки границ
    T& operator[](size_t ind) { return pMem[ind]; }
    const T& operator[](size_t ind) const { return pMem[ind]; }
    // Доступ с проверкой (бросает исключение при выходе за границы)
    T& at(size_t ind)
    {
        if (ind >= sz)
            throw out_of_range("Out of range");
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("Out of range");
        return pMem[ind];
    }

    // Сравнение на равенство (поэлементно)
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz)
            return false;
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i])
                return false;
        }
        return true;
    }
    // Неравенство — обратное к равенству
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // Сложение/вычитание/умножение на скаляр (поэлементно)
    TDynamicVector operator+(T val) const
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; i++) {
            result[i] = pMem[i] + val;
        }
        return result;
    }
    TDynamicVector operator-(T val) const
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; i++) {
            result[i] = pMem[i] - val;
        }
        return result;
    }
    TDynamicVector operator*(T val) const
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; i++) {
            result[i] = pMem[i] * val;
        }
        return result;
    }

    // Сложение и вычитание векторов (размеры должны совпадать)
    TDynamicVector operator+(const TDynamicVector& v) const
    {
        if (sz != v.sz)
            throw std::invalid_argument("Vectors sizes are not equal");
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; i++) {
            result[i] = pMem[i] + v.pMem[i];
        }
        return result;
    }
    TDynamicVector operator-(const TDynamicVector& v) const
    {
        if (sz != v.sz)
            throw std::invalid_argument("Vectors sizes are not equal");
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; i++) {
            result[i] = pMem[i] - v.pMem[i];
        }
        return result;
    }
    // Скалярное произведение векторов
    T operator*(const TDynamicVector& v) const
    {
        if (sz != v.sz)
            throw std::invalid_argument("Vectors sizes are not equal");
        T result = 0;
        for (size_t i = 0; i < sz; i++) {
            result += pMem[i] * v.pMem[i];
        }
        return result;
    }

    // Обмен содержимым двух векторов
    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // Ввод/вывод (последовательность элементов через пробел)
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' ';
        return ostr;
    }
};


// Квадратная матрица: массив векторов в динамической памяти
// Наследуется от вектора векторов (каждая строка — TDynamicVector<T>)
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    // Конструктор: создаём матрицу s x s, каждая строка — вектор длины s
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s > MAX_MATRIX_SIZE)
            throw std::out_of_range("Matrix size exceeds MAX_MATRIX_SIZE");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    // Проброс операторов и методов из базового класса
    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::at;
    using TDynamicVector<TDynamicVector<T>>::size;

    // Сравнение матриц поэлементно
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz)
            return false;
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                if (pMem[i][j] != m.pMem[i][j])
                    return false;
            }
        }
        return true;
    }

    // Умножение матрицы на скаляр (все элементы умножаются на val)
    TDynamicMatrix<T> operator*(const T& val)
    {
        TDynamicMatrix<T> result(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                result[i][j] = pMem[i][j] * val;
            }
        }
        return result;
    }

    // Умножение матрицы на вектор (размер вектора должен совпадать с размером матрицы)
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size())
            throw std::invalid_argument("Matrix and vector dimensions don't match for multiplication");
        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                result[i] += pMem[i][j] * v[j];
            }
        }
        return result;
    }

    // Сложение матриц (размеры должны совпадать)
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw std::invalid_argument("Matrix dimensions don't match for addition");
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                result[i][j] = pMem[i][j] + m.pMem[i][j];
            }
        }
        return result;
    }
    // Вычитание матриц
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw std::invalid_argument("Matrix dimensions don't match for subtraction");
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                result[i][j] = pMem[i][j] - m.pMem[i][j];
            }
        }
        return result;
    }
    // Умножение матриц (строка на столбец, тройной цикл)
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw std::invalid_argument("Matrix dimensions don't match for multiplication");
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t k = 0; k < sz; k++) {
                T temp = pMem[i][k];
                for (size_t j = 0; j < sz; j++) {
                    result[i][j] += temp * m.pMem[k][j];
                }
            }
        }
        return result;
    }

    // Ввод матрицы (элементы построчно)
    friend istream& operator>>(istream& istr, TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; i++) {
            for (size_t j = 0; j < m.sz; j++) {
                istr >> m[i][j];
            }
        }
        return istr;
    }

    // Вывод матрицы (каждая строка на новой строке, элементы через пробел)
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; i++) {
            for (size_t j = 0; j < m.sz; j++) {
                ostr << m[i][j];
                if (j < m.sz - 1)
                    ostr << ' ';
            }
            ostr << '\n';
        }
        return ostr;
    }
};

#endif
