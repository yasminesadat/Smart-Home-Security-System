#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include <string.h>
#include "queue.h"
#include "buzzer.h"
#include "ultrasonic_sensor.h"
#include "ir_sensor.h"
#include "servo.h"

void init() {
    stdio_init_all();
    buzzer_init();
    ultrasonic_sensor_init();
    ir_sensor_init();
    servo_init();
}

// Ultrasonic sensor control task
void ultrasonic_sensor_task(void *pvParameters) {
    while (true) {
        if (ultrasonic_sensor_read() && get_door_state() == DOOR_CLOSED) {
            printf("Someone is waiting in front of the door. Enter password: ");
            char password[4]; // Increase buffer size to handle longer input
            fgets(password, sizeof(password), stdin);

            // Remove newline character if present
            size_t len = strlen(password);
            if (len > 0 && password[len - 1] == '\n') {
                password[len - 1] = '\0';
            }

            printf("Password: %s\n", password);
            if (strcmp(password, "123") == 0) {
                // Password is correct, take action input
                printf("Password correct.\n Enter 'o' to open door.\n Enter 'b' to trigger buzzer if you are not expecting a visitor.\n");
                char input;
                while (true) {
                    input = getchar();
                    if (input == 'o' || input == 'b') {
                        break; // Exit the loop when a valid input is received
                    }
                    vTaskDelay(pdMS_TO_TICKS(100)); // Add a small delay to prevent rapid polling
                }
                if (input == 'o') {
                    open_door();
                    printf("Door is opened.\n");                 
                } else if (input == 'b' && !is_buzzer_on()) {
                    printf("Buzzer is ON. Enter 'OFF' to turn off the buzzer.\n");
                    char off_input[4];
                    fgets(off_input, sizeof(off_input), stdin);

                    // Remove newline character if present
                    size_t off_len = strlen(off_input);
                    if (off_len > 0 && off_input[off_len - 1] == '\n') {
                        off_input[off_len - 1] = '\0';
                    }

                    if (strcmp(off_input, "OFF") == 0) {
                        buzzer_off();
                        printf("Buzzer is OFF.\n");
                    }
                    vTaskDelay(pdMS_TO_TICKS(100)); // Add a small delay to prevent rapid polling
                }
                } else {
                // Password is incorrect
                printf("Incorrect password.\n");
            }
        }
        else if (get_door_state() == DOOR_OPEN && !ultrasonic_sensor_read()) {
            close_door();        
        }
        vTaskDelay(pdMS_TO_TICKS(2000)); // Add a delay to prevent rapid polling
    }
}

// IR sensor control task
void ir_sensor_task(void *pvParameters) {
    while (true) {
        if (ir_sensor_read() && !is_buzzer_on()) {
            printf("Intrusion detected in highly sensitive area. Triggering buzzer.\n");
            buzzer_on();
            printf("Buzzer is ON. Enter 'OFF' to turn off the buzzer.\n");
            char off_input[4];
            fgets(off_input, sizeof(off_input), stdin);

            // Remove newline character if present
            size_t off_len = strlen(off_input);
            if (off_len > 0 && off_input[off_len - 1] == '\n') {
                off_input[off_len - 1] = '\0';
            }

            if (strcmp(off_input, "OFF") == 0) {
                buzzer_off();
                printf("Buzzer is OFF.\n");
            }
        }
        vTaskDelay(pdMS_TO_TICKS(2000)); // Add a delay to prevent task from running too frequently
    }
}

// Main function
int main() {
    // Initialize
    init();

    // Create the ultrasonic sensor task
    if (xTaskCreate(ultrasonic_sensor_task, "Ultrasonic Sensor Task", 256, NULL, 1, NULL) != pdPASS) {
        printf("Failed to create Ultrasonic Sensor Task\n");
        return 1;
    }

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