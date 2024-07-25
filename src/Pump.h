#ifndef PUMP_H
#define PUMP_H

#include <chrono>
#include <cstdint>
#include <string>

#include "GPIOController.h"

using namespace std;

class Pump {
protected:
  string getDateTimeString(chrono::system_clock::time_point time_point) const;
  enum PumpState { OFF, ON };

private:
  PumpState state;
  uint16_t pin;
  GPIOController *gpio = nullptr;
  chrono::system_clock::time_point last_on;
  chrono::system_clock::time_point last_off;

public:
  Pump(uint16_t pin, GPIOController *_gpio);

  PumpState getState() const;
  string getLastOnDateTime() const;
  string getLastOffDateTime() const;

  void turnOn();
  void turnOff();
};

#endif // PUMP_H