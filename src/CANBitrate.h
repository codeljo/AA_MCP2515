#ifndef _CANBITRATE_H
#define _CANBITRATE_H

#include <Arduino.h>

namespace CANBitrate {
  
  // TODO: minimum baud-rate - TJA1050(60 kbps), MCP2551(16 kbps)
  // MHz: 8, 10, 16, 20
  // bps: (10 kbit/s), (20 kbit/s), (50 kbit/s), (125 kbit/s), (250 kbit/s), (500 kbit/s), (1000 kbit/s)(1 Mbit/s)
  
  struct Config {
    uint8_t cnf1;
    uint8_t cnf2;
    uint8_t cnf3;
  };
  
  // 8 MHz
  constexpr Config Config_8MHz_10kbps   { 0x13, 0xb6, 0x04 };
  constexpr Config Config_8MHz_20kbps   { 0x09, 0xb6, 0x04 };
  constexpr Config Config_8MHz_50kbps   { 0x03, 0xb6, 0x04 };
  constexpr Config Config_8MHz_125kbps  { 0x01, 0xac, 0x03 };
  constexpr Config Config_8MHz_250kbps  { 0x00, 0xac, 0x03 };
  constexpr Config Config_8MHz_500kbps  { 0x00, 0x91, 0x01 };
  constexpr Config Config_8MHz_1000kbps { 0x00, 0x80, 0x00 };

  // 10 MHz
  constexpr Config Config_10MHz_10kbps   { 0x18, 0xb6, 0x04 };
  constexpr Config Config_10MHz_20kbps   { 0x18, 0x92, 0x02 };
  constexpr Config Config_10MHz_50kbps   { 0x04, 0xb6, 0x04 };
  constexpr Config Config_10MHz_125kbps  { 0x04, 0x91, 0x01 };
  constexpr Config Config_10MHz_250kbps  { 0x00, 0xb6, 0x04 };
  constexpr Config Config_10MHz_500kbps  { 0x00, 0x92, 0x02 };
  constexpr Config Config_10MHz_1000kbps { 0x00, 0x80, 0x01 };

  // 16 MHz
  constexpr Config Config_16MHz_10kbps   { 0x27, 0xb6, 0x04 };
  constexpr Config Config_16MHz_20kbps   { 0x13, 0xb6, 0x04 };
  constexpr Config Config_16MHz_50kbps   { 0x07, 0xb6, 0x04 };
  constexpr Config Config_16MHz_125kbps  { 0x03, 0xac, 0x03 };
  constexpr Config Config_16MHz_250kbps  { 0x01, 0xac, 0x03 };
  constexpr Config Config_16MHz_500kbps  { 0x00, 0xac, 0x03 };
  constexpr Config Config_16MHz_1000kbps { 0x00, 0x91, 0x01 };

  // 20 MHz
  constexpr Config Config_20MHz_10kbps   { 0x31, 0xb6, 0x04 };
  constexpr Config Config_20MHz_20kbps   { 0x18, 0xb6, 0x04 };
  constexpr Config Config_20MHz_50kbps   { 0x09, 0xb6, 0x04 };
  constexpr Config Config_20MHz_125kbps  { 0x03, 0xb6, 0x04 };
  constexpr Config Config_20MHz_250kbps  { 0x01, 0xb6, 0x04 };
  constexpr Config Config_20MHz_500kbps  { 0x00, 0xb6, 0x04 };
  constexpr Config Config_20MHz_1000kbps { 0x00, 0x92, 0x02 };
}

#endif  /* _CANBITRATE_H */
