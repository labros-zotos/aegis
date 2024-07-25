#include <GPIOController.h>

#include <pigpio.h>
#include <spdlog/spdlog.h>

GPIOController::GPIOController() {
  gpio_status = gpioInitialise();
  if (gpio_status < 0) {
    spdlog::error("Failed to initialize GPIO library: {0:d}", gpio_status);
  } else {
    spdlog::info("Initialized GPIO library: {0:d}", gpio_status);
  }
}

GPIOController::~GPIOController() { gpioTerminate(); }

void GPIOController::setModeInput(int pin) { gpioSetMode(pin, PI_INPUT); }
void GPIOController::setModeOutput(int pin) {
  gpioSetMode(pin, PI_OUTPUT);
  gpioSetPullUpDown(pin, PI_PUD_OFF);
}
void GPIOController::setPullUpDown(int pin, int pud) {
  gpioSetPullUpDown(pin, pud);
}

void GPIOController::write(int pin, int level) { gpioWrite(pin, level); }