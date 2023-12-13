/***************************************************************************//**
 * @file
 * @brief sl_btmesh_ctl_client.h
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_BTMESH_CTL_CLIENT_H
#define SL_BTMESH_CTL_CLIENT_H

/***************************************************************************//**
 * This function changes the temperature and send it to the server.
 *
 * @param[in] temperature_percent Defines new color temperature value as percentage
 *                                Valid values 0-100 %
 ******************************************************************************/
void sl_btmesh_ctl_client_set_temperature(uint8_t temperature_percent);

/***************************************************************************//**
 * This function changes the lightness and send it to the server.
 *
 * @param[in] lightness_percent Defines new lightness value as percentage
 *                              Valid values 0-100 %
 ******************************************************************************/
void sl_btmesh_ctl_client_set_lightness(uint8_t lightness_percent);

#endif // SL_BTMESH_CTL_CLIENT_H
