"""
ESL AP Core.
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

import string
import threading
import secrets
import re
import os
import queue
import random
import struct
import traceback
from ap_config import *
from ap_constants import *
from ap_sensor import *
from ap_logger import getLogger, log
from image_converter import XbmConverter
from ap_response_parser import parse_response_data
from esl_tag import Tag
from ap_ead import KeyMaterial, EAD
from esl_command import ESLCommand
import esl_key_lib
import esl_lib
import esl_lib_wrapper as elw

# sanity check
if ESL_MAX_TAGS_IN_GROUP < ESL_MAX_TAGS_IN_AUTO_GROUP:
    raise Exception("Invalid configuration for auto addressing: ESL_MAX_TAGS_IN_AUTO_GROUP violates ESL specification")

class AccessPoint():
    """ Access Point """
    def __init__(self, config, cmd_mode=False, demo_mode=False):
        # Logger
        self.log = getLogger()

        self.scan_runs = False
        self.pawr_active = False
        self.auto_override = False
        self.cmd_mode = cmd_mode if not demo_mode else True
        self.demo_mode = demo_mode
        self.event_handler_prefix_list = [""] # TODO: this list should be thread safe!
        self.set_mode_handlers()
        # PAST timer, Note: interval is re-initialized properly after PA interval is set below
        self.past_timer = threading.Timer(10, self.past_timeout)
        self.past_timer.daemon = True
        self.past_initiated = False
        # some PAwR stuff
        self.cli_queue = None
        self.ead = EAD()
        self.lib = esl_lib.Lib(config)

        self.rssi_threshold = RSSI_THRESHOLD

        self.connection_dict = {}

        self.tags = {}
        self.ap_key = self.generate_key_material()
        self.ble_addresses = []
        self.blocked_list = []
        self.xbm_converter = XbmConverter()

        self.image_path = 'image/'
        self.image_files = [f for f in os.listdir(self.image_path) if os.path.isfile(os.path.join(self.image_path, f))]
        self.selected_image = 0
        self.raw_image = b""
        self.image_file = None
        self.label = None
        self.rotation = None
        self.state = IDLE
        self.active_address = None # used temporarily, until tag management is implemented
        self.start_time = dt.now()
        self.absolute_now = self.get_absolute_time(self.start_time)
        # ESL command dictionary of lists in a format: {group_id : [tlv0, tlv1, ..., tlvN]}
        self.esl_queued_commands = {}
        self.esl_pending_commands = {}
        self.esl_command_queue_lock = threading.Lock()
        self.esl_pending_commands_lock = threading.Lock()
        # Shutdown timer is executed if boot event fails
        self.shutdown_timer = threading.Timer(3.0, self.shutdown_cli)
        self.shutdown_timer.daemon = True
        self.shutdown_timer.start()
        # ESL Demo controller related attributes
        self.controller_command = None
        self.demo_auto_reconfigure = False
        self.image_from_controller = b""
        self.controller_image_index = None
        self.image_data_offset = bytearray(4)

        self.pawr_handle = None
        self.pawr_restart = None
        #PAwR default parameters
        self.adv_interval_min       = elw.ESL_LIB_PERIODIC_ADV_MIN_INTERVAL_DEFAULT
        self.adv_interval_max       = elw.ESL_LIB_PERIODIC_ADV_MAX_INTERVAL_DEFAULT
        self.adv_interval_last      = elw.ESL_LIB_PERIODIC_ADV_MAX_INTERVAL_DEFAULT
        self.subevent_count         = elw.ESL_LIB_PAWR_SUBEVENT_COUNT_DEFAULT
        self.subevent_interval      = elw.ESL_LIB_PAWR_SUBEVENT_INTERVAL_DEFAULT
        self.response_slot_delay    = elw.ESL_LIB_PAWR_RESPONSE_SLOT_DELAY_DEFAULT
        self.response_slot_spacing  = elw.ESL_LIB_PAWR_RESPONSE_SLOT_SPACING_DEFAULT
        self.response_slot_count    = elw.ESL_LIB_PAWR_RESPONSE_SLOT_COUNT_DEFAULT
        self.set_pawr_interval()

        self.consumer = threading.Thread(target=self.dequeue, daemon=True)
        self.consumer.start()

        self.key_db = esl_key_lib.Lib()

    ##################### CLI Handler methods #####################

    def ap_adv_start(self):
        # Start advertising
        if not self.demo_mode:
            self.lib.general_command(CMD_AP_CONTROL_ADV_ENABLE, b'\x01')
            self.log.info("Demo mode enabled.")
            self.demo_mode = True
            self.cmd_mode = True
            self.set_mode_handlers()
        else:
            self.log.info("Demo mode is already set.")

    def ap_adv_stop(self):
        if self.demo_mode:
            self.lib.general_command(CMD_AP_CONTROL_ADV_ENABLE, b'\x00')
            self.demo_mode = False
            self.set_mode_handlers()
            self.log.info("Demo mode disabled, switch to manual mode. To enable auto mode, please issue 'mode auto' command.")
        else:
            self.log.info("Not in Demo mode.")

    def ap_scan(self, start, active=False):
        """
        Start or stop scanning for advertising ESL devices.
        input:
            - start: 'True': start scanning, 'False': stop scanning
        """
        if start:
            self.start_scan(active, clear_lists=True)
        else:
            self.stop_scan()

    def ap_connect(self, esl_id, bt_addr, group_id, address_type):
        """
        Connect to an ESL device with the specified address.
        input:
            - esl_id:   ESL ID
            - bt_addr:  Bluetooth address
            - group_id: ESL group ID
        """
        if self.active_address is not None:
            self.log.warning(f"Already connected to {self.active_address}, request ignored.")
            return

        if esl_id is not None:
            address = self.bt_addr_from_esl(esl_id, group_id)
            if address is None:
                self.log.warning("Unknown tag: ESL ID: " + str(esl_id)
                                 + ", Group ID: " + str(group_id))
                return
        else:
            address = self.address_auto_type(bt_addr, address_type)

        _, subevent = self.esl_addr_from_bt(address)

        if subevent is not None and self.tags[address].state != ST_SYNCHRONIZED:
            subevent = None

        if not self.cmd_mode:
            self.auto_override = True

        self.connect(address, subevent)

    def ap_disconnect(self, esl_id, bt_addr, group_id):
        """
        Disconnect from an ESL device with the specified address.
        Do Periodic Advertisement Sync Transfer during the procedure.
        input:
            - esl_id:   ESL ID
            - bt_addr:  Bluetooth address
            - group_id: ESL group ID
        """
        do_past = False
        if esl_id is not None or bt_addr is not None:
            if esl_id is not None:
                address = self.bt_addr_from_esl(esl_id, group_id)
                if address is None:
                    self.log.warning("Unknown tag: ESL ID: " + str(esl_id)
                                     + ", Group ID: " + str(group_id))
                    return
                else:
                    do_past = self.tags[address].provisioned
            else:
                address = self.address_auto_type(bt_addr)
                esl_id, group_id = self.esl_addr_from_bt(address)
                if address in self.tags:
                    do_past = self.tags[address].provisioned
        elif self.active_address in self.tags:
            address = self.active_address
            esl_id, group_id = self.esl_addr_from_bt(address)
            do_past = self.tags[address].provisioned
        else:
            self.log.error("No active connection present!")
            return

        if do_past:
            if esl_id is not None:
                self.ap_update_complete(esl_id, group_id)
            else:
                self.past(address)
        else:
            self.disconnect(address)

    def ap_config(self, params):
        """
        Configure the writable mandatory GATT characteristics of the ESL tag.
        input:
            - params:   Configuration parameter dictionary. For further details see
                        the parameters of config command.
        """
        if self.active_address is None or self.active_address not in self.tags:
            self.log.warning("No tag connected to configure!")
            return
        tag = self.tags[self.active_address]
        values = {}
        esl_addr = None
        group_id = None
        for key in params:
            # All
            if key == "full":
                values = self.configure(tag)
            # ESL ID
            elif key == "esl_addr":
                esl_addr = params[key]
                if tag.esl_address is not None:
                    group_id = tag.group_id
                else:
                    group_id = 0
            # Group
            elif key == "group_id":
                group_id = params[key]
                if esl_addr is None:
                    if tag.esl_address is not None:
                        esl_addr = tag.esl_id
                    else:
                        esl_addr = 0
            # Sync Key
            elif key == "sync_key":
                values[elw.ESL_LIB_DATA_TYPE_GATT_AP_SYNC_KEY] = self.ap_key
            # Response Key
            elif key == "response_key":
                values[elw.ESL_LIB_DATA_TYPE_GATT_RESPONSE_KEY] = self.generate_key_material()
            # Raw Absolute Time value
            elif key == "absolute_time":
                absolute_time = params[key]
                values[elw.ESL_LIB_DATA_TYPE_GATT_CURRENT_TIME] = absolute_time.to_bytes(4, "little")
            # Time
            elif key == "time":
                self.absolute_now = self.get_absolute_time()
                values[elw.ESL_LIB_DATA_TYPE_GATT_CURRENT_TIME] = self.absolute_now.to_bytes(4, "little")
        if group_id is not None and esl_addr is not None:
            values[elw.ESL_LIB_DATA_TYPE_GATT_ESL_ADDRESS] = bytes([esl_addr & 0xff, group_id & 0x7f])
        if len(values):
            self.write_values(tag, values)
        else:
            self.log.error("No characteristic to configure, request ignored!")

    def ap_imageupdate(self, image_index, file, from_console=True, raw=False, display_ind=None, label=None, rotation=None, cropfit=False):
        """
        Update tag image.
        inputs:
            - image_index:  Image index
            - filename:     Filename with path
            - raw:          Open and load file without conversion
            - display_ind   Display index
            - label         Label to be printed as an overlay to the image
            - rotation      Clockwise (cw), Counter-clockwise (ccw), flip
        """

        # If image file is from console, check validity
        if from_console and not self.controller_command:
            self.raw_image = b""
            try:
                image_file = open(file, "rb")
                self.raw_image = image_file.read()
                image_file.close()
            except FileNotFoundError:
                self.log.error("Cannot open image file: %s", file)
                return

        # Check for connection
        if not self.active_address in self.tags:
            self.log.error("Image update needs an active connection!")
            return

        # If command is from AP remote controller (usually mobile running the demo application), send the notification
        if self.controller_command == CCMD_IMAGE_UPDATE:
            # This is the first request from the controller
            self.controller_image_index = image_index
            self.log.info("Image update command arrived from controller with the following parameters: index %s, filename %s", image_index, file)
            self.notify_controller(CCMD_REQUEST_DATA, CONTROLLER_COMMAND_SUCCESS, REQUEST_IMAGE_DATA_HEADER, self.image_data_offset, REQUEST_IMAGE_DATA_RESERVED)
            return

        if raw:
            self.log.info("Raw image file opened: %s", file)
            #nothing to do with raw files except upload!
        else:
            # Open and convert image file, otherwise
            ots_object_type = None
            if display_ind is None:
                self.image_file = file
                self.rotation = rotation
                self.label = label
                ots_object_type = self.ots_get_object_type(self.active_address, image_index)
                if ots_object_type == "unknown":
                    self.log.error("Unable to read ots object type")
                elif ots_object_type == None:
                    return # callback will take place in this case from OTS_RETURN_TYPE event handler!
                else:
                    display_ind = self.find_type_matching_display_index(self.active_address, ots_object_type)
                    if display_ind is None:
                        self.log.error("Unable to find a valid display index for ots_object_type: " + hex(ots_object_type))
                        eid, gid = self.esl_addr_from_bt(self.active_address)
                        self.ap_update_complete(eid, gid)
                        return
            else:
                if self.tags[self.active_address].display_count is None or display_ind >= self.tags[self.active_address].display_count:
                    self.log.error("Invalid display index: " + str(display_ind))
                    return
                _, ots_object_type = self.get_display_info(self.active_address, display_ind)

            disp_size, disp_type = self.get_display_info(self.active_address, display_ind)

            if ots_object_type and disp_type == ots_object_type:
                self.log.info("Display type matches object type")
                if type(file) == str:
                    self.xbm_converter.open(file)
                    if self.xbm_converter.image is not None:
                        self.log.info("Image file opened: %s", file)
                elif type(file) == bytes:
                    self.xbm_converter.open_frombytes(file)
                if ots_object_type == ESL_WSTK_DISPLAY_TYPE:
                    self.raw_image = self.xbm_converter.convert(display_size=disp_size, bw=True, label=label, rotation=rotation, cropfit=cropfit) # bw=true if object type FF, bw=False if FE
                elif ots_object_type == ESL_EPAPER_DISPLAY_TYPE:
                    self.raw_image = self.xbm_converter.convert(display_size=disp_size, bw=False, label=label, rotation=rotation, cropfit=cropfit)
                else:
                    self.raw_image = b""
                    self.log.error("Unknown OTS object type, automatic conversion can't be done. Please upload raw image data.")
            else:
                if self.controller_command == CCMD_IMAGE_UPDATE:
                    self.notify_controller(CCMD_IMAGE_UPDATE, CONTROLLER_COMMAND_FAIL)
                self.log.error("Cannot upload file: display type is not the same as object type!")

        # Send file if raw input or converted result seems OK
        if len(self.raw_image) != 0:
            if image_index > self.tags[self.active_address].auto_image_count:
                self.tags[self.active_address].auto_image_count = image_index
            self.update_image(image_index)
        else:
            self.log.error("Cannot upload file: image conversion failed!")
            if self.controller_command == CCMD_IMAGE_UPDATE:
                self.notify_controller(CCMD_IMAGE_UPDATE, CONTROLLER_COMMAND_FAIL)

    def ap_unassociate(self, address, group_id):
        """
        Unassociate tag from AP.
        inputs:
            - address:  Either Bluetooth address or ESL ID
            - group_id: ESL group ID
        """
        tlv = TLV_OPCODE_UNASSOCIATE
        esl_id = self.get_esl_id(address, group_id)

        data = bytearray(self.get_opcode_len(tlv))
        if esl_id is not None:
            if esl_id == BROADCAST_ADDRESS:
                self.remove_tag(esl_id, group_id)
                if self.controller_command == CCMD_UNASSOCIATE:
                    self.notify_controller(CCMD_UNASSOCIATE, CONTROLLER_COMMAND_SUCCESS, esl_id)
            else:
                tag = self.tags[self.bt_addr_from_esl(esl_id, group_id)]
                if tag.state not in [ST_UNASSOCIATED, ST_UNSYNCHRONIZED]:
                    tag.pending_unassociate = True
            data[0:2] = tlv, esl_id
            # Handle the connected ESL tag separately, if any
            if esl_id == BROADCAST_ADDRESS and self.active_address in self.tags:
                eid, gid = self.esl_addr_from_bt(self.active_address)
                if gid == group_id:
                    # broadcast addresses are otherwise routed over periodic advertisement, always!
                    self.route_command(eid, gid, data) # therefore the eid needs to be overridden for connected tags
                    self.log.warning("Unassociate connected ESL Tag results in disconnection!")
            else:
                self.route_command(esl_id, group_id, data)
        elif IOP_TEST and re.fullmatch(VALID_ESL_ID_NUMBER_REGEX, address) is not None:
            data[0:2] = tlv, int(address)
            self.queue_pawr_command(group_id, data)
            self.log.warning("Tag with address %s not found in group %d, send over PawR due IOP_TEST mode", address, group_id)
        else:
            try:
                bt_address = esl_lib.Address.from_str(address)
                if self.key_db.find_ltk(bt_address) is None:
                    raise esl_key_lib.Error(elw.SL_STATUS_NOT_FOUND)
                self.key_db.delete_ltk(bt_address)
                self.log.warning("Currently unconfigured Tag with address %s removed from the bonding database", address)
            except (ValueError, esl_key_lib.Error):
                self.log.error("Tag with address %s not found in any group nor in bonding database, command ignored", address)
                if self.controller_command == CCMD_UNASSOCIATE:
                    self.notify_controller(CCMD_UNASSOCIATE, CONTROLLER_COMMAND_FAIL)

    def ap_list(self, param_list, verbose=False, group_id = None):
        """
        List tag information.
        inputs:
            - param_list:             List of parameters, possible values:
                - 'advertising':      List advertising tags
                - 'synchronized':     List synchronized tags
                - 'unsynchronized':   List unsynchronized tags
                - 'connected':        List connected tags
            - verbose:                Print more verbose information
        """
        list_of_tags = []
        for param in param_list:
            count = 0
            # Advertising
            if param == "advertising":
                count = len(self.ble_addresses)
                for tag_addr in self.ble_addresses:
                    if tag_addr in self.tags:
                        log(self.tags[tag_addr])
                    else:
                        log(f"BLE Address: {tag_addr}")
                if count == 0:
                    log("There's no advertising tag.")
                elif count == 1:
                    log("There's one advertising tag.")
                else:
                    log(f"There are {count} advertising tags.")
            # Synchronized
            elif param == "synchronized":
                for key, tag in self.tags.items():
                    if tag.state == ST_SYNCHRONIZED and (group_id is None or group_id == tag.group_id):
                        if verbose:
                            log(tag.get_info())
                            log("-" * 36)
                        else:
                            log(tag)
                        count = count + 1
                        list_of_tags.append(tag.ble_address)
                if count == 0:
                    log("There's no synchronized tag.")
                elif count == 1:
                    log("There's one synchronized tag.")
                else:
                    log(f"There are {count} synchronized tags.")
            # Unsynchronized
            elif param == "unsynchronized":
                for key, tag in self.tags.items():
                    if key == self.active_address:
                        continue
                    if tag.state == ST_UNSYNCHRONIZED and (group_id is None or group_id == tag.group_id):
                        if verbose:
                            log(tag.get_info())
                            log("-" * 36)
                        else:
                            log(tag)
                        count = count + 1
                if count == 0:
                    log("There's no unsynchronized tag.")
                elif count == 1:
                    log("There's one unsynchronized tag.")
                else:
                    log(f"There are {count} unsynchronized tags.")
            # Connected
            elif param == "connected":
                if self.active_address in self.tags:
                    tag = self.tags[self.active_address]
                    if verbose:
                        log(tag.get_info())
                        log("-" * 36)
                    else:
                        log(tag)
                    count = count + 1
                if count == 0:
                    log("There's no connected tag.")
                elif count == 1:
                    log("There's one connected tag.")
                else:
                    log(f"There are {count} connected tags.")
            # Blocked
            elif param == "blocked":
                count = len(self.blocked_list)
                for tag_addr in self.blocked_list:
                    if tag_addr in self.tags:
                        log(self.tags[tag_addr])
                    else:
                        log(f"BLE Address: {tag_addr}")
                if count == 0:
                    log("There's no blocked tag.")
                elif count == 1:
                    log("There's one blocked tag.")
                else:
                    log(f"There are {count} blocked tags that may or may not advertising.")

        if self.controller_command == CCMD_LIST:
            if len(list_of_tags) != 0:
                for addr in list_of_tags:
                    if addr != list_of_tags[-1]:
                        self.notify_controller(CCMD_LIST, CONTROLLER_COMMAND_SUCCESS, CONTROLLER_REQUEST_MORE_DATA, self.tags[addr].esl_address,
                                               str(self.tags[addr].ble_address),
                                               self.tags[addr].max_image_index + 1 if self.tags[addr].max_image_index is not None else 0,
                                               len(self.tags[addr].display_info),
                                               struct.pack('<H', S_ID_PRESENT_INPUT_VOLTAGE) if S_ID_PRESENT_INPUT_VOLTAGE in self.tags[addr].sensor_info else struct.pack('<H', 0x0000),
                                               struct.pack('<H', S_ID_PRESENT_DEVICE_OPERATING_TEMPERATURE) if S_ID_PRESENT_DEVICE_OPERATING_TEMPERATURE in self.tags[addr].sensor_info else    struct.pack('<H', 0x0000))
                    else:
                        self.notify_controller(CCMD_LIST, CONTROLLER_COMMAND_SUCCESS, CONTROLLER_REQUEST_LAST_DATA, self.tags[addr].esl_address,
                                               str(self.tags[addr].ble_address),
                                               self.tags[addr].max_image_index + 1 if self.tags[addr].max_image_index is not None else 0,
                                               len(self.tags[addr].display_info),
                                               struct.pack('<H', S_ID_PRESENT_INPUT_VOLTAGE) if S_ID_PRESENT_INPUT_VOLTAGE in self.tags[addr].sensor_info else struct.pack('<H', 0x0000),
                                               struct.pack('<H', S_ID_PRESENT_DEVICE_OPERATING_TEMPERATURE) if S_ID_PRESENT_DEVICE_OPERATING_TEMPERATURE in self.tags[addr].sensor_info else struct.pack('<H', 0x0000))
            else:
                self.notify_controller(CCMD_LIST, CONTROLLER_COMMAND_SUCCESS, CONTROLLER_REQUEST_LAST_DATA, 0)

    def ap_led(self, address, group_id, repeat_field, index, absolute_value,
               gamut = 0, pattern = None):
        """
        Turn on / off or flash an LED utilizing the LED control command.
        input:
            - address:          Either Bluetooth address or ESL ID
            - group_id:         ESL group ID
            - repeat_field:     How many times the pattern shall be repeated
            - index:            Index of the LED
            - absolute_value:   Execution time of the command in ESL Absolute Time epoch value
            - gamut:            LED gamut
            - pattern:          Flashing pattern
        """
        esl_id = self.get_esl_id(address, group_id)

        if esl_id is not None:
            pass
        elif re.fullmatch(VALID_ESL_ID_NUMBER_REGEX, str(address)) is not None:
            esl_id = int(address)
        else:
            self.log.error("Tag with address %s not found in any group, command not sent", address)
            if self.controller_command != None:
                self.notify_controller(self.controller_command, CONTROLLER_COMMAND_FAIL)
            return

        self.led_control_command(esl_id, group_id, repeat_field, index,
                                  absolute_value, gamut, pattern)
        if self.controller_command == CCMD_LED and esl_id == BROADCAST_ADDRESS:
            self.notify_controller(CCMD_LED, CONTROLLER_COMMAND_SUCCESS, esl_id)

    def ap_read_sensor(self, address, group_id, sensor_idx):
        """
        Read sensor information.
        input:
            - address:      Either Bluetooth address or ESL ID
            - sensor_idx:   Sensor index
            - group_id:     ESL group ID
        """
        tlv = TLV_OPCODE_READ_SENSOR
        esl_id = self.get_esl_id(address, group_id)

        if esl_id is not None:
            pass
        elif re.fullmatch(VALID_ESL_ID_NUMBER_REGEX, str(address)) is not None:
            esl_id = int(address)
        else:
            self.log.error("Tag with address %s not found in any group, command not sent", address)
            return

        data = bytearray(self.get_opcode_len(tlv))
        data[0:3] = tlv, esl_id, sensor_idx
        self.route_command(esl_id, group_id, data)

    def ap_factory_reset(self, address, group_id, force_pawr=False):
        """
        Execute factory reset on tag.
        inputs:
            - address:  Either Bluetooth address or ESL ID
            - group_id: ESL group ID
        """
        tlv = TLV_OPCODE_FACTORY_RST
        esl_id = self.get_esl_id(address, group_id)
        if esl_id is not None:
            data = bytearray(self.get_opcode_len(tlv))

            data[0:2] = tlv, esl_id
            self.route_command(esl_id, group_id, data, force_pawr)
            state = ST_SYNCHRONIZED
            if esl_id != BROADCAST_ADDRESS:
                state = self.tags[self.bt_addr_from_esl(esl_id, group_id)].state
            if not force_pawr and (state == ST_CONFIGURING or state == ST_UPDATING):
                self.remove_tag(esl_id, group_id)
            else:
                self.log.warning("Factory reset command is invalid in Synchronized state!")
        else:
            self.log.warning("Tag with address %s not found in any group, command not sent", address)

    def ap_update_complete(self, address, group_id):
        """
        Issue an Update Complete command to a connected tag
        inputs:
            - address:  Either Bluetooth address or ESL ID
            - group_id: ESL group ID
        """

        # Check for connection
        if not self.active_address in self.tags:
            self.log.error("Update Complete can be used only with active connection!")
            if not IOP_TEST:
                return

        tlv = TLV_OPCODE_UPDATE_COMPLETE
        esl_id = self.get_esl_id(address, group_id)

        if esl_id is not None:
            state = self.tags[self.bt_addr_from_esl(esl_id, group_id)].state
            if state == ST_SYNCHRONIZED:
                self.log.warning("Update complete command is invalid in Synchronized state!")
            pass
        elif re.fullmatch(VALID_ESL_ID_NUMBER_REGEX, str(address)) is not None:
            esl_id = int(address)
        else:
            self.log.error("Tag with address %s not found in any group, command not sent", address)
            return

        data = bytearray(self.get_opcode_len(tlv))
        data[0:2] = tlv, esl_id
        self.route_command(esl_id, group_id, data)

    def ap_refresh_display(self, address, group_id, display_idx):
        """
        Refresh tag display.
        input:
            - address:      Either Bluetooth address or ESL ID
            - display_idx:  Display index
            - group_id:     ESL group ID
        """
        tlv = TLV_OPCODE_REFRESH_DISPLAY
        esl_id = self.get_esl_id(address, group_id)

        if esl_id is not None:
            pass
        elif re.fullmatch(VALID_ESL_ID_NUMBER_REGEX, str(address)) is not None:
            esl_id = int(address)
        else:
            self.log.error("Tag with address %s not found in any group, command not sent", address)
            return

        data = bytearray(self.get_opcode_len(tlv))
        data[0:3] = tlv, esl_id, display_idx
        self.route_command(esl_id, group_id, data)

    def ap_display_image(self, address, group_id, image_idx, display_idx, absolute_value):
        """
        Display tag image.
        input:
            - address:       Either Bluetooth address or ESL ID
            - image_idx:     Image index
            - display_idx:   Display index
            - group_id:      ESL group ID
            - delay_ms:      Delay in milliseconds
            - absolute_base: ESL Absolute Time epoch value
        """
        tlv = TLV_OPCODE_DISPLAY_IMAGE
        esl_id = self.get_esl_id(address, group_id)

        if esl_id is not None:
            pass
        elif re.fullmatch(VALID_ESL_ID_NUMBER_REGEX, str(address)) is not None:
            esl_id = int(address)
        else:
            if self.controller_command != None:
                self.notify_controller(self.controller_command, CONTROLLER_COMMAND_FAIL)
            self.log.error("Tag with address %s not found in any group, command not sent", address)
            return

        if absolute_value is not None:
            tlv = TLV_OPCODE_DISPLAY_TIMED_IMAGE
        data = bytearray(self.get_opcode_len(tlv))
        data[0:4] = tlv, esl_id, display_idx, image_idx

        if absolute_value is not None:
            data[4:8] = struct.pack("<I", (absolute_value & 0xFFFFFFFF))
            if absolute_value == 0:
                self.log.info("Delete timed display image command of display index %d", display_idx)
            else:
                self.log.info("Delayed display image command issued at absolute time %d", absolute_value)
        self.route_command(esl_id, group_id, data)
        if self.controller_command == CCMD_DISPLAY_IMAGE:
            self.log.info("Display image command arrived from controller")
            if esl_id == BROADCAST_ADDRESS:
                self.notify_controller(CCMD_DISPLAY_IMAGE, CONTROLLER_COMMAND_SUCCESS, esl_id)

    def ap_ping(self, address, group_id):
        """
        Send ESL ping command.
        input:
            - address:      Either Bluetooth address or ESL ID
            - group_id:     ESL group ID
        """
        tlv = TLV_OPCODE_PING
        esl_id = self.get_esl_id(address, group_id)

        if esl_id is None:
            self.log.warning("Tag with address %s not found in any group", address)
            if re.fullmatch(VALID_ESL_ID_NUMBER_REGEX, address) is not None:
                esl_id = int(address)
            else:
                self.log.error("Unknown address can be a valid ESL ID only, command ignored!")
                if self.controller_command != None:
                    self.notify_controller(self.controller_command, CONTROLLER_COMMAND_FAIL)
                return
        elif esl_id == BROADCAST_ADDRESS and not IOP_TEST:
            self.log.error("Using broadcast with ping makes no sense, command ignored!")
            if self.controller_command != None:
                self.notify_controller(self.controller_command, CONTROLLER_COMMAND_FAIL)
            return

        data = bytearray(self.get_opcode_len(tlv))
        data[0:2] = tlv, esl_id
        self.route_command(esl_id, group_id, data)
        if self.controller_command == CCMD_PING and esl_id == BROADCAST_ADDRESS:
            self.notify_controller(CCMD_PING, CONTROLLER_COMMAND_SUCCESS, esl_id)

    def ap_vendor_opcode(self, address, group_id, vendor_data=None):
        """
        Send ESL vendor specific opcode.
        input:
            - address:      Either Bluetooth address or ESL ID
            - group_id:     ESL group ID
            - data:         ESL vendor specific TLV
        """
        tlv = TLV_OPCODE_VENDOR_SPECIFIC
        esl_id = self.get_esl_id(address, group_id)

        data_length = self.get_opcode_len(tlv)

        if vendor_data is not None:
            extra_len = len(vendor_data)
            data_length += extra_len
            tlv = self.set_tlv_len(tlv, extra_len)

        if esl_id is None:
            self.log.warning("Tag with address %s not found in any group", address)
            if re.fullmatch(VALID_ESL_ID_NUMBER_REGEX, address) is not None:
                esl_id = int(address)
            else:
                self.log.error("Unknown address can be a valid ESL ID only, command ignored!")
                return

        data = bytearray(data_length)
        data[0:2] = tlv, esl_id
        if vendor_data is not None:
            data[2:] = vendor_data
        self.route_command(esl_id, group_id, data)

    def ap_service_reset(self, address, group_id):
        """
        Send Service Reset command.
        input:
            - address:      Either Bluetooth address or ESL ID
            - group_id:     ESL group ID
        """
        tlv = TLV_OPCODE_SERVICE_RST
        esl_id = self.get_esl_id(address, group_id)

        if esl_id is not None:
            pass
        elif re.fullmatch(VALID_ESL_ID_NUMBER_REGEX, str(address)) is not None:
            esl_id = int(address)
        else:
            self.log.error("Tag with address %s not found in any group, command not sent", address)
            return

        data = bytearray(self.get_opcode_len(tlv))
        data[0:2] = tlv, esl_id
        self.route_command(esl_id, group_id, data)

    def ap_sync(self, start, pa_interval=None):
        """
        Start / stop sending synchronization packets.
        input:
            - start:            Start sending periodic synchronization packets
            - pa_interval:      Periodic advertising interval list in ms.
                                See 'sync' command for more details.
        """
        if self.is_there_tag(ST_SYNCHRONIZED):
            self.log.warning("There are already synchronized tags, they will lose sync!")
            self.set_tags_state(ST_UNSYNCHRONIZED, ST_SYNCHRONIZED)

        if not start:
            self.stop_pawr_train()
            # Clear unsent commands
            self.esl_command_queue_lock.acquire()
            self.esl_queued_commands.clear()
            self.esl_command_queue_lock.release()
            self.remove_outdated_commands(0)
        else:
            self.start_pawr_train(pa_interval)
            # Restart scanning
            if self.scan_runs and (not self.cmd_mode or self.auto_override):
                self.start_scan(clear_lists=True)

    def ap_mode(self, auto_mode):
        """
        Changes ESL Access Point operation mode
        input:
            - auto_mode: 'True': automatic, 'False': manual, 'None': print current mode
        """
        if auto_mode == True:
            if not self.auto_override:
                if not self.pawr_active:
                    self.start_pawr_train()
                    self.log.debug("PAwR sync start requested.")
                else:
                    self.log.debug("PAwR sync train already running, no need to start.")
                self.start_scan(clear_lists=True)
            self.cmd_mode = False
            if self.demo_mode:
                self.demo_mode = False
                self.log.warning("Demo mode disabled by changing to auto mode.")
                self.lib.general_command(CMD_AP_CONTROL_ADV_ENABLE, b'\x00')
            self.auto_override = False
            self.log.info("Operation mode: automated")
        elif auto_mode == False:
            self.cmd_mode = True
            self.auto_override = False
            self.log.info("Operation mode: manual")
        else:
            log("  Current mode: {0}".format("manual" if self.cmd_mode else "automated"))
        self.set_mode_handlers()

    def ap_set_rssi_threshold(self, rssi_tresh):
        """
        Set RSSI filter threshold value.
        input:
            - rssi_tresh:   RSSI filter threshold value
        """
        self.rssi_threshold = rssi_tresh
        self.log.info("New RSSI threshold value: %d", self.rssi_threshold)

    ##################### helpers #####################
    def set_mode_handlers(self):
        while len(self.event_handler_prefix_list) > 1:
            elem = self.event_handler_prefix_list.pop()
        if self.auto_override or self.cmd_mode:
            self.event_handler_prefix_list.append("cli_")
        else:
            self.event_handler_prefix_list.append("auto_")
        if self.demo_mode:
            self.event_handler_prefix_list.append("demo_")

    def arg_check_ok(self, arg, pattern):
        """ Check command line arguments """
        return bool(re.fullmatch(pattern, arg) is not None)
    
    def address_auto_type(self, address: str, address_type=None):
        """ Guess address type if not provided """
        if address_type is None:
            for i in self.ble_addresses:
                if i == address:
                    return i
        return esl_lib.Address.from_str(address, address_type)

    ##################### ESL methods #####################
    def get_display_info(self, ble_address, display_ind):
        disp_size = None
        disp_type = None
        if ble_address in self.tags:
            disp_size = (self.tags[ble_address].display_info[display_ind].width, self.tags[ble_address].display_info[display_ind].height)
            disp_type = self.tags[ble_address].display_info[display_ind].type
        return disp_size, disp_type

    def find_type_matching_display_index(self, ble_address, display_type):
        if ble_address in self.tags:
            for x in self.tags[ble_address].display_info:
                if x.type == display_type:
                    return self.tags[ble_address].display_info.index(x)
        return None

    def ots_get_object_type(self, ble_address, image_index):
        obj_type = None
        if ble_address in self.tags:
            type_dict = self.tags[ble_address].ots_image_type
            try:
                obj_type = type_dict[image_index]
            except KeyError:
                pass

            if obj_type is None:
                self.lib.get_image_type(self.conn_handle_from_bt(ble_address), image_index)

        return obj_type

    def new_auto_address(self, id):
        esl_id = id % ESL_MAX_TAGS_IN_AUTO_GROUP
        group_id = int(id // ESL_MAX_TAGS_IN_AUTO_GROUP)
        esl_address = (esl_id & BROADCAST_ADDRESS) | (group_id & 0x7f) << 8
        return esl_address

    def sync_fake_tags(self, count, state=ST_SYNCHRONIZED):
        for i in range(count):
            address = "{}{}:{}{}:{}{}:{}{}:{}{}:{}{}".format(*random.choices(string.ascii_letters[:6] + string.digits, k=12))
            self.init_tag(address)
            values = self.configure(self.tags[address])
            self.tags[address].state = state
            self.tags[address].gatt_values.update(values)

    def get_absolute_time(self, now = None):
        """ Get absolute time in milliseconds """
        delta_time = 0
        if now is None:
            delta_time = dt.now() - self.start_time
        else:
            delta_time = now - self.start_time
        ms = (delta_time.days * 24 * 60 * 60 + delta_time.seconds) * 1000 + delta_time.microseconds / 1000.0
        int_ms = int(ms)
        return int_ms

    def calculate_exec_time(self, now, d_hour, d_min, d_sec, d_msec, date = None):
        """ Calculate command execution time delay in milliseconds """
        delay_ms = None
        delay_time = now
        delay_time = delay_time.replace(hour=d_hour, minute=d_min, second=d_sec, microsecond=d_msec*1000)
        if date is not None:
            delay_time = delay_time.replace(year=date.year, month=date.month, day=date.day)
        delta_time = delay_time - now
        ms = (delta_time.days * 24 * 60 * 60 + delta_time.seconds) * 1000 + delta_time.microseconds / 1000.0
        if int(ms) > ESL_MAX_DELAY:
            self.log.error("Requested date and time exceeds ESL delay limit (48 days)!")
        elif int(ms) > 0:
            delay_ms = int(ms + 0.5)
        elif int(ms) < 0:
            if date is None:
                delay_ms = int(ms + 0.5) + 86400000 # adds one day extra delay if time passed already and date is not specified
                self.log.warning("The time specified was interpreted as tomorrow time!")
            else:
                self.log.error("Requested date and time has passed already!")
        return delay_ms

    def generate_key_material(self):
        """ Generate AP key """
        return self.ead.generate_key() + secrets.token_bytes(EAD_IV_SIZE)

    def update_state(self, state):
        """ Update state """
        self.state = state
        if state in STATE_STRINGS:
            self.log.debug("[State] " + str(STATE_STRINGS[state]))
        else:
            self.log.warning("[State] unknown: %s", str(state))

    def queue_pawr_command(self, gid, data):
        """ Prepare periodic advertisement with responses payload by appending to esl command queue """
        self.esl_command_queue_lock.acquire()
        if gid not in self.esl_queued_commands:
            self.esl_queued_commands[gid] = []
        self.esl_queued_commands[gid].append(data)
        self.esl_command_queue_lock.release()

    def requeue_pawr_command(self, gid, data):
        """ Prepare periodic advertisement with responses payload by appending to esl command queue """
        self.esl_command_queue_lock.acquire()
        if gid not in self.esl_queued_commands:
            self.esl_queued_commands[gid] = []
        self.esl_queued_commands[gid].insert(0, data)
        self.esl_command_queue_lock.release()

    def send_pawr_commands(self, subevents):
        """ Pack and send commands over PAwR sync"""
        if self.esl_queued_commands:
            # try acquire, skip this turn if it's already acquired by producer task
            if self.esl_command_queue_lock.acquire(False):
                empty_gid_list = []
                # go through only groups of the most recent data request
                for gid in subevents:
                    if gid not in self.esl_queued_commands: # go to next if there's nothing to send this current group
                        continue
                    commands = []
                    pop_list = []
                    # go through all queued commands for the group
                    for i in range(len(self.esl_queued_commands[gid])):
                        tlv = self.esl_queued_commands[gid][i]

                        # check if current command can still fit into a single payload
                        payload_size = self.datasize(commands) + len(tlv)
                        if payload_size < MAX_ESL_PAYLOAD_SIZE:
                            commands.append(tlv)
                            pop_list.append(i)
                            self.log.debug("Opcode 0x" + '{:02X}'.format(tlv[0]) + " to ESL ID " + str(tlv[1]) + " in group " + str(gid) + " written to slot "+ str(i))
                        elif payload_size >= MAX_ESL_PAYLOAD_SIZE - 1:
                            break

                    for x in reversed(pop_list):
                        self.esl_queued_commands[gid].pop(x)
                        # remove any empty dictionaries
                        if len(self.esl_queued_commands[gid]) == 0:
                            empty_gid_list.append(gid)

                    data = self.create_sync_packet(gid, commands)
                    if data is not None:
                        self.lib.pawr_set_data(self.pawr_handle, gid, data)
                    self.update_pending_commands_list(gid, commands)

                for gid in empty_gid_list:
                    del self.esl_queued_commands[gid]

                self.esl_command_queue_lock.release()

    def datasize(self, cmd_list):
        """ Return with the size of the commands in byte in cmd_list """
        d_size = 0
        for x in cmd_list:
            d_size += len(x)
        return d_size

    def synchronization_handler(self):
        """ Handle Tag synchronization """
        if self.pawr_active:
            # Remove outdated commands
            calculated_timeout = self.pa_timer_interval * AUX_SYNC_IND_PDU_MAX_SKIP_COUNT
            max_timeout = 164 # From BLE spec: the maximum permitted time between successful receives of periodic advertisement packages is 163.84 seconds.
            self.remove_outdated_commands(calculated_timeout if calculated_timeout < max_timeout else max_timeout)

            for address, tag in self.tags.items():
                already_sent = []   # List of slots for resent tag commands

                if tag.state == ST_SYNCHRONIZED:
                    tnow = dt.now().timestamp()
                    req_timestamp_diff, resp_timestamp_diff = tag.timestamps_diff(tnow)

                    # Send NOP to keep tag synchronized
                    if req_timestamp_diff >= TAG_SYNC_KEEPING_INTERVAL - self.pa_timer_interval:
                        data = bytearray(self.get_opcode_len(TLV_OPCODE_PING))
                        data[0:2] = TLV_OPCODE_PING, tag.esl_id
                        self.queue_pawr_command(tag.group_id, data)
                        tag.update_request_timestamp()
                        tag.unresp_command_number += 1
                    # Check tag timeout
                    elif resp_timestamp_diff > TAG_SYNC_TIMEOUT + self.pa_timer_interval:
                        self.log.info("Set tag %s to Unsynchronized because of synchronization timeout", address)
                        tag.state = ST_UNSYNCHRONIZED
                        tag.update_flags(BASIC_STATE_FLAG_SYNCHRONIZED, False)
                        continue

                    # Resend unresponded commands
                    current_pending_commands = self.esl_pending_commands.copy()
                    for key in current_pending_commands:
                        for cmd in current_pending_commands[key]:
                            if cmd.esl_id == tag.esl_id and cmd.group_id == tag.group_id \
                                and ((tnow - cmd.timestamp) > 1.5 * self.pa_timer_interval + .1):
                                self.remove_esl_pending_command(cmd) # this will remove given command from self.esl_pending_commands
                                if self.bt_addr_from_esl(cmd.esl_id, cmd.group_id) != self.active_address and tag.unresp_command_number < ESL_CMD_MAX_RETRY_COUNT:
                                    self.log.info("Resending unresponded command: (0x%s)", cmd.params.hex())
                                    self.resend_pawr_command(cmd) # and then re-queuing it to the bottom of the "FIFO"
                                    if cmd.slot_number not in already_sent:
                                        tag.unresp_command_number += 1
                                        already_sent.append(cmd.slot_number)
                                elif tag.unresp_command_number >= ESL_CMD_MAX_RETRY_COUNT:
                                    self.log.warning("Tag at address %s does not respond to synchronization packets, stop retrying", address)
                                    tag.unresp_command_number = 0
                        already_sent = []

                elif tag.state == ST_UNSYNCHRONIZED:
                    tnow = dt.now().timestamp()
                    _, resp_timestamp_diff = tag.timestamps_diff(tnow)
                    # Check tag timeout
                    if resp_timestamp_diff > TAG_UNASSOCIATE_TIMEOUT:
                        self.log.info("Unassociate Tag %s because of timeout in Unsynchronized state", address)
                        tag.state = ST_UNASSOCIATED
                        continue

    def resend_pawr_command(self, cmd):
        """ Resend pawr command """
        self.requeue_pawr_command(cmd.group_id, cmd.params)

    def reorder_device_list(self, address: esl_lib.Address):
        """ Append address to the end of the list """
        if address in self.ble_addresses:
            self.ble_addresses.remove(address)
            if address not in self.blocked_list:
                self.ble_addresses.append(address)

    def upload_next_image(self, tag: Tag):
        if tag is None:
            return
        tag.auto_image_count += 1
        if tag.auto_image_count < min((tag.max_image_index + 1), IMAGE_MAX_AUTO_UPLOAD_COUNT):
            self.log.info("Sending new image")
            self.upload_auto_image(tag.auto_image_count)
        elif tag.provisioned:
            disp_image = bytearray(self.get_opcode_len(TLV_OPCODE_DISPLAY_IMAGE))
            disp_image[0:4] = TLV_OPCODE_DISPLAY_IMAGE, tag.esl_id , 0, 0
            disp_image = bytes(disp_image)
            self.send_cp_command(tag.ble_address, disp_image)
            self.log.info("Display Image command sent")

    def dequeue(self):
        """ Check and process event queue """
        while True:
            try:
                event = self.lib.event_queue.get(timeout=BLOCKING_WAIT_TIMEOUT)
            except queue.Empty:
                continue
            if isinstance(event, esl_lib.EventError):
                if event.lib_status not in [elw.ESL_LIB_STATUS_PAST_INIT_FAILED, elw.ESL_LIB_STATUS_PAWR_START_FAILED]:
                    self.log.warning("[Event] " + str(event))
            else:
                filter_events = [elw.ESL_LIB_EVT_PAWR_DATA_REQUEST, elw.ESL_LIB_EVT_TAG_FOUND]
                if not event.evt_code in filter_events:
                    self.log.debug("[Event] " + str(event))
            try:
                enum_prefix = "ESL_LIB_EVT_"
                event_name = esl_lib.get_enum(enum_prefix, event.evt_code)[len(enum_prefix):].lower()
                for prefix in self.event_handler_prefix_list:
                    event_handler_method = prefix + "esl_event_" + event_name
                    if hasattr(self, event_handler_method):
                        getattr(self, event_handler_method)(event)
            except Exception as err:
                print(err)
                print(traceback.format_exc())
                self.shutdown_cli()

    # ----------------------------------------------------------------------------------------------
    # Common ESL event handler methods for all modes (auto/command line/demo)

    def esl_event_system_boot(self, evt: esl_lib.EventSystemBoot):
        """ ESL event handler """
        self.shutdown_timer.cancel()
        # Init GATT database for demo mode
        self.lib.general_command(CMD_AP_CONTROL_INIT_GATTDB)

    def esl_event_tag_found(self, evt: esl_lib.EventTagFound):
        """ ESL event handler """
        if evt.rssi > self.rssi_threshold and evt.address not in self.ble_addresses:
            if evt.address in self.tags:
                self.tags[evt.address].reset()
                if self.tags[evt.address].state == ST_SYNCHRONIZED:
                    self.log.warning(f"The Tag {evt.address} lost sync!")
                    self.tags[evt.address].state = ST_UNSYNCHRONIZED
                    self.tags[evt.address].update_flags(BASIC_STATE_FLAG_SYNCHRONIZED, False)
            else:
                self.log.info(f"ESL service found at BLE address: {evt.address} with RSSI: {evt.rssi} dBm")

    def esl_event_connection_opened(self, evt: esl_lib.EventConnectionOpened):
        """ ESL event handler """
        self.connection_dict[evt.connection_handle] = evt.address
        self.active_address = evt.address
        if evt.address in self.ble_addresses:
            self.ble_addresses.remove(evt.address) # remove the device from the unprovisioned/advertising list
        self.init_tag(evt.address, evt.gattdb_handles)
        if not self.tags[evt.address].skip_get_info:
            # read device info
            self.lib.get_tag_info(evt.connection_handle)
            self.update_state(READING_VALUES)
        else:
            self.log.info("Tag info already available, skipping discovery.")
            self.update_state(CONNECTED)

    def esl_event_tag_info(self, evt: esl_lib.EventTagInfo):
        """ ESL event handler """
        self.update_state(CONNECTED)
        tag = self.get_tag(evt.connection_handle)
        tag.gatt_values.update(evt.tlv_data)
        tag.set_valid() # make ESL tag valid from this point on
        if elw.ESL_LIB_DATA_TYPE_GATT_PNP_ID in evt.tlv_data:
            if tag.pnp_vendor_id == None:
                self.log.error("PnP characteristic not found - vendor opcodes support disabled")
            elif tag.pnp_vendor_id == SIG_VENDOR_ID_SILABS:
                self.log.info("Silabs device found - vendor opcodes are not defined")
            else:
                self.log.info(f"PnP characteristic found: {tag.pnp_vendor_id:#x}")
        if elw.ESL_LIB_DATA_TYPE_GATT_SERIAL_NUMBER in evt.tlv_data:
            self.log.info("Serial Number String found: " + str(tag.serial_number))
        values = tag.gatt_write_values
        if len(values) and not tag.provisioned:
            self.write_values(tag, values) # auto-refresh existing tag config

    def esl_event_pawr_status(self, evt: esl_lib.EventPawrStatus):
        """ ESL event handler """
        if evt.enabled:
            self.log.info("Periodic advertisement started.")
        else:
            self.pawr_active = False
            if self.pawr_restart is not None:
                self.log.info("Periodic advertisement re-start requested.")
                self.start_pawr_train(self.pawr_restart)
                self.pawr_restart = None
            else:
                self.log.info("Periodic advertisement stopped.")

    def esl_event_scan_status(self, evt: esl_lib.EventScanStatus):
        """ ESL event handler """
        if evt.enabled:
            self.log.info("Scanning started.")
        else:
            self.log.info("Scanning stopped.")
            self.scan_runs = False

    def esl_event_configure_tag_response(self, evt: esl_lib.EventConfigureTagResponse):
        """ ESL event handler """
        self.update_state(CONNECTED)
        if evt.status == elw.SL_STATUS_OK:
            tag = self.get_tag(evt.connection_handle)
            tag.gatt_values[evt.type] = tag.gatt_write_values[evt.type]
            if tag.provisioned:
                self.log.info("ESL Tag fully provisioned")
                if self.controller_command == CCMD_CONFIG:
                    self.notify_controller(CCMD_CONFIG, CONTROLLER_COMMAND_SUCCESS,
                                           tag.esl_address,
                                           str(tag.ble_address),
                                           tag.max_image_index + 1 if tag.max_image_index is not None else 0,
                                           len(tag.display_info),
                                           struct.pack('<H', S_ID_PRESENT_INPUT_VOLTAGE) if S_ID_PRESENT_INPUT_VOLTAGE in tag.sensor_info else struct.pack('<H', 0x0000),
                                           struct.pack('<H', S_ID_PRESENT_DEVICE_OPERATING_TEMPERATURE) if S_ID_PRESENT_DEVICE_OPERATING_TEMPERATURE in tag.sensor_info else struct.pack('<H', 0x0000))

    def esl_event_control_point_response(self, evt: esl_lib.EventControlPointResponse):
        """ ESL event handler """
        self.log.info("Command written successfully")
        esl_id, _ = self.esl_addr_from_bt(self.connection_dict[evt.connection_handle])
        if evt.data_sent[0] == TLV_OPCODE_UPDATE_COMPLETE and evt.data_sent[1] == esl_id:
            self.past()

    def esl_event_image_transfer_finished(self, evt: esl_lib.EventImageTransferFinished):
        """ ESL event handler """
        self.log.info("Image sent to the device")
        if self.controller_command == CCMD_REQUEST_DATA:
            self.notify_controller(CCMD_IMAGE_UPDATE, CONTROLLER_COMMAND_SUCCESS)

    def esl_event_connection_closed(self, evt: esl_lib.EventConnectionClosed):
        """ ESL event handler """
        self.log.info(f"Connection to {evt.address} closed with reason " + esl_lib.get_enum("SL_STATUS_",evt.reason))
        self.past_timer.cancel()
        try:
            tag = self.tags[evt.address]
        except KeyError:
            # Create dummy tag object
            tag = Tag(evt.address, dummy=True)
        self.past_initiated = False
        if evt.reason == elw.SL_STATUS_BT_CTRL_REMOTE_USER_TERMINATED:
            if tag.esl_address is not None and not tag.pending_unassociate:
                tag.state = ST_SYNCHRONIZED
                tag.update_flags(BASIC_STATE_FLAG_SYNCHRONIZED)
            else:
                tag.state = ST_UNASSOCIATED
            tag.unresp_command_number = 0
            tag.update_timestamps()
        elif evt.reason == elw.SL_STATUS_BT_CTRL_CONNECTION_TERMINATED_BY_LOCAL_HOST:
            tag.state = ST_UNSYNCHRONIZED
            tag.update_flags(BASIC_STATE_FLAG_SYNCHRONIZED, False)
        if tag.esl_address is not None:
            log(tag.get_info())
        elif not tag.provisioned:
            self.key_db.delete_ltk(tag.ble_address)
        self.active_address = None
        del self.connection_dict[evt.connection_handle]
        self.update_state(IDLE)

    def esl_event_control_point_notification(self, evt: esl_lib.EventControlPointNotification):
        """ ESL event handler """
        # after an unassociate all command sent the evt.address will not be part of the list of tags!
        tag = self.get_tag(evt.connection_handle)
        if tag is None:
            return
        tag.update_state(evt.data, ST_UPDATING if tag.provisioned else ST_CONFIGURING)
        parse_response_data(evt.data, tag.sensor_info)
        if evt.data[0] == TLV_RESPONSE_BASIC_STATE:
            tag.basic_state_flags = int.from_bytes(evt.data[1:2], 'little')
            if tag.pending_unassociate:
                self.remove_tag(tag.esl_id, tag.group_id)
        if self.controller_command != None:
            self.notify_controller(self.controller_command, CONTROLLER_COMMAND_SUCCESS, tag.esl_id, tag.group_id, evt.data)

    def esl_event_pawr_response(self, evt: esl_lib.EventPawrResponse):
        """ ESL event handler """
        address = self.identify_sender_tag(evt.response_slot, evt.subevent)
        if address is not None:
            response = self.ead.decrypt(evt.data, KeyMaterial(self.tags[address].response_key))
            if len(response):
                self.handle_pawr_response(response, evt.response_slot, evt.subevent)
            else:
                pass # decryption error occured
        else:
            self.log.warning("PAwR response received but unable to decrypt: 0x" + evt.data.hex())

    def esl_event_pawr_data_request(self, evt: esl_lib.EventPawrDataRequest):
        """ ESL event handler """
        subevents = list(range(evt.subevent_start, evt.subevent_start + evt.subevent_data_count))
        self.send_pawr_commands([s % self.subevent_count for s in subevents])
        self.synchronization_handler()

    def esl_event_error(self, evt: esl_lib.EventError):
        """ ESL event handler """
        if evt.lib_status == elw.ESL_LIB_STATUS_BONDING_FAILED:
            if evt.sl_status in [elw.SL_STATUS_BT_CTRL_PIN_OR_KEY_MISSING, elw.SL_STATUS_BT_SMP_PAIRING_NOT_SUPPORTED]:
                tag = self.get_tag(evt.node_id)
                if tag is not None:
                    self.key_db.delete_ltk(tag.ble_address)
                self.active_address = None
                self.update_state(IDLE)
        elif evt.lib_status in [elw.ESL_LIB_STATUS_CONN_FAILED, elw.ESL_LIB_STATUS_CONN_CLOSE_FAILED, elw.ESL_LIB_STATUS_CONN_TIMEOUT]:
            self.past_initiated = False
            if evt.lib_status != elw.ESL_LIB_STATUS_CONN_CLOSE_FAILED:
                if self.active_address in self.ble_addresses:
                    self.ble_addresses.remove(self.active_address) # remove the device from the unprovisioned/advertising list
            if evt.sl_status != elw.SL_STATUS_ALREADY_EXISTS:
                # remove node from self.connection_dict
                self.connection_dict = {node:address for node, address in self.connection_dict.items() if address != self.active_address}
                self.active_address = None
                self.update_state(IDLE)
        elif evt.lib_status == elw.ESL_LIB_STATUS_GATT_TIMEOUT:
            tag = self.get_tag(evt.node_id)
            if tag is not None:
                if not tag.provisioned:
                    self.key_db.delete_ltk(tag.ble_address)
                    self.reorder_device_list(tag.ble_address)
            self.log.error("GATT Timeout, AP goes IDLE")
            self.update_state(IDLE)
        elif evt.lib_status == elw.ESL_LIB_STATUS_OTS_GOTO_FAILED:
            if evt.sl_status == elw.SL_STATUS_NOT_FOUND:
                self.log.error("No object found with the requested Object ID")
            return
        elif evt.lib_status == elw.ESL_LIB_STATUS_PAWR_START_FAILED:
            self.pawr_active = False
        elif evt.lib_status == elw.ESL_LIB_STATUS_PAST_INIT_FAILED:
            if evt.sl_status == elw.SL_STATUS_BT_CTRL_COMMAND_DISALLOWED:
                self.log.info("PAST skipped by ESL already in Synchronized state.")

    def esl_event_image_type(self, evt: esl_lib.EventImageType):
        # Cache image type
        tag = self.get_tag(evt.connection_handle)
        tag.ots_image_type[evt.img_index] = evt.type_data[3]
        self.ap_imageupdate(evt.img_index, self.image_file, False, label=self.label, rotation=self.rotation)

    def esl_event_bonding_data(self, evt: esl_lib.EventBondingData):
        """ ESL event handler """
        # export new LTK
        self.key_db.add_ltk(evt.address, evt.ltk)

    # ----------------------------------------------------------------------------------------------
    # ESL event handler method extensions in CLI mode

    def cli_esl_event_error(self, evt: esl_lib.EventError):
        if evt.lib_status == elw.ESL_LIB_STATUS_CONN_FAILED:
            if evt.sl_status == elw.SL_STATUS_ABORT and evt.node_id not in self.blocked_list: # handle advertisers bonded to different AP
                self.log.info("ESL at address %s refused connection attempts - probably bonded to other AP", evt.node_id)

    def cli_esl_event_system_boot(self, evt: esl_lib.EventSystemBoot):
        """ ESL event handler in CLI mode """
        self.log.info("Command line event handler started, system is idle.")
        self.log.info("Type 'help' for available commands.")

    def cli_esl_event_tag_found(self, evt: esl_lib.EventTagFound):
        """ ESL event handler in CLI mode """
        if evt.rssi > self.rssi_threshold:
            if evt.address not in self.ble_addresses:
                if not self.pawr_active:
                    self.log.warning("ESL Tag cannot be synchronized because PAwR is not started.")
                    self.log.info("Please start PAwR with command: 'sync start' before configuring.")
                self.ble_addresses.append(evt.address)


    def cli_esl_event_connection_closed(self, evt: esl_lib.EventConnectionClosed):
        """ ESL event handler in CLI mode """
        if self.auto_override:
            self.cmd_mode = False
            self.auto_override = False
            self.log.warning("REVERT TO AUTO MODE!")
            self.set_mode_handlers()

    # ----------------------------------------------------------------------------------------------
    # ESL event handler method extensions in auto mode

    def auto_esl_event_system_boot(self, evt: esl_lib.EventSystemBoot):
        """ ESL event handler in auto mode """
        self.start_scan()
        self.start_pawr_train()

    def auto_esl_event_tag_found(self, evt: esl_lib.EventTagFound):
        """ ESL event handler in auto mode """
        if evt.rssi > self.rssi_threshold:
            if self.pawr_active:
                if evt.address not in self.blocked_list:
                    if evt.address in self.ble_addresses and self.state == IDLE:
                        self.connect(evt.address)
            elif evt.address not in self.ble_addresses:
                self.log.error("ESL Tag cannot be synchronized because PAwR is not started!")
                self.log.info("Please re-start auto mode with command: 'mode auto' to recover.")
            if evt.address not in self.ble_addresses:
                self.ble_addresses.append(evt.address)
                if self.state == IDLE:
                    self.check_address_list()

    def auto_esl_event_error(self, evt: esl_lib.EventError):
        """ ESL event handler in auto mode """
        tag = self.get_tag(evt.node_id)
        if evt.lib_status == elw.ESL_LIB_STATUS_GATT_TIMEOUT:
            self.check_address_list()
        elif evt.lib_status in [elw.ESL_LIB_STATUS_OTS_INIT_FAILED, elw.ESL_LIB_STATUS_OTS_META_READ_FAILED]:
            self.disconnect()
        elif evt.lib_status in [elw.ESL_LIB_STATUS_OTS_ERROR, elw.ESL_LIB_STATUS_OTS_TRANSFER_FAILED, elw.ESL_LIB_STATUS_OTS_GOTO_FAILED, elw.ESL_LIB_STATUS_OTS_UNEXPECTED_OFFSET, elw.ESL_LIB_STATUS_OTS_WRITE_RESP_FAILED]:
            try:
                self.upload_next_image(tag)
            except:
                self.check_address_list()
        elif evt.lib_status == elw.ESL_LIB_STATUS_OTS_GOTO_FAILED:
            if evt.sl_status == elw.SL_STATUS_NOT_FOUND:
                self.upload_next_image(tag)
        elif evt.lib_status in [elw.ESL_LIB_STATUS_CONN_FAILED, elw.ESL_LIB_STATUS_CONN_CLOSE_FAILED, elw.ESL_LIB_STATUS_CONN_TIMEOUT]:
            if evt.sl_status == elw.SL_STATUS_ABORT and evt.node_id not in self.blocked_list: # handle advertisers bonded to different AP
                self.blocked_list.append(evt.node_id)
                self.log.warning("ESL at address %s has been blocked due to too many failed connection attempts", evt.node_id)
            self.auto_override = False
            self.set_mode_handlers()
            self.reorder_device_list(evt.node_id)
            self.check_address_list()

    def auto_esl_event_connection_opened(self, evt: esl_lib.EventConnectionOpened):
        """ ESL event handler in auto mode """
        if self.auto_override:
            self.log.warning("AUTO MODE TEMPORARILY CHANGED TO MANUAL!")
            self.cmd_mode = self.auto_override
            self.set_mode_handlers()

    def auto_esl_event_tag_info(self, evt: esl_lib.EventTagInfo):
        """ ESL event handler in auto mode """
        if not self.auto_override:
            tag = self.get_tag(evt.connection_handle)
            values = self.configure(tag)
            if self.state == CONNECTED:
                self.write_values(tag, values) # auto-refreshing the existing tag config may already doing this

    def auto_esl_event_control_point_response(self, evt: esl_lib.EventControlPointResponse):
        """ ESL event handler in auto mode """
        if evt.status == elw.SL_STATUS_OK:
            esl_id, group_id = self.esl_addr_from_bt(self.connection_dict[evt.connection_handle])
            if not (evt.data_sent[0] == TLV_OPCODE_UPDATE_COMPLETE and evt.data_sent[1] == esl_id):
                self.ap_update_complete(esl_id, group_id)

    def auto_esl_event_configure_tag_response(self, evt: esl_lib.EventConfigureTagResponse):
        """ ESL event handler in auto mode """
        if evt.status == elw.SL_STATUS_OK:
            tag = self.get_tag(evt.connection_handle)
            if tag.provisioned:
                if tag.max_image_index is not None and tag.has_image_transfer and IMAGE_MAX_AUTO_UPLOAD_COUNT and tag.auto_image_count < min((tag.max_image_index + 1), IMAGE_MAX_AUTO_UPLOAD_COUNT):
                    self.upload_auto_image(tag.auto_image_count)
                else:
                    esl_id, group_id = self.esl_addr_from_bt(self.connection_dict[evt.connection_handle])
                    self.ap_update_complete(esl_id, group_id)

    def auto_esl_event_image_transfer_finished(self, evt: esl_lib.EventImageTransferFinished):
        """ ESL event handler in auto mode """
        self.upload_next_image(self.get_tag(evt.connection_handle))

    def auto_esl_event_connection_closed(self, evt: esl_lib.EventConnectionClosed):
        """ ESL event handler in auto mode """
        if self.auto_override:
            self.cmd_mode = False
            self.auto_override = False
        self.reorder_device_list(evt.address)
        self.check_address_list()

    # ----------------------------------------------------------------------------------------------
    # ESL event handler method extensions in demo mode

    def demo_esl_event_system_boot(self, evt: esl_lib.EventSystemBoot):
        """ ESL event handler in demo mode """
        # Enable advertising
        self.lib.general_command(CMD_AP_CONTROL_ADV_ENABLE, b'\x01')
        self.scan_runs = False
        self.start_scan()
        self.pawr_active = False
        self.pawr_handle = None
        self.pawr_restart = None
        self.start_pawr_train()

    def demo_esl_event_general(self, evt: esl_lib.EventGeneral):
        """ ESL event handler in demo mode """
        subevent = evt.data[0]
        if subevent == 3:
            self.demo_ap_control_image_transfer(evt.data[1:])
        elif subevent == 2:
            self.demo_ap_control_request(evt.data[1:])
        elif subevent == 1:
            self.demo_ap_control_status(evt.data[1])

    def demo_ap_control_request(self, data: bytes):
        """ ESL subevent handler in demo mode """
        try:
            mcommand = data.decode('ascii')
            self.log.info("Command arrived from controller: %s", mcommand)
        except UnicodeDecodeError as e:
            self.log.error("Cannot decode command")
            self.log.error(e)
            self.notify_controller(CCMD_UNKNOWN, CONTROLLER_COMMAND_FAIL)
            return
        DEMO_COMMAND_DICT = {"connect": CCMD_CONNECT,
                             "config": CCMD_CONFIG,
                             "disconnect": CCMD_DISCONNECT,
                             "image_update": CCMD_IMAGE_UPDATE,
                             "display_image": CCMD_DISPLAY_IMAGE,
                             "led": CCMD_LED,
                             "list": CCMD_LIST,
                             "ping": CCMD_PING,
                             "unassociate": CCMD_UNASSOCIATE}
        command = mcommand.split(maxsplit=1)[0]
        # Additional actions for image update
        if command == "image_update":
            self.image_from_controller = b""
            self.image_data_offset = bytearray(4)
        try:
            self.controller_command = DEMO_COMMAND_DICT[command]
            if self.cli_queue is not None:
                if mcommand.find("full") != -1:
                    mcommand = mcommand.replace("full", "--full")
                elif mcommand.find("index=0") != -1:
                    mcommand = mcommand.replace("index=", "--index ")
                self.cli_queue.put(mcommand)
        except KeyError:
            self.log.error("Not a valid command")
            self.notify_controller(CCMD_UNKNOWN, CONTROLLER_COMMAND_FAIL)

    def demo_ap_control_image_transfer(self, data: bytes):
        """ ESL subevent handler in demo mode """
        if len(data) >= 3:
            # Store image data
            self.image_from_controller += data[1:]
            self.image_data_offset = struct.pack("<I", (len(self.image_from_controller) & 0xFFFFFFFF))
        if data[0] == CONTROLLER_REQUEST_MORE_DATA:
            # Request more data
            self.notify_controller(CCMD_REQUEST_DATA, CONTROLLER_COMMAND_SUCCESS, REQUEST_IMAGE_DATA_HEADER, self.image_data_offset, REQUEST_IMAGE_DATA_RESERVED)
        elif data[0] == CONTROLLER_REQUEST_LAST_DATA:
            # This was the last data, starting image update
            self.ap_imageupdate(self.controller_image_index, self.image_from_controller, from_console=False)
        else:
            self.log.error("Invalid data chunk arrived during image_update")
            self.notify_controller(CCMD_IMAGE_UPDATE, CONTROLLER_COMMAND_FAIL)

    def demo_ap_control_status(self, status: int):
        """ ESL subevent handler in demo mode """
        status_dict = {
            0x00: "disconnected",
            0x01: "connected",
            0x02: "subscribed"}
        try:
            status_str = status_dict[status]
        except KeyError:
            status_str = "unknown"
        self.log.info("AP control status %s", status_str)
        if self.demo_mode and status == 0x00:
            self.demo_mode = False
            self.ap_adv_start()

    def demo_esl_event_connection_opened(self, evt: esl_lib.EventConnectionOpened):
        """ ESL event handler in demo mode """
        if self.controller_command != None and not self.demo_auto_reconfigure:
            self.notify_controller(self.controller_command,CONTROLLER_COMMAND_SUCCESS)

    def demo_esl_event_tag_found(self, evt: esl_lib.EventTagFound):
        """ ESL event handler in demo mode """
        if self.pawr_active and evt.address in self.tags and self.state == IDLE:
            self.connect(evt.address)
            self.demo_auto_reconfigure = True

    def demo_esl_event_configure_tag_response(self, evt: esl_lib.EventConfigureTagResponse):
        """ ESL demo event handler """
        self.update_state(CONNECTED)
        if evt.status == elw.SL_STATUS_OK:
            tag = self.get_tag(evt.connection_handle)
            tag.gatt_values[evt.type] = tag.gatt_write_values[evt.type]
            if tag.provisioned and self.demo_auto_reconfigure:
                self.ap_update_complete(tag.esl_id, tag.group_id)

    def demo_esl_event_connection_closed(self, evt: esl_lib.EventConnectionClosed):
        """ ESL event handler in demo mode """
        self.demo_auto_reconfigure = False
        if self.controller_command == CCMD_DISCONNECT:
            self.notify_controller(self.controller_command, CONTROLLER_COMMAND_SUCCESS)
        elif self.controller_command != None:
            # In case of other command, the connection should't be closed -if closed it's a failure
            self.notify_controller(self.controller_command, CONTROLLER_COMMAND_FAIL)

    def demo_esl_event_error(self, evt: esl_lib.EventError):
        """ ESL event handler in demo mode """
        if evt.lib_status == elw.ESL_LIB_STATUS_CONN_FAILED:
            if self.controller_command != None:
                self.notify_controller(self.controller_command, CONTROLLER_COMMAND_FAIL)
        elif evt.lib_status == elw.ESL_LIB_STATUS_OTS_ERROR:
            if self.controller_command == CCMD_REQUEST_DATA:
                self.notify_controller(CCMD_IMAGE_UPDATE, CONTROLLER_COMMAND_FAIL)
        elif evt.lib_status in [elw.ESL_LIB_STATUS_OTS_INIT_FAILED, elw.ESL_LIB_STATUS_OTS_META_READ_FAILED]:
            self.disconnect()

    def check_address_list(self):
        """ Check address list """
        next_addr = list(set(self.ble_addresses) - set(self.blocked_list))
        self.log.info("Checking for next tag in list")
        if next_addr:
            if self.state == IDLE:
                self.log.debug(f"Address list: {str(next_addr)}")
                try:
                    self.connect(next_addr[0])
                    self.active_address = next_addr[0]
                except:
                    self.update_state(IDLE)
                    pass
            else:
                self.log.warning("Access point should be idle - auto provisioning may stop!")
        else:
            self.log.info("Advertising list is empty")
            if not self.scan_runs and not self.cmd_mode:
                self.log.warning("Scaning is disabled in auto mode.")

    def get_pawr_params(self):
        """ Get periodic advertisement current parameter set """
        return [self.adv_interval_min,
                self.adv_interval_max,
                self.subevent_count,
                self.subevent_interval,
                self.response_slot_delay,
                self.response_slot_spacing,
                self.response_slot_count]

    def set_pawr_interval(self, adv_interval=None, persistive=False):
        """
        Set periodic advertisement interval

        parameter:
            adv_interval: Periodic advertisement interval in units of 1.25 ms
        """
        adv_interval_max = self.adv_interval_max
        if adv_interval:
            adv_interval_max = adv_interval[-1]
            if persistive:
                self.adv_interval_min = adv_interval[0]
                self.adv_interval_max = adv_interval_max
        self.pa_timer_interval = adv_interval_max / 1000.0
        # Reinitilazize past timer, because pa interval has changed
        self.reinit_past_timer()

    def pawr_configure(self, adv_interval_min, adv_interval_max, subevent_count, subevent_interval, response_slot_delay, response_slot_spacing, response_slot_count):
        """
        Set PAwR configuration, validate if possible

        """
        self.adv_interval_min = adv_interval_min
        self.adv_interval_max = adv_interval_max
        self.subevent_count = subevent_count
        self.subevent_interval = subevent_interval
        self.response_slot_delay = response_slot_delay
        self.response_slot_spacing = response_slot_spacing
        self.response_slot_count = response_slot_count
        if self.pawr_handle is not None:
            self.lib.pawr_configure(self.pawr_handle,
                                    adv_interval_min=self.adv_interval_min,
                                    adv_interval_max=self.adv_interval_max,
                                    subevent_count=self.subevent_count,
                                    subevent_interval=self.subevent_interval,
                                    response_slot_delay=self.response_slot_delay,
                                    response_slot_spacing=self.response_slot_spacing,
                                    response_slot_count=self.response_slot_count)
        else:
            self.log.warning("PAwR is not running, skipping parameter validation.")

    def start_pawr_train(self, adv_interval=None):
        """
        Start periodic advertisement command

        parameter:
            adv_interval: Periodic advertisement interval in natural units
        """
        if not self.pawr_active:
            self.set_pawr_interval(adv_interval)
            if self.pawr_handle is None:
                self.pawr_handle = self.lib.pawr_create()
            self.lib.pawr_configure(self.pawr_handle,
                                    adv_interval_min=self.adv_interval_min if adv_interval is None else adv_interval[0],
                                    adv_interval_max=self.adv_interval_max if adv_interval is None else adv_interval[-1],
                                    subevent_count=self.subevent_count,
                                    subevent_interval=self.subevent_interval,
                                    response_slot_delay=self.response_slot_delay,
                                    response_slot_spacing=self.response_slot_spacing,
                                    response_slot_count=self.response_slot_count)
            self.lib.pawr_enable(self.pawr_handle)
            self.pawr_active = True
        else:
            self.pawr_restart = adv_interval if adv_interval is not None else [self.adv_interval_min, self.adv_interval_max]
            self.stop_pawr_train()

    def stop_pawr_train(self):
        """ Stop periodic advertisement command """
        if self.pawr_active:
            self.lib.pawr_enable(self.pawr_handle, False)
        else:
            self.log.info("PAwR train is not running.")

    def update_pending_commands_list(self, gid, cmds):
        """ Update unresponded command list """
        last_slotnum = {}
        # Get ESL response slot numbers
        for i in range(len(cmds)):
            esl_id = cmds[i][1]
            if esl_id != BROADCAST_ADDRESS:
                last_slotnum[esl_id] = i

        self.esl_pending_commands_lock.acquire()
        if gid not in self.esl_pending_commands:
            self.esl_pending_commands[gid] = []

        for i in range(len(cmds)):
            esl_id = cmds[i][1]
            # Broadcast address does not need response
            if esl_id != BROADCAST_ADDRESS:
                new_command = ESLCommand(cmds[i], gid, last_slotnum[esl_id])
                if new_command.response_opcode is not None:
                    self.esl_pending_commands[gid].insert(0,new_command)
        self.esl_pending_commands_lock.release()

    def remove_outdated_commands(self, limit):
        """ Remove outdated unresponded commands """
        now = dt.now().timestamp()
        self.esl_pending_commands_lock.acquire()
        empty_gid_list = []
        for key in self.esl_pending_commands:
            pop_list = []
            for item in self.esl_pending_commands[key]:
                if (now - item.timestamp) > limit:
                    cmd = item
                    self.log.warning("Unresponded command (0x%s) in subevent %s slot %d removed from queue.", cmd.params.hex(), key, cmd.slot_number)
                    address = self.bt_addr_from_esl(cmd.esl_id, cmd.group_id)
                    pop_list.append(self.esl_pending_commands[key].index(item))
                    if address in self.tags:
                        tag = self.tags[address]
                        if tag.unresp_command_number > 0:
                            tag.unresp_command_number -= 1

            for i in reversed(pop_list):
                self.esl_pending_commands[key].pop(i)

            # remove any empty dictionaries
            if len(self.esl_pending_commands[key]) == 0:
                empty_gid_list.append(key)

        for gid in empty_gid_list:
            del self.esl_pending_commands[gid]

        self.esl_pending_commands_lock.release()

    def remove_esl_pending_command(self, cmd):
        """ Remove command """
        gid = cmd.group_id
        self.esl_pending_commands_lock.acquire()
        if gid in self.esl_pending_commands:
            self.esl_pending_commands[gid].remove(cmd)

        # delete any emptied dictionary
        if len(self.esl_pending_commands[gid]) == 0:
            del self.esl_pending_commands[gid]

        self.esl_pending_commands_lock.release()

    def get_latest_command(self, tag: Tag):
        """ Get the latest pawr command sent to a tag """
        latest = None
        esl_id = tag.esl_id
        group_id = tag.group_id

        if group_id in self.esl_pending_commands:
            for cmd in self.esl_pending_commands[group_id]:
                if cmd.esl_id == esl_id and cmd.group_id == group_id:
                    if latest is not None:
                        if cmd.timestamp > latest.timestamp:
                            latest = cmd
                    else:
                        latest = cmd
        return latest

    def create_sync_packet(self, gid, tlvs):
        """
        Create ESL synchronization packet.

        parameters:
            tlvs: TLV list
        packet format:
            [ Randomizer | gid | TLV_0 | ... | TLV_n | MIC ]
        returns:
            pack: synchronization packet
        """
        pack = b""
        if (gid < 0) or (gid > 127):
            self.log.warning("Group id must be between 0 and 127")
            return None

        if tlvs:
            #print(gid)
            #gid += 1 # uncomment for ESLP/ESL/SYNC/BI-02-I [Invalid Synchronization Packet] Case 1
            payload = (gid).to_bytes(1, byteorder='little')
            for tlv in tlvs:
                payload += tlv
            self.log.debug("Unencrypted PAwR payload to send: %s", payload.hex())

            pack = self.ead.encrypt(payload, KeyMaterial(self.ap_key))
            #print(pack.hex())
            #pack = pack[:2] + b"*" + pack[3:] # uncomment for ESLP/ESL/SYNC/BI-02-I [Invalid Synchronization Packet] Case 2
            #print(pack.hex())
        else:
            self.log.warning("No TLV values to send")
            pack = None
        return pack

    def get_opcode_len(self, tlv):
        """ Decode opcode length from tlv """
        o_len = (tlv & 0xf0) >> 4
        o_len += 2  # Add TLV and ESL_ID bytes to the length
        return o_len

    def set_tlv_len(self, tlv, len):
        """ Encode length to a tlv """
        new_tlv = (len & 0x0f) << 4
        new_tlv |= (tlv & 0x0f)
        return new_tlv

    def start_scan(self, active=False, clear_lists=False):
        """ Start scanning """
        if clear_lists:
            self.ble_addresses.clear()
            self.blocked_list.clear()
        if not self.scan_runs:
            self.lib.scan_configure(active_mode=active)
            self.lib.scan_enable()
            self.scan_runs = True
        else:
            self.log.info("Scanning already running.")

    def stop_scan(self):
        """ Stop scanning """
        if self.scan_runs:
            self.lib.scan_enable(False)
            self.ble_addresses.clear()
        else:
            self.log.info("Scanning is not running.")

    def init_tag(self, address, gattdb_handles=None):
        """ Tag initialization """
        if address not in self.tags:
            self.tags[address] = Tag(address)
            self.tags[address].state = ST_CONFIGURING
            self.log.info("Registering ESL Tag at BLE address: "  + str(address))
        if gattdb_handles is not None:
            self.tags[address].gattdb_handles = gattdb_handles
        self.tags[address].pending_unassociate = False
        if self.tags[address].provisioned:
            self.log.info("Already known Tag at BLE address: "  + str(address))
            self.tags[address].state = ST_UPDATING
            cmd = self.get_latest_command(self.tags[address])
            if cmd is not None:
                self.log.debug("Unresponded command removed from PAwR queue!")
                self.remove_esl_pending_command(cmd)

    def configure(self, tag: Tag):
        """ Configure tag
        parameters:
            tag: ESL Tag to configure """

        if tag.esl_address is None:
            esl_address = self.new_auto_address(tag.id)
        else:
            esl_address = tag.esl_address

        self.absolute_now = self.get_absolute_time()

        values = {
            elw.ESL_LIB_DATA_TYPE_GATT_ESL_ADDRESS: esl_address.to_bytes(2, "little"),
            elw.ESL_LIB_DATA_TYPE_GATT_RESPONSE_KEY: self.generate_key_material(),
            elw.ESL_LIB_DATA_TYPE_GATT_AP_SYNC_KEY: self.ap_key,
            elw.ESL_LIB_DATA_TYPE_GATT_CURRENT_TIME: self.absolute_now.to_bytes(4, "little")
        }
        return values

    def connect(self, address, subevent=None):
        """ Establish connection with a tag normally or via PAwR"""
        if subevent is not None:
            pawr = esl_lib.PAWRSubevent(self.pawr_handle, subevent)
        else:
            pawr = None
        self.update_state(CONNECTING)
        ltk = self.key_db.find_ltk(address)
        if ltk is not None:
            key_type = elw.ESL_LIB_KEY_TYPE_LTK
        else:
            key_type = elw.ESL_LIB_KEY_TYPE_NO_KEY
        gattdb_handles = None
        if address in self.tags:
            gattdb_handles = self.tags[address].gattdb_handles
        self.log.info(f"Request connecting to: {address}")
        self.lib.connect(address, pawr, key_type=key_type, key=ltk, gattdb=gattdb_handles)

    def disconnect(self, address=None):
        """ Close connection with a tag """
        self.past_initiated = False

        if address is None:
            address = self.active_address
        try:
            self.lib.close_connection(self.conn_handle_from_bt(address))
        except esl_lib.CommandFailedError as err:
            self.log.warning(f"Failed to disconnect from {address}: {err}")

    def past(self, address=None):
        """ Do Periodic Advertisement Sync Transfer over connection """
        if self.past_initiated or self.active_address not in self.tags:
            return
        elif not self.pawr_active:
            self.disconnect(address)
            return

        # TODO: Since the PAST may take very long time by definition, it would be necesssary to open more connections in parallel while we're waiting for the Tags to get synced. Otherwise, the system scalability will suffer.
        if address is None:
            address = self.active_address
        self.lib.initiate_past(self.conn_handle_from_bt(address), self.pawr_handle)
        self.past_initiated = True
        if not self.past_timer.is_alive():
            self.reinit_past_timer()
            self.past_timer.start()

    def past_timeout(self):
        """ Called on PAST timeout """
        self.log.warning("PAST timeout, force close!")
        self.disconnect()

    def reinit_past_timer(self):
        """ Reinitialize PAST timer """
        running = self.past_timer.is_alive()
        if running:
            self.past_timer.cancel()
        self.past_timer = threading.Timer(self.pa_timer_interval * AUX_SYNC_IND_PDU_MAX_SKIP_COUNT, self.past_timeout)
        self.past_timer.daemon = True
        if running:
            self.past_timer.start()

    def write_values(self, tag: Tag, values: dict):
        """ Write values """
        tag.gatt_write_values.update(values)
        self.lib.configure_tag(self.conn_handle_from_bt(tag.ble_address), values, att_response=not IOP_TEST)
        self.update_state(WRITING_VALUES)

    def upload_auto_image(self, image_index):
        """ Automatic image update helper """
        if self.selected_image < (len(self.image_files) - 1):
            self.selected_image += 1
        else:
            self.selected_image = 0
        image_path = self.image_path + random.choice(random.sample(self.image_files, len(self.image_files)))
        self.ap_imageupdate(image_index, image_path, False)

    def update_image(self, image_index):
        """ Image update """
        self.lib.write_image(self.conn_handle_from_bt(self.active_address), image_index, self.raw_image)

    def shutdown(self):
        """ Initiate shutdown """
        try:
            self.lib.stop()
        except esl_lib.CommandFailedError:
            self.log.warning("Clean shutdown failed")

    def shutdown_cli(self):
        """ Propagate shutdown towards the CLI """
        if self.cli_queue is not None:
            self.cli_queue.put("exit")

    def get_tag(self, node_id):
        try:
            if isinstance(node_id, esl_lib.Address):
                return self.tags[node_id]
            elif isinstance(node_id, int): # Connection handle is assumed
                return self.tags[self.connection_dict[node_id]]
        except KeyError:
            pass
        return None

    def conn_handle_from_bt(self, bt_addr: esl_lib.Address):
        """ Find connection handle from BT address """
        conn_dict_inverse = {addr: conn for conn, addr in self.connection_dict.items()}
        try:
            return conn_dict_inverse[bt_addr]
        except KeyError:
            return None

    def esl_addr_from_bt(self, bt_addr: esl_lib.Address):
        """ Return with ESL ID and group ID from BT address """
        if bt_addr in self.tags:
            tag = self.tags[bt_addr]
            if tag.provisioned:
                return tag.esl_id, tag.group_id
        return None, None

    def is_tag_connected(self, esl_id, group_id):
        """ Returns true when a connection is open with the tag """
        address = self.bt_addr_from_esl(esl_id, group_id)
        return address is not None and address == self.active_address

    def bt_addr_from_esl(self, esl_id, group_id):
        """ Return BT address according to ESL ID and group ID """
        esl_addr = esl_id | (group_id << 8)
        if esl_id != BROADCAST_ADDRESS:
            for k in self.tags:
                if self.tags[k].esl_address == esl_addr:
                    return self.tags[k].ble_address
        return None

    def esl_id_exist(self, esl_id, group_id):
        """ Check if ESL ID is exist """
        for tag in self.tags.values():
            if tag.esl_id == esl_id and tag.group_id == group_id:
                return True
        return False

    def is_there_tag(self, state):
        """ Check if there is any tag in state described by 'state' argument """
        for tag in self.tags.values():
            if tag.state == state:
                return True
        return False

    def set_tags_state(self, state_to, state_from=None):
        """ Set the state of the ESL tags to 'state_to' """
        for addr in self.tags:
            if state_from is not None:
                if self.tags[addr].state == state_from:
                    self.tags[addr].state = state_to
                    if state_to == ST_UNSYNCHRONIZED:
                        self.tags[addr].update_flags(BASIC_STATE_FLAG_SYNCHRONIZED, False)
            else:
                self.tags[addr].state = state_to

    def remove_tag(self, esl_id, group_id):
        """ Remove tag from lists """
        bt_addr = self.bt_addr_from_esl(esl_id, group_id)
        if bt_addr is not None or esl_id == BROADCAST_ADDRESS:
            bt_addr_rem = [] # Elements to remove
            if bt_addr in self.tags:
                bt_addr_rem.append(bt_addr)
            if bt_addr in self.ble_addresses:
                self.ble_addresses.remove(bt_addr)

            # Remove all tag belongs to the group because of broadcast
            if esl_id == BROADCAST_ADDRESS:
                for k in self.tags:
                    eid, gid = self.esl_addr_from_bt(k)
                    if gid == group_id and not self.is_tag_connected(eid, gid):
                        bt_addr_rem.append(k)
                        if k in self.ble_addresses:
                            self.ble_addresses.remove(k)
            for addr in bt_addr_rem:
                self.tags.pop(addr, None)
                self.key_db.delete_ltk(addr)

    def get_esl_id(self, addr, group_id):
        """ Return ESL ID from either BT address or ESL ID string """
        esl_id = None
        # Check address type
        if re.fullmatch(VALID_BD_ADDRESS_REGEX, str(addr)) is not None:
            esl_id, _ = self.esl_addr_from_bt(esl_lib.Address.from_str(str(addr)))
        else:
            if addr == "all":
                esl_id = BROADCAST_ADDRESS
            elif addr is not None:
                esl_id = int(addr)
            # Check if esl_id is out of range
            if (esl_id < 0) or (esl_id > BROADCAST_ADDRESS):
                esl_id = None
            # Warn the user if ESL ID not found
            if esl_id == BROADCAST_ADDRESS:
                self.log.warning("All Tags in group %d will be addressed!", group_id)
            elif esl_id is not None and not self.esl_id_exist(esl_id, group_id):
                esl_id = None
                self.log.warning("Tag address unknown: %s in group %d", addr, group_id)
                if self.controller_command != None:
                    self.notify_controller(self.controller_command, CONTROLLER_COMMAND_FAIL)
        return esl_id

    def route_command(self, esl_id, group_id, data, force_pawr=False):
        """ Auto route commands between periodic advertisement (with responses) and ESL Control Point """
        data = bytes(data)
        group = group_id
        if self.active_address in self.tags:
            _, group = self.esl_addr_from_bt(self.active_address)
        if self.is_tag_connected(esl_id, group_id) and not force_pawr:
            address = self.bt_addr_from_esl(esl_id, group_id)
            self.send_cp_command(address, data)
        elif IOP_TEST and self.active_address in self.tags and group_id == group\
                and ((esl_id != BROADCAST_ADDRESS and not self.esl_id_exist(esl_id, group_id)) \
                or (data[0] == TLV_OPCODE_PING)): # force sending commands with unknown ESL ID or PING to ALL (test-only command!) to ESL CP if connected for IOP test case
            self.log.warning("Sending a deliberately misaddressed command to the current ESL Control Point")
            address = self.tags[self.active_address]
            self.send_cp_command(address, data)
        else:
            if force_pawr and self.active_address in self.tags and group_id == group:
                self.log.warning("Command routing overrided, send via PAwR while connected!")
            self.queue_pawr_command(group_id, data)

    def send_cp_command(self, address: esl_lib.Address, data):
        """ Writes a command to the control point """
        if address in self.tags:
            id, gid = self.esl_addr_from_bt(address)
            if data[0] == TLV_OPCODE_UNASSOCIATE and data[1] == id:
                self.tags[address].pending_unassociate = True
        self.lib.write_control_point(self.conn_handle_from_bt(address), data, att_response=not IOP_TEST)

    def led_control_command(self, esl_id, group_id, repeat_field, led_idx,
                                absolute_value, gamut = 0, pattern = None):
        """ Execute LED control command """
        tlv = TLV_OPCODE_LED_CONTROL
        if absolute_value is not None:
            tlv = TLV_OPCODE_LED_TIMED_CONTROL
        if pattern is None:
            pattern = bytearray(7)

        data = bytearray(self.get_opcode_len(tlv))

        data[0:3] = tlv, esl_id, led_idx
        data[3] = gamut       # color and brightness bits
        data[4:11] = pattern  # Flashing_Pattern field
        data[11:13] = repeat_field
        if absolute_value is not None:
            data[13:17] = struct.pack("<I", (absolute_value & 0xFFFFFFFF))
            if absolute_value == 0:
                self.log.info("Delete timed LED control command of led index %d", led_idx)
            else:
                self.log.info("Delayed LED control command issued at absolute time %d", absolute_value)

        self.route_command(esl_id, group_id, data)

    def identify_sender_tag(self, response_slot, subevent):
        """ Identify sender Tag """
        tag_addr = None
        if subevent in self.esl_pending_commands:
            for cmd in self.esl_pending_commands[subevent]:
                # Response is in expected slot and subevent
                if cmd.slot_number == response_slot and cmd.group_id == subevent:
                    address = self.bt_addr_from_esl(cmd.esl_id, cmd.group_id)
                    if address in self.tags:
                        tag_addr = address
                        id, gid = self.esl_addr_from_bt(address)
                        if id is not None and gid is not None:
                            self.log.info("Reply from ESL ID %d, in group %d.", id, gid)
                        else:
                            self.log.error("Implausible tag identification results - address: %s, ESL ID: %s, group: %s", tag_addr, str(id), str(gid))
                        break
        return tag_addr

    def handle_encrypted_pawr_response(self, data, response_slot, subevent):
        """ Handle one or more encrypted PAwR responses """
        

    def handle_pawr_response(self, data, response_slot, subevent):
        """ Handle one or more PAwR responses """
        data_index = AD_FRAME_OVERHEAD  # skip LL frame: Length + ESL AD Type!
        data_size = 0
        cmd_pos = 0
        sensor_info = None

        if len(data) < AD_FRAME_OVERHEAD or len(data) != (int(data[0]) + 1) or data[1] != ESL_AD_TYPE:
            self.log.warning("Received response error: %s, ignore.", data.hex())
            return

        pop_list = []
        address = ""
        while data_index < len(data):
            data_size = self.get_opcode_len(data[data_index])
            last_data = data_index + data_size
            response_data = data[data_index:last_data]

            if subevent in self.esl_pending_commands:
                for cmd in self.esl_pending_commands[subevent]:
                    # Response is in expected slot and subevent
                    if cmd.slot_number == response_slot and cmd.group_id == subevent:
                        address = self.bt_addr_from_esl(cmd.esl_id, cmd.group_id)
                        # Response belongs to known address and not already processed
                        if address in self.tags and self.esl_pending_commands[subevent].index(cmd) not in pop_list:
                            # Accept responses only that allowed by the spec.
                            if cmd.opcode_valid(response_data[0]):
                                self.tags[address].update_state(response_data)
                                self.tags[address].state = ST_SYNCHRONIZED
                                # Get sensor info
                                sensor_info = self.tags[address].sensor_info
                                self.tags[address].update_response_timestamp(dt.now().timestamp())
                                if response_data[0] == TLV_RESPONSE_BASIC_STATE:
                                    if self.tags[address].pending_unassociate:
                                        esl_id, group_id = self.esl_addr_from_bt(address)
                                        self.remove_tag(esl_id, group_id)
                                # Resend retry error responses
                                if response_data[0] == TLV_RESPONSE_ERROR:
                                    if response_data[1] == ERROR_RESPONSE_RETRY or response_data[1] == ERROR_RESPONSE_CAPACITY_LIMIT:
                                        self.log.info("Resending command: (0x%s)", cmd.params.hex())
                                        self.queue_pawr_command(cmd.group_id, cmd.params)
                            # pop_list is for already processed answers - will skip those in any next round of this the for cycle
                            pop_list.append(self.esl_pending_commands[subevent].index(cmd))
                            # Since we reach this point only if given cmd has been processed exactly once, thus we have to break the cycle for now
                            break
            else:
                self.log.error("Received response can't be found in pending commands! (%s)", data.hex())
                break;

            if last_data <= len(data):
                parse_response_data(response_data, sensor_info)
                if self.controller_command is not None:
                    if address != "":
                        esl_id, group_id = self.esl_addr_from_bt(address)
                    self.notify_controller(self.controller_command, CONTROLLER_COMMAND_SUCCESS, esl_id, group_id, response_data)
            else:
                self.log.warning("Broken PAwR response chunk: " + data[data_index:].hex())
            data_index += data_size
            cmd_pos += 1

        # Remove responded commands
        self.esl_pending_commands_lock.acquire()
        for x in reversed(pop_list):
            self.esl_pending_commands[subevent].pop(x)
        self.esl_pending_commands_lock.release()

    def notify_controller(self, command_id, result, *args):
        """ Send notification to the connected controller """
        list_to_send = [command_id, result]
        b_arr = bytes()
        if args:
            for x in args:
                if (type(x) == bytes) or (type(x) == bytearray):
                    b_arr += x
                elif type(x) == str:
                    b_arr += bytes(x, 'utf-8')
                elif x == None:
                    # Tag response can be None
                    pass
                else:
                    list_to_send.append(x)
        bytearray_to_send = bytes(list_to_send)
        bytearray_to_send += b_arr
        if command_id == CCMD_REQUEST_DATA:
            self.lib.general_command(CMD_AP_CONTROL_IT_RESPONSE, bytearray_to_send[2:])
            self.controller_command = CCMD_REQUEST_DATA # request more until the end of the image file
        else:
            self.lib.general_command(CMD_AP_CONTROL_CP_RESPONSE, bytearray_to_send)
            self.controller_command = None
