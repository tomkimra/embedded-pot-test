/**
 * @file interface.h
 * @author tomkimra
 * @brief インターフェイス関数
 * @version 0.1
 * @date 2024-09-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

/// @brief 水面センサ読み取り
/// @return 1なら下限
int read_level();

/// @brief ロック解除ボタン読み取り
/// @return 1なら押下
int read_lock();

/// @brief 給湯ボタン読み取り
/// @return 1なら押下
int read_supply();

/// @brief 温度センサ読み取り
/// @return 摂氏温度
float read_temp();

/// @brief ヒータ出力変更
/// @param value 1ならON
void write_heater(int value);

/// @brief ポンプ出力変更
/// @param value 1ならON
void write_pump(int value);

/// @brief LED出力変更
/// @param value 1ならON
void write_led(int value);
