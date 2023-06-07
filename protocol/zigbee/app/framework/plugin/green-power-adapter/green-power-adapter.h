/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef _SILABS_GREEN_POWER_ADAPTER_H_
#define _SILABS_GREEN_POWER_ADAPTER_H_

#include "zap-command.h"
#include "zap-id.h"
#include "zap-type.h"
#include "zap-enabled-incoming-commands.h"
#include "zap-command-structs.h"
#include "zap-cluster-command-parser.h"
#include "sl_service_function.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

#ifdef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "zcl-framework-core-config.h"
#endif // SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT

#include "green-power-adapter-config.h"

#endif // SL_COMPONENT_CATALOG_PRESENT

#include "green-power-stack-wrapper.h"
#include "green-power-print-wrapper.h"
#include "green-power-token-wrapper.h"
#include "green-power-event-wrapper.h"
#include "green-power-af-wrapper.h"

#endif //_SILABS_GREEN_POWER_ADAPTER_H_
