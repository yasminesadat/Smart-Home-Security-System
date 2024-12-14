#include "buzzer.h"

void buzzer_init() {
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}

void buzzer_on() {
    gpio_put(BUZZER_PIN, 1);
}
void buzzer_off() {
    gpio_put(BUZZER_PIN, 0);
}