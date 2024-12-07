#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "queue.h"
#include "buzzer.h"
#include "ultrasonic_sensor.h"
#include "ir_sensor.h"

static QueueHandle_t xQueue = NULL;
bool ir_state = false;

void init(){
    stdio_init_all();
    buzzer_init();
    ir_sensor_init();
    //ultrasonic_sensor_init();
}

// Ultrasonic sensor task
// void ultrasonic_task(void *pvParameters) {
//     while (true) {
//         if (ultrasonic_sensor_read() && !printUS) {
//             printf("ultrasonic sensor triggered\n");
//             printUS = true;
//         }
//         if (!ultrasonic_sensor_read() && printUS) {
//             printUS = false;
//         }
//         vTaskDelay(pdMS_TO_TICKS(1000)); // Add a delay to prevent task from running too frequently
//     }
// }

// IR sensor task
void ir_sensor_task(void *pvParameters) {
   while (true) {
    if (ir_sensor_read() && !ir_state) {
        printf("Intruder detected in protected room!\n");
        trigger_buzzer();
        ir_state = true;
        vTaskDelay(pdMS_TO_TICKS(1000)); // Add a delay to prevent rapid toggling
    }
    if (!ir_sensor_read() && ir_state) {
        ir_state = false;
        vTaskDelay(pdMS_TO_TICKS(1000)); // Add a delay to prevent rapid toggling
    }
    vTaskDelay(pdMS_TO_TICKS(100)); // Add a delay to prevent task from running too frequently
}
}

// Main function
int main() {
    init();

    // Create the queue
    xQueue = xQueueCreate(10, sizeof(uint));
    if (xQueue == NULL) {
        printf("Failed to create queue\n");
        return 1;
    }

    // Create the ultrasonic sensor task
    // if (xTaskCreate(ultrasonic_task, "Ultrasonic Task", 256, NULL, 1, NULL) != pdPASS) {
    //     printf("Failed to create Ultrasonic Task\n");
    //     return 1;
    // }

    // Create the IR sensor task
    if (xTaskCreate(ir_sensor_task, "IR Sensor Task", 256, NULL, 1, NULL) != pdPASS) {
        printf("Failed to create IR Sensor Task\n");
        return 1;
    }

    // Start the scheduler
    vTaskStartScheduler();

    // Should never reach here
    while (true) {
    }
    return 0;
}