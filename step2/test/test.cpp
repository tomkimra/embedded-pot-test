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

extern "C" {
#include "controller.h"
}
#include "interface_mock.h"

using ::testing::Mock;
using ::testing::Return;

// 最初のテストケース
TEST(HeatTest,1){
  Store store;
  store.state_heat = ST1_IDLE;
  // mock設定
  MockIO mockIO;
  setMock(&mockIO);
  EXPECT_CALL(mockIO, read_lock).Times(1).WillOnce(Return(0)); // 任意
  EXPECT_CALL(mockIO, read_supply).Times(1).WillOnce(Return(0)); // 任意
  EXPECT_CALL(mockIO, read_level).Times(1).WillOnce(Return(0));
  EXPECT_CALL(mockIO, read_temp).Times(1).WillOnce(Return(90));
  // テスト対象実行
  loopTask(&store);
  EXPECT_EQ(store.state_heat, ST1_IDLE);
}
