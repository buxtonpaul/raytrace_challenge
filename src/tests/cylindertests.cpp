#include "gtest/gtest.h"
#include "matrix.h"
#include "rays.h"
#include "cylinder.h"
#include "tuples.h"
// #include "pattern.h"

using namespace ray_lib;

struct named_rays
{
  std::string Name;
  Ray r;
  double t1;
  double t2;
};

TEST(Cylinder, Misses)
{
  Cylinder c;
  std::vector<struct named_rays> testcases{
      {"a", Ray({1, 0, 0}, Vector(0, 1, 0).normalise()), 0, 0},
      {"b", Ray({0, 0, 0}, Vector(0, 1, 0).normalise()), 0, 0},
      {"c", Ray({0, 0, -5}, Vector(1, 1, 1).normalise()), 0, 0},
  };

  for (auto testcase : testcases)
  {
    std::vector<Intersection> intersections{c.intersects(testcase.r)};
    EXPECT_EQ(intersections.size(), 0) << "testcase " << testcase.Name;
    // EXPECT_EQ(intersections[0].t(), testcase.t1) << testcase.Name;
    // EXPECT_EQ(intersections[1].t(), testcase.t2) << testcase.Name;
  }
}

TEST(Cylinder, Hits)
{
  Cylinder c;
  std::vector<struct named_rays> testcases{
      {"a", Ray({1, 0, -5}, Vector(0, 0, 1).normalise()), 5, 5},
      {"b", Ray({0, 0, -5}, Vector(0, 0, 1).normalise()), 4, 6},
      {"c", Ray({0.5, 0, -5}, Vector(0.1, 1, 1).normalise()), 6.80798, 7.0887237},
  };

  for (auto testcase : testcases)
  {
    std::vector<Intersection> intersections{c.intersects(testcase.r)};
    EXPECT_EQ(intersections.size(), 2) << "testcase " << testcase.Name;
    EXPECT_FLOAT_EQ(intersections[0].t(), testcase.t1) << testcase.Name;
    EXPECT_FLOAT_EQ(intersections[1].t(), testcase.t2) << testcase.Name;
  }
}

TEST(Cylinder, Normals)
{
  Cylinder c;

  std::vector<std::pair<Point, Vector>> testcases{
      {Point{1, 0, 0}, Vector{1, 0, 0}},
      {Point{0, 5, -1}, Vector{0, 0, -1}},
      {Point{0, -2, 1}, Vector{0, 0, 1}},
      {Point{-1, 1, 0}, Vector{-1, 0, 0}}};

  for (auto testcase : testcases)
  {
    EXPECT_EQ(c.normal(testcase.first), testcase.second);
  }
}


TEST(Cylinder, Defaults)
{
  Cylinder c;
  EXPECT_DOUBLE_EQ(c.min(), -INFINITY);
  EXPECT_DOUBLE_EQ(c.max(), INFINITY);
}




TEST(Cylinder, Constrained_Cylinder)
{
 Cylinder c{1,2};

  std::vector<std::pair<Ray, int>> testcases{
      {Ray{Point{0, 1.5, 0}, Vector{0.1, 1, 0}}, 0},
      {Ray{Point{0, 3, -5}, Vector{0, 0, 1}}, 0},
      {Ray{Point{0, 0, -5}, Vector{0, 0, 1}}, 0},
      {Ray{Point{0, 2, 5}, Vector{0, 0, 1}}, 0},
      {Ray{Point{0, 1, -5}, Vector{0, 0, 1}}, 0},
      {Ray{Point{0, 1.5, -2}, Vector{0, 0, 1}}, 2}
      };

  for (auto testcase : testcases)
  {
    std::vector<Intersection> intersections{c.intersects(testcase.first)};
    EXPECT_EQ(intersections.size(), testcase.second);
  }
}


TEST(Cylinder, Capped_Cylinder)
{
 Cylinder c{1, 2, true};

  std::vector<std::pair<Ray, int>> testcases{
      {Ray{Point{0, 3, 0}, Vector{0, -1, 0}}, 2},
      {Ray{Point{0, 3, -2}, Vector{0, -1, 2}}, 2},
      {Ray{Point{0, 4, -2}, Vector{0, -1, 1}}, 2},
      {Ray{Point{0, 0, -2}, Vector{0, 1, 2}}, 2},
      {Ray{Point{0, -1, -2}, Vector{0, 1, 1}}, 2}
      };

  for (auto testcase : testcases)
  {
    std::vector<Intersection> intersections{c.intersects(testcase.first)};
    EXPECT_EQ(intersections.size(), testcase.second);
  }
}


TEST(Cylinder, Capped_Cylinder_Normals)
{
 Cylinder c{1, 2, true};

  std::vector<std::pair<Point, Vector>> testcases{
      {Point{0, 1, 0}, Vector{0, -1, 0}},
      {Point{0.5, 1, 0}, Vector{0, -1, 0}.normalise()},
      {Point{0, 1, 0.5}, Vector{0, -1, 0}},
      {Point{0, 2, 0}, Vector{0, 1, 0}},
      {Point{0.5, 2, 0}, Vector{0, 1, 0}},
      {Point{0, 2, 0.5}, Vector{0, 1, 0}}
      };

  for (auto testcase : testcases)
  {
    EXPECT_EQ(c.normal(testcase.first), testcase.second);
  }
}
