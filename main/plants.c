#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"
#include "stemma.h"

static const char *TAG = "plants";

void app_main(void)
{
    ESP_LOGI(TAG, "Starting...");
    ESP_LOGI(TAG, "Initializing STEMMA soil sensor...");
    ESP_ERROR_CHECK(stemma_init());

    while (1) {
        uint16_t moisture_data;
        esp_err_t r = stemma_read_moisture(&moisture_data);
        if (r == ESP_OK) {
            ESP_LOGI(TAG, "Moisture level = %d", moisture_data);
            char moisture_str[16];
            snprintf(moisture_str, sizeof(moisture_str), "%d", moisture_data);
        } else {
            ESP_LOGE(TAG, "Stemma sensor read failed: %d", r);
        }
        
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }


}