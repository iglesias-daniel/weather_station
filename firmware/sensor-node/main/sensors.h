#pragma once

#include <stdint.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// Raw sensor reading, sent as-is over ESP-NOW.
// NOTE: keep this layout in sync with
// firmware/gateway-receiver/main/espnow_rx.h
typedef struct __attribute__((packed)) {
    float temperature_c;
    float humidity_pct;
    float pressure_hpa;
    float rain_mm;
    float wind_speed_ms;
    float wind_direction_deg;
    float battery_v;
} sensor_data_t;

// Initializes I2C/ADC peripherals for all sensors.
esp_err_t sensors_init(void);

// Takes a full reading from every sensor.
esp_err_t sensors_read(sensor_data_t *out);

#ifdef __cplusplus
}
#endif
