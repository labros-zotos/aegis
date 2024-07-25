# AEGIS: Autonomous Irrigation Controller for Frost Damage Prevention

This project implements an autonomous irrigation controller designed to prevent frost damage on citrus trees using undertree microsprinklers. 
The system monitors environmental conditions and activates the irrigation system when frost risk is detected.

## Hardware Components

- Raspberry Pi 3/4 Model B
- ~~BME280 Sensor (Temperature, Humidity, Pressure)~~
- SHT40 Sensor (Temperature, Humidity)
- 5V Power Supply
- Solid State Relay

## Features

- Real-time monitoring of temperature and humidity
- Automated activation of irrigation system based on temperature drop and frost risk
- Data logging for analysis 

## Dependencies

This project uses the following libraries:

- [Sensirion Raspberry Pi I2C SHT4x](https://github.com/Sensirion/raspberry-pi-i2c-sht4x): C library for the Sensirion SHT4x humidity and temperature sensor series.

Please refer to the respective library's documentation for installation and usage details.

## Acknowledgements

This project was inspired by the need to protect citrus orchards from frost damage, a common occurrence in the agriculture area around my hometown.

The frost protection strategy implemented in this project was based on information from the following publication:

Parsons, L. R., & Boman, B. J. (2023). Microsprinkler Irrigation for Cold Protection of Florida Citrus. EDIS, 2023(2). 
https://edis.ifas.ufl.edu/publication/CH182
