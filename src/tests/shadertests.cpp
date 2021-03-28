#include <cmath>
#include "color.h"
#include "gtest/gtest.h"
#include "light.h"
#include "material.h"
#include "matrix.h"
#include "rays.h"
#include "sphere.h"
#include "tuples.h"
#include "pattern.h"

using ray_lib::Light;
using ray_lib::Material;
using ray_lib::Point;
using ray_lib::Sphere;
using ray_lib::Vector;

TEST(Shader, Material)
{
  Material m;
  EXPECT_FLOAT_EQ(m.Ambient(), 0.1);
  EXPECT_FLOAT_EQ(m.Diffuse(), 0.9);
  EXPECT_FLOAT_EQ(m.Specular(), 0.9);
  EXPECT_FLOAT_EQ(m.Shininess(), 200);
}
TEST(Shader, Sphere_mat)
{
  Material m;
  Sphere s;
  EXPECT_EQ(m, s.Mat());
}

TEST(Shader, Sphere_mat_assign)
{
  Sphere s;
  Material m;
  m.Ambient(1);
  s.Mat(m);
  EXPECT_EQ(s.Mat(), m);
}

TEST(Shader, lighting1)
{
  Material m;
  ray_lib::SolidPattern s;
  m.SetPattern(s.asPattern());
  Point p{0, 0, 0};
  Sphere sp;

  Vector eyev{0, 0, -1};
  Vector normalv{0, 0, -1};
  Light point_light{Color(1, 1, 1), Point(0, 0, -10)};
  Color result{ray_lib::lighting(m, point_light, p, eyev, normalv, sp)};
  EXPECT_EQ(result, Color(1.9, 1.9, 1.9));
}

TEST(Shader, lighting2)
{
  Material m;
  ray_lib::SolidPattern s;
  m.SetPattern(s.asPattern());

  Point p{0, 0, 0};
  Sphere sp;
  Vector eyev{0, sqrt(2.0) / 2.0, sqrt(2.0) / 2.0};
  Vector normalv{0, 0, -1};
  Light point_light{Color(1, 1, 1), Point(0, 0, -10)};
  Color result{ray_lib::lighting(m, point_light, p, eyev, normalv, sp)};
  EXPECT_EQ(result, Color(1.0, 1.0, 1.0));
}

TEST(Shader, lighting3)
{
  Material m;
  ray_lib::SolidPattern s;
  m.SetPattern(s.asPattern());

  Point p{0, 0, 0};
  Sphere sp;
  Vector eyev{0, 0, -1};
  Vector normalv{0, 0, -1};
  Light point_light{Color(1, 1, 1), Point(0, 10, -10)};
  Color result{ray_lib::lighting(m, point_light, p, eyev, normalv, sp)};
  EXPECT_EQ(result, Color(0.7364, 0.7364, 0.7364));
}

TEST(Shader, lighting4)
{
  Material m;
  ray_lib::SolidPattern s;
  m.SetPattern(s.asPattern());

  Point p{0, 0, 0};
  Sphere sp;
  Vector eyev{0, -sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0};
  Vector normalv{0, 0, -1};
  Light point_light{Color(1, 1, 1), Point(0, 10, -10)};
  Color result{ray_lib::lighting(m, point_light, p, eyev, normalv, sp)};
  EXPECT_EQ(result, Color(1.6364, 1.6364, 1.6364));
}

TEST(Shader, lighting5)
{
  Material m;
  ray_lib::SolidPattern s;
  m.SetPattern(s.asPattern());

  Point p{0, 0, 0};
  Sphere sp;
  Vector eyev{0, 0, -1};
  Vector normalv{0, 0, -1};
  Light point_light(Color(1, 1, 1), Point(0, 0, 10));
  Color result = ray_lib::lighting(m, point_light, p, eyev, normalv, sp);
  EXPECT_EQ(result, Color(0.1, 0.1, 0.1));
}

TEST(Shader, inshadow1)
{
  Material m;
  ray_lib::SolidPattern s;
  m.SetPattern(s.asPattern());

  Point p{0, 0, 0};
  Sphere sp;
  Vector eyev{0, 0, -1};
  Vector normalv{0, 0, -1};
  Light point_light{Color(1, 1, 1), Point(0, 0, -10)};
  bool inShadow{true};
  Color result{ray_lib::lighting(m, point_light, p, eyev, normalv, sp, inShadow)};
  EXPECT_EQ(result, Color(0.1, 0.1, 0.1));
}

TEST(Shader, Pattern1)
{
  ray_lib::StripePattern s(Color(1, 1, 1), Color(0, 0, 0));
  Material m(1.0, 0.0, 0.0, 0.0, (ray_lib::Pattern *)&s);

  Vector eyev{0, 0, -1};
  Vector normalv{0, 0, -1};
  Sphere sp;
  Light point_light{Color(1, 1, 1), Point(0, 0, -10)};
  Point p{0, 0, 0};
  Color c1{ray_lib::lighting(m, point_light, Point(0.9, 0, 0), eyev, normalv, sp, false)};
  Color c2{ray_lib::lighting(m, point_light, Point(1.1, 0, 0), eyev, normalv, sp, false)};

  EXPECT_EQ(c1, Color(1, 1, 1));
  EXPECT_EQ(c2, Color(0, 0, 0));
}
