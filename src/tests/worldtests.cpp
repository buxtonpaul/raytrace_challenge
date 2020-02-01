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
    s1.Mat(m);
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

TEST_F(DefaultWorldTest, PrecomputeTest) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  ray_lib::Intersection xs(&s1, 4.0);

  ray_lib::IntersectionState i(xs, r);
  EXPECT_EQ(i.Position(), Point(0, 0, -1));
  EXPECT_EQ(i.Eye(), Vector(0, 0, -1));
  EXPECT_EQ(i.Normal(), Vector(0, 0, -1));
  EXPECT_EQ(i.Object(), &s1);
  EXPECT_EQ(i.t(), xs.t());
}

TEST_F(DefaultWorldTest, PrecomputeInsideTestOutside) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  ray_lib::Intersection xs(&s1, 4.0);

  ray_lib::IntersectionState i(xs, r);
  EXPECT_EQ(i.Inside(), false);
}

TEST_F(DefaultWorldTest, PrecomputeInsideTestInside) {
  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  ray_lib::Intersection xs(&s1, 1.0);

  ray_lib::IntersectionState i(xs, r);
  EXPECT_EQ(i.Inside(), true);
  EXPECT_EQ(i.Normal(), Vector(0, 0, -1));
}

TEST_F(DefaultWorldTest, ShadeHit) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  ray_lib::Shape* firstshape = w.WorldShapes()[0];
  ray_lib::Intersection xs(firstshape, 4.0);

  ray_lib::IntersectionState i(xs, r);

  Color c = w.shade_hit(i);
  EXPECT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

TEST_F(DefaultWorldTest, ShadeHit_inside) {
  l.Position(Point(0, 0.25, 0));
  l.Intensity(Color(1, 1, 1));

  Ray r(Point(0, 0, 0), Vector(0, 0, 1));

  ray_lib::Shape* secondshape = w.WorldShapes()[1];
  ray_lib::Intersection xs(secondshape, 0.5);

  ray_lib::IntersectionState i(xs, r);

  Color c = w.shade_hit(i);
  EXPECT_EQ(c, Color(0.90498, 0.90498, 0.90498));
}

TEST_F(DefaultWorldTest, Colot_at_miss) {
  Ray r(Point(0, 0, -5), Vector(0, 1, 0));
  EXPECT_EQ(w.color_at(r), Color(0, 0, 0));
}

TEST_F(DefaultWorldTest, Colot_at_hit) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  EXPECT_EQ(w.color_at(r), Color(0.38066, 0.47583, 0.2855));
}

TEST_F(DefaultWorldTest, Colot_at_inside) {
  Ray r(Point(0, 0, 0.75), Vector(0, 0, -1));
  ray_lib::Shape* inner = w.WorldShapes()[0];
  ray_lib::Shape* outer = w.WorldShapes()[1];

  ray_lib::Material m2;
  // m2.Ambient(1);
  // s1.Mat(m2);
  // s2.Mat(m2);
  // Need to add setteres to teh material :-(
  outer->Mat(ray_lib::Material().Ambient(1.0));
  inner->Mat(ray_lib::Material().Ambient(1.0));
  EXPECT_EQ(w.color_at(r), inner->Mat().GetColor());
}