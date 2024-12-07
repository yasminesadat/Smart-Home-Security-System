#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include <string.h>
#include "queue.h"
#include "buzzer.h"
#include "ultrasonic_sensor.h"
#include "ir_sensor.h"
#include "servo.h"

static QueueHandle_t xQueue = NULL;

void init(){
    stdio_init_all();
    buzzer_init();
    ultrasonic_sensor_init();
    ir_sensor_init();
    servo_init();
}

// Function to check if a value is in the queue
bool is_value_in_queue(QueueHandle_t queue, bool value) {
    bool queue_value;
    bool found = false;
    bool messages_waiting = uxQueueMessagesWaiting(queue);

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

// Ultrasonic sensor control task
void ultrasonic_sensor_task(void *pvParameters){
    bool trigger_app = 1;
    while(true){
        if(ultrasonic_sensor_read()){
          printf("Trigger app");
          xQueueSend(xQueue, &trigger_app, 0);
        }

        if(get_door_state() == DOOR_OPEN && !ultrasonic_sensor_read()){
            bool trigger_door_close = 1;
            xQueueSend(xQueue, &trigger_door_close, 0);
        }
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

// IR sensor control task
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
    bool trigger_buzzer;
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

// Servo control task
void servo_open_task(void *pvParameters) {
    bool trigger_door_open;
    while (true) {
        // Wait for a message from the queue
        if (xQueueReceive(xQueue, &trigger_door_open, portMAX_DELAY) == pdPASS) {
            // If a message is received, open the servo
            open_door();
        }
    }
}

void servo_close_task(void *pvParameters) {
    bool trigger_door_close;
    while (true) {
        // Wait for a message from the queue
        if (xQueueReceive(xQueue, &trigger_door_close, portMAX_DELAY) == pdPASS) {
            // If a message is received, close the servo
            close_door();
        }
    }
}

void app_task(void *pvParameters) {
 bool trigger_app;
    while (true) {
        // Wait for a message from the queue
        if (xQueueReceive(xQueue, &trigger_app, portMAX_DELAY) == pdPASS) {
            // If a message is received, take user input for password
            printf("Someone is waiting in front of the door. Enter password: ");
            char password[4];
            for (int i = 0; i < 3; i++) {
                password[i] = getchar();
            }
            password[3] = '\0';

            if (strcmp(password, "123") == 0) {
                // Password is correct, take action input
                printf("Password correct.\n Enter 'o' to open door.\n Enter 'b' to trigger buzzer if you are not expecting a visitor.\n");
                char input = getchar();
                if (input == 'o') {
                    bool trigger_door_open = 1;
                    xQueueSend(xQueue, &trigger_door_open, 0);
                } else if (input == 'b') {
                    bool trigger_buzzer = 1;
                    if (!is_value_in_queue(xQueue, trigger_buzzer)) {
                      xQueueSend(xQueue, &trigger_buzzer, 0);
                    }
                }
            } else {
                // Password is incorrect
                printf("Incorrect password.\n");
            }
        }
    }
}

// Main function
int main() {
    // Initialize
    init();

    // Create the queue
    xQueue = xQueueCreate(10, sizeof(bool));

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