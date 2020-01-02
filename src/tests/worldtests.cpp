#include <algorithm>
#include <vector>
#include "color.h"
#include "gtest/gtest.h"
#include "light.h"
#include "material.h"
#include "matrix.h"
#include "rays.h"
#include "shape.h"
#include "sphere.h"
#include "tuples.h"
#include "utils.h"
#include "world.h"

using ray_lib::Point;
using ray_lib::Ray;
using ray_lib::Vector;

class EmptyWorldTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  // put destructor here if required
  // void TearDown() override {}

  // Variables go here...

  ray_lib::World w;
};

TEST_F(EmptyWorldTest, EmptyWorld) {
  EXPECT_EQ(w.WorldShapes().size(), 0);
  EXPECT_EQ(w.WorldLights().size(), 0);
}

class DefaultWorldTest : public ::testing::Test {
 protected:
  void SetUp() override {
    m.SetColor(Color(0.8, 1, 0.6));
    m.Diffuse(0.7);
    m.Specular(0.2);
    l.Position(ray_lib::Point(-10, 10, -10));
    l.Intensity(Color(1, 1, 1));
    s2.Transform(ray_lib::Matrix::Identity.Scale(0.5, 0.5, 0.5));
    w.WorldLights().push_back(&l);
    w.WorldShapes().push_back(&s1);
    w.WorldShapes().push_back(&s2);
  }

  // put destructor here if required
  // void TearDown() override {}

  // Variables go here...

  ray_lib::Light l;
  ray_lib::Material m;
  ray_lib::Sphere s1;
  ray_lib::Sphere s2;
  ray_lib::World w;
};

TEST_F(DefaultWorldTest, TestDefault) {
  EXPECT_EQ(true, Contains(w.WorldShapes(), (ray_lib::Shape*)(&s1)));
  EXPECT_EQ(true, Contains(w.WorldShapes(), (ray_lib::Shape*)(&s2)));
}

TEST_F(DefaultWorldTest, TestSimpleIntersections) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  std::vector<ray_lib::Intersection> xs = w.WorldIntersections(r);
  EXPECT_EQ(xs.size(), 4);
  EXPECT_EQ(xs[0].t(), 4);
  EXPECT_EQ(xs[1].t(), 4.5);
  EXPECT_EQ(xs[2].t(), 5.5);
  EXPECT_EQ(xs[3].t(), 6);
}
