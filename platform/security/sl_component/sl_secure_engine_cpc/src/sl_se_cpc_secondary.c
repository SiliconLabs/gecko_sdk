/***************************************************************************//**
 * @file
 * @brief Silicon Labs Secondary Secure Engine mailbox over CPC
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

#include <stdlib.h>
#include <string.h>
#include "em_device.h"
#include "sli_se_cpc.h"
#include "sl_se_cpc_secondary.h"
#include "sl_se_manager.h"
#include "sli_se_manager_internal.h"

// -----------------------------------------------------------------------------
// Macros

#define SE_DATATRANSFER_PREPARE(datatransfer_struct, address, data_length)    \
  {                                                                           \
    datatransfer_struct.data = (void*)(address);                              \
    datatransfer_struct.next = (void*)SE_DATATRANSFER_STOP;                   \
    datatransfer_struct.length = data_length; /* includes transfer type bit*/ \
  }

// -----------------------------------------------------------------------------
// Typedefs

typedef struct {
  uint32_t    requested_command;   // Requested SE command
  sl_status_t se_command_response; // SE command response
  uint8_t     num_outputs;         // Number of outputs
  uint16_t    reserved;
  uint32_t    *output_lengths;     // Length of the outputs
} command_metadata_t;

// -----------------------------------------------------------------------------
// Static function declarations

static sl_status_t get_output_buffer(uint8_t  num_outputs,
                                     uint32_t output_lengths[],
                                     uint8_t  *response_buffer,
                                     size_t   response_buffer_size,
                                     size_t   *response_size,
                                     uint8_t  **output_data);
static void parse_execute_request(const uint8_t      *raw_command,
                                  size_t             raw_command_size,
                                  uint8_t            *response_buffer,
                                  size_t             response_buffer_size,
                                  size_t             *command_response_size,
                                  command_metadata_t *request_metadata);
static void serialize_response(command_metadata_t *response_metadata,
                               uint8_t            *command_response,
                               size_t             *command_response_size);

// -----------------------------------------------------------------------------
// Static functions

/*******************************************************************************
 * @brief
 *   Get pointer of the buffer to store the SE command output. Also, calculate
 *   the SE command response size.
 ******************************************************************************/
static sl_status_t get_output_buffer(uint8_t  num_outputs,
                                     uint32_t output_lengths[],
                                     uint8_t  *response_buffer,
                                     size_t   response_buffer_size,
                                     size_t   *response_size,
                                     uint8_t  **output_data)
{
  size_t output_size = 0u;
  for (size_t i = 0u; i < num_outputs; i++) {
    output_size += (output_lengths[i] & SE_DATATRANSFER_LENGTH_MASK);
  }
  size_t output_data_offset = SLI_RESPONSE_OUTPUT_LENGTHS_OFFSET
                              + (SLI_REQUEST_OUTPUT_LENGTHS_ELEMENT_SIZE * num_outputs);
  size_t expected_size = output_data_offset + output_size;

  // Validate the response buffer size. This is required since
  // we want to store the output data in the response buffer.
  if (response_buffer_size < expected_size) {
    return SL_STATUS_COMMAND_TOO_LONG;
  }
  *response_size = expected_size;
  *output_data = &response_buffer[output_data_offset];
  return SL_STATUS_OK;
}

/*******************************************************************************
 * @brief
 *   Parse and execute serialised SE command request.
 *
 * @param[in] command_request
 *   A buffer holding the serialised SE command.
 *
 * @param[in] command_request_size
 *   Size of the serialised SE command.
 *
 * @param[out] command_response
 *   A buffer to store the SE command response.
 *
 * @param[in] command_response_buffer_size
 *   Size of the buffer to store the SE command response.
 *
 * @param[in] command_response_size
 *   Size of the actual SE command response.
 *
 * @param[out] request_metadata
 *   Struct holding the SE command request metadata.
 ******************************************************************************/
static void parse_execute_request(const uint8_t      *command_request,
                                  size_t             command_request_size,
                                  uint8_t            *command_response,
                                  size_t             command_response_buffer_size,
                                  size_t             *command_response_size,
                                  command_metadata_t *request_metadata)
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

  sl_status_t status = SL_STATUS_FAIL;
  sl_se_command_context_t se_command;
  size_t parsed_command_size = 0u; // parsed command size in bytes

  // Command type
  uint8_t type = command_request[parsed_command_size];
  parsed_command_size += SLI_REQUEST_COMMAND_TYPE_SIZE;

  if (type != SLI_CMD_EXECUTE_SE_COMMAND) {
    request_metadata->se_command_response = SL_STATUS_COMMAND_IS_INVALID;
    return;
  }

  // SE command word
  uint32_t command_word = *(uint32_t *)&command_request[parsed_command_size];
  parsed_command_size += SLI_REQUEST_COMMAND_SIZE;
  request_metadata->requested_command = command_word;

  // Num parameters
  uint8_t num_params = command_request[parsed_command_size];
  parsed_command_size += SLI_REQUEST_NUM_PARAMS_SIZE;

  // Parameters
  uint32_t *parameters = (uint32_t *)&command_request[parsed_command_size];
  parsed_command_size += (SLI_REQUEST_PARAMS_ELEMENT_SIZE * num_params);

  // Num inputs
  uint8_t num_inputs = command_request[parsed_command_size];
  parsed_command_size += SLI_REQUEST_NUM_INPUTS_SIZE;

  // Input lengths
  uint32_t *input_lengths = (uint32_t *)&command_request[parsed_command_size];
  parsed_command_size += (SLI_REQUEST_INPUT_LENGTHS_ELEMENT_SIZE * num_inputs);

  // Num outputs
  request_metadata->num_outputs = command_request[parsed_command_size];
  parsed_command_size += SLI_REQUEST_NUM_OUTPUTS_SIZE;

  // Output lengths
  request_metadata->output_lengths = (uint32_t *)&command_request[parsed_command_size];
  parsed_command_size += (SLI_REQUEST_OUTPUT_LENGTHS_ELEMENT_SIZE * request_metadata->num_outputs);

  // Input data
  const uint8_t *input_data = &command_request[parsed_command_size];

  // Validate the command request length
  size_t input_size = 0u;
  for (size_t i = 0u; i < num_inputs; i++) {
    input_size += (input_lengths[i] & SE_DATATRANSFER_LENGTH_MASK);
  }
  parsed_command_size += input_size;
  if (command_request_size != parsed_command_size) {
    request_metadata->se_command_response = SL_STATUS_INVALID_PARAMETER;
    return;
  }

  // Get output data buffer
  uint8_t *output_data = NULL;
  status = get_output_buffer(request_metadata->num_outputs,
                             request_metadata->output_lengths,
                             command_response,
                             command_response_buffer_size,
                             command_response_size,
                             &output_data);
  if (status != SL_STATUS_OK) {
    request_metadata->se_command_response = status;
    return;
  }

  // Prepare SE command struct
  se_command.command.command = command_word;
  se_command.command.data_in = NULL;
  se_command.command.data_out = NULL;
  se_command.command.num_parameters = 0;

  // Prepare parameters
  for (size_t i = 0u; i < num_params; i++) {
    SE_addParameter(&se_command.command, parameters[i]);
  }

  // Prepare input linked list
  SE_DataTransfer_t *se_command_input = (SE_DataTransfer_t *)malloc(num_inputs * sizeof(SE_DataTransfer_t));
  if (se_command_input == NULL) {
    request_metadata->se_command_response = SL_STATUS_ALLOCATION_FAILED;
    return;
  }
  uint8_t *input_data_moving_pointer = (uint8_t *)input_data;
  for (size_t i = 0u; i < num_inputs; i++) {
    SE_DATATRANSFER_PREPARE(se_command_input[i],
                            input_data_moving_pointer,
                            input_lengths[i]);
    SE_addDataInput(&se_command.command, &se_command_input[i]);
    input_data_moving_pointer += (input_lengths[i] & SE_DATATRANSFER_LENGTH_MASK);
  }

  // Prepare output linked list
  SE_DataTransfer_t *se_command_output = (SE_DataTransfer_t *)malloc(request_metadata->num_outputs * sizeof(SE_DataTransfer_t));
  if (se_command_output == NULL) {
    free(se_command_input);
    request_metadata->se_command_response = SL_STATUS_ALLOCATION_FAILED;
    return;
  }

  uint8_t *output_data_moving_pointer = (uint8_t *)output_data;
  for (size_t i = 0u; i < request_metadata->num_outputs; i++) {
    SE_DATATRANSFER_PREPARE(se_command_output[i],
                            output_data_moving_pointer,
                            request_metadata->output_lengths[i]);
    SE_addDataOutput(&se_command.command, &se_command_output[i]);
    output_data_moving_pointer += (request_metadata->output_lengths[i] & SE_DATATRANSFER_LENGTH_MASK);
  }

  sl_se_init();
  request_metadata->se_command_response = sli_se_execute_and_wait(&se_command);
  free(se_command_input);
  free(se_command_output);
}

/*******************************************************************************
 * @brief
 *   Serialise SE command response.
 *
 * @param[in] response_metadata
 *   Struct holding the SE command response metadata.
 *
 * @param[in] command_response
 *   A buffer holding the serialised SE command response.
 *
 * @param[out] command_response_size
 *   Size of the SE command response.
 ******************************************************************************/
static void serialize_response(command_metadata_t *response_metadata,
                               uint8_t            *command_response,
                               size_t             *command_response_size)
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

  // Command type
  command_response[SLI_RESPONSE_COMMAND_TYPE_OFFSET] = SLI_CMD_EXECUTE_SE_COMMAND;
  // SE command
  memcpy(&command_response[SLI_RESPONSE_COMMAND_OFFSET],
         &response_metadata->requested_command,
         SLI_RESPONSE_COMMAND_SIZE);
  // SE command response
  memcpy(&command_response[SLI_RESPONSE_COMMAND_RESPONSE_OFFSET],
         &response_metadata->se_command_response,
         SLI_RESPONSE_COMMAND_RESPONSE_SIZE);

  if (response_metadata->se_command_response == SL_STATUS_OK) {
    // Num outputs
    command_response[SLI_RESPONSE_NUM_OUTPUTS_OFFSET] = response_metadata->num_outputs;
    // Output lengths
    memcpy(&command_response[SLI_RESPONSE_OUTPUT_LENGTHS_OFFSET],
           response_metadata->output_lengths,
           SLI_RESPONSE_OUTPUT_LENGTHS_ELEMENT_SIZE * response_metadata->num_outputs);
    // The output data is already processed.
  } else {
    // If we get an error, update the response size to discard output
    *command_response_size =  SLI_RESPONSE_COMMAND_RESPONSE_OFFSET
                             + SLI_RESPONSE_COMMAND_RESPONSE_SIZE;
  }
}

// -----------------------------------------------------------------------------
// Public functions

sl_status_t sl_cpc_se_execute_command(const uint8_t *command_request,
                                      size_t        command_request_size,
                                      uint8_t       *command_response,
                                      size_t        command_response_buffer_size,
                                      size_t        *command_response_size)
{
  command_metadata_t request_metadata = { 0 };
  parse_execute_request(command_request,
                        command_request_size,
                        command_response,
                        command_response_buffer_size,
                        command_response_size,
                        &request_metadata);
  serialize_response(&request_metadata,
                     command_response,
                     command_response_size);
  return SL_STATUS_OK;
}
