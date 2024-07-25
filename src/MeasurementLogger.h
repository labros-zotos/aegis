#ifndef MEASUREMENTLOGGER_H
#define MEASUREMENTLOGGER_H

#include <cstdint>
#include <string>
#include <vector>
#include <fstream>
// #include <iostream>

#include "Measurement.h"
#include "Pump.h"

class MeasurementLogger {
private:
  string filename;
  vector<Measurement> measurements;
  const size_t max_records = 60;
  std::ofstream file;

public:
  MeasurementLogger(string filename);

  ~MeasurementLogger();

  Measurement getLastMeasurement() const;

  void logMeasurement(Measurement measurement);

  void saveMeasurementToCSV(Measurement measurement, Pump pump);

  double getHourlyCoolingRate();
};

#endif // MEASUREMENTLOGGER_H