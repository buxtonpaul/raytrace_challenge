#include "color.h"
#include "gtest/gtest.h"

TEST(Color, Basic_colors) {
  Color a({-0.5, 0.4, -1.7});
  EXPECT_FLOAT_EQ(a.red(), -0.5);
  EXPECT_FLOAT_EQ(a.green(), 0.4);
  EXPECT_FLOAT_EQ(a.blue(), -1.7);
}

TEST(Color, Color_add) {
  Color c1({0.9, 0.6, 0.75});
  Color c2({0.7, 0.1, 0.25});

  EXPECT_EQ(c1 + c2, Color({1.6, 0.7, 1.0}));
}

TEST(Color, Color_sub) {
  Color c1({0.9, 0.6, 0.75});
  Color c2({0.7, 0.1, 0.25});

  EXPECT_EQ(c1 - c2, Color({0.2, 0.5, 0.5}));
}

TEST(Color, Color_scalar_multiply) {
  Color c1({0.2, 0.3, 0.4});

  EXPECT_EQ(c1 * 2.0, Color({0.4, 0.6, 0.8}));
}

TEST(Color, Color_multiply) {
  Color c1({1.0, 0.2, 0.4});
  Color c2({0.9, 1.0, 0.1});

  EXPECT_EQ(c1 * c2, Color({0.9, 0.2, 0.04}));
}
