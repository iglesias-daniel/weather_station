"""Reads JSON sensor readings from the gateway ESP32 over UART/USB-serial
and writes each one to InfluxDB."""

import json
import logging
import sys

import serial
import yaml

from db_writer import DBWriter

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s %(levelname)s %(message)s",
)
log = logging.getLogger("serial_listener")


def load_config(path: str) -> dict:
    with open(path, encoding="utf-8") as f:
        return yaml.safe_load(f)


def main(config_path: str) -> None:
    config = load_config(config_path)

    ser = serial.Serial(
        port=config["serial"]["port"],
        baudrate=config["serial"]["baud_rate"],
        timeout=5,
    )
    log.info("Listening on %s @ %d baud", ser.port, ser.baudrate)

    writer = DBWriter(config["influxdb"])

    try:
        while True:
            raw = ser.readline()
            if not raw:
                continue

            line = raw.decode("utf-8", errors="ignore").strip()
            if not line:
                continue

            try:
                reading = json.loads(line)
            except json.JSONDecodeError:
                log.warning("Discarding malformed line: %r", line)
                continue

            log.info("Received reading: %s", reading)
            writer.write_reading(reading)

    finally:
        writer.close()
        ser.close()


if __name__ == "__main__":
    config_path = sys.argv[1] if len(sys.argv) > 1 else "config/config.yaml"
    main(config_path)
