/*
  CAN Receive Interrupts Example

  This will setup the CAN controller(MCP2515) to receive CAN frames via hardware interrupts.
  Received frames will be printed to the Serial port.

  MIT License
  https://github.com/codeljo/AA_MCP2515
*/

#include "AA_MCP2515.h"

// TODO: change CANBitrate::Config, chip select(CS) pin, and interrupt(INT) pin as required.
const CANBitrate::Config CAN_BITRATE = CANBitrate::Config_8MHz_500kbps;
const uint8_t CAN_PIN_CS = 10;
const int8_t CAN_PIN_INT = 2;

CANConfig config(CAN_BITRATE, CAN_PIN_CS, CAN_PIN_INT);
CANController CAN(config);

void setup() {
  Serial.begin(115200);

  while(CAN.begin(CANController::Mode::Normal) != CANController::OK) {
    Serial.println("CAN begin FAIL - delaying for 1 second");
    delay(1000);
  }
  Serial.println("CAN begin OK");
  
  CAN.setInterruptCallbacks([](CANController&, CANFrame frame){ frame.print("RX"); }, [](CANController& controller){ controller.setMode(CANController::Mode::Normal); });
}

void loop() {
  delay(2000);
}
