#include "ultrasonic_sensor.h"
#include "hardware/timer.h"
#include <stdio.h>
void ultrasonic_sensor_init()
{
    gpio_init(TRIGGER_PIN);
    gpio_init(ECHO_PIN);
    gpio_set_dir(TRIGGER_PIN, GPIO_OUT);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
}




bool ultrasonic_sensor_read() {
    printf("Reading ultrasonic sensor\n");
    
    // Use busy-wait delays instead of sleep
    // Clear trigger pin
    gpio_put(TRIGGER_PIN, 0);
    busy_wait_us(2);
    
    // Send a 10us pulse to trigger
    gpio_put(TRIGGER_PIN, 1);
    busy_wait_us(10);
    gpio_put(TRIGGER_PIN, 0);
    
    // Add timeout for safety
    absolute_time_t timeout = make_timeout_time_ms(100); // 100ms timeout
    
    // Wait for the echo pin to go high with timeout
    while (gpio_get(ECHO_PIN) == 0) {
        if (absolute_time_diff_us(get_absolute_time(), timeout) <= 0) {
            printf("Timeout waiting for echo start\n");
            return false;
        }
    }
    
    uint32_t start_time_us = time_us_32();
    
    // Wait for echo pin to go low with timeout
    while (gpio_get(ECHO_PIN) == 1) {
        if (absolute_time_diff_us(get_absolute_time(), timeout) <= 0) {
            printf("Timeout waiting for echo end\n");
            return false;
        }
    }
    
    uint32_t end_time_us = time_us_32();
    uint32_t pulse_duration_us = end_time_us - start_time_us;
    
    // Add bounds checking
    if (pulse_duration_us > 23529) { // Greater than ~4m
        printf("Distance out of range\n");
        return false;
    }
    
    float distance_cm = pulse_duration_us / 58.0f;
    printf("Distance: %.2f cm\n", distance_cm);
    
    return (distance_cm <= MAX_DISTANCE);
}



// bool ultrasonic_sensor_read()
// {
//     printf("Reading ultrasonic sensor\n");
//     // Clear trigger pin
//     gpio_put(TRIGGER_PIN, 0);
//     printf("before sleep1");
//     //sleep_us(2);
//     printf("after sleep1");

//     // Send a 10us pulse to trigger
//     gpio_put(TRIGGER_PIN, 1);
//     printf("before sleep2");
//     //sleep_us(10);
//     printf("after sleep2");
//     gpio_put(TRIGGER_PIN, 0);

//     // Wait for the echo pin to go high
    
//     while (gpio_get(ECHO_PIN) == 0)
//     {
//         printf("Waiting for echo pin to go high\n");
        
//     }

//     printf("Echo pin is high\n");
//     // Measure the time the echo pin is high
//     uint32_t start_time_us = time_us_32();
//     while (gpio_get(ECHO_PIN) == 1){
//         printf("Waiting for echo pin to go low\n");
        
//     }
       
//     uint32_t end_time_us = time_us_32();

//     // Calculate the distance
//     uint32_t pulse_duration_us = end_time_us - start_time_us;
//     float distance_cm = pulse_duration_us / 58.0f;
//     //printf("Distance: %.2f cm\n", distance_cm);
//     return (distance_cm <= MAX_DISTANCE);
// }