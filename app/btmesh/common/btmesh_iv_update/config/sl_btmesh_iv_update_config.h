/***************************************************************************//**
 * @file
 * @brief IV Update Component Configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#ifndef SL_BTMESH_IV_UPDATE_CONFIG_H
#define SL_BTMESH_IV_UPDATE_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <q SL_BTMESH_IV_UPDATE_LOGGING_CFG_VAL> Enable logging
// <d> 1
#define SL_BTMESH_IV_UPDATE_LOGGING_CFG_VAL 1

// <q SL_BTMESH_IV_UPDATE_AUTO_RECOVERY> Automatic transition to IV Update Recovery mode
// <d> 1
#define SL_BTMESH_IV_UPDATE_AUTO_RECOVERY 1

// <e SL_BTMESH_IV_UPDATE_AGE_BACKUP_ENABLE> Backup of IV Update age
// <d> 1
#define SL_BTMESH_IV_UPDATE_AGE_BACKUP_ENABLE 1

// <o SL_BTMESH_IV_UPDATE_AGE_NVM_KEY_CFG_VAL>NVM key of the iv Update age (hexadecimal)<f.h>
// <d> 0x3000
#define SL_BTMESH_IV_UPDATE_AGE_NVM_KEY_CFG_VAL 0x3000

// <o SL_BTMESH_IV_UPDATE_AGE_BACKUP_PERIOD_S>IV Update age backup period in seconds<0..4294967>
// <d> 300
#define SL_BTMESH_IV_UPDATE_AGE_BACKUP_PERIOD_S 300

// </e>

// <e SL_BTMESH_IV_UPDATE_BY_AGE> IV Update by age
// <d> 1
#define SL_BTMESH_IV_UPDATE_BY_AGE 1

// <o SL_BTMESH_IV_UPDATE_FIX_TIMEOUT_S>IV Update Timeout<345600..4294967>
// <d> 345600
#define SL_BTMESH_IV_UPDATE_FIX_TIMEOUT_S 345600

// </e>

// <e SL_BTMESH_IV_UPDATE_BY_SEQ_NUM> IV Update by sequence number
// <d> 1
#define SL_BTMESH_IV_UPDATE_BY_SEQ_NUM 1

// <o SL_BTMESH_IV_UPDATE_SEQ_NUM_THRESHOLD> Sequence number threshold<0..16777215>
// <d> 0x700000
// <i> When any element's sequence number gets above this, an IV Update is requested.
#define SL_BTMESH_IV_UPDATE_SEQ_NUM_THRESHOLD 0x700000

// <o SL_BTMESH_IV_UPDATE_SEQ_NUM_TESTING_PERIOD_S> Sequence number testing period in seconds <0..4294967>
// <d> 10
#define SL_BTMESH_IV_UPDATE_SEQ_NUM_TESTING_PERIOD_S 10

// </e>

// <<< end of configuration section >>>
#endif
