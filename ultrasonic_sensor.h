#ifndef ULTRA_SONIC_SENSOR_H
#define ULTRA_SONIC_SENSOR_H

#ifndef PICO_STDLIB_H
#define PICO_STDLIB_H
#include "pico/stdlib.h"
#endif

#define MAX_DISTANCE 15 // Maximum distance we want to ping for (in centimeters)
#define TRIGGER_PIN 0
#define ECHO_PIN 1

void ultrasonic_sensor_init();
bool ultrasonic_sensor_read();

#endif