#include "s21_test.h"

TEST(BaseConstructor, test_1) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);
}

TEST(ParamConstructor, test_1) {
  S21Matrix matrix(2, 3);
  matrix(1, 0) = 555;
  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 3);
  EXPECT_EQ(matrix(1, 0), 555);
}

TEST(ParamConstructor, test_2) {
  EXPECT_ANY_THROW(S21Matrix matrix(-2, 3));
  EXPECT_ANY_THROW(S21Matrix matrix_2(2, -3));
}

TEST(CopyConstructor, test_1) {
  S21Matrix first(3, 2);
  first.SetRundomNum();
  S21Matrix second(first);
  EXPECT_EQ(second.EqMatrix(first), true);
}

TEST(CopyConstructor, test_2) {
  S21Matrix first(0, 0);
  S21Matrix second(first);
  EXPECT_EQ(second.EqMatrix(first), true);
}

TEST(MoveConstructor, test_1) {
  S21Matrix first(3, 2);
  first.SetRundomNum();
  S21Matrix expect(first);
  S21Matrix second = std::move(first);
  EXPECT_EQ(second.EqMatrix(expect), true);
}

TEST(Accessor, test_1) {
  S21Matrix first(5, 8);
  EXPECT_NEAR(first.GetRows(), 5, 1e-7);
  EXPECT_NEAR(first.GetCols(), 8, 1e-7);
}

TEST(Mutator, test_1) {
  S21Matrix first(5, 8);
  first.SetAnyNum(10);
  first.SetRows(3);
  first.SetCols(2);
  S21Matrix expect(3, 2);
  expect.SetAnyNum(10);
  EXPECT_EQ(expect.EqMatrix(first), true);
}

TEST(Mutator, test_2) {
  S21Matrix first(2, 1);
  first.SetAnyNum(10);
  first.SetRows(3);
  first.SetCols(2);
  S21Matrix expect(3, 2);
  expect.SetAnyNum(10);
  expect(0, 1) = 0.;
  expect(1, 1) = 0.;
  expect(2, 0) = 0.;
  expect(2, 1) = 0.;
  EXPECT_EQ(expect.EqMatrix(first), true);
}

TEST(Mutator, test_3) {
  S21Matrix first(2, 1);
  first.SetAnyNum(10);
  EXPECT_ANY_THROW(first.SetRows(-3));
  EXPECT_ANY_THROW(first.SetCols(-2));
}

TEST(EqMatrix, test1) {
  S21Matrix first(3, 3);
  first.SetAnyNum(2);
  S21Matrix second(3, 3);
  second.SetAnyNum(2);
  EXPECT_EQ(first.EqMatrix(second), true);
}

TEST(EqMatrix, test2) {
  S21Matrix first(3, 3);
  first.SetAnyNum(1);

  S21Matrix second(3, 3);
  second.SetAnyNum(2);

  EXPECT_EQ(first.EqMatrix(second), false);
}

TEST(SumFunction, test_1) {
  S21Matrix first(3, 3);
  first.SetAnyNum(1);
  S21Matrix second(3, 3);
  second.SetAnyNum(2);
  first.SumMatrix(second);
  for (int i = 0; i < first.GetRows(); i++) {
    for (int j = 0; j < first.GetCols(); j++) {
      EXPECT_NEAR(first(i, j), 3., 1e-7);
    }
  }
}

TEST(SumFunction, test_2) {
  S21Matrix first(3, 3);
  first.SetAnyNum(1);
  S21Matrix second(2, 2);
  second.SetAnyNum(1);

  EXPECT_ANY_THROW(first.SumMatrix(second));
}

TEST(SubFunction, test_1) {
  S21Matrix first(3, 3);
  first.SetAnyNum(1);
  S21Matrix second(3, 3);
  second.SetAnyNum(2);
  first.SubMatrix(second);
  for (int i = 0; i < first.GetRows(); i++) {
    for (int j = 0; j < first.GetCols(); j++) {
      EXPECT_NEAR(first(i, j), -1., 1e-7);
    }
  }
}

TEST(SubFunction, test_2) {
  S21Matrix first(3, 3);
  S21Matrix second(2, 2);
  EXPECT_ANY_THROW(first.SubMatrix(second));
}

TEST(MulNumber, test_1) {
  S21Matrix first(3, 3);
  double value = 2;
  first.SetAnyNum(7);
  first.MulNumber(value);
  for (int i = 0; i < first.GetRows(); i++) {
    for (int j = 0; j < first.GetCols(); j++) {
      EXPECT_NEAR(first(i, j), 14., 1e-7);
    }
  }
}

TEST(MulMatrix, test_1) {
  S21Matrix first(2, 3);
  first.SetAnyNum(2.);
  S21Matrix second(3, 2);
  second.SetAnyNum(4.);
  first.MulMatrix(second);
  S21Matrix expect(2, 2);
  expect.SetAnyNum(24.);
  EXPECT_EQ(first.EqMatrix(expect), true);
}

TEST(MulMatrix, test_3) {
  S21Matrix first(3, 3);
  first.SetAnyNum(6);
  S21Matrix second(3, 3);
  second.SetAnyNum(3);
  S21Matrix expect(3, 3);
  expect.SetAnyNum(486);
  first.MulMatrix(second);
  first.MulMatrix(second);
  EXPECT_EQ(expect.EqMatrix(first), true);
}

TEST(MulMatrix, test_2) {
  S21Matrix first(2, 3);
  S21Matrix second(5, 2);
  EXPECT_ANY_THROW(first.MulMatrix(second));
}

TEST(Transpose, test_1) {
  S21Matrix first(2, 3);
  S21Matrix expect(3, 2);
  S21Matrix got(3, 2);
  first(0, 0) = 1;
  first(0, 1) = 2;
  first(0, 2) = 3;
  first(1, 0) = 9;
  first(1, 1) = 7;
  first(1, 2) = 5;

  expect(0, 0) = 1;
  expect(0, 1) = 9;
  expect(1, 0) = 2;
  expect(1, 1) = 7;
  expect(2, 0) = 3;
  expect(2, 1) = 5;

  got = first.Transpose();

  EXPECT_EQ(got.EqMatrix(expect), true);
}

TEST(Determinant, test_1) {
  S21Matrix matrix(2, 3);
  EXPECT_ANY_THROW(matrix.Determinant());
}

TEST(Determinant, test_2) {
  S21Matrix matrix(0, 0);
  double value = matrix.Determinant();
  EXPECT_NEAR(value, 1, 1e-7);
}

TEST(Determinant, test_3) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 4;
  double value = matrix.Determinant();
  EXPECT_NEAR(value, 4, 1e-7);
}

TEST(Determinant, test_4) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 4;
  matrix(0, 1) = -5;
  matrix(1, 0) = 9;
  matrix(1, 1) = 15;
  double value = matrix.Determinant();
  EXPECT_NEAR(value, 105, 1e-7);
}

TEST(Determinant, test_5) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = -5;
  matrix(0, 2) = 9;
  matrix(1, 0) = 15;
  matrix(1, 1) = 4;
  matrix(1, 2) = 3;
  matrix(2, 0) = 2;
  matrix(2, 1) = 6;
  matrix(2, 2) = 7;
  double value = matrix.Determinant();
  EXPECT_NEAR(value, 1243, 1e-7);
}

TEST(Determinant, test_9) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = -9;
  matrix(0, 1) = 5;
  matrix(0, 2) = 4;
  matrix(1, 0) = 6;
  matrix(1, 1) = 3;
  matrix(1, 2) = 8;
  matrix(2, 0) = 4;
  matrix(2, 1) = 8;
  matrix(2, 2) = 5;
  double value = matrix.Determinant();
  EXPECT_NEAR(value, 595, 1e-7);
}

TEST(CalcComplements, test_1) {
  S21Matrix matrix(2, 3);
  EXPECT_ANY_THROW(matrix.CalcComplements());
}

TEST(CalcComplements, test_2) {
  S21Matrix matrix(1, 1);
  S21Matrix got(0, 0);
  got = matrix.CalcComplements();
  EXPECT_NEAR(got(0, 0), 1, 1e-7);
}

TEST(CalcComplements, test_3) {
  S21Matrix matrix(3, 3);
  S21Matrix expect(3, 3);
  S21Matrix got(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 0;
  matrix(1, 1) = 4;
  matrix(1, 2) = 2;
  matrix(2, 0) = 5;
  matrix(2, 1) = 2;
  matrix(2, 2) = 1;

  expect(0, 0) = 0;
  expect(0, 1) = 10;
  expect(0, 2) = -20;
  expect(1, 0) = 4;
  expect(1, 1) = -14;
  expect(1, 2) = 8;
  expect(2, 0) = -8;
  expect(2, 1) = -2;
  expect(2, 2) = 4;

  got = matrix.CalcComplements();

  EXPECT_EQ(got.EqMatrix(expect), true);
}

TEST(InverseMatrix, test_1_1) {
  S21Matrix matrix(0, 0);
  S21Matrix got(0, 0);
  EXPECT_EQ(got.EqMatrix(matrix), true);
}

TEST(InverseMatrix, test_2) {
  S21Matrix matrix(3, 3);

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  matrix(2, 2) = 9;

  EXPECT_ANY_THROW(matrix.InverseMatrix());
}

TEST(InverseMatrix, test_3) {
  S21Matrix matrix(3, 3);
  S21Matrix expect(3, 3);
  S21Matrix got(3, 3);

  matrix(0, 0) = 2;
  matrix(0, 1) = 5;
  matrix(0, 2) = 7;
  matrix(1, 0) = 6;
  matrix(1, 1) = 3;
  matrix(1, 2) = 4;
  matrix(2, 0) = 5;
  matrix(2, 1) = -2;
  matrix(2, 2) = -3;

  expect(0, 0) = 1;
  expect(0, 1) = -1;
  expect(0, 2) = 1;
  expect(1, 0) = -38;
  expect(1, 1) = 41;
  expect(1, 2) = -34;
  expect(2, 0) = 27;
  expect(2, 1) = -29;
  expect(2, 2) = 24;

  got = matrix.InverseMatrix();
  EXPECT_EQ(got.EqMatrix(expect), true);
}

TEST(InverseMatrix, test_4) {
  S21Matrix matrix(3, 3);
  S21Matrix expect(3, 3);
  S21Matrix got(3, 3);

  matrix(0, 0) = 2;
  matrix(0, 1) = 1;
  matrix(0, 2) = 1;
  matrix(1, 0) = 1;
  matrix(1, 1) = 1;
  matrix(1, 2) = 1;
  matrix(2, 0) = 1;
  matrix(2, 1) = 1;
  matrix(2, 2) = 2;

  expect(0, 0) = 1;
  expect(0, 1) = -1;
  expect(0, 2) = 0;
  expect(1, 0) = -1;
  expect(1, 1) = 3;
  expect(1, 2) = -1;
  expect(2, 0) = 0;
  expect(2, 1) = -1;
  expect(2, 2) = 1;

  got = matrix.InverseMatrix();

  EXPECT_EQ(got.EqMatrix(expect), true);
}
