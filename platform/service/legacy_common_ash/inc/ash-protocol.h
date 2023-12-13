/***************************************************************************//**
 * @file
 * @brief ASH protocol header
 *
 * See @ref ash for documentation.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
/** @addtogroup ash
 *
 * See ash-protocol.h for source code.
 *
 *@{
 */

#ifndef __ASH_PROTOCOL_H__
#define __ASH_PROTOCOL_H__

#ifdef EMBER_STACK_CONNECT
#include "ezsp/ezsp-protocol.h"
#else
#include "app/util/ezsp/ezsp-protocol.h"
#endif

#define ASH_VERSION 2   ///< protocol version

// Special byte values for ASH protocol and/or low-level comm
// Bytes with these values must be escaped (byte-stuffed) before transmission
#define ASH_FLAG  0x7E  /*!<  frame delimiter */
#define ASH_ESC   0x7D  /*!<  byte stuffing escape byte */
#define ASH_XON   0x11  /*!<  flow control byte - means resume transmission */
#define ASH_XOFF  0x13  /*!<  flow control byte - means suspend transmission */
#define ASH_SUB   0x18  /*!<  replaces bytes w framing, overrun or overflow errors */
#define ASH_CAN   0x1A  /*!<  frame cancel byte */

// The wake byte special function applies only when in between frames, so it
// does not need to be escaped within a frame.
#define ASH_WAKE  0xFF  /*!<  wake signal byte (also means NCP data pending) */

// Constant used in byte-stuffing
#define ASH_FLIP  0x20  /*!< XOR mask used in byte stuffing */

// Field and frame lengths, excluding flag byte and any byte stuffing overhead
// All limits are inclusive
#define ASH_MIN_DATA_FIELD_LEN    EZSP_MIN_FRAME_LENGTH                                              ///< ash min data field len
#define ASH_MAX_DATA_FIELD_LEN    EZSP_MAX_FRAME_LENGTH                                              ///< ash max data field len
#define ASH_MIN_DATA_FRAME_LEN    (ASH_MIN_DATA_FIELD_LEN + 1)                                       ///< with control
#define ASH_MIN_FRAME_LEN         1                                                                  ///< control plus data field, but not CRC
#define ASH_MAX_FRAME_LEN         (ASH_MAX_DATA_FIELD_LEN + 1)                                       ///< ash max frame len
#define ASH_CRC_LEN               2                                                                  ///< ash crc len
#define ASH_MIN_FRAME_WITH_CRC_LEN  (ASH_MIN_FRAME_LEN + ASH_CRC_LEN)                                ///< ash min frame with crc len
#define ASH_MAX_FRAME_WITH_CRC_LEN  (ASH_MAX_FRAME_LEN + ASH_CRC_LEN)                                ///< ash max frame with crc len

// Define lengths of short frames - includes control byte and data field
#define ASH_NCP_SHFRAME_RX_LEN    2     /*!< longest non-data frame received */
#define ASH_NCP_SHFRAME_TX_LEN    3     /*!< longest non-data frame sent */
#define ASH_HOST_SHFRAME_RX_LEN   3     /*!< longest non-data frame received */
#define ASH_HOST_SHFRAME_TX_LEN   2     /*!< longest non-data frame sent */

// Control byte formats
//  +---------+----+----+----+----+----+----+----+----++---------+
//  |         | B7 | B6 | B5 | B4 | B3 | B2 | B1 | B0 ||  Range  |
//  +---------+----+----+----+----+----+----+----+----++---------+
//  | DATA    |  0 |   frameNum   | rF |    ackNum    ||0x00-0x7F|
//  +---------+----+----+----+----+----+----+----+----++---------+
//  | ACK     |  1 |  0 |  0 | pF | nF |    ackNum    ||0x80-0x9F|
//  | NAK     |  1 |  0 |  1 | pF | nF |    ackNum    ||0xA0-0xBF|
//  +---------+----+----+----+----+----+----+----+----++---------+
//  | RST     |  1 |  1 |  0 |  0 |  0 |  0 |  0 |  0 ||   0xC0  |
//  | RSTACK  |  1 |  1 |  0 |  0 |  0 |  0 |  0 |  1 ||   0xC1  |
//  | ERROR   |  1 |  1 |  0 |  0 |  0 |  0 |  1 |  0 ||   0xC2  |
//  +---------+----+----+----+----+----+----+----+----++---------+
//           rF = rFlag (retransmission flag)
//           nF = nFlag (receiver not ready flag)
//           pF = flag reserved for future use
//  Control byte values 0xC3-0xFE are unused, 0xFF is reserved.

// Define frame control byte codes
#define ASH_DFRAME_MASK     0x80                   ///< ash dframe mask
#define ASH_CONTROL_DATA    0x00                   ///< ash control data

#define ASH_SHFRAME_MASK    0xE0                   ///< ash shframe mask
#define ASH_CONTROL_ACK     0x80                   ///< ash control ack
#define ASH_CONTROL_NAK     0xA0                   ///< ash control nak
#define ASH_CONTROL_RST     0xC0                   ///< ash control rst
#define ASH_CONTROL_RSTACK  0xC1                   ///< ash control rstack
#define ASH_CONTROL_ERROR   0xC2                   ///< ash control error

#define ASH_ACKNUM_MASK     0x07      /*!< acknowledge frame number */
#define ASH_ACKNUM_BIT         0                   ///< ash acknum bit
#define ASH_RFLAG_MASK      0x08      /*!< retransmitted frame flag */
#define ASH_RFLAG_BIT          3                   ///< ash rflag bit
#define ASH_NFLAG_MASK      0x08      /*!< receiver not ready flag */
#define ASH_NFLAG_BIT          3                   ///< ash nflag bit
#define ASH_PFLAG_MASK      0x10      /*!< flag reserved for future use */
#define ASH_PFLAG_BIT          4                   ///< ash pflag bit
#define ASH_FRMNUM_MASK     0x70      /*!< DATA frame number */
#define ASH_FRMNUM_BIT         4                   ///< ash frmnum bit
#define ASH_GET_RFLAG(ctl)  ((ctl & ASH_RFLAG_MASK) >> ASH_RFLAG_BIT)                                ///< ash get rflag(ctl)
#define ASH_GET_NFLAG(ctl)  ((ctl & ASH_NFLAG_MASK) >> ASH_NFLAG_BIT)                                ///< ash get nflag(ctl)
#define ASH_GET_FRMNUM(ctl) ((ctl & ASH_FRMNUM_MASK) >> ASH_FRMNUM_BIT)                              ///< ash get frmnum(ctl)
#define ASH_GET_ACKNUM(ctl) ((ctl & ASH_ACKNUM_MASK) >> ASH_ACKNUM_BIT)                              ///< ash get acknum(ctl)

// Lengths for each frame type: includes control and data field (if any),
// excludes the CRC and flag bytes
#define ASH_FRAME_LEN_DATA_MIN  (ASH_MIN_DATA_FIELD_LEN + 1)                                         ///< ash frame len data min
#define ASH_FRAME_LEN_ACK       1     ///< control
#define ASH_FRAME_LEN_NAK       1     ///< control
#define ASH_FRAME_LEN_RST       1     ///< control
#define ASH_FRAME_LEN_RSTACK    3     ///< control, version, reset reason
#define ASH_FRAME_LEN_ERROR     3     ///< control, version, error

// Define macros for handling 3-bit frame numbers modulo 8
#define MOD8(n)     ((n) & 7)         /*!< mask to frame number modulus  */
#define INC8(n)     (n = (MOD8(n + 1)))   /*!< increment in frame number modulus  */
// Return true if n is within the range lo through hi, computed (mod 8)
#define WITHIN_RANGE(lo, n, hi) (MOD8(n - lo) <= MOD8(hi - lo))                                      ///< within range lo and hi

#endif //__ASH_PROTOCOL_H__

/** @} END addtogroup
 */
