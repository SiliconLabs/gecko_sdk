/**
 * @file
 * Configuration API for CC Multi Channel
 *
 * @copyright 2023 Silicon Laboratories Inc.
 */
#ifndef CC_MULTI_CHANNEL_CONFIG_API_H_
#define CC_MULTI_CHANNEL_CONFIG_API_H_

#include <stdbool.h>
#include <stdint.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup Multichan
 * @{
 */

typedef struct {
  uint8_t generic_type;
  uint8_t specific_type;
}
cc_multi_channel_config_t;

cc_multi_channel_config_t const * cc_multi_channel_get_config(void);

cc_multi_channel_config_t const * cc_multi_channel_get_config_endpoint(uint8_t endpoint);

bool cc_multi_channel_are_endpoints_identical(void);

/**
 * @}
 * @}
 */

#endif /* CC_MULTI_CHANNEL_CONFIG_API_H_ */
