#include "gtest/gtest.h"
#include "matrix.h"
#include "rays.h"
#include "group.h"
#include "tuples.h"
#include "triangle.h"
using namespace ray_lib;



TEST(Triangle, ConstructTriangle)
{
  Point p1{0, 1, 0};
  Point p2{-1, 0, 0};
  Point p3{1, 0, 0};

  Triangle t{p1 ,p2, p3};

  EXPECT_EQ(t.p1(), p1);
  EXPECT_EQ(t.p2(), p2);
  EXPECT_EQ(t.p3(), p3);
  EXPECT_EQ(t.e1(), Vector(-1, -1, 0));
  EXPECT_EQ(t.e2(), Vector(1, -1, 0));
  EXPECT_EQ(t.normal(), Vector(0, 0, -1));

}

TEST(Triangle, TriangleNormal)
{
  Triangle t{Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0)};


  EXPECT_EQ(t.normal(Point{0, 0.5, 0}), t.normal());
}

TEST(Triangle, Intersectparallel)
{
  Triangle t{Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0)};
  Ray r{Point(0, -1, -2), Vector(0, 1, 0)};
  std::vector<Intersection> intersections{t.intersects(r)};
  EXPECT_EQ(intersections.size(), 0);
}

TEST(Triangle, MissP1P3Edge)
{
  Triangle t{Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0)};
  Ray r{Point(1, 1, -2), Vector(0, 0, 1)};
  std::vector<Intersection> intersections{t.intersects(r)};
  EXPECT_EQ(intersections.size(), 0);
}

TEST(Triangle, MissP1P2Edge)
{
  Triangle t{Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0)};
  Ray r{Point(-1, 1, -2), Vector(0, 0, 1)};
  std::vector<Intersection> intersections{t.intersects(r)};
  EXPECT_EQ(intersections.size(), 0);
}

TEST(Triangle, MissP2P3Edge)
{
  Triangle t{Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0)};
  Ray r{Point(0, -1, -2), Vector(0, 0, 1)};
  std::vector<Intersection> intersections{t.intersects(r)};
  EXPECT_EQ(intersections.size(), 0);
}

TEST(Triangle, RayStrikesTriangle)
{
  Triangle t{Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0)};
  Ray r{Point(0, 0.5, -2), Vector(0, 0, 1)};
  std::vector<Intersection> intersections{t.intersects(r)};
  EXPECT_EQ(intersections.size(), 1);
  EXPECT_FLOAT_EQ(intersections[0].t(),2.0);
}

