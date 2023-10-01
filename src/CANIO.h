#ifndef _CANIO_H
#define _CANIO_H

#include <Arduino.h>
#include <SPI.h>

class CANIO {
  public:
    CANIO(uint8_t cs_pin, SPIClass spi=SPI);
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
    uint8_t _cs_pin;
    SPIClass _spi;
    SPISettings _spi_settings { 10000000, MSBFIRST, SPI_MODE0 };
};

#endif  /* _CANIO_H */
