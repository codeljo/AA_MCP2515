#ifndef _CANCONTROLLER_H
#define _CANCONTROLLER_H

#include "CANBitrate.h"
#include "CANConfig.h"
#include "CANFrame.h"
#include "CANIO.h"
#include <Arduino.h>
#include <SPI.h>

struct CANErrors {
  uint8_t errorCountTx;
  uint8_t errorCountRx;
  uint8_t errorFlags;
  uint8_t txb0Flags;
  uint8_t txb1Flags;
  uint8_t txb2Flags;
  void print(Stream & out = Serial) {
    out.print("error count(tx:"); out.print(errorCountTx); out.print(" rx:"); out.print(errorCountRx); out.print(") error flags(flags:"); out.print(errorFlags, BIN);
    out.print(") error TXBn(txb0:"); out.print(txb0Flags, BIN); out.print(" txb1:"); out.print(txb1Flags, BIN); out.print(" txb2:"); out.print(txb2Flags, BIN); out.println(")");
  }
};

class CANController {
  public:
    enum Result : int8_t { OK=0, FAIL=-1 };
    enum class IOResult : int8_t { OK=0, FAIL=-1, NODATA=-2, NOBUFFER=-3, TIMEOUT=-4 };
    enum class Mode : uint8_t { Normal=0x00, Sleep=0x20, Loopback=0x40, ListenOnly=0x60, Config=0x80 };
  public:
    CANController(CANConfig& config);
    CANController(const CANController&) = delete;
    ~CANController();
    int8_t begin(Mode mode = Mode::Normal);
    bool setMode(Mode mode);
    bool setOneshot(bool enable);
    bool setFilters(bool enable);
    void setFiltersRxb0(uint32_t filter0, uint32_t filter1, uint32_t mask0, bool eid);
    void setFiltersRxb1(uint32_t filter2, uint32_t filter3, uint32_t filter4, uint32_t filter5, uint32_t mask1, bool eid);
    void setInterruptCallbacks(void (*onReceive)(CANController&, CANFrame), void (*onWakeup)(CANController&));
    Mode getMode();
    bool isOneshot();
    void onInterrupt();
    CANErrors getErrors();
    IOResult write(uint32_t id, const void * data, uint8_t data_length);
    IOResult write(CANFrame &frame);
    IOResult read(CANFrame &frame);
  private:
    void init();
    void setFilterId(uint8_t filter_base_register, uint32_t filter, bool eid);
    void setFilterMask(uint8_t mask_base_register, uint32_t mask, bool eid);
    bool sleep();
    bool wakeup(Mode mode);
    void delayMilliseconds(uint16_t delay);
    int8_t getFreeBuffer();
  private:
    CANConfig _config;
    CANIO _io;
    void (*_onReceive)(CANController&, CANFrame);
    void (*_onWakeup)(CANController&);
};

#endif  /* _CANCONTROLLER_H */
