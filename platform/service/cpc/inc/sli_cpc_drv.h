/***************************************************************************/ /**
 * @file
 * @brief CPC Driver Interface
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef SLI_CPC_DRV_H
#define SLI_CPC_DRV_H

#include "sli_cpc.h"
#include "sl_status.h"
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

#define SLI_CPC_RX_FRAME_MAX_LENGTH ((uint16_t)(SLI_CPC_RX_DATA_MAX_LENGTH + SLI_CPC_HDLC_HEADER_RAW_SIZE))

typedef struct {
  bool use_raw_rx_buffer;                 ///< Does the driver use raw RX buffers
  bool preprocess_hdlc_header;            ///< Is the HDLC header validated by driver
  bool uart_flowcontrol;                  ///< Is UART flow control enabled
} sli_cpc_drv_capabilities_t;

#ifdef __cplusplus
extern "C"
{
#endif

// -----------------------------------------------------------------------------
// Core to driver commands

/***************************************************************************//**
 * Initialize only the hardware peripheral to be used in a standalone manner
 * (during the bootloader poking)
 ******************************************************************************/
sl_status_t sli_cpc_drv_hw_init(void);

/***************************************************************************//**
 * Initialize the rest of the driver after the hardware peripheral has been
 * initialized in sli_cpc_drv_hw_init.
 *
 * @return SL_STATUS_OK if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sli_cpc_drv_init(void);

/***************************************************************************//**
 * Start recveiving packets
 *
 * @return SL_STATUS_OK if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sli_cpc_drv_start_rx(void);

/***************************************************************************//**
 * De-Initializes CPC driver for the firmware upgrade to take over control.
 ******************************************************************************/
void sli_cpc_drv_deinit_for_firmware_upgrade(void);

/***************************************************************************//**
 * Gets CPC driver capabilities.
 *
 * @param capabilities Pointer to structure that will receive the driver
 *                     capabilities.
 *  @return SL_STATUS_OK if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sli_cpc_drv_get_capabilities(sli_cpc_drv_capabilities_t *capabilities);

/***************************************************************************//**
 * Reads data from driver.
 *
 * @param buffer_handle Pointer to variable that will receive receive the buffer handle.
 *
 * @param payload_rx_len Pointer to variable that will receive the received
 *                       payload length, in bytes.
 *
 * @return SL_STATUS_OK if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sli_cpc_drv_read_data(sl_cpc_buffer_handle_t **buffer_handle);

/***************************************************************************//**
 * Checks if driver is ready to transmit.
 *
 * @return true if driver is ready to accept a tx. false otherwise.
 ******************************************************************************/
bool sli_cpc_drv_is_transmit_ready(void);

/***************************************************************************//**
 * Transmits data.
 *
 * @param buffer_handle Pointer to the buffer handle.
 *
 * @return SL_STATUS_OK if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sli_cpc_drv_transmit_data(sl_cpc_buffer_handle_t *buffer_handle);

/***************************************************************************//**
 * Get currently configured bus bitrate
 ******************************************************************************/
uint32_t sli_cpc_drv_get_bus_bitrate(void);

/***************************************************************************//**
 * Set bus bitrate
 ******************************************************************************/
void sli_cpc_drv_set_bus_bitrate(uint32_t bus_bitrate);

/***************************************************************************//**
 * Get maximum bus bitrate
 ******************************************************************************/
uint32_t sli_cpc_drv_get_bus_max_bitrate(void);

/***************************************************************************//**
 * Notification on freed RX buffer_handle
 ******************************************************************************/
SL_WEAK void sli_cpc_drv_on_rx_buffer_handle_free(void);

/***************************************************************************//**
 * Notification on freed RX buffer
 ******************************************************************************/
SL_WEAK void sli_cpc_drv_on_rx_buffer_free(void);

/** @} (end addtogroup cpc) */

#ifdef __cplusplus
}
#endif

#endif // SLI_CPC_DRV_H
