/**
 * @file
 * @brief Application FileSystem module
 *
 * @copyright 2022 Silicon Laboratories Inc.
 */
#include "ZAF_nvm_app.h"

static zpal_nvm_handle_t app_handle;

bool ZAF_nvm_app_init(void)
{
  app_handle = zpal_nvm_init(ZPAL_NVM_AREA_APPLICATION);

  return app_handle ? true : false;
}

bool ZAF_nvm_app_erase(void)
{
  return (ZPAL_STATUS_OK  == zpal_nvm_erase_all(app_handle));
}

zpal_status_t ZAF_nvm_app_erase_object(zpal_nvm_object_key_t key)
{
  return zpal_nvm_erase_object(app_handle, key);
}

zpal_status_t ZAF_nvm_app_read(zpal_nvm_object_key_t key, void *object, size_t object_size)
{
  return zpal_nvm_read(app_handle, key, object, object_size);
}

zpal_status_t ZAF_nvm_app_read_object_part(zpal_nvm_object_key_t key, void *object, size_t offset, size_t size)
{
  return zpal_nvm_read_object_part(app_handle, key, object, offset, size);
}

zpal_status_t ZAF_nvm_app_write(zpal_nvm_object_key_t key, const void *object, size_t object_size)
{
  return zpal_nvm_write(app_handle, key, object, object_size);
}

zpal_status_t ZAF_nvm_app_get_object_size(zpal_nvm_object_key_t key, size_t *len)
{
  return zpal_nvm_get_object_size(app_handle, key, len);
}
