#ifndef SL_RADIOPRS_INSTANCE_CONFIG_H
#define SL_RADIOPRS_INSTANCE_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>
// <h> Radio PRS Configuration

#define PRS_MODEM_DCLK (PRS_MODEM_PRESENT + 1)
#define PRS_MODEM_DOUT (PRS_MODEM_PRESENT + 2)

// <o RADIOPRS_INSTANCE_SOURCESEL> Radio PRS signal source
// <PRS_RAC_ACTIVE=> Radio enabled
// <PRS_RAC_TX=> Transmit mode enabled
// <PRS_RAC_RX=> Receive mode enabled
// <PRS_RAC_LNAEN=> LNA enabled for RX
// <PRS_RAC_PAEN=> PA enabled for TX
// <PRS_MODEM_FRAMEDET=> Frame detected
// <PRS_MODEM_PREDET=> Preamble detected
// <PRS_MODEM_TIMDET=> Timing detected
// <PRS_MODEM_FRAMESENT=> Frame sent
// <PRS_MODEM_SYNCSENT=> Sync word sent
// <PRS_MODEM_PRESENT=> Preamble sent
// <PRS_MODEM_DCLK=> Modem clock out
// <PRS_MODEM_DOUT=> Modem data out
// <PRS_MODEM_ANT0=> Antenna 0
// <PRS_MODEM_ANT1=> Antenna 1
// <i> Default: 0x5607
#define RADIOPRS_INSTANCE_SOURCESEL PRS_MODEM_DOUT

// </h>

// <<< end of configuration section >>>

// Useful Pins that work on most boards
// Pin,  Ch, Loc, Board gen     (conflict)  WSTK_P?     EXP_HEADER?
// PC10,  9,  15  Series1       (I2C)       WSTK_P12    EXP_HEADER15
// PC11, 10,   5  Series1       (I2C)       WSTK_P13    EXP_HEADER16
// PF02,  0,   2  xG1/xG13/xG14 (SWO)       WSTK_P28
// PF03,  1,   2  xG1/xG13/xG14 (TDI)       WSTK_P10    EXP_HEADER13
// PF04,  2,   2  xG1/xG13/xG14 (LED0)      WSTK_P8     EXP_HEADER11
// PF05,  3,   2  xG1/xG13/xG14 (LED1)      WSTK_P32
// PF06,  0,   6  xG1/xG13/xG14 (BTN0)      WSTK_P34
// PF07,  1,   6  xG1/xG13/xG14 (BTN1)      WSTK_P36
// PC09, 11,   2  xG12                      WSTK_P10    EXP_HEADER13
// PD09,  3,   8  xG12                      WSTK_P02    EXP_HEADER05
// PD10,  4,   1  xG12                      WSTK_P04    EXP_HEADER07
// PD11,  5,   1  xG12                      WSTK_P06    EXP_HEADER09
// PD12,  6,  14  xG12                      WSTK_P08    EXP_HEADER11

// <<< sl:start pin_tool >>>
// <prs gpio=true > RADIOPRS_INSTANCE
// $[PRS_RADIOPRS_INSTANCE]
#define RADIOPRS_INSTANCE_CHANNEL    9
#define RADIOPRS_INSTANCE_PORT       gpioPortC
#define RADIOPRS_INSTANCE_PIN        10
#define RADIOPRS_INSTANCE_LOC        15
// [PRS_RADIOPRS_INSTANCE]$
// <<< sl:end pin_tool >>>
# endif  // SL_RADIOPRS_INSTANCE_CONFIG_H
