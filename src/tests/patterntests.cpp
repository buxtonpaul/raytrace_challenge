#include "color.h"
#include "gtest/gtest.h"
#include "pattern.h"
#include "tuples.h"
#include "sphere.h"
#include "matrix.h"
#include "light.h"

using ray_lib::Point;
using ray_lib::StripePattern;
using ray_lib::TestPattern;
using ray_lib::GradientPattern;
using ray_lib::RingPattern;
using ray_lib::CheckPattern3d;

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

TEST(Pattern, GenericPattern1)
{
  TestPattern p{ray_lib::Matrix::Identity};

  EXPECT_EQ(p.getTransform(), ray_lib::Matrix::Identity);
}

TEST(Pattern, GenericPattern2)
{
  TestPattern p{ray_lib::Translation(1, 2, 3)};

  EXPECT_EQ(p.getTransform(), ray_lib::Translation(1, 2, 3));
}

TEST(Pattern, GenericPattern3)
{
  TestPattern p;
  ray_lib::Sphere s1;
  s1.Transform(ray_lib::Scale(2, 2, 2));

  Color c{ray_lib::PatternAtObject(p, s1, Point(2, 3, 4))};

  EXPECT_EQ(c, Color(1, 1.5, 2));
}

TEST(Pattern, GenericPattern4)
{
  TestPattern p{ray_lib::Scale(2, 2, 2)};
  ray_lib::Sphere s1;

  // pattern at object is not applying the object transofm
  Color c{ray_lib::PatternAtObject(p, s1, Point(2, 3, 4))};

  EXPECT_EQ(c, Color(1, 1.5, 2));
}

TEST(Pattern, GenericPattern5)
{
  TestPattern p{ray_lib::Translation(0.5, 1, 1.5)};
  ray_lib::Sphere s1{ray_lib::Scale(2, 2, 2)};

  Color c{ray_lib::PatternAtObject(p, s1, Point(2.5, 3, 3.5))};

  EXPECT_EQ(c, Color(0.75, 0.5, 0.25));
}


TEST(Pattern, Gradientpattern1)
{
  GradientPattern p{Color::White, Color::Black};
  EXPECT_EQ(p.getColor({0, 0, 0}), Color::White);
  EXPECT_EQ(p.getColor({0.25, 0, 0}), Color(0.75, 0.75, 0.75));
  EXPECT_EQ(p.getColor({0.5, 0, 0}), Color(0.5, 0.5, 0.5));
  EXPECT_EQ(p.getColor({0.75, 0, 0}), Color(0.25, 0.25, 0.25));
}

TEST(Pattern, Ringpattern1)
{
  RingPattern p{Color::White, Color::Black};
  EXPECT_EQ(p.getColor({0, 0, 0}), Color::White);
  EXPECT_EQ(p.getColor({1, 0, 0}), Color::Black);
  EXPECT_EQ(p.getColor({0, 0, 1}), Color::Black);
  EXPECT_EQ(p.getColor({0.708, 0, 0.708}), Color::Black);
}



TEST(Pattern, CheckPatternRepeatX)
{
  CheckPattern3d p{Color::White, Color::Black};
  EXPECT_EQ(p.getColor({0, 0, 0}), Color::White);
  EXPECT_EQ(p.getColor({0.99, 0, 0}), Color::White);
  EXPECT_EQ(p.getColor({1.01, 0, 0}), Color::Black);
}

TEST(Pattern, CheckPatternRepeatY)
{
  CheckPattern3d p{Color::White, Color::Black};
  EXPECT_EQ(p.getColor({0, 0, 0}), Color::White);
  EXPECT_EQ(p.getColor({0, 0.99, 0}), Color::White);
  EXPECT_EQ(p.getColor({0, 1.01, 0}), Color::Black);
}

TEST(Pattern, CheckPatternRepeatZ)
{
  CheckPattern3d p{Color::White, Color::Black};
  EXPECT_EQ(p.getColor({0, 0, 0}), Color::White);
  EXPECT_EQ(p.getColor({0, 0, 0.99}), Color::White);
  EXPECT_EQ(p.getColor({0, 0, 1.01}), Color::Black);
}
