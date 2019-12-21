#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "utils.h"

TEST(float_equals, equals)
{
  EXPECT_EQ(float_equals(1.0, 1.0), true);
  EXPECT_EQ(float_equals(1.0, 1.5), false);
  EXPECT_EQ(float_equals(1.0, 1.00001), true);
}

TEST(string_split, simpletest)
{
  std::string sample("P3\n5 3\n255\n");
  std::vector<std::string> split = splitlines(sample);

  EXPECT_EQ(split[0], "P3");
  EXPECT_EQ(split[1], "5 3");
}

TEST(string, limit_length)
{
  std::string a("123 456 7");
  EXPECT_EQ(limitlinelength(a, 12), "123 456 7");
  EXPECT_EQ(limitlinelength(a, 5), "123\n456\n7");
}