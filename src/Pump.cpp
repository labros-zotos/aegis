#include "Pump.h"

#include <spdlog/spdlog.h>

string
Pump::getDateTimeString(chrono::system_clock::time_point time_point) const {
  char buf[19];
  time_t time = chrono::system_clock::to_time_t(time_point);
  tm local_tm = *localtime(&time);
  strftime(buf, 19, "%d/%m/%y %H:%M:%S", &local_tm);
  return buf;
  return string(buf);
}

Pump::Pump(uint16_t pin, GPIOController *_gpio)
    : state(OFF), pin(pin), gpio(_gpio) {
  gpio->setModeOutput(pin);
  last_on = chrono::system_clock::now();
  last_off = chrono::system_clock::now();
}

Pump::PumpState Pump::getState() const { return state; }

string Pump::getLastOnDateTime() const { return getDateTimeString(last_on); }

string Pump::getLastOffDateTime() const { return getDateTimeString(last_off); }

void Pump::turnOn() {
  if (state != ON) {
    gpio->write(pin, 1);
    state = ON;
    last_on = chrono::system_clock::now();
    spdlog::debug("Water pump turned on at: {0}", getDateTimeString(last_on));
  }
}

void Pump::turnOff() {
  if (state != OFF) {
    gpio->write(pin, 0);
    state = OFF;
    last_off = chrono::system_clock::now();
    spdlog::debug("Water pump turned off at: {0}", getDateTimeString(last_off));
  }
}