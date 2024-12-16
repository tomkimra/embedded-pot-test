/**
 * @file test.cpp
 * @author tomkimra
 * @brief テストケース
 * @version 0.1
 * @date 2024-09-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <gtest/gtest.h>

int sum(int x, int y){
  return x+y;
}

TEST(Sample,1){
  int x=1, y=2;
  EXPECT_EQ(sum(x,y), x+y);
}
