#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "servo.h" 
#include "buzzer.h"
#include "led.h"
// CGI handler which is run when a request for /led.cgi is detected
const char *cgi_buzzer_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    // Check if an request for LED has been made (/led.cgi?led=x)
    if (strcmp(pcParam[0] , "buzzer") == 0){
        // Look at the argument to check if LED is to be turned on (x=1) or off (x=0)
        if(strcmp(pcValue[0], "0") == 0)
           buzzer_off();
        else if(strcmp(pcValue[0], "1") == 0)
          buzzer_on();
    }
    
    // Send the index page back to the user
    return "/index.shtml";
}
const char *cgi_servo_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
  

    // Check if a request for servo has been made (/servo.cgi?servo=x)
    if ( strcmp(pcParam[0], "servo") == 0) {
        // Look at the argument to check if the servo is to be opened or closed
        if (strcmp(pcValue[0], "close") == 0 && get_door_state() == DOOR_OPEN) {
            close_door();
        } else if (strcmp(pcValue[0], "open") == 0 && get_door_state() == DOOR_CLOSED) {
            open_door();
        }
    }
    
    // Send the index page back to the user
    return "/index.shtml";
}


const char *cgi_led_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    // Check if a request for LED has been made (/led.cgi?led=x)
    if (strcmp(pcParam[0], "led") == 0) {
        // Turn LED on (x=1) or off (x=0)
        if (strcmp(pcValue[0], "0") == 0) {
            leds_off();
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        } else if (strcmp(pcValue[0], "1") == 0) {
            leds_on();
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        }
    }
    return "/index.shtml";
}




// tCGI Struct
// Fill this with all of the CGI requests and their respective handlers
static const tCGI cgi_handlers[] = {
    {
        // Html request for "/led.cgi" triggers cgi_handler
        "/buzzer.cgi", cgi_buzzer_handler
    },
    {

        "/servo.cgi", cgi_servo_handler
    },
    {
        // Html request for "/led.cgi" triggers cgi_handler
        "/led.cgi", cgi_led_handler
    }

};

void cgi_init(void)
{
    http_set_cgi_handlers(cgi_handlers, 3);
}