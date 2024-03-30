#include "CANController.h"
#include "CANInterruptHandler.h"
#include "CANRegisters.h"

CANController::CANController(CANConfig& config) : _config(config), _io(_config) { }

CANController::~CANController() {
  CANInterruptHandler::removeInterruptHandler(this, _config.pin_int);
}

int8_t CANController::begin(Mode mode) {

  if (_config.pin_int >= 0) { pinMode(_config.pin_int, INPUT_PULLUP); }
  
  // spi
  _io.begin();

  // set configuration mode
  _io.write(INSTRUCTION_RESET);
  delayMilliseconds(500);
  if ((_io.read(CANSTAT) & CANSTAT_OPMOD_MASK) != static_cast<uint8_t>(Mode::Config)) { return FAIL; }

  // set cnf1,2,3
  _io.write(CNF1, _config.bitrate.cnf1);
  _io.write(CNF2, _config.bitrate.cnf2);
  _io.write(CNF3, _config.bitrate.cnf3);

  // set filters

  // set mode
  return setMode(mode) ? OK : FAIL;
}

bool CANController::setMode(Mode mode) {
  if (mode == Mode::Sleep) { return sleep(); }
  if (getMode() == Mode::Sleep) { return wakeup(mode); }
  _io.writeBits(CANCTRL, CANCTRL_REQOP_MASK, static_cast<uint8_t>(mode));
  return ((_io.read(CANCTRL) & CANCTRL_REQOP_MASK) == (static_cast<uint8_t>(mode) & CANCTRL_REQOP_MASK));
}

bool CANController::setOneshot(bool enable) {
  _io.writeBits(CANCTRL, CANCTRL_OSM, enable ? CANCTRL_OSM : 0);
  return ((_io.read(CANCTRL) & CANCTRL_OSM) == ((enable ? CANCTRL_OSM : 0) & CANCTRL_OSM));
}

bool CANController::setFilters(bool enable) {
  // (00 = mask/filters ON (default)) (11 = mask/filters OFF; receives any message)
  _io.writeBits(RXB0CTRL, RXBnCTRL_RXM_MASK, enable ? 0 : RXBnCTRL_RXM_MASK);
  _io.writeBits(RXB1CTRL, RXBnCTRL_RXM_MASK, enable ? 0 : RXBnCTRL_RXM_MASK);
  if ((_io.read(RXB0CTRL) & RXBnCTRL_RXM_MASK) != ((enable ? 0 : RXBnCTRL_RXM_MASK) & RXBnCTRL_RXM_MASK)) { return false; }
  if ((_io.read(RXB1CTRL) & RXBnCTRL_RXM_MASK) != ((enable ? 0 : RXBnCTRL_RXM_MASK) & RXBnCTRL_RXM_MASK)) { return false; }
  return true;
}

void CANController::setFilterId(uint8_t filter_base_register, uint32_t filter, bool eid) {
  // 29-bit extended message identifier is split into 11-bit (Most Significant) and 18-bit (Least Significant) sections
  if (eid) {
    filter = ((filter & 0x1FFC0000) >> 18) | ((filter & 0x3FFFF) << 11);
  }
  _io.write(filter_base_register, (filter >> 3) & 0xFF);
  _io.write(filter_base_register + 1, ((filter & 0b111) << 5) | (eid == 0 ? 0 : 1<<3) | ((filter & 0x18000000) >> 27));
  _io.write(filter_base_register + 2, ((filter & 0x7F80000) >> 19));
  _io.write(filter_base_register + 3, ((filter & 0x7F800) >> 11));
}

void CANController::setFilterMask(uint8_t mask_base_register, uint32_t mask, bool eid) {
  // 29-bit extended message identifier is split into 11-bit (Most Significant) and 18-bit (Least Significant) sections
  if (eid) {
    mask = ((mask & 0x1FFC0000) >> 18) | ((mask & 0x3FFFF) << 11);
  }
  _io.write(mask_base_register, (mask >> 3) & 0xFF);
  _io.write(mask_base_register + 1, ((mask & 0b111) << 5) | ((mask & 0x18000000) >> 27));
  _io.write(mask_base_register + 2, ((mask & 0x7F80000) >> 19));
  _io.write(mask_base_register + 3, ((mask & 0x7F800) >> 11));
}

// RXF0, RXF1 (and filter mask, RXM0), are associated with RXB0
void CANController::setFiltersRxb0(uint32_t filter0, uint32_t filter1, uint32_t mask0, bool eid) {
  //RXFnSIDH, RXFnSIDL, RXFnEID8, RXFnEID0 (RXB0 filters: RXF0, RXF1)
  //RXM0SIDH, RXM0SIDL, RXM0EID8, RXM0EID0 (RXB0 mask:    RXM0)
  setFilterId(RXF0SIDH, filter0, eid);
  setFilterId(RXF1SIDH, filter1, eid);
  setFilterMask(RXM0SIDH, mask0, eid);
}

// RXF2, RXF3, RXF4, RXF5 (and filter mask, RXM1), are associated with RXB1
void CANController::setFiltersRxb1(uint32_t filter2, uint32_t filter3, uint32_t filter4, uint32_t filter5, uint32_t mask1, bool eid) {
  //RXFnSIDH, RXFnSIDL, RXFnEID8, RXFnEID0 (RXB1 filters: RXF2, RXF3, RXF4, RXF5)
  //RXM1SIDH, RXM1SIDL, RXM1EID8, RXM1EID0 (RXB1 mask:    RXM1)
  setFilterId(RXF2SIDH, filter2, eid);
  setFilterId(RXF3SIDH, filter3, eid);
  setFilterId(RXF4SIDH, filter4, eid);
  setFilterId(RXF5SIDH, filter5, eid);
  setFilterMask(RXM1SIDH, mask1, eid);
}

void CANController::setInterruptCallbacks(void (*onReceive)(CANController&, CANFrame), void (*onWakeup)(CANController&)) {
  _onReceive = onReceive;
  _onWakeup = onWakeup;
  _io.writeBits(CANINTE, (CANINTE_RX1IE | CANINTE_RX0IE), onReceive ? (CANINTE_RX1IE | CANINTE_RX0IE) : 0);
  _io.writeBits(CANINTE, CANINTE_WAKIE, onWakeup ? CANINTE_WAKIE : 0);
  CANInterruptHandler::addInterruptHandler(this, _config.pin_int);
}

void CANController::onInterrupt() {

  // interrupts are disabled in ISR, handle each interrupt source before clearing the flags
  uint8_t sources = _io.read(CANINTF);

  // wakeup interrupt
  if ((sources & CANINTF_WAKIF) == CANINTF_WAKIF) {
    _io.writeBits(CANINTF, CANINTF_WAKIF, 0);
    if (_onWakeup) { _onWakeup(*this); }
  }
  
  // rx interrupt
  if ( ((sources & CANINTF_RX0IF) == CANINTF_RX0IF) || ((sources & CANINTF_RX1IF) == CANINTF_RX1IF) ) {
    CANFrame frame;
    if (read(frame) == IOResult::OK) {
      if (_onReceive) { _onReceive(*this, frame); }
    }
  }

}

CANController::Mode CANController::getMode() {
  uint8_t mode = (_io.read(CANSTAT) & CANSTAT_OPMOD_MASK);
  return static_cast<Mode>(mode);
}

bool CANController::isOneshot() {
  return (_io.read(CANCTRL) & CANCTRL_OSM) == CANCTRL_OSM;
}

CANErrors CANController::getErrors() {
  //return { _io.read(TEC), _io.read(REC), _io.read(EFLG) };
  return { _io.read(TEC),
           _io.read(REC),
           _io.read(EFLG),
           (uint8_t)(_io.read(TXB0CTRL) & TXBnCTRL_ABTF_MLOA_TXERR_MASK),
           (uint8_t)(_io.read(TXB1CTRL) & TXBnCTRL_ABTF_MLOA_TXERR_MASK),
           (uint8_t)(_io.read(TXB2CTRL) & TXBnCTRL_ABTF_MLOA_TXERR_MASK) };
}

int8_t CANController::getFreeBuffer() {
  uint8_t status = _io.readStatus();
  if ((status & READSTATUS_TX0REQ) == 0) { return TXB0CTRL; }
  if ((status & READSTATUS_TX1REQ) == 0) { return TXB1CTRL; }
  if ((status & READSTATUS_TX2REQ) == 0) { return TXB2CTRL; }
  return -1;
}

CANController::IOResult CANController::write(uint32_t id, const void * data, uint8_t data_length) {
  CANFrame frame(id, data, data_length);
  return write(frame);
}

CANController::IOResult CANController::write(CANFrame &frame) {

  const int8_t tx_register_base = getFreeBuffer();
  if (tx_register_base == -1) { return IOResult::NOBUFFER; }

  _io.write(tx_register_base + 1, &frame._register_buffer.sidh, (5 + frame.getDlc()));

  switch(tx_register_base) {
    case TXB0CTRL:
      _io.write(INSTRUCTION_RTS0);
      break;
    case TXB1CTRL:
      _io.write(INSTRUCTION_RTS1);
      break;
    case TXB2CTRL:
      _io.write(INSTRUCTION_RTS2);
      break;
  }

  uint8_t timeout = 20;
  while (timeout--) {
    uint8_t ctrl = _io.read(tx_register_base);
    if ((ctrl & TXBnCTRL_ABTF_MLOA_TXERR_MASK) != 0) { return IOResult::FAIL; }
    if ((ctrl & TXBnCTRL_TXREQ) == 0) { return IOResult::OK; }
    delayMicroseconds(1000);
  }
  return IOResult::TIMEOUT;
}

CANController::IOResult CANController::read(CANFrame &frame) {

  uint8_t rx_register;
  uint8_t rx_flag;

  switch(_io.readStatus() & (READSTATUS_RX1IF | READSTATUS_RX0IF)) {
    case 0x01:
      rx_register = RXB0SIDH;
      rx_flag = CANINTF_RX0IF;
      break;
    case 0x02:
    case 0x03:
      rx_register = RXB1SIDH;
      rx_flag = CANINTF_RX1IF;
      break;
    default:
      return IOResult::NODATA;
  }

  _io.read(rx_register, &frame._register_buffer.sidh, sizeof(CANFrameRegisterBuffer));
  _io.writeBits(CANINTF, rx_flag, 0);
  return IOResult::OK;
}

bool CANController::sleep() {
  for (uint16_t i=0; i<4096; i++) {
    _io.writeBits(CANCTRL, CANCTRL_REQOP_MASK, static_cast<uint8_t>(CANController::Mode::Sleep));
    if (i==0) { delayMilliseconds(100); }
    delayMicroseconds(1000);
    if (getMode() == CANController::Mode::Sleep) { return true; }
  }
  return false;
}

bool CANController::wakeup(Mode mode) {
  // device will wake up in ListenOnly mode
  if (getMode() == Mode::Sleep) {
    bool wakie = (_io.read(CANINTE) & CANINTE_WAKIE) == CANINTE_WAKIE;
    if (!wakie) { _io.writeBits(CANINTE, CANINTE_WAKIE, CANINTE_WAKIE); }
    _io.writeBits(CANINTF, CANINTF_WAKIF, CANINTF_WAKIF);
    delayMilliseconds(1000);
    if (!wakie) { _io.writeBits(CANINTE, CANINTE_WAKIE, 0); }
    _io.writeBits(CANINTF, CANINTF_WAKIF, 0);
  }

  if (getMode() != Mode::ListenOnly) { return false; }
  return setMode(mode);
}

void CANController::delayMilliseconds(uint16_t delay) {
  for (uint16_t i=0; i<delay; i++) { delayMicroseconds(1000); }
}
