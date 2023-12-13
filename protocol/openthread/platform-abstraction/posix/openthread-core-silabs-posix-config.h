/*
 *  Copyright (c) 2017, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file includes all compile-time configuration constants used by SiLabs POSIX builds.
 *
 *   To use this configuration in your POSIX builds, copy this file into the following folder:
 *   <openthread_location>/src/posix/platform/
 */

#ifndef OPENTHREAD_CORE_SILABS_POSIX_CONFIG_H_
#define OPENTHREAD_CORE_SILABS_POSIX_CONFIG_H_

/******************************************************************************
 * Recommended setup strings for Thread certified Silicon Labs OTBRs
 *****************************************************************************/

/****************************
 * 1.3 certified OTBR
 ****************************/

/*
sudo RELEASE=1 REFERENCE_DEVICE=1 BACKBONE_ROUTER=1 NAT64=1 DNS64=1 \
     ./script/bootstrap

sudo INFRA_IF_NAME=eth0 \
     RELEASE=1 REFERENCE_DEVICE=1 BACKBONE_ROUTER=1 BORDER_ROUTING=1 NAT64=1 DNS64=1 \
     OTBR_OPTIONS="-DOT_THREAD_VERSION=1.3 \
                   -DOT_PLATFORM_CONFIG=openthread-core-silabs-posix-config.h \
                   -DOTBR_DUA_ROUTING=ON -DOTBR_DNSSD_DISCOVERY_PROXY=ON -DOTBR_SRP_ADVERTISING_PROXY=ON" \
     ./script/setup
*/

/****************************
 * 1.3 certified CPC OTBR
 ****************************/

/*
sudo RELEASE=1 REFERENCE_DEVICE=1 BACKBONE_ROUTER=1 NAT64=1 DNS64=1 \
     ./script/bootstrap

sudo INFRA_IF_NAME=eth0 \
     RELEASE=1 REFERENCE_DEVICE=1 BACKBONE_ROUTER=1 BORDER_ROUTING=1 NAT64=1 DNS64=1 \
     OTBR_OPTIONS="-DOT_THREAD_VERSION=1.3 \
                   -DOT_MULTIPAN_RCP=ON \
                   -DCPCD_SOURCE_DIR=$GSDK_DIR/platform/service/cpc/daemon \
                   -DOT_POSIX_RCP_VENDOR_BUS=ON \
                   -DOT_POSIX_CONFIG_RCP_VENDOR_DEPS_PACKAGE=$GSDK_DIR/protocol/openthread/platform-abstraction/posix/posix_vendor_rcp.cmake \
                   -DOT_POSIX_CONFIG_RCP_VENDOR_INTERFACE=$GSDK_DIR/protocol/openthread/platform-abstraction/posix/cpc_interface.cpp \
                   -DOT_CLI_VENDOR_EXTENSION=$GSDK_DIR/protocol/openthread/platform-abstraction/posix/posix_vendor_cli.cmake \
                   -DOT_PLATFORM_CONFIG=openthread-core-silabs-posix-config.h \
                   -DOTBR_DUA_ROUTING=ON -DOTBR_DNSSD_DISCOVERY_PROXY=ON -DOTBR_SRP_ADVERTISING_PROXY=ON" \
     ./script/setup
*/

/****************************
 * 1.2 certified OTBR
 ****************************/

/*
sudo RELEASE=1 REFERENCE_DEVICE=1 BACKBONE_ROUTER=1 NAT64=0 DNS64=0 \
     ./script/bootstrap

sudo INFRA_IF_NAME=eth0 RELEASE=1 REFERENCE_DEVICE=1 BACKBONE_ROUTER=1 BORDER_ROUTING=0 NAT64=0 DNS64=0 \
     OTBR_OPTIONS="-DOT_THREAD_VERSION=1.2 \
                   -DOT_PLATFORM_CONFIG=openthread-core-silabs-posix-config.h \
                   -DOTBR_DUA_ROUTING=ON -DOTBR_DNSSD_DISCOVERY_PROXY=OFF -DOTBR_SRP_ADVERTISING_PROXY=OFF" \
     ./script/setup
*/

/****************************
 * 1.2 certified CPC OTBR
 ****************************/

/*
sudo RELEASE=1 REFERENCE_DEVICE=1 BACKBONE_ROUTER=1 NAT64=0 DNS64=0 \
     ./script/bootstrap

sudo INFRA_IF_NAME=eth0 RELEASE=1 REFERENCE_DEVICE=1 BACKBONE_ROUTER=1 BORDER_ROUTING=0 NAT64=0 DNS64=0 \
     OTBR_OPTIONS="-DOT_THREAD_VERSION=1.2 \
                   -DOT_MULTIPAN_RCP=ON \
                   -DCPCD_SOURCE_DIR=$GSDK_DIR/platform/service/cpc/daemon \
                   -DOT_POSIX_RCP_VENDOR_BUS=ON \
                   -DOT_POSIX_CONFIG_RCP_VENDOR_DEPS_PACKAGE=$GSDK_DIR/protocol/openthread/platform-abstraction/posix/posix_vendor_rcp.cmake \
                   -DOT_POSIX_CONFIG_RCP_VENDOR_INTERFACE=$GSDK_DIR/protocol/openthread/platform-abstraction/posix/cpc_interface.cpp \
                   -DOT_CLI_VENDOR_EXTENSION=$GSDK_DIR/protocol/openthread/platform-abstraction/posix/posix_vendor_cli.cmake \
                   -DOT_PLATFORM_CONFIG=openthread-core-silabs-posix-config.h \
                   -DOTBR_DUA_ROUTING=ON -DOTBR_DNSSD_DISCOVERY_PROXY=OFF -DOTBR_SRP_ADVERTISING_PROXY=OFF"  \
        ./script/setup
*/

/******************************************************************************
 * Vendor defaults
 *****************************************************************************/
/**
 * OPENTHREAD_POSIX_CONFIG_SPINEL_VENDOR_INTERFACE_URL_PROTOCOL_NAME
 *
 * Define the URL protocol name of our vendor Spinel interface, which is CPC
 *
 */
#ifndef OPENTHREAD_POSIX_CONFIG_SPINEL_VENDOR_INTERFACE_URL_PROTOCOL_NAME
#define OPENTHREAD_POSIX_CONFIG_SPINEL_VENDOR_INTERFACE_URL_PROTOCOL_NAME "spinel+cpc"
#endif

/**
 * Provide radio url help message for vendor RCP bus configuration
 *
 * This supports Multipan/CPC configurations:
 * (OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE &&
 *  OPENTHREAD_POSIX_CONFIG_SPINEL_VENDOR_INTERFACE_ENABLE)
 *
 * Unfortunately this file is included prior to OPENTHREAD_POSIX_CONFIG_SPINEL_VENDOR_INTERFACE_ENABLE
 * being defined so we can't check here.
 */
#define OT_VENDOR_RADIO_URL_HELP_BUS                                 \
    "    spinel+cpc://cpcd_0?${Parameters} for connecting to cpcd\n" \
    "Parameters:\n"                                                  \
    "    cpc-bus-speed[=speed]         CPC bus speed used for communicating with RCP.\n"

/******************************************************************************
 * CLI Interpreter defaults
 *****************************************************************************/

/**
 * Default to 2 to allow adding cli user commands in addition to posix commands
 */

#ifndef OPENTHREAD_CONFIG_CLI_MAX_USER_CMD_ENTRIES
#define OPENTHREAD_CONFIG_CLI_MAX_USER_CMD_ENTRIES 2
#endif

/******************************************************************************
 * Stack / MAC defaults for OTBR
 *****************************************************************************/

#ifndef OPENTHREAD_CONFIG_THREAD_VERSION
#define OPENTHREAD_CONFIG_THREAD_VERSION OT_THREAD_VERSION_1_3
#endif

/**
 * OPENTHREAD_CONFIG_DUA_ENABLE
 *
 * Define as 1 to support Thread 1.2 Domain Unicast Address feature.
 *
 */
#undef OPENTHREAD_CONFIG_DUA_ENABLE
#define OPENTHREAD_CONFIG_DUA_ENABLE (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)

/**
 * OPENTHREAD_CONFIG_MLR_ENABLE
 *
 * Define as 1 to support Thread 1.2 Multicast Listener Registration feature.
 *
 */
#undef OPENTHREAD_CONFIG_MLR_ENABLE
#define OPENTHREAD_CONFIG_MLR_ENABLE (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)

/**
 * OPENTHREAD_CONFIG_BORDER_ROUTING_ENABLE
 *
 * Define to 1 to enable Border Routing Manager feature.
 *
 */
#undef OPENTHREAD_CONFIG_BORDER_ROUTING_ENABLE
#define OPENTHREAD_CONFIG_BORDER_ROUTING_ENABLE (OPENTHREAD_CONFIG_THREAD_VERSION == OT_THREAD_VERSION_1_3)

/**
 * OPENTHREAD_CONFIG_DHCP6_CLIENT_ENABLE
 *
 * Define to 1 to enable DHCPv6 Client support.
 *
 */
#undef OPENTHREAD_CONFIG_DHCP6_CLIENT_ENABLE
#define OPENTHREAD_CONFIG_DHCP6_CLIENT_ENABLE (OPENTHREAD_CONFIG_THREAD_VERSION == OT_THREAD_VERSION_1_3)

/**
 * OPENTHREAD_CONFIG_DHCP6_SERVER_ENABLE
 *
 * Define to 1 to enable DHCPv6 Server support.
 *
 */
#undef OPENTHREAD_CONFIG_DHCP6_SERVER_ENABLE
#define OPENTHREAD_CONFIG_DHCP6_SERVER_ENABLE (OPENTHREAD_CONFIG_THREAD_VERSION == OT_THREAD_VERSION_1_3)

/**
 * OPENTHREAD_CONFIG_SRP_CLIENT_ENABLE
 *
 * Define to 1 to enable SRP Client support.
 *
 */
#undef OPENTHREAD_CONFIG_SRP_CLIENT_ENABLE
#define OPENTHREAD_CONFIG_SRP_CLIENT_ENABLE (OPENTHREAD_CONFIG_THREAD_VERSION == OT_THREAD_VERSION_1_3)

/**
 * OPENTHREAD_CONFIG_RADIO_LINK_TREL_ENABLE
 *
 * Set to 1 to enable support for Thread Radio Encapsulation Link (TREL).
 *
 */
#undef OPENTHREAD_CONFIG_RADIO_LINK_TREL_ENABLE
#define OPENTHREAD_CONFIG_RADIO_LINK_TREL_ENABLE (OPENTHREAD_CONFIG_THREAD_VERSION == OT_THREAD_VERSION_1_3)

/**
 * OPENTHREAD_CONFIG_MLE_MAX_CHILDREN
 *
 * The maximum number of children, set on the OTBR host.
 *
 * On the host, the value determines the size of the child table.
 * On the RCP, this is used for frame pending lookup for indirect messaging.
 *
 * If the host value <= RCP value, then the OTBR primarily defaults to the host
 * value. It won’t allow more than that number of children to join the network.
 *
 * If the host value > RCP value, then the OTBR still defaults to the host value
 * and allows that many children — however, it cannot buffer messages for more
 * than the RCP number. This is because it cannot do frame pending lookup.
 *
 * Note that the default RCP value is 10 (src/core/config/mle.h), so this means:
 * The OTBR can have 128 children, but cannot simultaneously buffer messages for
 * more than 10 sleepy children at once.
 *
 */
#undef OPENTHREAD_CONFIG_MLE_MAX_CHILDREN
#define OPENTHREAD_CONFIG_MLE_MAX_CHILDREN 128

/**
 * OPENTHREAD_CONFIG_MAC_CSL_REQUEST_AHEAD_US
 *
 * Define how many microseconds ahead should MAC deliver CSL frame to SubMac.
 *
 * This value is a higher on the OTBR than the stack default.
 *
 */
#undef OPENTHREAD_CONFIG_MAC_CSL_REQUEST_AHEAD_US
#define OPENTHREAD_CONFIG_MAC_CSL_REQUEST_AHEAD_US 5000

/**
 * OPENTHREAD_CONFIG_CSL_TRANSMIT_TIME_AHEAD
 *
 * Transmission scheduling and ramp up time needed for the CSL transmitter
 * to be ready, in units of microseconds. This time must include at least
 * the radio's turnaround time between end of CCA and start of preamble
 * transmission. To avoid early CSL transmission it also must not be configured
 * higher than the actual scheduling and ramp up time.
 *
 * Same as stack default, but can change if needed for OTBR as CSL transmitter.
 */
#undef OPENTHREAD_CONFIG_CSL_TRANSMIT_TIME_AHEAD
#define OPENTHREAD_CONFIG_CSL_TRANSMIT_TIME_AHEAD 40

/******************************************************************************
 * MultiPan RCP (CPC) defaults
 *****************************************************************************/

/**
 * Define to 1 to enable multipan RCP support.
 */
#ifndef OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE
#define OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE 0
#endif

#if OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE

/**
 * Force disable max power table support.
 *
 */
#undef OPENTHREAD_POSIX_CONFIG_MAX_POWER_TABLE_ENABLE
#define OPENTHREAD_POSIX_CONFIG_MAX_POWER_TABLE_ENABLE 0

/**
 * Force disable Channel Manager support.
 *
 */
#undef OPENTHREAD_CONFIG_CHANNEL_MANAGER_ENABLE
#define OPENTHREAD_CONFIG_CHANNEL_MANAGER_ENABLE 0

/**
 * Force diable Channel Monitor support.
 *
 */
#undef OPENTHREAD_CONFIG_CHANNEL_MONITOR_ENABLE
#define OPENTHREAD_CONFIG_CHANNEL_MONITOR_ENABLE 0

#endif // OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE

/******************************************************************************
 * Proprietary SubGhz defaults
 *****************************************************************************/

/**
 * Define to 1 if you want to enable proprietary radio support as defined by platform.
 *
 * @note If this setting is set to 1, the channel range is defined by the platform. Choosing this option requires
 * the following configuration options to be defined by Platform:
 * OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_PAGE,
 * OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MIN,
 * OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MAX and,
 * OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MASK.
 *
 */
#ifndef OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_SUPPORT
#ifndef OPENTHREAD_CONFIG_RADIO_915MHZ_OQPSK_SUPPORT
#ifndef OPENTHREAD_CONFIG_RADIO_2P4GHZ_OQPSK_SUPPORT
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_SUPPORT 0
#define OPENTHREAD_CONFIG_RADIO_915MHZ_OQPSK_SUPPORT         0
#define OPENTHREAD_CONFIG_RADIO_2P4GHZ_OQPSK_SUPPORT         1
#endif
#endif
#endif

#if OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_SUPPORT

#undef OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_PAGE
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_PAGE 23

#undef OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MIN
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MIN 0

#undef OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MAX
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MAX 24

#undef OPENTHREAD_CONFIG_DEFAULT_CHANNEL
#define OPENTHREAD_CONFIG_DEFAULT_CHANNEL OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MIN

#undef OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MASK
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MASK 0x1ffffff

/**
 * Force disable OQPSK modulation in 915MHz frequency band. The physical layer parameters are defined in
 * section 6 of IEEE802.15.4-2006.
 *
 */
#undef OPENTHREAD_CONFIG_RADIO_915MHZ_OQPSK_SUPPORT
#define OPENTHREAD_CONFIG_RADIO_915MHZ_OQPSK_SUPPORT 0

/**
 * Force disable OQPSK modulation in 2.4GHz frequency band. The physical layer parameters are defined in
 * section 6 of IEEE802.15.4-2006.
 *
 */
#undef OPENTHREAD_CONFIG_RADIO_2P4GHZ_OQPSK_SUPPORT
#define OPENTHREAD_CONFIG_RADIO_2P4GHZ_OQPSK_SUPPORT 0

/**
 * Define to enable platform logging and `otLog{Level}Plat()` OT functions.
 *
 */
#undef OPENTHREAD_CONFIG_LOG_PLATFORM
#define OPENTHREAD_CONFIG_LOG_PLATFORM 1

#endif // OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_SUPPORT

/******************************************************************************
 * Project defaults
 *
 * See also ot-br-posix/third_party/openthread/CMakeLists.txt for other defaults
 *****************************************************************************/

/**
 * Define to 1 to enable Factory Diagnostics support.
 *
 */
#undef OPENTHREAD_CONFIG_DIAG_ENABLE
#define OPENTHREAD_CONFIG_DIAG_ENABLE 1

/**
 * The log level (used at compile time). If `OPENTHREAD_CONFIG_LOG_LEVEL_DYNAMIC_ENABLE` is set, this defines the most
 * verbose log level possible. See `OPENTHREAD_CONFIG_LOG_LEVEL_INIT` to set the initial log level.
 *
 */
#undef OPENTHREAD_CONFIG_LOG_LEVEL
#define OPENTHREAD_CONFIG_LOG_LEVEL OT_LOG_LEVEL_DEBG

/**
 * Define to prepend the log level to all log messages.
 *
 */
#undef OPENTHREAD_CONFIG_LOG_PREPEND_LEVEL
#define OPENTHREAD_CONFIG_LOG_PREPEND_LEVEL 1

/**
 * Defines the max count of RCP failures allowed to be recovered.
 * 0 means to disable RCP failure recovering.
 *
 */
#undef OPENTHREAD_SPINEL_CONFIG_RCP_RESTORATION_MAX_COUNT
#define OPENTHREAD_SPINEL_CONFIG_RCP_RESTORATION_MAX_COUNT 100

/**
 * Define to enable CLI logging and `otLogCli()` OT function.
 *
 */
#undef OPENTHREAD_CONFIG_LOG_CLI
#define OPENTHREAD_CONFIG_LOG_CLI 0

/******************************************************************************
 * Include OpenThread project's POSIX defaults
 *****************************************************************************/
#include "openthread-core-posix-config.h"

#endif // OPENTHREAD_CORE_SILABS_POSIX_CONFIG_H_
