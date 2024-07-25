#ifndef GPIOCONTROLLER_H
#define GPIOCONTROLLER_H

#include <cstdint>

class GPIOController {
private:
  int gpio_status;

public:
  GPIOController();
  ~GPIOController();

  void setModeInput(int pin);
  void setModeOutput(int pin);
  void setPullUpDown(int pin, int pud);

  void write(int pin, int level);
};

#endif // GPIOCONTROLLER_H