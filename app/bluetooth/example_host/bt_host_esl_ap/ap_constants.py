"""
ESL AP constants.
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

# Parameters for periodic advertisement
PA_INTERVAL_ABS_MIN = 15 # not PAwR but ESL (reasonable) limit!
PA_INTERVAL_ABS_MAX = 81918.75
PA_SUBEVENT_MIN = 1
PA_SUBEVENT_MAX = 128
PA_SUBEVENT_INTERVAL_MIN = 6
PA_SUBEVENT_INTERVAL_MAX = 255
PA_RESPONSE_SLOT_DELAY_MIN = 2 # not PAwR but ESL (reasonable) limit!
PA_RESPONSE_SLOT_DELAY_MAX = 254
PA_RESPONSE_SLOT_SPACING_MIN = 6 # not PAwR but ESL (reasonable) limit!
PA_RESPONSE_SLOT_SPACING_MAX = 255
PA_RESPONSE_SLOT_NUMBERS_MIN = 1
PA_RESPONSE_SLOT_NUMBERS_MAX = 23 # not PAwR but ESL (reasonable) limit!

AUX_SYNC_IND_PDU_MAX_SKIP_COUNT = 6 # from Core Vol6 PartB 4.4.5.1

# OTS constants
OTS_RESP_OBJECT_ID_NOT_FOUND = 0x08

# Address types
ADDRESS_TYPE_PUBLIC_ADDRESS = 0
ADDRESS_TYPE_STATIC_ADDRESS = 1

# Display type Assigned Numbers
ESL_DISPLAY_TYPE_BLACK_WHITE = 0x01
ESL_DISPLAY_TYPE_3_GRAY_SCALE = 0x02
ESL_DISPLAY_TYPE_4_GRAY_SCALE = 0x03
ESL_DISPLAY_TYPE_8_GRAY_SCALE = 0x04
ESL_DISPLAY_TYPE_16_GRAY_SCALE = 0x05
ESL_DISPLAY_TYPE_RED_BLACK_WHITE = 0x06
ESL_DISPLAY_TYPE_YELLOW_BLACK_WHITE = 0x07
ESL_DISPLAY_TYPE_RED_YELLOW_BLACK_WHITE = 0x08
ESL_DISPLAY_TYPE_7_COLOR = 0x09
ESL_DISPLAY_TYPE_16_COLOR = 0x0A
ESL_DISPLAY_TYPE_FULL_RGB = 0x0B

# Silabs ESL example display types 
ESL_WSTK_DISPLAY_TYPE = ESL_DISPLAY_TYPE_BLACK_WHITE
ESL_EPAPER_DISPLAY_TYPE = ESL_DISPLAY_TYPE_RED_BLACK_WHITE

# OTS Service
# Mask to check if OACP Write Op Code and Truncation of Objects are supported
OTS_FEATURES_REQUIRED_MASK = 0b10100000

SIG_VENDOR_ID_SILABS = 0x02ff

VENDOR_ID_STRINGS = {
    SIG_VENDOR_ID_SILABS: "Silicon Labs"
}

# Periodic advertisement field size in bytes
MAX_ESL_PAYLOAD_SIZE = 48

# Adverti Data and EAD constants
AD_TYPE_FIELD_SIZE = 1
AD_LENGTH_FIELD_SIZE = 1
AD_FRAME_OVERHEAD = AD_LENGTH_FIELD_SIZE + AD_TYPE_FIELD_SIZE
EAD_RANDOMIZER_SIZE = 5
EAD_MIC_SIZE = 4
EAD_IV_SIZE = 8
EAD_PACKET_OVERHEAD = AD_FRAME_OVERHEAD + EAD_RANDOMIZER_SIZE + EAD_MIC_SIZE
MAX_PA_PAYLOAD_SIZE = AD_FRAME_OVERHEAD + EAD_PACKET_OVERHEAD + MAX_ESL_PAYLOAD_SIZE

# Encrypted Data AD Type - BARB assigned number
EAD_AD_TYPE              = 0x31
# ESL AD Type -BARB assigned number
ESL_AD_TYPE              = 0x34

# ESL TLVs
TLV_OPCODE_PING = 0x00
TLV_OPCODE_UNASSOCIATE = 0x01
TLV_OPCODE_SERVICE_RST = 0x02
TLV_OPCODE_FACTORY_RST = 0x03
TLV_OPCODE_UPDATE_COMPLETE = 0x04
TLV_OPCODE_READ_SENSOR = 0x10
TLV_OPCODE_REFRESH_DISPLAY = 0x11
TLV_OPCODE_DISPLAY_IMAGE = 0x20
TLV_OPCODE_DISPLAY_TIMED_IMAGE = 0x60
TLV_OPCODE_LED_CONTROL = 0xB0
TLV_OPCODE_LED_TIMED_CONTROL = 0xF0
TLV_OPCODE_VENDOR_SPECIFIC = 0x0F
# Silabs vendor specific opcode example
TLV_OPCODE_SILABS_SKIP_SET = 0x1F

# ESL response opcodes
TLV_RESPONSE_ERROR = 0x00
TLV_RESPONSE_LED_STATE = 0x01
TLV_RESPONSE_BASIC_STATE = 0x10
TLV_RESPONSE_DISPLAY_STATE = 0x11
TLV_RESPONSE_READ_SENSOR = 0x0E
TLV_RESPONSE_VENDOR_SPECIFIC = 0x0F
# Silabs vendor specific opcode example
TLV_RESPONSE_SILABS_SKIP = 0x0F

SUPPORTED_RESPONSES = [TLV_RESPONSE_ERROR, TLV_RESPONSE_LED_STATE, TLV_RESPONSE_BASIC_STATE,
                      TLV_RESPONSE_DISPLAY_STATE, TLV_RESPONSE_READ_SENSOR]

RESPONSE_STRINGS = {
    TLV_RESPONSE_ERROR: "ESL Error",
    TLV_RESPONSE_LED_STATE: "LED State",
    TLV_RESPONSE_BASIC_STATE: "Basic state",
    TLV_RESPONSE_DISPLAY_STATE: "Display state",
    TLV_RESPONSE_READ_SENSOR: "Sensor value",
    TLV_RESPONSE_SILABS_SKIP: "New PAwR skip parameter"
}

# Basic State response flags
BASIC_STATE_FLAG_SERVICE_NEEDED = (1 << 0)
BASIC_STATE_FLAG_SYNCHRONIZED = (1 << 1)
BASIC_STATE_FLAG_ACTIVE_LED = (1 << 2)
BASIC_STATE_FLAG_PENDING_LED_UPDATE = (1 << 3)
BASIC_STATE_FLAG_PENDING_DISPLAY_UPDATE = (1 << 4)

# Textual representation of the basic state flags
BASIC_STATE_STRINGS = {
    BASIC_STATE_FLAG_SERVICE_NEEDED: "Service needed",
    BASIC_STATE_FLAG_SYNCHRONIZED: "Synchronized",
    BASIC_STATE_FLAG_ACTIVE_LED: "Active LED",
    BASIC_STATE_FLAG_PENDING_LED_UPDATE: "Pending LED update",
    BASIC_STATE_FLAG_PENDING_DISPLAY_UPDATE: "Pending display update"
}

# Error response codes
ERROR_RESPONSE_UNSPECIFIED_ERR = 0x01
ERROR_RESPONSE_INVALID_OPCODE = 0x02
ERROR_RESPONSE_INVALID_STATE = 0x03
ERROR_RESPONSE_INVALID_IMAGE_INDEX = 0x04
ERROR_RESPONSE_IMAGE_NOT_AVAILABLE = 0x05
ERROR_RESPONSE_INVALID_PARAMETERS = 0x06
ERROR_RESPONSE_CAPACITY_LIMIT = 0x07
ERROR_RESPONSE_INSUFFICIENT_BATTERY = 0x08
ERROR_RESPONSE_INSUFFICIENT_RESOURCES = 0x09
ERROR_RESPONSE_RETRY = 0x0A
ERROR_RESPONSE_QUEUE_FULL = 0x0B
ERROR_RESPONSE_INPLAUSIBLE_ABS_TIME = 0x0C

ERROR_RESPONSE_STRINGS = {
    ERROR_RESPONSE_UNSPECIFIED_ERR: "Unspecified error",
    ERROR_RESPONSE_INVALID_OPCODE: "Invalid opcode",
    ERROR_RESPONSE_INVALID_STATE: "Invalid state",
    ERROR_RESPONSE_INVALID_IMAGE_INDEX: "Invalid image index",
    ERROR_RESPONSE_IMAGE_NOT_AVAILABLE: "Image not available",
    ERROR_RESPONSE_INVALID_PARAMETERS: "Invalid parameter(s)",
    ERROR_RESPONSE_CAPACITY_LIMIT: "Capacity limit",
    ERROR_RESPONSE_INSUFFICIENT_BATTERY: "Insufficient battery",
    ERROR_RESPONSE_INSUFFICIENT_RESOURCES: "Insufficient resources",
    ERROR_RESPONSE_RETRY: "Retry",
    ERROR_RESPONSE_QUEUE_FULL: "Queue full",
    ERROR_RESPONSE_INPLAUSIBLE_ABS_TIME: "Implausible absolute time"
}

# LED
LED_PATTERN_LENGTH = 5
LED_DEFAULT_GAMUT = b"\x7f"  # white, 50% brightness by default
LED_DEFAULT_PATTERN = b"\x76\xef\x96\x08\x91" # low-res PPM sine pattern
LED_DEFAULT_PERIOD = b"\x07\x06" # about 2Hz flash rate
LED_DEFAULT_DURATION = b"\x15\x00" # 10 sec duration
LED_DEFAULT_REPEATS = b"\x14\x00" # repeat 10 times

# ESL maximum delay is 48 days by spec
ESL_MAX_DELAY = (48 * 24 * 60 * 60 * 1000) #in milliseconds

# Tags in a group, overall limit
ESL_MAX_TAGS_IN_GROUP = 255
BROADCAST_ADDRESS = 0xFF

VALID_BD_ADDRESS_REGEX = r"(([a-fA-F0-9]{2}:){5}[a-fA-F0-9]{2}$)"
VALID_ESL_ID_NUMBER_REGEX = r"\b(0|[1]?\d\d?|2[0-4]\d|25[0-5])\b"

# Subevent
SUBEVENT_START = "subevent_start"
SUBEVENT_DATA_COUNT = "subevent_data_count"

# General command codes
CMD_AP_CONTROL_ADV_ENABLE = 101
CMD_AP_CONTROL_CP_RESPONSE = 102
CMD_AP_CONTROL_IT_RESPONSE = 103

# Controller commands for ESL demo
CCMD_CONNECT = 0
CCMD_CONFIG = 1
CCMD_DISCONNECT = 2
CCMD_IMAGE_UPDATE = 3
CCMD_REQUEST_DATA = 4
CCMD_DISPLAY_IMAGE = 5
CCMD_LED = 6
CCMD_LIST = 7
CCMD_PING = 8
CCMD_UNASSOCIATE = 9
CCMD_UNKNOWN = 100

CCMD_STRINGS = {
    CCMD_CONNECT: "Connect command arrived from controller",
    CCMD_DISCONNECT: "Disconnect command arrived from controller",
    CCMD_CONFIG: "Config command arrived from controller",
    CCMD_IMAGE_UPDATE: "Image update command arrived from controller",
    CCMD_DISPLAY_IMAGE: "Display image command arrived from controller",
    CCMD_LED: "Led command arrived from controller",
    CCMD_LIST: "List command arrived from controller",
    CCMD_PING: "Ping command arrived from controller"
}

REQUEST_IMAGE_DATA_HEADER = b"\xef"
REQUEST_IMAGE_DATA_RESERVED = b"\x00"
CONTROLLER_REQUEST_MORE_DATA = 0
CONTROLLER_REQUEST_LAST_DATA = 1
CONTROLLER_COMMAND_SUCCESS = 0
CONTROLLER_COMMAND_FAIL = 1

# Advertising timeout [s]
ADVERTISING_TIMEOUT = 30
