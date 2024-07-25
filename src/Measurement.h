#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <chrono>
#include <cstdint>
#include <string>

using namespace std;

class Measurement {
private:
  float temperature;
  float humidity;
  time_t timestamp;

public:
  Measurement(float temperature, float humidity);

  float getTemperature() const;
  float getHumidity() const;
  time_t getTime() const;
  string getDateTimeString() const;
};

#endif // MEASUREMENT_H