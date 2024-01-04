/*
  CAN Receive Filters Example
  based on CAN Receive Interrupts Callback Example

  This will setup the CAN controller(MCP2515) to receive CAN frames via hardware interrupts.
  The receive filters will be setup to only receive 11-bit ID's 0x0100, and 0x0103. All other ID's will be filtered out / ignored.
  Received frames will be printed to the Serial port.

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

void onReceive(CANController&, CANFrame frame) {
  frame.print("RX");
}

void onWakeup(CANController& controller) {
  controller.setMode(CANController::Mode::Normal);
}

void setup() {
  Serial.begin(115200);

  while(CAN.begin(CANController::Mode::Config) != CANController::OK) {
    Serial.println("CAN begin FAIL - delaying for 1 second");
    delay(1000);
  }
  Serial.println("CAN begin OK");

  // CAN controller is in Config mode so setup receive filters, then change to Normal mode.
  // The receive filters will be setup to only receive 11-bit ID's 0x0100, and 0x0103. All other ID's will be filtered out / ignored.
  // 11-bit ID filter
  CAN.setFiltersRxb0(0x100, 0x103, 0x07ff, false);
  CAN.setFiltersRxb1(0x100, 0x100, 0x100, 0x100, 0x07ff, false);
  CAN.setFilters(true);
  Serial.println("CAN filters setup");
  
  // -or- 29-bit ID filter
  //CAN.setFiltersRxb0(0x100, 0x103, 0x1FFFFFFF, true);
  //CAN.setFiltersRxb1(0x100, 0x100, 0x100, 0x100, 0x1FFFFFFF, true);
  //CAN.setFilters(true);

  CAN.setMode(CANController::Mode::Normal);

  CAN.setInterruptCallbacks(&onReceive, &onWakeup);
}

void loop() {
  delay(2000);
}
