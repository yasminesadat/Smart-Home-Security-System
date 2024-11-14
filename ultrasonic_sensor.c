#include "ultrasonic_sensor.h"

void ultrasonic_sensor_init()
{
    gpio_init(TRIGGER_PIN);
    gpio_init(ECHO_PIN);
    gpio_set_dir(TRIGGER_PIN, GPIO_OUT);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
}

bool ultrasonic_sensor_read()
{
    // Clear trigger pin
    gpio_put(TRIGGER_PIN, 0);
    sleep_us(2);

    // Send a 10us pulse to trigger
    gpio_put(TRIGGER_PIN, 1);
    sleep_us(10);
    gpio_put(TRIGGER_PIN, 0);

    // Wait for the echo pin to go high
    while (gpio_get(ECHO_PIN) == 0)
        ;

    // Measure the time the echo pin is high
    uint32_t start_time_us = time_us_32();
    while (gpio_get(ECHO_PIN) == 1)
        ;
    uint32_t end_time_us = time_us_32();

    // Calculate the distance
    uint32_t pulse_duration_us = end_time_us - start_time_us;
    float distance_cm = pulse_duration_us / 58.0f;

    return (distance_cm <= MAX_DISTANCE);
}