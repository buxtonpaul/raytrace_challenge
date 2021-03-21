#include "color.h"
#include "gtest/gtest.h"
#include "pattern.h"
#include "tuples.h"

using ray_lib::Point;
using ray_lib::StripePattern;

TEST(Pattern, Stripe_ConstantY) {
  StripePattern a(Color::White, Color::Black);

  EXPECT_EQ(a.getColor(Point(0, 0, 0)), Color::White);
  EXPECT_EQ(a.getColor(Point(0, 1, 0)), Color::White);
  EXPECT_EQ(a.getColor(Point(0, 2, 0)), Color::White);
}

TEST(Pattern, Stripe_ConstantZ) {
  StripePattern a(Color::White, Color::Black);

  EXPECT_EQ(a.getColor(Point(0, 0, 0)), Color::White);
  EXPECT_EQ(a.getColor(Point(0, 0, 1)), Color::White);
  EXPECT_EQ(a.getColor(Point(0, 0, 2)), Color::White);
}

TEST(Pattern, Stripe_AlternateX) {
  StripePattern a(Color::White, Color::Black);

  EXPECT_EQ(a.getColor(Point(0, 0, 0)), Color::White);
  EXPECT_EQ(a.getColor(Point(0.9, 0, 0)), Color::White);

  EXPECT_EQ(a.getColor(Point(1, 0, 0)), Color::Black);
  EXPECT_EQ(a.getColor(Point(-0.1, 0, 0)), Color::Black);

  EXPECT_EQ(a.getColor(Point(-1, 0, 0)), Color::Black);
  EXPECT_EQ(a.getColor(Point(-1.1, 0, 0)), Color::White);
}
