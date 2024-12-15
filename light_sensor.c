#include "light_sensor.h"

void light_sensor_init()
{
    gpio_init(LIGHT_SENSOR_PIN);
    gpio_set_dir(LIGHT_SENSOR_PIN, GPIO_IN);
}

bool light_sensor_read()
{
    return !gpio_get(LIGHT_SENSOR_PIN);
}