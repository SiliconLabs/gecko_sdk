# Copyright 2022 Silicon Laboratories Inc. www.silabs.com
#
# SPDX-License-Identifier: Zlib
#
# The licensor of this software is Silicon Laboratories Inc.
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

import dataclasses
import io
import logging
import re
from configparser import ConfigParser, ExtendedInterpolation, SectionProxy
from pathlib import Path
from typing import Dict, Iterable, List, Set

import btmesh.util
from btmesh.db import ModelID
from btmesh.mdl import NamedModelID
from btmesh.util import (BtmeshMulticastRetryParams, BtmeshRetryParams,
                         ConnectionParamsRange)

DEFAULT_APP_CFG_INI = """# BT Mesh Host DFU configuration file

[appgroup]
# Automatic binding or unbinding of an appkey to model of an element in the app
# group when the publication or subscription is configured on the model.
# If it is true then the automatic binding is enabled by default.
auto_bind_default = true

# Strict DCD check raises an error when a model which shall be configured
# (publication, subscription, binding) does not exist on the specified element
# address based on the DCD.
# If it is true then the strict DCD check is enabled by default.
dcd_check_default = false

# Publication Time-To-Live default value of the app group.
# Valid publication TTL range is 0 or [2,127]. The special 255 value can be set to
# use default TTL of the node.
pub_ttl_default = 5

# Publication default friendship credential flag of the app group.
# If zero, publication is done using normal credentials.
# If one, it is done with friendship credentials, meaning only the friend can
# decrypt the published message and relay it forward using the normal credentials.
pub_cred_default = 0

# Publication default period in milliseconds of the app group.
# Note that the resolution of the publication period is limited by the
# specification to 100ms up to a period of 6.3s, 1s up to a period of 63s, 10s
# up to a period of 630s, and 10 minutes above that.
# Maximum period allowed is 630 minutes.
pub_period_ms_default = 0

# Publication retransmission count of the app group.
# Valid values range from 0 to 7.
pub_tx_cnt_default = 0

# Publication default retransmission interval in millisecond units of the
# app group. The range of value is 50 to 1600ms, and the resolution of the
# value is 50 milliseconds.
pub_tx_int_ms_default = 0

# App group model profiles make it easier to provide publication, subscription
# and bind model parameters to app group commands. A model profile name refers
# to these model sets.
# The model profile options shall follow the following naming convention:
# - Pattern: profile_<mdl_profile_name>_<postfix>
# - <mdl_profile_name>: It identifies the model profile in app group commands.
# - The <postfix> shall be one of the followings:
#   - pub_mdls: Models from option value are appended to publication models.
#   - sub_mdls: Models from option value are appended to subscription models.
#   - bind_mdls: Models from option value are appended to bind models.
#   - auto_bind: If true then the pub_mdls and sub_mdls are added to bind_mdls.
#                If this option does not exist then it defaults to false.
#   - help: Text added to the command help message.
# - The models shall be separated by commas when more than one is provided.
# - The models can be specified in the following ways:
#   - The SIG model identifier can be specified as a binary (0b), octal(0o),
#     decimal, hex (0x) integer.
#   - The vendor model identifier can be specified as a pair of binary(0b),
#     octal(0o), decimal, hex (0x) integers separated by any special
#     characters (-/:).
#   - The SIG model name can be specified by special model name which contains
#     underscore (_) characters instead of spaces.
profile_target_node_sub_mdls = FIRMWARE_UPDATE_SERVER, BLOB_TRANSFER_SERVER
profile_target_node_auto_bind = true
profile_target_node_help = Configuration for target nodes.

profile_distributor_bind_mdls = FIRMWARE_DISTRIBUTION_SERVER, FIRMWARE_UPDATE_CLIENT,
    BLOB_TRANSFER_CLIENT, BLOB_TRANSFER_SERVER
profile_distributor_auto_bind = true
profile_distributor_help = Configuration for distributor.

profile_lightness_pub_mdls = GENERIC_ONOFF_CLIENT, GENERIC_LEVEL_CLIENT,
    GENERIC_POWER_LEVEL_CLIENT, LIGHT_LIGHTNESS_CLIENT
profile_lightness_sub_mdls = GENERIC_ONOFF_SERVER, GENERIC_LEVEL_SERVER,
    GENERIC_POWER_LEVEL_SERVER, LIGHT_LIGHTNESS_SERVER, LIGHT_LIGHTNESS_SETUP_SERVER
profile_lightness_auto_bind = true
profile_lightness_help = Configuration of Light Lightness Client,
    Light Lightness Server, Light Lightness Setup Server and related
    generic models.


[common]
# Default path of Bluetooth and BT Mesh API xml files.
# The PyBGAPI creates classes, commands and events from xapi files at runtime.
# The app uses the PyBGAPI through the btmesh layer which implements complex
# BT Mesh procedures and provides a simple interface.
# If relative path is provided then the base path is the location of this
# configuration file.
api_xmls_default = ../../../../protocol/bluetooth/api/sl_bt.xapi,
                   ../../../../protocol/bluetooth/api/sl_btmesh.xapi

# Maximum command retry count when the expected event is not received or the
# received event means a recoverable error.
# If the maximum retry count is exceeded and the expected event is not found or
# the received event means the same recoverable error then an error is raised.
# Example: the response message of server is lost due to interference.
# Note: this default value is used unless a more specific configuration option
# overrides it. See <prefix>_retry_max_default parameters in this file.
retry_max_default = 5

# The retry interval is measured between commands in seconds during retry when the
# expected event is not received or the received event means a recoverable error.
# Example: keep some time between message transmissions to wait for the
# response message of the remote node.
# Note: this default value is used unless a more specific configuration option
# overrides it. See <prefix>_retry_interval_default parameters in this file.
retry_interval_default = 1.0

# The retry interval is measured between commands in seconds during retry when the
# expected event is not received or the received event means a recoverable error.
# This retry interval is used when the target node is a Low Power Node or the
# target element address belongs to a Low Power Node.
# Example: keep some time between message transmissions to wait for the response
# message of the remote Low Power Node.
# Note: this default value is used unless a more specific configuration option
# overrides it. See <prefix>_retry_interval_lpn_default parameters in this file.
retry_interval_lpn_default = 5.0

# Maximum command retry count when a command fails due to recoverable error.
# If the max command retry count is exceeded and the command still fails with
# the same recoverable error then an error is raised.
# Example for recoverable error: lack of dynamic memory in BT Mesh stack. "
# Note: this default value is used unless a more specific configuration option
# overrides it. See <prefix>_retry_cmd_max_default parameters in this file.
retry_cmd_max_default = 10

# The retry command interval is measured between commands in seconds during retry
# when the command fails due to recoverable error.
# Example: keep time between commands to wait to free dynamic memory.
# Note: this default value is used unless a more specific configuration option
# overrides it. See <prefix>_retry_cmd_interval_default parameters in this file.
retry_cmd_interval_default = 0.5

# If the number of remaining node elements (element addresses) with missing
# status messages exceeds or equals to the retry multicast threshold then the
# group address is used to send BT Mesh messages, otherwise each element address
# is looped through one by one. Zero value means unicast addressing.
retry_multicast_threshold_default = 2

# If auto unicast retry feature is turned on and the multicast retry procedure
# fails before the number of remaining nodes elements (element addresses) with
# missing status messages goes below the retry multicast threshold then an
# additional unicast retry procedure is executed otherwise the remaining node
# elements fail with timeout.
retry_auto_unicast_default = False


[conf]
# If Strict Auto Configuration is turned on and an auto configuration procedure
# fails with error then an error is raised and the auto configuration is stopped.
# Otherwise the failing configuration procedure is displayed on the UI and the
# auto configuration continues.
auto_conf_strict = true

# Default maximum number of additional Config Node Reset messages which are sent
# until the Config Node Reset Status message is received from the remote node.
# Note: it is possible that the Config Node Reset or Config Node Reset Status
#       message is lost which makes additional retry necessary to make sure that
#       the node receives the message.
reset_node_retry_max_default = 8

# Default interval in seconds between Config Node Reset messages when the Config
# Node Reset Status message is not received from the remote node.
# Warning! The Config Reset Node message is not idempotent completely because
# the remote node resets itself by removing network, device and application keys
# so it is no longer able to respond with Config Reset Node Status messages.
# Therefore, the remote node starts a timer with configurable timeout (default: 2s)
# when it receives Config Reset Node message so it is able to respond while
# the timer is running to additional messages. (see Factory Reset in SOC projects)
reset_node_retry_interval_default = 0.5

# Default interval in seconds between Config Node Reset messages when the Config
# Node Reset Status message is not received from the remote Low Power Node.
reset_node_retry_interval_lpn_default = 5

# If true then the node is removed from the NCP node (provisioner) device database
# and from the application database when the retry max is exceeded otherwise no
# operation is performed.
# Note: if true then it assumes that the remote node received Config Reset Node
#       message and it responded with status message but it was lost due to
#       interference and the node reset itself so it was not able to respond to
#       additional messages and hence retry limit was exceeded.
reset_node_local_remove_on_retry_limit = true

# Default maximum number of additional Config messages which are sent until the
# corresponding status message is not received from the Configuration Server.
# For example: Config Appkey Add, Config Model Publication Set, Config Model
# Subscription Add, Config Model App Bind, Config Composition Data Get, etc.
# Note: this default value is used for BT Mesh Configuration messages unless
# a more specific configuration option overrides it like the Config Reset
# Node message is affected by reset_node_retry_max_default.
conf_retry_max_default = 5

# Default interval in seconds between Config messages when the corresponding
# status message is not received from the Configuration Server.
# For example: Config Appkey Add, Config Model Publication Set, Config Model
# Subscription Add, Config Model App Bind, Config Composition Data Get, etc.
# Note: this default value is used for BT Mesh Configuration messages unless
# a more specific configuration option overrides it like the Config Reset
# Node message is affected by reset_node_retry_interval_default.
conf_retry_interval_default = 1.0

# Default interval in seconds between Config messages when the corresponding
# status message is not received from the Configuration Server model of a
# Low Power Node.
# For example: Config Appkey Add, Config Model Publication Set, Config Model
# Subscription Add, Config Model App Bind, Config Composition Data Get, etc.
# Note: this default value is used for BT Mesh Configuration messages unless
# a more specific configuration option overrides it like the Config Reset
# Node message is affected by reset_node_retry_interval_lpn_default.
conf_retry_interval_lpn_default = 30.0

# Default maximum number of additional Silabs Config Get or Set messages which
# are sent until the Silabs Config Status message is not received from the
# Silabs Config Server.
# Note: The configuration of BT Mesh over Advertisement Extension proprietary
# feature is performed through Silabs Config messages. (see conf ae command)
silabs_retry_max_default = 5

# Default interval in seconds between Silabs Config Get or Set messages when the
# Silabs Config Status message is not received from the Silabs Config Server.
# Note: The configuration of BT Mesh over Advertisement Extension proprietary
# feature is performed through Silabs Config messages. (see conf ae command)
silabs_retry_interval_default = 1.0

# Default interval in seconds between Silabs Config Get or Set messages when the
# Silabs Config Status message is not received from the Silabs Config Server
# model of a Low Power Node.
# Note: The configuration of BT Mesh over Advertisement Extension proprietary
# feature is performed through Silabs Config messages. (see conf ae command)
silabs_retry_interval_lpn_default = 5.0

# Default multicast threshold used during Silabs Configuration procedures.
# If the number of uncompleted Silabs Config Servers with missing Silabs Config
# Status messages during the aforementioned Silabs Configuration procedures
# exceeds or is equal to this number then the group address is used.
# Otherwise, servers are looped through one by one.
# Zero value means unicast addressing.
# Note: The configuration of BT Mesh over Advertisement Extension proprietary
# feature is performed through Silabs Config messages. (see conf ae command)
silabs_retry_multicast_threshold_default = 2

# If DCD Query Auto Configuration option is true then the DCD is queried from
# each node immediately upon their provisioning into the network.
auto_conf_dcd_query = true

# If Default TTL Auto Configuration is true then the Default TTL state is
# configured on each node immediately upon their provisioning into the network.
# The local Default TTL state is configured on the Provisioner as well when
# the network is created.
auto_conf_default_ttl = true

# Default value of Default TTL determines TTL value used when sending messages.
# The Default TTL is applied by the access layer or by the upper transport layer
# unless the application or functionality specifies a TTL.
# Valid value range is from 2 to 127 for relayed PDUs, and 0 for non-relayed PDUs.
default_ttl_default = 5

# Default relay retransmit count controls the number of retransmissions of
# Network PDUs relayed by the node.
# Valid values range from 0 to 7.
relay_retx_count_default = 2

# Default relay retransmit interval in milliseconds controls the interval
# between retransmissions of Network PDUs relayed by the node.
# Valid values range from 10 ms to 320 ms, with a resolution of 10 ms.
relay_retx_interval_ms_default = 10

# If Network Transmit Auto Configuration is true then the Network Transmit state
# is configured with the specific network_tx default configuration options on
# each node immediately upon their provisioning into the network.
# The local Network Transmit state is configured on the Provisioner as well when
# the network is created.
# Network Transmit is a composite state that controls the number and timing of
# the transmissions of Network PDUs originating from a node.
auto_conf_network_tx = true

# Default Network Transmit Count controls the number of transmissions of Network
# PDUs that originate from the node.
# Valid values range from 1 to 8.
network_tx_count_default = 1

# Default interval in milliseconds between network PDU transmissions which
# originates from the same nodes.
# Valid values range from 10 ms to 320 ms, with a resolution of 10 ms.
network_tx_interval_ms_default = 10

# If Segmentation and Reassembly Auto Configuration is true then the SAR
# Transmitter and Receiver states are configured with specific sar_tx and
# sar_rx default configuration options on each node immediately upon their
# provisioning into the network.
# The local SAR Transmitter and Receiver states are configured on the Provisioner
# as well when the network is created.
# The SAR Transmitter state is a composite state that controls the number and
# timing of transmissions of segmented messages.
# The SAR Receiver state is a composite state that controls the number and
# timing of Segment Acknowledgment transmissions and the discarding of
# reassembly of a segmented message.
auto_conf_sar = true

# Default SAR Transmitter Segment Interval Step controls the interval between
# transmissions of segments of a segmented message in milliseconds.
# The value is the range of 10ms to 160ms in 10ms steps, intermediate values are
# rounded down to the nearest multiple of 10.
# Default value is 20ms in specification.
sar_tx_segment_interval_step_default = 20

# Default SAR Transmitter Unicast Retransmission Count controls the maximum number
# of transmissions of segments of segmented messages to a unicast destination.
# Valid range is 0 - 15, where 0 represents a single transmission.
# The default value is 2 in specification, resulting in 3 transmissions total.
sar_tx_unicast_retrans_count_default = 7

# Default SAR Transmitter Unicast Retransmissions Without Progress Count controls
# the maximum number of retransmissions of segments of segmented messages to a
# unicast destination without progress (without marking newly marking any
# segments acknowledged).
# Valid range is 0 - 15, where 0 represents a single transmission.
# The default value is 2 in specification, resulting in 3 transmissions.
# Value of this state should be set to a value greater by two or more than the
# value of the SAR Receiver Acknowledgement Retransmissions Count on a peer node.
# This helps prevent the SAR Transmitter from abandoning the SAR prematurely.
sar_tx_unicast_retrans_wo_progress_count_default = 2

# Default SAR Transmitter Unicast Retransmissions Interval Step state controls
# the minimum interval between retransmissions of segments of a segmented message
# for a destination that is a unicast address in 25ms steps.
# Valid range is 25 - 400ms, intermediate values are rounded down to the nearest
# multiple of 25. Default value is 200ms in specification.
sar_tx_unicast_retrans_interval_step_default = 200

# Default SAR Transmitter Unicast Retransmissions Interval Increment state
# controls the incremental component (TTL) of the interval between retransmissions
# of segments of a segmented message for a destination that is a unicast address
# in 25ms steps.
# Valid range is 25 - 400ms, intermediate values are rounded down to the nearest
# multiple of 25. Default value is 50ms in specification.
sar_tx_unicast_retrans_interval_increment_default = 50

# Default SAR Transmitter Multicast Retransmissions Count state controls the
# maximum number of transmissions of segments of segmented messages to a group
# address or a virtual address.
# Valid range is 0 - 15, where 0 represents a single transmission.
# The default value is 1 in specification, resulting in 2 transmissions.
# WARNING! The BLOB Transfer procedure has a high-level retransmission logic
# which detects missing chunks and retransmits the missing ones.
# It is recommended to disable multicast retransmissions in Lower Transport
# layer in low noise environment because it slows down the multicast BLOB
# Transfer significantly, and consequently multicast retransmissions are
# disabled by default.
# More multicast retransmissions can be beneficial during BLOB Transfer for
# chunks with many segments in noisy environment because one missing chunk
# segment leads to the loss of whole BLOB Chunk Transfer access message.
sar_tx_multicast_retrans_count_default = 0

# Default SAR Transmitter Multicast Retransmissions Interval Step state controls
# the interval between retransmissions of segments of a segmented message for a
# destination that is a group address or a virtual address in 25ms steps.
# Valid range is 25-400ms, intermediate values are rounded down to the nearest
# multiple of 25. Default values is 100ms in specification.
sar_tx_multicast_retrans_interval_step_default = 100

# Default SAR Receiver Segments Threshold state represents the size of a
# segmented message in number of segments above which the Segment Acknowledgment
# messages are enabled.
# Valid range is 0 - 31, the default value is 3 (segments) in specification.
sar_rx_segments_threshold_default = 3

# Default SAR Receiver Acknowledgment Delay Increment state control the interval
# between the reception of a new segment of a segmented message for a destination
# that is a unicast address and the transmission of the Segment Acknowledgment
# for that message.
# Formula: acknowledgment delay increment=SAR Acknowledgment Delay Increment+1.5
# Valid range is 0 - 7, default is 2 in specification resulting in 3.5 segment
# transmission interval steps.
sar_rx_ack_delay_increment_default = 2

# Default SAR Receiver Discard Timeout state controls the time that the lower
# transport layer waits after receiving unique segments of a segmented message
# before discarding that segmented message in 5s steps.
# Valid range is 5000 - 80000ms, intermediate values are rounded down to the
# nearest multiple of 5s. The default value is 10000ms in specification.
sar_rx_discard_timeout_default = 10000

# Default SAR Receiver Segment Interval Step state indicates the interval between
# received segments of a segmented message in milliseconds.
# This is used to control rate of transmission of Segment Acknowledgment messages.
# Valid range is 10 - 160, intermediate values are rounded down to the nearest
# multiple of 10. The default value is 20ms in specification.
sar_rx_segment_interval_step_default = 20

# Default SAR Receiver Acknowledgment Retransmissions Count state controls the
# maximum number of retransmissions of Segment Acknowledgment messages sent by
# the lower transport layer.
# Valid range is 0 - 3. The default value is 1 in specification, representing
# 1 retransmissions or 2 in total.
sar_rx_ack_retrans_count_default = 2


[dist_clt]
# Element index of the FW Distribution Client model on NCP node.
elem_index = 0

# Default appkey index used for sending FW Distribution messages.
appkey_index_default = 0

# Default TTL used for sending FW Distribution messages.
ttl_default = 5

# The default timeout base of FW upload to the Distributor including the upload
# start-status timeout and BLOB Transfer timeout.
# Client side timeout is (10000 * (timeout_base + 2)) + (100 * ttl) ms.
# Server side timeout is (10000 * (timeout_base + 1)) ms.
upload_timeout_base_default = 3

# Default preferred chunk size during BLOB transfer phase of FW upload procedure.
# The maximum chunk size is limited by the Max Chunk Size capabilities of
# participating BLOB Transfer Servers.
# The minimum chunk size is limited by the calculated block size and the Max
# Total chunk capabilities of participating BLOB Transfer Servers.
# The default chunk size calculation algorithm selects the preferred chunk size
# if it is in the range defined by min and max chunk size limits. Otherwise,
# the algorithm selects the nearest valid value which fills the BT Mesh messages.
# If Silabs BT Mesh over Advertisement Extensions proprietary feature is enabled
# then the network PDU size is selected as the chunk size unless the minimum
# chunk size is higher.
# The standard (non-AE) segmented chunks are able to transfer 12 bytes per
# advertisement minus 1 byte opcode and 2 bytes chunk number and 4 bytes of MIC.
# This means N advertisements are able to transfer 12 x N - 7 bytes of chunk data.
# The standard unsegmented chunk is  able to transfer 8 bytes of chunk data.
upload_chunk_size_default = 53

# The default appkey index used for the communication between the Distributor
# and Target Nodes.
dist_appkey_index_default = 0

# The default TTL for the Distributor to use when communicating with the
# Target Nodes.
dist_ttl_default = 5

# The default timeout base used for FW distribution including FW update message
# procedures and BLOB transfer.
dist_timeout_base_default = 3

# Default poll interval for distribution progress reporting in seconds.
dist_poll_int_default = 5.0

# Default maximum number of additional Firmware Distribution messages which are
# sent until the corresponding status message is not received from the Firmware
# Distribution Server.
# For example: FW Distribution Upload Start, FW Distribution Receivers Add,
# FW Distribution Start message etc.
# Note: this default value is used unless a more specific configuration option
# overrides it. See delete_retry_max_default parameter in this file.
dist_retry_max_default = 5

# Default interval in seconds between Firmware Distribution messages when the
# corresponding status message is not received from the Firmware Distribution
# Server.
# For example: FW Distribution Upload Start, FW Distribution Receivers Add,
# FW Distribution Start messages etc.
# This default retry interval is used for BLOB Transfer during FW Upload
# procedure as the repetition rate of BLOB Transfer messages when the
# corresponding BLOB Transfer status message is not received from the BLOB
# Transfer Server on the Distributor.
# This default retry interval is used for Metadata Check Procedure at the
# beginning of Firmware Distribution procedure between Firmware Update Metadata
# Check messages sent to the target nodes.
# Note: this default value is used unless a more specific configuration option
# overrides it. See delete_retry_interval_default parameter in this file.
dist_retry_interval_default = 1.0

# Default interval in seconds between Firmware Update Firmware Metadata Check
# messages when the corresponding status messages are not received from
# the Firmware Update Server model of each selected low power target nodes.
# Note: This parameters affects the Firmware Metadata Check at the beginning
# of the Firmware Distribution procedure.
dist_retry_interval_lpn_default = 5.0

# Default multicast threshold used during the Firmware Compatibility Check
# (Metadata Check) at the beginning of the Firmware Distribution procedure.
# If the number of uncompleted servers (missing status messages) during the
# aforementioned Firmware Compatibility Check procedure exceeds or is equal
# to this number then the group address is used. Otherwise, servers are looped
# through one by one. Zero value means unicast addressing.
# WARNING! The multicast threshold of distribution process is determined by the
# configuration of Firmware Distribution Server component on the Distributor node.
dist_retry_multicast_threshold_default = 2

# Default maximum number of additional Firmware Distribution Firmware Delete or
# Delete All messages which are sent until the corresponding status message
# is not received from the Firmware Distribution Server.
# Note: the firmware delete procedure requires specific retry parameters because
# the FW delete operation might take from 5 to 25 seconds and it can be slow
# especially in case of external flash (SPI flash).
delete_retry_max_default = 6

# Default interval in seconds between Firmware Distribution Firmware Delete or
# Delete All messages when the corresponding status message is not received from
# the Firmware Distribution Server.
# Note: the firmware delete procedure requires specific retry parameters because
# the FW delete operation might take from 5 to 25 seconds and it can be slow
# especially in case of external flash (SPI flash).
delete_retry_interval_default = 5.0


[dfu_clt]
# Element index of the Firmware Update Client model on NCP node.
elem_index = 0

# Default appkey index used for sending FW Update and BLOB Transfer messages
# during Standalone FW Update and FW Information Query procedures.
appkey_index_default = 0

# Default TTL used for sending FW Update and BLOB Transfer messages during
# Standalone FW Update and FW Information Query procedures.
ttl_default = 5

# The default timeout base of Standalone FW Update procedure including FW update
# procedures and BLOB transfer.
# Client side timeout is (10000 * (timeout_base + 2)) + (100 * ttl) ms.
# Server side timeout is (10000 * (timeout_base + 1)) ms.
timeout_base_default = 3

# Maximum number of target nodes which can be updated simultaneously
max_target_nodes = 8

# Default preferred chunk size during BLOB transfer phase of FW Update procedure.
# The maximum chunk size is limited by the Max Chunk Size capabilities of
# participating BLOB Transfer Servers.
# The minimum chunk size is limited by the calculated block size and the Max
# Total chunk capabilities of participating BLOB Transfer Servers.
# The default chunk size calculation algorithm selects the preferred chunk size
# if it is in the range defined by min and max chunk size limits. Otherwise,
# the algorithm selects the nearest valid value which fills the BT Mesh messages.
# If Silabs BT Mesh over Advertisement Extensions proprietary feature is enabled
# then the network PDU size is selected as the chunk size unless the minimum
# chunk size is higher.
# The standard (non-AE) segmented chunks are able to transfer 12 bytes per
# advertisement minus 1 byte opcode and 2 bytes chunk number and 4 bytes of MIC.
# This means N advertisements are able to transfer 12 x N - 7 bytes of chunk data.
# The standard unsegmented chunk is able to transfer 8 bytes of chunk data.
dfu_chunk_size_default = 53

# Default maximum number of additional Firmware Update messages which are sent
# until the corresponding Firmware Update messages are received from the Firmware
# Update Server model of each selected target nodes.
# This configuration option is used during Firmware Information Query and
# Firmware Metadata Check procedures and it is not used during Standalone
# Firmware Update procedure.
# The default maximum number of retransmissions in each Standalone Firmware
# Update phase is determined by the timeout base and dfu_retry_interval_default.
dfu_retry_max_default = 5

# Default interval in seconds between Firmware Update and BLOB Transfer messages
# when the corresponding status messages are not received from the Firmware
# Update Server or BLOB Transfer Server model of each selected target nodes.
# This parameter affects those BLOB Transfers which are initiated by the
# Standalone Firmware Update procedure.
dfu_retry_interval_default = 1.0

# Default interval in seconds between Firmware Update and BLOB Transfer messages
# when the corresponding status messages are not received from the Firmware
# Update Server or BLOB Transfer Server model of each selected low power
# target nodes.
# This parameter affects those BLOB Transfers which are initiated by the
# Standalone Firmware Update procedure.
dfu_retry_interval_lpn_default = 5.0

# Default multicast threshold used during Check For Current Firmware procedure
# and during the Firmware Compatibility Check (Metadata Check) and BLOB Transfer
# phase of FW update.
# If the number of uncompleted servers (missing status messages) during the
# aforementioned FW Update procedures or during any BLOB Transfer procedure
# step exceeds or is equal to this number then the group address is used.
# Otherwise, servers are looped through one by one.
# Zero value means unicast addressing.
# WARNING! The FW Update Start, Get (Verification), Cancel and Apply steps of
# FW Update uses unicast addressing only and loops through each server on by one.
# Note: Each BT Mesh message sent to a group address triggers the response of
# several nodes which send the corresponding status messages with random delay.
# As the number of nodes increases the probability of collisions increases as well.
# If the number of nodes with missing status messages is low then it is better
# to send multiple unicast messages instead of a single message to the group
# address because the collisions could lead to the loss of the status messages.
dfu_retry_multicast_threshold_default = 2


[mbt_clt]
# Element index of the BLOB Transfer Client model on NCP node.
elem_index = 0

# Maximum number of BLOB Transfer Servers participating in a BLOB transfer.
# Note: The BT Mesh stack allocates memory based on this configuration option
#       when MBT Client model is initialized.
max_servers = 8

# Maximum number of blocks during a BLOB transfer. The MBT Client breaks the
# BLOB into suitably sized blocks during BLOB transfer.
# Note: The BT Mesh stack allocates memory based on this configuration option
#       when MBT Client model is initialized.
max_blocks = 1850

# Max number of chunks in a block during a BLOB transfer.
# Each block is composed of identically sized chunks of data, except for the
# last chunk which may be smaller than the other chunks.
# Note: The BT Mesh stack allocates memory based on this configuration option
#       when MBT Client model is initialized.
max_chunks_per_block = 128


[network]
# Random netkey is created when a new BT Mesh network is created.
random_netkey = true

# Network key used when a new BT Mesh network is created and random_netkey is
# set to false to use fix key.
netkey = EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE

# Random appkey is created when a new BT Mesh network is created.
random_appkey = true

# If random_appkey is set to true then this configuration option determines
# the number of generated random application keys.
random_appkey_cnt = 4

# Application key used when a new BT Mesh network is created and random_appkey
# is set to false to use fix key.
# Multiple appkeys can be specified by adding non-negative consecutive decimal
# integer postfix to the "appkey" words starting from 0 to maximum 31.
# If "appkey" exists then no postfixes are checked and only one appkey is created.
appkey0 = AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

# Name of the provisioner node in the BT Mesh database.
prov_node_name = Provisioner


[persistence]
# Path of json file which stores the persistent data of program.
path = btmesh_host_dfu_persistence.json

# If true then default is used when persistent data load fails then otherwise
# the program is terminated.
default_on_failed_load = true

# If true then a backup is created from the failed persistent data file before
# it is overwritten with the default values.
backup_on_failed_load = true


[proxy]
# Default scanning timeout for Proxy Service Advertisements with node identity
# in seconds.
scan_timeout_default = 2.0

# Default bluetooth connection opening and proxy connection establishment timeout
# in milliseconds.
conn_open_timeout_ms_default = 5000.0

# Default minimum value for the connection event interval in milliseconds.
# Range: 7.5ms to 4s
# Resolution: 1.25ms
conn_min_interval_ms_default = 7.5

# Default maximum value for the connection event interval in milliseconds.
# Range: 7.5ms to 4s
# Resolution: 1.25ms
conn_max_interval_ms_default = 7.5

# Default peripheral latency, which defines how many connection intervals the peripheral
# can skip if it has no data to send.
# Range: 0x0000 to 0x01f3
conn_latency_default = 0

# Default supervision timeout in milliseconds, which defines the time that
# the connection is maintained although the devices can't communicate at the
# currently configured connection intervals.
# The supervision timeout value in milliseconds shall be larger than
# (1 + latency) * max_interval * 2, where max_interval is given in ms.
# Range: 100ms to 32s
# Resolution: 10ms
conn_timeout_ms_default = 5000.0

# Default minimum length of the connection event.
# This value defines the minimum time that should be given to the connection
# event in a situation where other tasks need to run immediately after the
# connection event. When the value is very small, the connection event still
# has at least one TX/RX operation.
# If this value is increased, more time is reserved for the connection event
# so it can transmit and receive more packets in a connection interval.
# Range: 0x0000 to 0xffff (multiplied by 0.625ms)
# Resolution: 0.625 ms
conn_min_ce_length_ms_default = 0

# Default maximum length of the connection event.
# This value is used for limiting the connection event length so that a
# connection that has large amounts of data to transmit or receive doesn't
# block other tasks.
# Limiting the connection event is a hard stop. If there is no enough time
# to send or receive a packet, the connection event will be closed.
# If the value is set to 0, the connection event still has at least one TX/RX
# operation. This is useful to limit power consumption or leave more time to
# other tasks.
# Range: 0x0000 to 0xffff (multiplied by 0.625ms)
# Resolution: 0.625 ms
conn_max_ce_length_ms_default = 40000.0


[reset]
# It is necessary to perform a system reset after the persistent data (e.g. keys)
# is removed from the NCP node. The NVM and key storage erase takes some time so
# the system reset shall be delayed in order to guarantee the proper execution
# of factory reset.
factory_reset_delay_s = 2.0


[ui]
# Default text table width on the UI in characters.
# Some data is displayed on the ui in text table format. The optimal width of
# a table depends on the terminal and display size. If the table width is too
# high then the table might not fit on the screen or it might be wrapped into
# multiple lines. If the table width is too low then the content in the cells
# might be wrapped into multiple lines which makes readability worse.
table_width_default = 100

# The format determines if the version information part of FW identifier shall
# be converted into hex string or it shall be converted into a regular string
# by utf-8 decoding when it is shown on the UI.
# Valid values: str, hex
fwid_format = str

# The format determines if the metadata shall  be converted into hex string or
# it shall be converted into a regular string by utf-8 decoding when it is
# shown on the UI.
# Valid values: str, hex
metadata_format = str

# The format determines how the node is shown on the UI.
# The node format can be any valid python format string which may use the
# following keyword parameters:
#   - name: Node name as string
#   - uuid: Node UUID as string (32 hex characters)
#   - prim_addr: Node primary address as integer(element index 0)
# Examples:
#   - {name}                      =>  Node_Light
#   - 0x{prim_addr:04X}           =>  0x200B
#   - {name} (0x{prim_addr:04X})  =>  Node_Light (0x200B)
node_format={name}

# The format determines how the node element is shown on the UI.
# The node element format can be any valid python format string which may use
# the following keyword parameters:
#   - name: Node name as string
#   - uuid: Node UUID as string (32 hex characters)
#   - prim_addr: Node primary address as integer(element index 0)
#   - elem_index: Element index on the node as integer
#   - elem_addr: Address of node element as integer
# Examples:
#   - {name}[{elem_index}]                =>  Node_Light[1]
#   - 0x{elem_addr:04X}                   =>  0x200B
#   - {name}[{elem_index}] ({elem_addr})  =>  Node_Light[1] (0x200B)
elem_format={name}[{elem_index}]
"""

logger = logging.getLogger(__name__)


CFG_OPT_INTERNAL_SEP = ","


@dataclasses.dataclass
class BtmeshDfuAppMdlProfile:
    name: str
    pub_mdls: Set[ModelID] = dataclasses.field(default_factory=set)
    sub_mdls: Set[ModelID] = dataclasses.field(default_factory=set)
    bind_mdls: Set[ModelID] = dataclasses.field(default_factory=set)
    help: str = ""

    @property
    def mdls(self):
        mdls_set = set()
        mdls_set |= self.pub_mdls
        mdls_set |= self.sub_mdls
        mdls_set |= self.bind_mdls
        return mdls_set


class BtmeshDfuAppGroupCfg:
    def __init__(self, section: SectionProxy):
        self.section = section
        sect = section
        # auto_bind_default
        self._auto_bind_default = sect.getboolean("auto_bind_default")
        # dcd_check_default
        self._dcd_check_default = sect.getboolean("dcd_check_default")
        # pub_ttl_default
        self._pub_ttl_default = sect.getint("pub_ttl_default")
        # pub_cred_default
        self._pub_cred_default = sect.getint("pub_cred_default")
        # pub_period_ms_default
        self._pub_period_ms_default = sect.getint("pub_period_ms_default")
        # pub_tx_cnt_default
        self._pub_tx_cnt_default = sect.getint("pub_tx_cnt_default")
        # pub_tx_int_ms_default
        self._pub_tx_int_ms_default = sect.getint("pub_tx_int_ms_default")
        # profile
        self._mdl_profiles = self.process_mdl_profiles()
        sectname = sect.name
        logger.debug(f"{sectname}:auto_bind_default: {self.auto_bind_default}")
        logger.debug(f"{sectname}:dcd_check_default: {self.dcd_check_default}")
        logger.debug(f"{sectname}:pub_ttl_default: {self.pub_ttl_default}")
        logger.debug(f"{sectname}:pub_cred_default: {self.pub_cred_default}")
        logger.debug(f"{sectname}:pub_period_ms_default: {self.pub_period_ms_default}")
        logger.debug(f"{sectname}:pub_tx_cnt_default: {self.pub_tx_cnt_default}")
        logger.debug(f"{sectname}:pub_tx_int_ms_default: {self.pub_tx_int_ms_default}")
        for mp in self.mdl_profiles:
            pub_mdls = ", ".join(mdl.pretty_name() for mdl in mp.pub_mdls)
            logger.debug(f"{sectname}:profile_{mp.name}:pub_mdls: {pub_mdls}")
            sub_mdls = ", ".join(mdl.pretty_name() for mdl in mp.sub_mdls)
            logger.debug(f"{sectname}:profile_{mp.name}:sub_mdls: {sub_mdls}")
            bind_mdls = ", ".join(mdl.pretty_name() for mdl in mp.bind_mdls)
            logger.debug(f"{sectname}:profile_{mp.name}:bind_mdls: {bind_mdls}")
            logger.debug(f"{sectname}:profile_{mp.name}:help: {mp.help}")

    @property
    def auto_bind_default(self) -> bool:
        return self._auto_bind_default

    @property
    def dcd_check_default(self) -> bool:
        return self._dcd_check_default

    @property
    def pub_ttl_default(self) -> int:
        return self._pub_ttl_default

    @property
    def pub_cred_default(self) -> int:
        return self._pub_cred_default

    @property
    def pub_period_ms_default(self) -> int:
        return self._pub_period_ms_default

    @property
    def pub_tx_cnt_default(self) -> int:
        return self._pub_tx_cnt_default

    @property
    def pub_tx_int_ms_default(self) -> int:
        return self._pub_tx_int_ms_default

    @property
    def mdl_profiles(self) -> Iterable[BtmeshDfuAppMdlProfile]:
        return (mp for mp in self._mdl_profiles.values())

    def process_mdl_profiles(self):
        MDL_PROFILE_POSTFIXES = (
            "pub_mdls",
            "sub_mdls",
            "bind_mdls",
            "auto_bind",
            "help",
        )
        MDL_PROFILE_POSTFIX_PATTERN = "|".join(MDL_PROFILE_POSTFIXES)
        MDL_PROFILE_PATTERN = f"profile_(\\w+)_({MDL_PROFILE_POSTFIX_PATTERN})"
        MDL_PROFILE_GENERIC_PATTERN = r"profile_\w+"
        sect = self.section
        mdl_profiles: Dict[str, BtmeshDfuAppMdlProfile] = {}
        mdl_profiles_auto_bind: Dict[str, bool] = {}
        for opt_name, opt_value in sect.items():
            match = re.fullmatch(MDL_PROFILE_PATTERN, opt_name)
            if not match:
                if re.fullmatch(MDL_PROFILE_GENERIC_PATTERN, opt_name):
                    valid_postfixes = ", ".join(MDL_PROFILE_POSTFIXES)
                    raise ValueError(
                        f'The "{sect.name}:{opt_name}" model profile option name '
                        f"is invalid because no valid postfix is found "
                        f"(profile_<name>_<postfix>). "
                        f"Valid postfixes: {valid_postfixes}."
                    )
                continue
            name = match.group(1)
            if name not in mdl_profiles:
                mdl_profiles[name] = BtmeshDfuAppMdlProfile(name)
                auto_bind_opt_name = f"profile_{name}_auto_bind"
                # Process auto_bind as soon as the first profile_<name>_<attr>
                # option is found with the given <name> because the auto_bind
                # information is required to process pub_mdls and sub_mdls opts.
                if auto_bind_opt_name in sect:
                    mdl_profiles_auto_bind[name] = sect[auto_bind_opt_name]
                else:
                    mdl_profiles_auto_bind[name] = False
            profile_attr = match.group(2)
            if profile_attr == "pub_mdls":
                self.add_mdls_from_opt(
                    mdl_profiles[name].pub_mdls, sect, opt_name, opt_value
                )
                if mdl_profiles_auto_bind[name]:
                    self.add_mdls_from_opt(
                        mdl_profiles[name].bind_mdls, sect, opt_name, opt_value
                    )
            elif profile_attr == "sub_mdls":
                self.add_mdls_from_opt(
                    mdl_profiles[name].sub_mdls, sect, opt_name, opt_value
                )
                if mdl_profiles_auto_bind[name]:
                    self.add_mdls_from_opt(
                        mdl_profiles[name].bind_mdls, sect, opt_name, opt_value
                    )
            elif profile_attr == "bind_mdls":
                self.add_mdls_from_opt(
                    mdl_profiles[name].bind_mdls, sect, opt_name, opt_value
                )
            elif profile_attr == "auto_bind":
                # The profile_<name>_auto_bind is not processed in sequence
                # because it requires early processing to have it available
                # when pub_mdls and sub_mdls are processed.
                continue
            elif profile_attr == "help":
                mdl_profiles[name].help = btmesh.util.join_text_lines(opt_value)
            else:
                # This should not happen if the regex is consistent with
                # the if-else structure of the code.
                raise ValueError(
                    f'The "{sect.name}:{opt_name}" model profile option name '
                    f'is invalid because the "{profile_attr}" postfix '
                    f"is unknown."
                )
        return mdl_profiles

    def add_mdls_from_opt(
        self, dest_set: Set[ModelID], sect: SectionProxy, opt_name: str, opt_value: str
    ):
        text = btmesh.util.join_text_lines(opt_value)
        if not text:
            return
        raw_mdls = (raw_mdl.strip() for raw_mdl in text.split(CFG_OPT_INTERNAL_SEP))
        for raw_mdl in raw_mdls:
            if re.fullmatch(btmesh.util.INTEGER_PATTERN, raw_mdl):
                mdl_id = int(raw_mdl, 0)
                mdl = ModelID(model_id=mdl_id)
                dest_set.add(mdl)
            elif re.fullmatch(btmesh.util.INTEGER_PAIR_PATTERN, raw_mdl):
                match = re.fullmatch(btmesh.util.INTEGER_PAIR_PATTERN, raw_mdl)
                vendor_id = int(match.group(1), 0)
                mdl_id = int(match.group(2), 0)
                mdl = ModelID(model_id=mdl_id, vendor_id=vendor_id)
                dest_set.add(mdl)
            elif NamedModelID.is_name_valid(raw_mdl):
                mdl_id = NamedModelID.get_id_by_name(raw_mdl)
                mdl = ModelID(model_id=mdl_id)
                dest_set.add(mdl)
            else:
                raise ValueError(
                    f"Invalid model identifier ({raw_mdl}) found in "
                    f"{sect.name}:{opt_name} configuration option."
                )


class BtmeshDfuCommonCfg:
    def __init__(self, section: SectionProxy):
        self.section = section
        sect = section
        # api_xmls_default
        self._api_xmls_default = self.process_api_xmls_default()
        # retry_max_default
        self._retry_max_default = sect.getint("retry_max_default")
        # retry_interval_default
        self._retry_interval_default = sect.getfloat("retry_interval_default")
        # retry_interval_lpn_default
        self._retry_interval_lpn_default = sect.getfloat("retry_interval_lpn_default")
        # retry_cmd_max_default
        self._retry_cmd_max_default = sect.getint("retry_cmd_max_default")
        # retry_cmd_interval_default
        self._retry_cmd_interval_default = sect.getfloat("retry_cmd_interval_default")
        # retry_multicast_threshold_default
        self._retry_multicast_threshold_default = sect.getint(
            "retry_multicast_threshold_default"
        )
        # retry_auto_unicast_default
        self._retry_auto_unicast_default = sect.getboolean("retry_auto_unicast_default")
        # Log common configuration
        sectname = sect.name
        api_xmls_default_str = ", ".join(str(path) for path in self.api_xmls_default)
        logger.debug(f"{sectname}:api_xmls_default: {api_xmls_default_str}")
        logger.debug(f"{sectname}:retry_max_default: {self.retry_max_default}")
        logger.debug(
            f"{sectname}:retry_interval_default: {self.retry_interval_default}"
        )
        logger.debug(
            f"{sectname}:retry_interval_lpn_default: "
            f"{self.retry_interval_lpn_default}"
        )
        logger.debug(f"{sectname}:retry_cmd_max_default: {self.retry_cmd_max_default}")
        logger.debug(
            f"{sectname}:retry_cmd_interval_default: "
            f"{self.retry_cmd_interval_default}"
        )
        logger.debug(
            f"{sectname}:retry_multicast_threshold_default: "
            f"{self.retry_multicast_threshold_default}"
        )
        logger.debug(
            f"{sectname}:retry_auto_unicast_default: "
            f"{self.retry_auto_unicast_default}"
        )

    @property
    def api_xmls_default(self):
        for path in self._api_xmls_default:
            yield path

    @property
    def retry_max_default(self):
        return self._retry_max_default

    @property
    def retry_interval_default(self):
        return self._retry_interval_default

    @property
    def retry_interval_lpn_default(self):
        return self._retry_interval_lpn_default

    @property
    def retry_cmd_max_default(self):
        return self._retry_cmd_max_default

    @property
    def retry_cmd_interval_default(self):
        return self._retry_cmd_interval_default

    @property
    def retry_multicast_threshold_default(self):
        return self._retry_multicast_threshold_default

    @property
    def retry_auto_unicast_default(self):
        return self._retry_auto_unicast_default

    @property
    def retry_params_default(self):
        return self.btmesh_multicast_retry_params_default.to_base()

    @property
    def btmesh_retry_params_default(self):
        return self.btmesh_multicast_retry_params_default.to_btmesh()

    @property
    def btmesh_multicast_retry_params_default(self):
        return BtmeshMulticastRetryParams(
            retry_max=self.retry_max_default,
            retry_interval=self.retry_interval_default,
            retry_interval_lpn=self.retry_interval_lpn_default,
            retry_cmd_max=self.retry_cmd_max_default,
            retry_cmd_interval=self.retry_cmd_interval_default,
            multicast_threshold=self.retry_multicast_threshold_default,
            auto_unicast=self.retry_auto_unicast_default,
        )

    def process_api_xmls_default(self) -> List[Path]:
        sect = self.section
        api_xmls_text = sect.get("api_xmls_default")
        api_xml_paths = []
        for api_xml_text in api_xmls_text.split(CFG_OPT_INTERNAL_SEP):
            api_xml_text = api_xml_text.strip()
            if api_xml_text:
                api_xml_path = Path(api_xml_text)
                api_xml_paths.append(api_xml_path)
        return api_xml_paths


class BtmeshDfuAppConfCfg:
    def __init__(self, section: SectionProxy):
        self.section = section
        sect = section
        # auto_conf_strict
        self._auto_conf_strict = sect.getboolean("auto_conf_strict")
        # reset_node_retry_max_default
        self._reset_node_retry_max_default = sect.getint("reset_node_retry_max_default")
        # reset_node_retry_interval_default
        self._reset_node_retry_interval_default = sect.getfloat(
            "reset_node_retry_interval_default"
        )
        # reset_node_retry_interval_lpn_default
        self._reset_node_retry_interval_lpn_default = sect.getfloat(
            "reset_node_retry_interval_lpn_default"
        )
        # reset_node_local_remove_on_retry_limit
        self._reset_node_local_remove_on_retry_limit = sect.getboolean(
            "reset_node_local_remove_on_retry_limit"
        )
        # conf_retry_max_default
        self._conf_retry_max_default = sect.getint("conf_retry_max_default")
        # conf_retry_interval_default
        self._conf_retry_interval_default = sect.getfloat("conf_retry_interval_default")
        # conf_retry_interval_lpn_default
        self._conf_retry_interval_lpn_default = sect.getfloat(
            "conf_retry_interval_lpn_default"
        )
        # silabs_retry_max_default
        self._silabs_retry_max_default = sect.getint("silabs_retry_max_default")
        # silabs_retry_interval_default
        self._silabs_retry_interval_default = sect.getfloat(
            "silabs_retry_interval_default"
        )
        # silabs_retry_interval_lpn_default
        self._silabs_retry_interval_lpn_default = sect.getfloat(
            "silabs_retry_interval_lpn_default"
        )
        # silabs_retry_multicast_threshold_default
        self._silabs_retry_multicast_threshold_default = sect.getint(
            "silabs_retry_multicast_threshold_default"
        )
        # auto_conf_dcd_query
        self._auto_conf_dcd_query = sect.getboolean("auto_conf_dcd_query")
        # auto_conf_default_ttl
        self._auto_conf_default_ttl = sect.getboolean("auto_conf_default_ttl")
        # default_ttl_default
        self._default_ttl_default = sect.getint("default_ttl_default")
        # relay_retx_count_default
        self._relay_retx_count_default = sect.getint("relay_retx_count_default")
        # relay_retx_interval_ms_default
        self._relay_retx_interval_ms_default = sect.getint(
            "relay_retx_interval_ms_default"
        )
        # auto_conf_network_tx
        self._auto_conf_network_tx = sect.getboolean("auto_conf_network_tx")
        # network_tx_count_default
        self._network_tx_count_default = sect.getint("network_tx_count_default")
        # network_tx_interval_ms_default
        self._network_tx_interval_ms_default = sect.getint(
            "network_tx_interval_ms_default"
        )
        # auto_conf_sar
        self._auto_conf_sar = sect.getboolean("auto_conf_sar")
        # sar_tx_segment_interval_step_default
        self._sar_tx_segment_interval_step_default = sect.getint(
            "sar_tx_segment_interval_step_default"
        )
        # sar_tx_unicast_retrans_count_default
        self._sar_tx_unicast_retrans_count_default = sect.getint(
            "sar_tx_unicast_retrans_count_default"
        )
        # sar_tx_unicast_retrans_wo_progress_count_default
        self._sar_tx_unicast_retrans_wo_progress_count_default = sect.getint(
            "sar_tx_unicast_retrans_wo_progress_count_default"
        )
        # sar_tx_unicast_retrans_interval_step_default
        self._sar_tx_unicast_retrans_interval_step_default = sect.getint(
            "sar_tx_unicast_retrans_interval_step_default"
        )
        # sar_tx_unicast_retrans_interval_increment_default
        self._sar_tx_unicast_retrans_interval_increment_default = sect.getint(
            "sar_tx_unicast_retrans_interval_increment_default"
        )
        # sar_tx_multicast_retrans_count_default
        self._sar_tx_multicast_retrans_count_default = sect.getint(
            "sar_tx_multicast_retrans_count_default"
        )
        # sar_tx_multicast_retrans_interval_step_default
        self._sar_tx_multicast_retrans_interval_step_default = sect.getint(
            "sar_tx_multicast_retrans_interval_step_default"
        )
        # sar_rx_segments_threshold_default
        self._sar_rx_segments_threshold_default = sect.getint(
            "sar_rx_segments_threshold_default"
        )
        # sar_rx_ack_delay_increment_default
        self._sar_rx_ack_delay_increment_default = sect.getint(
            "sar_rx_ack_delay_increment_default"
        )
        # sar_rx_discard_timeout_default
        self._sar_rx_discard_timeout_default = sect.getint(
            "sar_rx_discard_timeout_default"
        )
        # sar_rx_segment_interval_step_default
        self._sar_rx_segment_interval_step_default = sect.getint(
            "sar_rx_segment_interval_step_default"
        )
        # sar_rx_ack_retrans_count_default
        self._sar_rx_ack_retrans_count_default = sect.getint(
            "sar_rx_ack_retrans_count_default"
        )
        # Log conf configuration
        sectname = sect.name
        logger.debug(f"{sectname}:auto_conf_strict: {self.auto_conf_strict}")
        logger.debug(
            f"{sectname}:reset_node_retry_max_default: "
            f"{self.reset_node_retry_max_default}"
        )
        logger.debug(
            f"{sectname}:reset_node_retry_interval_default: "
            f"{self.reset_node_retry_interval_default}"
        )
        logger.debug(
            f"{sectname}:reset_node_retry_interval_lpn_default: "
            f"{self.reset_node_retry_interval_lpn_default}"
        )
        logger.debug(
            f"{sectname}:reset_node_local_remove_on_retry_limit: "
            f"{self.reset_node_local_remove_on_retry_limit}"
        )
        logger.debug(
            f"{sectname}:conf_retry_max_default: {self.conf_retry_max_default}"
        )
        logger.debug(
            f"{sectname}:conf_retry_interval_default: "
            f"{self.conf_retry_interval_default}"
        )
        logger.debug(
            f"{sectname}:conf_retry_interval_lpn_default: "
            f"{self.conf_retry_interval_lpn_default}"
        )
        logger.debug(
            f"{sectname}:silabs_retry_max_default: {self.silabs_retry_max_default}"
        )
        logger.debug(
            f"{sectname}:silabs_retry_interval_default: "
            f"{self.silabs_retry_interval_default}"
        )
        logger.debug(
            f"{sectname}:silabs_retry_interval_lpn_default: "
            f"{self.silabs_retry_interval_lpn_default}"
        )
        logger.debug(
            f"{sectname}:silabs_retry_multicast_threshold_default: "
            f"{self.silabs_retry_multicast_threshold_default}"
        )
        logger.debug(f"{sectname}:auto_conf_dcd_query: {self.auto_conf_dcd_query}")
        logger.debug(f"{sectname}:auto_conf_default_ttl: {self.auto_conf_default_ttl}")
        logger.debug(f"{sectname}:default_ttl_default: {self.default_ttl_default}")
        logger.debug(
            f"{sectname}:relay_retx_count_default: {self.relay_retx_count_default}"
        )
        logger.debug(
            f"{sectname}:relay_retx_interval_ms_default: "
            f"{self.relay_retx_interval_ms_default}"
        )
        logger.debug(f"{sectname}:auto_conf_network_tx: {self.auto_conf_network_tx}")
        logger.debug(
            f"{sectname}:network_tx_count_default: {self.network_tx_count_default}"
        )
        logger.debug(
            f"{sectname}:network_tx_interval_ms_default: "
            f"{self.network_tx_interval_ms_default}"
        )
        logger.debug(f"{sectname}:auto_conf_sar: {self.auto_conf_sar}")
        logger.debug(
            f"{sectname}:sar_tx_segment_interval_step_default: "
            f"{self.sar_tx_segment_interval_step_default}"
        )
        logger.debug(
            f"{sectname}:sar_tx_unicast_retrans_count_default: "
            f"{self.sar_tx_unicast_retrans_count_default}"
        )
        logger.debug(
            f"{sectname}:sar_tx_unicast_retrans_wo_progress_count_default: "
            f"{self.sar_tx_unicast_retrans_wo_progress_count_default}"
        )
        logger.debug(
            f"{sectname}:sar_tx_unicast_retrans_interval_step_default: "
            f"{self.sar_tx_unicast_retrans_interval_step_default}"
        )
        logger.debug(
            f"{sectname}:sar_tx_unicast_retrans_interval_increment_default: "
            f"{self.sar_tx_unicast_retrans_interval_increment_default}"
        )
        logger.debug(
            f"{sectname}:sar_tx_multicast_retrans_count_default: "
            f"{self.sar_tx_multicast_retrans_count_default}"
        )
        logger.debug(
            f"{sectname}:sar_tx_multicast_retrans_interval_step_default: "
            f"{self.sar_tx_multicast_retrans_interval_step_default}"
        )
        logger.debug(
            f"{sectname}:sar_rx_segments_threshold_default: "
            f"{self.sar_rx_segments_threshold_default}"
        )
        logger.debug(
            f"{sectname}:sar_rx_ack_delay_increment_default: "
            f"{self.sar_rx_ack_delay_increment_default}"
        )
        logger.debug(
            f"{sectname}:sar_rx_discard_timeout_default: "
            f"{self.sar_rx_discard_timeout_default}"
        )
        logger.debug(
            f"{sectname}:sar_rx_segment_interval_step_default: "
            f"{self.sar_rx_segment_interval_step_default}"
        )
        logger.debug(
            f"{sectname}:sar_rx_ack_retrans_count_default: "
            f"{self.sar_rx_ack_retrans_count_default}"
        )

    @property
    def auto_conf_strict(self):
        return self._auto_conf_strict

    @property
    def reset_node_retry_max_default(self) -> int:
        return self._reset_node_retry_max_default

    @property
    def reset_node_retry_interval_default(self) -> float:
        return self._reset_node_retry_interval_default

    @property
    def reset_node_retry_interval_lpn_default(self) -> float:
        return self._reset_node_retry_interval_lpn_default

    @property
    def reset_node_local_remove_on_retry_limit(self) -> bool:
        return self._reset_node_local_remove_on_retry_limit

    @property
    def conf_retry_max_default(self) -> int:
        return self._conf_retry_max_default

    @property
    def conf_retry_interval_default(self) -> float:
        return self._conf_retry_interval_default

    @property
    def conf_retry_interval_lpn_default(self) -> float:
        return self._conf_retry_interval_lpn_default

    @property
    def silabs_retry_max_default(self) -> int:
        return self._silabs_retry_max_default

    @property
    def silabs_retry_interval_default(self) -> float:
        return self._silabs_retry_interval_default

    @property
    def silabs_retry_interval_lpn_default(self) -> float:
        return self._silabs_retry_interval_lpn_default

    @property
    def silabs_retry_multicast_threshold_default(self) -> int:
        return self._silabs_retry_multicast_threshold_default

    @property
    def auto_conf_dcd_query(self) -> bool:
        return self._auto_conf_dcd_query

    @property
    def auto_conf_default_ttl(self) -> bool:
        return self._auto_conf_default_ttl

    @property
    def default_ttl_default(self) -> int:
        return self._default_ttl_default

    @property
    def relay_retx_count_default(self) -> int:
        return self._relay_retx_count_default

    @property
    def relay_retx_interval_ms_default(self) -> int:
        return self._relay_retx_interval_ms_default

    @property
    def auto_conf_network_tx(self) -> bool:
        return self._auto_conf_network_tx

    @property
    def network_tx_count_default(self) -> int:
        return self._network_tx_count_default

    @property
    def network_tx_interval_ms_default(self) -> int:
        return self._network_tx_interval_ms_default

    @property
    def auto_conf_sar(self) -> bool:
        return self._auto_conf_sar

    @property
    def sar_tx_segment_interval_step_default(self) -> int:
        return self._sar_tx_segment_interval_step_default

    @property
    def sar_tx_unicast_retrans_count_default(self) -> int:
        return self._sar_tx_unicast_retrans_count_default

    @property
    def sar_tx_unicast_retrans_wo_progress_count_default(self) -> int:
        return self._sar_tx_unicast_retrans_wo_progress_count_default

    @property
    def sar_tx_unicast_retrans_interval_step_default(self) -> int:
        return self._sar_tx_unicast_retrans_interval_step_default

    @property
    def sar_tx_unicast_retrans_interval_increment_default(self) -> int:
        return self._sar_tx_unicast_retrans_interval_increment_default

    @property
    def sar_tx_multicast_retrans_count_default(self) -> int:
        return self._sar_tx_multicast_retrans_count_default

    @property
    def sar_tx_multicast_retrans_interval_step_default(self) -> int:
        return self._sar_tx_multicast_retrans_interval_step_default

    @property
    def sar_rx_segments_threshold_default(self) -> int:
        return self._sar_rx_segments_threshold_default

    @property
    def sar_rx_ack_delay_increment_default(self) -> int:
        return self._sar_rx_ack_delay_increment_default

    @property
    def sar_rx_discard_timeout_default(self) -> int:
        return self._sar_rx_discard_timeout_default

    @property
    def sar_rx_segment_interval_step_default(self) -> int:
        return self._sar_rx_segment_interval_step_default

    @property
    def sar_rx_ack_retrans_count_default(self) -> int:
        return self._sar_rx_ack_retrans_count_default


class BtmeshDfuAppFwDistClientCfg:
    def __init__(self, section: SectionProxy):
        self.section = section
        sect = section
        # elem_index
        self._elem_index = sect.getint("elem_index")
        # appkey_index_default
        self._appkey_index_default = sect.getint("appkey_index_default")
        # ttl_default
        self._ttl_default = sect.getint("ttl_default")
        # upload_timeout_base_default
        self._upload_timeout_base_default = sect.getint("upload_timeout_base_default")
        # upload_chunk_size_default
        self._upload_chunk_size_default = sect.getint("upload_chunk_size_default")
        # dist_appkey_index_default
        self._dist_appkey_index_default = sect.getint("dist_appkey_index_default")
        # dist_ttl_default
        self._dist_ttl_default = sect.getint("dist_ttl_default")
        # dist_timeout_base_default
        self._dist_timeout_base_default = sect.getint("dist_timeout_base_default")
        # dist_poll_int_default
        self._dist_poll_int_default = sect.getfloat("dist_poll_int_default")
        # dist_retry_max_default
        self._dist_retry_max_default = sect.getint("dist_retry_max_default")
        # dist_retry_interval_default
        self._dist_retry_interval_default = sect.getfloat("dist_retry_interval_default")
        # dist_retry_interval_lpn_default
        self._dist_retry_interval_lpn_default = sect.getfloat(
            "dist_retry_interval_lpn_default"
        )
        # dist_retry_multicast_threshold_default
        self._dist_retry_multicast_threshold_default = sect.getint(
            "dist_retry_multicast_threshold_default"
        )
        # delete_retry_max_default
        self._delete_retry_max_default = sect.getint("delete_retry_max_default")
        # delete_retry_interval_default
        self._delete_retry_interval_default = sect.getfloat(
            "delete_retry_interval_default"
        )

        # Log dist_clt configuration
        sectname = sect.name
        logger.debug(f"{sectname}:elem_index: {self.elem_index}")
        logger.debug(f"{sectname}:appkey_index_default: {self.appkey_index_default}")
        logger.debug(f"{sectname}:ttl_default: {self.ttl_default}")
        logger.debug(
            f"{sectname}:upload_timeout_base_default: {self.upload_timeout_base_default}"
        )
        logger.debug(
            f"{sectname}:upload_chunk_size_default: {self.upload_chunk_size_default}"
        )
        logger.debug(
            f"{sectname}:dist_appkey_index_default: {self.dist_appkey_index_default}"
        )
        logger.debug(f"{sectname}:dist_ttl_default: {self.dist_ttl_default}")
        logger.debug(
            f"{sectname}:dist_timeout_base_default: {self.dist_timeout_base_default}"
        )
        logger.debug(f"{sectname}:dist_poll_int_default: {self.dist_poll_int_default}")
        logger.debug(
            f"{sectname}:dist_retry_max_default: {self.dist_retry_max_default}"
        )
        logger.debug(
            f"{sectname}:dist_retry_interval_default: "
            f"{self.dist_retry_interval_default}"
        )
        logger.debug(
            f"{sectname}:dist_retry_interval_lpn_default: "
            f"{self.dist_retry_interval_lpn_default}"
        )
        logger.debug(
            f"{sectname}:dist_retry_multicast_threshold_default: "
            f"{self.dist_retry_multicast_threshold_default}"
        )
        logger.debug(
            f"{sectname}:delete_retry_max_default: {self.delete_retry_max_default}"
        )
        logger.debug(
            f"{sectname}:delete_retry_interval_default: "
            f"{self.delete_retry_interval_default}"
        )

    @property
    def elem_index(self):
        return self._elem_index

    @property
    def appkey_index_default(self):
        return self._appkey_index_default

    @property
    def ttl_default(self):
        return self._ttl_default

    @property
    def upload_timeout_base_default(self):
        return self._upload_timeout_base_default

    @property
    def upload_chunk_size_default(self):
        return self._upload_chunk_size_default

    @property
    def dist_appkey_index_default(self):
        return self._dist_appkey_index_default

    @property
    def dist_ttl_default(self):
        return self._dist_ttl_default

    @property
    def dist_timeout_base_default(self):
        return self._dist_timeout_base_default

    @property
    def dist_poll_int_default(self):
        return self._dist_poll_int_default

    @property
    def dist_retry_max_default(self):
        return self._dist_retry_max_default

    @property
    def dist_retry_interval_default(self):
        return self._dist_retry_interval_default

    @property
    def dist_retry_interval_lpn_default(self):
        return self._dist_retry_interval_lpn_default

    @property
    def dist_retry_multicast_threshold_default(self):
        return self._dist_retry_multicast_threshold_default

    @property
    def delete_retry_max_default(self):
        return self._delete_retry_max_default

    @property
    def delete_retry_interval_default(self):
        return self._delete_retry_interval_default


class BtmeshDfuAppFwUpdateClientCfg:
    def __init__(self, section: SectionProxy):
        self.section = section
        sect = section
        # elem_index
        self._elem_index = sect.getint("elem_index")
        # appkey_index_default
        self._appkey_index_default = sect.getint("appkey_index_default")
        # ttl_default
        self._ttl_default = sect.getint("ttl_default")
        # timeout_base_default
        self._timeout_base_default = sect.getint("timeout_base_default")
        # max_target_nodes
        self._max_target_nodes = sect.getint("max_target_nodes")
        # dfu_chunk_size_default
        self._dfu_chunk_size_default = sect.getint("dfu_chunk_size_default")
        # dfu_retry_max_default
        self._dfu_retry_max_default = sect.getint("dfu_retry_max_default")
        # dfu_retry_interval_default
        self._dfu_retry_interval_default = sect.getfloat("dfu_retry_interval_default")
        # dfu_retry_interval_lpn_default
        self._dfu_retry_interval_lpn_default = sect.getfloat(
            "dfu_retry_interval_lpn_default"
        )
        # dfu_retry_multicast_threshold_default
        self._dfu_retry_multicast_threshold_default = sect.getint(
            "dfu_retry_multicast_threshold_default"
        )

        # Log dfu_clt configuration
        sectname = sect.name
        logger.debug(f"{sectname}:elem_index: {self.elem_index}")
        logger.debug(f"{sectname}:appkey_index_default: {self.appkey_index_default}")
        logger.debug(f"{sectname}:ttl_default: {self.ttl_default}")
        logger.debug(f"{sectname}:timeout_base_default: {self.timeout_base_default}")
        logger.debug(f"{sectname}:max_target_nodes: {self.max_target_nodes}")
        logger.debug(
            f"{sectname}:dfu_chunk_size_default: {self.dfu_chunk_size_default}"
        )
        logger.debug(f"{sectname}:dfu_retry_max_default: {self.dfu_retry_max_default}")
        logger.debug(
            f"{sectname}:dfu_retry_interval_default: "
            f"{self.dfu_retry_interval_default}"
        )
        logger.debug(
            f"{sectname}:dfu_retry_interval_lpn_default: "
            f"{self.dfu_retry_interval_lpn_default}"
        )
        logger.debug(
            f"{sectname}:dfu_retry_multicast_threshold_default: "
            f"{self.dfu_retry_multicast_threshold_default}"
        )

    @property
    def elem_index(self):
        return self._elem_index

    @property
    def appkey_index_default(self):
        return self._appkey_index_default

    @property
    def ttl_default(self):
        return self._ttl_default

    @property
    def timeout_base_default(self):
        return self._timeout_base_default

    @property
    def max_target_nodes(self):
        return self._max_target_nodes

    @property
    def dfu_chunk_size_default(self):
        return self._dfu_chunk_size_default

    @property
    def dfu_retry_max_default(self):
        return self._dfu_retry_max_default

    @property
    def dfu_retry_interval_default(self):
        return self._dfu_retry_interval_default

    @property
    def dfu_retry_interval_lpn_default(self):
        return self._dfu_retry_interval_lpn_default

    @property
    def dfu_retry_multicast_threshold_default(self):
        return self._dfu_retry_multicast_threshold_default


class BtmeshDfuAppBlobTransferClientCfg:
    def __init__(self, section: SectionProxy):
        self.section = section
        sect = section
        # elem_index
        self._elem_index = sect.getint("elem_index")
        # max_servers
        self._max_servers = sect.getint("max_servers")
        # max_blocks
        self._max_blocks = sect.getint("max_blocks")
        # max_chunks_per_block
        self._max_chunks_per_block = sect.getint("max_chunks_per_block")
        # Log mbt_clt configuration
        sectname = sect.name
        logger.debug(f"{sectname}:elem_index: {self.elem_index}")
        logger.debug(f"{sectname}:max_servers: {self.max_servers}")
        logger.debug(f"{sectname}:max_blocks: {self.max_blocks}")
        logger.debug(f"{sectname}:max_chunks_per_block: {self.max_chunks_per_block}")

    @property
    def elem_index(self):
        return self._elem_index

    @property
    def max_servers(self):
        return self._max_servers

    @property
    def max_blocks(self):
        return self._max_blocks

    @property
    def max_chunks_per_block(self):
        return self._max_chunks_per_block


class BtmeshDfuAppNetworkCfg:
    MAX_APPKEY_COUNT = 32

    def __init__(self, section: SectionProxy):
        self.section = section
        sect = section
        # random_netkey
        self._random_netkey = sect.getboolean("random_netkey")
        # netkey
        nkey = bytes.fromhex(sect["netkey"])
        if (not self.random_netkey) and (len(nkey) != 16):
            raise ValueError("Invalid netkey config value size.")
        self._netkey = nkey
        # random_appkey
        self._random_appkey = sect.getboolean("random_appkey")
        # appkeys
        raw_akeys = []
        if "appkey" in sect:
            raw_akeys.append(sect["appkey"])
        else:
            for idx in range(self.MAX_APPKEY_COUNT):
                appkey_name = f"appkey{idx}"
                if appkey_name in sect:
                    raw_akeys.append(sect[appkey_name])
                else:
                    break
        self._appkeys = []
        for raw_akey in raw_akeys:
            akey = bytes.fromhex(raw_akey)
            if (not self.random_appkey) and (len(akey) != 16):
                raise ValueError("Invalid appkey config value size.")
            self._appkeys.append(akey)
        if not self.random_appkey and not len(self.appkeys):
            raise ValueError("At least one appkey shall be configured.")
        # appkey_cnt
        if self.random_appkey:
            self._appkey_cnt = sect.getint("random_appkey_cnt")
            if self.appkey_cnt < 1:
                raise ValueError(
                    f"The random_appkey_cnt shall be positive integer "
                    f"but it is {self.appkey_cnt}."
                )
        else:
            self._appkey_cnt = len(self.appkeys)
        # prov_node_name
        self._prov_node_name = sect.get("prov_node_name")
        btmesh.util.validate_name(self.prov_node_name)

        # Log network configuration
        sectname = sect.name
        logger.debug(f"{sectname}:random_netkey: {self.random_netkey}")
        logger.debug(f"{sectname}:netkey: {self.netkey.hex().upper()}")
        logger.debug(f"{sectname}:random_appkey: {self.random_appkey}")
        for idx, appkey in enumerate(self.appkeys):
            logger.debug(f"{sectname}:appkey{idx}: {appkey.hex().upper()}")
        logger.debug(f"{sectname}:appkey_cnt: {self.appkey_cnt}")
        logger.debug(f"{sectname}:prov_node_name: {self.prov_node_name}")

    @property
    def random_netkey(self) -> bool:
        return self._random_netkey

    @property
    def netkey(self) -> bytes:
        return self._netkey

    @property
    def random_appkey(self) -> bool:
        return self._random_appkey

    @property
    def appkey_cnt(self) -> int:
        return self._appkey_cnt

    @property
    def appkeys(self) -> Iterable[bytes]:
        return self._appkeys

    @property
    def prov_node_name(self) -> str:
        return self._prov_node_name


class BtmeshDfuAppPersistenceCfg:
    def __init__(self, section: SectionProxy):
        self.section = section
        sect = section
        # path
        self._path = Path(sect["path"])
        # default_on_failed_load
        self._default_on_failed_load = sect.getboolean("default_on_failed_load")
        # backup_on_failed_load
        self._backup_on_failed_load = sect.getboolean("backup_on_failed_load")
        # Log persistence configuration
        sectname = sect.name
        logger.debug(f"{sectname}:path: {self.path}")
        logger.debug(
            f"{sectname}:default_on_failed_load: {self.default_on_failed_load}"
        )
        logger.debug(f"{sectname}:backup_on_failed_load: {self.backup_on_failed_load}")

    @property
    def path(self):
        return self._path

    @property
    def default_on_failed_load(self):
        return self._default_on_failed_load

    @property
    def backup_on_failed_load(self):
        return self._backup_on_failed_load


class BtmeshDfuAppProxyCfg:
    def __init__(self, section: SectionProxy):
        self.section = section
        sect = section
        # scan_timeout_default
        self._scan_timeout_default = sect.getfloat("scan_timeout_default")
        # conn_open_timeout_ms_default
        self._conn_open_timeout_ms_default = sect.getfloat(
            "conn_open_timeout_ms_default"
        )
        # conn_min_interval_ms_default
        self._conn_min_interval_ms_default = sect.getfloat(
            "conn_min_interval_ms_default"
        )
        # conn_max_interval_ms_default
        self._conn_max_interval_ms_default = sect.getfloat(
            "conn_max_interval_ms_default"
        )
        # conn_latency_default
        self._conn_latency_default = sect.getint("conn_latency_default")
        # conn_timeout_ms_default
        self._conn_timeout_ms_default = sect.getfloat("conn_timeout_ms_default")
        # conn_min_ce_length_ms_default
        self._conn_min_ce_length_ms_default = sect.getfloat(
            "conn_min_ce_length_ms_default"
        )
        # conn_max_ce_length_ms_default
        self._conn_max_ce_length_ms_default = sect.getfloat(
            "conn_max_ce_length_ms_default"
        )
        # Log persistence configuration
        sectname = sect.name
        logger.debug(f"{sectname}:scan_timeout_default: {self.scan_timeout_default}")
        logger.debug(
            f"{sectname}:conn_open_timeout_ms_default: "
            f"{self.conn_open_timeout_ms_default}"
        )
        logger.debug(
            f"{sectname}:conn_min_interval_ms_default: "
            f"{self.conn_min_interval_ms_default}"
        )
        logger.debug(
            f"{sectname}:conn_max_interval_ms_default: "
            f"{self.conn_max_interval_ms_default}"
        )
        logger.debug(f"{sectname}:conn_latency_default: {self.conn_latency_default}")
        logger.debug(
            f"{sectname}:conn_timeout_ms_default: {self.conn_timeout_ms_default}"
        )
        logger.debug(
            f"{sectname}:conn_min_ce_length_ms_default: "
            f"{self.conn_min_ce_length_ms_default}"
        )
        logger.debug(
            f"{sectname}:conn_max_ce_length_ms_default: "
            f"{self.conn_max_ce_length_ms_default}"
        )
        btmesh.util.validate_conn_params_range(
            min_interval_ms=self.conn_min_interval_ms_default,
            max_interval_ms=self.conn_max_interval_ms_default,
            latency=self.conn_latency_default,
            timeout_ms=self.conn_timeout_ms_default,
            min_ce_length_ms=self.conn_min_ce_length_ms_default,
            max_ce_length_ms=self.conn_max_ce_length_ms_default,
        )

    @property
    def scan_timeout_default(self) -> float:
        return self._scan_timeout_default

    @property
    def conn_open_timeout_ms_default(self) -> float:
        return self._conn_open_timeout_ms_default

    @property
    def conn_min_interval_ms_default(self) -> float:
        return self._conn_min_interval_ms_default

    @property
    def conn_max_interval_ms_default(self) -> float:
        return self._conn_max_interval_ms_default

    @property
    def conn_latency_default(self) -> int:
        return self._conn_latency_default

    @property
    def conn_timeout_ms_default(self) -> float:
        return self._conn_timeout_ms_default

    @property
    def conn_min_ce_length_ms_default(self) -> float:
        return self._conn_min_ce_length_ms_default

    @property
    def conn_max_ce_length_ms_default(self) -> float:
        return self._conn_max_ce_length_ms_default

    @property
    def conn_params_range(self) -> ConnectionParamsRange:
        return ConnectionParamsRange(
            min_interval_ms=self.conn_min_interval_ms_default,
            max_interval_ms=self.conn_max_interval_ms_default,
            latency=self.conn_latency_default,
            timeout_ms=self.conn_timeout_ms_default,
            min_ce_length_ms=self.conn_min_ce_length_ms_default,
            max_ce_length_ms=self.conn_max_ce_length_ms_default,
        )


class BtmeshDfuAppResetCfg:
    def __init__(self, section: SectionProxy):
        self.section = section
        sect = section
        # factory_reset_delay_s
        self._factory_reset_delay_s = sect.getfloat("factory_reset_delay_s")
        # Log reset configuration
        sectname = self.section.name
        logger.debug(f"{sectname}:factory_reset_delay_s: {self.factory_reset_delay_s}")

    @property
    def factory_reset_delay_s(self):
        return self._factory_reset_delay_s


class BtmeshDfuAppUICfg:
    VALID_FORMATS = ("str", "hex")

    def __init__(self, section: SectionProxy):
        self.section = section
        sect = section
        # table_width_default
        self._table_width_default = sect.getint("table_width_default")
        # fwid_format
        self._fwid_format = sect["fwid_format"]
        if self.fwid_format not in self.VALID_FORMATS:
            opt_name = "fwid_format"
            valid_formats = ",".join(self.VALID_FORMATS)
            raise ValueError(
                f"Invalid {sect.name}:{opt_name} configuration option. "
                f"Valid formats are: {valid_formats}."
            )
        # metadata_format
        self._metadata_format = sect["metadata_format"]
        if self.metadata_format not in self.VALID_FORMATS:
            opt_name = "metadata_format"
            valid_formats = ",".join(self.VALID_FORMATS)
            raise ValueError(
                f"Invalid {sect.name}:{opt_name} configuration option. "
                f"Valid formats are: {valid_formats}."
            )
        # node_format
        opt_name = "node_format"
        node_format = sect[opt_name]
        self.validate_node_format(sect, opt_name, node_format)
        self._node_format = node_format
        # elem_format
        opt_name = "elem_format"
        elem_format = sect[opt_name]
        self.validate_elem_format(sect, opt_name, elem_format)
        self._elem_format = elem_format

        # Log reset configuration
        sectname = self.section.name
        logger.debug(f"{sectname}:table_width_default: {self.table_width_default}")
        logger.debug(f"{sectname}:fwid_format: {self.fwid_format}")
        logger.debug(f"{sectname}:metadata_format: {self.metadata_format}")
        logger.debug(f"{sectname}:node_format: {self.node_format}")
        logger.debug(f"{sectname}:elem_format: {self.elem_format}")

    def validate_node_format(self, sect: SectionProxy, opt_name: str, node_format: str):
        # Test the format string with dummy data to make sure that valid
        # node_format string was provided.
        try:
            node_format.format(
                name="NodeName",
                uuid=bytes.fromhex("0123456789ABCDEFFEDCBA9876543210"),
                prim_addr=0x2000,
            )
        except Exception as e:
            raise ValueError(
                f"Invalid {sect.name}:{opt_name} configuration option. "
                f"The format string is invalid."
            ) from e

    def validate_elem_format(self, sect: SectionProxy, opt_name: str, elem_format: str):
        # Test the format string with dummy data to make sure that valid
        # elem_format string was provided.
        try:
            elem_format.format(
                name="NodeName",
                uuid=bytes.fromhex("0123456789ABCDEFFEDCBA9876543210"),
                prim_addr=0x2000,
                elem_index=0,
                elem_addr=0x2003,
            )
        except Exception as e:
            raise ValueError(
                f"Invalid {sect.name}:{opt_name} configuration option. "
                f"The format string is invalid."
            ) from e

    @property
    def table_width_default(self) -> int:
        return self._table_width_default

    @property
    def fwid_format(self) -> str:
        return self._fwid_format

    @property
    def metadata_format(self) -> str:
        return self._metadata_format

    @property
    def node_format(self) -> str:
        return self._node_format

    @property
    def elem_format(self) -> str:
        return self._elem_format


class BtmeshDfuAppCfg:
    @staticmethod
    def bool2str(b):
        return str(bool(b)).lower()

    @staticmethod
    def save_default_cfg_file(file):
        file.write(DEFAULT_APP_CFG_INI)

    def _create_cfg_sections(self):
        self.appgroup = BtmeshDfuAppGroupCfg(self.cp["appgroup"])
        self.common = BtmeshDfuCommonCfg(self.cp["common"])
        self.conf = BtmeshDfuAppConfCfg(self.cp["conf"])
        self.dist_clt = BtmeshDfuAppFwDistClientCfg(self.cp["dist_clt"])
        self.dfu_clt = BtmeshDfuAppFwUpdateClientCfg(self.cp["dfu_clt"])
        self.mbt_clt = BtmeshDfuAppBlobTransferClientCfg(self.cp["mbt_clt"])
        self.network = BtmeshDfuAppNetworkCfg(self.cp["network"])
        self.persistence = BtmeshDfuAppPersistenceCfg(self.cp["persistence"])
        self.proxy = BtmeshDfuAppProxyCfg(self.cp["proxy"])
        self.reset = BtmeshDfuAppResetCfg(self.cp["reset"])
        self.ui = BtmeshDfuAppUICfg(self.cp["ui"])

    def load_cfg(self, file):
        logger.info("BT Mesh Host DFU configuration is loading...")
        self.cp.read_file(file)
        self._create_cfg_sections()

    def __init__(self):
        self.cp = ConfigParser(interpolation=ExtendedInterpolation())
        default_ini = io.StringIO(DEFAULT_APP_CFG_INI)
        self.cp.read_file(default_ini)
        self._create_cfg_sections()


app_cfg = BtmeshDfuAppCfg()
