#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "queue.h"
#include "stdio.h"
#include "servo.h"

static QueueHandle_t xQueue = NULL;

void init(){
    stdio_init_all();
    servo_init();
}

// Servo control task
void servo_task(void *pvParameters) {
    while (true) {
        open_door();
        sleep_ms(3000);
        close_door();
        sleep_ms(3000);
    }
}


// USB logging task
void usb_task(void *pvParameters) {
    while (true) {
        printf("bla bla bla\n");
        vTaskDelay(pdMS_TO_TICKS(7000));
        // uint value;

        // while (true) {
        //     // Wait to receive from the queue
    }
}

// Main function
int main() {
    // Initialize the SDK
    init();

    // Create the queue
    xQueue = xQueueCreate(10, sizeof(uint));
    if (xQueue == NULL) {
        printf("Failed to create queue\n");
        return 1;
    }

    // Create the buzzer task
    if (xTaskCreate(servo_task, "Servo Task", 256, NULL, 1, NULL) != pdPASS) {
        printf("Failed to create Servo Task\n");
        return 1;
    }

    // Create the USB logging task
    if (xTaskCreate(usb_task, "USB Task", 256, NULL, 1, NULL) != pdPASS) {
        printf("Failed to create USB Task\n");
        return 1;
    }

    // Start the scheduler
    vTaskStartScheduler();

    // Should never reach here
    while (true) {
    }
    return 0;
}