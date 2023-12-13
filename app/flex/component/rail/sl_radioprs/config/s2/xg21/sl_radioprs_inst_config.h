#ifndef SL_RADIOPRS_INSTANCE_CONFIG_H
#define SL_RADIOPRS_INSTANCE_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>
// <h> Radio PRS Configuration

// <o RADIOPRS_INSTANCE_SOURCESEL> Radio PRS signal source
// <PRS_RAC_ACTIVE=> Radio enabled
// <PRS_RAC_TX=> Transmit mode enabled
// <PRS_RAC_RX=> Receive mode enabled
// <PRS_RAC_LNAEN=> LNA enabled for RX
// <PRS_RAC_PAEN=> PA enabled for TX
// <PRS_MODEML_ANT0=> Antenna 0
// <PRS_MODEML_ANT1=> Antenna 1
// <PRS_MODEML_DCLK=> Modem clock out
// <PRS_MODEML_DOUT=> Modem data out
// <PRS_MODEML_FRAMEDET=> Sync detected
// <PRS_MODEM_FRAMESENT=> Frame sent
// <PRS_MODEM_PREDET=> Preamble detected
// <PRS_MODEMH_PRESENT=> Preamble sent
// <PRS_MODEMH_RSSIJUMP=> change in RSSI
// <PRS_MODEMH_SYNCSENT=> Sync word sent
// <PRS_MODEMH_EOF=> end of frame
// <PRS_FRC_DCLK=> FRC clock out
// <PRS_FRC_DOUT=> FRC data out
// <i> Default: PRS_MODEML_DOUT
#define RADIOPRS_INSTANCE_SOURCESEL PRS_MODEML_DOUT

// </h>

// <<< end of configuration section >>>

// Useful Pins that work on most boards
// Pin,  Ch, Board gen  (conflict)  WSTK_P?     EXP_HEADER?
// PC00   6  xG21       (DISP_SPI)  WSTK_P01    EXP_HEADER4

// <<< sl:start pin_tool >>>
// <prs gpio=true > RADIOPRS_INSTANCE
// $[PRS_RADIOPRS_INSTANCE]
#define RADIOPRS_INSTANCE_CHANNEL    6
#define RADIOPRS_INSTANCE_PORT       gpioPortA
#define RADIOPRS_INSTANCE_PIN        3
// [PRS_RADIOPRS_INSTANCE]$
// <<< sl:end pin_tool >>>
# endif  // SL_RADIOPRS_INSTANCE_CONFIG_H
