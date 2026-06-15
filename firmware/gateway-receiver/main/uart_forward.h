#pragma once

#include "esp_err.h"
#include "espnow_rx.h"

#ifdef __cplusplus
extern "C" {
#endif

// Initializes the UART used to talk to the Raspberry Pi.
esp_err_t uart_forward_init(void);

// Serializes a sensor reading as a single JSON line and writes it to UART.
esp_err_t uart_forward_send(const sensor_data_t *data);

#ifdef __cplusplus
}
#endif
