#include <chrono>

#include "GPIOController.h"
#include "Measurement.h"
#include "MeasurementLogger.h"
#include "Pump.h"
#include "SHT40Sensor.h"

#include "spdlog/spdlog.h"

using namespace std;

int main() {
  spdlog::set_level(spdlog::level::debug);

  GPIOController *gpio = new GPIOController();
  SHT40Sensor sensor;
  sensor.softReset();
  spdlog::info("SHT40 sensor initialized");
  spdlog::debug("SHT40 Serial number: {0:d}", sensor.getSerialNumber());

  Pump pump((uint16_t)17, gpio);
  MeasurementLogger data_logger("data/raw/measurements.csv");

  int16_t error;
  while (true) {
    error = sensor.measureLowestPrecision();
    if (error != 0) {
      spdlog::error(
          "Error receiving temperature or humidity from SHT40 sensor: {0:d}",
          error);
      sensor.softReset();
      continue;
    }

    Measurement current_measurement =
        Measurement(sensor.getTemperature(), sensor.getHumidity());
    data_logger.logMeasurement(current_measurement);

    spdlog::debug("Temperature: {:03.2f}, Humidity: {:03.2f}",
                  current_measurement.getTemperature(),
                  current_measurement.getHumidity());
    spdlog::debug("Cooling Rate: {:03.2f}", data_logger.getHourlyCoolingRate());

    bool frost_risk_detected = (current_measurement.getTemperature() < 2.0 &&
                                data_logger.getHourlyCoolingRate() < -0.5) ||
                               current_measurement.getTemperature() < 0.5;

    bool frost_risk_over = (current_measurement.getTemperature() > 1.5 &&
                            data_logger.getHourlyCoolingRate() > 0.5) ||
                           current_measurement.getTemperature() > 3.0;

    if (frost_risk_detected) {
      pump.turnOn();
    } else if (frost_risk_over) {
      pump.turnOff();
    }

    data_logger.saveMeasurementToCSV(current_measurement, pump);

    this_thread::sleep_for(chrono::seconds(58));
  }

  delete gpio;

  return 0;
}
