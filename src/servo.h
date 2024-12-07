#ifndef SERVO_H
#define SERVO_H

#ifndef PICO_STDLIB_H
#define PICO_STDLIB_H
#include "pico/stdlib.h"
#endif

#ifndef PWM_MODULE
#define PWM_MODULE
#include "hardware/pwm.h"
#endif

#define ROTATE_0 1000
#define ROTATE_180 2000
#define SERVO_PIN 15

void servo_init();
void go_degree(float degree);
void open_door();
void close_door();

#endif  // SERVO_H