#ifndef LED_H
#define LED_H

#ifndef PICO_STDLIB_H 
#define PICO_STDLIB_H 
#include "pico/stdlib.h"
#endif

#define LED_PIN 6

void led_init(void);
void led_on();
void led_off();

#endif // LED_H