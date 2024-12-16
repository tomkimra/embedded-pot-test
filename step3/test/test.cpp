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

/// @brief Storeのprev情報をセット
/// @param lock 
/// @param supply 
void initStoreSupply(Store* store, int state, int lock, int supply){
  store->state_supply = state;
  store->btn_unlock = lock;
  store->btn_supply = supply;
}

//// Supply状態テスト
void testState(MockIO* mockIO, Store* store, 
    int lock, int supply, int level, float temp, 
    int expect_state, int expect_led, int expect_pump){
  EXPECT_CALL(*mockIO, read_lock).Times(1).WillOnce(Return(lock));
  EXPECT_CALL(*mockIO, read_supply).Times(1).WillOnce(Return(supply));
  EXPECT_CALL(*mockIO, read_level).Times(1).WillOnce(Return(level));
  EXPECT_CALL(*mockIO, read_temp).Times(1).WillOnce(Return(temp));
  if(expect_led>=0){
    EXPECT_CALL(*mockIO, write_led(expect_led)).Times(1);
  }
  if(expect_pump>=0){
    EXPECT_CALL(*mockIO, write_pump(expect_pump)).Times(1);
  }
  loopTask(store);
  EXPECT_EQ(store->state_supply, expect_state);
}

/// @brief 1-スイッチ 給湯状態遷移テスト
/// @param st0 初期状態
/// @param lock0 ロック解除ボタン 初期値
/// @param sup0 給湯ボタン 初期値
/// @param lock1 ロック解除ボタン 1ステップ目の値
/// @param sup1 給湯ボタン 1ステップ目の値
/// @param st1 1ステップ後の状態
/// @param led1 LED出力状態 1ステップ後アサーション
/// @param pump1 ポンプ出力状態 1ステップ後アサーション
/// @param lock2 ロック解除ボタン 2ステップ目の値
/// @param sup2 給湯ボタン 2ステップ目の値
/// @param st2 2ステップ後の状態
/// @param led2 LED出力状態 2ステップ後アサーション
/// @param pump2 ポンプ出力状態 2ステップ後アサーション
void one_switch(int st0, int lock0, int sup0,
                int lock1, int sup1, int st1, int led1, int pump1,
                int lock2, int sup2, int st2, int led2, int pump2){
  Store store;
  initStoreSupply(&store,(st0),(lock0),(sup0));
  MockIO mockIO;
  setMock(&mockIO);
  testState(&mockIO, &store,(lock1),(sup1),(0),(30),(st1),(led1),(pump1));
  testState(&mockIO, &store,(lock2),(sup2),(1),(100),(st2),(led2),(pump2));
}

TEST(SuuplyTest,1){ one_switch(ST0_IDLE,0,0,0,1,ST0_IDLE,-1,-1,0,0,ST0_IDLE,-1,-1);}
TEST(SuuplyTest,2){ one_switch(ST0_IDLE,0,1,0,0,ST0_IDLE,-1,-1,0,1,ST0_IDLE,-1,-1);}
TEST(SuuplyTest,3){ one_switch(ST0_IDLE,0,1,1,1,ST0_UNLOCK,1,-1,1,0,ST0_UNLOCK,-1,-1);}
TEST(SuuplyTest,4){ one_switch(ST0_IDLE,0,0,0,1,ST0_IDLE,-1,-1,1,1,ST0_UNLOCK,1,-1);}
TEST(SuuplyTest,5){ one_switch(ST0_IDLE,0,1,0,0,ST0_IDLE,-1,-1,1,0,ST0_UNLOCK,1,-1);}
TEST(SuuplyTest,6){ one_switch(ST0_IDLE,0,0,1,0,ST0_UNLOCK,1,-1,1,1,ST0_SUPPLY,-1,1);}
TEST(SuuplyTest,7){ one_switch(ST0_UNLOCK,0,0,1,0,ST0_IDLE,0,-1,1,1,ST0_IDLE,-1,-1);}
TEST(SuuplyTest,8){ one_switch(ST0_UNLOCK,0,1,1,1,ST0_IDLE,0,-1,1,0,ST0_IDLE,-1,-1);}
TEST(SuuplyTest,9){ one_switch(ST0_UNLOCK,0,1,0,0,ST0_UNLOCK,-1,-1,1,0,ST0_IDLE,0,-1);}
TEST(SuuplyTest,10){ one_switch(ST0_UNLOCK,0,0,0,1,ST0_SUPPLY,-1,1,0,0,ST0_UNLOCK,-1,0);}
TEST(SuuplyTest,11){ one_switch(ST0_UNLOCK,0,0,0,1,ST0_SUPPLY,-1,1,1,1,ST0_SUPPLY,-1,-1);}
TEST(SuuplyTest,12){ one_switch(ST0_UNLOCK,0,1,0,0,ST0_UNLOCK,-1,-1,0,1,ST0_SUPPLY,-1,1);}
TEST(SuuplyTest,13){ one_switch(ST0_SUPPLY,0,1,1,1,ST0_SUPPLY,-1,-1,1,0,ST0_UNLOCK,-1,0);}
TEST(SuuplyTest,14){ one_switch(ST0_SUPPLY,1,1,1,0,ST0_UNLOCK,-1,0,1,1,ST0_SUPPLY,-1,1);}

/// 加熱状態の初期化
void initStoreHeat(Store* store, int state){
  store->state_heat = state;
}

/// 1ループでのHeat状態チェック
void testHeat(MockIO* mockIO, Store* store, 
    int lock, int supply, int level, float temp, 
    int expect_state, int expect_heater){
  EXPECT_CALL(*mockIO, read_lock).Times(1).WillOnce(Return(lock));
  EXPECT_CALL(*mockIO, read_supply).Times(1).WillOnce(Return(supply));
  EXPECT_CALL(*mockIO, read_level).Times(1).WillOnce(Return(level));
  EXPECT_CALL(*mockIO, read_temp).Times(1).WillOnce(Return(temp));
  if(expect_heater>=0){
    EXPECT_CALL(*mockIO, write_heater(expect_heater)).Times(1);
  }
  loopTask(store);
  EXPECT_EQ(store->state_heat, expect_state);
}

/// @brief 0-スイッチ 加熱状態遷移テスト
/// @param st0 初期状態
/// @param lev0 水位センサ 初期値
/// @param temp0 温度センサ 初期値
/// @param lev1 水位センサ 次の値
/// @param temp1 温度センサ 次の値
/// @param st1 次状態
/// @param heat1 ヒータ出力状態アサーション
void zero_switch_heat(int st0, int lev0, float temp0,
                int lev1, float temp1, int st1, int heat1){
  Store store;
  initStoreHeat(&store,st0);
  MockIO mockIO;
  setMock(&mockIO);
  testHeat(&mockIO, &store, 0, 0, lev1, temp1, st1, heat1);
}

TEST(HeatTest,1){ zero_switch_heat(ST1_IDLE,0,90,0,89.9,ST1_HEAT,1);}
TEST(HeatTest,2){ zero_switch_heat(ST1_IDLE,0,90,0,90,ST1_IDLE,-1);}
TEST(HeatTest,3){ zero_switch_heat(ST1_IDLE,0,90,0,100,ST1_IDLE,-1);}
TEST(HeatTest,4){ zero_switch_heat(ST1_IDLE,0,90,1,89.9,ST1_IDLE,-1);}
TEST(HeatTest,5){ zero_switch_heat(ST1_HEAT,0,90,0,89.9,ST1_HEAT,-1);}
TEST(HeatTest,6){ zero_switch_heat(ST1_HEAT,0,90,0,90,ST1_HEAT,-1);}
TEST(HeatTest,7){ zero_switch_heat(ST1_HEAT,0,90,0,100,ST1_IDLE,0);}
TEST(HeatTest,8){ zero_switch_heat(ST1_HEAT,0,90,1,89.9,ST1_IDLE,0);}
