#include <cmath>
#include "gtest/gtest.h"
#include "tuples.h"

using ray_lib::Point;
using ray_lib::Tuple;
using ray_lib::Vector;

TEST(Tuples, accessor) {
  Tuple a({4.3, -4.2, 3.1, 1.0});
  EXPECT_FLOAT_EQ(a[0], 4.3);
  EXPECT_FLOAT_EQ(a[1], -4.2);
  EXPECT_FLOAT_EQ(a[2], 3.1);
  EXPECT_FLOAT_EQ(a[3], 1.0);
}

TEST(Tuples, IsPoint) {
  Tuple a({4.3, -4.2, 3.1, 1.0});
  EXPECT_FLOAT_EQ(a.x(), 4.3);
  EXPECT_FLOAT_EQ(a.y(), -4.2);
  EXPECT_FLOAT_EQ(a.z(), 3.1);
  EXPECT_FLOAT_EQ(a.w(), 1.0);

  EXPECT_EQ(a.isPoint(), true);
  EXPECT_EQ(a.isVector(), false);
}

TEST(Tuples, IsVector) {
  Tuple a({4.3, -4.2, 3.1, 0});
  EXPECT_FLOAT_EQ(a.x(), 4.3);
  EXPECT_FLOAT_EQ(a.y(), -4.2);
  EXPECT_FLOAT_EQ(a.z(), 3.1);
  EXPECT_FLOAT_EQ(a.w(), 0.0);

  EXPECT_EQ(a.isPoint(), false);
  EXPECT_EQ(a.isVector(), true);
}

TEST(Tuples, CreatePoint) {
  Point p(4, -4, 3);
  EXPECT_EQ(p, Point({4, -4, 3, 1}));
  EXPECT_EQ(p.isPoint(), true);
}

TEST(Tuples, CreateVector) {
  Vector v(4, -4, 3);
  EXPECT_EQ(v, Tuple({4, -4, 3, 0.0}));
  EXPECT_EQ(v.isPoint(), false);
}

TEST(Tuples, Additions_TupleTuple) {
  Tuple p1({3, -2, 5, 1});
  Tuple p2({-2, 3, 1, 0});
  EXPECT_EQ(p1 + p2, Tuple({1, 1, 6, 1}));
}

TEST(STuples, Subtractions_PointPoint) {
  EXPECT_EQ(Point(3, 2, 1) - Point(5, 6, 7), Vector(-2, -4, -6));
}

TEST(Tuples, Subtractions_VectorPoint) {
  EXPECT_EQ(Point(3, 2, 1) - Vector(5, 6, 7), Point(-2, -4, -6));
}
TEST(Tuples, Subtractions_VectorVector) {
  EXPECT_EQ(Vector(3, 2, 1) - Vector(5, 6, 7), Vector(-2, -4, -6));
}

TEST(Vectors, Negation) {
  EXPECT_EQ(Vector(0, 0, 0) - Vector(1, -2, 3), Vector(-1, 2, -3));
}

TEST(Tuples, Negation) {
  EXPECT_EQ(-Tuple({1, -2, 3, -4}), Tuple({-1, 2, -3, 4}));
}

TEST(Tuples, Multiplication_scalar) {
  EXPECT_EQ(3.5 * Tuple({1, -2, 3, -4}), Tuple({3.5, -7, 10.5, -14}));
  EXPECT_EQ(Tuple({1, -2, 3, -4}) * 2, Tuple({2, -4, 6, -8}));
}

TEST(Tuples, Multiplication_fraction) {
  EXPECT_EQ(0.5 * Tuple({1, -2, 3, -4}), Tuple({0.5, -1, 1.5, -2}));
}

TEST(Tuples, Division_scalar) {
  EXPECT_EQ(Tuple({1, -2, 3, -4}) / 2, Tuple({0.5, -1, 1.5, -2}));
}

TEST(Vectors, Magnitude_Unit) {
  EXPECT_FLOAT_EQ(Vector(1, 0, 0).magnitude(), 1);
  EXPECT_FLOAT_EQ(Vector(0, 1, 0).magnitude(), 1);
  EXPECT_FLOAT_EQ(Vector(0, 0, 1).magnitude(), 1);
}

TEST(Vectors, Magnitude_NonUnit) {
  EXPECT_FLOAT_EQ(Vector(1, 2, 3).magnitude(), sqrt(14));
  EXPECT_FLOAT_EQ(Vector(-1, -2, -3).magnitude(), sqrt(14));
}

TEST(Vectors, Normalise) {
  EXPECT_EQ(Vector(4, 0, 0).normalise(), Vector(1, 0, 0));
  EXPECT_EQ(Vector(1, 2, 3).normalise(), Vector(0.26726, 0.53452, 0.80178));
  EXPECT_FLOAT_EQ(Vector(1, 2, 3).normalise().magnitude(), 1.0);
}

TEST(Vectors, DotProduct) {
  EXPECT_FLOAT_EQ(Vector(1, 2, 3).dotproduct(Vector(2, 3, 4)), 20.0);
}

TEST(Vectors, CrossProduct) {
  EXPECT_EQ(Vector(1, 2, 3).crossproduct(Vector(2, 3, 4)),
            Vector(-1.0, 2.0, -1.0));
  EXPECT_EQ(Vector(2, 3, 4).crossproduct(Vector(1, 2, 3)), Vector(1, -2, 1));
}

TEST(Vectors, reflect_45) {
  Vector v(1, -1, 0);
  Vector n(0, 1, 0);
  Vector r = v.reflect(n);
  EXPECT_EQ(r, Vector(1, 1, 0));
}

TEST(Vectors, reflect_slanted) {
  Vector v(0, -1, 0);
  Vector n(sqrt(2.0) / 2.0, sqrt(2.0) / 2.0, 0);
  Vector r = v.reflect(n);
  EXPECT_EQ(r, Vector(1, 0, 0));
}
