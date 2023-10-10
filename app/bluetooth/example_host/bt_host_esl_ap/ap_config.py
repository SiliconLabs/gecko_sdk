"""
ESL AP configuration.
"""
# Copyright 2023 Silicon Laboratories Inc. www.silabs.com
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
# Common constants used both by the BLE and ESL threads

# alternates GATT Write With or Without Response requests and enables other dirty hacks if set to True
IOP_TEST = False

# Tag synchronization timeout in seconds
TAG_SYNC_TIMEOUT = 3600 # one hour according to ESLP spec.
TAG_UNASSOCIATE_TIMEOUT = 2 * TAG_SYNC_TIMEOUT # one hour more after sync timeout according to ESLP spec.
TAG_SYNC_KEEPING_INTERVAL = TAG_SYNC_TIMEOUT / 2 # send NOP commands in every 30 minutes

# Max number of images to upload automatically
IMAGE_MAX_AUTO_UPLOAD_COUNT = 2

# Connection timeout
CONNECTION_TIMEOUT_SEC = 10

# Retry count for ESL command opcodes re-sending
ESL_CMD_MAX_RETRY_COUNT = 3

# Pending count for connection requests: 1 is the minmum ad also the safest value, but auto provisioning will be the slowest
ESL_CMD_MAX_PENDING_CONNECTION_REQUEST_COUNT = 2

# Tags in a group in automated mode addressing
ESL_MAX_TAGS_IN_AUTO_GROUP = 16

# Default RSSI threshold in dBm
RSSI_THRESHOLD = -60

# The timeout is needed to get the KeyboardInterrupt.
# The timeout value is a tradeoff between CPU load and KeyboardInterrupt response time.
# timeout=None: minimal CPU usage, KeyboardInterrupt not recognized until blocking wait is released.
# timeout=0: maximal CPU usage, KeyboardInterrupt recognized immediately.
# See the documentation of Queue.get method for details.
BLOCKING_WAIT_TIMEOUT = 0.1
