#include "sensors.h"

#include "esp_log.h"

static const char *TAG = "sensors";

// TODO: replace with real driver init (I2C bus for BME280, ADC for the
// wind vane and battery divider, pulse counters for rain/wind, etc.)
esp_err_t sensors_init(void)
{
    ESP_LOGI(TAG, "Initializing sensors");
    return ESP_OK;
}

// TODO: replace each field with a real driver read.
esp_err_t sensors_read(sensor_data_t *out)
{
    if (out == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    out->temperature_c = 0.0f;      // BME280
    out->humidity_pct = 0.0f;       // BME280
    out->pressure_hpa = 0.0f;       // BME280
    out->rain_mm = 0.0f;            // tipping-bucket rain gauge (ULP pulse count)
    out->wind_speed_ms = 0.0f;      // anemometer (ULP pulse count)
    out->wind_direction_deg = 0.0f; // wind vane (ADC)
    out->battery_v = 0.0f;          // battery voltage divider (ADC)

    return ESP_OK;
}
