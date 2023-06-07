/**
 * @file
 * User Code IO abstraction.
 *
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef CC_USERCODE_IO_H
#define CC_USERCODE_IO_H

#include <CC_UserCode.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup UserCode
 * @{
 */

void CC_UserCode_Migrate();

bool CC_UserCode_Write(uint8_t identifier, SUserCode *userCodeData);

bool CC_UserCode_Read(uint8_t identifier, SUserCode *userCodeData);

/**
 * @}
 * @}
 */ 

#endif /* CC_USERCODE_IO_H */
