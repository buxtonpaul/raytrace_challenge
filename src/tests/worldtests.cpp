#include <algorithm>
#include <vector>
#include <cmath>
#include "color.h"
#include "gtest/gtest.h"
#include "light.h"
#include "material.h"
#include "matrix.h"
#include "rays.h"
#include "shape.h"
#include "sphere.h"
#include "plane.h"
#include "tuples.h"
#include "utils.h"
#include "world.h"
#include "pattern.h"

using namespace ray_lib;

class EmptyWorldTest : public ::testing::Test
{
protected:
  void SetUp() override {}

  // put destructor here if required
  // void TearDown() override {}

  // Variables go here...

  World w;
};

TEST_F(EmptyWorldTest, EmptyWorld)
{
  EXPECT_EQ(w.WorldShapes().size(), 0);
  EXPECT_EQ(w.WorldLights().size(), 0);
}

class DefaultWorldTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    p.setColor(Color(0.8, 1, 0.6));
    m.SetPattern((Pattern *)&p);
    m.Diffuse(0.7);
    m.Specular(0.2);
    l.Position(Point(-10, 10, -10));
    l.Intensity(Color(1, 1, 1));
    s2.Transform(Matrix::Identity.Scale(0.5, 0.5, 0.5));
    w.WorldLights().push_back(&l);
    w.WorldShapes().push_back(&s1);
    w.WorldShapes().push_back(&s2);
    s1.material(m);
  }

  // put destructor here if required
  // void TearDown() override {}

  // Variables go here...

  Light l;
  Material m;
  SolidPattern p;
  Sphere s1;
  Sphere s2;
  World w;
};

TEST_F(DefaultWorldTest, TestDefault)
{
  EXPECT_EQ(true, Contains(w.WorldShapes(), (Shape *)(&s1)));
  EXPECT_EQ(true, Contains(w.WorldShapes(), (Shape *)(&s2)));
}

TEST_F(DefaultWorldTest, TestSimpleIntersections)
{
  Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
  std::vector<Intersection> xs{w.WorldIntersections(r)};
  EXPECT_EQ(xs.size(), 4);
  EXPECT_EQ(xs[0].t(), 4);
  EXPECT_EQ(xs[1].t(), 4.5);
  EXPECT_EQ(xs[2].t(), 5.5);
  EXPECT_EQ(xs[3].t(), 6);
}

TEST_F(DefaultWorldTest, PrecomputeTest)
{
  Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
  Intersection xs{&s1, 4.0};

  IntersectionState i{xs, r};
  EXPECT_EQ(i.Position(), Point(0, 0, -1));
  EXPECT_EQ(i.Eye(), Vector(0, 0, -1));
  EXPECT_EQ(i.Normal(), Vector(0, 0, -1));
  EXPECT_EQ(i.Object(), &s1);
  EXPECT_EQ(i.t(), xs.t());
}

TEST_F(DefaultWorldTest, PrecomputeInsideTestOutside)
{
  Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
  Intersection xs{&s1, 4.0};

  IntersectionState i{xs, r};
  EXPECT_EQ(i.Inside(), false);
}

TEST_F(DefaultWorldTest, PrecomputeInsideTestInside)
{
  Ray r{Point(0, 0, 0), Vector(0, 0, 1)};
  Intersection xs{&s1, 1.0};

  IntersectionState i{xs, r};
  EXPECT_EQ(i.Inside(), true);
  EXPECT_EQ(i.Normal(), Vector(0, 0, -1));
}

TEST_F(DefaultWorldTest, ShadeHit)
{
  Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
  Shape *firstshape{w.WorldShapes()[0]};
  Intersection xs{firstshape, 4.0};

  IntersectionState i{xs, r};

  Color c{w.shade_hit(i)};
  EXPECT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

TEST_F(DefaultWorldTest, ShadeHit_inside)
{
  l.Position(Point(0, 0.25, 0));
  l.Intensity(Color(1, 1, 1));

  Ray r{Point(0, 0, 0), Vector(0, 0, 1)};

  Shape *secondshape{w.WorldShapes()[1]};
  Intersection xs{secondshape, 0.5};

  IntersectionState i{xs, r};

  Color c{w.shade_hit(i)};
  EXPECT_EQ(c, Color(0.90498, 0.90498, 0.90498));
}

TEST_F(DefaultWorldTest, Colot_at_miss)
{
  Ray r{Point(0, 0, -5), Vector(0, 1, 0)};
  EXPECT_EQ(w.color_at(r), Color(0, 0, 0));
}

TEST_F(DefaultWorldTest, Colot_at_hit)
{
  Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
  EXPECT_EQ(w.color_at(r), Color(0.38066, 0.47583, 0.2855));
}

TEST_F(DefaultWorldTest, Color_at_inside)
{
  Ray r{Point(0, 0, 0.75), Vector(0, 0, -1)};
  Shape *inner{w.WorldShapes()[0]};
  Shape *outer{w.WorldShapes()[1]};

  Material m2;
  m2.Ambient(1.0);
  outer->material(m2);
  inner->material(m2);
  EXPECT_EQ(w.color_at(r), inner->material().GetPat().getColor(Point(0, 0, 0)));
}

TEST_F(DefaultWorldTest, Shadow_NoShadow)
{
  Point p{0, 10, 0};

  EXPECT_EQ(w.isShadowed(p), false);
}

TEST_F(DefaultWorldTest, Shadow_ObjectBetweenLight)
{
  Point p{10, -10, 10};

  EXPECT_EQ(w.isShadowed(p), true);
}

TEST_F(DefaultWorldTest, Shadow_ObjectBehindLight)
{
  Point p{-20, 20, -20};

  EXPECT_EQ(w.isShadowed(p), false);
}

TEST_F(DefaultWorldTest, Shadow_ObjectBehindPoint)
{
  Point p{-2, 2, -2};

  EXPECT_EQ(w.isShadowed(p), false);
}

TEST(World, Shadow_IntersectionInShadow)
{
  World w;
  Light l{Color(1, 1, 1), Point(0, 0, -10)};
  w.WorldLights().push_back(&l);
  Sphere s1;
  Sphere s2;
  s2.Transform(Translation(0, 0, 10));
  w.WorldShapes().push_back(&s1);
  w.WorldShapes().push_back(&s2);
  Ray r{Point(0, 0, 5), Vector(0, 0, 1)};
  Intersection xs{&s2, 4};
  IntersectionState i{xs, r};

  Color c{w.shade_hit(i)};
  EXPECT_EQ(c, Color(0.1, 0.1, 0.1));
}

TEST(World, Shadow_RayAtHitOffset)
{
  Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
  Sphere s1;
  s1.Transform(Translation(0, 0, 1));

  Intersection xs{&s1, 5};
  IntersectionState i{xs, r};
  EXPECT_EQ(true, i.OverPoint().z() < -DBL_EPSILON / 2.0);
  EXPECT_EQ(true, i.Position().z() > i.OverPoint().z());
}

TEST_F(DefaultWorldTest, PrecomputeReflectionVector)
{
  Ray r{Point(0, 1, -1), Vector(0, -sqrt(2.0) / 2.0, sqrt(2.0) / 2.0)};
  Plane p;
  Intersection xs(&p, sqrt(2.0));

  IntersectionState i{xs, r};
  EXPECT_EQ(i.ReflectV(), Vector(0.0, sqrt(2.0) / 2.0, sqrt(2.0) / 2.0));
}

TEST_F(DefaultWorldTest, NonReflective)
{
  Ray r{Point(0, 0, 0), Vector(0, 0, -1)};
  Shape *inner{w.WorldShapes()[0]};
  Shape *outer{w.WorldShapes()[1]};

  Material m2;
  m2.Ambient(1.0);
  outer->material(m2);
  Intersection xs{outer, 1};
  IntersectionState i{xs, r};
  EXPECT_EQ(w.reflection_hit(i), Color(0, 0, 0));
}

TEST_F(DefaultWorldTest, ReflectiveTest)
{
  Material plane_pat;
  plane_pat.Reflectivity(0.5);
  Plane p(Translation(0, -1, 0));
  p.material(plane_pat);
  w.WorldShapes().push_back(&p);

  Ray r{Point(0, 0, -3), Vector(0, -sqrt(2.0) / 2.0, sqrt(2.0) / 2.0)};

  Intersection xs{&p, sqrt(2)};
  IntersectionState i{xs, r};
  EXPECT_EQ(w.reflection_hit(i), Color(0.19032, 0.2379, 0.14274));
}

TEST_F(DefaultWorldTest, ReflectiveTest2)
{
  Material plane_pat;
  plane_pat.Reflectivity(0.5);
  Plane p(Translation(0, -1, 0));
  p.material(plane_pat);
  w.WorldShapes().push_back(&p);

  Ray r{Point(0, 0, -3), Vector(0, -sqrt(2.0) / 2.0, sqrt(2.0) / 2.0)};

  Intersection xs{&p, sqrt(2)};
  IntersectionState i{xs, r};
  EXPECT_EQ(w.shade_hit(i), Color(0.87677, 0.92436, 0.82918));
}

TEST_F(DefaultWorldTest, ReflectiveRecursion)
{
  Material plane_pat;
  plane_pat.Reflectivity(0.5);
  Plane p(Translation(0, -1, 0));
  p.material(plane_pat);
  w.WorldShapes().push_back(&p);

  Ray r{Point(0, 0, -3), Vector(0, -sqrt(2.0) / 2.0, sqrt(2.0) / 2.0)};

  Intersection xs{&p, sqrt(2)};
  IntersectionState i{xs, r};
  EXPECT_EQ(w.reflection_hit(i, 0), Color(0.0, 0.0, 0.0));
}

TEST(Refractions, RefractionIntersections)
{
  Sphere A{Scale(2, 2, 2)};
  Material mA{glass};
  mA.RefractiveIndex(1.5);
  A.material(mA);

  Sphere B{Scale(0, 0, -0.25)};
  Material mB{glass};
  mB.RefractiveIndex(2.0);
  B.material(mB);

  Sphere C{Scale(0, 0, 0.25)};
  Material mC{glass};
  mC.RefractiveIndex(2.5);
  C.material(mC);

  Ray r{Point(0, 0, -4), Vector(0, 0, 1)};
  std::vector<Intersection> intersections{{&A, 2.0}, {&B, 2.75}, {&C, 3.25}, {&B, 4.75}, {&C, 5.25}, {&A, 6}};

  std::vector<IntersectionState> precomps;
  for (auto a : intersections)
  {
    precomps.push_back(IntersectionState{a, r, intersections});
  }

  double n1s[] = {1.0, 1.5, 2.0, 2.5, 2.5, 1.5};
  double n2s[] = {1.5, 2.0, 2.5, 2.5, 1.5, 1.0};

  for (int i = 0; i < 6; ++i)
  {
    EXPECT_EQ(precomps[i].n1(), n1s[i]);
    EXPECT_EQ(precomps[i].n2(), n2s[i]);
  }
}

TEST(Refractions, UnderPoint)
{
  Sphere A{Translation(0, 0, 1)};
  Material mA{glass};
  A.material(mA);

  Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
  Intersection intersection{&A, 5.0};
  IntersectionState xs{intersection, r};

  EXPECT_GT(xs.Under().z(), DBL_EPSILON / 2);
  EXPECT_LT(xs.Position().z(), xs.Under().z());
}

TEST_F(DefaultWorldTest, RefractedColorOpaque)
{
  Shape *shape{w.WorldShapes()[0]};
  Ray r{Point(0, 0, -5), Vector(0, 0, 1)};

  Intersection intersection{shape, 5.0};
  IntersectionState xs{intersection, r};

  w.refracted_color(xs, 5);

  EXPECT_EQ(w.refracted_color(xs, 5), Color::Black);
}

TEST_F(DefaultWorldTest, RefractedColorAtDepth)
{
  Shape *shape{w.WorldShapes()[0]};
  Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
  Material mA{glass};
  mA.Transparency(1.0);
  mA.RefractiveIndex(1.5);
  shape->material(mA);

  std::vector<Intersection> intersections{{shape, 4}, {shape, 6}};
  IntersectionState xs{intersections[0], r, intersections};
  EXPECT_EQ(w.refracted_color(xs, 0), Color::Black);
}

TEST_F(DefaultWorldTest, TotalInternalRefraction)
{
  Shape *shape{w.WorldShapes()[0]};
  Ray r{Point(0, 0, sqrt(2.0) / 2.0), Vector(0, 1, 0)};
  Material mA{glass};
  mA.Transparency(1.0);
  mA.RefractiveIndex(1.5);
  shape->material(mA);

  std::vector<Intersection> intersections{{shape, -(sqrt(2.0) / 2.0)}, {shape, sqrt(2.0) / 2.0}};
  IntersectionState xs{intersections[1], r, intersections};
  EXPECT_EQ(w.refracted_color(xs, 5), Color::Black);
}

TEST_F(DefaultWorldTest, RefractedColor)
{
  Shape *a{w.WorldShapes()[0]};
  Material mA;
  mA.Ambient(1);
  TestPattern pA{Matrix::Identity};
  mA.SetPattern(&pA);
  a->material(mA);

  Shape *b{w.WorldShapes()[1]};
  Material mB;
  mB.Transparency(1.0);
  mB.RefractiveIndex(1.5);
  mB.Ambient(1);
  b->material(mB);

  Ray r{Point(0, 0, 0.1), Vector(0, 1, 0)};
  std::vector<Intersection> intersections{{a, -0.9899}, {b, -0.4899}, {b, 0.4899}, {a, 0.9899}};
  IntersectionState xs{intersections[2], r, intersections};
  EXPECT_EQ(w.refracted_color(xs, 5), Color(0, 0.99888, 0.04725));
}

TEST_F(DefaultWorldTest, ShadeHitTransparent)
{
  Material mFloor;
  mFloor.Transparency(0.5);
  mFloor.RefractiveIndex(1.5);
  Plane floor{Translation(0, -1, 0)};
  floor.material(mFloor);

  w.WorldShapes().push_back(&floor);

  Sphere ball{Translation(0, -3.5, -0.5)};
  Material mBall;
  SolidPattern pBall{Color(1, 0, 0)};
  mBall.Ambient(0.5);
  mBall.SetPattern(&pBall);
  w.WorldShapes().push_back(&ball);
  ball.material(mBall);

  Ray r{Point(0, 0, -3), Vector(0, -(sqrt(2.0) / 2.0), sqrt(2.0) / 2.0)};

  Intersection intersection{&floor, sqrt(2.0)};
  IntersectionState xs{intersection, r};

  EXPECT_EQ(w.shade_hit(xs, 5), Color(0.93642, 0.68642, 0.68642));
}

TEST(Refractions, Reflectance_InternalReflection)
{
  Sphere A{};
  Material mA{glass};
  A.material(mA);

  Ray r{Point(0, 0, sqrt(2.0) / 2.0), Vector(0, 1, 0)};
  std::vector<Intersection> intersections{{&A, -sqrt(2.0) / 2.0}, {&A, sqrt(2.0) / 2.0}};
  IntersectionState xs{intersections[1], r, intersections};

  EXPECT_EQ(xs.schlick(), 1.0);
}

TEST(Refractions, Reflectance_Perpendicular)
{
  Sphere A{};
  Material mA{glass};
  A.material(mA);

  Ray r{Point(0, 0, 0), Vector(0, 1, 0)};
  std::vector<Intersection> intersections{{&A, -1}, {&A, 1}};
  IntersectionState xs{intersections[1], r, intersections};

  EXPECT_FLOAT_EQ(xs.schlick(), 0.04);
}

TEST(Refractions, ReflectanceN2gtN1)
{
  Sphere A{};
  Material mA{glass};
  A.material(mA);

  Ray r{Point(0, 0.99, -2), Vector(0, 0, 1)};
  std::vector<Intersection> intersections{{&A, 1.8589}};
  IntersectionState xs{intersections[0], r, intersections};

  // modify this value somewhat as the precision of compparison causes issues
  EXPECT_FLOAT_EQ(xs.schlick(), 0.48873082);
}

TEST_F(DefaultWorldTest, ShadeHitTransparentReflectance)
{
  Ray r{Point(0, 0, -3), Vector(0, -(sqrt(2.0) / 2.0), sqrt(2.0) / 2.0)};
  Material mFloor;
  mFloor.Transparency(0.5);
  mFloor.Reflectivity(0.5);
  mFloor.RefractiveIndex(1.5);
  Plane floor{Translation(0, -1, 0)};
  floor.material(mFloor);
  w.WorldShapes().push_back(&floor);

  Sphere ball{Translation(0, -3.5, -0.5)};
  Material mBall;
  SolidPattern pBall{Color(1, 0, 0)};
  mBall.Ambient(0.5);
  mBall.SetPattern(&pBall);
  w.WorldShapes().push_back(&ball);
  ball.material(mBall);

  Intersection intersection{&floor, sqrt(2.0)};
  IntersectionState xs{intersection, r};

  EXPECT_EQ(w.shade_hit(xs, 5), Color(0.93391, 0.69643, 0.69243));
}
