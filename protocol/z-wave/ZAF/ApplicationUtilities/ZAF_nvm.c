/**
 * @file
 * @brief ZAF FileSystem module
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */
#include "ZAF_nvm.h"

static zpal_nvm_handle_t zaf_handle;

bool ZAF_nvm_init(void)
{
  zaf_handle = zpal_nvm_init(ZPAL_NVM_AREA_ZAF);

  return zaf_handle ? true : false;
}

bool ZAF_nvm_erase(void)
{
  return (ZPAL_STATUS_OK  == zpal_nvm_erase_all(zaf_handle));
}

zpal_status_t ZAF_nvm_erase_object(zpal_nvm_object_key_t key)
{
  return zpal_nvm_erase_object(zaf_handle, key);
}

zpal_status_t ZAF_nvm_read(zpal_nvm_object_key_t key, void *object, size_t object_size)
{
  return zpal_nvm_read(zaf_handle, key, object, object_size);
}

zpal_status_t ZAF_nvm_read_object_part(zpal_nvm_object_key_t key, void *object, size_t offset, size_t size)
{
  return zpal_nvm_read_object_part(zaf_handle, key, object, offset, size);
}

zpal_status_t ZAF_nvm_write(zpal_nvm_object_key_t key, const void *object, size_t object_size)
{
  return zpal_nvm_write(zaf_handle, key, object, object_size);
}

zpal_status_t ZAF_nvm_get_object_size(zpal_nvm_object_key_t key, size_t *len)
{
  return zpal_nvm_get_object_size(zaf_handle, key, len);
}
