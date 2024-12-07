#include "ir_sensor.h"

void ir_sensor_init() {
    gpio_init(IR_SENSOR_PIN);
    gpio_set_dir(IR_SENSOR_PIN, GPIO_IN);
}

bool ir_sensor_read() {
    return !gpio_get(IR_SENSOR_PIN);
}