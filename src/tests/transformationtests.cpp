#include <cmath>
#include "gtest/gtest.h"
#include "matrix.h"
#include "tuples.h"
#define _USE_MATH_DEFINES

using ray_lib::Matrix;
using ray_lib::Point;
using ray_lib::Scale;
using ray_lib::Tuple;
using ray_lib::Vector;

TEST(Transformations, Translation)
{
  Matrix M1 = ray_lib::Translation(5, -3, 2);
  Tuple P = Point(-3, 4, 5);

  EXPECT_EQ(M1 * P, Point(2, 1, 7));
}

TEST(Transformations, Translation_Inverse)
{
  Matrix M1 = ray_lib::Translation(5, -3, 2);
  Tuple P = Point(-3, 4, 5);

  EXPECT_EQ(M1.inverse() * P, Point(-8, 7, 3));
}

TEST(Transformations, Translation_Vector)
{
  Matrix M1 = ray_lib::Translation(5, -3, 2);
  Tuple v = Vector(-3, 4, 5);

  EXPECT_EQ(M1 * v, v);
}

TEST(Transformations, Scaling_point)
{
  Matrix transform = ray_lib::Scale(2, 3, 4);
  Tuple p = Point(-4, 6, 8);

  EXPECT_EQ(transform * p, Point(-8, 18, 32));
}

TEST(Transformations, Scaling_vector)
{
  Matrix transform = ray_lib::Scale(2, 3, 4);
  Tuple v = Vector(-4, 6, 8);

  EXPECT_EQ(transform * v, Vector(-8, 18, 32));
}

TEST(Transformations, Scaling_inverse)
{
  Matrix transform = ray_lib::Scale(2, 3, 4);
  Tuple v = Vector(-4, 6, 8);

  EXPECT_EQ(transform.inverse() * v, Vector(-2, 2, 2));
}

TEST(Transformations, ScalingReflection)
{
  Matrix transform = ray_lib::Scale(1, -1, 1);
  Tuple p = Point(-4, 6, 8);

  EXPECT_EQ(transform.inverse() * p, Point(-4, -6, 8));
}

TEST(Transformations, RotX1)
{
  Tuple p = Point(0, 1, 0);
  Matrix half_quarter = ray_lib::Rotation_x(M_PI / 4.0);
  Matrix full_quarter = ray_lib::Rotation_x(M_PI / 2.0);

  EXPECT_EQ(full_quarter * p, Point(0, 0, 1));
  EXPECT_EQ(half_quarter * p, Point(0, sqrt(2.0) / 2.0, sqrt(2.0) / 2.0));
}

TEST(Transformations, RotX2)
{
  Tuple p = Point(0, 1, 0);
  Matrix half_quarter = ray_lib::Rotation_x(M_PI / 4.0);
  Matrix inv = half_quarter.inverse();

  EXPECT_EQ(inv * p, Point(0, sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0));
}

TEST(Transformations, RotY1)
{
  Tuple p = Point(0, 0, 1);
  Matrix half_quarter = ray_lib::Rotation_y(M_PI / 4.0);
  Matrix full_quarter = ray_lib::Rotation_y(M_PI / 2.0);

  EXPECT_EQ(half_quarter * p, Point(sqrt(2.0) / 2.0, 0, sqrt(2.0) / 2.0));
  EXPECT_EQ(full_quarter * p, Point(1, 0, 0));
}

TEST(Transformations, Rotz1)
{
  Tuple p = Point(0, 1, 0);
  Matrix half_quarter = ray_lib::Rotation_z(M_PI / 4.0);
  Matrix full_quarter = ray_lib::Rotation_z(M_PI / 2.0);

  EXPECT_EQ(half_quarter * p, Point(-sqrt(2.0) / 2.0, sqrt(2.0) / 2.0, 0));
  EXPECT_EQ(full_quarter * p, Point(-1, 0, 0));
}

TEST(Transformations, Shear_xy)
{
  Matrix transform = ray_lib::Shear(1, 0, 0, 0, 0, 0);
  Tuple p = Point(2, 3, 4);

  EXPECT_EQ(transform * p, Point(5, 3, 4));
}

TEST(Transformations, Shear_xz)
{
  Matrix transform = ray_lib::Shear(0, 1, 0, 0, 0, 0);
  Tuple p = Point(2, 3, 4);

  EXPECT_EQ(transform * p, Point(6, 3, 4));
}

TEST(Transformations, Shear_yx)
{
  Matrix transform = ray_lib::Shear(0, 0, 1, 0, 0, 0);
  Tuple p = Point(2, 3, 4);

  EXPECT_EQ(transform * p, Point(2, 5, 4));
}

TEST(Transformations, Shear_yz)
{
  Matrix transform = ray_lib::Shear(0, 0, 0, 1, 0, 0);
  Tuple p = Point(2, 3, 4);

  EXPECT_EQ(transform * p, Point(2, 7, 4));
}

TEST(Transformations, Shear_zx)
{
  Matrix transform = ray_lib::Shear(0, 0, 0, 0, 1, 0);
  Tuple p = Point(2, 3, 4);

  EXPECT_EQ(transform * p, Point(2, 3, 6));
}

TEST(Transformations, Shear_zy)
{
  Matrix transform = ray_lib::Shear(0, 0, 0, 0, 0, 1);
  Tuple p = Point(2, 3, 4);

  EXPECT_EQ(transform * p, Point(2, 3, 7));
}

TEST(Transformation, Sequence)
{
  Tuple p = Point(1, 0, 1);
  Matrix A = ray_lib::Rotation_x(M_PI / 2);
  Matrix B = ray_lib::Scale(5, 5, 5);
  Matrix C = ray_lib::Translation(10, 5, 7);

  Tuple p2 = A * p;
  EXPECT_EQ(p2, Point(1, -1, 0));

  Tuple p3 = B * p2;
  EXPECT_EQ(p3, Point(5, -5, 0));

  Tuple p4 = C * p3;

  EXPECT_EQ(p4, Point(15, 0, 7));
}

TEST(Transformation, ChainSequence)
{
  Tuple p = Point(1, 0, 1);
  Matrix A = ray_lib::Rotation_x(M_PI / 2);
  Matrix B = ray_lib::Scale(5, 5, 5);
  Matrix C = ray_lib::Translation(10, 5, 7);

  Matrix Combined = C * B * A;

  EXPECT_EQ(Combined * p, Point(15, 0, 7));
}

TEST(Transformation, FluentChainSequence)
{
   Tuple p = Point(1, 0, 1);
   Matrix t = ray_lib::identity_4.Rotate_x(M_PI / 2).Scale(5, 5, 5).Translate(10, 5, 7);
   EXPECT_EQ(t * p, Point(15, 0, 7));
}
