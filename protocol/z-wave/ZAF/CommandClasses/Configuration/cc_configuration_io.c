/***************************************************************************//**
 * @file
 *
 * @copyright 2022 Silicon Laboratories Inc.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#include <stddef.h>
#include <stdbool.h>
#include <cc_configuration_io.h>
#include <ZW_typedefs.h>
#include <ZAF_nvm_app.h>
#include <ZAF_nvm.h>
#include <cc_configuration_config_api.h>
#include <zpal_nvm.h>

// -----------------------------------------------------------------------------
//              Public Function
// -----------------------------------------------------------------------------
ZW_WEAK bool
cc_configuration_io_write(zpal_nvm_object_key_t file_id, uint8_t const* data, size_t size)
{
  zpal_status_t status = ZPAL_STATUS_FAIL;

  if ((data != NULL) && (size > 0)) {
    status = ZAF_nvm_write(file_id, data, size);
  }
  return (status == ZPAL_STATUS_OK) ? true : false;
}

ZW_WEAK bool
cc_configuration_io_read(zpal_nvm_object_key_t file_id, uint8_t *data, size_t size)
{
  zpal_status_t status = ZPAL_STATUS_FAIL;

  if ((data != NULL) && (size > 0)) {
    status = ZAF_nvm_read(file_id, data, size);
  }

  return (status == ZPAL_STATUS_OK) ? true : false;
}
