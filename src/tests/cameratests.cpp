#include <string>
#include "camera.h"
#include "canvas.h"
#include "color.h"
#include "gtest/gtest.h"
#include "matrix.h"
#include "rays.h"
#include "sphere.h"
#include "world.h"

using ray_lib::Camera;
using ray_lib::Matrix;
using ray_lib::Point;
using ray_lib::Ray;
using ray_lib::Sphere;
using ray_lib::Vector;

TEST(Camera, Camera_Initialise_test) { EXPECT_EQ(1, 1); }

TEST(Camera, Camera_Initialise_Zpos) {
  Point from(0, 0, 0);
  Point to(0, 0, 1);
  Vector up(0, 1, 0);
  Matrix t = ray_lib::view_transform(from, to, up);
  EXPECT_EQ(t, ray_lib::Scale(-1, 1, -1));
}

TEST(Camera, Camera_Initialise_Zneg) {
  Point from(0, 0, 8);
  Point to(0, 0, 0);
  Vector up(0, 1, 0);
  Matrix t = ray_lib::view_transform(from, to, up);

  EXPECT_EQ(t, ray_lib::Translation(0, 0, -8));
}

TEST(Camera, Camera_Initialise_arbitrary) {
  Point from(1, 3, 2);
  Point to(4, -2, 8);
  Vector up(1, 1, 0);
  Matrix t = ray_lib::view_transform(from, to, up);
  Matrix m({{-0.50709, 0.50709, 0.67612, -2.36643},
            {0.76772, 0.60609, 0.12122, -2.82843},
            {-0.35857, 0.59761, -0.71714, 0.000},
            {0, 0, 0, 1}});
  EXPECT_EQ(t, m);
}

TEST(Camera, Camera_initparams) {
  Camera c(160, 120, M_PI / 2);

  EXPECT_FLOAT_EQ(c.FOV(), M_PI / 2);
  EXPECT_EQ(c.HSize(), 160);
  EXPECT_EQ(c.VSize(), 120);
  EXPECT_EQ(c.viewTransform(), ray_lib::Matrix::Identity);
}

TEST(Camera, Camera_pelsize1) {
  Camera c(200, 125, M_PI / 2);

  EXPECT_FLOAT_EQ(c.pixelSize(), 0.01);
}

TEST(Camera, Camera_pelsize2) {
  Camera c(125, 200, M_PI / 2);

  EXPECT_FLOAT_EQ(c.pixelSize(), 0.01);
}

TEST(Camera, Camera_raycenter) {
  Camera c(201, 101, M_PI / 2);

  Ray r = c.ray_for_pixel(100, 50);

  EXPECT_EQ(r.Origin(), Point(0, 0, 0));
  EXPECT_EQ(r.Direction(), Vector(0, 0, -1));
}

TEST(Camera, Camera_raycorner) {
  Camera c(201, 101, M_PI / 2);

  Ray r = c.ray_for_pixel(0, 0);

  EXPECT_EQ(r.Origin(), Point(0, 0, 0));
  EXPECT_EQ(r.Direction(), Vector(0.66519, 0.33259, -0.66851));
}

TEST(Camera, Camera_rayTransformed) {
  Camera c(201, 101, M_PI / 2);

  c.viewTransform(Matrix::Identity.Translate(0, -2, 5).Rotate_y(M_PI / 4));
  Ray r = c.ray_for_pixel(100, 50);

  EXPECT_EQ(r.Origin(), Point(0, 2, -5));
  EXPECT_EQ(r.Direction(), Vector(sqrt(2.0) / 2.0, 0, -sqrt(2.0) / 2.0));
}

class DefaultWorldCameraTest : public ::testing::Test {
 protected:
  void SetUp() override {
    m.SetColor(Color(0.8, 1, 0.6));
    m.Diffuse(0.7);
    m.Specular(0.2);
    l.Position(ray_lib::Point(-10, 10, -10));
    l.Intensity(Color(1, 1, 1));
    s2.Transform(Matrix::Identity.Scale(0.5, 0.5, 0.5));
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

TEST_F(DefaultWorldCameraTest, RenderTest) {
  Camera c(11, 11, M_PI / 2);

  Point from(0, 0, -5);
  Point to(0, 0, 0);
  Vector up(0, 1, 0);
  c.viewTransform(ray_lib::view_transform(from, to, up));
  Canvas image = c.Render(w);
  EXPECT_EQ(image.Pixel(5, 5), Color(0.38066, 0.47583, 0.2855));
}
