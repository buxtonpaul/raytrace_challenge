#include <cmath>
#include "gtest/gtest.h"
#include "matrix.h"
#include "tuples.h"
#define _USE_MATH_DEFINES

using ray_lib::Matrix;
using ray_lib::Point;
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
