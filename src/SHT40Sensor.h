#ifndef SHT40SENSOR_H
#define SHT40SENSOR_H

#include <cstdint>

class SHT40Sensor {
private:
  uint8_t i2c_address;
  uint32_t serial_number;
  float temperature;
  float humidity;
  time_t last_heater_activation;

public:
  SHT40Sensor();

  uint32_t getSerialNumber();
  float getTemperature();
  float getHumidity();

  int16_t measureLowestPrecision();

  void softReset();
  void activateHeater();
};

#endif // SHT40SENSOR_H
