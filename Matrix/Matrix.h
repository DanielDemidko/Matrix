#pragma once
#include <vector>
#include <sstream>
#include <iterator>


template<typename T> std::ostream &operator<<(std::ostream &out, const std::vector<T> &vec)
{
    std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator<T>(out, " "));
    return out;
}


// Класс представляет собой матрицу. Индексация ведётся с единицы
/// Согласно ТЗ реализованно три пункта: 1 - вывод, 2 - транспонирование, 3 - умножение на матрицу
template<typename T> class Matrix
{
private:
    std::vector<std::vector<T>> Table;

public:
    /// Реализуем вывод согласно ТЗ(1)
    friend std::ostream& operator<<(std::ostream &out, const Matrix &self)
    {
        for (const auto &vec : self.Table)
        {
            out << vec << std::endl;
        }
        return out;
    }

    friend std::istream& operator>>(std::istream &in, Matrix &self)
    {
        for (auto &vec : self.Table)
        {
            for (auto &i : vec)
            {
                in >> i;
            }
        }
        return in;
    }

    T &operator()(const size_t m, const size_t n)
    {
        return Table[m - 1][n - 1];
    }

    const T &operator()(const size_t m, const size_t n) const
    {
        return Table[m - 1][n - 1];
    }

    // Число столбцов
    size_t Columns() const
    {
        return Table.empty() ? 0 : Table.front().size();
    }

    // Число строк
    size_t Rows() const
    {
        return Table.size();
    }

    /// Реализуем транспонирование согласно ТЗ(2)
    Matrix Transpose() const
    {
        Matrix result(Columns(), Rows());
        for (size_t i = 1; i <= result.Rows(); ++i)
        {
            for (size_t j = 1; j <= result.Columns(); ++j)
            {
                result(i, j) = operator()(j, i);
            }
        }
        return result;
    }

    bool CanMultiplied(const Matrix &other) const
    {
        return Columns() == other.Rows();
    }

    explicit Matrix(const size_t rows, const size_t columns) : Table(rows, std::vector<T>(columns))
    {
    }

    explicit Matrix(const size_t rows) : Matrix(rows, rows)
    {
    }
};


template<typename T> T Sum(const size_t i, const size_t j, const Matrix<T> &a, const Matrix<T> &b)
{
    T result{};
    for (size_t r = 1; r <= a.Columns(); ++r)
    {
        result += (a(i, r) * b(r, j));
    }
    return result;
}


/// Реализуем умножение на другую матрицу согласно ТЗ(3)
template<typename T> Matrix<T> operator*(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.Columns() != b.Rows())
    {
        throw std::runtime_error("Matrix operator*(a, b): \"a.Colums() != b.Rows()\"");
    }
    Matrix<T> result(a.Rows(), b.Columns());
    for (size_t i = 1; i <= result.Rows(); ++i)
    {
        for (size_t j = 1; j <= result.Columns(); ++j)
        {
            result(i, j) = Sum(i, j, a, b);
        }
    }
    return result;
}