/*
  CAN Loopback Example

  This will verify the SPI connection between the Arduino and the CAN controller(MCP2515) are correct.
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

  while(CAN.begin(CANController::Mode::Loopback) != CANController::OK) {
    Serial.println("CAN begin FAIL - delaying for 1 second");
    delay(1000);
  }
  Serial.println("CAN begin OK");
}

void loop() {

  // transmit
  CANFrame frame1(0x100, data, sizeof(data));
  CAN.write(frame1);
  frame1.print("CAN TX");

  // receive
  CANFrame frame2;
  CANController::IOResult rxResult = CAN.read(frame2);
  switch(rxResult) {
    case CANController::IOResult::OK:
      frame2.print("CAN RX");
      break;
    default:
      Serial.println("CAN RX NODATA");
      break;
  }

  delay(2000);
}
