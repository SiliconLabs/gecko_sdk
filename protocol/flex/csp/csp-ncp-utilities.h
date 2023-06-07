/***************************************************************************//**
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef __CSP_NCP_UTILITIES_H__
#define __CSP_NCP_UTILITIES_H__

// Pre/post hooks allow for special handling before/after the default behavior
// of generated NCP command handler/return code.

bool cspNcpLaunchStandaloneBootloaderPreHook(uint8_t mode);

#endif //__CSP_NCP_UTILITIES_H__
