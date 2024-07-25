#include <ctime>

#include "SHT40Sensor.h"

#include "sensirion_common.h"
#include "sensirion_i2c_hal.h"
#include "sht4x_i2c.h"
#include "spdlog/spdlog.h"

using namespace std;

SHT40Sensor::SHT40Sensor() {
  sensirion_i2c_hal_init();
  sht4x_init(SHT40_I2C_ADDR_44);
  serial_number = 0;
  temperature = -1;
  humidity = -1;
}

uint32_t SHT40Sensor::getSerialNumber() {
  int16_t error = sht4x_serial_number(&serial_number);
  if (error != NO_ERROR) {
    spdlog::error("Error calling sht4x_serial_number(): {0:d}", error);
    return 0;
  }

  return serial_number;
}

float SHT40Sensor::getTemperature() { return temperature; }

float SHT40Sensor::getHumidity() { return humidity; }

int16_t SHT40Sensor::measureLowestPrecision() {
  return sht4x_measure_lowest_precision(&temperature, &humidity);
}

void SHT40Sensor::softReset() {
  sht4x_soft_reset();
  this_thread::sleep_for(chrono::milliseconds(10));
}

void SHT40Sensor::activateHeater() {
  uint16_t temp_ticks, hum_ticks;
  sht4x_activate_medium_heater_power_long_ticks(&temp_ticks, &hum_ticks);
  time(&last_heater_activation);

  spdlog::debug("Temperature after heating: {:03.2f}",
                sht4x_signal_temperature(temp_ticks));
  spdlog::debug("Humidity after heating: {:03.2f}",
                sht4x_signal_humidity(hum_ticks));
}