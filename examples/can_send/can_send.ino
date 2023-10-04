/*
  CAN Send Example

  This will setup the CAN controller(MCP2515) to send CAN frames.
  Transmitted frames will be printed to the Serial port.
  Transmits a CAN standard frame every 2 seconds.

  MIT License
  https://github.com/codeljo/AA_MCP2515
*/

#include "AA_MCP2515.h"

// TODO: modify CAN_BITRATE, CAN_PIN_CS(Chip Select) pin, and CAN_PIN_INT(Interrupt) pin as required.
const CANBitrate::Config CAN_BITRATE = CANBitrate::Config_8MHz_500kbps;
const uint8_t CAN_PIN_CS = 10;
const int8_t CAN_PIN_INT = 2;

CANConfig config(CAN_BITRATE, CAN_PIN_CS, CAN_PIN_INT);
CANController CAN(config);

uint8_t data[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };

void setup() {
  Serial.begin(115200);

  while(CAN.begin(CANController::Mode::Normal) != CANController::OK) {
    Serial.println("CAN begin FAIL - delaying for 1 second");
    delay(1000);
  }
  Serial.println("CAN begin OK");
}

void loop() {

  // transmit
  CANFrame frame(0x100, data, sizeof(data));
  CAN.write(frame);
  frame.print("CAN TX");

  // modify data to simulate updated data from sensor, etc
  data[0] += 1;

  delay(2000);
}
