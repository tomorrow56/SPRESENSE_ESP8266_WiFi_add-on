# SPRESENSE Wi-Fi Add-on

[日本語](README.md)

## Overview

This add-on board adds Wi-Fi functionality to Sony's low-power, high-performance
IoT development board, SPRESENSE.
It is equipped with an ESP8266 (ESP-WROOM-02, certified for Japan), and
communication between SPRESENSE and ESP8266 uses the
[Espressif standard AT commands](ESP8266_AT_command/).

## Key Features

- ESP8266 (ESP-WROOM-02) onboard
- Directly mountable on the top-side expansion connector of the SPRESENSE main
  board (with level shifter)
- Half-size design, can be used together with other half-size modules
- Can be used together with I2C/SPI modules (with some limitations)
- Certified for Japan

### About v2.2 (Released in Jan 2026)

Compared to the previous version (v1.1), v2.2 includes the following change:

- Support for ESP8266 Deep Sleep

To support this, the reset circuit design has been updated. Therefore, when
using the v1.1 software on v2.2 hardware, you need to add control for the reset
pin (D21) as shown below.

```cpp
#define rst_pin PIN_D21   // ESP8266 reset pin, HIGH resets

void setup() {
  // Configure ESP8266 reset pin
  pinMode(rst_pin, OUTPUT);
  // Release reset (set reset pin LOW)
  digitalWrite(rst_pin, LOW);

```

## Product Images (PCB color may change without notice)

### v1.1

#### Top

![Top](img/v1.1_top.jpg)

#### Bottom

![Bottom](img/v1.1_bottom.jpg)

#### Assembled with SPRESENSE (SPRESENSE is not included)

![Assembled with SPRESENSE](img/v1.1_assembled.jpg)

### v2.2

#### Top

![Top](img/v2.2_top.jpg)

#### Bottom

![Bottom](img/v2.2_bottom.jpg)

#### Assembled with SPRESENSE (SPRESENSE is not included)

![Assembled with SPRESENSE](img/v2.2_assembled.jpg)

## Schematics

### v1.1

![v1.1 schematic](kicad/v1.1/schematic_v1.1.png)

### v2.2

![v2.2 schematic](kicad/v2.2/schematic_v2.2.png)

## Sample Code

Sample code for each version is stored under the `example/` directory.

- v1.1: `example/v1.1/`
- v2.2: `example/v2.2/`

Each sample is designed to run in the SPRESENSE Arduino IDE environment.
For detailed usage, see the comments in each sample.

## License

This project is provided under the GNU General Public License v3.0.
See the [LICENSE](LICENSE) file for details.

## Author

- [tomorrow56](https://github.com/tomorrow56)
