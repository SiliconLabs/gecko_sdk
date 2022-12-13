/**
 * @file
 * @brief Defines file system for application.
 *
 * @details The module contains a zpal_nvm_handle_t that defines the file system
 * for the application. A pointer to the handle is passed as output parameter
 * from ZAF_nvm_app_init(). There are also functions for verifying
 * that the file system contains the files that are expected.
 *
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef ZAF_APPLICATIONUTILITIES_NVM_APP_H_
#define ZAF_APPLICATIONUTILITIES_NVM_APP_H_

#include <stdbool.h>
#include <zpal_nvm.h>

/**
 * @addtogroup ZAF
 * @{
 * @addtogroup NVM
 * @{
 */

/**
 * @brief Opens file system for application
 *
 * @return bool true if zpal_nvm_init() succeeded else false.
 */
bool ZAF_nvm_app_init(void);

/**
 * @brief Erases application nvm. (Does nothing on 800s since it has 1 shared nvm for application and protocol.)
 *
 * @return true on successful erase
 */
bool ZAF_nvm_app_erase(void);

/**
 * @brief Erases an object from application nvm.
 *
 * @param[in]  key            Object key.
 * @return status of erase operation
 */
zpal_status_t ZAF_nvm_app_erase_object(zpal_nvm_object_key_t key);

/**
 * @brief Reads an object from application nvm.
 *
 * @param[in]  key            Object key.
 * @param[out] object         Address of array where object can be written to.
 * @param[in]  object_size    Size of the stored object.
 * @return status of read operation
 */
zpal_status_t ZAF_nvm_app_read(zpal_nvm_object_key_t key, void *object, size_t object_size);

/**
 * @brief Reads part of an object from application nvm.
 *
 * @param[in]  key          Object key.
 * @param[out] object       Address of array where part of object can be written to.
 * @param[in]  offset       The offset in object where part shall be read from.
 * @param[in]  size         Size of the object part.
 * @return status of read operation
 */
zpal_status_t ZAF_nvm_app_read_object_part(zpal_nvm_object_key_t key, void *object, size_t offset, size_t size);

/**
 * @brief Writes an object to application nvm.
 *
 * @param[in]  key          Object key.
 * @param[out] object       Address of array of object that is written.
 * @param[in]  object_size  Size of the stored object.
 * @return status of write operation
 */
zpal_status_t ZAF_nvm_app_write(zpal_nvm_object_key_t key, const void *object, size_t object_size);

/**
 * @brief Get the object size identified with a given key from NVM.
 *
 * @param[in]   key     Object key.
 * @param[out]  len     Object size.
 * @return status of operation
 */
zpal_status_t ZAF_nvm_app_get_object_size(zpal_nvm_object_key_t key, size_t *len);

/**
 * @} // NVM
 * @} // ZAF
 */

#endif /* ZAF_APPLICATIONUTILITIES_NVM_APP_H_ */
