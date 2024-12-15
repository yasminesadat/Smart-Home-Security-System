#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"
#include "ir_sensor.h" // Add this line to include the header file for ir_sensor_read
#include "ultrasonic_sensor.h"

// SSI tags - tag length limited to 8 bytes by default
const char *ssi_tags[] = {"irsensor","ultrasonicreading"};

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen)
{
  size_t printed;

  printf("ssi_handler called with index: %d\n", iIndex);

  switch (iIndex)
  {
  case 0: // Infrared
  {

    bool ir_status = ir_sensor_read();
    if (ir_status == true)
    {
      printed = snprintf(pcInsert, iInsertLen, "ON");
    }
    else
    {
      printed = snprintf(pcInsert, iInsertLen, "OFF");
    }
  }
  break;
  case 1: // UltraSonic
  {

    printf("ultrasonicccccccccccc \n");

    bool ultrasonic_status = ultrasonic_sensor_read();
    if (ultrasonic_status == true)
    {
      printf("ultrasonicccccccccccc takes reading");
      printed = snprintf(pcInsert, iInsertLen, "ON");
    }
    else
    {
      printf("ultrasonicccccccccccc noooooooooooo");
      printed = snprintf(pcInsert, iInsertLen, "OFF");
    }
  }

  break;

  default:
    printed = 0;
    break;
  }

  return (u16_t)printed;
}

// Initialise the SSI handler
void ssi_init()
{
  // Initialise ADC (internal pin)

  http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}