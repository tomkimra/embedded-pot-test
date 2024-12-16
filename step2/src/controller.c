/**
 * @file controller.c
 * @author tomkimra
 * @brief 制御ロジックモジュール
 * @version 0.1
 * @date 2024-09-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "controller.h"
#include "interface.h"

void loopTask(Store* store){
  updateSensors(store);
  updateState(store);
}

void updateSensors(Store* store){
  // 前状態を保存
  store->prev_btn_unlock = store->btn_unlock;
  store->prev_btn_supply = store->btn_supply;
  // 現状態を取得
  store->btn_unlock = read_lock();
  store->btn_supply = read_supply();
  store->level = read_level();
  store->temp = read_temp();
}

void updateState(Store* store){
  // 給湯状態の更新
  switch(store->state_supply){
  case ST0_IDLE:
    if(!store->prev_btn_unlock && store->btn_unlock ){
      store->state_supply = ST0_UNLOCK;
      write_led(1);
    }
    break;
  case ST0_UNLOCK: 
    if(!store->prev_btn_unlock && store->btn_unlock){
      store->state_supply = ST0_IDLE;
      write_led(0);
    } else if(!store->prev_btn_supply && store->btn_supply){
      store->state_supply = ST0_SUPPLY;
      write_pump(1);
    }
    break;
  case ST0_SUPPLY:
    if(!store->btn_supply){
      store->state_supply = ST0_UNLOCK;
      write_pump(0);
    }
    break;
  default:
    break;
  }
  // 加熱状態の更新
  switch(store->state_heat){
  case ST1_IDLE:
    if(!store->level && store->temp<90){
      store->state_heat = ST1_HEAT;
      write_heater(1);
    }
    break;
  case ST1_HEAT:
    if(store->level || store->temp>=100){
      store->state_heat = ST1_IDLE;
      write_heater(0);
    }
    break;
  default:
    break;
  }
}


