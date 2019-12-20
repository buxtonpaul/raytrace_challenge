#include "gtest/gtest.h"
#include "matrix.h"

TEST(Matrix, 4x4)
{
  Matrix m({{1, 2, 3, 4},
  {5.5, 6.5, 7.5, 8.5},
  {9, 10, 11, 12},
  {13.5, 14.5, 15.5, 16.5}});

  EXPECT_EQ(m.Data()[0][0], 1);
  EXPECT_EQ(m.Data()[0][3], 4);
  EXPECT_EQ(m.Data()[1][0], 5.5);
  EXPECT_EQ(m.Data()[1][2], 7.5);
  EXPECT_EQ(m.Data()[2][2], 11);
  EXPECT_EQ(m.Data()[3][0], 13.5);
  EXPECT_EQ(m.Data()[3][2], 15.5);
}

TEST(Matrix, 3x3)
{
  Matrix m({{-3, 5, 0},
  {1, -2, -7},
  {0, 1, 1}});

  EXPECT_EQ(m.Data()[0][0], -3);
  EXPECT_EQ(m.Data()[1][1], -2);
  EXPECT_EQ(m.Data()[2][2], 1);
}

TEST(Matrix, 2x2)
{
  Matrix m({{-3, 5},
  {1, -2}});

  EXPECT_EQ(m.Data()[0][0], -3);
  EXPECT_EQ(m.Data()[0][1], 5);
  EXPECT_EQ(m.Data()[1][0], 1);
  EXPECT_EQ(m.Data()[1][1], -2);
}

TEST(Matrix, Eq)
{
  Matrix m1({{-3, 5}, {1, -2}});
  Matrix m2({{-3, 5}, {1, -2}});
  EXPECT_EQ(m1, m2);
}

TEST(Matrix, F_Eq)
{
  Matrix m1({{-3.0005, 5}, {1, -2}});
  Matrix m2({{-3, 5}, {1, -2}});
  EXPECT_EQ(m1, m2);
}

TEST(Matrix, NEq)
{
  Matrix m1({{-3, 5}, {1, -2}});
  Matrix m2({{-3, 5.5}, {1, -2}});
  EXPECT_NE(m1, m2);
}
