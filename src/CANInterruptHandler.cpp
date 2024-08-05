#include "CANInterruptHandler.h"

#define CAN_INT_INSTANCE_MAX 4

#if defined(ESP32) || defined(ARDUINO_ARCH_ESP32)
#define CAN_INT_MODE ONLOW
#else
#define CAN_INT_MODE LOW
#endif

namespace CANInterruptHandler {

  namespace {

    CANController * _controller_instances[CAN_INT_INSTANCE_MAX] = { nullptr, nullptr, nullptr, nullptr };

    void onInterruptInstance0() {
      if (_controller_instances[0]) { _controller_instances[0]->onInterrupt(); }
    }

    void onInterruptInstance1() {
      if (_controller_instances[1]) { _controller_instances[1]->onInterrupt(); }
    }

    void onInterruptInstance2() {
      if (_controller_instances[2]) { _controller_instances[2]->onInterrupt(); }
    }

    void onInterruptInstance3() {
      if (_controller_instances[3]) { _controller_instances[3]->onInterrupt(); }
    }

  }

  bool addInterruptHandler(CANController * controller, uint8_t int_pin) {

    #ifdef NOT_AN_INTERRUPT
    if (digitalPinToInterrupt(int_pin) == NOT_AN_INTERRUPT) { return false; }
    #endif

    for (uint8_t i=0; i<CAN_INT_INSTANCE_MAX; i++) {
      if (_controller_instances[i] == nullptr) {
        _controller_instances[i] = controller;
        pinMode(int_pin, INPUT_PULLUP);
        switch(i) {
          case 0:
            attachInterrupt(digitalPinToInterrupt(int_pin), onInterruptInstance0, CAN_INT_MODE);
            break;
          case 1:
            attachInterrupt(digitalPinToInterrupt(int_pin), onInterruptInstance1, CAN_INT_MODE);
            break;
          case 2:
            attachInterrupt(digitalPinToInterrupt(int_pin), onInterruptInstance2, CAN_INT_MODE);
            break;
          case 3:
            attachInterrupt(digitalPinToInterrupt(int_pin), onInterruptInstance3, CAN_INT_MODE);
            break;
        }
        return true;
      }
    }

    return false;
  }

  void removeInterruptHandler(CANController * controller, uint8_t int_pin) {

    #ifdef NOT_AN_INTERRUPT
    if (digitalPinToInterrupt(int_pin) == NOT_AN_INTERRUPT) { return; }
    #endif
    
    for (uint8_t i=0; i<CAN_INT_INSTANCE_MAX; i++) {
      if (_controller_instances[i] == controller) {
        detachInterrupt(digitalPinToInterrupt(int_pin));
        _controller_instances[i] = nullptr;
        break;
      }
    }
    
  }

}
