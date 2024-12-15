#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#ifndef PICO_STDLIB_H
#define PICO_STDLIB_H
#include "pico/stdlib.h"
#endif

#define LIGHT_SENSOR_PIN 12

// Function declarations
void light_sensor_init();
bool light_sensor_read();

#endif // LIGHT_SENSOR_H