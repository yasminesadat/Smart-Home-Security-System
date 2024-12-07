#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "queue.h"
#include "buzzer.h"
#include "ultrasonic_sensor.h"
#include "ir_sensor.h"

static QueueHandle_t xQueue = NULL;

void init(){
    stdio_init_all();
    buzzer_init();
    ultrasonic_sensor_init();
    ir_sensor_init();
}

// Function to check if a value is in the queue
bool is_value_in_queue(QueueHandle_t queue, int value) {
    int queue_value;
    bool found = false;
    int messages_waiting = uxQueueMessagesWaiting(queue);

    for (int i = 0; i < messages_waiting; i++) {
        if (xQueueReceive(queue, &queue_value, 0) == pdPASS) {
            if (queue_value == value) {
                found = true;
            }
            // Add the value back to the queue
            xQueueSend(queue, &queue_value, 0);
        }
    }
    return found;
}

// Ultrasonic sensor task
void ultrasonic_sensor_task(void *pvParameters){
    bool trigger_app = 1;
    while(true){
        if(ultrasonic_sensor_read()){
          printf("Trigger app");
          xQueueSend(xQueue, &trigger_app, 0);
        }
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

// IR sensor task
void ir_sensor_task(void *pvParameters){
    bool trigger_buzzer = 1;
    while (true) {
        if (ir_sensor_read()) {
            // Check if the value is already in the queue
            if (!is_value_in_queue(xQueue, trigger_buzzer)) {
                xQueueSend(xQueue, &trigger_buzzer, 0);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(3000)); // Add a delay to prevent task from running too frequently
    }
}

// Buzzer control task
void buzzer_task(void *pvParameters) {
    int trigger_buzzer;
    while (true) {
        // Wait for a message from the queue
        if (xQueueReceive(xQueue, &trigger_buzzer, portMAX_DELAY) == pdPASS) {
            // If a message is received, trigger the buzzer
            buzzer_on();
            vTaskDelay(pdMS_TO_TICKS(2000)); // Buzzer on for 2 seconds
            buzzer_off();
        }
    }
}

// Main function
int main() {
    // Initialize
    init();

    // Create the queue
    xQueue = xQueueCreate(2, sizeof(bool));

    // Create the buzzer task
    if(xTaskCreate(buzzer_task, "Buzzer Task", 256, NULL, 1, NULL) != pdPASS){
        printf("Failed to create Ultrasonic Sensor Task\n");
        return 1;
    }

    // Create the ultrasonic sensor task
    if(xTaskCreate(ultrasonic_sensor_task, "Ultrasonic Sensor Task", 256, NULL, 1, NULL) != pdPASS){
        printf("Failed to create Ultrasonic Sensor Task\n");
        return 1;
    }

    // Create the ultrasonic sensor task
    if(xTaskCreate(ir_sensor_task, "IR Sensor Task", 256, NULL, 1, NULL) != pdPASS){
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