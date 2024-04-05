#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <utility>

class S21Matrix {
 public:
  S21Matrix() noexcept;  // Default constructor
  S21Matrix(int rows, int cols);
  // Параметризированный конструктор с количеством строк и столбцов
  S21Matrix(const S21Matrix& other);  // Конструктор копирования
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;  // Конструктор переноса
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  ~S21Matrix() noexcept;  // Destructor

  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int new_rows);
  void SetCols(int new_cols);

  // functions

  bool EqMatrix(const S21Matrix& other) const noexcept;
  // Проверяет матрицы на равенство между собой

  void SumMatrix(const S21Matrix& other);
  // Прибавляет вторую матрицы к текущей

  void SubMatrix(const S21Matrix& other);
  // Вычитает из текущей матрицы другую

  void MulNumber(const double num) noexcept;
  // Умножает текущую матрицу на число

  void MulMatrix(const S21Matrix& other);
  // Умножает текущую матрицу на вторую

  S21Matrix Transpose() const;
  // Создает новую транспонированную матрицу из текущей и возвращает ее

  S21Matrix CalcComplements() const;
  // Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее

  double Determinant() const;
  // Вычисляет и возвращает определитель текущей матрицы

  S21Matrix InverseMatrix() const;
  // Вычисляет и возвращает обратную матрицу

  void Free() noexcept;
  void SetAnyNum(double num) noexcept;
  void SetRundomNum();
  S21Matrix GetMinorMatrix(const int skip_row, const int skip_column) const;

  // operators

  bool operator==(const S21Matrix& other) const noexcept;
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator*(double number) const noexcept;
  S21Matrix& operator*=(double number);
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix& operator*=(const S21Matrix& other);
  const double& operator()(int row, int col) const;
  double& operator()(int row, int col);
  friend S21Matrix operator*(double number, const S21Matrix& matrix) noexcept;

 private:
  // Attributes
  int rows_, cols_;
  double* matrix_;
  const double kEpsilon = 1e-7;
};

#endif  // S21_MATRIX_OOP_H_