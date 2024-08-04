#include "CANFrame.h"
#include "CANRegisters.h"

constexpr uint32_t CAN_11BIT_ID_MAX = 0x7FF;
constexpr uint32_t CAN_29BIT_ID_MAX = 0x1FFFFFFF;
constexpr uint8_t CAN_DLC_MAX = 0x08;

CANFrame::CANFrame() : CANFrame::CANFrame(0, NULL, 0, false, false) { }

CANFrame::CANFrame(uint32_t id, const void * data, uint8_t data_length) : CANFrame::CANFrame(id, data, data_length, false, (id > CAN_11BIT_ID_MAX)) { }

CANFrame::CANFrame(uint32_t id, const void * data, uint8_t data_length, bool isRemoteFrame, bool isExtendedFrame) : _extendedframe(isExtendedFrame) {
  setId(id);
  setData(data, data_length);
  setRemoteFrame(isRemoteFrame);
}

CANFrame::~CANFrame() { }

void CANFrame::setId(uint32_t id) {
  if ((id <= CAN_11BIT_ID_MAX) && (!_extendedframe)) {
		_register_buffer.sidh = (id >> 3);
		_register_buffer.sidl = (id << 5);
		_register_buffer.eid8 = 0;
		_register_buffer.eid0 = 0;
	} else {
    id &= CAN_29BIT_ID_MAX;
		_register_buffer.sidh = (id >> 21);
		_register_buffer.sidl = ((id >> 13) & TXBnSIDL_SID2_1_0_MASK) | TXBnSIDL_EXIDE | ((id >> 16) & TXBnSIDL_EID17_16_MASK);
		_register_buffer.eid8 = (id & 0x0000FF00) >> 8;
		_register_buffer.eid0 = (id & 0x000000FF);
	}
}

void CANFrame::setData(const void * data, uint8_t data_length) {
  uint8_t * src = (uint8_t *)data;
  uint8_t * dst = _register_buffer.data;
  for (uint8_t i=0; i<min(data_length, CAN_DLC_MAX); i++) {
    *(dst++) = *(src++);
  }
  setDlc(data_length);
}

void CANFrame::setDlc(uint8_t dlc) {
  _register_buffer.dlc = (_register_buffer.dlc & (~TXBnDLC_DLC_MASK)) | min(dlc, CAN_DLC_MAX);
}

void CANFrame::setRemoteFrame(bool isRemoteFrame) {
  _register_buffer.dlc = (_register_buffer.dlc & (~TXBnDLC_RTR)) | (isRemoteFrame ? TXBnDLC_RTR : 0);
}

uint32_t CANFrame::getId() {
  uint32_t id = (_register_buffer.sidh << 3) | ((_register_buffer.sidl & TXBnSIDL_SID2_1_0_MASK) >> 5);
  if (_register_buffer.sidl & TXBnSIDL_EXIDE) {
    id = (id << 18) | (((uint32_t)_register_buffer.sidl & TXBnSIDL_EID17_16_MASK) << 16) | ((uint32_t)_register_buffer.eid8 << 8) | _register_buffer.eid0;
  }
  return id;
}

uint8_t CANFrame::getDlc() {
  return (_register_buffer.dlc & TXBnDLC_DLC_MASK);
}

bool CANFrame::isRemoteFrame() {
  // TX - RTR (Remote Transmission Request)
  // RX - SRR (Standard Frame Remote Transmit Request), RTR (Extended Frame Remote Transmission Request)
  bool isTxRtr = ((_register_buffer.dlc & TXBnDLC_RTR) == TXBnDLC_RTR);
  bool isRxSrr = ((_register_buffer.sidl & RXBnSIDL_SRR) == RXBnSIDL_SRR) && ((_register_buffer.sidl & RXBnSIDL_IDE) == 0);
  bool isRxRtr = ((_register_buffer.dlc & RXBnDLC_RTR) == RXBnDLC_RTR) && ((_register_buffer.sidl & RXBnSIDL_IDE) == RXBnSIDL_IDE);
  return isTxRtr | isRxSrr | isRxRtr;
}

bool CANFrame::isExtendedFrame() {
  return (_register_buffer.sidl & TXBnSIDL_EXIDE) == TXBnSIDL_EXIDE;
}

const uint8_t * CANFrame::getData() {
  return (const uint8_t *)_register_buffer.data;
}

void CANFrame::getData(uint8_t data_out[], uint8_t data_length) {
  const uint8_t dlc = getDlc();
  for (uint8_t i=0; i<min(data_length, CAN_DLC_MAX); i++) {
      data_out[i] = (i < dlc) ? _register_buffer.data[i] : 0;
  }
}

void CANFrame::reset() {
  //_extendedframe = false;
  _register_buffer.reset();
}

void CANFrame::print(String title, Stream & out) {
  out.print(title);
  out.print(" id:0x"); out.print(getId(), HEX);
  out.print(" dlc:"); out.print(getDlc());
  out.print(" remote:"); out.print(isRemoteFrame());
  out.print(" extended:"); out.print(isExtendedFrame());
  out.print(" data:");
  const uint8_t *data = getData();
  const uint8_t dlc = getDlc();
  for (uint8_t i = 0; i<dlc; i++) {
    out.print("0x"); out.print(*(data++), HEX); out.print(" ");
  }
  out.println("");
}
