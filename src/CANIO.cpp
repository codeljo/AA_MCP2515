#include "CANIO.h"
#include "CANRegisters.h"

CANIO::CANIO(CANConfig& config) : _pin_cs(config.pin_cs), _spi(config.spi_class), _spi_settings(config.spi_settings) { }

CANIO::~CANIO() { }

void CANIO::begin() {
  pinMode(_pin_cs, OUTPUT);
  digitalWrite(_pin_cs, HIGH);
  _spi->begin();
}

uint8_t CANIO::read(uint8_t address) {
  uint8_t i = 0;
  read(address, &i, 1);
  return i;
}

void CANIO::read(uint8_t address, uint8_t * data, uint8_t data_length) {
  _spi->beginTransaction(_spi_settings);
  digitalWrite(_pin_cs, LOW);
  _spi->transfer(INSTRUCTION_READ);
  _spi->transfer(address);
  while (data_length--) {
    *(data++) = _spi->transfer(0x00);
  }
  digitalWrite(_pin_cs, HIGH);
  _spi->endTransaction();
}

uint8_t CANIO::readStatus() {
  _spi->beginTransaction(_spi_settings);
  digitalWrite(_pin_cs, LOW);
  _spi->transfer(INSTRUCTION_READSTATUS);
  uint8_t status = _spi->transfer(0x00);
  digitalWrite(_pin_cs, HIGH);
  _spi->endTransaction();
  return status;
}

void CANIO::write(uint8_t value) {
  _spi->beginTransaction(_spi_settings);
  digitalWrite(_pin_cs, LOW);
  _spi->transfer(value);
  digitalWrite(_pin_cs, HIGH);
  _spi->endTransaction();
}

void CANIO::write(uint8_t address, uint8_t value) {
  write(address, &value, 1);
}

void CANIO::write(uint8_t address, uint8_t * data, uint8_t data_length) {
  _spi->beginTransaction(_spi_settings);
  digitalWrite(_pin_cs, LOW);
  _spi->transfer(INSTRUCTION_WRITE);
  _spi->transfer(address);
  while (data_length--) {
    _spi->transfer(*(data++));
  }
  digitalWrite(_pin_cs, HIGH);
  _spi->endTransaction();
}

void CANIO::writeBits(uint8_t address, uint8_t mask, uint8_t value) {
  _spi->beginTransaction(_spi_settings);
  digitalWrite(_pin_cs, LOW);
  _spi->transfer(INSTRUCTION_BITMODIFY);
  _spi->transfer(address);
  _spi->transfer(mask);
  _spi->transfer(value);
  digitalWrite(_pin_cs, HIGH);
  _spi->endTransaction();
}
