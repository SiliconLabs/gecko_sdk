/***************************************************************************//**
 * @file
 * @brief FTP (File Transfer Protocol) configuration header.
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
#ifndef SL_FTP_CONFIG_H
#define SL_FTP_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> File Transfer protocol general configuration

// <q SL_FTP_ENABLE_FTP_PROTOCOL> Enable FTP TCP based protocol
// <i> Default value: 1
#define SL_FTP_ENABLE_FTP_PROTOCOL                  0U

// <q SL_FTP_ENABLE_TFTP_PROTOCOL> Enable TFTP UDP based protocol
// <i> Default value: 1
#define SL_FTP_ENABLE_TFTP_PROTOCOL                 1U
// </h>

// <h> File Transfer protocol (TCP) configuration
#if SL_FTP_ENABLE_FTP_PROTOCOL

// <o SL_FTP_CLNT_STACK_SIZE_WORD> FTP Client service stack size in word
// <i> Default value 256 bytes
#define SL_FTP_CLNT_STACK_SIZE_WORD                 256UL

// <q SL_FTP_CLNT_DEFAULT_BUFF_ENABLE> Enable FTP default static buffers for Control and Data channels
// <i> Default value: 1
#define SL_FTP_CLNT_DEFAULT_BUFF_ENABLE             1U

#if SL_FTP_CLNT_DEFAULT_BUFF_ENABLE

// <o SL_FTP_CLNT_CTRL_BUFF_SIZE> FTP default (static) control buffer size (bytes)
// <i> Default value 512 bytes
#define SL_FTP_CLNT_CTRL_BUFF_SIZE                  512UL

// <o SL_FTP_CLNT_DATA_BUFF_SIZE> FTP default (static) data buffer size (bytes)
// <i> Default value 512 bytes
#define SL_FTP_CLNT_DATA_BUFF_SIZE                  512UL
#endif

// <o SL_FTP_CLNT_RECV_TIMEOUT_MS> FTP default receive timeout (ms)
// <i> Default value 20000 ms
#define SL_FTP_CLNT_RECV_TIMEOUT_MS                 20000UL

// <s SL_FTP_CLNT_AUTH_DEFAUL_HOST> FTP Default remote host address string
// <i> Default: "aabb:ccdd::eeff:0011:2233:4455" (dummy)
#define SL_FTP_CLNT_AUTH_DEFAUL_HOST                "aabb:ccdd::eeff:0011:2233:4455"

// <s SL_FTP_CLNT_AUTH_DEFAUL_HOST> FTP Default user name
// <i> Default: "user" (dummy)
#define SL_FTP_CLNT_AUTH_DEFAULT_USER               "user"

// <s SL_FTP_CLNT_AUTH_DEFAUL_HOST> FTP Default password
// <i> Default: "password" (dummy)
#define SL_FTP_CLNT_AUTH_DEFAULT_PASSWORD           "password"

#endif
// </h>

// <h> Trivial File Transfer protocol (UDP) configuration
#if SL_FTP_ENABLE_TFTP_PROTOCOL

// <o SL_TFTP_CLNT_STACK_SIZE_WORD> TFTP Client service stack size in word
// <i> Default value 256 bytes
#define SL_TFTP_CLNT_STACK_SIZE_WORD                 256UL

// <o SL_TFTP_ADDR_SIZE> TFTP address storage size in bytes
// <i> Default value 20 bytes
#define SL_TFTP_ADDR_SIZE                            28UL

// <s SL_TFTP_CLNT_DEFAULT_HOST> TFTP Default remote host address string
// <i> Default: "aabb:ccdd::eeff:0011:2233:4455" (dummy)
#define SL_TFTP_CLNT_DEFAULT_HOST                   "aabb:ccdd::eeff:0011:2233:4455"

// <o SL_TFTP_CLNT_RECV_TIMEOUT_MS> TFTP default receive timeout (ms)
// <i> Default value 20000 ms
#define SL_TFTP_CLNT_RECV_TIMEOUT_MS                 20000UL

#endif
// </h>

// <<< end of configuration section >>>

#endif
