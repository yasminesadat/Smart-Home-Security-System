#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "queue.h"

#define BUZZER_PIN 2

static QueueHandle_t xQueue = NULL;

// Buzzer control task
void buzzer_task(void *pvParameters) {
    uint value = 0;

    while (true) {
        gpio_put(BUZZER_PIN, 1);
        value = 1;
        xQueueSend(xQueue, &value, 0); // Send "BUZZER ON" to queue
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
        gpio_put(BUZZER_PIN, 0);
        value = 0;
        xQueueSend(xQueue, &value, 0); // Send "BUZZER OFF" to queue
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }
}

// Main function
int main() {
    // Initialize the SDK
    stdio_init_all();
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    // Create the queue
    xQueue = xQueueCreate(10, sizeof(uint));

    // Create the buzzer task
    xTaskCreate(buzzer_task, "Buzzer Task", 256, NULL, 1, NULL);

    // Start the scheduler
    vTaskStartScheduler();

    // Should never reach here
    while (true) {
    }
    return 0;
}