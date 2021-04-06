#include "gtest/gtest.h"
#include "matrix.h"
#include "rays.h"
#include "cube.h"
#include "tuples.h"
#include "pattern.h"

using namespace ray_lib;

struct named_rays
{
  std::string Name;
  Ray r;
  double t1;
  double t2;
};

TEST(Cube, Intersects)
{
  Cube c;
  std::vector<struct named_rays> testcases{
      {"plsX", Ray({5, 0.5, 0}, Vector(-1, 0, 0)), 4, 6},
      {"mnsX", Ray({-5, 0.5, 0}, Vector(1, 0, 0)), 4, 6},
      {"plsY", Ray({0.5, 5, 0}, Vector(0, -1, 0)), 4, 6},
      {"mnsY", Ray({0.5, -5, 0}, Vector(0, 1, 0)), 4, 6},
      {"plsZ", Ray({0.5, 0, 5}, Vector(0, 0, -1)), 4, 6},
      {"mnsZ", Ray({0.5, 0, -5}, Vector(0, 0, 1)), 4, 6},
      {"inside", Ray({0, 0.5, 0}, Vector(0, 0, 1)), -1, 1},
  };

  for (auto testcase : testcases)
  {
    std::vector<Intersection> intersections{c.intersects(testcase.r)};
    EXPECT_EQ(intersections.size(), 2) << "testcase " << testcase.Name;
    EXPECT_EQ(intersections[0].t(), testcase.t1) << testcase.Name;
    EXPECT_EQ(intersections[1].t(), testcase.t2) << testcase.Name;
  }
}

TEST(Cube, Misses)
{
  Cube c;
  std::vector<struct named_rays> testcases{
      {"a", Ray({-2, 0, 0}, Vector(0.2673, 0.5354, 0.8018)), 0, 0},
      {"b", Ray({0, -2, 0}, Vector(0.8018, 0.2673, 0.5354)), 0, 0},
      {"c", Ray({0, 0, -2}, Vector(0.5354, 0.8018, 0.2673)), 0, 0},
      {"d", Ray({2, 0, 2}, Vector(0, 0, -1)), 0, 0},
      {"e", Ray({0, 2, 2}, Vector(0, -1, 0)), 0, 0},
      {"f", Ray({2, 2, 0}, Vector(-1, 0, 0)), 4, 6},
  };

  for (auto testcase : testcases)
  {
    std::vector<Intersection> intersections{c.intersects(testcase.r)};
    EXPECT_EQ(intersections.size(), 0) << "testcase " << testcase.Name;
  }
}

TEST(Cube, Normals)
{
  Cube c;

  std::vector<std::pair<Point, Vector>> testcases{
      {Point{1, 0.5, -0.8}, Vector{1, 0, 0}},
      {Point{-1, -0.2, 0.9}, Vector{-1, 0, 0}},
      {Point{-0.4, 1, -0.1}, Vector{0, 1, 0}},
      {Point{0.3, -1, -0.7}, Vector{0, -1, 0}},
      {Point{-0.6, 0.3, 1}, Vector{0, 0, 1}},
      {Point{0.4, 0.4, -1}, Vector{0, 0, -1}},
      {Point{1, 1, 1}, Vector{1, 0, 0}},
      {Point{-1, -1, -1}, Vector{-1, 0, 0}}};

  for (auto testcase : testcases)
  {
    EXPECT_EQ(c.Normal(testcase.first), testcase.second);
  }
}

