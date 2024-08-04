#ifndef _CANIO_H
#define _CANIO_H

#include "CANConfig.h"
#include <Arduino.h>
#include <SPI.h>

class CANIO {
  public:
    CANIO(CANConfig& config);
    CANIO(const CANIO&) = delete;
    ~CANIO();
    void begin();
    uint8_t read(uint8_t address);
    void read(uint8_t address, uint8_t * data, uint8_t data_length);
    void write(uint8_t value);
    void write(uint8_t address, uint8_t value);
    void write(uint8_t address, uint8_t * data, uint8_t data_length);
    void writeBits(uint8_t address, uint8_t mask, uint8_t value);
    uint8_t readStatus();
  private:
    const uint8_t _pin_cs;
    SPIClass * _spi;
    const SPISettings _spi_settings;
};

#endif  /* _CANIO_H */
