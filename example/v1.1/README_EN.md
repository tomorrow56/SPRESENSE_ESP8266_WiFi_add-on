# SPRESENSE v1.1 Examples

[日本語](README.md)

## Overview

This directory contains sample programs for the SPRESENSE Wi-Fi add-on v1.1. Version 1.1 provides basic Wi-Fi communication functionality and can serve as a foundation for various IoT applications.

## Sample List

### 1. SPRESENSE_ESP8266

A simple sample for verifying the basic operation of the Wi-Fi add-on.

#### Features

- Connection to Wi-Fi access points
- HTTP client communication with web servers
- Display of communication status via serial monitor

#### Characteristics

- Basic sample for first-time users of SPRESENSE Wi-Fi add-on
- Learn basic AT command usage
- Ideal for testing ESP8266 communication

### 2. SPRESENSE_ESP8266_ambient

A sample for sending sensor data to Ambient (IoT data visualization service).

#### Features

- Periodic sensor data acquisition
- Data transmission to Ambient server
- Data visualization through graphs

#### Requirements

- Ambient account and channel ID
- Sensors (temperature, humidity, etc.)

### 3. SPRESENSE_SERIAL_TEST

A sample for testing serial communication between SPRESENSE and ESP8266.

#### Features

- Bidirectional serial communication testing
- AT command send/receive verification
- Communication speed and stability verification

### 4. SPRESENSE_Sparkfun_ESP8266_Phant

A sample for sending data to SparkFun Phant service.

#### Features

- Data posting to Phant server
- IoT data logging
- Cloud data store integration

### 5. SPRESENSE_Sparkfun_ESP8266_Ping

A Ping test sample for verifying network connectivity.

#### Features

- Ping transmission to specified hosts
- Network latency measurement
- Connection status monitoring

### 6. SPRESENSE_Sparkfun_ESP8266_Shield_Demo

A demonstration showing basic usage of the SparkFun ESP8266 Shield.

#### Features

- Wi-Fi shield initialization
- Various network service usage examples
- Practical application templates

## Library

### SparkFun ESP8266 AT Arduino Library

Arduino library used in v1.1 samples.

#### Features

- Simple interface for ESP8266 AT commands
- Wi-Fi connection management
- HTTP/TCP/UDP communication
- DNS resolution

#### Usage

1. Install the library in Arduino IDE
2. Open the sample sketch
3. Modify Wi-Fi settings
4. Upload sketch to SPRESENSE

## Hardware Requirements

- SPRESENSE main board
- SPRESENSE Wi-Fi add-on v1.1
- USB cable (for programming)
- Wi-Fi access point

## Configuration

All samples require the following configuration:

```cpp
// Wi-Fi settings
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";
```

For sample-specific configurations, please refer to the comments in each sketch.

## Important Notes

- This sample is exclusive to SPRESENSE Wi-Fi add-on v1.1
- Does not support v2.2 Deep Sleep functionality
- Requires 2.4GHz band Wi-Fi access points
- Some samples require external service accounts

## License

Each sample code and library is provided under the GNU General Public License v3.0, same as the entire project.
