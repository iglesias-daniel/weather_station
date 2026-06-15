# Gateway Receiver Firmware (ESP32)

Listens for ESP-NOW packets from the
[sensor node](../sensor-node) and forwards each reading as a JSON line over
UART to the Raspberry Pi.

## Layout

- `main/espnow_rx.c` / `.h` — Wi-Fi/ESP-NOW init, receive callback
- `main/uart_forward.c` / `.h` — UART init, JSON serialization and write

## Build & flash

```bash
idf.py set-target esp32
idf.py build flash monitor
```

The gateway prints its Wi-Fi station MAC on boot:

```
I (xxx) espnow_rx: Gateway MAC: aa:bb:cc:dd:ee:ff
```

Copy this address into `GATEWAY_MAC` in
[../sensor-node/main/espnow_tx.c](../sensor-node/main/espnow_tx.c) before
flashing the sensor node.

## UART wiring

Connect the gateway's UART1 TX pin to the Raspberry Pi's RX (USB-to-serial
adapter, or Raspberry Pi UART header). Adjust `UART_TX_PIN` / `UART_RX_PIN`
in `main/uart_forward.c` to match your wiring.
