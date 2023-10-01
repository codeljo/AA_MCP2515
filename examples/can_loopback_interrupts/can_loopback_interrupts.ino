/*
  CAN Loopback Interrupts Example

  This will verify the SPI connection between the Arduino and the CAN controller(MCP2515) are correct.
  Transmits a CAN standard frame every 2 seconds.

  MIT License
  https://github.com/codeljo/AA_MCP2515
*/
#include "AA_MCP2515.h"

const uint8_t CAN_PIN_CHIPSELECT = 10;
const int8_t CAN_PIN_INTERRUPT = 2;

CANController CAN(CANBitrate::Config_8MHz_500kbps, CAN_PIN_CHIPSELECT, CAN_PIN_INTERRUPT);

uint8_t data[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };

void setup() {
  Serial.begin(115200);

  if (CAN.begin(CANController::Mode::Loopback) == CANController::OK) {
    Serial.println("CAN begin OK");
  } else {
    Serial.println("CAN begin FAIL");
    // TODO: handle CAN begin failure here
  }

  CAN.setInterruptCallbacks([](CANController&, CANFrame frame){ frame.print("RX"); }, [](CANController& controller){ controller.setMode(CANController::Mode::Normal); });
}

void loop() {

  //CANFrame frame(0x100, data, sizeof(data));
  //CAN.write(frame);
  // -or-
  CAN.write(0x100, data, sizeof(data));

  delay(2000);
}
