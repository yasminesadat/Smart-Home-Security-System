#include "servo.h"
#include "hardware/clocks.h"

static door_state_t door_state = DOOR_CLOSED;

void go_degree(float degree)
{
    int duty = (((float)(ROTATE_180 - ROTATE_0) / 180.0) * degree) + ROTATE_0;
    pwm_set_gpio_level(SERVO_PIN, duty);
}

void servo_init()
{
    gpio_init(SERVO_PIN);

    // Setup up PWM t
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    pwm_set_gpio_level(SERVO_PIN, 0);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);

    // Get clock speed and compute divider for 50 hz
    uint32_t clk = clock_get_hz(clk_sys);
    uint32_t div = clk / (20000 * 50);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, (float)div);

    // Set wrap so the period is 20 ms
    pwm_config_set_wrap(&config, 20000);

    // Load the configuration
    pwm_init(slice_num, &config, false);

    pwm_set_enabled(slice_num, true);
    go_degree(92);
}


void open_door(){
    go_degree(280);
    door_state = DOOR_OPEN;
}

void close_door(){
    go_degree(92);
    door_state = DOOR_OPEN;
}

door_state_t get_door_state() {
    return door_state;
}
