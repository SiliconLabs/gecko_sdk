 /***************************************************************************//**
 * @file CC_Configuration.c
 * @brief CC_Configuration.c
 * @copyright 2020 Silicon Laboratories Inc.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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
// -----------------------------------------------------------------------------
//                   Includes
// -----------------------------------------------------------------------------
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <CC_Configuration.h>
#include <ZW_TransportEndpoint.h>
#include <ZAF_Common_interface.h>
#include <stddef.h>
#include <cc_configuration_config_api.h>
#include <cc_configuration_io.h>
#include "zaf_transport_tx.h"

//#define DEBUGPRINT
#include "DebugPrint.h"

// -----------------------------------------------------------------------------
//                Macros and Typedefs
// -----------------------------------------------------------------------------
#define SLI_CC_CONFIGURATION_MAX_STR_LENGTH (256)
#define DEFAULT_FLAG (0x80)
#define HANDSHAKE_FLAG (0x40)
// -----------------------------------------------------------------------------
//              Static Function Declarations
// -----------------------------------------------------------------------------

/**
 * Handler for Configuration CC set command
 * @param[in] pRxOpt Receive options.
 * @param[in] pCmd Payload including command class.
 * @param[in] cmdLength Length of the received command.
 * @return Result of command parsing.
*/
static received_frame_status_t
cc_configuration_command_set(  RECEIVE_OPTIONS_TYPE_EX const * pRxOpt,
                                  ZW_APPLICATION_TX_BUFFER const * pCmd,
                                  const uint8_t cmdLength);

/**
 * Handler for Configuration CC get command
 * @param[in] pRxOpt Receive options.
 * @param[in] pCmd Payload including command class.
 * @param[in] cmdLength Length of the received command.
 * @return Result of command parsing.
*/
static received_frame_status_t
cc_configuration_command_get(  RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                  ZW_APPLICATION_TX_BUFFER const * pCmd,
                                  const uint8_t cmdLength);

/**
 * Handler for Configuration CC get info command
 * @param[in] pRxOpt Receive options.
 * @param[in] pCmd Payload including command class.
 * @param[in] cmdLength Length of the received command.
 * @return Result of command parsing.
*/
static received_frame_status_t
cc_configuration_command_info( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                  ZW_APPLICATION_TX_BUFFER const * pCmd,
                                  const uint8_t cmdLength);

/**
 * Handler for Configuration CC get name command
 * @param[in] pRxOpt Receive options.
 * @param[in] pCmd Payload including command class.
 * @param[in] cmdLength Length of the received command.
 * @return Result of command parsing.
*/
static received_frame_status_t
cc_configuration_command_name_get( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                      ZW_APPLICATION_TX_BUFFER const * pCmd,
                                      const uint8_t cmdLength);

/**
 * Handler for Configuration CC get property
 * @param[in] pRxOpt Receive options.
 * @param[in] pCmd Payload including command class.
 * @param[in] cmdLength Length of the received command.
 * @return Result of command parsing.
*/
static received_frame_status_t
cc_configuration_command_properties_get( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                            ZW_APPLICATION_TX_BUFFER const * pCmd,
                                            const uint8_t cmdLength);

/**
 * Handler for Configuration CC get bulk
 * @param[in] pRxOpt Receive options.
 * @param[in] pCmd Payload including command class.
 * @param[in] cmdLength Length of the received command.
 * @return Result of command parsing.
*/
static received_frame_status_t
cc_configuration_command_bulk_get( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                      ZW_APPLICATION_TX_BUFFER const * pCmd,
                                      const uint8_t cmdLength);

/**
 * Handler for Configuration CC set bulk
 * @param[in] pRxOpt Receive options.
 * @param[in] pCmd Payload including command class.
 * @param[in] cmdLength Length of the received command.
 * @return Result of command parsing.
*/
static received_frame_status_t
cc_configuration_command_bulk_set( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                      ZW_APPLICATION_TX_BUFFER const * pCmd,
                                      const uint8_t cmdLength);

/**
 * Handler for sending bulk report response
 * @param[in] pRxOpt Receive options.
 * @param[in] parameter_offset offset from the first parameter's number
 * @param[in] stop number where the bulk report should end
 * @param[in] flag_handshake if true the function call is a result of handshake request
 * @return Result of command parsing.
*/
static received_frame_status_t
cc_configuration_command_send_bulk_report( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                              const uint16_t parameter_offset,
                                              const uint16_t stop_number,
                                              const bool flag_handshake);

/**
 * Handler for resetting to the default state
 * @param[in] pRxOpt Receive options.
 * @param[in] pCmd Payload including command class.
 * @param[in] cmdLength Length of the received command.
 * @return Result of command parsing.
*/
static received_frame_status_t
cc_configuration_command_default_reset( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                           ZW_APPLICATION_TX_BUFFER const * pCmd,
                                           const uint8_t cmdLength);

/**
 * Copy value to raw frame
 * @param[out] pFrame the raw frame where the data will be copied to
 * @param[in] parameter_buffer reference to the parameter
 * @param[in] pField which will be copied from
 * @return Result of the conversion which is a recevived_frame_status_t type
*/
static void
cc_configuration_copyToFrame(  cc_config_parameter_value_t* pFrame,
                                  const cc_config_parameter_buffer_t* parameter_buffer,
                                  const cc_config_parameter_value_t* pField);

/**
 * Resets a configuration value back to default value
 * @param[in] parameter_number configuration's number to reset
 * @return Result of the reset true in case of success, else false
*/
static bool
cc_configuration_reset_to_default_value(uint16_t parameter_number);

/**
 * Sets a configuration's value to a new one
 * @param[in] parameter_number configuration's number to change
 * @param[in] new_value pointer to a new configuration value
 * @param[in] size size of the new configuration value
 * @return Result of the setting, NOT_SUPPORTED, FAIL, or OK
*/
static cc_config_configuration_set_return_value
cc_configuration_set(uint16_t parameter_number,
                        cc_config_parameter_value_t* new_value,
                        cc_config_parameter_size_t size);

/**
 * Checks if a parameter is between the min and max values, it not it minimize or maximize.
 * This function is for signed integers
 * @param[in] parameter_buffer configuration's parameter which has the limits
 * @param[out] pNewValue the new value to be limited
 * @return Result of the limiting true in case of success, else false
*/
static bool 
cc_configuration_limit_value_signed_int(cc_config_parameter_buffer_t const* parameter_buffer,
                                           cc_config_parameter_value_t * pNewValue);

/**
 * Checks if a parameter is between the min and max values, it not it minimize or maximize.
 * This function is for signed integers
 * @param[in] parameter_buffer configuration's parameter which has the limits
 * @param[out] pNewValue the new value to be limited
 * @return Result of the limiting true in case of success, else false
*/
static bool 
cc_configuration_limit_value_signed_int_8bit(cc_config_parameter_buffer_t const * parameter_buffer,
                                                 cc_config_parameter_value_t * pNewValue);

/**
 * Checks if a parameter is between the min and max values, it not it minimize or maximize.
 * This function is for signed integers
 * @param[in] parameter_buffer configuration's parameter which has the limits
 * @param[out] pNewValue the new value to be limited
 * @return Result of the limiting true in case of success, else false
*/
static bool 
cc_configuration_limit_value_signed_int_16bit(cc_config_parameter_buffer_t const * parameter_buffer,
                                                 cc_config_parameter_value_t * pNewValue);

/**
 * Checks if a parameter is between the min and max values, it not it minimize or maximize.
 * This function is for signed integers
 * @param[in] parameter_buffer configuration's parameter which has the limits
 * @param[out] pNewValue the new value to be limited
 * @return Result of the limiting true in case of success, else false
*/
static bool 
cc_configuration_limit_value_signed_int_32bit(cc_config_parameter_buffer_t const * parameter_buffer,
                                                 cc_config_parameter_value_t * pNewValue);

/**
 * Checks if a parameter is between the min and max values, it not it minimize or maximize.
 * This function is for unsigned integers
 * @param[in] parameter_buffer configuration's parameter which has the limits
 * @param[out] pNewValue the new value to be limited
 * @return Result of the limiting true in case of success, else false
*/
static bool 
cc_configuration_limit_value_unsigned_int(cc_config_parameter_buffer_t const* parameter_buffer,
                                             cc_config_parameter_value_t * pNewValue);

/**
 * Checks if a parameter is between the min and max values, it not it minimize or maximize.
 * This function is for unsigned integers
 * @param[in] parameter_buffer configuration's parameter which has the limits
 * @param[out] pNewValue the new value to be limited
 * @return Result of the limiting true in case of success, else false
*/
static bool 
cc_configuration_limit_value_unsigned_int_8bit(cc_config_parameter_buffer_t const* parameter_buffer,
                                                   cc_config_parameter_value_t * pNewValue);

/**
 * Checks if a parameter is between the min and max values, it not it minimize or maximize.
 * This function is for unsigned integers
 * @param[in] parameter_buffer configuration's parameter which has the limits
 * @param[out] pNewValue the new value to be limited
 * @return Result of the limiting true in case of success, else false
*/
static bool 
cc_configuration_limit_value_unsigned_int_16bit(cc_config_parameter_buffer_t const* parameter_buffer,
                                                   cc_config_parameter_value_t * pNewValue);

/**
 * Checks if a parameter is between the min and max values, it not it minimize or maximize.
 * This function is for unsigned integers
 * @param[in] parameter_buffer configuration's parameter which has the limits
 * @param[out] pNewValue the new value to be limited
 * @return Result of the limiting true in case of success, else false
*/
static bool 
cc_configuration_limit_value_unsigned_int_32bit(cc_config_parameter_buffer_t const* parameter_buffer,
                                                   cc_config_parameter_value_t * pNewValue);
/**
 * Finds the configuration with the lowest number in the pool
 * @param[out] parameter_buffer a pointer to a cc_config_parameter_t pointer to pass back the reference of the first configuration
 * @return Result of the look up true in case of success, else false
*/
static bool
cc_configuration_get_first_parameter(cc_config_parameter_buffer_t* parameter_buffer);


/**
 * Calculates how many more frames are needed to send the whole dara
 * @param[in] data_length  length of the data to be sent
 * @param[in] payload_limit maximum payload length
 * @return number of maximum reports to follow
*/
static uint8_t
cc_configuration_calc_reports_to_follow(size_t data_length, size_t payload_limit);

/**
 * Determine the first parameter number
 *
 * @param[out] parameter_buffer pointer to a parameter buffer which will holds the metadata and current value of a parameter
 * @return same type as cc_configuration_get
 */
static bool
cc_configuration_probe(cc_config_parameter_buffer_t* parameter_buffer);

/**
 * Find the next valid parameter number in case of an invalid  one
 * @param[in] input holds the value of the current (invalid) parameter number
 * @return the next available parameter number, if not exist, the fist available parameter number is given back
 */
static uint16_t
cc_configuration_find_next_valid_parameter_number(uint16_t input);

/**
 * Give back the first available parameter number
 * @return the fist available parameter number is given back
 */
static uint16_t
cc_configuration_get_lowest_parameter_number();

/**
 * Check if the given parameter number is valid
 * @param[in] input holds the value of the current tested parameter number
 * @return true if the parameter number is valid, false anyway
 */
static bool
cc_configuration_check_if_parameter_number_is_valid(uint16_t input);

/**
 * Check, whether the size parameter is valid or not
 * @param[in] size_value the size value that needs to be checked
 * @return true if valid, false anyways
*/
static bool 
cc_configuration_is_valid_size(cc_config_parameter_size_t size_value);

static size_t
cc_configuration_strnlen(const char *str, size_t maxlen);
// -----------------------------------------------------------------------------
//                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                Static Variables
// -----------------------------------------------------------------------------
/**< cc_configuration_t pointer to the meta data of the parameters */
static cc_configuration_t const* configuration_pool;
// -----------------------------------------------------------------------------
//              Public Function Definitions
// -----------------------------------------------------------------------------
static void
init_and_reset()
{
  bool retval = false;
  bool is_migrated = false;
  cc_config_parameter_buffer_t parameter_buffer;
  configuration_pool = cc_configuration_get_configuration();

  for(uint16_t loop_cnt = 0; loop_cnt < configuration_pool->numberOfParameters ; loop_cnt++)
  {
    is_migrated = false;

    parameter_buffer.metadata = &configuration_pool->parameters[loop_cnt];

    retval = cc_configuration_io_read( parameter_buffer.metadata->file_id,
                                        (uint8_t*)&parameter_buffer.data_buffer,
                                          sizeof(cc_config_parameter_value_t));

    if(retval == false)
    {
      /*Parameter is not stored, let's write it*/
      retval = cc_configuration_io_write( parameter_buffer.metadata->file_id,
                                            (const uint8_t*)&configuration_pool->parameters[loop_cnt].attributes.default_value,
                                            sizeof(cc_config_parameter_value_t));
    }
    else if(configuration_pool->parameters[loop_cnt].migration_handler != NULL)
    {
      is_migrated = configuration_pool->parameters[loop_cnt].migration_handler(&parameter_buffer);
    }

    if(is_migrated == true)
    {
      /*Parameter is not stored, let's write it*/
      retval = cc_configuration_io_write( parameter_buffer.metadata->file_id,
                                            (const uint8_t*)&parameter_buffer.data_buffer,
                                            sizeof(cc_config_parameter_value_t));
    }
  }

  ASSERT(retval == true);
}

static void
cc_configuration_copyToFrame(  cc_config_parameter_value_t* pFrame,
                                  const cc_config_parameter_buffer_t* parameter_buffer,
                                  const cc_config_parameter_value_t* pField)
{
  if( (pFrame != NULL)           &&
      (parameter_buffer != NULL) &&
      (pField != NULL))
  {

    if(NULL != parameter_buffer->metadata)
    {
      int8_t src_ix  = (int8_t)parameter_buffer->metadata->attributes.size - 1;
      int8_t dest_ix = 0;

      while((src_ix >= 0) && (dest_ix < (int8_t)sizeof(pFrame->as_uint8_array)))
      {
        pFrame->as_uint8_array[dest_ix] = pField->as_uint8_array[src_ix];
        src_ix--;
        dest_ix++;
      }
    }
  }
}

static received_frame_status_t CC_Configuration_handler(RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                                        ZW_APPLICATION_TX_BUFFER *pCmd,
                                                        uint8_t cmdLength,
                                                        ZW_APPLICATION_TX_BUFFER * pFrameOut,
                                                        uint8_t * pLengthOut)
{
  received_frame_status_t frame_status = RECEIVED_FRAME_STATUS_NO_SUPPORT;
  UNUSED(pFrameOut);
  UNUSED(pLengthOut);

  switch (pCmd->ZW_Common.cmd) {
    case CONFIGURATION_INFO_GET_V4:
      frame_status = cc_configuration_command_info(pRxOpt, pCmd, cmdLength);
      break;
    case CONFIGURATION_GET_V4:
      frame_status = cc_configuration_command_get(pRxOpt, pCmd, cmdLength);
      break;
    case CONFIGURATION_SET_V4:
      frame_status = cc_configuration_command_set(pRxOpt, pCmd, cmdLength);
      break;
    case CONFIGURATION_NAME_GET_V4:
      frame_status = cc_configuration_command_name_get(pRxOpt, pCmd, cmdLength);
      break;
    case CONFIGURATION_PROPERTIES_GET_V4:
      frame_status = cc_configuration_command_properties_get(pRxOpt, pCmd, cmdLength);
      break;
    case CONFIGURATION_BULK_GET_V4:
      frame_status = cc_configuration_command_bulk_get(pRxOpt, pCmd, cmdLength);
      break;
    case CONFIGURATION_BULK_SET_V4:
      frame_status = cc_configuration_command_bulk_set(pRxOpt, pCmd, cmdLength);
      break;
    case CONFIGURATION_DEFAULT_RESET_V4:
      frame_status = cc_configuration_command_default_reset(pRxOpt, pCmd, cmdLength);
      break;
    default:
      break;
  }
  return frame_status;
}

// -----------------------------------------------------------------------------
//              Static Function Definitions
// -----------------------------------------------------------------------------
static bool 
cc_configuration_limit_value_signed_int_8bit(cc_config_parameter_buffer_t const * parameter_buffer,
                                                cc_config_parameter_value_t * pNewValue)
{
  bool return_value = true;

  if( parameter_buffer->metadata->attributes.min_value.as_int8 > pNewValue->as_int8)
  {
    pNewValue->as_int8 = parameter_buffer->metadata->attributes.min_value.as_int8;
    return_value = false;
  }
  else if( parameter_buffer->metadata->attributes.max_value.as_int8 < pNewValue->as_int8)
  {
    pNewValue->as_int8 = parameter_buffer->metadata->attributes.max_value.as_int8;
    return_value = false;
  }

  return return_value;
}

static bool 
cc_configuration_limit_value_signed_int_16bit(cc_config_parameter_buffer_t const * parameter_buffer,
                                                 cc_config_parameter_value_t * pNewValue)
{
  bool return_value = true;

  if( parameter_buffer->metadata->attributes.min_value.as_int16 > pNewValue->as_int16)
  {
    pNewValue->as_int16 = parameter_buffer->metadata->attributes.min_value.as_int16;
    return_value = false;
  }
  else if( parameter_buffer->metadata->attributes.max_value.as_int16 < pNewValue->as_int16)
  {
    pNewValue->as_int16 = parameter_buffer->metadata->attributes.max_value.as_int16;
    return_value = false;
  }

  return return_value;
}

static bool 
cc_configuration_limit_value_signed_int_32bit(cc_config_parameter_buffer_t const * parameter_buffer,
                                                 cc_config_parameter_value_t * pNewValue)
{
  bool return_value = true;

  if( parameter_buffer->metadata->attributes.min_value.as_int32 > pNewValue->as_int32)
  {
    pNewValue->as_int32 = parameter_buffer->metadata->attributes.min_value.as_int32;
    return_value = false;
  }
  else if( parameter_buffer->metadata->attributes.max_value.as_int32 < pNewValue->as_int32)
  {
    pNewValue->as_int32 = parameter_buffer->metadata->attributes.max_value.as_int32;
    return_value = false;
  }

  return return_value;
}

static bool 
cc_configuration_limit_value_signed_int(cc_config_parameter_buffer_t const * parameter_buffer,
                                           cc_config_parameter_value_t * pNewValue)
{
  bool return_value = true;

  switch(parameter_buffer->metadata->attributes.size)
  {
    case CC_CONFIG_PARAMETER_SIZE_8_BIT:
      return_value = cc_configuration_limit_value_signed_int_8bit(parameter_buffer, pNewValue);
      break;
    case CC_CONFIG_PARAMETER_SIZE_16_BIT:
      return_value = cc_configuration_limit_value_signed_int_16bit(parameter_buffer, pNewValue);
      break;
    case CC_CONFIG_PARAMETER_SIZE_32_BIT:
      return_value = cc_configuration_limit_value_signed_int_32bit(parameter_buffer, pNewValue);
      break;
    default:
      break;
  }

  return return_value;
}

static bool 
cc_configuration_limit_value_unsigned_int_8bit(cc_config_parameter_buffer_t const* parameter_buffer,
                                             cc_config_parameter_value_t * pNewValue)
{
  bool return_value = true;

  if( parameter_buffer->metadata->attributes.min_value.as_uint8 > pNewValue->as_uint8)
  {
    pNewValue->as_uint8 = parameter_buffer->metadata->attributes.min_value.as_uint8;
    return_value = false;
  }
  else if( parameter_buffer->metadata->attributes.max_value.as_uint8 < pNewValue->as_uint8)
  {
    pNewValue->as_uint8 = parameter_buffer->metadata->attributes.max_value.as_uint8;
    return_value = false;
  }

  return return_value;
}

static bool 
cc_configuration_limit_value_unsigned_int_16bit(cc_config_parameter_buffer_t const* parameter_buffer,
                                                   cc_config_parameter_value_t * pNewValue)
{
  bool return_value = true;

  if( parameter_buffer->metadata->attributes.min_value.as_uint16 > pNewValue->as_uint16)
  {
    pNewValue->as_uint16 = parameter_buffer->metadata->attributes.min_value.as_uint16;
    return_value = false;
  }
  else if( parameter_buffer->metadata->attributes.max_value.as_uint16 < pNewValue->as_uint16)
  {
    pNewValue->as_uint16 = parameter_buffer->metadata->attributes.max_value.as_uint16;
    return_value = false;
  }

  return return_value;
}

static bool 
cc_configuration_limit_value_unsigned_int_32bit(cc_config_parameter_buffer_t const* parameter_buffer,
                                                   cc_config_parameter_value_t * pNewValue)
{
  bool return_value = true;

  if( parameter_buffer->metadata->attributes.min_value.as_uint32 > pNewValue->as_uint32)
  {
    pNewValue->as_uint32 = parameter_buffer->metadata->attributes.min_value.as_uint32;
    return_value = false;
  }
  else if( parameter_buffer->metadata->attributes.max_value.as_uint32 < pNewValue->as_uint32)
  {
    pNewValue->as_uint32 = parameter_buffer->metadata->attributes.max_value.as_uint32;
    return_value = false;
  }
  
  return return_value;
}

static bool 
cc_configuration_limit_value_unsigned_int(cc_config_parameter_buffer_t const* parameter_buffer,
                                             cc_config_parameter_value_t * pNewValue)
{
  bool return_value = true;

  switch(parameter_buffer->metadata->attributes.size)
  {
    case CC_CONFIG_PARAMETER_SIZE_8_BIT:
      return_value = cc_configuration_limit_value_unsigned_int_8bit(parameter_buffer, pNewValue);
      break;
    case CC_CONFIG_PARAMETER_SIZE_16_BIT:
      return_value = cc_configuration_limit_value_unsigned_int_16bit(parameter_buffer, pNewValue);
      break;
    case CC_CONFIG_PARAMETER_SIZE_32_BIT:
      return_value = cc_configuration_limit_value_unsigned_int_32bit(parameter_buffer, pNewValue);
      break;
    default:
      break;
  }

  return return_value;
}

bool
cc_configuration_limit_value(cc_config_parameter_buffer_t const* parameter_buffer,
                                cc_config_parameter_value_t * pNewValue)
{
  bool return_value = true;

  switch (parameter_buffer->metadata->attributes.format)
  {
    case CC_CONFIG_PARAMETER_FORMAT_SIGNED_INTEGER:
      return_value = cc_configuration_limit_value_signed_int(parameter_buffer, pNewValue);
      break;
    case CC_CONFIG_PARAMETER_FORMAT_UNSIGNED_INTEGER:
      return_value = cc_configuration_limit_value_unsigned_int(parameter_buffer, pNewValue);
      break;
    default:
      break;
  }

  return return_value;
}

static received_frame_status_t
cc_configuration_command_info(   RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                    const ZW_APPLICATION_TX_BUFFER *pCmd,
                                    const uint8_t cmdLength)
{
  UNUSED(cmdLength);

  ZW_CONFIGURATION_PROPERTIES_GET_V4_FRAME const* pCfgNameGetFrame = &pCmd->ZW_ConfigurationPropertiesGetV4Frame;

  cc_config_parameter_buffer_t parameter_buffer;
  const uint16_t payload_limit = ZAF_getAppHandle()->pNetworkInfo->MaxPayloadSize;
  uint16_t parameter_number = (uint16_t)(((uint16_t)pCfgNameGetFrame->parameterNumber1<<8) | pCfgNameGetFrame->parameterNumber2);
  ZW_APPLICATION_TX_BUFFER txBuf;
  zaf_tx_options_t tx_options;
  bool is_io_transaction_success = false;
  uint8_t reports_to_follow_count = 0;
  size_t info_str_length = 0;
  size_t info1_offset_in_struct = offsetof(ZW_CONFIGURATION_INFO_REPORT_4BYTE_V4_FRAME , info1);

  if (true == Check_not_legal_response_job(pRxOpt))
  {
    return RECEIVED_FRAME_STATUS_FAIL;
  }

  is_io_transaction_success = cc_configuration_get(parameter_number, &parameter_buffer);
  memset((void*)&txBuf.ZW_ConfigurationInfoReport4byteV4Frame, 0 ,sizeof(txBuf.ZW_ConfigurationInfoReport4byteV4Frame));
  txBuf.ZW_ConfigurationInfoReport4byteV4Frame.cmdClass   = COMMAND_CLASS_CONFIGURATION_V4;
  txBuf.ZW_ConfigurationInfoReport4byteV4Frame.cmd        = CONFIGURATION_INFO_REPORT_V4;
  txBuf.ZW_ConfigurationInfoReport4byteV4Frame.parameterNumber1 = pCfgNameGetFrame->parameterNumber1;
  txBuf.ZW_ConfigurationInfoReport4byteV4Frame.parameterNumber2 = pCfgNameGetFrame->parameterNumber2;
  txBuf.ZW_ConfigurationInfoReport4byteV4Frame.reportsToFollow  = reports_to_follow_count;
  zaf_transport_rx_to_tx_options(pRxOpt, &tx_options);

  if(is_io_transaction_success != false)
  {
    size_t str_pointer = 0;
    info_str_length = cc_configuration_strnlen(parameter_buffer.metadata->attributes.info,
                                                  SLI_CC_CONFIGURATION_MAX_STR_LENGTH);
    // maximum supported length of an info field per frame
    uint16_t info_field_limit = payload_limit - info1_offset_in_struct;
    reports_to_follow_count = cc_configuration_calc_reports_to_follow(info_str_length, info_field_limit);
    txBuf.ZW_ConfigurationInfoReport4byteV4Frame.reportsToFollow  = reports_to_follow_count;

    while(str_pointer < info_str_length)
    {
      size_t remaining_byte_count = info_str_length - str_pointer;
      size_t byte_count_to_send   = (remaining_byte_count >= info_field_limit) ? info_field_limit : remaining_byte_count;
      size_t frame_size_bytes     = info1_offset_in_struct /*header size*/
                                    + byte_count_to_send;

      uint8_t* raw_buffer = (uint8_t*)&txBuf;
      memcpy((void*)&raw_buffer[info1_offset_in_struct],
             (const void*)&parameter_buffer.metadata->attributes.info[str_pointer],
             byte_count_to_send);

      if(!zaf_transport_tx((uint8_t*) &txBuf, frame_size_bytes, NULL, &tx_options)) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      str_pointer+=byte_count_to_send;
      txBuf.ZW_ConfigurationInfoReport4byteV4Frame.reportsToFollow--;
    }
  }
  else
  {
    if(!zaf_transport_tx((uint8_t*) &txBuf, sizeof(txBuf.ZW_ConfigurationInfoReport4byteV4Frame), NULL, &tx_options)) {
      return RECEIVED_FRAME_STATUS_FAIL;
    }
  }

  return RECEIVED_FRAME_STATUS_SUCCESS;
}

static received_frame_status_t
cc_configuration_command_name_get( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                      const ZW_APPLICATION_TX_BUFFER *pCmd,
                                      const uint8_t cmdLength)
{
  UNUSED(cmdLength);

  ZW_CONFIGURATION_NAME_GET_V4_FRAME const* pCfgNameGetFrame = &pCmd->ZW_ConfigurationNameGetV4Frame;

  const uint16_t payload_limit = ZAF_getAppHandle()->pNetworkInfo->MaxPayloadSize;
  uint16_t parameter_number = (uint16_t)(((uint16_t)pCfgNameGetFrame->parameterNumber1<<8) | pCfgNameGetFrame->parameterNumber2);
  cc_config_parameter_buffer_t parameter_buffer;
  ZW_APPLICATION_TX_BUFFER txBuf;
  zaf_tx_options_t tx_options;
  bool is_io_transaction_success = false;
  uint8_t reports_to_follow_count = 0;
  size_t name_str_length = 0;

  if (true == Check_not_legal_response_job(pRxOpt))
  {
    return RECEIVED_FRAME_STATUS_FAIL;
  }

  is_io_transaction_success = cc_configuration_get(parameter_number, &parameter_buffer);
  memset((void*)&txBuf.ZW_ConfigurationNameReport4byteV4Frame, 0, sizeof(txBuf.ZW_ConfigurationNameReport4byteV4Frame));
  txBuf.ZW_ConfigurationNameReport4byteV4Frame.cmdClass = COMMAND_CLASS_CONFIGURATION_V4;
  txBuf.ZW_ConfigurationNameReport4byteV4Frame.cmd      = CONFIGURATION_NAME_REPORT_V4;
  txBuf.ZW_ConfigurationNameReport4byteV4Frame.parameterNumber1 = pCfgNameGetFrame->parameterNumber1;
  txBuf.ZW_ConfigurationNameReport4byteV4Frame.parameterNumber2 = pCfgNameGetFrame->parameterNumber2;
  txBuf.ZW_ConfigurationNameReport4byteV4Frame.reportsToFollow  = reports_to_follow_count;
  zaf_transport_rx_to_tx_options(pRxOpt, &tx_options);

  if(is_io_transaction_success != false)
  {
    size_t str_pointer = 0;
    size_t name1_offset_in_struct = offsetof(ZW_CONFIGURATION_NAME_REPORT_4BYTE_V4_FRAME , name1);

    name_str_length = cc_configuration_strnlen(parameter_buffer.metadata->attributes.name,
                                                   SLI_CC_CONFIGURATION_MAX_STR_LENGTH);

    reports_to_follow_count = cc_configuration_calc_reports_to_follow(name_str_length, payload_limit);
    txBuf.ZW_ConfigurationNameReport4byteV4Frame.reportsToFollow  = reports_to_follow_count;
    
    while(str_pointer < name_str_length)
    {
      size_t remaining_byte_count = name_str_length - str_pointer;
      size_t byte_count_to_send   = (remaining_byte_count >= payload_limit) ? payload_limit : remaining_byte_count;
      size_t frame_size_bytes     = name1_offset_in_struct /*header size*/
                                    + byte_count_to_send;

      uint8_t* raw_buffer = (uint8_t*)&txBuf;
      memcpy((void*)&raw_buffer[name1_offset_in_struct],
            (const void*)&parameter_buffer.metadata->attributes.name[str_pointer],
            byte_count_to_send);

      if(!zaf_transport_tx((uint8_t*) &txBuf, frame_size_bytes, NULL, &tx_options)) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      str_pointer+=byte_count_to_send;
      txBuf.ZW_ConfigurationInfoReport4byteV4Frame.reportsToFollow--;
    }
  }
  else
  {
    if(!zaf_transport_tx((uint8_t*) &txBuf, sizeof(txBuf.ZW_ConfigurationInfoReport4byteV4Frame), NULL, &tx_options)) {
      return RECEIVED_FRAME_STATUS_FAIL;
    }

  }
  
  return RECEIVED_FRAME_STATUS_SUCCESS;
}

static received_frame_status_t
cc_configuration_command_set(  RECEIVE_OPTIONS_TYPE_EX const *rxOpt,
                                  ZW_APPLICATION_TX_BUFFER const *pCmd,
                                  const uint8_t cmdLength)
{
  UNUSED(rxOpt);
  UNUSED(cmdLength);

  received_frame_status_t frame_status = RECEIVED_FRAME_STATUS_SUCCESS;
  ZW_CONFIGURATION_SET_4BYTE_V4_FRAME const* pCfgSetFrame = &pCmd->ZW_ConfigurationSet4byteV4Frame;
  cc_config_parameter_size_t size  =   pCfgSetFrame->level&0x07;

  if((false == cc_configuration_is_valid_size(size)))
  {
    return RECEIVED_FRAME_STATUS_FAIL;
  }

  bool is_default                  = ((pCfgSetFrame->level&0x80) == 0x80)?true:false;
  cc_config_parameter_value_t new_value;

  if(is_default == false)
  {
    memset(&new_value, 0, sizeof(cc_config_parameter_value_t));
    const cc_config_parameter_value_t* pConfigValue = ( cc_config_parameter_value_t *)&pCmd->ZW_ConfigurationSet4byteV4Frame.configurationValue1;
    uint8_t size_of_configuration_values = (uint8_t)size;

    for(uint8_t index = 0; index < size_of_configuration_values; index++)
    {
      new_value.as_uint8_array[size_of_configuration_values - index - 1] = pConfigValue->as_uint8_array[index];
    }

    cc_config_configuration_set_return_value return_value = cc_configuration_set(pCfgSetFrame->parameterNumber, &new_value, size);
    if(( CC_CONFIG_RETURN_CODE_IO_FAIL == return_value) || (CC_CONFIG_RETURN_CODE_NOT_SUPPORTED == return_value))
    {
      frame_status = RECEIVED_FRAME_STATUS_FAIL;
    }
  }
  else
  {
    if(false == cc_configuration_reset_to_default_value(pCfgSetFrame->parameterNumber))
    {
      frame_status = RECEIVED_FRAME_STATUS_FAIL;
    }
  }
  
  return frame_status;
}

static received_frame_status_t
cc_configuration_command_get(  RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                  ZW_APPLICATION_TX_BUFFER const * pCmd,
                                  const uint8_t cmdLength)
{
  UNUSED(cmdLength);

  ZW_CONFIGURATION_GET_V4_FRAME const* pCfgGetFrame = &pCmd->ZW_ConfigurationGetV4Frame;
  ZW_APPLICATION_TX_BUFFER txBuf;
  uint16_t parameter_number = pCfgGetFrame->parameterNumber;
  cc_config_parameter_buffer_t parameter_buffer;
  bool is_io_transaction_success = false;
  zaf_tx_options_t tx_options;

  memset(&txBuf, 0, sizeof(ZW_APPLICATION_TX_BUFFER));

  if (true == Check_not_legal_response_job(pRxOpt))
  {
    return RECEIVED_FRAME_STATUS_FAIL;
  }

  is_io_transaction_success = cc_configuration_get(parameter_number, &parameter_buffer);

  // Sonarcube error suppress (Dereference of undefined pointer value)
  if(NULL != parameter_buffer.metadata)
  {
    parameter_number = parameter_buffer.metadata->number;
  }
  

  if(is_io_transaction_success == false)
  {
    /*Unknown parameter number, get the first one*/
    is_io_transaction_success = cc_configuration_get_first_parameter(&parameter_buffer);
  }

  txBuf.ZW_ConfigurationReport4byteV4Frame.cmdClass        = COMMAND_CLASS_CONFIGURATION_V4;
  txBuf.ZW_ConfigurationReport4byteV4Frame.cmd             = CONFIGURATION_REPORT_V4;
  txBuf.ZW_ConfigurationReport4byteV4Frame.parameterNumber = (uint8_t)parameter_number;
  if(NULL != parameter_buffer.metadata)
  {
    txBuf.ZW_ConfigurationReport4byteV4Frame.level         = (uint8_t)parameter_buffer.metadata->attributes.size;
  }
  
  cc_configuration_copyToFrame((cc_config_parameter_value_t *)&txBuf.ZW_ConfigurationReport4byteV4Frame.configurationValue1,
                                  &parameter_buffer,
                                  &parameter_buffer.data_buffer);

  zaf_transport_rx_to_tx_options(pRxOpt, &tx_options);

  if(!zaf_transport_tx((uint8_t*) &txBuf, sizeof(txBuf.ZW_ConfigurationReport4byteV4Frame), NULL, &tx_options)) {
    return RECEIVED_FRAME_STATUS_FAIL;
  }

  return RECEIVED_FRAME_STATUS_SUCCESS;
}


static uint16_t
cc_configuration_find_next_valid_parameter_number(uint16_t input)
{
  uint16_t global_difference = 0xFF;
  uint16_t next_number = 0;
  const uint16_t lowest_number = cc_configuration_get_lowest_parameter_number();

  for(uint8_t i = 0; i < configuration_pool->numberOfParameters; i++)
  {
    if((configuration_pool->parameters[i].next_number - input) <= global_difference)
    {
      global_difference = configuration_pool->parameters[i].next_number - input;
      next_number = configuration_pool->parameters[i].next_number;
    }
  }
  // return the calculated next number
  return ((next_number == 0) ? lowest_number : next_number);
}

static bool
cc_configuration_check_if_parameter_number_is_valid(uint16_t input)
{
  bool result = false;

  for(uint8_t i = 0; i < configuration_pool->numberOfParameters; i++)
  {
    if(input == configuration_pool->parameters[i].number)
    {
      result = true;
      break;
    }
  }
  return result;
}


static received_frame_status_t
cc_configuration_command_properties_get(  RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                             ZW_APPLICATION_TX_BUFFER const * pCmd,
                                             const uint8_t cmdLength)
{
  UNUSED(cmdLength);

  ZW_CONFIGURATION_PROPERTIES_GET_V4_FRAME const* pCfgNameGetFrame = &pCmd->ZW_ConfigurationPropertiesGetV4Frame;
  uint16_t parameter_number = (uint16_t)(((uint16_t)pCfgNameGetFrame->parameterNumber1<<8) | pCfgNameGetFrame->parameterNumber2);
  cc_config_parameter_buffer_t parameter_buffer;
  ZW_APPLICATION_TX_BUFFER txBuf;
  zaf_tx_options_t tx_options;
  bool is_valid_parameter_number = cc_configuration_check_if_parameter_number_is_valid(parameter_number);
  if (true == Check_not_legal_response_job(pRxOpt))
  {
    return RECEIVED_FRAME_STATUS_FAIL;
  }

  if(0 == parameter_number)
  {
    cc_configuration_probe(&parameter_buffer);
  }
  else if(true == is_valid_parameter_number)
  {
    cc_configuration_get(parameter_number, &parameter_buffer);
  }

  zaf_transport_rx_to_tx_options(pRxOpt, &tx_options);

  if( false == is_valid_parameter_number)
  {
    uint8_t* raw_buffer = (uint8_t*)&txBuf;
    uint8_t raw_buffer_index = 0;

    uint16_t next_parameter_number = cc_configuration_find_next_valid_parameter_number(parameter_number);

    raw_buffer[raw_buffer_index++] = COMMAND_CLASS_CONFIGURATION_V4;
    raw_buffer[raw_buffer_index++] = CONFIGURATION_PROPERTIES_REPORT_V4;
    raw_buffer[raw_buffer_index++] = pCfgNameGetFrame->parameterNumber1;
    raw_buffer[raw_buffer_index++] = pCfgNameGetFrame->parameterNumber2;
    raw_buffer[raw_buffer_index++] = 0; // size and format bits are 0 if the parameter number is invalid
    raw_buffer[raw_buffer_index++] = (uint8_t)((next_parameter_number >> 8) & 0xFF);
    raw_buffer[raw_buffer_index++] = (uint8_t)(next_parameter_number  & 0xFF);
    raw_buffer[raw_buffer_index++] = 0; // Properties 2
    
    if(!zaf_transport_tx((uint8_t*) &txBuf, raw_buffer_index, NULL, &tx_options)) {
      return RECEIVED_FRAME_STATUS_FAIL;
    }
  }
  else
  {
    typedef struct
    {
      uint8_t command_class;
      uint8_t command;
      uint8_t parameter_number_msb;
      uint8_t parameter_number_lsb;

      uint8_t size : 3;
      uint8_t format : 3;
      uint8_t read_only : 1;
      uint8_t altering_capabilities : 1;

      uint8_t variable_info[12 + 2 + 1]; // Min, max & default (1,2,4 bytes), next param & flags
    }
    frame_t;
    frame_t * p_frame = (frame_t *)&txBuf;
    p_frame->command_class          = COMMAND_CLASS_CONFIGURATION_V4;
    p_frame->command                = CONFIGURATION_PROPERTIES_REPORT_V4;
    p_frame->parameter_number_msb   = pCfgNameGetFrame->parameterNumber1;
    p_frame->parameter_number_lsb   = pCfgNameGetFrame->parameterNumber2;
    p_frame->altering_capabilities  = parameter_buffer.metadata->attributes.flags.altering_capabilities;
    p_frame->read_only              = parameter_buffer.metadata->attributes.flags.read_only;
    p_frame->format                 = parameter_buffer.metadata->attributes.format;
    p_frame->size                   = parameter_buffer.metadata->attributes.size;

    uint8_t i = 0;
    cc_configuration_copyToFrame((cc_config_parameter_value_t *)&p_frame->variable_info[i],
                                 &parameter_buffer,
                                 &parameter_buffer.metadata->attributes.min_value);
    i += parameter_buffer.metadata->attributes.size;

    cc_configuration_copyToFrame((cc_config_parameter_value_t *)&p_frame->variable_info[i],
                                 &parameter_buffer,
                                 &parameter_buffer.metadata->attributes.max_value);
    i += parameter_buffer.metadata->attributes.size;

    cc_configuration_copyToFrame((cc_config_parameter_value_t *)&p_frame->variable_info[i],
                                 &parameter_buffer,
                                 &parameter_buffer.metadata->attributes.default_value);
    i += parameter_buffer.metadata->attributes.size;

    // Set next parameter number
    p_frame->variable_info[i++] = (uint8_t)(parameter_buffer.metadata->next_number >> 8);
    p_frame->variable_info[i++] = (uint8_t)(parameter_buffer.metadata->next_number);

    // Hardcode "No Bulk Support" to 0 and add "Advanced" flag.
    p_frame->variable_info[i++] = parameter_buffer.metadata->attributes.flags.advanced & 0x01;

    if(!zaf_transport_tx((uint8_t*) p_frame, offsetof(ZW_CONFIGURATION_PROPERTIES_REPORT_4BYTE_V4_FRAME , minValue1) + i, NULL, &tx_options)) {
      return RECEIVED_FRAME_STATUS_FAIL;
    }
  }

  return RECEIVED_FRAME_STATUS_SUCCESS;
}


static received_frame_status_t
cc_configuration_command_bulk_get( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                      ZW_APPLICATION_TX_BUFFER const * pCmd,
                                      const uint8_t cmdLength)
{
  UNUSED(cmdLength);

  ZW_CONFIGURATION_BULK_GET_V4_FRAME const* pCfgBulkGetFrame = &pCmd->ZW_ConfigurationBulkGetV4Frame;

  uint16_t parameter_offset    = (uint16_t)(((uint16_t)pCfgBulkGetFrame->parameterOffset1<<8) |
                                                       pCfgBulkGetFrame->parameterOffset2);
  uint8_t number_of_parameters = pCfgBulkGetFrame->numberOfParameters;

  if (true == Check_not_legal_response_job(pRxOpt))
  {
    return RECEIVED_FRAME_STATUS_FAIL;
  }

  /*
   * Invoke cc_configuration_command_send_bulk_report() with CC_CONFIG_PARAMETER_SIZE_NOT_SPECIFIED
   * as the Configuration Bulk Get doesn't contain a size.
   */
  return cc_configuration_command_send_bulk_report(pRxOpt,
                                                      parameter_offset,
                                                      parameter_offset + number_of_parameters,
                                                      false);
}

static received_frame_status_t
cc_configuration_command_bulk_set( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                      ZW_APPLICATION_TX_BUFFER const * pCmd,
                                      const uint8_t cmdLength)
{
  UNUSED(cmdLength);

  received_frame_status_t frame_status = RECEIVED_FRAME_STATUS_SUCCESS;
  uint8_t const* p_raw_cmd = (uint8_t const*)pCmd;
  bool io_transaction_result = false;
  cc_config_parameter_buffer_t parameter_buffer;
  
  uint8_t cmd_index = 0;
  cmd_index++; /*Command Class*/
  cmd_index++; /*Command */

  /*combine parameter offset 1 and 2*/
  uint16_t parameter_offset = (uint16_t)(((uint16_t)p_raw_cmd[cmd_index]<<8) | p_raw_cmd[cmd_index + 1] );
  cmd_index+=2;
  uint8_t number_of_parameters = p_raw_cmd[cmd_index];   /*Number of parameters*/
  cmd_index++;
  
  bool is_default   = ((p_raw_cmd[cmd_index]&(1<<7)) == 0x80)?true:false; /*Default*/
  bool handshake    = ((p_raw_cmd[cmd_index]&(1<<6)) == 0x40)?true:false; /*Handshake*/
  cc_config_parameter_size_t size = p_raw_cmd[cmd_index]&0x07; /*Size*/
  if(false == cc_configuration_is_valid_size(size))
  {
    return RECEIVED_FRAME_STATUS_FAIL;
  }
  cmd_index++;

  cc_config_parameter_value_t new_parameter_value;
  uint16_t updated_parameter_counter = 0;
  uint16_t first_parameter_number   = parameter_offset;
  bool status = cc_configuration_get_first_parameter(&parameter_buffer);
  if(status == true)
  {
    first_parameter_number   += parameter_buffer.metadata->number;
  }

  uint8_t size_of_new_parameter_value = sizeof(new_parameter_value.as_int32); //sets the default size to 4 bytes
  switch(size)
  {

    case CC_CONFIG_PARAMETER_SIZE_8_BIT:
    size_of_new_parameter_value = sizeof(new_parameter_value.as_int8); //1bytes
    break;

    case CC_CONFIG_PARAMETER_SIZE_16_BIT:
    size_of_new_parameter_value = sizeof(new_parameter_value.as_int16); //2bytes
    break;

    case CC_CONFIG_PARAMETER_SIZE_32_BIT:
    size_of_new_parameter_value = sizeof(new_parameter_value.as_int32); //4bytes
    break;

    default:
    break;
  }

  while(updated_parameter_counter < number_of_parameters)
  {
    bool has_to_break = false;
    io_transaction_result = cc_configuration_get(first_parameter_number, &parameter_buffer);

    if(io_transaction_result == false)
    {
      frame_status = RECEIVED_FRAME_STATUS_FAIL;
      has_to_break = true;
    }

    if(has_to_break == true)
    {
      break;
    }

    if(is_default == true)
    {
      cc_configuration_reset_to_default_value(first_parameter_number);
    }
    else
    {
      memset(&new_parameter_value, 0, sizeof(cc_config_parameter_value_t));

      for(uint8_t index = 0; index < size_of_new_parameter_value ; index++)
      {
        new_parameter_value.as_uint8_array[size_of_new_parameter_value - index -1] = p_raw_cmd[cmd_index + index];  
      }

      cc_config_configuration_set_return_value return_value = cc_configuration_set(first_parameter_number, &new_parameter_value, size);
      if(( CC_CONFIG_RETURN_CODE_IO_FAIL == return_value) || (CC_CONFIG_RETURN_CODE_NOT_SUPPORTED == return_value))
      {
        frame_status = RECEIVED_FRAME_STATUS_FAIL;
        has_to_break = true;
      }
      cmd_index += size;
    }

    if(parameter_buffer.metadata->next_number != 0x0000)
    {
      first_parameter_number = parameter_buffer.metadata->next_number;
    }
    else
    {
      //This is the last parameter
      has_to_break = true;
    }
    updated_parameter_counter++;
    
  }

  if(handshake == true)
  {
    frame_status = cc_configuration_command_send_bulk_report(pRxOpt,
                                                                parameter_offset,
                                                                parameter_offset + number_of_parameters,
                                                                handshake);
  }

  return frame_status;
}

static received_frame_status_t
cc_configuration_command_send_bulk_report( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                              const uint16_t parameter_offset,
                                              const uint16_t stop_number,
                                              const bool flag_handshake)
{
  bool enqueue_status = false;

  zaf_tx_options_t tx_options;
  zaf_transport_rx_to_tx_options(pRxOpt, &tx_options);

  bool status = true;
  cc_config_parameter_buffer_t parameter_buffer;
  status = cc_configuration_get_first_parameter(&parameter_buffer);
  uint16_t first_parameter_number = parameter_buffer.metadata->number;

  /*
   * Create the first part of the report.
   */
  ZW_APPLICATION_TX_BUFFER frame;
  uint8_t * p_frame = (uint8_t *)&frame;
  *(p_frame + 0) = COMMAND_CLASS_CONFIGURATION_V4;
  *(p_frame + 1) = CONFIGURATION_BULK_REPORT_V4;
  *(p_frame + 2) = (uint8_t)(parameter_offset >> 8);
  *(p_frame + 3) = (uint8_t)parameter_offset;
  *(p_frame + 4) = 0; // Number of parameters will be filled out later.
  *(p_frame + 5) = 0; // Reports to follow will be filled out later.

  // Set default flag initially. Will be cleared later, if required.
  *(p_frame + 6) = DEFAULT_FLAG;

  if (true == flag_handshake) {
    *(p_frame + 6) |= HANDSHAKE_FLAG;
  }

  uint32_t count = 0;
  cc_config_parameter_size_t parameter_size = 0;
  cc_config_parameter_size_t first_parameter_size = CC_CONFIG_PARAMETER_SIZE_NOT_SPECIFIED;

  // Calculate parameter number for the first parameter to report.
  uint16_t parameter_number = parameter_offset + first_parameter_number;

  /*
   * Calculate the number of consecutive parameters to be reported.
   *
   * The loop breaks on a change in size as the reported parameters must have the same size.
   *
   * This number is required to calculate the total number of reports.
   */
  uint16_t requested_parameter_count = stop_number - parameter_offset;
  for (; count < requested_parameter_count; count++)
  {
    // Get the parameter
    status = cc_configuration_get(parameter_number, &parameter_buffer);

    if (true != status)
    {
      break;
    }

    parameter_size = parameter_buffer.metadata->attributes.size;

    if (CC_CONFIG_PARAMETER_SIZE_NOT_SPECIFIED == first_parameter_size)
    {
      // Set first_parameter_size to a valid value if it hasn't been set already.
      first_parameter_size = parameter_size;
    }

    if (parameter_size != first_parameter_size)
    {
      // Only parameters of the same size are allowed in a bulk report. Hence, break on different size.
      break;
    }

    parameter_number = parameter_buffer.metadata->next_number;
  }

  // Set the size
  *(p_frame + 6) |= ((uint8_t)parameter_size & 0x07);

  // Calculate parameter number for the first parameter to report.
  parameter_number = parameter_offset + first_parameter_number;

  const uint8_t REPORT_BASE_LENGTH = 7; // Report contains 7 bytes without any parameters.

  uint8_t generated_report_length = REPORT_BASE_LENGTH; // Initial length of report.

  // Increase p_frame_parameter by initial report size so it's ready for the first parameter.
  uint8_t * p_frame_parameter = p_frame + generated_report_length;

  uint16_t offset_to_report = parameter_offset;

  /*
   * Calculate the remaining number of reports.
   *
   * This number is used as an initial value to report the number of remaining (following) reports.
   */
  uint8_t remaining_number_of_reports  = 0;
  uint8_t required_payload_size = count * parameter_buffer.metadata->attributes.size;
  const uint16_t payload_limit = ZAF_getAppHandle()->pNetworkInfo->MaxPayloadSize;
  uint8_t available_payload = payload_limit - 7;
  if (available_payload < required_payload_size) {
    remaining_number_of_reports = required_payload_size / available_payload;
    if (required_payload_size % available_payload) {
      remaining_number_of_reports++;
    }
  }

  uint8_t parameter_count_to_report = 0;

  for (uint32_t i = 0; i < count; i++)
  {
    parameter_count_to_report++;

    // Get the parameter
    status = cc_configuration_get(parameter_number, &parameter_buffer);

    if (false != status) {
      // TODO: Handle this case.
    }

    /*
     * CC:0070.02.09.11.007: Set the default flag to 1 unless one or more of the parameters are
     * set to a non-default value.
     */
    if (parameter_buffer.data_buffer.as_uint32 != parameter_buffer.metadata->attributes.default_value.as_uint32) {
      *(p_frame + 6) &= ~DEFAULT_FLAG; // Clear default flag.
    }

    generated_report_length += parameter_buffer.metadata->attributes.size;

    cc_configuration_copyToFrame(  (cc_config_parameter_value_t *)p_frame_parameter,
                                      &parameter_buffer,
                                      &parameter_buffer.data_buffer);

    if ((generated_report_length + parameter_buffer.metadata->attributes.size > payload_limit) ||
        ((i + 1) == requested_parameter_count)) {
      // No room for the next parameter or we reach the total number of parameters => Transmit now.

      *(p_frame + 2) = (uint8_t)(offset_to_report >> 8);
      *(p_frame + 3) = (uint8_t)offset_to_report;

      *(p_frame + 4) = parameter_count_to_report; // Number of parameters.

      if (remaining_number_of_reports) {
        remaining_number_of_reports--;
      }
      *(p_frame + 5) = remaining_number_of_reports; // Reports to follow

      enqueue_status = zaf_transport_tx((uint8_t*) p_frame, generated_report_length,
                                        NULL, &tx_options);

      generated_report_length = REPORT_BASE_LENGTH; // Reset generated report length to initial value.
      p_frame_parameter = p_frame + generated_report_length; // Reset pointer to first parameter in report.
      offset_to_report += i + 1; // Increase offset by the number of parameters included in this report.
      parameter_count_to_report = 0;
      *(p_frame + 6) |= DEFAULT_FLAG; // Reset default flag to initial value.
    } else {
      // Increase frame pointer for next parameter
      p_frame_parameter += parameter_buffer.metadata->attributes.size;
    }
    parameter_number = parameter_buffer.metadata->next_number;
  }

  return enqueue_status ? RECEIVED_FRAME_STATUS_SUCCESS : RECEIVED_FRAME_STATUS_FAIL;
}

static received_frame_status_t
cc_configuration_command_default_reset( RECEIVE_OPTIONS_TYPE_EX *pRxOpt,
                                           ZW_APPLICATION_TX_BUFFER const * pCmd,
                                           const uint8_t cmdLength)
{
  UNUSED(pRxOpt);
  UNUSED(pCmd);
  UNUSED(cmdLength);
  bool write_success = false;

  for(uint16_t parameter_ix = 0 ; parameter_ix < configuration_pool->numberOfParameters ; parameter_ix++)
  {
    write_success = cc_configuration_io_write( configuration_pool->parameters[parameter_ix].file_id,
                                                        (const uint8_t*)&configuration_pool->parameters[parameter_ix].attributes.default_value,
                                                          sizeof(cc_config_parameter_value_t)); 
    if(false == write_success)
    {
      return RECEIVED_FRAME_STATUS_FAIL;
    }

  }
  return RECEIVED_FRAME_STATUS_SUCCESS;
}

static cc_config_configuration_set_return_value
cc_configuration_set(uint16_t parameter_number,  cc_config_parameter_value_t* new_value, cc_config_parameter_size_t size)
{
  cc_config_configuration_set_return_value return_value = CC_CONFIG_RETURN_CODE_OK;
  bool io_transaction_result = false;
  bool is_value_in_range = false;
  bool has_to_break = false;
  cc_config_parameter_buffer_t parameter_buffer;

    for(uint16_t parameter_ix = 0 ; parameter_ix < configuration_pool->numberOfParameters ; parameter_ix++)
    {
      if( configuration_pool->parameters[parameter_ix].attributes.flags.read_only == false            && 
          configuration_pool->parameters[parameter_ix].number                     == parameter_number) 
      {
        if(configuration_pool->parameters[parameter_ix].attributes.size != size)
        {
          return_value = CC_CONFIG_RETURN_CODE_NOT_SUPPORTED;
          has_to_break = true;
        }
        if(true == has_to_break)
        {
          break;
        }
        io_transaction_result = cc_configuration_io_read( configuration_pool->parameters[parameter_ix].file_id,
                                                            (uint8_t*)&parameter_buffer.data_buffer,
                                                            sizeof(cc_config_parameter_value_t));

        if(io_transaction_result == false)
        {
          return_value = CC_CONFIG_RETURN_CODE_IO_FAIL;
        }
        
        parameter_buffer.metadata = &configuration_pool->parameters[parameter_ix];
        is_value_in_range = cc_configuration_limit_value(&parameter_buffer, new_value);
        if( true == is_value_in_range)
        {
            memcpy( (void*)(uint8_t*)&parameter_buffer.data_buffer.as_uint8_array,
                  (const void*)new_value->as_uint8_array,
                  sizeof(cc_config_parameter_value_t));

            io_transaction_result = cc_configuration_io_write( configuration_pool->parameters[parameter_ix].file_id,
                                                            (const uint8_t*)&parameter_buffer.data_buffer,
                                                            sizeof(cc_config_parameter_value_t));
           
          

          
        }
        if(io_transaction_result == false)
        {
          return_value = CC_CONFIG_RETURN_CODE_IO_FAIL;
        }
        has_to_break = true;
      }

    }

    return return_value;
}

bool
cc_configuration_get(uint16_t parameter_number, cc_config_parameter_buffer_t* parameter_buffer)
{
  bool io_transaction_result = false;

  if(parameter_buffer != NULL)
  { 
     for(uint16_t parameter_ix = 0 ; parameter_ix < configuration_pool->numberOfParameters ; parameter_ix++)
     {
       if(configuration_pool->parameters[parameter_ix].number == parameter_number)
       {
         parameter_buffer->metadata = &configuration_pool->parameters[parameter_ix];
         io_transaction_result = cc_configuration_io_read( configuration_pool->parameters[parameter_ix].file_id,
                                                             (uint8_t*)&parameter_buffer->data_buffer,
                                                             sizeof(cc_config_parameter_value_t));
         break;
       }
     }
   }
  return io_transaction_result;
}

static bool
cc_configuration_probe(cc_config_parameter_buffer_t* parameter_buffer)
{
  static cc_config_parameter_metadata_t zero_meta;
  static uint16_t lowest_parameter_number;

  lowest_parameter_number = cc_configuration_get_lowest_parameter_number();
  zero_meta.next_number = lowest_parameter_number;
  memset(parameter_buffer, 0, sizeof(cc_config_parameter_buffer_t));
  parameter_buffer->metadata = &zero_meta;
  return true;
}

static bool
cc_configuration_reset_to_default_value(uint16_t parameter_number)
{
  bool io_transaction_result = false;

  for(uint16_t parameter_ix = 0 ; parameter_ix < configuration_pool->numberOfParameters ; parameter_ix++)
  {
    if(configuration_pool->parameters[parameter_ix].number == parameter_number)
    {
      io_transaction_result = cc_configuration_io_write( configuration_pool->parameters[parameter_ix].file_id,
                                                          (const uint8_t*)&configuration_pool->parameters[parameter_ix].attributes.default_value,
                                                           sizeof(cc_config_parameter_value_t));
      
      break;
    }
  }
  
  return io_transaction_result;
}

static bool
cc_configuration_get_first_parameter(cc_config_parameter_buffer_t* parameter_buffer)
{
  uint16_t lowest_parameter_number = cc_configuration_get_lowest_parameter_number(parameter_buffer);
  return cc_configuration_get(lowest_parameter_number, parameter_buffer);
}

static uint16_t
cc_configuration_get_lowest_parameter_number()
{
  uint16_t lowest_parameter_number = 0xFFFF;

  /*Find the lowest number to be the first one*/
  for(uint16_t parameter_ix = 0 ; parameter_ix < configuration_pool->numberOfParameters ; parameter_ix++)
  {
    uint16_t current_parameter_number = configuration_pool->parameters[parameter_ix].number;
    if(lowest_parameter_number > current_parameter_number)
    {
      lowest_parameter_number = current_parameter_number;
    }
  }
  return lowest_parameter_number;
}

static uint8_t
cc_configuration_calc_reports_to_follow(size_t data_length, size_t payload_limit)
{
  uint16_t reports_to_follow_count  = (uint16_t)(data_length / payload_limit);
  uint16_t val = ((data_length % payload_limit) != 0)?1:0;
  reports_to_follow_count += val; /*Round up*/
  reports_to_follow_count-=1; /*If the data fits in payload it should be zero*/

  return (uint8_t)reports_to_follow_count;
}

static size_t
cc_configuration_strnlen(const char *str, size_t maxlen)
{
  size_t i = 0;
  if(str != NULL)
  {
    for(i = 0; i < maxlen && str[i]; i++);
  }
  return i;
}

static bool 
cc_configuration_is_valid_size(cc_config_parameter_size_t size_value)
{
  //Reffering to SDS13781-15 document, table-32 (page 165)
  bool return_value = false;
  switch(size_value)
  {
    case CC_CONFIG_PARAMETER_SIZE_8_BIT:
      return_value = true;
    break;

    case CC_CONFIG_PARAMETER_SIZE_16_BIT:
      return_value = true;
    break;

    case CC_CONFIG_PARAMETER_SIZE_32_BIT:
      return_value = true;
    break;

    case CC_CONFIG_PARAMETER_SIZE_NOT_SPECIFIED:
      return_value = false;
    break;

    default:
      return_value = false;
    break;
  }
  return return_value;

}

REGISTER_CC_V4(COMMAND_CLASS_CONFIGURATION_V4, CONFIGURATION_VERSION_V4, CC_Configuration_handler, NULL, NULL, NULL, 0, init_and_reset, init_and_reset);
