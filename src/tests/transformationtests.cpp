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

TEST(Transformations, Translation) {
  Matrix M1 = ray_lib::Translation(5, -3, 2);
  Point P(-3, 4, 5);

  EXPECT_EQ(M1 * P, Point(2, 1, 7));
}

TEST(Transformations, Translation_Inverse) {
  Matrix M1 = ray_lib::Translation(5, -3, 2);
  Point P(-3, 4, 5);

  EXPECT_EQ(M1.inverse() * P, Point(-8, 7, 3));
}

TEST(Transformations, Translation_Vector) {
  Matrix M1 = ray_lib::Translation(5, -3, 2);
  Vector v(-3, 4, 5);

  EXPECT_EQ(M1 * v, v);
}

TEST(Transformations, Scaling_point) {
  Matrix transform = ray_lib::Scale(2, 3, 4);
  Point p(-4, 6, 8);

  EXPECT_EQ(transform * p, Point(-8, 18, 32));
}

TEST(Transformations, Scaling_vector) {
  Matrix transform = ray_lib::Scale(2, 3, 4);
  Vector v(-4, 6, 8);

  EXPECT_EQ(transform * v, Vector(-8, 18, 32));
}

TEST(Transformations, Scaling_inverse) {
  Matrix transform = ray_lib::Scale(2, 3, 4);
  Vector v(-4, 6, 8);

  EXPECT_EQ(transform.inverse() * v, Vector(-2, 2, 2));
}

TEST(Transformations, ScalingReflection) {
  Matrix transform = ray_lib::Scale(1, -1, 1);
  Point p(-4, 6, 8);

  EXPECT_EQ(transform.inverse() * p, Point(-4, -6, 8));
}

TEST(Transformations, RotX1) {
  Point p(0, 1, 0);
  Matrix half_quarter = ray_lib::Rotation_x(M_PI / 4.0);
  Matrix full_quarter = ray_lib::Rotation_x(M_PI / 2.0);

  EXPECT_EQ(full_quarter * p, Point(0, 0, 1));
  EXPECT_EQ(half_quarter * p, Point(0, sqrt(2.0) / 2.0, sqrt(2.0) / 2.0));
}

TEST(Transformations, RotX2) {
  Point p(0, 1, 0);
  Matrix half_quarter = ray_lib::Rotation_x(M_PI / 4.0);
  Matrix inv = half_quarter.inverse();

  EXPECT_EQ(inv * p, Point(0, sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0));
}

TEST(Transformations, RotY1) {
  Point p(0, 0, 1);
  Matrix half_quarter = ray_lib::Rotation_y(M_PI / 4.0);
  Matrix full_quarter = ray_lib::Rotation_y(M_PI / 2.0);

  EXPECT_EQ(half_quarter * p, Point(sqrt(2.0) / 2.0, 0, sqrt(2.0) / 2.0));
  EXPECT_EQ(full_quarter * p, Point(1, 0, 0));
}

TEST(Transformations, Rotz1) {
  Point p(0, 1, 0);
  Matrix half_quarter = ray_lib::Rotation_z(M_PI / 4.0);
  Matrix full_quarter = ray_lib::Rotation_z(M_PI / 2.0);

  EXPECT_EQ(half_quarter * p, Point(-sqrt(2.0) / 2.0, sqrt(2.0) / 2.0, 0));
  EXPECT_EQ(full_quarter * p, Point(-1, 0, 0));
}

TEST(Transformations, Shear_xy) {
  Matrix transform = ray_lib::Shear(1, 0, 0, 0, 0, 0);
  Point p(2, 3, 4);

  EXPECT_EQ(transform * p, Point(5, 3, 4));
}

TEST(Transformations, Shear_xz) {
  Matrix transform = ray_lib::Shear(0, 1, 0, 0, 0, 0);
  Point p(2, 3, 4);

  EXPECT_EQ(transform * p, Point(6, 3, 4));
}

TEST(Transformations, Shear_yx) {
  Matrix transform = ray_lib::Shear(0, 0, 1, 0, 0, 0);
  Point P(2, 3, 4);

  EXPECT_EQ(transform * P, Point(2, 5, 4));
}

TEST(Transformations, Shear_yz) {
  Matrix transform = ray_lib::Shear(0, 0, 0, 1, 0, 0);
  Point p(2, 3, 4);

  EXPECT_EQ(transform * p, Point(2, 7, 4));
}

TEST(Transformations, Shear_zx) {
  Matrix transform = ray_lib::Shear(0, 0, 0, 0, 1, 0);
  Point p(2, 3, 4);

  EXPECT_EQ(transform * p, Point(2, 3, 6));
}

TEST(Transformations, Shear_zy) {
  Matrix transform = ray_lib::Shear(0, 0, 0, 0, 0, 1);
  Point p(2, 3, 4);

  EXPECT_EQ(transform * p, Point(2, 3, 7));
}

TEST(Transformation, Sequence) {
  Point p(1, 0, 1);
  Matrix A = ray_lib::Rotation_x(M_PI / 2);
  Matrix B = ray_lib::Scale(5, 5, 5);
  Matrix C = ray_lib::Translation(10, 5, 7);

  Point p2 = A * p;
  EXPECT_EQ(p2, Point(1, -1, 0));

  Point p3 = B * p2;
  EXPECT_EQ(p3, Point(5, -5, 0));

  Point p4 = C * p3;

  EXPECT_EQ(p4, Point(15, 0, 7));
}

TEST(Transformation, ChainSequence) {
  Point p(1, 0, 1);
  Matrix A = ray_lib::Rotation_x(M_PI / 2);
  Matrix B = ray_lib::Scale(5, 5, 5);
  Matrix C = ray_lib::Translation(10, 5, 7);

  Matrix Combined = C * B * A;

  EXPECT_EQ(Combined * p, Point(15, 0, 7));
}

TEST(Transformation, FluentChainSequence) {
  Point p(1, 0, 1);
  Matrix t =
      ray_lib::Matrix::Identity.Rotate_x(M_PI / 2).Scale(5, 5, 5).Translate(
          10, 5, 7);
  EXPECT_EQ(t * p, Point(15, 0, 7));
}
