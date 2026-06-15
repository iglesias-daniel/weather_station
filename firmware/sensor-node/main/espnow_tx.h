#pragma once

#include "esp_err.h"
#include "sensors.h"

#ifdef __cplusplus
extern "C" {
#endif

// Initializes Wi-Fi in station mode and ESP-NOW, and registers the
// gateway receiver as a peer.
esp_err_t espnow_tx_init(void);

// Sends a sensor reading to the gateway receiver.
esp_err_t espnow_tx_send(const sensor_data_t *data);

// Tears down ESP-NOW and Wi-Fi to save power before deep sleep.
void espnow_tx_deinit(void);

#ifdef __cplusplus
}
#endif
