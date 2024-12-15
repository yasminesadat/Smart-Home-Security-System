#ifndef LED_H
#define LED_H

#ifndef PICO_STDLIB_H
#define PICO_STDLIB_H
#include "pico/stdlib.h"
#endif


#define LED_PIN 17

void leds_init();
void leds_on();
void leds_off();

#endif 
