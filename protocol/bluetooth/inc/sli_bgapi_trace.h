/***************************************************************************//**
 * @file
 * @brief Functions used by the BGAPI protocol to output BGAPI trace over RTT
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SLI_BGAPI_TRACE_H
#define SLI_BGAPI_TRACE_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup sl_bgapi_trace
 * @{
 *
 * @brief BGAPI trace utility for tracing BGAPI commands and events
 *
 * The functions provided by this component are automatically called by the
 * BGAPI protocol implementation when a command is processed or an event is
 * delivered to the application. The application does not need to and must not
 * call these functions directly.
 *
 ******************************************************************************/

/**
 * @brief Specifies the full type of a BGAPI message.
 */
typedef enum {
  sli_bgapi_trace_message_type_command  = 0x0, /**< (0x0) The message is a BGAPI command */
  sli_bgapi_trace_message_type_response = 0x1, /**< (0x1) The message is a BGAPI response */
  sli_bgapi_trace_message_type_event    = 0x2  /**< (0x2) The message is a BGAPI event */
} sli_bgapi_trace_message_type_t;

/***************************************************************************//**
 * Initialize BGAPI tracing.
 ******************************************************************************/
void sli_bgapi_trace_init(void);

/***************************************************************************//**
 * Output a BGAPI message to the trace channel.
 *
 * @param[in]  type    The BGAPI message type
 * @param[in]  header  The BGAPI message header
 * @param[in]  data    The BGAPI message payload data
 ******************************************************************************/
void sli_bgapi_trace_output_message(sli_bgapi_trace_message_type_t type,
                                    uint32_t header,
                                    const void *data);

/** @} end sl_bgapi_trace */

#ifdef __cplusplus
}
#endif

#endif // SLI_BGAPI_TRACE_H
