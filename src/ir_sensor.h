#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#ifndef PICO_STDLIB_H 
#define PICO_STDLIB_H 
#include "pico/stdlib.h"
#endif

#define IR_SENSOR_PIN 4

// Function declarations
void ir_sensor_init();
bool ir_sensor_read();

#endif // IR_SENSOR_H