#include "led.h"

void leds_init() {
   
        gpio_init(LED_PIN);
        gpio_set_dir(LED_PIN, GPIO_OUT);
    
}


void leds_on() {
   
        gpio_put(LED_PIN, true);
    
}

void leds_off() {
  
        gpio_put(LED_PIN, false);
    
}
