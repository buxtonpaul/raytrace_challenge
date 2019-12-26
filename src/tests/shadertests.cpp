#include <cmath>
#include "color.h"
#include "gtest/gtest.h"
#include "light.h"
#include "material.h"
#include "matrix.h"
#include "rays.h"
#include "sphere.h"
#include "tuples.h"

using ray_lib::Light;
using ray_lib::Material;
using ray_lib::Point;
using ray_lib::Sphere;
using ray_lib::Vector;

TEST(Shader, Material) {
  Material m;
  EXPECT_FLOAT_EQ(m.Ambient(), 0.1);
  EXPECT_FLOAT_EQ(m.Diffuse(), 0.9);
  EXPECT_FLOAT_EQ(m.Specular(), 0.9);
  EXPECT_FLOAT_EQ(m.Shininess(), 200);
  EXPECT_EQ(m.GetColor(), Color(1, 1, 1));
}
TEST(Shader, Sphere_mat) {
  Material m;
  Sphere s;
  EXPECT_EQ(m, s.Mat());
}

TEST(Shader, Sphere_mat_assign) {
  Sphere s;
  Material m;
  m.Ambient(1);
  s.Mat(m);
  EXPECT_EQ(s.Mat(), m);
}

TEST(Shader, lighting1) {
  Material m;
  Point p(0, 0, 0);

  Vector eyev(0, 0, -1);
  Vector normalv(0, 0, -1);
  Light point_light(Color(1, 1, 1), Point(0, 0, -10));
  Color result = ray_lib::lighting(m, point_light, p, eyev, normalv);
  EXPECT_EQ(result, Color(1.9, 1.9, 1.9));
}

TEST(Shader, lighting2) {
  Material m;
  Point p(0, 0, 0);

  Vector eyev(0, sqrt(2.0) / 2.0, sqrt(2.0) / 2.0);
  Vector normalv(0, 0, -1);
  Light point_light(Color(1, 1, 1), Point(0, 0, -10));
  Color result = ray_lib::lighting(m, point_light, p, eyev, normalv);
  EXPECT_EQ(result, Color(1.0, 1.0, 1.0));
}

TEST(Shader, lighting3) {
  Material m;
  Point p(0, 0, 0);

  Vector eyev(0, 0, -1);
  Vector normalv(0, 0, -1);
  Light point_light(Color(1, 1, 1), Point(0, 10, -10));
  Color result = ray_lib::lighting(m, point_light, p, eyev, normalv);
  EXPECT_EQ(result, Color(0.7364, 0.7364, 0.7364));
}

TEST(Shader, lighting4) {
  Material m;
  Point p(0, 0, 0);

  Vector eyev(0, -sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0);
  Vector normalv(0, 0, -1);
  Light point_light(Color(1, 1, 1), Point(0, 10, -10));
  Color result = ray_lib::lighting(m, point_light, p, eyev, normalv);
  EXPECT_EQ(result, Color(1.6364, 1.6364, 1.6364));
}

TEST(Shader, lighting5) {
  Material m;
  Point p(0, 0, 0);

  Vector eyev(0, 0, -1);
  Vector normalv(0, 0, -1);
  Light point_light(Color(1, 1, 1), Point(0, 0, 10));
  Color result = ray_lib::lighting(m, point_light, p, eyev, normalv);
  EXPECT_EQ(result, Color(0.1, 0.1, 0.1));
}