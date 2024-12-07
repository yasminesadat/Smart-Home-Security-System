#include "buzzer.h"

void buzzer_init() {
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}

void trigger_buzzer() {
    gpio_put(BUZZER_PIN, 1);
    sleep_ms(1000);
    gpio_put(BUZZER_PIN, 0);
}