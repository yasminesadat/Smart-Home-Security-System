#include <stdio.h>
#include "pir_sensor.h"

#ifndef PICO_STDLIB_H 
#define PICO_STDLIB_H 
#include "pico/stdlib.h"
#endif

// All initializations
void init(){
    pir_sensor_init();
}

int main() {
    stdio_init_all();  // Initialize standard I/O
    init();
    sleep_ms(2000);  // Delay for sensor stabilization
    
    bool pir_state = false;
    bool password_trigger = false; // False means no motion and True means trigger password on the app
    bool password_correct = false; 
    bool is_intruder = false;
  
    while (true) {
        bool pir_sensor_value = pir_sensor_read(PIR_SENSOR_PIN);  // Read the PIR sensor

        if (pir_sensor_value && !pir_state) {
            printf("Motion detected by PIR Sensor!\n");
            pir_state = true;
        } else if (!pir_sensor_value && pir_state) {
            printf("No motion detected by PIR Sensor.\n");
            pir_state = false;
        }
        sleep_ms(500);  // Delay to avoid rapid updates
}
}