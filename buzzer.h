#include <stdio.h>

#ifndef BUZZER_H
#define BUZZER_H

#ifndef PICO_STDLIB_H
#define PICO_STDLIB_H
#include "pico/stdlib.h"
#endif

#define BUZZER_PIN 2 

void buzzer_init();
void trigger_buzzer();

#endif // BUZZER_H