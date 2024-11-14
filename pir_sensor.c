#include "pir_sensor.h"

// Function to initialize the PIR sensor
void pir_sensor_init() {
    gpio_init(PIR_SENSOR_PIN);
    gpio_set_dir(PIR_SENSOR_PIN, GPIO_IN);
}

// Function to read the value of PIR sensor
bool pir_sensor_read() {
    return gpio_get(PIR_SENSOR_PIN);
}