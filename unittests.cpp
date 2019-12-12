#include "gtest/gtest.h"
#include "tuples.h"

TEST(GtestTest, CheckGtest) {
  EXPECT_EQ(add(2,3), 5);
  EXPECT_EQ(add(4,5), 9);
}