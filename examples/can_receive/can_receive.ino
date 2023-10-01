/*
  CAN Receive Example

  This will setup the CAN controller(MCP2515) to receive CAN frames.
  Received frames will be printed to the Serial port.

  MIT License
  https://github.com/codeljo/AA_MCP2515
*/
#include "AA_MCP2515.h"

const uint8_t CAN_PIN_CHIPSELECT = 10;
const int8_t CAN_PIN_INTERRUPT = 2;

CANController CAN(CANBitrate::Config_8MHz_500kbps, CAN_PIN_CHIPSELECT, CAN_PIN_INTERRUPT);

void setup() {
  Serial.begin(115200);

  if (CAN.begin(CANController::Mode::Normal) == CANController::OK) {
    Serial.println("CAN begin OK");
  } else {
    Serial.println("CAN begin FAIL");
    // TODO: handle CAN begin failure here
  }
}

void loop() {

  CANFrame frame;
  if (CAN.read(frame) == CANController::IOResult::OK) {
    frame.print("RX");
  }
  
  delay(500);
}
