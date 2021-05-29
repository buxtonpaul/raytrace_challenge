#include <string>
#include "camera.h"
#include "canvas.h"
#include "color.h"
#include "gtest/gtest.h"
#include "matrix.h"
#include "rays.h"
#include "sphere.h"
#include "world.h"
#include "pattern.h"


using namespace ray_lib;

TEST(Camera, Camera_Initialise_test) { EXPECT_EQ(1, 1); }

TEST(Camera, Camera_Initialise_Zpos)
{
  Point from{0, 0, 0};
  Point to{0, 0, 1};
  Vector up{0, 1, 0};
  Matrix t{view_transform(from, to, up)};
  EXPECT_EQ(t, scale(-1, 1, -1));
}

TEST(Camera, Camera_Initialise_Zneg)
{
  Point from{0, 0, 8};
  Point to{0, 0, 0};
  Vector up{0, 1, 0};
  Matrix t{view_transform(from, to, up)};

  EXPECT_EQ(t, translation(0, 0, -8));
}

TEST(Camera, Camera_Initialise_arbitrary)
{
  Point from{1, 3, 2};
  Point to{4, -2, 8};
  Vector up{1, 1, 0};
  Matrix t{view_transform(from, to, up)};
  Matrix m{{{-0.50709, 0.50709, 0.67612, -2.36643},
            {0.76772, 0.60609, 0.12122, -2.82843},
            {-0.35857, 0.59761, -0.71714, 0.000},
            {0, 0, 0, 1}}};
  EXPECT_EQ(t, m);
}

TEST(Camera, Camera_initparams)
{
  Camera c{160, 120, M_PI / 2};

  EXPECT_FLOAT_EQ(c.fov(), M_PI / 2);
  EXPECT_EQ(c.h_size(), 160);
  EXPECT_EQ(c.v_size(), 120);
  EXPECT_EQ(c.view_transform(), Matrix::Identity);
}

TEST(Camera, Camera_pelsize1)
{
  Camera c{200, 125, M_PI / 2};

  EXPECT_FLOAT_EQ(c.pixel_size(), 0.01);
}

TEST(Camera, Camera_pelsize2)
{
  Camera c{125, 200, M_PI / 2};

  EXPECT_FLOAT_EQ(c.pixel_size(), 0.01);
}

TEST(Camera, Camera_raycenter)
{
  Camera c{201, 101, M_PI / 2};

  Ray r{c.ray_for_pixel(100, 50)};

  EXPECT_EQ(r.Origin(), Point(0, 0, 0));
  EXPECT_EQ(r.Direction(), Vector(0, 0, -1));
}

TEST(Camera, Camera_raycorner)
{
  Camera c{201, 101, M_PI / 2};

  Ray r{c.ray_for_pixel(0, 0)};

  EXPECT_EQ(r.Origin(), Point(0, 0, 0));
  EXPECT_EQ(r.Direction(), Vector(0.66519, 0.33259, -0.66851));
}

TEST(Camera, Camera_rayTransformed)
{
  Camera c{201, 101, M_PI / 2};

  c.view_transform(Matrix::Identity.translate(0, -2, 5).rotate_y(M_PI / 4));
  Ray r{c.ray_for_pixel(100, 50)};

  EXPECT_EQ(r.Origin(), Point(0, 2, -5));
  EXPECT_EQ(r.Direction(), Vector(sqrt(2.0) / 2.0, 0, -sqrt(2.0) / 2.0));
}

class DefaultWorldCameraTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    p.setColor(Color(0.8, 1, 0.6));
    m.pattern(p);

    m.diffuse(0.7);
    m.specular(0.2);
    l.position(Point(-10, 10, -10));
    l.intensity(Color(1, 1, 1));
    s1 = std::make_shared<Sphere> ( );
    s2 = std::make_shared<Sphere> ( );

    s2->Transform(Matrix::Identity.scale(0.5, 0.5, 0.5));
    w.WorldLights().push_back(&l);
    w.WorldShapes().push_back(s1);
    w.WorldShapes().push_back(s2);
    s1->material(m);
  }

  // put destructor here if required
  // void TearDown() override {}

  // Variables go here...

  Light l;
  Material m;
  std::shared_ptr<Sphere> s1;
  std::shared_ptr<Sphere> s2;
  World w;
  SolidPattern p;
};

TEST_F(DefaultWorldCameraTest, RenderTest)
{
  Camera c{11, 11, M_PI / 2};

  Point from{0, 0, -5};
  Point to{0, 0, 0};
  Vector up{0, 1, 0};
  c.view_transform(view_transform(from, to, up));
  Canvas image{c.render(&w)};
  EXPECT_EQ(image.pixel(5, 5), Color(0.38066, 0.47583, 0.2855));
}
