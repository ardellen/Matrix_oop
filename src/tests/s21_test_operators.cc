#include "s21_test.h"

TEST(SumOperator, test_1) {
  S21Matrix first(3, 3);
  first.SetAnyNum(1);
  S21Matrix second(3, 3);
  second.SetAnyNum(2);
  S21Matrix expect(3, 3);
  expect.SetAnyNum(3);
  EXPECT_EQ(expect.EqMatrix(first + second), true);
}

TEST(SumOperator, test_2) {
  S21Matrix first(3, 3);
  first.SetAnyNum(1);
  S21Matrix second(3, 3);
  second.SetAnyNum(2);
  S21Matrix expect(3, 3);
  expect.SetAnyNum(7);
  for (int i = 0; i < 3; i++) {
    first += second;
  }
  EXPECT_EQ(expect.EqMatrix(first), true);
}

TEST(SumOperator, test_3) {
  S21Matrix first(3, 3);
  first.SetAnyNum(1);
  S21Matrix second(2, 2);
  second.SetAnyNum(1);

  EXPECT_ANY_THROW(first + second);
}

TEST(SumOperator, test_4) {
  S21Matrix first(3, 3);
  first.SetAnyNum(1);
  S21Matrix second(2, 2);
  second.SetAnyNum(1);

  EXPECT_ANY_THROW(first += second);
}

TEST(SubOperator, test_1) {
  S21Matrix first(3, 3);
  first.SetAnyNum(1);
  S21Matrix second(3, 3);
  second.SetAnyNum(2);
  S21Matrix expect(3, 3);
  expect.SetAnyNum(-1);
  EXPECT_EQ(expect.EqMatrix(first - second), true);
}

TEST(SubOperator, test_2) {
  S21Matrix first(3, 3);
  first.SetAnyNum(10);
  S21Matrix second(3, 3);
  second.SetAnyNum(3);
  S21Matrix expect(3, 3);
  expect.SetAnyNum(1);
  for (int i = 0; i < 3; i++) {
    first -= second;
  }
  EXPECT_EQ(expect.EqMatrix(first), true);
}

TEST(SubOperator, test_3) {
  S21Matrix first(3, 3);
  first.SetAnyNum(1);
  S21Matrix second(2, 2);
  second.SetAnyNum(1);

  EXPECT_ANY_THROW(first - second);
}

TEST(SubOperator, test_4) {
  S21Matrix first(3, 3);
  first.SetAnyNum(1);
  S21Matrix second(2, 2);
  second.SetAnyNum(1);

  EXPECT_ANY_THROW(first -= second);
}

TEST(MulOperator, test_1) {
  S21Matrix first(3, 3);
  first.SetAnyNum(6);
  S21Matrix second(3, 3);
  second.SetAnyNum(2);
  S21Matrix expect(3, 3);
  expect.SetAnyNum(36);
  EXPECT_EQ(expect.EqMatrix(first * second), true);
}

TEST(MulOperator, test_2) {
  S21Matrix first(3, 3);
  first.SetAnyNum(6);
  S21Matrix expect(3, 3);
  expect.SetAnyNum(18);
  EXPECT_EQ(expect.EqMatrix(first * 3), true);
}

TEST(MulOperator, test_2_1) {
  S21Matrix first(3, 3);
  first.SetAnyNum(6);
  S21Matrix expect(3, 3);
  expect.SetAnyNum(18);
  EXPECT_EQ(expect.EqMatrix(3.0 * first), true);
}

TEST(MulOperator, test_3) {
  S21Matrix first(3, 3);
  first.SetAnyNum(1);
  S21Matrix second(2, 2);
  second.SetAnyNum(1);

  EXPECT_ANY_THROW(first * second);
}

TEST(MulOperator, test_4) {
  S21Matrix first(3, 3);
  first.SetAnyNum(6);
  S21Matrix second(3, 3);
  second.SetAnyNum(3);
  S21Matrix expect(3, 3);
  expect.SetAnyNum(486);
  for (int i = 0; i < 2; i++) {
    first *= second;
  }
  EXPECT_EQ(expect.EqMatrix(first), true);
}

TEST(MulOperator, test_5) {
  S21Matrix first(3, 3);
  first.SetAnyNum(6);
  S21Matrix expect(3, 3);
  expect.SetAnyNum(150);
  for (int i = 0; i < 2; i++) {
    first *= 5;
  }
  EXPECT_EQ(expect.EqMatrix(first), true);
}

TEST(MulOperator, test_6) {
  S21Matrix first(3, 3);
  first.SetAnyNum(1);
  S21Matrix second(2, 2);
  second.SetAnyNum(1);

  EXPECT_ANY_THROW(first *= second);
}

TEST(EqOperator, test_1) {
  S21Matrix first(3, 3);
  first.SetAnyNum(6);
  S21Matrix second(3, 3);
  second.SetAnyNum(6);

  EXPECT_EQ(first == second, true);
}

TEST(EqOperator, test_2) {
  S21Matrix first(3, 3);
  first.SetAnyNum(6);
  S21Matrix second(3, 3);
  second.SetAnyNum(7);

  EXPECT_EQ(first == second, false);
}

TEST(EqOperator, test_3) {
  S21Matrix first(3, 3);
  first.SetAnyNum(6);
  S21Matrix second(2, 3);
  second.SetAnyNum(6);

  EXPECT_EQ(first == second, false);
}

TEST(EqOperator, test_4) {
  S21Matrix first(3, 3);
  first.SetAnyNum(6);
  S21Matrix second(3, 3);
  second.SetAnyNum(2);
  S21Matrix expect(3, 3);
  expect.SetAnyNum(2);
  first = second;
  EXPECT_EQ(expect.EqMatrix(first), true);
}

TEST(EqOperator, test_5) {
  S21Matrix first(2, 2);
  first.SetAnyNum(6);
  S21Matrix second(3, 3);
  second.SetAnyNum(2);
  S21Matrix expect(3, 3);
  expect.SetAnyNum(2);
  first = second;
  EXPECT_EQ(expect.EqMatrix(first), true);
}

TEST(EqOperator, test_6) {
  S21Matrix first(7, 8);
  first.SetAnyNum(6);
  S21Matrix second(3, 3);
  second.SetAnyNum(2);
  S21Matrix expect(3, 3);
  expect.SetAnyNum(2);
  first = second;
  EXPECT_EQ(expect.EqMatrix(first), true);
}

TEST(EqOperator, test_7) {
  S21Matrix first(3, 3);
  first.SetAnyNum(6);
  S21Matrix second(3, 3);
  second.SetAnyNum(6);
  S21Matrix expect(3, 3);
  expect.SetAnyNum(6);
  first = second;
  EXPECT_EQ(expect.EqMatrix(first), true);
}

TEST(EqOperator, test_8) {
  S21Matrix first(3, 3);
  first.SetAnyNum(6);
  S21Matrix second(3, 3);
  second.SetAnyNum(6);
  S21Matrix expect(3, 3);
  expect.SetAnyNum(6);
  first = std::move(second);
  EXPECT_EQ(expect.EqMatrix(first), true);
}

TEST(EqOperator, test_9) {
  S21Matrix first(1, 1);
  S21Matrix second(0, 0);
  S21Matrix expect(0, 0);
  first = second;
  EXPECT_EQ(expect.EqMatrix(first), true);
}

TEST(BracketOperator, test_1) {
  S21Matrix first(3, 3);
  first.SetAnyNum(6);
  first.SetRows(5);
  EXPECT_NEAR(first(2, 2), 6., 1e-7);
  EXPECT_NEAR(first(4, 2), 0., 1e-7);
  //
}

TEST(BracketOperator, test_2) {
  S21Matrix first(3, 3);
  first.SetAnyNum(6);
  EXPECT_ANY_THROW(first(23, 33));
  EXPECT_ANY_THROW(first(1, -3));
}
