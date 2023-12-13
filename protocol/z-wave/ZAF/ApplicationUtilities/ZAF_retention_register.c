/**
 * @file
 * @copyright 2023 Silicon Laboratories Inc.
 */
#include <zpal_retention_register.h>
#include "AppTimer.h"
#include "ZAF_retention_register.h"

#define RESERVED_COUNT (ZPAL_RETENTION_REGISTER_PROTOCOL_RESERVED_COUNT + APP_TIMER_RETENTION_REGISTER_RESERVED_COUNT)

zpal_status_t ZAF_retention_register_read(uint32_t index, uint32_t *data)
{
  return zpal_retention_register_read(index + RESERVED_COUNT, data);
}

zpal_status_t ZAF_retention_register_write(uint32_t index, uint32_t value)
{
  return zpal_retention_register_write(index + RESERVED_COUNT, value);
}

size_t ZAF_retention_register_count(void)
{
  return zpal_retention_register_count() - RESERVED_COUNT;
}
