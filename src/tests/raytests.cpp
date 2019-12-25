#include "gtest/gtest.h"
#include "matrix.h"
#include "rays.h"
#include "sphere.h"
#include "tuples.h"

using ray_lib::Intersection;
using ray_lib::Matrix;
using ray_lib::Point;
using ray_lib::Ray;
using ray_lib::Vector;

TEST(Ray, Createray) {
  Point p(1, 2, 3);
  Vector d(4, 5, 6);
  Ray r(p, d);
  EXPECT_EQ(r.Origin(), p);
  EXPECT_EQ(r.Direction(), d);
}

TEST(Ray, Position) {
  Ray r(Point(2, 3, 4), Vector(1, 0, 0));

  EXPECT_EQ(r.Position(0), Point(2, 3, 4));
  EXPECT_EQ(r.Position(1), Point(3, 3, 4));
  EXPECT_EQ(r.Position(-1), Point(1, 3, 4));
  EXPECT_EQ(r.Position(2.5), Point(4.5, 3, 4));
}

TEST(Ray, SphereNormal) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  ray_lib::Sphere s;
  std::vector<Intersection> intersections = s.intersects(r);
  EXPECT_EQ(intersections.size(), 2);
  EXPECT_FLOAT_EQ(intersections[0].t(), 4.0);
  EXPECT_FLOAT_EQ(intersections[1].t(), 6.0);
}

TEST(Ray, SphereTangent) {
  Ray r(Point(0, 1, -5), Vector(0, 0, 1));
  ray_lib::Sphere s;
  std::vector<Intersection> intersections = s.intersects(r);
  EXPECT_EQ(intersections.size(), 2);
  EXPECT_FLOAT_EQ(intersections[0].t(), 5.0);
  EXPECT_FLOAT_EQ(intersections[1].t(), 5.0);
}

TEST(Ray, SphereMiss) {
  Ray r(Point(0, 2, -5), Vector(0, 0, 1));
  ray_lib::Sphere s;
  std::vector<Intersection> intersections = s.intersects(r);
  EXPECT_EQ(intersections.size(), 0);
}

TEST(Ray, Sphere_Ray_origin) {
  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  ray_lib::Sphere s;
  std::vector<Intersection> intersections = s.intersects(r);
  EXPECT_EQ(intersections.size(), 2);
  EXPECT_FLOAT_EQ(intersections[0].t(), -1);
  EXPECT_FLOAT_EQ(intersections[1].t(), 1);
}

TEST(Ray, Sphere_Ray_behind) {
  Ray r(Point(0, 0, 5), Vector(0, 0, 1));
  ray_lib::Sphere s;
  std::vector<Intersection> intersections = s.intersects(r);
  EXPECT_EQ(intersections.size(), 2);
  EXPECT_FLOAT_EQ(intersections[0].t(), -6);
  EXPECT_FLOAT_EQ(intersections[1].t(), -4);
}

TEST(Ray, IntersctionHandle) {
  Ray r(Point(0, 0, 5), Vector(0, 0, 1));
  ray_lib::Sphere s;
  Intersection i(&s, 3.5, r);
  EXPECT_FLOAT_EQ(i.t(), 3.5);
  EXPECT_EQ(i.GetShape(), &s);
  EXPECT_EQ(&i.GetRay(), &r);
}

TEST(Ray, AggregateIntersections) {
  Ray r(Point(0, 0, 5), Vector(0, 0, 1));
  ray_lib::Sphere s;
  ray_lib::Shape &l = s;
  std::vector<Intersection> intersections = s.intersects(r);
  EXPECT_EQ(intersections.size(), 2);
  EXPECT_EQ(intersections[0].GetShape(), &s);
  EXPECT_EQ(intersections[1].GetShape(), &s);
  EXPECT_EQ(&intersections[0].GetRay(), &r);
  EXPECT_EQ(&intersections[1].GetRay(), &r);
}

TEST(Ray, Intersection_Hits1) {
  Ray r(Point(0, 0, 5), Vector(0, 0, 1));
  ray_lib::Sphere s;

  std::vector<Intersection> i;
  Intersection i1(&s, 1, r);
  Intersection i2(&s, 2, r);
  i.push_back(i1);
  i.push_back(i2);
  EXPECT_EQ(i1 < i2, true);
  const Intersection *xs = ray_lib::Intersection::GetHit(i);
  EXPECT_EQ(*xs, i1);
}

TEST(Ray, Intersection_Hits2) {
  Ray r(Point(0, 0, 5), Vector(0, 0, 1));
  ray_lib::Sphere s;

  std::vector<Intersection> i;
  Intersection i1(&s, -1, r);
  Intersection i2(&s, 1, r);
  i.push_back(i1);
  i.push_back(i2);
  const Intersection *xs = ray_lib::Intersection::GetHit(i);
  EXPECT_EQ(*xs, i2);
}
TEST(Ray, Intersection_Hits3) {
  Ray r(Point(0, 0, 5), Vector(0, 0, 1));
  ray_lib::Sphere s;

  std::vector<Intersection> i;
  Intersection i1(&s, -2, r);
  Intersection i2(&s, -1, r);
  i.push_back(i1);
  i.push_back(i2);
  const Intersection *xs = ray_lib::Intersection::GetHit(i);
  EXPECT_EQ(xs, nullptr);
}
TEST(Ray, Intersection_Hits4) {
  Ray r(Point(0, 0, 5), Vector(0, 0, 1));
  ray_lib::Sphere s;

  std::vector<Intersection> i;
  Intersection i1(&s, 5, r);
  Intersection i2(&s, 7, r);
  Intersection i3(&s, -3, r);
  Intersection i4(&s, 2, r);
  i.push_back(i1);
  i.push_back(i2);
  i.push_back(i3);
  i.push_back(i4);
  const Intersection *xs = ray_lib::Intersection::GetHit(i);
  EXPECT_EQ(*xs, i4);
}

TEST(Ray, RayTranslation) {
  Ray r(Point(1, 2, 3), Vector(0, 1, 0));
  Matrix m(Matrix::Identity.Translate(3, 4, 5));
  Ray r2 = r.Transform(m);
  EXPECT_EQ(r2.Origin(), Point(4, 6, 8));
  EXPECT_EQ(r2.Direction(), Vector(0, 1, 0));
}

TEST(Ray, RayScaling) {
  Ray r(Point(1, 2, 3), Vector(0, 1, 0));
  Matrix m(Matrix::Identity.Scale(2, 3, 4));
  Ray r2 = r.Transform(m);
  EXPECT_EQ(r2.Origin(), Point(2, 6, 12));
  EXPECT_EQ(r2.Direction(), Vector(0, 3, 0));
}

TEST(Sphere, DefaultTransform) {
  ray_lib::Sphere s;
  Matrix m = s.Transform();
  EXPECT_EQ(m, Matrix::Identity);
}

TEST(Sphere, SetTransform) {
  ray_lib::Sphere s;
  Matrix transform = Matrix::Identity.Translate(2, 3, 4);
  s.Transform(transform);
  EXPECT_EQ(s.Transform(), transform);
}

TEST(Ray, ScaledSphereIntersection) {
  ray_lib::Sphere s;
  ray_lib::Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  s.Transform(Matrix::Identity.Scale(2, 2, 2));
  std::vector<Intersection> i = s.intersects(r);
  EXPECT_EQ(i.size(), 2);
  EXPECT_EQ(i[0].t(), 3);
  EXPECT_EQ(i[1].t(), 7);
}

TEST(Ray, TranslatedSphereIntersection) {
  ray_lib::Sphere s;
  ray_lib::Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  s.Transform(Matrix::Identity.Translate(5, 0, 0));
  std::vector<Intersection> i = s.intersects(r);
  EXPECT_EQ(i.size(), 0);
}
