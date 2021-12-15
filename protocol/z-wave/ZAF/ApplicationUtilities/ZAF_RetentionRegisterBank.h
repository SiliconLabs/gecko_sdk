/**
 * @file
 * Retention Register Bank
 *
 * Provides functions for writing to and reading from retention registers.
 *
 * The ZAF and application together has 16 x 32-bit retention registers with IDs going from 16 to
 * 31.
 *
 * If a retention register is not in use, make sure to set it to zero because any other value will
 * consume more power.
 *
 * @copyright 2019 Silicon Laboratories Inc.
 */
#ifndef ZAF_APPLICATIONUTILITIES_ZAF_RETENTIONREGISTERBANK_H_
#define ZAF_APPLICATIONUTILITIES_ZAF_RETENTIONREGISTERBANK_H_

#include <stdint.h>

/**
 * Return values for ZAF_RetentionRegBank_ReadReg() and ZAF_RetentionRegBank_WriteReg().
 */
typedef enum
{
  ZAF_RETENTION_REGISTER_BANK_SUCCESS = 0,   //!< RETENTION_REGISTER_BANK_SUCCESS
  ZAF_RETENTION_REGISTER_BANK_INVALID_INDEX, //!< RETENTION_REGISTER_BANK_INVALID_INDEX
  ZAF_RETENTION_REGISTER_BANK_INVALID_POINTER//!< RETENTION_REGISTER_BANK_INVALID_POINTER
}
zaf_retention_register_bank_error_code_t;

/**
 * Reads a 32-bit value from the specified retention register.
 * @param[in] index Retention register number (16-31).
 * @param[out] pData Pointer to a 32-bit variable where the value can be stored.
 * @return ZAF_RETENTION_REGISTER_BANK_SUCCESS on success.
 *         Otherwise, ZAF_RETENTION_REGISTER_BANK_INVALID_INDEX or
 *         ZAF_RETENTION_REGISTER_BANK_INVALID_POINTER.
 */
zaf_retention_register_bank_error_code_t ZAF_RetentionRegBank_ReadReg(uint32_t index, uint32_t * pData);

/**
 * Write a 32-bit value to the specified retention register
 * @param[in] index Retention register number (16-31).
 * @param[in] value 32-bit value to save in retention register.
 * @return 0 if success. ZAF_RETENTION_REGISTER_BANK_INVALID_INDEX otherwise.
 */
zaf_retention_register_bank_error_code_t ZAF_RetentionRegBank_WriteReg(uint32_t index, uint32_t value);

#endif /* ZAF_APPLICATIONUTILITIES_ZAF_RETENTIONREGISTERBANK_H_ */
