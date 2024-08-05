# AA_MCP2515

## MCP2515 CAN Controller Library for Arduino

<br>

## Features

* Supports the Microchip MCP2510, and MCP2515 CAN Controllers.

* Crystals - 8, 10, 16, 20 MHz crystals are preconfigured. Any other crystal speed can be added via `CANConfig`.

* Bitrate - 10, 20, 50, 125, 250, 500, 1000 (kbit/s) (kbps) are preconfigured. Any other bitrate can be added via `CANConfig`.

* Interrupts - Support for receive, and wakeup interrupts.

* Filters - Support for receive filters based on 11-bit and 29-bit ID's.

* Many examples included to easily add CAN to your project.

<br>

## Connections

MCP2515 | Uno | Nano | Leonardo | Mega 2560 | Uno R4
------- | --- | ---- | -------- | ---- | ------
SPI CS (SS) | 10 | 10 | 10 | 53 | 10
SPI MOSI (SI) | 11 | 11 | 11 | 51 | 11
SPI MISO (SO) | 12 | 12 | 12 | 50 | 12
SPI Clock (SCK) | 13 | 13 | 13 | 52 | 13
Interrupt (INT) | 2 | 2 | 2 | 2 | 2

## Version History

> `1.0.7` - UNO R4 Minima, and UNO R4 WiFi bug fixes.

> `1.0.6` - Nano Every bug fix.

> `1.0.5` - ESP32 based boards are now supported.

<br>

## Example Usage

Note: Refer to the `examples` folder for complete ready to run examples.

### CANConfig

```cpp
#include "AA_MCP2515.h"

const CANBitrate::Config CAN_BITRATE = CANBitrate::Config_8MHz_500kbps;
const uint8_t CAN_CS = 10;
const int8_t CAN_INT = 2;

CANConfig config(CAN_BITRATE, CAN_CS, CAN_INT);

// -or- specify SPI, and SPI speed

const uint32_t CAN_SPI_HZ = 8000000;
CANConfig config(CAN_BITRATE, CAN_CS, CAN_INT, SPI, CAN_SPI_HZ);
```

### CANController

```cpp
CANController CAN(config);
CAN.begin(CANController::Mode::Normal);
```

### Transmit

```cpp
uint8_t data[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };

CANFrame frame(0x100, data, sizeof(data));
CAN.write(frame);

// -or-

CAN.write(0x100, data, sizeof(data));
```

### Receive

```cpp
CANFrame frame;
if (CAN.read(frame) == CANController::IOResult::OK) {
    frame.print("RX");
}
```
