#include "uart_forward.h"

#include <stdio.h>
#include "driver/uart.h"
#include "esp_log.h"

static const char *TAG = "uart_forward";

#define UART_PORT     UART_NUM_1
#define UART_TX_PIN   17
#define UART_RX_PIN   16
#define UART_BAUD     115200

esp_err_t uart_forward_init(void)
{
    uart_config_t cfg = {
        .baud_rate  = UART_BAUD,
        .data_bits  = UART_DATA_8_BITS,
        .parity     = UART_PARITY_DISABLE,
        .stop_bits  = UART_STOP_BITS_1,
        .flow_ctrl  = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    ESP_ERROR_CHECK(uart_driver_install(UART_PORT, 1024, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_PORT, &cfg));
    ESP_ERROR_CHECK(uart_set_pin(UART_PORT,
                                 UART_TX_PIN, UART_RX_PIN,
                                 UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    return ESP_OK;
}

esp_err_t uart_forward_send(const sensor_data_t *data)
{
    char line[200];
    int len = snprintf(line, sizeof(line),
        "{\"temperature_c\":%.2f,\"humidity_pct\":%.2f,\"pressure_hpa\":%.2f,"
        "\"rain_mm\":%.2f,\"wind_speed_ms\":%.2f,\"wind_direction_deg\":%.2f,"
        "\"battery_v\":%.2f}\n",
        data->temperature_c, data->humidity_pct, data->pressure_hpa,
        data->rain_mm, data->wind_speed_ms, data->wind_direction_deg,
        data->battery_v);

    if (len < 0 || len >= (int)sizeof(line)) {
        ESP_LOGE(TAG, "Failed to format reading");
        return ESP_ERR_INVALID_SIZE;
    }

    uart_write_bytes(UART_PORT, line, len);
    return ESP_OK;
}
