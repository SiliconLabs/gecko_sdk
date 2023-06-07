/**
 * @file
 * Command Class User Code I/O handling with NVM
 * @copyright 2022 Silicon Laboratories Inc.
 */
#include <string.h>

#include <cc_user_code_io.h>
#include <cc_user_code_config.h>

#include <ZAF_nvm_app.h>
#include <ZAF_nvm.h>
#include <ZAF_file_ids.h>
#include <zpal_nvm.h>
#include <zpal_misc.h>
#include <Assert.h>
//#define DEBUGPRINT
#include "DebugPrint.h"

#define CC_USER_CODE_FILE_OFFSET(a) (ZAF_FILE_ID_CC_USER_CODE_BASE + a)

bool
CC_UserCode_Write(uint8_t identifier, SUserCode *userCodeData)
{
  zpal_status_t status;

  // Make sure identifier is valid
  if (identifier == 0 || identifier > CC_USER_CODE_MAX_IDS) {
    return false;
  }

  status = ZAF_nvm_write(CC_USER_CODE_FILE_OFFSET(identifier - 1), userCodeData, sizeof(SUserCode));

  return status == ZPAL_STATUS_OK;
}

bool
CC_UserCode_Read(uint8_t identifier, SUserCode *userCodeData)
{
  zpal_status_t status;

  // Make sure identifier is valid
  if (identifier == 0 || identifier > CC_USER_CODE_MAX_IDS) {
    return false;
  }

  status = ZAF_nvm_read(CC_USER_CODE_FILE_OFFSET(identifier - 1), userCodeData, sizeof(SUserCode));

  return status == ZPAL_STATUS_OK;
}

void
CC_UserCode_Migrate()
{
  #ifdef ZW_MIGRATION_TO_7_19
  uint8_t i;
  zpal_status_t status;
  SUserCode userCodeData[CC_USER_CODE_MAX_IDS];

  // Migration needed for all apps before 7.19.0
  status = ZAF_nvm_read(ZAF_FILE_ID_USERCODE, userCodeData, sizeof(userCodeData));
  // If the file is not present, we don't have anything to migrate
  if (status != ZPAL_STATUS_OK) {
    return;
  }

  for (i = 0; i < CC_USER_CODE_MAX_IDS; i++) {
    ZAF_nvm_write(CC_USER_CODE_FILE_OFFSET(i), &userCodeData[i], sizeof(userCodeData[i]));
  }

  ZAF_nvm_erase_object(ZAF_FILE_ID_USERCODE);

  #endif // 7.19 migration code block
}
