#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

// Define the logging tag and the LED pin
static const char *TAG = "HARDWARE_TEST";
#define BLINK_GPIO 2 

void app_main(void)
{
    ESP_LOGI(TAG, "Initializing ESP32-P4 core...");
    ESP_LOGI(TAG, "Configuring GPIO %d as output", BLINK_GPIO);

    // Initialize the GPIO pin
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    int led_state = 0;

    // The infinite FreeRTOS task loop
    while (1) {
        ESP_LOGI(TAG, "Setting LED state to: %s", led_state == 0 ? "OFF" : "ON");
        gpio_set_level(BLINK_GPIO, led_state);
        
        // Toggle state
        led_state = !led_state;
        
        // Yield to the RTOS scheduler for 1000 milliseconds
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}