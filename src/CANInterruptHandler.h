#ifndef _CANINTERRUPTHANDLER_H
#define _CANINTERRUPTHANDLER_H

#include "CANController.h"
#include <Arduino.h>

namespace CANInterruptHandler {
    bool addInterruptHandler(CANController * controller, uint8_t int_pin);
    void removeInterruptHandler(CANController * controller, uint8_t int_pin);
}

#endif  /* _CANINTERRUPTHANDLER_H */
