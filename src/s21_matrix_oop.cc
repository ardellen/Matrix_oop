#include "./s21_matrix_oop.h"

// Default constructor
S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

// Параметризированный конструктор с количеством строк и столбцов
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0) {
    throw std::length_error("Matrix size must be greater or equal than 0");
  }
  matrix_ = new double[rows_ * cols_]{};
}

// Конструктор копирования
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(new double[rows_ * cols_]) {
  std::copy(other.matrix_, other.matrix_ + cols_ * rows_, matrix_);
}

// Конструктор переноса
S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

// Destructor
S21Matrix::~S21Matrix() noexcept { Free(); }

// functions

// Проверяет матрицы на равенство между собой
bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (std::abs(other.matrix_[cols_ * i + j] - matrix_[cols_ * i + j]) >
          kEpsilon)
        return false;
    }
  }
  return true;
}

// Прибавляет вторую матрицы к текущей
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("Incorrect matrix size for function Sum");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) += other(i, j);
    }
  }
}

// Вычитает из текущей матрицы другую
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("Incorrect matrix size for function Sub");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) -= other(i, j);
    }
  }
}

// Умножает текущую матрицу на число
void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) *= num;
    }
  }
}

// Умножает текущую матрицу на вторую
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::logic_error("Incorrect matrix size for function Mul");
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      for (int k = 0; k < cols_; ++k) {
        result(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = std::move(result);
}

// Создает новую транспонированную матрицу из текущей и возвращает ее
S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(j, i) = (*this)(i, j);
    }
  }
  return result;
}

// Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее
S21Matrix S21Matrix::CalcComplements() const {
  if (cols_ != rows_)
    throw std::logic_error(
        "Incorrect matrix size for function CalcComplements");
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor_matrix = GetMinorMatrix(i, j);
      result(i, j) = minor_matrix.Determinant();
      if ((i + j) % 2 != 0) {
        result(i, j) = -result(i, j);
      }
    }
  }
  return result;
}

// Вычисляет и возвращает определитель текущей матрицы
double S21Matrix::Determinant() const {
  if (cols_ != rows_)
    throw std::logic_error("Incorrect matrix size for function Determinant");
  double determinant = 1;
  int size = rows_;
  S21Matrix tmp{*this};
  for (int i = 0; i < size; i++) {
    int i_max = i;
    for (int i2 = i + 1; i2 < size; i2++) {
      if (std::abs(tmp(i2, i)) > std::abs(tmp(i_max, i))) i_max = i2;
    }
    if (std::abs(tmp(i_max, i)) < kEpsilon) return 0.0;
    for (int m = 0; m < size; m++) {
      double swap = tmp(i, m);
      tmp(i, m) = tmp(i_max, m);
      tmp(i_max, m) = swap;
    }
    determinant *= tmp(i, i);
    if (i != i_max) determinant = -determinant;
    if (tmp(i, i) == 0) return 0.0;  // pup
    for (int k = i + 1; k < size; k++) {
      double divide = tmp(k, i) / tmp(i, i);
      for (int j = i; j < size; j++) {
        tmp(k, j) -= divide * tmp(i, j);
      }
    }
  }
  return determinant;
}

// Вычисляет и возвращает обратную матрицу
S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::logic_error("Incorrect matrix size for Inverse");
  }
  double determinant_matrix = Determinant();
  if (std::abs(determinant_matrix) < kEpsilon) {
    throw std::logic_error("Matrix determinant must be non-zero for Inverse");
  }

  return Transpose().CalcComplements() * (1.0 / determinant_matrix);
}

void S21Matrix::Free() noexcept {
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

// operators

// `+`      | Сложение двух матриц  | различная размерность матриц |
S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix tmp(*this);
  tmp.SumMatrix(other);
  return tmp;
}

// | `-`   | Вычитание одной матрицы из другой | различная размерность матриц |
S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix tmp(*this);
  tmp.SubMatrix(other);
  return tmp;
}

// | `*`  | Умножение матриц и умножение матрицы на число | число столбцов
// первой матрицы не равно числу строк второй матрицы |
S21Matrix S21Matrix::operator*(double number) const noexcept {
  S21Matrix tmp(*this);
  tmp.MulNumber(number);
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix tmp(*this);
  tmp.MulMatrix(other);
  return tmp;
}

S21Matrix operator*(double number, const S21Matrix& matrix) noexcept {
  S21Matrix tmp = matrix * number;
  return tmp;
}

//| `==`  | Проверка на равенство матриц (`EqMatrix`) |
bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  return EqMatrix(other);
}

// | `=`  | Присвоение матрице значений другой матрицы
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  S21Matrix copy(other);
  *this = std::move(copy);
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
  return *this;
}

// | `+=`  | Присвоение сложения (`SumMatrix`)   | различная размерность матриц
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  (*this).SumMatrix(other);
  return *this;
}

// | `-=`  | Присвоение разности (`SubMatrix`) | различная размерность матриц

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

// | `*=`  | Присвоение умножения (`MulMatrix`/`MulNumber`)
S21Matrix& S21Matrix::operator*=(double number) {
  MulNumber(number);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

// (int i, int j) | Индексация по элементам матрицы (строка, колонка)
const double& S21Matrix::operator()(int row, int col) const {
  if (row > rows_ || col > cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input for (), index is out of range.");
  }
  return matrix_[row * cols_ + col];
}

double& S21Matrix::operator()(int row, int col) {
  if (row > rows_ || col > cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input for (), index is out of range.");
  }
  return matrix_[row * cols_ + col];
}

int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

void S21Matrix::SetAnyNum(double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) = num;
    }
  }
}

void S21Matrix::SetRundomNum() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) = rand() % 1000;
    }
  }
}

void S21Matrix::SetRows(int new_rows) {
  if (new_rows < 0) {
    throw std::length_error("Matrix rows count must be non-negative");
  }
  if (new_rows != rows_) {
    S21Matrix tmp(new_rows, cols_);
    int min = std::min(rows_, new_rows);
    for (int i = 0; i < min; ++i) {
      for (int j = 0; j < cols_; ++j) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(tmp);
  }
}

void S21Matrix::SetCols(int new_cols) {
  if (new_cols < 0) {
    throw std::length_error("Matrix columns count must be non-negative");
  }
  if (new_cols != cols_) {
    S21Matrix tmp(rows_, new_cols);
    int min = std::min(cols_, new_cols);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < min; ++j) {
        tmp(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(tmp);
  }
}

S21Matrix S21Matrix::GetMinorMatrix(const int skip_row,
                                    const int skip_column) const {
  S21Matrix result{rows_ - 1, cols_ - 1};
  for (int i = 0, i2 = 0; i < rows_; i++) {
    if (i == skip_row) continue;
    for (int j = 0, j2 = 0; j < cols_; j++) {
      if (j == skip_column) continue;
      result(i2, j2) = (*this)(i, j);
      j2++;
    }
    i2++;
  }
  return result;
}
