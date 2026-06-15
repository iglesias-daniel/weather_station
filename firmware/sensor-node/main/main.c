#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_err.h"

#include "sensors.h"
#include "espnow_tx.h"

static const char *TAG = "sensor_node";

// How often the main core wakes up to take a full reading and transmit it.
#define WAKE_INTERVAL_SEC 60

void app_main(void)
{
    esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
    ESP_LOGI(TAG, "Wake cause: %d", cause);

    ESP_ERROR_CHECK(sensors_init());

    sensor_data_t reading = {0};
    esp_err_t err = sensors_read(&reading);

    if (err == ESP_OK) {
        ESP_LOGI(TAG,
                 "T=%.2fC H=%.1f%% P=%.1fhPa rain=%.2fmm wind=%.2fm/s @ %.0fdeg batt=%.2fV",
                 reading.temperature_c, reading.humidity_pct, reading.pressure_hpa,
                 reading.rain_mm, reading.wind_speed_ms, reading.wind_direction_deg,
                 reading.battery_v);

        ESP_ERROR_CHECK(espnow_tx_init());
        espnow_tx_send(&reading);
        espnow_tx_deinit();
    } else {
        ESP_LOGW(TAG, "Sensor read failed (%s), skipping transmission", esp_err_to_name(err));
    }

    ESP_LOGI(TAG, "Entering deep sleep for %d s", WAKE_INTERVAL_SEC);
    esp_sleep_enable_timer_wakeup((uint64_t)WAKE_INTERVAL_SEC * 1000000ULL);
    esp_deep_sleep_start();
}
