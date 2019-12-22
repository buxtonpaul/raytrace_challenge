#include "gtest/gtest.h"
#include "matrix.h"
#include "tuples.h"

using ray_lib::identity_4;
using ray_lib::Matrix;
using ray_lib::Tuple;

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

TEST(Matrix, Mul)
{
  Matrix m1({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}});
  Matrix m2({{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}});

  EXPECT_EQ(m1 * m2,
            Matrix({{20, 22, 50, 48}, {44, 54, 114, 108}, {40, 58, 110, 102}, {16, 26, 46, 42}}));
}

TEST(Matrix, Row)
{
  Matrix m1({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}});
  EXPECT_EQ(m1.row(2), std::vector<double>({9, 8, 7, 6}));
}

TEST(Matrix, Column)
{
  Matrix m1({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}});
  EXPECT_EQ(m1.col(2), std::vector<double>({3, 7, 7, 3}));
}

TEST(Matrix, Tuple)
{
  Matrix m({{1, 2, 3, 4},
            {2, 4, 4, 2},
            {8, 6, 4, 1},
            {0, 0, 0, 1}});

  Tuple t({1, 2, 3, 1});

  EXPECT_EQ(m * t, Tuple({18, 24, 33, 1}));
}

TEST(Matrix, matrix_x_identity)
{
  Matrix m({{1, 2, 3, 4},
            {5.5, 6.5, 7.5, 8.5},
            {9, 10, 11, 12},
            {13.5, 14.5, 15.5, 16.5}});
  EXPECT_EQ(m * identity_4, m);
}

TEST(Matrix, tuple_x_identity)
{
  Tuple t({1, 2, 3, 1});
  EXPECT_EQ(identity_4 * t, t);
}

TEST(Matrix, transpose)
{
  Matrix m({{0, 9, 3, 0}, {9, 8, 0, 8}, {1, 8, 5, 3}, {0, 0, 5, 8}});
  Matrix t({{0, 9, 1, 0}, {9, 8, 8, 0}, {3, 0, 5, 5}, {0, 8, 3, 8}});

  EXPECT_EQ(m.transpose(), t);
}

TEST(Matrix, transpose_identiry)
{
  EXPECT_EQ(identity_4.transpose(), identity_4);
}

TEST(Matrix, determinant_2x2)
{
  Matrix m({{1, 5}, {-3, 2}});
  EXPECT_EQ(m.determinant(), 17);
}

TEST(Matrix, accessor)
{
  Matrix m({{-3, 5, 0},
            {1, -2, -7},
            {0, 1, 1}});

  EXPECT_EQ(m[0][0], -3);
  EXPECT_EQ(m[0][1], 5);
  EXPECT_EQ(m[2][1], 1);
  EXPECT_EQ(m[1][2], -7);
}

TEST(Matrix, submatrix)
{
  Matrix m({{1, 5, 0}, {-3, 2, 7}, {0, 6, -3}});

  EXPECT_EQ(m.submatrix(0, 2), Matrix({{-3, 2}, {0, 6}}));
}

TEST(Matrix, submatrix_4x4)
{
  Matrix m({{-6, 1, 1, 6}, {-8, 5, 8, 6}, {-1, 0, 8, 2}, {-7, 1, -1, 1}});

  EXPECT_EQ(m.submatrix(2, 1), Matrix({{-6, 1, 6}, {-8, 8, 6}, {-7, -1, 1}}));
}

TEST(Matrix, Minors)
{
  Matrix m({{3, 5, 0}, {2, -1, -7}, {6, -1, 5}});

  Matrix b = m.submatrix(1, 0);

  EXPECT_EQ(b.determinant(), 25);
  EXPECT_EQ(m.get_minor(1, 0), 25);
}

TEST(Matrix, Cofactors)
{
  Matrix m({{3, 5, 0}, {2, -1, -7}, {6, -1, 5}});

  EXPECT_EQ(m.get_minor(0, 0), -12);
  EXPECT_EQ(m.cofactor(0, 0), -12);
  EXPECT_EQ(m.get_minor(1, 0), 25);
  EXPECT_EQ(m.cofactor(1, 0), -25);
}

TEST(Matrix, 3x3Determinant)
{
  Matrix m({{1, 2, 6}, {-5, 8, -4}, {2, 6, 4}});

  EXPECT_EQ(m.cofactor(0, 0), 56);
  EXPECT_EQ(m.cofactor(0, 1), 12);
  EXPECT_EQ(m.cofactor(0, 2), -46);
  EXPECT_EQ(m.determinant(), -196);
}

TEST(Matrix, 4x4Determinant)
{
  Matrix m({{-2, -8, 3, 5},
            {-3, 1, 7, 3},
            {1, 2, -9, 6},
            {-6, 7, 7, -9}});

  EXPECT_EQ(m.cofactor(0, 0), 690);
  EXPECT_EQ(m.cofactor(0, 1), 447);
  EXPECT_EQ(m.cofactor(0, 2), 210);
  EXPECT_EQ(m.cofactor(0, 3), 51);
  EXPECT_EQ(m.determinant(), -4071);
}

TEST(Matrix, Invertable1)
{
  Matrix m({{6, 4, 4, 4},
            {5, 5, 7, 6},
            {4, -9, 3, -7},
            {9, 1, 7, -6}});
  EXPECT_EQ(m.determinant(), -2120);
  EXPECT_EQ(m.invertable(), true);
}

TEST(Matrix, Invertable2)
{
  Matrix m({{-4, 2, -2, -3}, {9, 6, 2, 6}, {0, -5, 1, -5}, {0, 0, 0, 0}});

  EXPECT_EQ(m.determinant(), 0);
  EXPECT_EQ(m.invertable(), false);
}

TEST(Matrix, Inversion1)
{
  Matrix a({{-5, 2, 6, -8},
            {1, -5, 1, 8},
            {7, 7, -6, -7},
            {1, -3, 7, 4}});

  Matrix b = a.inverse();
  EXPECT_EQ(a.determinant(), 532);
  EXPECT_EQ(a.cofactor(2, 3), -160);
  EXPECT_FLOAT_EQ(b[3][2], -160.0 / 532);

  EXPECT_EQ(a.cofactor(3, 2), 105);
  EXPECT_FLOAT_EQ(b[2][3], 105.0 / 532);

  EXPECT_EQ(Matrix({{0.21805, 0.45113, 0.24060, -0.04511},
                    {-0.80827, -1.45677, -0.44361, 0.52068},
                    {-0.07895, -0.22368, -0.05263, 0.19737},
                    {-0.52256, -0.81391, -0.30075, 0.30639}}),
            b);
}

TEST(Matrix, Inverse2)
{
  Matrix a({{8, -5, 9, 2},
            {7, 5, 6, 1},
            {-6, 0, 9, 6},
            {-3, 0, -9, -4}});
  Matrix b({{-0.15385, -0.15385, -0.28205, -0.53846},
            {-0.07692, 0.12308, 0.02564, 0.03077},
            {0.35897, 0.35897, 0.43590, 0.92308},
            {-0.69231, -0.69231, -0.76923, -1.92308}});
  EXPECT_EQ(a.inverse(), b);
}

TEST(Matrix, Inverse3)
{
  Matrix a({{9, 3, 0, 9},
            {-5, -2, -6, -3},
            {-4, 9, 6, 4},
            {-7, 6, 6, 2}});
  Matrix b({{-0.04074, -0.07778, 0.14444, -0.22222},
            {-0.07778, 0.03333, 0.36667, -0.33333},
            {-0.02901, -0.14630, -0.10926, 0.12963},
            {0.17778, 0.06667, -0.26667, 0.33333}});
  EXPECT_EQ(a.inverse(), b);
}

TEST(Matrix, InverseXproduct)
{
  Matrix a({{3, -9, 7, 3},
            {3, -8, 2, -9},
            {-4, 4, 4, 1},
            {-6, 5, -1, 1}});
  Matrix b({{8, 2, 2, 2},
            {3, -1, 7, 0},
            {7, 0, 5, 4},
            {6, -2, 0, 5}});

  Matrix C = a * b;
  EXPECT_EQ(C * b.inverse(), a);
}
