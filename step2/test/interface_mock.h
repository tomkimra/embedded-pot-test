/**
 * @file interface_mock.h
 * @author tomkimra
 * @brief インターフェイスのテスト用関数
 * @version 0.1
 * @date 2024-09-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <gmock/gmock.h>

class MockIO {
public:
  MOCK_METHOD(int, read_lock, ());
  MOCK_METHOD(int, read_supply, ());
  MOCK_METHOD(int, read_level, ());
  MOCK_METHOD(float, read_temp, ());
  MOCK_METHOD(void, write_heater, (int value));
  MOCK_METHOD(void, write_pump, (int value));
  MOCK_METHOD(void, write_led, (int value));
};
void setMock(MockIO* m);
