#ifndef _CANREGISTERS_H
#define _CANREGISTERS_H

// SPI Instructions
#define INSTRUCTION_RESET 0xc0
#define INSTRUCTION_READ  0x03
#define INSTRUCTION_WRITE 0x02
#define INSTRUCTION_RTS0  0x81
#define INSTRUCTION_RTS1  0x82
#define INSTRUCTION_RTS2  0x84
#define INSTRUCTION_READSTATUS 0xa0
#define INSTRUCTION_RXSTATUS   0xb0
#define INSTRUCTION_BITMODIFY  0x05

// SPI READ STATUS bits
#define READSTATUS_TX2IF  (1<<7)
#define READSTATUS_TX2REQ (1<<6)
#define READSTATUS_TX1IF  (1<<5)
#define READSTATUS_TX1REQ (1<<4)
#define READSTATUS_TX0IF  (1<<3)
#define READSTATUS_TX0REQ (1<<2)
#define READSTATUS_RX1IF  (1<<1)
#define READSTATUS_RX0IF  (1<<0)

// Filter Registers 0,1,2
#define RXF0SIDH 0x00
#define RXF0SIDL 0x01
#define RXF0EID8 0x02
#define RXF0EID0 0x03
#define RXF1SIDH 0x04
#define RXF1SIDL 0x05
#define RXF1EID8 0x06
#define RXF1EID0 0x07
#define RXF2SIDH 0x08
#define RXF2SIDL 0x09
#define RXF2EID8 0x0a
#define RXF2EID0 0x0b

// Pin Control, Status Registers
#define BFPCTRL   0x0c
#define TXRTSCTRL 0x0d

// CAN registers
#define CANSTAT 0x0e
#define CANCTRL 0x0f

// Filter Registers 3,4,5
#define RXF3SIDH 0x10
#define RXF3SIDL 0x11
#define RXF3EID8 0x12
#define RXF3EID0 0x13
#define RXF4SIDH 0x14
#define RXF4SIDL 0x15
#define RXF4EID8 0x16
#define RXF4EID0 0x17
#define RXF5SIDH 0x18
#define RXF5SIDL 0x19
#define RXF5EID8 0x1a
#define RXF5EID0 0x1b

// Error Counter Registers
#define TEC 0x1c
#define REC 0x1d

// Mask Registers
#define RXM0SIDH 0x20
#define RXM0SIDL 0x21
#define RXM0EID8 0x22
#define RXM0EID0 0x23
#define RXM1SIDH 0x24
#define RXM1SIDL 0x25
#define RXM1EID8 0x26
#define RXM1EID0 0x27

// Configuration Registers
#define CNF3 0x28
#define CNF2 0x29
#define CNF1 0x2a

// Interrupt Registers
#define CANINTE 0x2b
#define CANINTF 0x2c

// Error Flag Register
#define EFLG 0x2d

// Transmit Registers (0)
#define TXB0CTRL 0x30
#define TXB0SIDH 0x31
#define TXB0SIDL 0x32
#define TXB0EID8 0x33
#define TXB0EID0 0x34
#define TXB0DLC  0x35
#define TXB0D0 0x36
#define TXB0D1 0x37
#define TXB0D2 0x38
#define TXB0D3 0x39
#define TXB0D4 0x3a
#define TXB0D5 0x3b
#define TXB0D6 0x3c
#define TXB0D7 0x3d

// Transmit Registers (1)
#define TXB1CTRL 0x40
#define TXB1SIDH 0x41
#define TXB1SIDL 0x42
#define TXB1EID8 0x43
#define TXB1EID0 0x44
#define TXB1DLC  0x45
#define TXB1D0 0x46
#define TXB1D1 0x47
#define TXB1D2 0x48
#define TXB1D3 0x49
#define TXB1D4 0x4a
#define TXB1D5 0x4b
#define TXB1D6 0x4c
#define TXB1D7 0x4d

// Transmit Registers (2)
#define TXB2CTRL 0x50
#define TXB2SIDH 0x51
#define TXB2SIDL 0x52
#define TXB2EID8 0x53
#define TXB2EID0 0x54
#define TXB2DLC  0x55
#define TXB2D0 0x56
#define TXB2D1 0x57
#define TXB2D2 0x58
#define TXB2D3 0x59
#define TXB2D4 0x5a
#define TXB2D5 0x5b
#define TXB2D6 0x5c
#define TXB2D7 0x5d

// Receive Registers (0)
#define RXB0CTRL 0x60
#define RXB0SIDH 0x61
#define RXB0SIDL 0x62
#define RXB0EID8 0x63
#define RXB0EID0 0x64
#define RXB0DLC  0x65
#define RXB0D0 0x66
#define RXB0D1 0x67
#define RXB0D2 0x68
#define RXB0D3 0x69
#define RXB0D4 0x6a
#define RXB0D5 0x6b
#define RXB0D6 0x6c
#define RXB0D7 0x6d

// Receive Registers (1)
#define RXB1CTRL 0x70
#define RXB1SIDH 0x71
#define RXB1SIDL 0x72
#define RXB1EID8 0x73
#define RXB1EID0 0x74
#define RXB1DLC  0x75
#define RXB1D0 0x76
#define RXB1D1 0x77
#define RXB1D2 0x78
#define RXB1D3 0x79
#define RXB1D4 0x7a
#define RXB1D5 0x7b
#define RXB1D6 0x7c
#define RXB1D7 0x7d

// BFPCTRL bits
#define BFPCTRL_B1BFS (1<<5)
#define BFPCTRL_B0BFS (1<<4)
#define BFPCTRL_B1BFE (1<<3)
#define BFPCTRL_B0BFE (1<<2)
#define BFPCTRL_B1BFM (1<<1)
#define BFPCTRL_B0BFM (1<<0)

// TXRTSCTRL bits
#define TXRTSCTRL_B2RTS (1<<5)
#define TXRTSCTRL_B1RTS (1<<4)
#define TXRTSCTRL_B0RTS (1<<3)
#define TXRTSCTRL_B2RTSM (1<<2)
#define TXRTSCTRL_B1RTSM (1<<1)
#define TXRTSCTRL_B0RTSM (1<<0)

// CANSTAT bits
#define CANSTAT_OPMOD_MASK 0b11100000
#define CANSTAT_ICOD_MASK  0b00001110
#define CANSTAT_ICOD_NO_INT     0b00000000
#define CANSTAT_ICOD_ERROR_INT  0b00000010
#define CANSTAT_ICOD_WAKEUP_INT 0b00000100
#define CANSTAT_ICOD_TXB0_INT   0b00000110
#define CANSTAT_ICOD_TXB1_INT   0b00001000
#define CANSTAT_ICOD_TXB2_INT   0b00001010
#define CANSTAT_ICOD_RXB0_INT   0b00001100
#define CANSTAT_ICOD_RXB1_INT   0b00001110

// CANCTRL bits
#define CANCTRL_REQOP_MASK  0b11100000
#define CANCTRL_CLKPRE_MASK 0b00000011
#define CANCTRL_ABAT  (1<<4)
#define CANCTRL_OSM   (1<<3)
#define CANCTRL_CLKEN (1<<2)
#define CANCTRL_REQOP_NORMAL     0b00000000
#define CANCTRL_REQOP_SLEEP      0b00100000
#define CANCTRL_REQOP_LOOPBACK   0b01000000
#define CANCTRL_REQOP_LISTENONLY 0b01100000
#define CANCTRL_REQOP_CONFIG     0b10000000

// CNF3 bits
#define CNF3_PHSEG2_MASK 0b00000111
#define CNF3_SOF (1<<7)
#define CNF3_WAKFIL  (1<<6)
#define CNF3_PHSEG22 (1<<2)
#define CNF3_PHSEG21 (1<<1)
#define CNF3_PHSEG20 (1<<0)

// CNF2 bits
#define CNF2_PHSEG1_MASK 0b00111000
#define CNF2_PRSEG_MASK  0b00000111
#define CNF2_BTLMODE (1<<7)
#define CNF2_SAM     (1<<6)
#define CNF2_PHSEG12 (1<<5)
#define CNF2_PHSEG11 (1<<4)
#define CNF2_PHSEG10 (1<<3)
#define CNF2_PRSEG2  (1<<2)
#define CNF2_PRSEG1  (1<<1)
#define CNF2_PRSEG0  (1<<0)

// CNF1 bits
#define CNF3_SJW_MASK 0b11000000
#define CNF3_BRP_MASK 0b00111111
#define CNF3_SJW1 (1<<7)
#define CNF3_SJW0 (1<<6)
#define CNF3_BRP5 (1<<5)
#define CNF3_BRP4 (1<<4)
#define CNF3_BRP3 (1<<3)
#define CNF3_BRP2 (1<<2)
#define CNF3_BRP1 (1<<1)
#define CNF3_BRP0 (1<<0)

// CANINTE bits
#define CANINTE_MERRE (1<<7)
#define CANINTE_WAKIE (1<<6)
#define CANINTE_ERRIE (1<<5)
#define CANINTE_TX2IE (1<<4)
#define CANINTE_TX1IE (1<<3)
#define CANINTE_TX0IE (1<<2)
#define CANINTE_RX1IE (1<<1)
#define CANINTE_RX0IE (1<<0)

// CANINTF bits
#define CANINTF_MERRF (1<<7)
#define CANINTF_WAKIF (1<<6)
#define CANINTF_ERRIF (1<<5)
#define CANINTF_TX2IF (1<<4)
#define CANINTF_TX1IF (1<<3)
#define CANINTF_TX0IF (1<<2)
#define CANINTF_RX1IF (1<<1)
#define CANINTF_RX0IF (1<<0)

// EFLG bits
#define EFLG_RX1OVR (1<<7)
#define EFLG_RX0OVR (1<<6)
#define EFLG_TXBO   (1<<5)
#define EFLG_TXEP   (1<<4)
#define EFLG_RXEP   (1<<3)
#define EFLG_TXWAR  (1<<2)
#define EFLG_RXWAR  (1<<1)
#define EFLG_EWARN  (1<<0)

// TXBnCTRL bits
#define TXBnCTRL_ABTF_MLOA_TXERR_MASK 0b01110000
#define TXBnCTRL_TXP_MASK 0b00000011
#define TXBnCTRL_ABTF  (1<<6)
#define TXBnCTRL_MLOA  (1<<5)
#define TXBnCTRL_TXERR (1<<4)
#define TXBnCTRL_TXREQ (1<<3)
#define TXBnCTRL_TXP1  (1<<1)
#define TXBnCTRL_TXP0  (1<<0)

// TXBnSIDL bits
#define TXBnSIDL_SID2_1_0_MASK 0b11100000
#define TXBnSIDL_EID17_16_MASK 0b00000011
#define TXBnSIDL_EXIDE (1<<3)

// TXBnDLC bits
#define TXBnDLC_DLC_MASK 0b00001111
#define TXBnDLC_RTR (1<<6)

// RXBnCTRL bits
#define RXBnCTRL_RXM_MASK 0b01100000
#define RXBnCTRL_RXM_OFF  0b01100000
#define RXBnCTRL_RXM_ON   0b00000000
#define RXBnCTRL_RXRTR (1<<3)
#define RXB0CTRL_BUKT  (1<<2)
#define RXB1CTRL_FILHIT2 (1<<2)
#define RXB1CTRL_FILHIT1 (1<<1)
#define RXBnCTRL_FILHIT0 (1<<0)

// RXBnSIDL bits
#define RXBnSIDL_SID2_1_0_MASK 0b11100000
#define RXBnSIDL_EID17_16_MASK 0b00000011
#define RXBnSIDL_SRR (1<<4)
#define RXBnSIDL_IDE (1<<3)

// RXBnDLC bits
#define RXBnDLC_DLC_MASK 0b00001111
#define RXBnDLC_RTR (1<<6)

// RXFnSIDL bits
#define RXFnSIDL_SID2_1_0_MASK 0b11100000
#define RXFnSIDL_EID17_16_MASK 0b00000011
#define RXFnSIDL_EXIDE (1<<3)

// RXMnSIDL bits
#define RXMnSIDL_SID2_1_0_MASK 0b11100000
#define RXMnSIDL_EID17_16_MASK 0b00000011

#endif  /* _CANREGISTERS_H */

/*
  Configuration mode is the only mode where the following registers are modifiable:
  • CNF1, CNF2, CNF3 registers
  • TXRTSCTRL register
  • Filter registers
  • Mask registers
*/

/*
  11-bit id (max 11-bit id: 0x7FF)
  29-bit id (max 29-bit id: 0x1FFFFFFF)

  2^11 = 2,048 standard message identifiers
  2^29 = 536,870,912 extended message identifiers
  Both formats, standard (11-bit message ID) and Extended (29-bit message ID), may co-exist on the same CAN bus.

  To enable standard and extended frames to be sent across a shared network,
  the 29-bit extended message identifier is split into 11-bit (Most Significant) and 18-bit (Least Significant) sections.
*/
