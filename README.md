# weather_station
A weather station with a ultra-low-power design for temperature, pressure, rain, humidity, wind direction and wind speed.

# Arquitecture

~~~mermaid
flowchart TB
A[ESP32S3 - ULP] <--> B
B[ESP32S3] <-->|ESP NOW| C
C[ESP32] <-->|USB| D
D[Raspberry]

~~~

## ESP32S3 Ultra-Low Power Coprocessor

Processor, manage deep sleep, save data

## ESP32S3 Main Processor

Send data to the ESP32

## ESP32

Receive data from the ESP32S3, and send to the Raspberry

## Raspberry

Save the data, create a server, grafana