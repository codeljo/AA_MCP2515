#ifndef _CANCONFIG_H
#define _CANCONFIG_H

#include "CANBitrate.h"
#include <Arduino.h>
#include <SPI.h>

struct CANConfig {
  
  static const uint32_t DEFAULT_SPI_HZ = 10000000;
    
  CANConfig(CANBitrate::Config bitrate_config, uint8_t cs_pin, int8_t int_pin, SPIClass& spi = SPI, uint32_t spi_hz = DEFAULT_SPI_HZ) :
            bitrate(bitrate_config),
            pin_cs(cs_pin),
            pin_int(int_pin),
            spi_class(&spi),
            spi_settings(spi_hz, MSBFIRST, SPI_MODE0) { }
  ~CANConfig() { }

  const CANBitrate::Config bitrate;
  const uint8_t pin_cs;
  const int8_t pin_int;
  SPIClass * spi_class;
  const SPISettings spi_settings;
};

#endif  /* _CANCONFIG_H */
