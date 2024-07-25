#include "Measurement.h"

Measurement::Measurement(float temperature, float humidity)
    : temperature(temperature), humidity(humidity) {
  time(&timestamp);
}

float Measurement::getTemperature() const { return temperature; }

float Measurement::getHumidity() const { return humidity; }

time_t Measurement::getTime() const { return timestamp; }

string Measurement::getDateTimeString() const {
  char buf[19];
  time_t time_t_now =
      chrono::system_clock::to_time_t(chrono::system_clock::now());
  tm local_tm = *localtime(&time_t_now);
  strftime(buf, 19, "%d/%m/%y %H:%M:%S", &local_tm);
  return string(buf);
}
