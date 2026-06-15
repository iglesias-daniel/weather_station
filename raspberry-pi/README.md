# Raspberry Pi — Data Stack

Runs InfluxDB + Grafana via Docker Compose and ingests sensor readings from
the [gateway receiver](../firmware/gateway-receiver) over a USB-serial link.

## Layout

- `docker-compose.yml` — InfluxDB 2.x + Grafana services
- `src/serial_listener.py` — reads JSON lines from UART, calls `db_writer`
- `src/db_writer.py` — InfluxDB client wrapper
- `grafana/dashboards/sensors.json` — pre-built dashboard (import via UI)
- `config/config.example.yaml` — configuration template

## Quick start

```bash
# 1. Start the data stack
docker compose up -d

# 2. Install Python dependencies
python -m venv .venv && source .venv/bin/activate
pip install -r requirements.txt

# 3. Copy and edit the config
cp config/config.example.yaml config/config.yaml
# edit config.yaml: set serial port and InfluxDB token

# 4. Run the ingestion script
python src/serial_listener.py config/config.yaml
```

Then open Grafana at http://localhost:3000, add an InfluxDB datasource
pointing at `http://influxdb:8086`, and import
`grafana/dashboards/sensors.json`.
