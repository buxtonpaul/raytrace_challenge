#include <string>
#include "canvas.h"
#include "color.h"
#include "gtest/gtest.h"
#include "utils.h"

TEST(Canvas, Canvas_Initialise)
{
  Canvas c{10, 20};
  for (unsigned int i = 0; i < c.width(); ++i)
  {
    for (unsigned int j = 0; j < c.height(); ++j)
    {
      EXPECT_EQ(c.Pixel(i, j), Color(0, 0, 0));
    }
  }
}

TEST(Canvas, Set_Pixel)
{
  Canvas c{10, 20};
  Color red{1, 0, 0};
  c.Pixel(2, 3, red);
  EXPECT_EQ(c.Pixel(2, 3), red);
}

TEST(Canvas, Canvas_to_ppm_header)
{
  Canvas c{5, 3};
  std::string header{"P3\n5 3\n255\n"};
  std::vector<std::string> ppm = splitlines(c.ppm());
  EXPECT_EQ(ppm[0], "P3");
  EXPECT_EQ(ppm[1], "5 3");
  EXPECT_EQ(ppm[2], "255");
}

TEST(Canvas, Canvas_to_ppm_data)
{
  Canvas c{5, 3};
  Color c1{1.5, 0, 0};
  Color c2{0, 0.5, 0};
  Color c3{-0.5, 0, 1};

  c.Pixel(0, 0, c1);
  c.Pixel(2, 1, c2);
  c.Pixel(4, 2, c3);

  std::vector<std::string> ppm{splitlines(c.ppm())};
  std::string l1{"255 0 0 0 0 0 0 0 0 0 0 0 0 0 0"};
  std::string l2{"0 0 0 0 0 0 0 128 0 0 0 0 0 0 0"};
  std::string l3{"0 0 0 0 0 0 0 0 0 0 0 0 0 0 255"};
  EXPECT_EQ(ppm[3], l1);
  EXPECT_EQ(ppm[4], l2);
  EXPECT_EQ(ppm[5], l3);
}

TEST(Canvas, ppm_long_lines)
{
  Canvas c{10, 2};
  Color c1{1, 0.8, 0.6};

  for (unsigned int i = 0; i < c.width(); ++i)
  {
    for (unsigned int j = 0; j < c.height(); ++j)
    {
      c.Pixel(i, j, c1);
    }
  }
  std::vector<std::string> ppm{splitlines(c.ppm())};
  std::string l1{"255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204"};
  std::string l2{"153 255 204 153 255 204 153 255 204 153 255 204 153"};

  EXPECT_EQ(ppm[3], l1);
  EXPECT_EQ(ppm[4], l2);
  EXPECT_EQ(ppm[5], l1);
  EXPECT_EQ(ppm[6], l2);
}
