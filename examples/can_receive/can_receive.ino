#include "AA_MCP2515.h"

#define CAN_PIN_CHIPSELECT 10
#define CAN_PIN_INTERRUPT 2

CANController CAN(CANBitrate::Config_8MHz_500kbps, CAN_PIN_CHIPSELECT, CAN_PIN_INTERRUPT);

void setup() {
  Serial.begin(115200);

  if (CAN.begin(CANController::Mode::Normal) == CANController::OK) {
    Serial.println("CAN begin OK");
  } else {
    Serial.println("CAN begin FAIL");
  }
}

void loop() {

  CANFrame frame;
  if (CAN.read(frame) == CANController::IOResult::OK) {
    frame.print("RX");
  }
  
  delay(1000);
}
