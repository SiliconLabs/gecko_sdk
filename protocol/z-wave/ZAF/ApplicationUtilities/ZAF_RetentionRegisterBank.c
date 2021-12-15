/*
 * @file
 * Retention Register Bank
 *
 * Provides functions for writing to and reading from retention registers.
 *
 * @copyright 2019 Silicon Laboratories Inc.
 */
#include <ZAF_RetentionRegisterBank.h>
#include <RetentionRegisterBank.h>

#define REGISTER_INDEX_ZAF_APP_START 16

zaf_retention_register_bank_error_code_t ZAF_RetentionRegBank_ReadReg(uint32_t index, uint32_t * pData)
{
  if (index < REGISTER_INDEX_ZAF_APP_START)
  {
    return ZAF_RETENTION_REGISTER_BANK_INVALID_INDEX;
  }
  return (zaf_retention_register_bank_error_code_t)RetentionRegBank_ReadReg(index, pData);
}

zaf_retention_register_bank_error_code_t ZAF_RetentionRegBank_WriteReg(uint32_t index, uint32_t value)
{
  if (index < REGISTER_INDEX_ZAF_APP_START)
  {
    return ZAF_RETENTION_REGISTER_BANK_INVALID_INDEX;
  }
  return (zaf_retention_register_bank_error_code_t)RetentionRegBank_WriteReg(index, value);
}
