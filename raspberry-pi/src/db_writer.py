"""Thin wrapper around the InfluxDB 2.x client for writing weather readings."""

import logging

from influxdb_client import InfluxDBClient, Point
from influxdb_client.client.write_api import SYNCHRONOUS

log = logging.getLogger("db_writer")

MEASUREMENT = "weather"


class DBWriter:
    def __init__(self, config: dict):
        self.bucket = config["bucket"]
        self.org = config["org"]
        self.client = InfluxDBClient(
            url=config["url"],
            token=config["token"],
            org=self.org,
        )
        self.write_api = self.client.write_api(write_options=SYNCHRONOUS)

    def write_reading(self, reading: dict) -> None:
        point = Point(MEASUREMENT)
        for field, value in reading.items():
            point = point.field(field, float(value))

        try:
            self.write_api.write(bucket=self.bucket, org=self.org, record=point)
        except Exception:
            log.exception("Failed to write reading to InfluxDB")

    def close(self) -> None:
        self.client.close()
