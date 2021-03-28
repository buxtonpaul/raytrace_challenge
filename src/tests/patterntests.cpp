#include "color.h"
#include "gtest/gtest.h"
#include "pattern.h"
#include "tuples.h"
#include "sphere.h"
#include "matrix.h"
#include "light.h"

using ray_lib::Point;
using ray_lib::StripePattern;

TEST(Pattern, Stripe_ConstantY)
{
  StripePattern a{Color::White, Color::Black};

  EXPECT_EQ(a.getColor(Point{0, 0, 0}), Color::White);
  EXPECT_EQ(a.getColor(Point{0, 1, 0}), Color::White);
  EXPECT_EQ(a.getColor(Point{0, 2, 0}), Color::White);
}

TEST(Pattern, Stripe_ConstantZ)
{
  StripePattern a(Color::White, Color::Black);

  EXPECT_EQ(a.getColor(Point{0, 0, 0}), Color::White);
  EXPECT_EQ(a.getColor(Point{0, 0, 1}), Color::White);
  EXPECT_EQ(a.getColor(Point{0, 0, 2}), Color::White);
}

TEST(Pattern, Stripe_AlternateX)
{
  StripePattern a(Color::White, Color::Black);

  EXPECT_EQ(a.getColor(Point{0, 0, 0}), Color::White);
  EXPECT_EQ(a.getColor(Point{0.9, 0, 0}), Color::White);

  EXPECT_EQ(a.getColor(Point{1, 0, 0}), Color::Black);
  EXPECT_EQ(a.getColor(Point{-0.1, 0, 0}), Color::Black);

  EXPECT_EQ(a.getColor(Point{-1, 0, 0}), Color::Black);
  EXPECT_EQ(a.getColor(Point{-1.1, 0, 0}), Color::White);
}

// patterns with transforms
// the lookup function into the pattern needs to support
// an object transform
// a pattern transform
// Would expect both pattern colors, and transform to be associated with the object?
// should assocaite the pattern transform with the pattern, and pass the object transform in when querying the color

TEST(Pattern, Stripe_ObjectTransform)
{
  ray_lib::Sphere s1;
  s1.Transform(ray_lib::Scale(2, 2, 2));

  StripePattern p{Color::White, Color::Black};

  Color c{ray_lib::PatternAtObject(p, s1, Point(1.5, 0, 0))};

  EXPECT_EQ(c, Color::White);
}

TEST(Pattern, Stripe_PatternTransform)
{
  ray_lib::Sphere s1;

  StripePattern p{Color::White, Color::Black, ray_lib::Scale(2, 2, 2)};

  Color c{ray_lib::PatternAtObject(p, s1, Point(1.5, 0, 0))};

  EXPECT_EQ(c, Color::White);
}

TEST(Pattern, Stripe_ObjectPatternTransform)
{

  ray_lib::Sphere s1;
  s1.Transform(ray_lib::Scale(2, 2, 2));

  StripePattern p{Color::White, Color::Black, ray_lib::Translation(0.5, 0, 0)};

  Color c{ray_lib::PatternAtObject(p, s1, Point(2.5, 0, 0))};

  EXPECT_EQ(c, Color::White);

}
