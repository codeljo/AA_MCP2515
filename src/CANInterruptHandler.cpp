#include "CANInterruptHandler.h"

#define CAN_INT_INSTANCE_MAX 4

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

    if (digitalPinToInterrupt(int_pin) == NOT_AN_INTERRUPT) { return false; }

    for (uint8_t i=0; i<CAN_INT_INSTANCE_MAX; i++) {
      if (_controller_instances[i] == nullptr) {
        _controller_instances[i] = controller;
        switch(i) {
          case 0:
            attachInterrupt(digitalPinToInterrupt(int_pin), onInterruptInstance0, LOW);
            break;
          case 1:
            attachInterrupt(digitalPinToInterrupt(int_pin), onInterruptInstance1, LOW);
            break;
          case 2:
            attachInterrupt(digitalPinToInterrupt(int_pin), onInterruptInstance2, LOW);
            break;
          case 3:
            attachInterrupt(digitalPinToInterrupt(int_pin), onInterruptInstance3, LOW);
            break;
        }
        return true;
      }
    }

    return false;
  }

  void removeInterruptHandler(CANController * controller, uint8_t int_pin) {

    if (digitalPinToInterrupt(int_pin) == NOT_AN_INTERRUPT) { return; }
    
    for (uint8_t i=0; i<CAN_INT_INSTANCE_MAX; i++) {
      if (_controller_instances[i] == controller) {
        detachInterrupt(digitalPinToInterrupt(int_pin));
        _controller_instances[i] = nullptr;
        break;
      }
    }
    
  }

}
