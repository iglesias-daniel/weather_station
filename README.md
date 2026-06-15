# weather_station
A weather station with a ultra-low-power design for temperature, pressure, rain, humidity, wind direction and wind speed.

# Arquitecture

~~~mermaid
flowchart LR
    subgraph Nodo["Nodo Sensor — ESP32-S3"]
        S[Sensores] --> ULP[ULP Co-Processor]
        ULP --> Main[Main Processor]
    end

    Main <-->|ESP-NOW| RX[ESP32 Receptor]

    RX<-->|UART|RP[(Data)]

    subgraph Gateway["Server - Raspberry"]
        RP --> Graf[Grafana]
    end

~~~

## ESP32S3 Ultra-Low Power Coprocessor

Processor, manage deep sleep, save data

## ESP32S3 Main Processor

Send data to the ESP32

## ESP32

Receive data from the ESP32S3, and send to the Raspberry

## Raspberry

Save the data, create a server, grafana