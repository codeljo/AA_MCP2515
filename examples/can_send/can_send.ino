/*
  CAN Send Example

  This will setup the CAN controller(MCP2515) to send CAN frames.
  Transmitted frames will be printed to the Serial port.
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

  if (CAN.begin(CANController::Mode::Normal) == CANController::OK) {
    Serial.println("CAN begin OK");
  } else {
    Serial.println("CAN begin FAIL");
    // TODO: handle CAN begin failure here
  }
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
