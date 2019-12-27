#include "color.h"
#include "gtest/gtest.h"
#include "light.h"
#include "material.h"
#include "matrix.h"
#include "shape.h"
#include "sphere.h"
#include "tuples.h"
#include "world.h"

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

TEST_F(DefaultWorldTest, TestDefault) {}
