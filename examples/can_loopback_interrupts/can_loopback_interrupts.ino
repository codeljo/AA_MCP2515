#include "AA_MCP2515.h"

#define CAN_PIN_CHIPSELECT 10
#define CAN_PIN_INTERRUPT 2

CANController CAN(CANBitrate::Config_8MHz_500kbps, CAN_PIN_CHIPSELECT, CAN_PIN_INTERRUPT);

uint8_t data[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };

void setup() {
  Serial.begin(115200);

  if (CAN.begin(CANController::Mode::Loopback) == CANController::OK) {
    CAN.setInterruptCallbacks([](CANController&, CANFrame frame){ frame.print("RX"); }, [](CANController& controller){ controller.setMode(CANController::Mode::Normal); });
    Serial.println("CAN begin OK");
  } else {
    Serial.println("CAN begin FAIL");
  }
}

void loop() {

  //CANFrame frame(0x100, data, sizeof(data));
  //CAN.write(frame);
  // -or-
  CAN.write(0x100, data, sizeof(data));

  delay(2000);
}
