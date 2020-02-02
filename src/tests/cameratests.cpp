#include <string>
#include "camera.h"
#include "gtest/gtest.h"
#include "matrix.h"

using ray_lib::Matrix;
using ray_lib::Point;
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
