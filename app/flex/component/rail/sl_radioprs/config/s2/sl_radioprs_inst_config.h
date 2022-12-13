#ifndef SL_RADIOPRS_INSTANCE_CONFIG_H
#define SL_RADIOPRS_INSTANCE_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>
// <h> Radio PRS Configuration

// <o RADIOPRS_INSTANCE_SOURCESEL> Radio PRS signal source
// <PRS_RACL_RX=> RX active
// <PRS_RACL_TX=> TX active
// <PRS_RACL_ACTIVE=> Radio enabled
// <PRS_RACL_LNAEN=> LNA enabled for RX
// <PRS_RACL_PAEN=> PA enabled for TX
// <PRS_MODEML_ANT0=> Antenna 0
// <PRS_MODEML_ANT1=> Antenna 1
// <PRS_MODEML_DCLK=> RX data clock
// <PRS_MODEML_DOUT=> RX data out
// <PRS_MODEML_FRAMEDET=> Sync detected
// <PRS_MODEML_FRAMESENT=> Sync sent
// <PRS_MODEM_PREDET=> Preamble detected
// <PRS_MODEMH_PRESENT=> Preamble sent
// <PRS_MODEMH_RSSIJUMP=> change in RSSI
// <PRS_MODEMH_SYNCSENT=> Sync word sent
// <PRS_MODEMH_EOF=> end of frame
// <PRS_FRC_DCLK=> FRC DCLK
// <PRS_FRC_DOUT=> FRC DOUT
// <i> Default: PRS_MODEML_DOUT
#define RADIOPRS_INSTANCE_SOURCESEL PRS_MODEML_DOUT

// </h>

// <<< end of configuration section >>>

// Useful Pins that work on most boards
// Pin,  Ch, Board gen  (conflict)  WSTK_P?     EXP_HEADER?
// PC00   6  xG21       (DISP_SPI)  WSTK_P01    EXP_HEADER4
// PA06   0  xG22       (I2C)       WSTK_P11    EXP_HEADER14
// PC05   6  xG23       (I2C)       WSTK_P12    EXP_HEADER15
// PC07   6  xG24       (I2C)       WSTK_P13    EXP_HEADER16

// <<< sl:start pin_tool >>>
// <prs gpio=true > RADIOPRS_INSTANCE
// $[PRS_RADIOPRS_INSTANCE]
#define RADIOPRS_INSTANCE_CHANNEL    6
#define RADIOPRS_INSTANCE_PORT       gpioPortC
#define RADIOPRS_INSTANCE_PIN        5
// [PRS_RADIOPRS_INSTANCE]$
// <<< sl:end pin_tool >>>
# endif  // SL_RADIOPRS_INSTANCE_CONFIG_H
