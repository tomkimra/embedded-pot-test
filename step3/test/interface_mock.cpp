/**
 * @brief 
 * 
 */

extern "C" {
#include "interface.h"
}
#include "interface_mock.h"

MockIO *mockIO;
void setMock(MockIO* m){
  mockIO = m;
}

extern "C" {
  int read_lock(){ return mockIO->read_lock(); }
  int read_supply(){ return mockIO->read_supply(); }
  int read_level(){ return mockIO->read_level(); }
  float read_temp(){ return mockIO->read_temp(); }
  void write_heater(int value){ return mockIO->write_heater(value); }
  void write_pump(int value){ return mockIO->write_pump(value); }
  void write_led(int value){ return mockIO->write_led(value); }
}
