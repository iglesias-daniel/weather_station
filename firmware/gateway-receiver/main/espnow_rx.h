#pragma once

#include <stdint.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// Mirrors firmware/sensor-node/main/sensors.h's sensor_data_t.
// Both definitions must stay in sync (same field order, __attribute__((packed))).
typedef struct __attribute__((packed)) {
    float temperature_c;
    float humidity_pct;
    float pressure_hpa;
    float rain_mm;
    float wind_speed_ms;
    float wind_direction_deg;
    float battery_v;
} sensor_data_t;

// Initializes Wi-Fi in station mode and ESP-NOW in receive mode.
// Incoming sensor_data_t packets are forwarded to uart_forward_send().
esp_err_t espnow_rx_init(void);

#ifdef __cplusplus
}
#endif
