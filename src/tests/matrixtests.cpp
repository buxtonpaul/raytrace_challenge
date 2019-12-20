#include "gtest/gtest.h"
#include "matrix.h"
#include "tuples.h"

TEST(Matrix, 4x4)
{
  ray_lib::Matrix m({{1, 2, 3, 4},
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
  ray_lib::Matrix m({{-3, 5, 0},
  {1, -2, -7},
  {0, 1, 1}});

  EXPECT_EQ(m.Data()[0][0], -3);
  EXPECT_EQ(m.Data()[1][1], -2);
  EXPECT_EQ(m.Data()[2][2], 1);
}

TEST(Matrix, 2x2)
{
  ray_lib::Matrix m({{-3, 5},
  {1, -2}});

  EXPECT_EQ(m.Data()[0][0], -3);
  EXPECT_EQ(m.Data()[0][1], 5);
  EXPECT_EQ(m.Data()[1][0], 1);
  EXPECT_EQ(m.Data()[1][1], -2);
}

TEST(Matrix, Eq)
{
  ray_lib::Matrix m1({{-3, 5}, {1, -2}});
  ray_lib::Matrix m2({{-3, 5}, {1, -2}});
  EXPECT_EQ(m1, m2);
}

TEST(Matrix, F_Eq)
{
  ray_lib::Matrix m1({{-3.0005, 5}, {1, -2}});
  ray_lib::Matrix m2({{-3, 5}, {1, -2}});
  EXPECT_EQ(m1, m2);
}

TEST(Matrix, NEq)
{
  ray_lib::Matrix m1({{-3, 5}, {1, -2}});
  ray_lib::Matrix m2({{-3, 5.5}, {1, -2}});
  EXPECT_NE(m1, m2);
}

TEST(Matrix, Mul)
{
  ray_lib::Matrix m1({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}});
  ray_lib::Matrix m2({{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}});

  EXPECT_EQ(m1 * m2 ,
          ray_lib::Matrix({{20, 22, 50, 48}, {44, 54, 114, 108}, {40, 58, 110, 102}, {16, 26, 46, 42}}));
}


TEST(Matrix, Row)
{
  ray_lib::Matrix m1({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}});
  EXPECT_EQ(m1.row(2), std::vector<double>({9, 8, 7, 6}));
}

TEST(Matrix, Column)
{
  ray_lib::Matrix m1({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}});
  EXPECT_EQ(m1.col(2), std::vector<double>({3, 7, 7, 3}));
}

TEST(Matrix, tuple)
{
  ray_lib::Matrix m({{1, 2, 3, 4},
  {2, 4, 4, 2},
  {8, 6, 4, 1},
  {0, 0, 0, 1}});

  ray_lib::tuple t({1, 2, 3, 1});

  EXPECT_EQ(m * t, ray_lib::tuple({18, 24, 33, 1}));
}

TEST(Matrix , matrix_x_identity)
{
  ray_lib::Matrix m({{1, 2, 3, 4},
  {5.5, 6.5, 7.5, 8.5},
  {9, 10, 11, 12},
  {13.5, 14.5, 15.5, 16.5}});
  EXPECT_EQ(m * ray_lib::identity_4, m);
}

TEST(Matrix, tuple_x_identity)
{
  ray_lib::tuple t({1, 2, 3, 1});
  EXPECT_EQ(ray_lib::identity_4 * t, t);
}

TEST(Matrix, transpose)
{
  ray_lib::Matrix m({{0, 9, 3, 0}, {9, 8, 0, 8}, {1, 8, 5, 3}, {0, 0, 5, 8}});
  ray_lib::Matrix t({{0, 9, 1, 0}, {9, 8, 8, 0}, {3, 0, 5, 5}, {0, 8, 3, 8}});

  EXPECT_EQ(m.transpose(), t);
}

TEST(Matrix, transpose_identiry)
{
  EXPECT_EQ(ray_lib::identity_4.transpose(), ray_lib::identity_4);
}

TEST(Matrix, determinant_2x2)
{
  ray_lib::Matrix m({{1, 5}, {-3, 2}});
  EXPECT_EQ(m.determinant(), 17);
}
