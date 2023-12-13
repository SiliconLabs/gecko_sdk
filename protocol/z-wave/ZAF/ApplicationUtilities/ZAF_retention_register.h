/**
 * @file
 * @brief Retention Registers module.
 *
 * @copyright 2023 Silicon Laboratories Inc.
 */

#ifndef ZAF_RETENTION_REGISTER_H_
#define ZAF_RETENTION_REGISTER_H_

#include <stddef.h>
#include <zpal_status.h>

/**
 * @addtogroup ZAF
 * @{
 * @addtogroup RETENTIONREGISTER Retention Register
 * @{
 */

/**
 * @brief Reads a 32-bit value from the specified retention register.
 *
 * @param[in]   index Retention register number (zero-based).
 * @param[out]  data  Pointer to a 32-bit variable where the value can be stored.
 * @return @ref ZPAL_STATUS_OK on success, @ref ZPAL_STATUS_INVALID_ARGUMENT on
 * invalid @p index or @p data and @ref ZPAL_STATUS_FAIL otherwise.
 */
zpal_status_t ZAF_retention_register_read(uint32_t index, uint32_t *data);

/**
 * @brief Write a 32-bit value to the specified retention register.
 *
 * @param[in] index Retention register number (zero-based).
 * @param[in] value 32-bit value to save in retention register.
 * @return @ref ZPAL_STATUS_OK on success, @ref ZPAL_STATUS_INVALID_ARGUMENT on
 * invalid @p index and @ref ZPAL_STATUS_FAIL otherwise.
 */
zpal_status_t ZAF_retention_register_write(uint32_t index, uint32_t value);

/**
 * @brief Get number of retention registers available for application.
 *
 * @return number of retention registers.
 */
size_t ZAF_retention_register_count(void);

/**
 * @} // RETENTIONREGISTER
 * @} // ZAF
 */

#endif /* ZAF_RETENTION_REGISTER_H_ */
