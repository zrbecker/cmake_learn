#include <gtest/gtest.h>

TEST(MyFirstTestSuite, CheckOneNotEqualToTwo) {
  ASSERT_NE(1, 2);
}

TEST(MyFirstTestSuite, CheckOneEqualToOne) {
  ASSERT_EQ(1, 1);
}

TEST(MyFirstTestSuite, CheckFiveEqualToFive) {
  ASSERT_EQ(5, 5);
}