#include "MeasurementLogger.h"

MeasurementLogger::MeasurementLogger(string filename) : filename(filename) {
  file.open(filename);
}

MeasurementLogger::~MeasurementLogger() {
  if (file.is_open()) {
    file.close();
  }
}

Measurement MeasurementLogger::getLastMeasurement() const {
  if (measurements.empty()) {
    return Measurement(0.0, 0.0);
  }

  return measurements.back();
}

void MeasurementLogger::logMeasurement(Measurement measurement) {
  measurements.push_back(measurement);
  if (measurements.size() > max_records) {
    measurements.erase(measurements.begin(),
                       measurements.begin() +
                           (measurements.size() - max_records));
  }
}

void MeasurementLogger::saveMeasurementToCSV(Measurement measurement,
                                             Pump pump) {
  if (file.is_open()) {
    for (Measurement measurement : measurements) {
      file << measurement.getDateTimeString() << ","
           << measurement.getTemperature() << "," << measurement.getHumidity()
           << ",0," << pump.getState() << "," << pump.getLastOnDateTime() << ","
           << pump.getLastOffDateTime() << "\n";
    }
  }
}

double MeasurementLogger::getHourlyCoolingRate() {
  if (measurements.size() < 2) {
    return 0.0;
  }

  double sum_of_rates = 0.0;
  for (size_t i = 1; i < measurements.size(); ++i) {
    double d_temp =
        measurements[i - 1].getTemperature() - measurements[i].getTemperature();
    time_t duration = measurements[i - 1].getTime() - measurements[i].getTime();
    double delta_time = chrono::duration<double, ratio<3600>>(duration).count();
    sum_of_rates += (d_temp / delta_time);
  }
  return sum_of_rates / (measurements.size() - 1);
}
