#include "gtest/gtest.h"
#include "matrix.h"
#include "plane.h"
#include "rays.h"
#include "sphere.h"
#include "tuples.h"
#include "pattern.h"

using namespace ray_lib;

TEST(Ray, Createray)
{
  Point p{1, 2, 3};
  Vector d{4, 5, 6};
  Ray r{p, d};
  EXPECT_EQ(r.Origin(), p);
  EXPECT_EQ(r.Direction(), d);
}

TEST(Ray, Position)
{
  Ray r{Point(2, 3, 4), Vector(1, 0, 0)};

  EXPECT_EQ(r.Position(0), Point(2, 3, 4));
  EXPECT_EQ(r.Position(1), Point(3, 3, 4));
  EXPECT_EQ(r.Position(-1), Point(1, 3, 4));
  EXPECT_EQ(r.Position(2.5), Point(4.5, 3, 4));
}

TEST(Ray, SphereNormal)
{
  Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
  Sphere s;
  std::vector<Intersection> intersections{s.intersects(r)};
  EXPECT_EQ(intersections.size(), 2);
  EXPECT_FLOAT_EQ(intersections[0].t(), 4.0);
  EXPECT_FLOAT_EQ(intersections[1].t(), 6.0);
}

TEST(Ray, SphereTangent)
{
  Ray r{Point(0, 1, -5), Vector(0, 0, 1)};
  Sphere s;
  std::vector<Intersection> intersections{s.intersects(r)};
  EXPECT_EQ(intersections.size(), 2);
  EXPECT_FLOAT_EQ(intersections[0].t(), 5.0);
  EXPECT_FLOAT_EQ(intersections[1].t(), 5.0);
}

TEST(Ray, SphereMiss)
{
  Ray r{Point(0, 2, -5), Vector(0, 0, 1)};
  Sphere s;
  std::vector<Intersection> intersections{s.intersects(r)};
  EXPECT_EQ(intersections.size(), 0);
}

TEST(Ray, Sphere_Ray_origin)
{
  Ray r{Point(0, 0, 0), Vector(0, 0, 1)};
  Sphere s;
  std::vector<Intersection> intersections{s.intersects(r)};
  EXPECT_EQ(intersections.size(), 2);
  EXPECT_FLOAT_EQ(intersections[0].t(), -1);
  EXPECT_FLOAT_EQ(intersections[1].t(), 1);
}

TEST(Ray, Sphere_Ray_behind)
{
  Ray r{Point(0, 0, 5), Vector(0, 0, 1)};
  Sphere s;
  std::vector<Intersection> intersections{s.intersects(r)};
  EXPECT_EQ(intersections.size(), 2);
  EXPECT_FLOAT_EQ(intersections[0].t(), -6);
  EXPECT_FLOAT_EQ(intersections[1].t(), -4);
}

TEST(Ray, IntersctionHandle)
{
  Ray r{Point(0, 0, 5), Vector(0, 0, 1)};
  Sphere s;
  Intersection i{&s, 3.5};
  EXPECT_FLOAT_EQ(i.t(), 3.5);
  EXPECT_EQ(i.GetShape(), &s);
}

TEST(Ray, AggregateIntersections)
{
  Ray r{Point(0, 0, 5), Vector(0, 0, 1)};
  Sphere s;
  Shape &l{s};
  std::vector<Intersection> intersections{s.intersects(r)};
  EXPECT_EQ(intersections.size(), 2);
  EXPECT_EQ(intersections[0].GetShape(), &s);
  EXPECT_EQ(intersections[1].GetShape(), &s);
}

TEST(Ray, Intersection_Hits1)
{
  Ray r{Point(0, 0, 5), Vector(0, 0, 1)};
  Sphere s;

  std::vector<Intersection> i;
  Intersection i1{&s, 1};
  Intersection i2{&s, 2};
  i.push_back(i1);
  i.push_back(i2);
  EXPECT_EQ(i1 < i2, true);
  const Intersection *xs{Intersection::GetHit(i)};
  EXPECT_EQ(*xs, i1);
}

TEST(Ray, Intersection_Hits2)
{
  Ray r{Point(0, 0, 5), Vector(0, 0, 1)};
  Sphere s;

  std::vector<Intersection> i;
  Intersection i1{&s, -1};
  Intersection i2{&s, 1};
  i.push_back(i1);
  i.push_back(i2);
  const Intersection *xs{Intersection::GetHit(i)};
  EXPECT_EQ(*xs, i2);
}
TEST(Ray, Intersection_Hits3)
{
  Ray r{Point(0, 0, 5), Vector(0, 0, 1)};
  Sphere s;

  std::vector<Intersection> i;
  Intersection i1{&s, -2};
  Intersection i2{&s, -1};
  i.push_back(i1);
  i.push_back(i2);
  const Intersection *xs{Intersection::GetHit(i)};
  EXPECT_EQ(xs, nullptr);
}
TEST(Ray, Intersection_Hits4)
{
  Ray r{Point(0, 0, 5), Vector(0, 0, 1)};
  Sphere s;

  std::vector<Intersection> i;
  Intersection i1{&s, 5};
  Intersection i2{&s, 7};
  Intersection i3{&s, -3};
  Intersection i4{&s, 2};
  i.push_back(i1);
  i.push_back(i2);
  i.push_back(i3);
  i.push_back(i4);
  const Intersection *xs{Intersection::GetHit(i)};
  EXPECT_EQ(*xs, i4);
}

TEST(Ray, RayTranslation)
{
  Ray r{Point(1, 2, 3), Vector(0, 1, 0)};
  Matrix m{Matrix::Identity.translate(3, 4, 5)};
  Ray r2{r.Transform(m)};
  EXPECT_EQ(r2.Origin(), Point(4, 6, 8));
  EXPECT_EQ(r2.Direction(), Vector(0, 1, 0));
}

TEST(Ray, RayScaling)
{
  Ray r{Point(1, 2, 3), Vector(0, 1, 0)};
  Matrix m{Matrix::Identity.scale(2, 3, 4)};
  Ray r2{r.Transform(m)};
  EXPECT_EQ(r2.Origin(), Point(2, 6, 12));
  EXPECT_EQ(r2.Direction(), Vector(0, 3, 0));
}

TEST(Sphere, DefaultTransform)
{
  Sphere s;
  Matrix m{s.Transform()};
  EXPECT_EQ(m, Matrix::Identity);
}

TEST(Sphere, SetTransform)
{
  Sphere s;
  Matrix transform{Matrix::Identity.translate(2, 3, 4)};
  s.Transform(transform);
  EXPECT_EQ(s.Transform(), transform);
}

TEST(Ray, ScaledSphereIntersection)
{
  Sphere s;
  Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
  s.Transform(Matrix::Identity.scale(2, 2, 2));
  std::vector<Intersection> i{s.intersects(r)};
  EXPECT_EQ(i.size(), 2);
  EXPECT_EQ(i[0].t(), 3);
  EXPECT_EQ(i[1].t(), 7);
}

TEST(Ray, TranslatedSphereIntersection)
{
  Sphere s;
  Ray r{Point(0, 0, -5), Vector(0, 0, 1)};
  s.Transform(Matrix::Identity.translate(5, 0, 0));
  std::vector<Intersection> i{s.intersects(r)};
  EXPECT_EQ(i.size(), 0);
}

TEST(Ray, SphereNormal_xAxis)
{
  Sphere s;
  Vector n{s.normal(Point(1, 0, 0))};
  EXPECT_EQ(n, Vector(1, 0, 0));
}

TEST(Ray, SphereNormal_yAxis)
{
  Sphere s;
  Vector n{s.normal(Point(0, 1, 0))};
  EXPECT_EQ(n, Vector(0, 1, 0));
}

TEST(Ray, SphereNormal_zAxis)
{
  Sphere s;
  Vector n{s.normal(Point(0, 0, 1))};
  EXPECT_EQ(n, Vector(0, 0, 1));
}

TEST(Ray, SphereNormal_nonAxial)
{
  Sphere s;
  Vector n{s.normal(Point(sqrt(3.0) / 3.0, sqrt(3.0) / 3.0, sqrt(3.0) / 3.0))};
  EXPECT_EQ(n, Vector(sqrt(3.0) / 3.0, sqrt(3.0) / 3.0, sqrt(3.0) / 3.0));
}

TEST(Ray, SphereNormal_isnormalised)
{
  Sphere s;
  Vector n{s.normal(Point(sqrt(3.0) / 3.0, sqrt(3.0) / 3.0, sqrt(3.0) / 3.0))};
  EXPECT_EQ(n, n.normalise());
}

TEST(Ray, SphereNormal_translated)
{
  Sphere s;
  s.Transform(Matrix::Identity.translate(0, 1, 0));
  Vector n{s.normal(Point(0, 1.70711, -0.70711))};
  EXPECT_EQ(n, Vector(0, 0.70711, -0.70711));
}

TEST(Ray, SphereNormal_transformed)
{
  Sphere s;
  Matrix m{
      Matrix::Identity.scale(1, 0.5, 1) * Matrix::Identity.rotate_z(M_PI / 5.0)};
  s.Transform(m);

  // in the canonical form this is the Rotate first, followed by the scale!
  // s.Transform(Matrix::Identity.Rotate_z(M_PI / 5.0).Scale(1, 0.5, 1));
  Vector n{s.normal(Point(0, sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0))};
  EXPECT_EQ(n, Vector(0, 0.97014, -0.24254));
}

TEST(Shape, Reference)
{
  Sphere sp;
  Shape &p{sp}; // why is this here?
  SolidPattern pattern{Color(.5, .5, .5)};
  auto a = std::make_shared<Material>(Material(1.23, 1.7, 112.1, 20.1, 0.0, 0, 1, pattern));
  sp.material(a);
  EXPECT_FLOAT_EQ(sp.material().diffuse(), sp.material().diffuse());
}

TEST(Plane, Constant_Normal)
{
  Plane p;
  EXPECT_EQ(p.normal(Point(0, 0, 0)), Vector(0, 1, 0));
  EXPECT_EQ(p.normal(Point(10, 0, -10)), Vector(0, 1, 0));
  EXPECT_EQ(p.normal(Point(-5, 0, 150)), Vector(0, 1, 0));
}

TEST(Plane, Intersects_parallel)
{
  Plane p;
  Ray r{Point(0, 10, 0), Vector(0, 0, 1)};
  std::vector<Intersection> intersections{p.intersects(r)};
  EXPECT_EQ(intersections.empty(), true);
}

TEST(Plane, Intersects_Coplanar)
{
  Plane p;
  Ray r{Point(0, 0, 0), Vector(0, 0, 1)};
  std::vector<Intersection> intersections{p.intersects(r)};
  EXPECT_EQ(intersections.empty(), true);
}

TEST(Plane, Intersects_FromAbove)
{
  Plane p;
  Ray r{Point(0, 1, 0), Vector(0, -1, 0)};
  std::vector<Intersection> intersections{p.intersects(r)};
  EXPECT_EQ(intersections.size(), 1);
  EXPECT_EQ(intersections[0].t(), 1);
  EXPECT_EQ(intersections[0].GetShape(), &p);
}

TEST(Plane, Intersects_FromBelow)
{
  Plane p;
  Ray r{Point(0, -1, 0), Vector(0, 1, 0)};
  std::vector<Intersection> intersections{p.intersects(r)};
  EXPECT_EQ(intersections.size(), 1);
  EXPECT_EQ(intersections[0].t(), 1);
  EXPECT_EQ(intersections[0].GetShape(), &p);
}

