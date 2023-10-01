#ifndef _CANFRAME_H
#define _CANFRAME_H

#include <Arduino.h>

struct CANFrameRegisterBuffer {
  uint8_t sidh;
  uint8_t sidl;
  uint8_t eid8;
  uint8_t eid0;
  uint8_t dlc;
  uint8_t data[8];
  void reset() {
    uint8_t * ptr = (uint8_t*)this;
    for (uint8_t i=0; i < sizeof(CANFrameRegisterBuffer); i++) {
      *(ptr++) = 0;
    }
  }
};

class CANFrame {
  friend class CANController;
  public:
    CANFrame();
    CANFrame(uint32_t id, const void * data, uint8_t data_length);
    CANFrame(uint32_t id, const void * data, uint8_t data_length, bool isRemoteFrame, bool isExtendedFrame);
    ~CANFrame();
    void setId(uint32_t id);
    void setData(const void * data, uint8_t data_length);
    uint32_t getId();
    uint8_t getDlc();
    bool isRemoteFrame();
    bool isExtendedFrame();
    const uint8_t * getData();
    void getData(uint8_t data_out[], uint8_t data_length);
    void reset();
    void print(String title, Stream & out = Serial);
  private:
    bool _extendedframe;
    void setDlc(uint8_t dlc);
    void setRemoteFrame(bool isRemoteFrame);
    CANFrameRegisterBuffer _register_buffer {};
};

#endif  /* _CANFRAME_H */
