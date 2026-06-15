# Setup

Step-by-step instructions to build, flash, and run the whole stack.

## Prerequisites

- [ESP-IDF v5.x](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/index.html) installed and exported (`. ./export.sh` / `export.bat`)
- An ESP32-S3 dev board (sensor node) and an ESP32 dev board (gateway)
- Python 3.10+
- Docker and Docker Compose (on the Raspberry Pi or any host for the data stack)
- A USB-to-serial link between the gateway ESP32 and the Raspberry Pi

## 1. Flash the gateway receiver first

The gateway prints its Wi-Fi station MAC address on boot — the sensor node
needs this address to send it data.

```bash
cd firmware/gateway-receiver
idf.py set-target esp32
idf.py build flash monitor
```

Note the MAC address printed in the log (`Gateway MAC: AA:BB:CC:DD:EE:FF`).

## 2. Configure and flash the sensor node

Edit `firmware/sensor-node/main/espnow_tx.c` and set `GATEWAY_MAC` to the
address from step 1. Adjust `WAKE_INTERVAL_SEC` in `main.c` and the rain/wind
pulse pins in `main/ulp/ulp_main.c` to match your wiring (see
[hardware/bom.md](../hardware/bom.md)).

```bash
cd firmware/sensor-node
idf.py set-target esp32s3
idf.py build flash monitor
```

## 3. Bring up InfluxDB + Grafana

On the Raspberry Pi (or any Docker host):

```bash
cd raspberry-pi
docker compose up -d
```

- InfluxDB: http://localhost:8086 (org `weather-station`, bucket `sensors`)
- Grafana: http://localhost:3000 (default login `admin` / `admin`)

Import the dashboard from `grafana/dashboards/sensors.json` and point its
InfluxDB datasource at the `sensors` bucket.

## 4. Run the ingestion script

```bash
cd raspberry-pi
python -m venv .venv && source .venv/bin/activate
pip install -r requirements.txt

cp config/config.example.yaml config/config.yaml
# edit config.yaml: serial port + InfluxDB token

python src/serial_listener.py config/config.yaml
```

## 5. Verify

- `serial_listener.py` should log one parsed reading per transmission from
  the sensor node.
- New points should appear in the InfluxDB `sensors` bucket
  (measurement `weather`).
- The Grafana dashboard should start updating within one wake cycle of the
  sensor node.
