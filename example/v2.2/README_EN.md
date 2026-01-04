# SPRESENSE v2.2 Examples

[日本語](README.md)

## Overview

This directory contains sample programs for the SPRESENSE Wi-Fi add-on v2.2. Version 2.2 supports ESP8266 Deep Sleep functionality, and when combined with SPRESENSE's Cold Sleep feature, it can significantly reduce power consumption during battery operation.

## Sample List

### 1. SPRESENSE_PIR_to_LINE

This is a low-power IoT application that sends messages to the LINE Messaging API via SPRESENSE and ESP8266, triggered by PIR (motion) sensor interrupt detection.

#### Features

- **Ultra-low power design**: Reduces power consumption to several μA by putting ESP8266 in Deep Sleep and SPRESENSE in Cold Sleep during standby
- **Event-driven**: Automatically wakes up when the PIR sensor detects human presence, sends messages, and returns to sleep mode
- **Real-time notifications**: Can send instant notifications to the LINE app

#### Operation Overview

1. **Initialization**: Initialize SPRESENSE and ESP8266, establish Wi-Fi connection
2. **Sleep transition**: Put ESP8266 in Deep Sleep and SPRESENSE in Cold Sleep
3. **Event detection**: PIR sensor detects human presence and wakes up SPRESENSE
4. **Processing**: Wake up ESP8266 and send messages via LINE Messaging API
5. **Return to sleep**: Return both chips to sleep mode after processing completion

#### Required Hardware

- SPRESENSE main board
- SPRESENSE Wi-Fi add-on v2.2
- PIR sensor module (output: HIGH/LOW digital signal)
- Power supply (battery or USB power)

#### Configuration

The following settings are required before use:

- Wi-Fi access point information (SSID, password)
- LINE Messaging API channel access token
- Destination LINE group or user ID

For detailed configuration methods, please refer to the comments in each sketch.

### 2. Library/ESP8266_LINE_Messaging_API

An Arduino library for easily using the LINE Messaging API with SPRESENSE + ESP8266.

#### Features

- LINE Messaging API v3.0 compatible
- Text message sending functionality
- Simple initialization and authentication process
- Error handling functionality

#### Usage

After installing the library in Arduino IDE, follow these steps with reference to the sample sketch:

1. Include the library
2. Set the access token
3. Establish Wi-Fi connection
4. Call the message sending function

For detailed API reference, please refer to the comments in the library.

## Power Saving Features

### Deep Sleep (ESP8266)

- Power consumption: Approx. 10μA
- Wake-up time: Approx. 200ms
- Wakes up via reset pin (D21) control

### Cold Sleep (SPRESENSE)

- Power consumption: Approx. 1μA (excluding RTC)
- Wake-up time: Approx. 1ms
- Wakes up via GPIO interrupt

### Combined Effect

By combining both sleep functions, the operating life during battery operation can be significantly extended. For example, for applications that detect events several times per day, operation for several months to years with coin batteries is possible.

## Important Notes

- This sample is exclusive to SPRESENSE Wi-Fi add-on v2.2. It does not work with v1.1.
- Deep Sleep functionality requires connection of the reset pin (D21).
- Sleep power consumption varies depending on supply voltage and ambient temperature.
- Internet connection is required for using LINE Messaging API.

## License

Each sample code and library is provided under the GNU General Public License v3.0, same as the entire project.
