#include "esp_log.h"
#include "esp_err.h"

#include "espnow_rx.h"
#include "uart_forward.h"

static const char *TAG = "gateway_receiver";

void app_main(void)
{
    ESP_ERROR_CHECK(uart_forward_init());
    ESP_ERROR_CHECK(espnow_rx_init());

    ESP_LOGI(TAG, "Gateway ready — waiting for sensor packets");
}
