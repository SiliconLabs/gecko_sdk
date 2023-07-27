"""
ESL Tag.
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

from collections import namedtuple
from datetime import datetime as dt
from ap_constants import *
from ap_config import IOP_TEST
from ap_logger import getLogger
from ap_sensor import SENSOR_INFO_LENGTH_SHORT, SENSOR_INFO_LENGTH_LONG, SENSOR_TYPES
import esl_lib_wrapper as elw

PNP_VENDOR_ID_SOURCE_SIG = 1
DISPLAY_INFO_STRUCT_SIZE = 5

class Tag():
    """ ESL Tag """
    _counter = 0

    def __init__(self, address, dummy=False):
        self.id = type(self)._counter
        if not dummy:
            type(self)._counter +=1
        # ESL specific attributes
        self.ble_address = address
        self.ots_image_type = {}
        self.pending_unassociate = False
        self.state = ST_UNASSOCIATED
        self.last_req_timestamp = dt.now().timestamp()
        self.last_resp_timestamp = dt.now().timestamp()
        self.unresp_command_number = 0
        self.basic_state_flags = 0
        self.logger = getLogger()
        self.gatt_values = {}
        self.gatt_write_values = {}
        self.gattdb_handles = None
        self.auto_image_count = 0

    def get_value_as_bytes(self, key) -> bytes:
        try:
            return self.gatt_values[key]
        except KeyError:
            return None

    def get_value_as_int(self, key):
        try:
            return int.from_bytes(self.gatt_values[key], 'little')
        except KeyError:
            return None

    @property
    def provisioned(self):
        """ Tell if the tag is provisioned """
        return self.esl_address is not None and self.response_key is not None and self.ap_sync_key is not None and self.time is not None

    @property
    def skip_get_info(self):
        """ Tell if getting tag info can be skipped during connecting """
        return elw.ESL_LIB_DATA_TYPE_GATT_CONTROL_POINT in self.gatt_values

    @property
    def esl_address(self):
        return self.get_value_as_int(elw.ESL_LIB_DATA_TYPE_GATT_ESL_ADDRESS)

    @property
    def esl_id(self):
        if self.esl_address is None:
            return None
        return self.esl_address & 0xff

    @property
    def group_id(self):
        if self.esl_address is None:
            return None
        return (self.esl_address >> 8) & 0x7f

    @property
    def ap_sync_key(self):
        return self.get_value_as_bytes(elw.ESL_LIB_DATA_TYPE_GATT_AP_SYNC_KEY)

    @property
    def response_key(self):
        return self.get_value_as_bytes(elw.ESL_LIB_DATA_TYPE_GATT_RESPONSE_KEY)

    @property
    def time(self):
        """ Current time in milliseconds """
        return self.get_value_as_int(elw.ESL_LIB_DATA_TYPE_GATT_CURRENT_TIME)

    @property
    def led_type(self):
        """ LED types represented on one byte per LED """
        return self.get_value_as_bytes(elw.ESL_LIB_DATA_TYPE_GATT_LED_INFO)

    @property
    def max_image_index(self):
        return self.get_value_as_int(elw.ESL_LIB_DATA_TYPE_GATT_IMAGE_INFO)

    @property
    def sensor_info(self):
        try:
            value = self.gatt_values[elw.ESL_LIB_DATA_TYPE_GATT_SENSOR_INFO]
        except KeyError:
            return []
        index = 0
        sensor_info = []
        while index < len(value):
            if value[index] == 0:
                sensor_info.append(int.from_bytes(value[index + 1: index + SENSOR_INFO_LENGTH_SHORT], "little"))
                index += SENSOR_INFO_LENGTH_SHORT
            else:
                sensor_info.append(int.from_bytes(value[index + 1: index + SENSOR_INFO_LENGTH_LONG], "little"))
                index += SENSOR_INFO_LENGTH_LONG
        return sensor_info

    @property
    def display_info(self):
        try:
            value = self.gatt_values[elw.ESL_LIB_DATA_TYPE_GATT_DISPLAY_INFO]
        except KeyError:
            return []
        if (len(value) % DISPLAY_INFO_STRUCT_SIZE != 0):
            self.logger.error("Invalid display information")
            return []
        field_index = 0
        display_info = []
        TagDisplayInfo = namedtuple("TagDisplayInfo", ["width", "height", "type"])
        while (field_index < len(value)):
            display_info.append(TagDisplayInfo(int.from_bytes(value[field_index : field_index + 2], "little"),
                                               int.from_bytes(value[field_index + 2 : field_index + 4], "little"),
                                               value[field_index + 4]))
            field_index += DISPLAY_INFO_STRUCT_SIZE
        return display_info

    @property
    def display_count(self):
        return len(self.display_info)

    @property
    def has_image_transfer(self):
        try:
            value = self.gatt_values[elw.ESL_LIB_DATA_TYPE_GATT_OTS_FEATURE]
        except KeyError:
            return False
        # Cut the unnecessary parts of the byte array and use the mask
        # If the OTS Feature of the Tag supports truncation and write opcodes
        # then the Tag has image transfer
        if int.from_bytes(value[0:5], "little") & OTS_FEATURES_REQUIRED_MASK == OTS_FEATURES_REQUIRED_MASK:
            return True
        return False

    @property
    def pnp_vendor_id(self):
        try:
            value = self.gatt_values[elw.ESL_LIB_DATA_TYPE_GATT_PNP_ID]
        except KeyError:
            return None
        if value[0] == PNP_VENDOR_ID_SOURCE_SIG:
            return int.from_bytes(value[1:3], "little")
        return None

    @property
    def pnp_product_id(self):
        try:
            value = self.gatt_values[elw.ESL_LIB_DATA_TYPE_GATT_PNP_ID]
        except KeyError:
            return None
        if value[0] == PNP_VENDOR_ID_SOURCE_SIG:
            return int.from_bytes(value[3:5], "little")
        return None

    @property
    def pnp_product_version(self):
        try:
            value = self.gatt_values[elw.ESL_LIB_DATA_TYPE_GATT_PNP_ID]
        except KeyError:
            return None
        if value[0] == PNP_VENDOR_ID_SOURCE_SIG:
            return int.from_bytes(value[5:7], "little")
        return None

    @property
    def serial_number(self):
        return self.get_value_as_bytes(elw.ESL_LIB_DATA_TYPE_GATT_SERIAL_NUMBER)

    def set_valid(self):
        """ Set object as a real/valid ESL (as opposed to a virtual ones used for simulation, or those unassociated yet) """
        self.gatt_values[elw.ESL_LIB_DATA_TYPE_GATT_CONTROL_POINT] = True # ESL Control Point is a mandatory characteristic

    def reset(self):
        """ Reset object states """
        keys = [elw.ESL_LIB_DATA_TYPE_GATT_AP_SYNC_KEY,
                elw.ESL_LIB_DATA_TYPE_GATT_RESPONSE_KEY,
                elw.ESL_LIB_DATA_TYPE_GATT_CURRENT_TIME,
                elw.ESL_LIB_DATA_TYPE_GATT_ESL_ADDRESS]
        self.gattdb_handles = None
        self.pending_unassociate = False
        self.update_timestamps()
        self.state = ST_UNSYNCHRONIZED
        self.update_flags(BASIC_STATE_FLAG_SYNCHRONIZED,False)
        self.gatt_write_values = {key: value for key, value in self.gatt_values.items() if key in keys}
        # keep ESL Address if exists, delete the rest - also make the ESL object invalid for possible future re-discovery
        self.gatt_values = {key: value for key, value in self.gatt_values.items() if key == elw.ESL_LIB_DATA_TYPE_GATT_ESL_ADDRESS}

    def update_state(self, data, state=ST_SYNCHRONIZED):
        """ Update tag state """
        self.state = state
        # Error
        if data[0] == TLV_RESPONSE_ERROR:
            pass
        # LED state
        elif data[0] == TLV_RESPONSE_LED_STATE:
            pass
        # Basic state
        elif data[0] == TLV_RESPONSE_BASIC_STATE:
            bs_bitmap = int.from_bytes(data[1:], byteorder="little")
            self.update_flags(bs_bitmap)
        # Display state
        elif data[0] == TLV_RESPONSE_DISPLAY_STATE:
            pass
        # Sensor info
        elif (data[0] & 0x0F) == TLV_RESPONSE_READ_SENSOR:
            pass
        else:
            return

        if self.unresp_command_number > 0:
            self.unresp_command_number -= 1

    def update_timestamps(self, timestamp=None):
        """ Update both request and response timestamps """
        self.update_request_timestamp(timestamp)
        self.update_response_timestamp(timestamp)

    def update_request_timestamp(self, timestamp=None):
        """ Update last request timestamp """
        if timestamp is None:
            timestamp = dt.now().timestamp()
        self.last_req_timestamp = timestamp

    def update_response_timestamp(self, timestamp=None):
        """ Update last request timestamp """
        if timestamp is None:
            timestamp = dt.now().timestamp()
        self.last_resp_timestamp = timestamp

    def timestamps_diff(self, timestamp):
        """ Get timestamp difference """
        return timestamp - self.last_req_timestamp, timestamp - self.last_resp_timestamp

    def update_flags(self, flags, new_state=True):
        """ Update basic state flags """
        if flags is not None:
            if new_state:
                self.basic_state_flags = self.basic_state_flags | flags
            else:
                self.basic_state_flags = self.basic_state_flags & ~flags

            if self.basic_state_flags & BASIC_STATE_FLAG_SYNCHRONIZED:
                self.state = ST_SYNCHRONIZED
            else:
                self.last_req_timestamp = dt.now().timestamp()

            if flags & BASIC_STATE_FLAG_SERVICE_NEEDED:
                self.logger.warning("ESL ID %d in group %d needs attention, Service Needed flag is active!", self.esl_id, self.group_id)

    def get_info(self):
        """ Get tag information """
        justify_column = 17
        info = f"{'BLE Address:':{justify_column}}{self.ble_address}"
        info += f"\n{'ESL Address:':{justify_column}}"
        if self.esl_address is not None:
            info += f"{self.esl_address} ({self.esl_address:#06x})"
            info += f"\n{'ESL ID:':{justify_column}}{self.esl_id}"
            info += f"\n{'Group ID:':{justify_column}}{self.group_id}"
        else:
            info += "Not configured"
        info += f"\n{'AP sync key:':{justify_column}}"
        if self.ap_sync_key is not None:
            info += "**** (Set)" if not IOP_TEST else "0x" + self.ap_sync_key.hex()
        else:
            info += "Not set"
        info += f"\n{'Response key:':{justify_column}}"
        if self.response_key is not None:
            info += "**** (Set)" if not IOP_TEST else "0x" + self.response_key.hex()
        else:
            info += "Not set"
        info += f"\n{'Absolute Time:':{justify_column}}"
        if self.time is not None:
            info += f"Last time set to {self.time}"
        else:
            info += "Out of sync"

        info += f"\n{'Display:':{justify_column}}"
        if self.display_info is not None:
            items = []
            for i, display in enumerate(self.display_info):
                items.append(f"[{i}] width: {display.width} height: {display.height} type: {display.type}")
            info += ("\n" + " " * justify_column).join(items)
        else:
            info += "Not present"

        if self.max_image_index is not None:
            info += f"\n{'Max image index:':{justify_column}}" + str(self.max_image_index)
        else:
            info += "\n" + "No image support."

        info += f"\n{'Sensors:':{justify_column}}"
        if len(self.sensor_info) > 0:
            items = []
            for i, sensor in enumerate(self.sensor_info):
                items.append(f"[{i}] {SENSOR_TYPES[sensor].desc if sensor in SENSOR_TYPES else hex(sensor)}")
            info += ("\n" + " " * justify_column).join(items)
        else:
            info += "Not supported"

        info += f"\n{'LED Info:':{justify_column}}"
        if self.led_type is not None:
            items = []
            for i, b in enumerate(self.led_type):
                bin_num = bin(b)[2:].zfill(8)
                R, G, B = int(bin_num[2:4], 2), int(bin_num[4:6], 2), int(bin_num[6:8], 2)
                if bin_num[0:2] == "00":
                    items.append(f"[{i}] Colored, current color: RGB({R}{G}{B})")
                elif bin_num[0:2] == "01":
                    items.append(f"[{i}] Monochrome, current color: RGB({R}{G}{B})")
                else:
                    items.append(f"[{i}] RFU")
            info += ("\n" + " " * justify_column).join(items)
        else:
            info += "Not available"

        info += f"\n{'PnP Info:':{justify_column}}"
        if self.pnp_vendor_id is not None:
            if self.pnp_vendor_id in VENDOR_ID_STRINGS:
                info += f"Vendor: {VENDOR_ID_STRINGS[self.pnp_vendor_id]}"
            else:
                info += f"Vendor_ID: {self.pnp_vendor_id:#x}"
            info += f" Product_ID: {self.pnp_product_id:#x} Product_version: {self.pnp_product_version:#x}"
        else:
            info += "Not available"

        info += f"\n{'Last status:':{justify_column}}"
        bs_string = ", ".join([value for key, value in BASIC_STATE_STRINGS.items() if self.basic_state_flags & key])
        if len(bs_string) == 0:
            bs_string = "No Basic State flag is set"
        info += f"{bs_string} ({self.basic_state_flags:#06x})"
        return info

    def __str__(self):
        if self.esl_address is None:
            return f"BLE Address: {self.ble_address}, Unassociated"
        return f"BLE Address: {self.ble_address}, ESL ID {self.esl_id} in group {self.group_id} ({self.esl_address:#06x})"
