#ifndef PIR_SENSOR_H
#define PIR_SENSOR_H

#ifndef PICO_STDLIB_H 
#define PICO_STDLIB_H 
#include "pico/stdlib.h"
#endif

// Constants
#define PIR_SENSOR_PIN 2 

// Function declarations
void pir_sensor_init();
bool pir_sensor_read();

#endif // PIR_SENSOR_H