#include "gtest/gtest.h"
#include "matrix.h"
#include "tuples.h"
#include "rays.h"

TEST(Ray, Createray)
{
  ray_lib::Tuple p = ray_lib::Point(1, 2, 3);
  ray_lib::Tuple d = ray_lib::Vector(4, 5, 6);
  ray_lib::Ray r(p, d);
  EXPECT_EQ(r.Origin(), p);
  EXPECT_EQ(r.Direction(), d);
}