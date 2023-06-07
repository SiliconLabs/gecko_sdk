/***************************************************************************//**
 * @file
 * @brief Silicon Labs Primary Secure Engine mailbox over CPC
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "sl_cpc.h"
#include "sl_se_cpc_primary.h"
#include "sli_se_cpc.h"

// -----------------------------------------------------------------------------
// Macros

#define VALIDATE_CPC_BUFFER_USAGE(buffer_index)   \
  if (!validate_cpc_buffer_usage(buffer_index)) { \
    return SL_STATUS_COMMAND_TOO_LONG;            \
  }

#if !defined(CPC_TX_PAYLOAD_MAX_LENGTH)
  #define CPC_TX_PAYLOAD_MAX_LENGTH (256u)
#endif
#if !defined(SE_CPC_TRANSMIT_WINDOW)
  #define SE_CPC_TRANSMIT_WINDOW 1
#endif

// -----------------------------------------------------------------------------
// Static variables

static cpc_endpoint_t se_endpoint;
static uint8_t cpc_tx_data[CPC_TX_PAYLOAD_MAX_LENGTH] = { 0u };
static uint8_t cpc_rx_data[SL_CPC_READ_MINIMUM_SIZE] = { 0u };

// -----------------------------------------------------------------------------
// Static function declarations

static bool validate_cpc_buffer_usage(size_t buffer_index);
static sl_status_t serialize_request(sl_se_command_context_t *cmd_ctx,
                                     size_t *command_request_length);

// -----------------------------------------------------------------------------
// Static functions

/*******************************************************************************
 * @brief
 *   Validate the CPC buffer usage to make sure that it does not overflow.
 ******************************************************************************/
static bool validate_cpc_buffer_usage(size_t buffer_index)
{
  if (buffer_index >= CPC_TX_PAYLOAD_MAX_LENGTH) {
    return false;
  }
  return true;
}

/*******************************************************************************
 * @brief
 *   Serialised SE command request.
 *
 * @param[in] cmd_ctx
 *   Pointer to a filled-out SE command structure.
 *
 * @param[out] command_request_length
 *   Length of the command requested.
 ******************************************************************************/
static sl_status_t serialize_request(sl_se_command_context_t *cmd_ctx,
                                     size_t *command_request_length)
{
  // The serialised command request adhere the following format
  // 1. Command type   (1 byte)
  // 2. SE command     (4 bytes)
  // 3. Num parameters (1 byte)
  // 4. Parameters     (4 * num parameters)
  // 5. Num inputs     (1 byte)
  // 6. Input lengths  (4 * num inputs)
  // 7. Num outputs    (1 byte)
  // 8. Output lengths (4 * num outputs)
  // 9. Input data     (sum(input_lengths))

  size_t current_command_size = 0u; // Current command size in bytes

  // Command type
  cpc_tx_data[current_command_size] = SLI_CMD_EXECUTE_SE_COMMAND;
  current_command_size += SLI_REQUEST_COMMAND_TYPE_SIZE;

  // SE command word
  memcpy(&cpc_tx_data[current_command_size],
         &cmd_ctx->command.command,
         SLI_REQUEST_COMMAND_SIZE);
  current_command_size += SLI_REQUEST_COMMAND_SIZE;

  // Num parameters
  uint8_t num_params = (uint8_t)cmd_ctx->command.num_parameters;
  cpc_tx_data[current_command_size] = num_params;
  current_command_size += SLI_REQUEST_NUM_PARAMS_SIZE;

  // Parameters
  VALIDATE_CPC_BUFFER_USAGE(current_command_size + (SLI_REQUEST_PARAMS_ELEMENT_SIZE * num_params));
  memcpy(&cpc_tx_data[current_command_size],
         cmd_ctx->command.parameters,
         SLI_REQUEST_PARAMS_ELEMENT_SIZE * num_params);
  current_command_size += (SLI_REQUEST_PARAMS_ELEMENT_SIZE * num_params);

  // Input number and lengths
  VALIDATE_CPC_BUFFER_USAGE(current_command_size + SLI_REQUEST_NUM_INPUTS_SIZE);
  size_t num_input_index = current_command_size;
  current_command_size += SLI_REQUEST_NUM_INPUTS_SIZE;
  cpc_tx_data[num_input_index] = 0u;
  if (cmd_ctx->command.data_in != NULL) {
    SE_DataTransfer_t *current_data = cmd_ctx->command.data_in;
    do {
      cpc_tx_data[num_input_index]++;
      VALIDATE_CPC_BUFFER_USAGE(current_command_size + SLI_REQUEST_INPUT_LENGTHS_ELEMENT_SIZE);
      size_t input_data_len = current_data->length;
      memcpy(&cpc_tx_data[current_command_size],
             (uint32_t *)&input_data_len,
             SLI_REQUEST_INPUT_LENGTHS_ELEMENT_SIZE);
      current_command_size += SLI_REQUEST_INPUT_LENGTHS_ELEMENT_SIZE;
      current_data = current_data->next;
    } while (current_data != (void *)SE_DATATRANSFER_STOP);
  }

  // Output number and lengths
  VALIDATE_CPC_BUFFER_USAGE(current_command_size + SLI_REQUEST_NUM_OUTPUTS_SIZE);
  size_t num_output_index = current_command_size;
  current_command_size += SLI_REQUEST_NUM_OUTPUTS_SIZE;
  cpc_tx_data[num_output_index] = 0u;
  if (cmd_ctx->command.data_out != NULL) {
    SE_DataTransfer_t *current_data = cmd_ctx->command.data_out;
    do {
      cpc_tx_data[num_output_index]++;
      VALIDATE_CPC_BUFFER_USAGE(current_command_size + SLI_REQUEST_OUTPUT_LENGTHS_ELEMENT_SIZE);
      size_t output_data_len = current_data->length;
      memcpy(&cpc_tx_data[current_command_size],
             (uint32_t *)&output_data_len,
             SLI_REQUEST_OUTPUT_LENGTHS_ELEMENT_SIZE);
      current_command_size += SLI_REQUEST_OUTPUT_LENGTHS_ELEMENT_SIZE;
      current_data = current_data->next;
    } while (current_data != (void *)SE_DATATRANSFER_STOP);
  }

  // Input Data
  size_t number_of_inputs = cpc_tx_data[num_input_index];
  SE_DataTransfer_t *current_data = cmd_ctx->command.data_in;
  for (size_t i = 0u; i < number_of_inputs; i++) {
    size_t input_data_len = (current_data->length & SE_DATATRANSFER_LENGTH_MASK);
    VALIDATE_CPC_BUFFER_USAGE(current_command_size + input_data_len);
    memcpy(&cpc_tx_data[current_command_size],
           (void *)current_data->data,
           input_data_len);
    current_data = current_data->next;
    current_command_size += input_data_len;
  }
  *command_request_length = current_command_size;

  return SL_STATUS_OK;
}

/*******************************************************************************
 * @brief
 *   Parse the SE command response.
 *
 * @param[in] cmd_ctx
 *   Pointer to a filled-out SE command structure.
 ******************************************************************************/
static sl_status_t parse_response(sl_se_command_context_t *cmd_ctx)
{
  // The serialised command response adhere the following format
  // 1. Command type        (1 byte)
  // 2. SE command          (4 bytes)
  // 3. SE command response (4 bytes)
  // 4. Num outputs         (1 byte)
  // 5. Output length       (4 * num outputs)
  // 6. Output data         (sum(output_lengths))
  // If the command response is success everything is returned in the response,
  // however, upon any failure the response 4,5, and 6 will not be included

  sl_status_t status = SL_STATUS_FAIL;
  // Command type
  uint8_t type = cpc_rx_data[SLI_REQUEST_COMMAND_TYPE_OFFSET];
  if (type != SLI_CMD_EXECUTE_SE_COMMAND) {
    return SL_STATUS_COMMAND_IS_INVALID;
  }

  // SE command
  uint32_t command_word = *(uint32_t *)&cpc_rx_data[SLI_REQUEST_COMMAND_OFFSET];
  if (command_word != cmd_ctx->command.command) {
    return SL_STATUS_COMMAND_IS_INVALID;
  }

  // SE command response
  status = *(uint32_t *)&cpc_rx_data[SLI_RESPONSE_COMMAND_RESPONSE_OFFSET];
  if (status != SL_STATUS_OK) {
    return status;
  }

  uint8_t num_outputs = cpc_rx_data[SLI_RESPONSE_NUM_OUTPUTS_OFFSET];
  uint32_t *output_lengths = (uint32_t *)&cpc_rx_data[SLI_RESPONSE_OUTPUT_LENGTHS_OFFSET];

  SE_DataTransfer_t *current_data_output = cmd_ctx->command.data_out;
  size_t output_data_index = (SLI_RESPONSE_COMMAND_TYPE_SIZE
                              + SLI_RESPONSE_COMMAND_SIZE
                              + SLI_RESPONSE_COMMAND_RESPONSE_SIZE
                              + SLI_RESPONSE_NUM_OUTPUTS_SIZE
                              + (SLI_RESPONSE_OUTPUT_LENGTHS_ELEMENT_SIZE * num_outputs));
  for (size_t i = 0u; i < num_outputs; i++) {
    size_t output_data_len = (output_lengths[i] & SE_DATATRANSFER_LENGTH_MASK);
    if (current_data_output->data != NULL) {
      memcpy((void *)current_data_output->data,
             &cpc_rx_data[output_data_index],
             output_data_len);
    }
    current_data_output = current_data_output->next;
    output_data_index += output_data_len;
  }

  return status;
}

// -----------------------------------------------------------------------------
// Public functions

int sl_cpc_se_init(cpc_handle_t *lib_handle)
{
  return cpc_open_endpoint(*lib_handle,
                           &se_endpoint,
                           SL_CPC_ENDPOINT_SE,
                           SE_CPC_TRANSMIT_WINDOW);
}

sl_status_t sli_se_execute_and_wait(sl_se_command_context_t *cmd_ctx)
{
  ssize_t size;
  size_t command_request_length = 0u; // Current command size in bytes
  sl_status_t status = SL_STATUS_FAIL;
  memset(cpc_tx_data, 0u, CPC_TX_PAYLOAD_MAX_LENGTH); // Always start by resetting the CPC TX buffer
  status = serialize_request(cmd_ctx, &command_request_length);
  if (status != SL_STATUS_OK) {
    return status;
  }

  size = cpc_write_endpoint(se_endpoint,
                            cpc_tx_data,
                            command_request_length,
                            CPC_ENDPOINT_WRITE_FLAG_NONE);
  if (size != command_request_length) {
    return SL_STATUS_FAIL;
  }

  size = cpc_read_endpoint(se_endpoint,
                           cpc_rx_data,
                           sizeof(cpc_rx_data),
                           CPC_ENDPOINT_READ_FLAG_NONE);
  if (size < 0u) {
    return SL_STATUS_FAIL;
  }

  return parse_response(cmd_ctx);
}
