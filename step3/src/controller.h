/**
 * @file controller.h
 * @author tomkimra
 * @brief 制御ロジックモジュール
 * @version 0.1
 * @date 2024-09-22
 * 
 * @copyright Copyright (c) 
 * 
 */

#pragma once

/// 状態の定義
// 給湯状態 state_supply
#define ST0_IDLE 0    // 初期状態(ロック中)
#define ST0_UNLOCK 1  // ロック解除中
#define ST0_SUPPLY 2  // 給湯中
// 加熱状態 state_heat
#define ST1_IDLE 0    // 非加熱中
#define ST1_HEAT 1    // 加熱中

/// @brief 制御ロジック内部状態
typedef struct _Store {
  int state_supply;     // 給湯状態
  int state_heat;       // 加熱状態
  int btn_unlock;       // ロック解除ボタン値
  int prev_btn_unlock;  // 前期のロック解除ボタン値
  int btn_supply;       // 給湯ボタン値
  int prev_btn_supply;  // 前期の給湯ボタン値
  int level;            // 水面センサ値
  float temp;           // 温度センサ値
  float prev_temp;      // 前期の温度センサ値(不使用)
} Store;

/// @brief ループ関数
/// @param store 内部状態
void loopTask(Store* store);

/// @brief センサ更新
/// @param store 内部状態
void updateSensors(Store* store);

/// @brief 状態更新
/// @param store 内部状態
void updateState(Store* store);
