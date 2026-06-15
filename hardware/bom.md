# Bill of Materials

## Sensor node (ESP32-S3, battery + solar)

| Qty | Part | Notes |
|---|---|---|
| 1 | ESP32-S3-DevKitC-1 (or equivalent) | Main + ULP RISC-V co-processor |
| 1 | BME280 | Temperature, humidity, pressure (I2C) |
| 1 | Anemometer (reed switch / pulse output) | Wind speed |
| 1 | Wind vane (potentiometer output) | Wind direction (ADC) |
| 1 | Tipping-bucket rain gauge (reed switch) | Rainfall (pulse count) |
| 1 | 3.7V Li-ion/LiPo battery | Sensor node power |
| 1 | Solar panel (5–6V) + charge controller (e.g. TP4056) | Battery charging |
| 1 | Voltage divider (2x resistors) | Battery voltage monitoring (ADC) |
| 1 | Weatherproof enclosure | Outdoor mounting |

## Gateway receiver (ESP32, mains-powered)

| Qty | Part | Notes |
|---|---|---|
| 1 | ESP32 DevKitC (or equivalent) | ESP-NOW <-> UART bridge |
| 1 | USB cable | Power + UART link to Raspberry Pi |

## Server

| Qty | Part | Notes |
|---|---|---|
| 1 | Raspberry Pi (3B+ or newer) | Runs Docker, InfluxDB, Grafana |
| 1 | microSD card (16GB+) | OS + data storage |

See [schematics/](schematics/) for wiring diagrams.
