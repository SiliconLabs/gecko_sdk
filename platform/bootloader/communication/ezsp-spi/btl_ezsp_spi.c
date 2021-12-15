/***************************************************************************//**
 * @file
 * @brief EZSP-SPI communication component for Silicon Labs Bootloader.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "config/btl_config.h"

#include "em_device.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "communication/ezsp-spi/btl_ezsp_spi.h"
#include "driver/btl_driver_delay.h"
#include "driver/btl_driver_spi_peripheral.h"

#include "api/btl_reset_info.h"
#include "api/btl_interface.h"

#include "core/btl_reset.h"
#include "core/btl_bootload.h"

// Parser
#include "parser/gbl/btl_gbl_parser.h"
#include "security/btl_security_types.h"

#include "debug/btl_debug.h"

#include "btl_ezsp_gpio_activation_cfg.h"

#ifdef BTL_SPI_EUSART_ENABLE
#include "btl_spi_peripheral_eusart_driver_cfg.h"
#else
#include "btl_spi_peripheral_usart_driver_cfg.h"
#endif

// ‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
// Local variables
static EzspSpiState_t state;
static EzspSpiTxMessage_t reply;
static EzspSpiTxMessage_t interrupt;
static EzspSpiRxMessage_t rxBuffer;

static bool done = false;
static bool imageError = false;
static bool interruptPending = false;
static bool errorPending = true;
static bool querySent = false;

static bool transferActive = false;
static unsigned int transferPolls = 0;

static const EzspSpiQueryResponse_t queryResponse = {
  .btlCommand = EZSP_SPI_FRAME_BTL_QUERYRESP,
  .btlActive = 0x01,
  .manufacturerId = { 0xFF, 0xFF },
  .hardwareTag = { 0 },
  .btlCapabilities = 0x00,
  // CortexM3 platform
  .platform = 4,
  // EFR32 micro
  .micro = 24,
  // EFR32 PHY
  .phy = 9,
  .btlMajorVersion = BOOTLOADER_VERSION_MAIN_MAJOR,
  .btlMinorVersion = BOOTLOADER_VERSION_MAIN_MINOR
};

static const BootloaderParserCallbacks_t parseCb = {
  .context = NULL,
  .applicationCallback = bootload_applicationCallback,
  // Standalone bootloading doesn't care about metadata
  .metadataCallback = NULL,
  .bootloaderCallback = bootload_bootloaderCallback
};

static ImageProperties_t imageProps = {
  .contents = 0U,
  .instructions = 0xFFU,
  .imageCompleted = false,
  .imageVerified = false,
  .bootloaderVersion = 0,
  .application = { 0 }
};

static ParserContext_t parserContext;
static DecryptContext_t decryptContext;
static AuthContext_t authContext;

// ‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
// Local function prototypes

static void ezspSpi_parse(EzspSpiRxMessage_t* buffer);
static uint8_t ezspSpi_parseFrame(EzspSpiRxMessage_t* buffer);
static void ezspSpi_error(uint8_t error);
static void ezspSpi_wakeHandshake(void);

// -‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
// Helper macros

#define nHOST_ASSERT()    GPIO_PinOutClear(SL_EZSPSPI_HOST_INT_PORT, \
                                           SL_EZSPSPI_HOST_INT_PIN)
#define nHOST_DEASSERT()  GPIO_PinOutSet(SL_EZSPSPI_HOST_INT_PORT, \
                                         SL_EZSPSPI_HOST_INT_PIN)
#ifdef BTL_SPI_EUSART_ENABLE
#define nCS_ACTIVE()      (GPIO_PinInGet(SL_EUSART_SPINCP_CS_PORT, \
                                         SL_EUSART_SPINCP_CS_PIN) == 0)
#else
#define nCS_ACTIVE()      (GPIO_PinInGet(SL_USART_SPINCP_CS_PORT, \
                                         SL_USART_SPINCP_CS_PIN) == 0)
#endif

// -‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
// Functions

void communication_init(void)
{
  // Setup EZSP-specific GPIO (nHOST_INT, nWAKE)
#if defined(CMU_CTRL_HFPERCLKEN)
  CMU->CTRL |= CMU_CTRL_HFPERCLKEN;
  CMU_ClockEnable(cmuClock_GPIO, true);
#endif

  GPIO_PinModeSet(SL_EZSPSPI_HOST_INT_PORT,
                  SL_EZSPSPI_HOST_INT_PIN,
                  gpioModePushPull,
                  1);
  GPIO_PinModeSet(SL_EZSPSPI_WAKE_INT_PORT,
                  SL_EZSPSPI_WAKE_INT_PIN,
                  gpioModeInputPull,
                  1);
  // Init SPI peripheral driver
  spi_peripheral_init();
}

int32_t communication_start(void)
{
  // Assert nHOST_INT to signal to the host that we have data to send.
  // But first check for a handshake
  ezspSpi_wakeHandshake();
  nHOST_ASSERT();
  state = EZSP_SPI_STATE_RESETMESSAGE;
  reply.messageBuffer[0] = EZSP_SPI_ERROR_RESET;
  reply.messageBuffer[1] = EZSP_SPI_DEFAULT_RESET_REASON;
  reply.messageBuffer[2] = EZSP_SPI_FRAME_TERMINATOR;
  reply.messageLength = 3;
  xmodem_reset();

  return BOOTLOADER_OK;
}

int32_t communication_main(void)
{
  int32_t retVal;
  size_t rxSize;
  bool exit = false;
  bool timeout = false;

  parser_init(&parserContext,
              &decryptContext,
              &authContext,
              PARSER_FLAG_PARSE_CUSTOM_TAGS);

  while (!exit) {
    switch (state) {
      case EZSP_SPI_STATE_PROCESSING:
        spi_peripheral_enableReceiver(false);
        spi_peripheral_flush(false, true);

        if (errorPending) {
          delay_microseconds(500);
        } else {
          ezspSpi_parse(&rxBuffer);
        }

        state = EZSP_SPI_STATE_ANSWERING;
        break;

      case EZSP_SPI_STATE_ANSWERING:
        retVal = spi_peripheral_sendBuffer(reply.messageBuffer,
                                           reply.messageLength);

        if (retVal == BOOTLOADER_OK) {
          // Assert nHOST_INT to signal TX availability
          nHOST_ASSERT();
          while (spi_peripheral_getTxBytesLeft() >= reply.messageLength) ;
          nHOST_DEASSERT();
          errorPending = false;
        }
        while (nCS_ACTIVE()) ;

        spi_peripheral_enableTransmitter(false);

        if (interruptPending) {
          state = EZSP_SPI_STATE_INTERRUPTING;
        } else {
          exit = done | imageError;
          state = EZSP_SPI_STATE_IDLE;
        }
        break;

      case EZSP_SPI_STATE_RESETMESSAGE:
      case EZSP_SPI_STATE_INTERRUPTING:
        // Wait for SS to deassert
        while (nCS_ACTIVE()) ;

        delay_microseconds(20);
        nHOST_ASSERT();

        state = EZSP_SPI_STATE_IDLE;
        break;

      case EZSP_SPI_STATE_IDLE:
        // Wait for SS to deassert before re-enabling the receiver to avoid
        // garbage in the RX buffer
        while (nCS_ACTIVE()) ;

        // Re-enable the receiver to be ready for incoming commands
        spi_peripheral_enableReceiver(true);

        if (transferActive) {
          delay_milliseconds(5000, false);
        } else {
          delay_milliseconds(1000, false);
        }

        while (!nCS_ACTIVE()) {
          // During idle time, watch for WAKE handshake
          ezspSpi_wakeHandshake();
          // Also send XMODEM-CRC polling characters. Every second (up to 60)
          // when transfer hasn't started yet, every 5 seconds (up to 60) when
          // a transfer is active.
          if (delay_expired() && !interruptPending) {
            transferPolls++;
            if (transferActive) {
              if (transferPolls > 12) {
                // Timed out, cancel transfer
                timeout = true;
                break;
              } else {
                delay_milliseconds(5000, false);
              }
            } else {
              if (transferPolls > 60) {
                // Timed out, cancel transfer
                timeout = true;
                break;
              } else {
                delay_milliseconds(1000, false);
              }
            }
          }
        }

        if (timeout) {
          return BOOTLOADER_ERROR_COMMUNICATION_ERROR;
        }

        // Wait for the receiver to send a command
        rxBuffer.data.btlMessage.command = 0xFFU;
        while (rxBuffer.data.btlMessage.command == 0xFFU) {
          spi_peripheral_receiveByte(&(rxBuffer.data.btlMessage.command));
        }

        nHOST_DEASSERT();

        // Get length or terminator
        spi_peripheral_receiveByte(&(rxBuffer.data.btlMessage.length));

        // Parse command byte
        if ((rxBuffer.data.btlMessage.command == EZSP_SPI_COMMAND_BTL_FRAME)
            || (rxBuffer.data.btlMessage.command
                == EZSP_SPI_COMMAND_EZSP_FRAME)) {
          // Check for oversized packets
          if (rxBuffer.data.btlMessage.length > 133) {
            ezspSpi_error(EZSP_SPI_ERROR_OVERSIZED);
          }

          // Get packet data and terminator
          retVal = spi_peripheral_receiveBuffer(
            rxBuffer.data.btlMessage.payload.buffer,
            rxBuffer.data.btlMessage.length + 1,
            &rxSize,
            true,
            500);

          // Check status and terminator
          if (retVal != BOOTLOADER_OK) {
            ezspSpi_error(EZSP_SPI_ERROR_ABORTED);
          } else if (rxBuffer.data.btlMessage.payload.buffer[rxSize - 1]
                     != EZSP_SPI_FRAME_TERMINATOR) {
            ezspSpi_error(EZSP_SPI_ERROR_NO_TERMINATOR);
          }
        } else {
          // Check terminator
          if (rxBuffer.data.btlMessage.length != EZSP_SPI_FRAME_TERMINATOR) {
            ezspSpi_error(EZSP_SPI_ERROR_NO_TERMINATOR);
          }
        }

        state = EZSP_SPI_STATE_PROCESSING;
        break;
      default:
        break;
    }
  }

  if (imageError) {
    return BOOTLOADER_ERROR_COMMUNICATION_IMAGE_ERROR;
  }

  if (done) {
#if defined(SEMAILBOX_PRESENT) || defined(CRYPTOACC_PRESENT)
    if (imageProps.contents & BTL_IMAGE_CONTENT_SE) {
      // Install SE upgrade
      bootload_commitSeUpgrade(BTL_UPGRADE_LOCATION);

      // If we get here, the SE upgrade failed, reset and enter back to the bootloader
      reset_resetWithReason(BOOTLOADER_RESET_REASON_BOOTLOAD);
    }
#endif
    if (imageProps.contents & BTL_IMAGE_CONTENT_BOOTLOADER) {
      if (imageProps.bootloaderVersion > mainBootloaderTable->header.version) {
        // Install bootloader upgrade
        bootload_commitBootloaderUpgrade(BTL_UPGRADE_LOCATION, imageProps.bootloaderUpgradeSize);
      }

      // If we get here, the bootloader upgrade failed, reset and enter back to the bootloader
      reset_resetWithReason(BOOTLOADER_RESET_REASON_BOOTLOAD);
    }

    return BOOTLOADER_OK;
  }

  return BOOTLOADER_ERROR_COMMUNICATION_DONE;
}

/***************************************************************************//**
 * Stop communication between the bootloader and external host.
 *
 * @return @ref BOOTLOADER_OK on success
 ******************************************************************************/
void communication_shutdown(void)
{
  // Reset USART
  spi_peripheral_deinit();

  // Reset specific GPIO to Hi-Z
  GPIO_PinModeSet(SL_EZSPSPI_HOST_INT_PORT,
                  SL_EZSPSPI_HOST_INT_PIN,
                  gpioModeDisabled,
                  0);
  GPIO_PinModeSet(SL_EZSPSPI_WAKE_INT_PORT,
                  SL_EZSPSPI_WAKE_INT_PIN,
                  gpioModeDisabled,
                  0);
}

// ‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
// Local functions
// Parses raw data clocked in by SPI host
void ezspSpi_parse(EzspSpiRxMessage_t* buffer)
{
  switch (buffer->data.btlMessage.command) {
    case EZSP_SPI_COMMAND_SPI_STATUS:
      reply.messageBuffer[0] = EZSP_SPI_RESPONSE_ALIVE;
      reply.messageBuffer[1] = EZSP_SPI_FRAME_TERMINATOR;
      reply.messageLength = 2;
      return;

    case EZSP_SPI_COMMAND_SPI_VERSION:
      reply.messageBuffer[0] = EZSP_SPI_RESPONSE_VERSION;
      reply.messageBuffer[1] = EZSP_SPI_FRAME_TERMINATOR;
      reply.messageLength = 2;
      return;

    case EZSP_SPI_COMMAND_BTL_FRAME:
    case EZSP_SPI_COMMAND_EZSP_FRAME:
      // Parsing logic executes command, and overwrites reply if necessary
      reply.messageBuffer[0] = EZSP_SPI_COMMAND_BTL_FRAME;
      reply.messageBuffer[3] = EZSP_SPI_FRAME_TERMINATOR;
      reply.messageLength = 1;
      reply.messageBuffer[2] = ezspSpi_parseFrame(buffer);
      reply.messageBuffer[1] = reply.messageLength;
      reply.messageLength += 3;

      if (reply.messageBuffer[2] == EZSP_SPI_FRAME_BTL_FILEABORT) {
        interrupt.messageBuffer[0] = XMODEM_CMD_CAN;
        interrupt.messageLength = 1;
        imageError = true;
      }
      return;
    default:
      ezspSpi_error(EZSP_SPI_ERROR_UNSUPPORTED);
      return;
  }
}

// Parses the EZSP frame content and populates a reply
// Returns synchronous answer byte
uint8_t ezspSpi_parseFrame(EzspSpiRxMessage_t* buffer)
{
  int32_t retVal;
  uint8_t response;

  if ((buffer->data.btlMessage.length == 1)
      && (buffer->data.btlMessage.payload.buffer[0]
          == EZSP_SPI_FRAME_BTL_QUERY)) {
    // Bootloader query
    if (interruptPending) {
      // Reply with the interrupt data we wanted to get out
      memcpy(&reply.messageBuffer[2],
             interrupt.messageBuffer,
             interrupt.messageLength);
      reply.messageBuffer[2 + interrupt.messageLength]
        = EZSP_SPI_FRAME_TERMINATOR;
      reply.messageLength = interrupt.messageLength;
      interruptPending = false;
      return reply.messageBuffer[2];
    } else {
      // Reply with bootloader data
      memcpy(interrupt.messageBuffer,
             &queryResponse,
             sizeof(EzspSpiQueryResponse_t));
      interrupt.messageLength = sizeof(EzspSpiQueryResponse_t);
      interruptPending = true;
      querySent = true;
      return EZSP_SPI_FRAME_BTL_QUERYFOUND;
    }
  } else {
    // Parse as XMODEM
    if (!querySent) {
      return EZSP_SPI_FRAME_BTL_NO_QUERY;
    }

    if ((buffer->data.btlMessage.payload.xmodemPacket.header == XMODEM_CMD_SOH)
        && (buffer->data.btlMessage.length != (XMODEM_DATA_SIZE + 5))) {
      return EZSP_SPI_FRAME_BTL_BLOCKERR_PARTIAL;
    }

    retVal = xmodem_parsePacket(&(buffer->data.btlMessage.payload.xmodemPacket),
                                &response);

    // Store XMODEM response as an interrupt for later
    interrupt.messageBuffer[0] = response;
    if (response == XMODEM_CMD_ACK) {
      // Add the packet number
      interrupt.messageBuffer[1] = xmodem_getLastPacketNumber();
      interrupt.messageBuffer[2] = 0;
      interrupt.messageLength = 3;
    } else {
      interrupt.messageLength = 1;
    }
    interruptPending = true;

    switch (retVal) {
      case BOOTLOADER_OK:
        transferActive = true;
        transferPolls = 0;
        // Push data through GBL parser and flash
        retVal = parser_parse(&parserContext,
                              &imageProps,
                              buffer->data.btlMessage.payload.xmodemPacket.data,
                              XMODEM_DATA_SIZE,
                              &parseCb);
        if ((retVal != BOOTLOADER_OK) && !imageProps.imageCompleted) {
          // Error condition! Break off transfer
          return EZSP_SPI_FRAME_BTL_FILEABORT;
        } else if (imageProps.imageCompleted && !imageProps.imageVerified) {
          // Error condition! Break off transfer
          return EZSP_SPI_FRAME_BTL_FILEABORT;
        } else {
          return EZSP_SPI_FRAME_BTL_BLOCKOK;
        }

      case BOOTLOADER_ERROR_XMODEM_CRCL:
        return EZSP_SPI_FRAME_BTL_BLOCKERR_CRCL;

      case BOOTLOADER_ERROR_XMODEM_CRCH:
        return EZSP_SPI_FRAME_BTL_BLOCKERR_CRCH;

      case BOOTLOADER_ERROR_XMODEM_PKTNUM:
        return EZSP_SPI_FRAME_BTL_BLOCKERR_CHK;

      case BOOTLOADER_ERROR_XMODEM_PKTDUP:
        return EZSP_SPI_FRAME_BTL_BLOCKERR_DUP;

      case BOOTLOADER_ERROR_XMODEM_PKTSEQ:
        return EZSP_SPI_FRAME_BTL_BLOCKERR_SEQUENCE;

      case BOOTLOADER_ERROR_XMODEM_DONE:
        // XMODEM transfer complete, but we didn't receive a complete/valid GBL file
        if (!imageProps.imageCompleted || !imageProps.imageVerified) {
          return EZSP_SPI_FRAME_BTL_FILEABORT;
        }

#if defined(SEMAILBOX_PRESENT) || defined(CRYPTOACC_PRESENT)
        // SE upgrade with upgrade version < running version. Abort the transfer.
        if (imageProps.contents & BTL_IMAGE_CONTENT_SE) {
          if (!bootload_checkSeUpgradeVersion(imageProps.seUpgradeVersion)) {
            return EZSP_SPI_FRAME_BTL_FILEABORT;
          }
        }
#endif

        done = true;
        // EZSP-SPI expects packet number + 1 on ACK'ing the EOT command
        interrupt.messageBuffer[1] = xmodem_getLastPacketNumber() + 1;
        return EZSP_SPI_FRAME_BTL_FILEDONE;

      case BOOTLOADER_ERROR_XMODEM_CANCEL:
        return EZSP_SPI_FRAME_BTL_BLOCKOK;

      case BOOTLOADER_ERROR_XMODEM_NO_SOH:
        return EZSP_SPI_FRAME_BTL_BLOCKERR_SOH;

      default:
        return EZSP_SPI_FRAME_BTL_FILEABORT;
    }
  }
}

// Updates the reply buffer with the given error message
static void ezspSpi_error(uint8_t error)
{
  if (!errorPending) {
    reply.messageBuffer[0] = error;
    reply.messageBuffer[1] = 0;
    reply.messageBuffer[2] = EZSP_SPI_FRAME_TERMINATOR;
    reply.messageLength = 3;

    errorPending = true;
  }
}

// Checks the WAKE line and performs handshake if needed
static void ezspSpi_wakeHandshake(void)
{
  unsigned int hostIntState = GPIO_PinOutGet(SL_EZSPSPI_HOST_INT_PORT,
                                             SL_EZSPSPI_HOST_INT_PIN);

  if (hostIntState == 0) {
    // AN711 10: A wake handshake cannot be performed if nHOST_INT is already
    // asserted.
    return;
  }

  // check for wake up sequence
  if (GPIO_PinInGet(SL_EZSPSPI_WAKE_INT_PORT, SL_EZSPSPI_WAKE_INT_PIN) == 0) {
    // This is a handshake. Assert nHOST_INT until WAKE deasserts
    nHOST_ASSERT();
    while (GPIO_PinInGet(SL_EZSPSPI_WAKE_INT_PORT, SL_EZSPSPI_WAKE_INT_PIN)
           == 0) ;
    delay_microseconds(20);
    nHOST_DEASSERT();
    delay_microseconds(50);
  }
}
