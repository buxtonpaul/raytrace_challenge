#include "gtest/gtest.h"
#include "tuples.h"

TEST(Tuples, IsPoint) {
  Raytuple a(4.3, -4.2, 3.1 , 1.0);
  EXPECT_FLOAT_EQ(a.x(), 4.3);
  EXPECT_FLOAT_EQ(a.y(), -4.2);
  EXPECT_FLOAT_EQ(a.z(), 3.1);
  EXPECT_FLOAT_EQ(a.w(), 1.0);

  EXPECT_EQ(a.isPoint(), true);
  EXPECT_EQ(a.isVector(), false);
}

TEST(Tuples, IsVector) {
  Raytuple a(4.3, -4.2, 3.1 , 0);
  EXPECT_FLOAT_EQ(a.x(), 4.3);
  EXPECT_FLOAT_EQ(a.y(), -4.2);
  EXPECT_FLOAT_EQ(a.z(), 3.1);
  EXPECT_FLOAT_EQ(a.w(), 0.0);

  EXPECT_EQ(a.isPoint(), false);
  EXPECT_EQ(a.isVector(), true);
}

TEST(Points, CreatePoint)
{
  Raytuple p(Point(4, -4, 3));
  EXPECT_EQ(p, Raytuple(4, -4, 3, 1));
  EXPECT_EQ(p.isPoint(), true);
}

TEST(Vector, CreateVector)
{
  Raytuple v(Vector(4, -4, 3));
  EXPECT_EQ(v, Raytuple(4, -4, 3, 0.0));
  EXPECT_EQ(v.isPoint(), false);
}


TEST(Additions, TupleTuple)
{
  Raytuple p1(3, -2, 5, 1);
  Raytuple p2(-2, 3, 1, 0);
  EXPECT_EQ(p1 + p2, Raytuple(1, 1, 6, 1));
}

TEST(Subtractions, PointPoint)
{
  EXPECT_EQ(Point(3, 2, 1) - Point(5, 6, 7), Vector(-2, -4, -6));
}

TEST(Subtractions, VectorPoint)
{
  EXPECT_EQ(Point(3, 2, 1) - Vector(5, 6, 7), Point(-2, -4, -6));
}
TEST(Subtractions, VectorVector)
{
  EXPECT_EQ(Vector(3, 2, 1) - Vector(5, 6, 7), Vector(-2, -4, -6));
}

TEST(Vectors, Negation)
{
  EXPECT_EQ(Vector(0, 0, 0) - Vector(1, -2, 3), Vector(-1, 2, -3));
}

TEST(Tuples, Negation)
{
  EXPECT_EQ(-Raytuple(1, -2, 3, -4), Raytuple(-1, 2, -3, 4));
}

TEST(Tuples, Multiplication_scalar)
{
 EXPECT_EQ(3.5* Raytuple(1, -2, 3, -4), Raytuple(3.5, -7, 10.5, -14));
 EXPECT_EQ(Raytuple(1, -2, 3, -4) * 2, Raytuple(2, -4, 6, -8));
}

TEST(Tuples, Multiplication_fraction)
{
  EXPECT_EQ(0.5 * Raytuple(1, -2, 3, -4), Raytuple(0.5, -1, 1.5, -2));
}


TEST(Tuples, Division_scalar)
{
  EXPECT_EQ(Raytuple(1, -2, 3, -4) / 2, Raytuple(0.5, -1, 1.5, -2) );
}

TEST(Tuples_Magnitude, Unit)
{
  EXPECT_FLOAT_EQ(Vector(1, 0, 0).magnitude(), 1);
  EXPECT_FLOAT_EQ(Vector(0, 1, 0).magnitude(), 1);
  EXPECT_FLOAT_EQ(Vector(0, 0, 1).magnitude(), 1);
}

TEST(Tuples_Magnitude, NonUnit)
{
  EXPECT_FLOAT_EQ(Vector(1, 2, 3).magnitude(), sqrt(14));
  EXPECT_FLOAT_EQ(Vector(-1, -2, -3).magnitude(), sqrt(14));
}
