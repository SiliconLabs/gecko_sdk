/**
 * @file
 *
 * Retention Register Bank API
 *
 * @copyright 2019 Silicon Laboratories Inc.
 */
#ifndef COMPONENTS_RETENTIONREGISTERBANK_RETENTIONREGISTERBANK_H_
#define COMPONENTS_RETENTIONREGISTERBANK_RETENTIONREGISTERBANK_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * Return values for RetentionRegBank_ReadReg() and RetentionRegBank_WriteReg().
 */
typedef enum
{
  RETENTION_REGISTER_BANK_SUCCESS = 0,   //!< RETENTION_REGISTER_BANK_SUCCESS
  RETENTION_REGISTER_BANK_INVALID_INDEX, //!< RETENTION_REGISTER_BANK_INVALID_INDEX
  RETENTION_REGISTER_BANK_INVALID_POINTER//!< RETENTION_REGISTER_BANK_INVALID_POINTER
}
retention_register_bank_error_code_t;

/**
 * Retention registers with index 0-15 are reserved for ZWave protocol code
 */
#define SMARTSTART_RETENTION_REGISTER            0
#define RESPONSEROUTE_RETENTION_REGISTER_1       1
#define RESPONSEROUTE_RETENTION_REGISTER_2       2
#define RESPONSEROUTE_RETENTION_REGISTER_3       3
#define RESPONSEROUTE_RETENTION_REGISTER_4       4
#define EM4SLEEP_TICK_RETENTION_REGISTER         5
#define TXPOWER_RSSI_LR_RETENTION_REGISTER       6
#define LOWSIDECAL_RETENTION_REGISTER            7
#define HIGHSIDECAL_RETENTION_REGISTER           8
/**
 * Initialize the retention register bank clock
 */
bool RetentionRegBank_Init(void);

/**
 * Sets the value of all retention registers to zero.
 */
void RetentionRegBank_Clear(void);

/**
 * Reads a 32-bit value from the specified retention register.
 * @param[in] index Retention register number (zero-based).
 * @param[out] pData Pointer to a 32-bit variable where the value can be stored.
 * @return RETENTION_REGISTER_BANK_SUCCESS on success.
 *         Otherwise, RETENTION_REGISTER_BANK_INVALID_INDEX or
 *         RETENTION_REGISTER_BANK_INVALID_POINTER.
 */
retention_register_bank_error_code_t RetentionRegBank_ReadReg(uint32_t index, uint32_t * pData);

/**
 * Write a 32-bit value to the specified retention register
 * @param[in] index Retention register number (zero-based).
 * @param[in] value  32-bit value to save in retention register.
 * @return 0 if success. RETENTION_REGISTER_BANK_INVALID_INDEX otherwise.
 */
retention_register_bank_error_code_t RetentionRegBank_WriteReg(uint32_t index, uint32_t value);

#endif /* COMPONENTS_RETENTIONREGISTERBANK_RETENTIONREGISTERBANK_H_ */
