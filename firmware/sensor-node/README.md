# Sensor Node Firmware (ESP32-S3)

Reads the full sensor suite and transmits each reading to the
[gateway receiver](../gateway-receiver) over ESP-NOW, then goes back to deep
sleep. The ULP RISC-V co-processor counts rain/wind pulses while the main
core sleeps and can wake it early once a threshold is reached.

## Layout

- `main/main.c` — wake handling, sensor read, ESP-NOW send, deep sleep
- `main/sensors.c` / `.h` — sensor drivers (`sensor_data_t`)
- `main/espnow_tx.c` / `.h` — Wi-Fi/ESP-NOW init and send
- `main/ulp/ulp_main.c` — ULP RISC-V program (rain/wind pulse counting)

## Build & flash

```bash
idf.py set-target esp32s3
idf.py build flash monitor
```

## Configuration

- Set the gateway's MAC address in `main/espnow_tx.c` (`GATEWAY_MAC`) —
  printed by the [gateway receiver](../gateway-receiver) on boot.
- Adjust `WAKE_INTERVAL_SEC` in `main/main.c` for the desired sampling
  period.
- Adjust the rain/wind GPIOs and wake threshold in `main/ulp/ulp_main.c` to
  match your wiring (see [../../hardware/bom.md](../../hardware/bom.md)).
