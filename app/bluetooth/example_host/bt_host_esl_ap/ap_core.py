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

import threading
import re
import os
import queue
import random
import struct
import traceback
from datetime import datetime, timedelta
from ap_config import *
from ap_constants import *
from ap_sensor import *
from ap_logger import getLogger, log, logLevel, LEVELS
from ap_response_parser import ResponseParser
from esl_tag import Tag, TagState, EslState, InvalidTagStateError, ImageUpdateFailed, ImageTypeRequired
from esl_tag_db import TagDB
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
    def __init__(self, config, unsecure, cmd_mode=False, demo_mode=False):
        self.scan_runs = False
        self.pawr_active = False
        self.auto_override = False
        self.cmd_mode = cmd_mode if not demo_mode else True
        self.demo_mode = demo_mode
        self.event_handler_prefix_list = [""] # TODO: this list should be thread safe!
        self.set_mode_handlers()
        # some PAwR stuff
        self.cli_queue = None
        self.ead = EAD()
        if not unsecure:
            config += ' -secure'
        else:
            self.log.warning("Starting with NCP encryption disabled!")

        self.lib = esl_lib.Lib(config)

        self.rssi_threshold = RSSI_THRESHOLD

        self.tag_db = TagDB()
        self.ap_key = self.ead.generate_key_material()

        self.image_path = 'image/'
        self.image_files = [f for f in os.listdir(self.image_path) if os.path.isfile(os.path.join(self.image_path, f))]
        self.start_time = datetime.now()
        self.auto_config_start_time = None
        self.auto_configured_tags_in_single_run = 0
        # ESL command dictionary of lists in a format: {group_id : [tlv0, tlv1, ..., tlvN]}
        self.esl_queued_commands = {}
        self.esl_pending_commands = {}
        self.esl_command_queue_lock = threading.Lock()
        self.esl_pending_commands_lock = threading.Lock()
        # Shutdown timer is executed if boot event fails
        self.shutdown_timer = threading.Timer(3.0, self.shutdown_timeout)
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

        # State of connection count for demo/auto modes
        self.max_conn_count_reached = False
        self.bonding_finished       = True

        self.consumer = threading.Thread(target=self.dequeue, daemon=True)
        self.consumer.start()

        self.key_db = esl_key_lib.Lib()

    # Logger
    @property
    def log(self):
        return getLogger()

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
        if start is None:
            log(f"Scanning is currently{' ' if self.scan_runs else ' not '}in progress.")
        elif start:
            self.start_scan(active, clear_lists=True)
        else:
            self.stop_scan()

    def ap_connect(self, esl_id, bt_addr: str, group_id, address_type):
        """
        Connect to an ESL device with the specified address.
        input:
            - esl_id:   ESL ID or 'all' - the latter with special meaning: try connectin to more advertising tags at once
            - bt_addr:  Bluetooth address
            - group_id: ESL group ID
        """
        connecting_to = []
        if esl_id is not None:
            if esl_id == "all":
                connecting_to = [tag for tag in self.tag_db.list_state(TagState.IDLE) if (tag.advertising and (group_id is None or tag.group_id == group_id))]
            else:
                if group_id is None:
                    group_id = 0
                tag = self.tag_db.find((esl_id, group_id))
                if tag is None:
                    self.log.error("Can't connect to unknown tag: ESL ID: %u, Group ID: %u", esl_id, group_id)
                    return
                else:
                    connecting_to.append(tag)
        elif bt_addr is not None:
            if address_type is None:
                bt_address_public = esl_lib.Address.from_str(bt_addr, ADDRESS_TYPE_PUBLIC_ADDRESS)
                bt_address_static = esl_lib.Address.from_str(bt_addr, ADDRESS_TYPE_STATIC_ADDRESS)
                tags = [self.tag_db.find(bt_address_public), self.tag_db.find(bt_address_static)]
                tag_count = sum(x is not None for x in tags)
                if tag_count == 0:
                    self.log.debug("No address type given - using default public address type.") # Will result in using the default ADDRESS_TYPE_PUBLIC_ADDRESS
                elif tag_count != 1:
                    self.log.error("There are more tags in the database with same address but different address type, please specify the address type!")
                    return
                else:
                    tag = next(item for item in tags if item is not None)
                    address_type = tag.ble_address.address_type
            bt_address = esl_lib.Address.from_str(bt_addr, address_type)
            tag = self.tag_db.find(bt_address)
            if tag is None or (address_type is not None and tag.ble_address.address_type != address_type):
                tag = self.tag_db.add(self.lib, bt_address)
            connecting_to.append(tag)
        else:
            connecting_to = [tag for tag in self.tag_db.list_state(TagState.IDLE) if (tag.advertising and (group_id is None or tag.group_id == group_id))]
            if len(connecting_to) > 1:
                if group_id is None:
                    self.log.warning("There are more than one tags advertising, please specify one or issue command with argument: 'all'!")
                else:
                    self.log.warning("There are more than one advertising tag in group %d, please specify one or issue command with argument: 'all -g %d'!", group_id, group_id)
                self.ap_list(["advertising"], group_id=group_id)
                return

        if len(connecting_to) == 0:
            self.log.warning("There's no advertising tag to connect to!")
            return

        for tag in connecting_to:
            if tag.state in (TagState.CONNECTED, TagState.CONNECTING):
                self.log.warning("%s already to %s, request ignored.", tag.state, tag.ble_address)
                continue

            if not self.cmd_mode and not self.auto_override:
                self.auto_override = True

            if not self.max_conn_count_reached:
                self.connect(tag)
            else:
                self.log.warning("Maximum number of available connections reached, connecting to 'all' halted!")
                return

    def ap_disconnect(self, esl_id, bt_addr: str, group_id):
        """
        Disconnect from an ESL device with the specified address.
        Do Periodic Advertisement Sync Transfer during the procedure.
        input:
            - esl_id:   ESL ID
            - bt_addr:  Bluetooth address
            - group_id: ESL group ID
        """
        disconnect_from = []

        if esl_id is not None:
            if esl_id == "all":
                disconnect_from = [tag for tag in self.tag_db.list_state((TagState.CONNECTING, TagState.CONNECTED)) if (group_id is None or tag.group_id == group_id)]
                if not disconnect_from:
                    self.log.error("No connected tag present!")
            else:
                if group_id is None:
                    group_id = 0
                tag = self.tag_db.find((esl_id, group_id))
                if tag is None:
                    self.log.error("Can't disconnect from unknown tag: ESL ID: %u, Group ID: %u", esl_id, group_id)
                else:
                    disconnect_from.append(tag)
        elif bt_addr is not None:
            # Also checking CONNECTING state, because it is not possible to abort connection process.
            tag = self.tag_db.find(bt_addr)
            if tag is not None and tag.state != TagState.CONNECTED:
                tag = None
            if tag is None:
                self.log.error("Can't disconnect from address %s!", bt_addr)
            else:
                disconnect_from.append(tag)
        else:
            tag = self.get_active_tag()
            if tag is not None:
                disconnect_from.append(tag)

        if len(disconnect_from) == 0:
            if self.controller_command == CCMD_DISCONNECT:
                self.notify_controller(CCMD_DISCONNECT, CONTROLLER_COMMAND_FAIL)

        for tag in disconnect_from:
            if tag.provisioned:
                if tag.esl_id is not None:
                    self.ap_update_complete(tag.esl_id, tag.group_id)
                else:
                    self.past(tag)
            else:
                self.disconnect(tag)

    def ap_config(self, params: dict, bt_addr: str=None):
        """
        Configure the writable mandatory GATT characteristics of the ESL tag(s).
        input:
            - params:   Configuration parameter dictionary. For further details see
                        the parameters of config command.
        """
        ALL = 'all'
        tags_to_configure = []
        if bt_addr == ALL:
            tags_to_configure = self.tag_db.list_esl_state((EslState.UPDATING, EslState.CONFIGURING))
            if not tags_to_configure:
                self.log.error("No connected tag present!")
        else:
            tag = self.get_active_tag(bt_addr)
            if tag is None:
                if bt_addr is not None:
                    self.log.error("ESL at address: %s is not connected, nothing to configure.", bt_addr)
                return
            else:
                tags_to_configure.append(tag)

        for tag in tags_to_configure:
            values = {}
            esl_addr = None
            group_id = None
            # Check all first
            if "full" in params.keys():
                values = self.configure(tag)
                esl_addr = values[elw.ESL_LIB_DATA_TYPE_GATT_ESL_ADDRESS][0]
            for key, param in params.items():
                # ESL ID
                if key == "esl_addr" and bt_addr != ALL:
                    esl_addr = param
                    self.log.info("Set ESL ID to %d.", esl_addr & 0xff)
                    if group_id is None:
                        if tag.group_id is not None:
                            group_id = tag.group_id
                        else:
                            group_id = 0
                # Group
                elif key == "group_id":
                    group_id = param
                    self.log.info("Set group ID to %d.", group_id)
                    if esl_addr is None:
                        if tag.esl_id is not None:
                            esl_addr = tag.esl_id
                        else:
                            esl_addr = self.new_auto_address(tag.id)
                            self.log.warning("ESL group entered without a valid ESL ID - the ESL ID set to %d automatically to avoid ambiguous network configuration.", esl_addr & 0xff)
                # Sync Key
                elif key == "sync_key":
                    values[elw.ESL_LIB_DATA_TYPE_GATT_AP_SYNC_KEY] = self.ap_key
                # Response Key
                elif key == "response_key":
                    values[elw.ESL_LIB_DATA_TYPE_GATT_RESPONSE_KEY] = self.ead.generate_key_material()
                # Raw Absolute Time value
                elif key == "absolute_time":
                    absolute_time = param
                    values[elw.ESL_LIB_DATA_TYPE_GATT_CURRENT_TIME] = absolute_time.to_bytes(4, "little")
                # Time
                elif key == "time":
                    absolute_time = self.get_absolute_time()
                    values[elw.ESL_LIB_DATA_TYPE_GATT_CURRENT_TIME] = absolute_time.to_bytes(4, "little")

            if group_id is not None and esl_addr is not None:
                values[elw.ESL_LIB_DATA_TYPE_GATT_ESL_ADDRESS] = bytes([esl_addr & 0xff, group_id & 0x7f])
            if len(values):
                # Always use GATT Write With Response with manual config. IOP_TEST will randomly override if set.
                self.write_values(tag, values, True if not IOP_TEST else random.choice([True, False]))
            else:
                self.log.error("No characteristic to configure, request ignored!")

    def ap_imageupdate(self, image_index, file, raw=False, display_ind=None, label=None, rotation=None, cropfit=False, address=None, group_id=None):
        """
        Update tag image.
        inputs:
            - address:      Either Bluetooth address or ESL ID or 'all'
            - group_id:     ESL group ID
            - image_index:  Image index
            - filename:     Filename with path
            - raw:          Open and load file without conversion
            - display_ind   Display index
            - label         Label to be printed as an overlay to the image
            - rotation      Clockwise (cw), Counter-clockwise (ccw), flip
        """
         # If image file is from console, check validity
        if isinstance(file, str) and not self.controller_command:
            self.raw_image = b""
            try:
                image_file = open(file, "rb")
                self.raw_image = image_file.read()
                image_file.close()
            except FileNotFoundError:
                raise ImageUpdateFailed(f"Cannot open image file: {file}")

        tags_to_update = []
        tag = None
        if address is None: # if no address is given, then check if there's only one active connection
            tag = self.get_active_tag()
            if tag is None:
                return
        else:
            if not isinstance(address, esl_lib.Address): # Check for non-address datatype
                esl_id, gid = self.get_esl_address(address, group_id)
                if esl_id == BROADCAST_ADDRESS:
                    tags_to_update =  [tag for tag in self.tag_db.list_state(TagState.CONNECTED) if (group_id is None or tag.group_id == group_id)]
                    if len(tags_to_update) == 0:
                        self.log.error("No ESL from group %d seems to be connected, image upload failed. Please try another group.", gid)
                elif esl_id is None:
                    tag = self.tag_db.find(address)
                    if tag is None:
                        self.log.error("Tag at address %s not found in any group, command not sent", address)
                        return
                else:
                    tag = self.tag_db.find((esl_id, gid))
            else:
                tag = self.tag_db.find(address)

        if tag is not None:
            tags_to_update.append(tag)

        # If command is from AP remote controller (usually mobile running the demo application), send the notification
        if self.controller_command == CCMD_IMAGE_UPDATE:
            # This is the first request from the controller
            self.controller_image_index = image_index
            self.log.info("Image update command arrived from controller with the following parameters: index %s, filename %s", image_index, file)
            self.notify_controller(CCMD_REQUEST_DATA, CONTROLLER_COMMAND_SUCCESS, REQUEST_IMAGE_DATA_HEADER, self.image_data_offset, REQUEST_IMAGE_DATA_RESERVED)
            return

        for tag in tags_to_update:
            try:
                tag.image_update(image_index, file, raw, display_ind, label, rotation, cropfit)
                self.log.info("Image update started for tag at %s to image slot %d", tag.ble_address, image_index)
            except ImageUpdateFailed as ex:
                self.log.error("Image update failed for tag at %s to image slot %d", tag.ble_address, image_index)
                self.log.error(ex)
                continue
            except ImageTypeRequired:
                self.log.debug("Type info required for image %d on tag at %s - request readout", image_index, tag.ble_address)
                continue

    def ap_unassociate(self, address, group_id):
        """
        Unassociate tag from AP.
        inputs:
            - address:  Either Bluetooth address or ESL ID
            - group_id: ESL group ID
        """
        tlv = TLV_OPCODE_UNASSOCIATE
        esl_id, group_id = self.get_esl_address(address, group_id)
        data = bytearray(self.get_opcode_len(tlv))
        if esl_id is not None:
            data[0:2] = tlv, esl_id
            self.route_command(esl_id, group_id, data)
            if esl_id == BROADCAST_ADDRESS:
                synced_in_group = [tag for tag in self.tag_db.list_esl_state(EslState.SYNCHRONIZED) if tag.group_id == group_id]
                for tag in synced_in_group:
                    tag.block(elw.ESL_LIB_STATUS_UNASSOCITED) # blocking before remove_tag() call will preserve tag object in memory but still clears LTK!
                    if tag.state != TagState.CONNECTING:
                        self.remove_tag(tag=tag)
                if self.controller_command == CCMD_UNASSOCIATE:
                    self.notify_controller(CCMD_UNASSOCIATE, CONTROLLER_COMMAND_SUCCESS, esl_id)
            else:
                tag = self.tag_db.find((esl_id, group_id))
                if tag is not None and tag.esl_state not in [EslState.UNASSOCIATED, EslState.UNSYNCHRONIZED]:
                    tag.pending_unassociate = True # need to set explicitly for tags in synchronized state
        elif IOP_TEST and re.fullmatch(VALID_ESL_ID_NUMBER_REGEX, address) is not None:
            data[0:2] = tlv, int(address)
            self.queue_pawr_command(group_id, data)
            self.log.warning("Tag at address %s not found in group %d, send over PawR due IOP_TEST mode", address, group_id)
        else:
            try:
                bt_address = esl_lib.Address.from_str(address)
                if self.key_db.find_ltk(bt_address) is None:
                    raise esl_key_lib.Error(elw.SL_STATUS_NOT_FOUND)
                self.key_db.delete_ltk(bt_address)
                self.log.warning("Currently unconfigured tag at address %s removed from the bonding database", address)
            except (ValueError, esl_key_lib.Error):
                self.log.error("Tag at address %s not found in any group nor in bonding database, command ignored", address)
                if self.controller_command == CCMD_UNASSOCIATE:
                    self.notify_controller(CCMD_UNASSOCIATE, CONTROLLER_COMMAND_FAIL)

    def ap_list(self, param_list, verbose=False, group_id=None):
        """
        List tag information.
        """
        list_of_tags: list[Tag] = []
        for param in param_list:
            verbose_param = verbose
            # Advertising
            if param == "advertising":
                tags = self.tag_db.list_advertising()
                verbose_param = False
            # Synchronized
            elif param == "synchronized":
                tags = self.tag_db.list_esl_state(EslState.SYNCHRONIZED)
                list_of_tags += tags
            # Unsynchronized
            elif param == "unsynchronized":
                tags = self.tag_db.list_esl_state(EslState.UNSYNCHRONIZED)
            # Connected
            elif param == "connected":
                tags = self.tag_db.list_state((TagState.CONNECTED, TagState.CONNECTING))
            # Blocked
            elif param == "blocked":
                tags = self.tag_db.list_blocked()
                verbose_param = False
            # Invalid
            else:
                continue

            if group_id is not None:
                tags = [tag for tag in tags if tag.group_id == group_id]

            for tag in tags:
                if verbose_param:
                    log(tag.get_info())
                    log("-" * 36)
                else:
                    if tag.blocked and verbose:
                        log(str(tag) + f", blocked by {esl_lib.get_enum('ESL_LIB_STATUS_', tag.blocked)} on {dt.fromtimestamp(tag.last_req_timestamp).strftime('%d/%b %H:%M:%S.%f')[:-3]}")
                    else:
                        log(tag)
            if len(tags) == 0:
                log(f"There's no {param} tag" + (f" in group {group_id}" if group_id is not None else " at all."))
            elif len(tags) == 1:
                log(f"There's one {param} tag" + (f" in group {group_id}" if group_id is not None else " overall."))
            else:
                log(f"There are {len(tags)} {param} tags" + (f" in group {group_id}" if group_id is not None else " overall."))

        if self.controller_command == CCMD_LIST:
            if len(list_of_tags) != 0:
                for tag in list_of_tags:
                    self.notify_controller(CCMD_LIST, CONTROLLER_COMMAND_SUCCESS,
                                           CONTROLLER_REQUEST_MORE_DATA if tag is not list_of_tags[-1] else CONTROLLER_REQUEST_LAST_DATA,
                                           tag.esl_address,
                                           str(tag.ble_address),
                                           tag.max_image_index + 1 if tag.max_image_index is not None else 0,
                                           len(tag.display_info),
                                           struct.pack('<H', S_ID_PRESENT_INPUT_VOLTAGE) if S_ID_PRESENT_INPUT_VOLTAGE in tag.sensor_info else struct.pack('<H', 0x0000),
                                           struct.pack('<H', S_ID_PRESENT_DEVICE_OPERATING_TEMPERATURE) if S_ID_PRESENT_DEVICE_OPERATING_TEMPERATURE in tag.sensor_info else struct.pack('<H', 0x0000))
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
        esl_id, group_id = self.get_esl_address(address, group_id)

        if esl_id is None:
            self.log.error("Tag at address %s not found in any group, command not sent", address)
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
        esl_id, group_id = self.get_esl_address(address, group_id)

        if esl_id is None:
            self.log.error("Tag at address %s not found in any group, command not sent", address)
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
        esl_id, group_id = self.get_esl_address(address, group_id)
        if esl_id is not None:
            data = bytearray(self.get_opcode_len(tlv))
            tag = None
            data[0:2] = tlv, esl_id
            self.route_command(esl_id, group_id, data, force_pawr)
            esl_state = EslState.SYNCHRONIZED
            if esl_id != BROADCAST_ADDRESS:
                tag = self.tag_db.find((esl_id, group_id))
                esl_state = tag.esl_state
            if not force_pawr and tag is not None and esl_state in [EslState.CONFIGURING, EslState.UPDATING]:
                tag.block() # keep tag objects in memory
                self.remove_tag(tag=tag) # delete the bonding, only
                tag.unblock() # release blocking as it was only needed for bonding removal
            else:
                synced_in_group = [tag for tag in self.tag_db.list_esl_state(EslState.SYNCHRONIZED) if tag.group_id == group_id]
                if len(synced_in_group) > 0:
                    self.log.error("Factory reset command is invalid and thus ignored by tags in Synchronized state!")
        else:
            self.log.warning("Tag at address %s not found in any group, command not sent", address)

    def ap_update_complete(self, address, group_id):
        """
        Issue an Update Complete command to connected tag(s)
        inputs:
            - address:  Either Bluetooth address or ESL ID
            - group_id: ESL group ID
        """
        tag = None
        tlv = TLV_OPCODE_UPDATE_COMPLETE
        esl_id, gid = self.get_esl_address(address, group_id)

        if esl_id is not None:
            if esl_id != BROADCAST_ADDRESS:
                tag = self.tag_db.find((esl_id, gid))
                if tag.esl_state == EslState.SYNCHRONIZED:
                    self.log.warning("Update complete command is invalid in Synchronized state!")
        else:
            self.log.error("Tag at address %s not found in any group, command not sent", address)
            return

        # Check for connection
        if tag is not None and tag.state != TagState.CONNECTED:
            self.log.error("Update Complete can be used only with active connection!")
            if not IOP_TEST:
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
        esl_id, group_id = self.get_esl_address(address, group_id)

        if esl_id is None:
            self.log.error("Tag at address %s not found in any group, command not sent", address)
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
        esl_id, group_id = self.get_esl_address(address, group_id)

        if esl_id is None:
            self.log.error("Tag at address %s not found in any group, command not sent", address)
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
        esl_id, group_id = self.get_esl_address(address, group_id)

        if esl_id is None:
            self.log.error("Unknown address can be a valid ESL ID only, command ignored!")
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
        esl_id, group_id = self.get_esl_address(address, group_id)

        if esl_id is None:
            self.log.error("Unknown address can be a valid ESL ID only, command ignored!")
            return

        data_length = self.get_opcode_len(tlv)

        if vendor_data is not None:
            extra_len = len(vendor_data)
            data_length += extra_len
            tlv = self.set_tlv_len(tlv, extra_len)

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
        esl_id, group_id = self.get_esl_address(address, group_id)

        if esl_id is None:
            self.log.error("Tag at address %s not found in any group, command not sent", address)
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
        syncronized_tags = self.tag_db.list_esl_state(EslState.SYNCHRONIZED)
        if len(syncronized_tags):
            self.log.warning("There are already synchronized tags, they will lose sync!")

        if start is None:
            log(f"PAwR sync is currently{' ' if self.pawr_active else ' not '}running")
        elif not start:
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

    ##################### ESL methods #####################

    def new_auto_address(self, id):
        esl_id = id % ESL_MAX_TAGS_IN_AUTO_GROUP
        group_id = int(id // ESL_MAX_TAGS_IN_AUTO_GROUP)
        esl_address = (esl_id & BROADCAST_ADDRESS) | (group_id & 0x7f) << 8
        return esl_address

    def add_fake_tags(self, count):
        for _ in range(count):
            address = esl_lib.Address(bytes(random.choices(range(256), k=6)))
            tag = self.tag_db.add(self.lib, address)
            values = self.configure(tag)
            tag.gatt_values.update(values)

    def get_absolute_time(self):
        """ Get absolute time in milliseconds """
        delta_time = datetime.now() - self.start_time
        ms = delta_time / timedelta(microseconds=1000)
        return int(ms)

    def calculate_exec_time(self, now, d_hour, d_min, d_sec, d_micsec, date=None):
        """ Calculate command execution time delay in milliseconds """
        delay_ms = None
        delay_time = now
        delay_time = delay_time.replace(hour=d_hour, minute=d_min, second=d_sec, microsecond=d_micsec)
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
                        self.lib.pawr_set_data(self.pawr_handle, gid, len(commands), data)
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
        if not self.pawr_active:
            return

        # Remove outdated commands
        calculated_timeout = self.pa_timer_interval * AUX_SYNC_IND_PDU_MAX_SKIP_COUNT
        max_timeout = 164 # From BLE spec: the maximum permitted time between successful receives of periodic advertisement packages is 163.84 seconds.
        self.remove_outdated_commands(min(calculated_timeout, max_timeout))

        syncronized_tags = self.tag_db.list_esl_state(EslState.SYNCHRONIZED)
        response_timeout = (1.5 * self.pa_timer_interval) + (0.00125 * self.response_slot_delay)
        tnow = dt.now().timestamp()

        for tag in syncronized_tags:
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
                self.log.info("Set tag %s to Unsynchronized because of synchronization timeout", tag.ble_address)
                tag.unsynchronize()
                continue

            already_sent = []   # List of slots for resent tag commands
            # Resend unresponded commands
            if tag.group_id in self.esl_pending_commands:
                current_pending_commands = self.esl_pending_commands[tag.group_id]
                for cmd in current_pending_commands:
                    if cmd.esl_id == tag.esl_id and cmd.group_id == tag.group_id \
                        and ((tnow - cmd.timestamp) > response_timeout):
                        self.remove_esl_pending_command(cmd) # this will remove given command from self.esl_pending_commands
                        # Tag must be in IDLE state to send the command
                        if tag.state == TagState.IDLE and tag.unresp_command_number < ESL_CMD_MAX_RETRY_COUNT:
                            self.log.info("Resending command: (0x%s) to ESL %d in group %d", cmd.params.hex(), tag.esl_id, tag.group_id)
                            self.requeue_pawr_command(cmd.group_id, cmd.params) # and then re-queuing it to the bottom of the "FIFO"
                            if cmd.slot_number not in already_sent:
                                tag.unresp_command_number += 1
                                already_sent.append(cmd.slot_number)
                        elif tag.unresp_command_number >= ESL_CMD_MAX_RETRY_COUNT:
                            self.log.warning("Tag at address %s does not respond to synchronization packets, stop retrying", tag.ble_address)
                            tag.unresp_command_number = 0

        unsyncronized_tags = self.tag_db.list_esl_state(EslState.UNSYNCHRONIZED)
        for tag in unsyncronized_tags:
            tnow = dt.now().timestamp()
            _, resp_timestamp_diff = tag.timestamps_diff(tnow)
            # Check tag timeout
            if resp_timestamp_diff > TAG_UNASSOCIATE_TIMEOUT:
                self.log.info("Unassociate tag %s because of timeout in Unsynchronized state", tag.ble_address)
                tag.unassociate()

    def upload_next_image(self, tag: Tag):
        if tag is None:
            return
        tag.auto_image_count += 1
        if tag.auto_image_count < min((tag.max_image_index + 1), IMAGE_MAX_AUTO_UPLOAD_COUNT):
            self.log.info("Sending new image to ESL at address %s", tag.ble_address)
            self.upload_auto_image((tag.auto_image_count % len(self.image_files)), tag)
        elif tag.provisioned:
            disp_image = bytearray(self.get_opcode_len(TLV_OPCODE_DISPLAY_IMAGE))
            disp_image[0:4] = TLV_OPCODE_DISPLAY_IMAGE, tag.esl_id , 0, 0
            disp_image = bytes(disp_image)
            self.send_cp_command(tag, disp_image)
            self.log.info("Display Image command sent")

    def dequeue(self):
        """ Check and process event queue """
        while True:
            try:
                event = self.lib.event_queue.get(timeout=BLOCKING_WAIT_TIMEOUT)
            except queue.Empty:
                continue

            if isinstance(event, esl_lib.EventError):
                if event.lib_status not in [elw.ESL_LIB_STATUS_PAST_INIT_FAILED, elw.ESL_LIB_STATUS_PAWR_START_FAILED, elw.ESL_LIB_STATUS_PAWR_SET_DATA_FAILED]:
                    self.log.warning("[Event] " + str(event))
                elif event. sl_status == elw.SL_STATUS_TRANSMIT or (event.sl_status == elw.SL_STATUS_BT_CTRL_UNKNOWN_ADVERTISING_IDENTIFIER and self.pawr_active):
                    self.log.error("[Event] " + str(event))
            else:
                filter_events = [elw.ESL_LIB_EVT_PAWR_DATA_REQUEST, elw.ESL_LIB_EVT_TAG_FOUND]
                if not event.evt_code in filter_events:
                    self.log.debug("[Event] " + str(event))

            if hasattr(event, "node_id"):
                tag = self.tag_db.find(event.node_id)
            elif hasattr(event, "address"):
                tag = self.tag_db.find(event.address)
            elif hasattr(event, "connection_handle"):
                tag = self.tag_db.find(event.connection_handle)
            else:
                tag = None # prevent sending unsolicited / mismatching events to tag found in previous cylcle iteration!

            if tag is not None:
                tag.handle_event(event)

            try:
                enum_prefix = "ESL_LIB_EVT_"
                event_name = esl_lib.get_enum(enum_prefix, event.evt_code)[len(enum_prefix):].lower()
                for prefix in self.event_handler_prefix_list:
                    event_handler_method = prefix + "esl_event_" + event_name
                    if hasattr(self, event_handler_method):
                        getattr(self, event_handler_method)(event)
            except Exception as err:
                log(err)
                log(traceback.format_exc())
                self.shutdown_cli()

    # ----------------------------------------------------------------------------------------------
    # Common ESL event handler methods for all modes (auto/command line/demo)

    def esl_event_system_boot(self, evt: esl_lib.EventSystemBoot):
        """ ESL event handler """
        self.scan_runs = False
        self.pawr_active = False
        self.pawr_handle = None
        self.pawr_restart = None
        self.shutdown_timer.cancel()
        self.max_conn_count_reached = False
        self.bonding_finished = True
        for tag in self.tag_db.all():
            if tag.state == TagState.CONNECTING or tag.esl_state == EslState.CONFIGURING:
                self.key_db.delete_ltk(tag.ble_address)
            tag.reset()

    def esl_event_tag_found(self, evt: esl_lib.EventTagFound):
        """ ESL event handler """
        if evt.rssi > self.rssi_threshold:
            tag = self.tag_db.find(evt.address)
            if tag is None:
                tag = self.tag_db.add(self.lib, evt.address)
            tag.handle_event(evt)

    def esl_event_connection_opened(self, evt: esl_lib.EventConnectionOpened):
        """ ESL event handler """
        tag = self.tag_db.find(evt.address)
        if tag.provisioned:
            cmd = self.get_latest_command(tag)
            if cmd is not None:
                self.log.debug("Unresponded command removed from PAwR queue!")
                self.remove_esl_pending_command(cmd)

    def esl_event_bonding_finished(self, evt: esl_lib.EventBondingData):
        """ ESL event handler """
        self.bonding_finished = True

    def esl_event_tag_info(self, evt: esl_lib.EventTagInfo):
        """ ESL event handler """
        pass

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
            for tag in self.tag_db.list_advertising():
                tag.reset_advertising()

    def esl_event_configure_tag_response(self, evt: esl_lib.EventConfigureTagResponse):
        """ ESL event handler """
        if evt.status == elw.SL_STATUS_OK:
            tag = self.tag_db.find(evt.connection_handle)
            if tag.provisioned:
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
        tag = self.tag_db.find(evt.connection_handle)
        if evt.data_sent[0] == TLV_OPCODE_UPDATE_COMPLETE and evt.data_sent[1] == tag.esl_id:
            self.past(tag)

    def esl_event_image_transfer_finished(self, evt: esl_lib.EventImageTransferFinished):
        """ ESL event handler """
        if self.controller_command == CCMD_REQUEST_DATA:
            self.notify_controller(CCMD_IMAGE_UPDATE, CONTROLLER_COMMAND_SUCCESS)

    def esl_event_connection_closed(self, evt: esl_lib.EventConnectionClosed):
        """ ESL event handler """
        self.max_conn_count_reached = False
        tag = self.tag_db.find(evt.address) # Can return None after unassociate command written successfully to ESL Control Point if connected tag
        if tag is not None:
            if not tag.provisioned or (evt.reason == elw.SL_STATUS_BT_CTRL_REMOTE_USER_TERMINATED and tag.pending_unassociate):
                # delete stored LTK for tags that didn't finish provisioning before the connection closed according to ESL Profile spec. 
                # or if there's a pending unassociate executed succesfully
                self.key_db.delete_ltk(tag.ble_address)
                tag.reset()
            if logLevel() <= LEVELS['DEBUG'] and tag.associated:
                log("Tag info about disconnected device:", _half_indent_log=True)
                log(tag.get_info())

    def esl_event_control_point_notification(self, evt: esl_lib.EventControlPointNotification):
        """ ESL event handler """
        # after an unassociate all command sent the evt.address will not be part of the list of tags!
        tag = self.tag_db.find(evt.connection_handle)
        if tag is None:
            return
        ResponseParser(evt.data, tag.sensor_info)
        if evt.data[0] == TLV_RESPONSE_BASIC_STATE and tag.pending_unassociate:
            tag.block(elw.ESL_LIB_STATUS_UNASSOCITED) # blocking before remove_tag() call will preserve tag object in memory but still clears LTK!
            self.remove_tag(tag=tag)
        if self.controller_command != None:
            self.notify_controller(self.controller_command, CONTROLLER_COMMAND_SUCCESS, tag.esl_id, tag.group_id, evt.data)

    def esl_event_pawr_response(self, evt: esl_lib.EventPawrResponse):
        """ ESL event handler """
        tag = self.identify_sender_tag(evt.response_slot, evt.subevent)
        if tag is not None:
            response = self.ead.decrypt(evt.data, KeyMaterial(tag.response_key))
            if len(response):
                self.handle_pawr_response(response, evt.response_slot, evt.subevent)
            else:
                pass # decryption error occurred
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
                tag = self.tag_db.find(evt.node_id)
                self.bonding_finished = True
                if tag is not None:
                    self.key_db.delete_ltk(tag.ble_address)
        elif evt.lib_status == elw.ESL_LIB_STATUS_CONN_FAILED:
            self.bonding_finished = True
            if evt.sl_status == elw.SL_STATUS_ABORT or evt.sl_status == elw.SL_STATUS_BT_CTRL_AUTHENTICATION_FAILURE: # handle advertisers that refuse connection retry attempts - e.g. because bonded to other AP
                tag = self.tag_db.find(evt.node_id)
                if tag is not None and not tag.blocked and not tag.provisioned:
                    self.log.warning("ESL at address %s has been blocked due to unsuccessful connection attempt(s).", evt.node_id)
                    tag.block(elw.ESL_LIB_STATUS_BONDING_FAILED)
            elif evt.sl_status in [elw.SL_STATUS_NO_MORE_RESOURCE, elw.SL_STATUS_BT_CTRL_CONNECTION_LIMIT_EXCEEDED] and not self.max_conn_count_reached:
                self.max_conn_count_reached = True
                self.log.warning("Access point connection limit reached - suspend connect requests until a connection is closed.")
        elif evt.lib_status == elw.ESL_LIB_STATUS_CONN_TIMEOUT:
            self.bonding_finished = True
            tag = self.tag_db.find(evt.node_id)
            if tag is not None and not tag.associated and not tag.blocked and evt.data == elw.ESL_LIB_CONNECTION_STATE_CONNECTING:
                self.remove_tag(tag=tag) # keeps the tag database safe from orphaned objects which have shown no sign of existing
        elif evt.lib_status == elw.ESL_LIB_STATUS_GATT_TIMEOUT:
            tag = self.tag_db.find(evt.node_id)
            if tag is not None:
                if not tag.provisioned:
                    self.key_db.delete_ltk(tag.ble_address)
                self.log.error("GATT Timeout for address %s", tag.ble_address)
        elif evt.lib_status == elw.ESL_LIB_STATUS_OTS_GOTO_FAILED:
            tag = self.tag_db.find(evt.node_id)
            if tag is not None:
                if evt.sl_status == elw.SL_STATUS_NOT_FOUND:
                    self.log.error("No object found with the requested Object ID for address %s", tag.ble_address)
        elif evt.lib_status == elw.ESL_LIB_STATUS_PAWR_START_FAILED:
            self.pawr_active = False
        elif evt.lib_status == elw.ESL_LIB_STATUS_PAST_INIT_FAILED:
            if evt.sl_status == elw.SL_STATUS_BT_CTRL_COMMAND_DISALLOWED:
                self.log.info("PAST skipped by ESL already in Synchronized state.")
        elif evt.lib_status == elw.ESL_LIB_STATUS_CONN_CLOSE_FAILED:
            self.bonding_finished = True
            if evt.sl_status == elw.SL_STATUS_TIMEOUT and evt.data == elw.ESL_LIB_CONNECTION_STATE_PAST_CLOSE_CONNECTION:
                tag = self.tag_db.find(evt.node_id)
                if tag is not None and tag.provisioned and not tag.advertising:
                    self.log.debug("Check if Tag at address %s got synchronized despite the connection closing timeout.", tag.ble_address)
                    self.ap_ping(tag.esl_id, tag.group_id) # Special edge case in which the synced flag may not be set after disconnection -> check if tag is synced

    def esl_event_image_type(self, evt: esl_lib.EventImageType):
        """ ESL event handler """
        # Cache image type
        tag = self.tag_db.find(evt.connection_handle)
        self.ap_imageupdate(evt.img_index, tag.image_file, address = tag.ble_address, label=tag.label, rotation=tag.rotation)

    def esl_event_bonding_data(self, evt: esl_lib.EventBondingData):
        """ ESL event handler """
        # export new LTK
        self.key_db.add_ltk(evt.address, evt.ltk)

    # ----------------------------------------------------------------------------------------------
    # ESL event handler method extensions in CLI mode

    def cli_esl_event_error(self, evt: esl_lib.EventError):
        """ ESL event handler in CLI mode """
        if evt.lib_status in [elw.ESL_LIB_STATUS_CONN_FAILED, elw.ESL_LIB_STATUS_CONN_CLOSE_FAILED, elw.ESL_LIB_STATUS_CONN_TIMEOUT]:
            if evt.lib_status == elw.ESL_LIB_STATUS_CONN_FAILED:
                if evt.sl_status == elw.SL_STATUS_BT_CTRL_AUTHENTICATION_FAILURE: # handle advertisers bonded to different AP
                    self.log.info("ESL at address %s refused connection attempts - seemingly bonded to other AP", evt.node_id)
            elif evt.lib_status == elw.ESL_LIB_STATUS_CONN_TIMEOUT:
                self.log.error("Timeout occured on connection attempt to address %s", evt.node_id)
            self.revert_auto_mode()

    def cli_esl_event_system_boot(self, evt: esl_lib.EventSystemBoot):
        """ ESL event handler in CLI mode """
        self.log.info("Command line event handler started, system is idle.")
        self.log.info("Type 'help' for available commands.")

    def cli_esl_event_tag_found(self, evt: esl_lib.EventTagFound):
        """ ESL event handler in CLI mode """
        tag = self.tag_db.find(evt.address)
        if tag is None:
            return # Happens until the RSSI threshold is met
        if not self.pawr_active and not tag.advertising and not tag.state == TagState.CONNECTING:
            self.log.warning("ESL tag can't be synchronized because PAwR is not running.")
            self.log.info("Don't forget to start PAwR with 'sync start' before completing configuration!")

    def cli_esl_event_connection_closed(self, evt: esl_lib.EventConnectionClosed):
        """ ESL event handler in CLI mode """
        self.revert_auto_mode()

    # ----------------------------------------------------------------------------------------------
    # ESL event handler method extensions in auto mode

    def auto_esl_event_system_boot(self, evt: esl_lib.EventSystemBoot):
        """ ESL event handler in auto mode """
        self.start_scan()
        self.start_pawr_train()

    def auto_esl_event_tag_found(self, evt: esl_lib.EventTagFound):
        """ ESL event handler in auto mode """
        tag = self.tag_db.find(evt.address)
        if tag is not None and tag.state == TagState.IDLE:
            if tag.advertising:
                if self.pawr_active and not tag.blocked:
                    self.check_address_list()
            elif not self.pawr_active:
                self.log.error("ESL tag cannot be synchronized because PAwR is not started!")
                self.log.info("Please re-start auto mode with command: 'mode auto' to recover.")

    def auto_esl_event_error(self, evt: esl_lib.EventError):
        """ ESL event handler in auto mode """
        tag = self.tag_db.find(evt.node_id)
        if evt.lib_status in [elw.ESL_LIB_STATUS_OTS_ERROR, elw.ESL_LIB_STATUS_OTS_TRANSFER_FAILED, elw.ESL_LIB_STATUS_OTS_GOTO_FAILED, elw.ESL_LIB_STATUS_OTS_UNEXPECTED_OFFSET, elw.ESL_LIB_STATUS_OTS_WRITE_RESP_FAILED]:
            if evt.sl_status != elw.SL_STATUS_TIMEOUT:
                try:
                    self.upload_next_image(tag)
                    return
                except:
                    pass
                if not self.max_conn_count_reached:
                    self.check_address_list()
        elif evt.lib_status == elw.ESL_LIB_STATUS_OTS_GOTO_FAILED:
            if evt.sl_status == elw.SL_STATUS_NOT_FOUND:
                self.upload_next_image(tag)
        elif evt.lib_status == elw.ESL_LIB_STATUS_BONDING_FAILED:
            if tag is not None: # Tag may have been already deleted in the edge case where connection timeout of an unprovisined tag precedes bonding fail error
                tag.block(evt.lib_status)
        elif evt.lib_status in [elw.ESL_LIB_STATUS_CONN_FAILED, elw.ESL_LIB_STATUS_CONN_CLOSE_FAILED, elw.ESL_LIB_STATUS_CONN_TIMEOUT]:
            self.auto_override = False
            self.set_mode_handlers()
            if evt.sl_status not in [elw.SL_STATUS_NO_MORE_RESOURCE, elw.SL_STATUS_BT_CTRL_CONNECTION_LIMIT_EXCEEDED]:
                self.check_address_list()

    def auto_esl_event_connection_opened(self, evt: esl_lib.EventConnectionOpened):
        """ ESL event handler in auto mode """
        tag = self.tag_db.find(evt.address)
        if tag is not None and not tag.associated:
            self.auto_configured_tags_in_single_run += 1

        if self.auto_override:
            self.log.warning("AUTO MODE TEMPORARILY CHANGED TO MANUAL!")
            self.cmd_mode = self.auto_override
            self.set_mode_handlers()
        elif tag is not None and tag.provisioned: # we remain in auto mode, so aviod stuck connected in special case below
            if tag.max_image_index is not None and tag.has_image_transfer and IMAGE_MAX_AUTO_UPLOAD_COUNT and tag.auto_image_count < min((tag.max_image_index + 1), IMAGE_MAX_AUTO_UPLOAD_COUNT):
                self.upload_auto_image((tag.auto_image_count % len(self.image_files)), tag)
            else:
                self.ap_update_complete(tag.esl_id, tag.group_id)

    def auto_esl_event_tag_info(self, evt: esl_lib.EventTagInfo):
        """ ESL event handler in auto mode """
        if not self.auto_override:
            tag = self.tag_db.find(evt.connection_handle)
            if not tag.associated: # auto-refreshing of an existing tag config may happened already within the tag event handling
                values = self.configure(tag)
                self.write_values(tag, values)

    def auto_esl_event_control_point_response(self, evt: esl_lib.EventControlPointResponse):
        """ ESL event handler in auto mode """
        if evt.status == elw.SL_STATUS_OK:
            tag = self.tag_db.find(evt.connection_handle)
            if evt.data_sent[1] == tag.esl_id and not evt.data_sent[0] == TLV_OPCODE_UPDATE_COMPLETE:
                self.ap_update_complete(tag.esl_id, tag.group_id)

    def auto_esl_event_configure_tag_response(self, evt: esl_lib.EventConfigureTagResponse):
        """ ESL event handler in auto mode """
        if evt.status == elw.SL_STATUS_OK:
            tag = self.tag_db.find(evt.connection_handle)
            if tag.provisioned:
                if tag.max_image_index is not None and tag.has_image_transfer and IMAGE_MAX_AUTO_UPLOAD_COUNT and tag.auto_image_count < min((tag.max_image_index + 1), IMAGE_MAX_AUTO_UPLOAD_COUNT):
                    self.upload_auto_image((tag.auto_image_count % len(self.image_files)), tag)
                else:
                    self.ap_update_complete(tag.esl_id, tag.group_id)

    def auto_esl_event_image_transfer_finished(self, evt: esl_lib.EventImageTransferFinished):
        """ ESL event handler in auto mode """
        self.upload_next_image(self.tag_db.find(evt.connection_handle))

    def auto_esl_event_connection_closed(self, evt: esl_lib.EventConnectionClosed):
        """ ESL event handler in auto mode """
        if self.auto_override:
            self.cmd_mode = False
            self.auto_override = False
        self.check_address_list()

    def auto_esl_event_bonding_finished(self, evt: esl_lib.EventBondingData):
        """ ESL event handler in auto mode """
        if not self.max_conn_count_reached:
            self.check_address_list()

    # ----------------------------------------------------------------------------------------------
    # ESL event handler method extensions in demo mode

    def demo_esl_event_system_boot(self, evt: esl_lib.EventSystemBoot):
        """ ESL event handler in demo mode """
        # Enable advertising
        self.lib.general_command(CMD_AP_CONTROL_ADV_ENABLE, b'\x01')
        self.start_scan()
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
            self.ap_imageupdate(self.controller_image_index, self.image_from_controller)
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
        tag = self.tag_db.find(evt.address)
        if self.pawr_active and tag is not None and tag.esl_state == EslState.UNSYNCHRONIZED and tag.state == TagState.IDLE:
            self.connect(tag)
            self.demo_auto_reconfigure = True

    def demo_esl_event_configure_tag_response(self, evt: esl_lib.EventConfigureTagResponse):
        """ ESL demo event handler """
        if evt.status == elw.SL_STATUS_OK:
            tag = self.tag_db.find(evt.connection_handle)
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
            tag = self.tag_db.find(evt.node_id)
            self.disconnect(tag)

    # ----------------------------------------------------------------------------------------------
    # AP Class methods

    def revert_auto_mode(self):
        if self.auto_override and len(self.tag_db.list_state((TagState.CONNECTED, TagState.CONNECTING))) == 0:
            self.cmd_mode = False
            self.auto_override = False
            self.log.warning("REVERT TO AUTO MODE!")
            self.set_mode_handlers()

    def check_address_list(self):
        """ Check address list """
        if self.pawr_active and self.bonding_finished and len(self.tag_db.list_state(TagState.CONNECTING)) < ESL_CMD_MAX_PENDING_CONNECTION_REQUEST_COUNT:
            self.log.info("Checking for next advertising ESL")
            # Advertising IDLE state tags those are not blocked
            tag_list = [tag for tag in self.tag_db.list_state(TagState.IDLE) if not tag.blocked and tag.advertising]
            if len(tag_list) > 0:
                tag = tag_list[0]
                if not self.max_conn_count_reached:
                    self.bonding_finished = False
                    self.connect(tag)
                    if self.auto_config_start_time is None:
                        self.auto_config_start_time = dt.now()
                else:
                    self.log.info("Access point connection limit reached - auto provisioning suspended!")
            else:
                if len(self.tag_db.list_state((TagState.CONNECTING, TagState.CONNECTED))) == 0:
                    if not self.scan_runs:
                        self.log.error("Scanning is disabled, auto commissioning stopped until scanning is enabled!")
                    else:
                        self.log.warning("No advertising ESL found within RSSI threshold of %d dBm, auto commissioning suspended until further detection!", self.rssi_threshold)
                    log("Auto mode summary:", _half_indent_log=True)
                    time = None
                    try:
                        time = dt.now() - self.auto_config_start_time # self.auto_config_start_time can be None in an edge case
                        time_per_tag = time.total_seconds() / self.auto_configured_tags_in_single_run
                        log(f"Last auto config session for {self.auto_configured_tags_in_single_run} "   \
                            f"{'tags' if self.auto_configured_tags_in_single_run > 1 else 'tag'} took "  \
                            f"a total time of {str(time)[:-3]}, which is {time_per_tag:.3f} seconds per ESL.")
                    except:
                        # since self.auto_configured_tags_in_single_run will always count brand new configurations, only: it can be zero, resulting in div by 0 exception
                        if time is not None: # if self.auto_config_start_time was not None, then time must be valid, at least
                            log(f"Last auto re-config session took a total time of {str(time.total_seconds())[:-3]}.") # in this case we don't know how many tags has been re-configured
                    self.auto_config_start_time = None
                    self.auto_configured_tags_in_single_run = 0
                    self.ap_list(["synchronized","unsynchronized","blocked"])
                if not self.scan_runs and not self.cmd_mode:
                    self.log.warning("Scanning is disabled in auto mode - please consider enabling it by issuing 'scan start' command!")
                return
            # Gather some useful stats until there are tags advertising
            tag_list = self.tag_db.all()
            synced_count = len(self.tag_db.list_esl_state(EslState.SYNCHRONIZED))
            connected_count = len(self.tag_db.list_state(TagState.CONNECTED))
            connecting_count = len(self.tag_db.list_state(TagState.CONNECTING))
            blocked_count = len([tag for tag in tag_list if tag.blocked])
            total_count = len(tag_list)
            self.log.info("Multiconnection stats - TOTAL: %d, CONNECTING: %d, CONNECTED: %d, SYNCED: %d, BLOCKED: %d", total_count, connecting_count, connected_count, synced_count, blocked_count)

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
        self.pa_timer_interval = adv_interval_max / 800.0 # don't forget: the natural units of adv_interval values are 1.25[ms]!

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
            try:
                self.lib.pawr_enable(self.pawr_handle, False)
            except Exception as e:
                self.log.error(e)
        else:
            self.log.info("PAwR train is not running.")

    def update_pending_commands_list(self, gid, cmds):
        """ Update unresponded command list """
        last_slotnum = {}
        previous_pending = []
        # Get ESL response slot numbers
        for i in range(len(cmds)):
            esl_id = cmds[i][1]
            if esl_id != BROADCAST_ADDRESS:
                last_slotnum[esl_id] = i

        self.esl_pending_commands_lock.acquire()
        if gid in self.esl_pending_commands:
            previous_pending = self.esl_pending_commands[gid]
        self.esl_pending_commands[gid] = []

        for i in range(len(cmds)):
            esl_id = cmds[i][1]
            # Broadcast address does not need response
            if esl_id != BROADCAST_ADDRESS:
                new_command = ESLCommand(cmds[i], gid, last_slotnum[esl_id])
                if new_command.response_opcode is not None:
                    self.esl_pending_commands[gid].append(new_command)
        self.esl_pending_commands[gid].extend(previous_pending)
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
                    pop_list.append(self.esl_pending_commands[key].index(item))
                    tag = self.tag_db.find((cmd.esl_id, cmd.group_id))
                    if tag is not None:
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
            try:
                self.esl_pending_commands[gid].remove(cmd)
            except ValueError:
                # nothing to delete, pass silently
                pass

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
            for tag in self.tag_db.list_advertising():
                tag.reset_advertising()
            for tag in self.tag_db.list_blocked():
                tag.unblock()
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
        else:
            self.log.info("Scanning is not running.")

    def configure(self, tag: Tag):
        """ Configure tag
        parameters:
            tag: ESL tag to configure """

        if tag.esl_address is None:
            esl_address = self.new_auto_address(tag.id)
            self.log.info("New auto ESL Address: 0x%04x", esl_address)
        else:
            esl_address = tag.esl_address
            self.log.info("Reuse ESL Address: 0x%04x", esl_address)

        absolute_time = self.get_absolute_time()

        values = {
            elw.ESL_LIB_DATA_TYPE_GATT_ESL_ADDRESS: esl_address.to_bytes(2, "little"),
            elw.ESL_LIB_DATA_TYPE_GATT_RESPONSE_KEY: self.ead.generate_key_material(),
            elw.ESL_LIB_DATA_TYPE_GATT_AP_SYNC_KEY: self.ap_key,
            elw.ESL_LIB_DATA_TYPE_GATT_CURRENT_TIME: absolute_time.to_bytes(4, "little")
        }
        return values

    def connect(self, tag: Tag):
        """ Establish connection with a tag normally or via PAwR"""
        # group ID shouldn't be None if the tag is in sychronized state, but better to doublecheck
        if tag.esl_state == EslState.SYNCHRONIZED and tag.group_id is not None:
            pawr = esl_lib.PAWRSubevent(self.pawr_handle, tag.group_id)
        else:
            pawr = None
        ltk = self.key_db.find_ltk(tag.ble_address)
        if ltk is not None:
            key_type = elw.ESL_LIB_KEY_TYPE_LTK
            self.log.info("Bonding LTK found for ESL at %s", tag.ble_address)
        else:
            key_type = elw.ESL_LIB_KEY_TYPE_NO_KEY
        self.log.info("Request connecting to: %s %s", tag.ble_address, "over PAwR" if pawr else "via connectable advertisement")
        try:
            tag.connect(pawr, key_type=key_type, key=ltk)
        except Exception as e:
            self.log.error(e)

    def disconnect(self, tag: Tag):
        """ Close connection with a tag """
        try:
            tag.close_connection()
        except esl_lib.CommandFailedError as err:
            self.log.warning("Failed to disconnect from %s: %s", tag.ble_address, err)

    def past(self, tag: Tag):
        """ Do Periodic Advertisement Sync Transfer over connection """
        if tag.past_initiated:
            return
        elif not self.pawr_active:
            if self.cmd_mode:
                self.log.warning("PAwR is not running, tag won't be synchronized!")
            else:
                self.log.error("PAwR is not running, auto provisioning will stop until PAwR train is started by 'sync start' command!")
            tag.close_connection()
            return
        tag.initiate_past(self.pawr_handle, self.pa_timer_interval)

    def write_values(self, tag: Tag, values: dict, att_response=True):
        """ Write values """
        tag.configure_tag(values, att_response)

    def upload_auto_image(self, image_index, tag:Tag):
        """ Automatic image update helper """
        image_path = self.image_path + random.choice(random.sample(self.image_files, len(self.image_files)))
        self.ap_imageupdate(image_index, image_path, address=tag.ble_address)

    def shutdown(self):
        """ Initiate shutdown """
        try:
            self.lib.stop()
        except esl_lib.CommandFailedError:
            self.log.warning("Clean shutdown failed")

    def shutdown_timeout(self):
        """ Shutdown on ESL AP NCP init timeout """
        self.log.critical("ESL AP NCP initialization timeout, no response received! Shutdown.")
        self.shutdown_cli()

    def shutdown_cli(self):
        """ Propagate shutdown towards the CLI """
        if self.cli_queue is not None:
            self.cli_queue.put("exit")

    def get_active_tag(self, bt_addr: str=None, state=TagState.CONNECTED):
        """ CLI helper to get 1 connected tag if bt_addr is omitted """
        tag = None
        if bt_addr is not None:
            if re.fullmatch(VALID_BD_ADDRESS_REGEX, str(bt_addr)) is not None:
                tag = self.tag_db.find(bt_addr)
                if tag is None:
                    self.log.error("Unknown tag address: %s", bt_addr)
            else:
                self.log.error("Invalid tag address: %s", bt_addr)
        else:
            tags = self.tag_db.list_state(state)
            if len(tags) == 0:
                self.log.error("No connected tag present!")
            elif len(tags) == 1:
                tag = tags[0]
            else:
                address_list = ", ".join([str(t.ble_address) for t in tags])
                self.log.warning("%u connected tags present, select one: %s!", len(tags), address_list)
        return tag

    def remove_tag(self, esl_id=None, group_id=None, tag: Tag= None):
        """ Remove tag from lists """
        tags_to_remove = []
        if tag is not None:
            tags_to_remove.append(tag)
        elif esl_id is not None:
            node_id = esl_id, group_id
            if esl_id == BROADCAST_ADDRESS:
                tags_to_remove = self.tag_db.list_group(group_id)
            else:
                tag = self.tag_db.find(node_id)
                tags_to_remove.append(tag)
        if len(tags_to_remove) == 0:
            self.log.error("Unable to remove tag: no matching tag found")
            return
        for tag in tags_to_remove:
            if not tag.blocked: # keep tags with blocked status - manual connection can override blocking, later!
                self.log.info("Tag removed at address %s", tag.ble_address)
                self.tag_db.remove(tag)
            else:
                self.log.info("Delete bonding for blocked tag at address %s", tag.ble_address)
            self.key_db.delete_ltk(tag.ble_address)
            tag.unassociate()


    def get_esl_address(self, addr, group_id):
        """ Return ESL ID from either BT address or ESL ID string - can return with BROADCAST_ADDRESS value (0xFF)! """
        tag = None
        esl_id = None
        if group_id is None:
            group_id = 0 # defaulting group 0 if none is given
        if addr == "all" or addr == BROADCAST_ADDRESS:
            esl_id = BROADCAST_ADDRESS # convert user friendly keyword to broadcast address
            if len(self.tag_db.list_group(group_id)):
                self.log.warning("All tags in group %d will be addressed!", group_id)
            else:
                self.log.warning("Group %d is empty, the command will have no effect!", group_id)
        elif re.fullmatch(VALID_BD_ADDRESS_REGEX, str(addr)) is not None:
            tag = self.tag_db.find(addr)
        elif addr is not None:
            try:
                esl_id = int(addr)
            except TypeError:
                self.log.error("%d is not a valid address, request ignored!", str(addr))
            else:
                tag = self.tag_db.find((esl_id, group_id))

        if tag is None:
            if esl_id is not None:
                if esl_id != BROADCAST_ADDRESS:
                    self.log.warning("Tag address unknown: %s in group %d", addr, group_id)
            else:
                self.log.warning("Tag address unknown: %s", addr)
            if self.controller_command != None:
                self.notify_controller(self.controller_command, CONTROLLER_COMMAND_FAIL)
        else:
            esl_id = tag.esl_id
            group_id = tag.group_id
        return esl_id, group_id

    def route_command(self, esl_id, group_id, data, force_pawr=False):
        """ Auto route commands between periodic advertisement (with responses) and ESL Control Point """
        if esl_id == BROADCAST_ADDRESS:
            connected_in_group = [tag for tag in self.tag_db.list_state((TagState.CONNECTED,TagState.CONNECTING)) if (group_id is None or tag.group_id == group_id)]
            control_point_data = data.copy()
            # Handle the connected ESL tag(s) within the given group explicitly, if any
            for tag in connected_in_group:
                # broadcast addresses are otherwise routed over periodic advertisement, always!
                if not IOP_TEST: # following line could break future IOP BI test cases that require writing 0xFF ESL ID to ESL CP!
                    control_point_data[1] = tag.esl_id # ESL Service Spec v1.0 3.9.2 Command behavior, paragraph 3: broadcast address would be rejected by INVALID_PARAMETER error.
                self.send_cp_command(tag, control_point_data)
                if control_point_data[0] == TLV_OPCODE_UNASSOCIATE:
                    self.log.warning("Unassociate connected ESL tag at %s results in immediate disconnection!", tag.ble_address)
                elif control_point_data[0] == TLV_OPCODE_FACTORY_RST:
                    self.log.warning("Factory reset of ESL tag at %s results in immediate disconnection!", tag.ble_address)

        tag = self.tag_db.find((esl_id, group_id))
        if tag is not None:
            # check for different dispatch path override cases
            if force_pawr:
                self.log.warning("Override command dispatch path: send via PAwR")
                tag = None
            elif tag.state != TagState.CONNECTED:
                # tag exists but is currently not connected then send via PAwR by default
                if data[0] == TLV_OPCODE_PING:
                    tag.update_request_timestamp()
                tag = None
        elif IOP_TEST:
            # force sending commands with unknown ESL ID or PING to ALL (IOP test-only command!) to ESL CP
            active_tag = self.get_active_tag()
            if active_tag is not None and len(active_tag) == 1 and active_tag.group_id == group_id \
                    and (esl_id != BROADCAST_ADDRESS or (data[0] == TLV_OPCODE_PING)):
                self.log.warning("Sending a deliberately misaddressed command to the current ESL Control Point")
                tag = active_tag

        if tag is None:
            self.queue_pawr_command(group_id, data)
        else:
            self.send_cp_command(tag, data)

    def send_cp_command(self, tag: Tag, data: bytes):
        """ Writes a command to the control point """
        try:
            tag.write_control_point(data, att_response=not IOP_TEST)
        except InvalidTagStateError:
            self.log.error("ESL ID %d in group %d is not connected, Control Point can't be written!", tag.esl_id, tag.group_id)

    def led_control_command(self, esl_id, group_id, repeat_field, led_idx,
                                absolute_value, gamut=0, pattern=None):
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
        if subevent in self.esl_pending_commands:
            for cmd in self.esl_pending_commands[subevent]:
                # Response is in expected slot and subevent
                if cmd.slot_number == response_slot and cmd.group_id == subevent:
                    tag = self.tag_db.find((cmd.esl_id, cmd.group_id))
                    if tag is not None:
                        self.log.info("Reply in slot %d from ESL ID %d in group %d.", response_slot, tag.esl_id, tag.group_id)
                    else:
                        self.log.warning("Unable to identify sender tag ID %d in group %d", cmd.esl_id, cmd.group_id)
                    return tag
        return None

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
        tag = None
        while data_index < len(data):
            data_size = self.get_opcode_len(data[data_index])
            last_data = data_index + data_size
            response_data = data[data_index:last_data]

            if subevent in self.esl_pending_commands:
                for cmd in self.esl_pending_commands[subevent]:
                    # Response is in expected slot and subevent
                    if cmd.slot_number == response_slot and cmd.group_id == subevent:
                        tag = self.tag_db.find((cmd.esl_id, cmd.group_id))
                        # Response belongs to known address and not already processed
                        if tag is not None and self.esl_pending_commands[subevent].index(cmd) not in pop_list:
                            # Accept responses only that allowed by the spec.
                            if cmd.opcode_valid(response_data[0]):
                                tag.handle_response(response_data)
                                # Get sensor info
                                sensor_info = tag.sensor_info
                                tag.update_response_timestamp(dt.now().timestamp())
                                if response_data[0] == TLV_RESPONSE_BASIC_STATE and tag.pending_unassociate:
                                    tag.block(elw.ESL_LIB_STATUS_UNASSOCITED) # blocking before remove_tag() call will preserve tag object in memory but still clears LTK!
                                    self.remove_tag(tag=tag)
                                # Resend retry error responses
                                if response_data[0] == TLV_RESPONSE_ERROR:
                                    if response_data[1] == ERROR_RESPONSE_RETRY or response_data[1] == ERROR_RESPONSE_CAPACITY_LIMIT:
                                        self.log.info("Resending command: (0x%s) to ESL %d in group %d", cmd.params.hex(), tag.esl_id, tag.group_id)
                                        self.queue_pawr_command(cmd.group_id, cmd.params)
                            # pop_list is for already processed answers - will skip those in any next round of this the for cycle
                            pop_list.append(self.esl_pending_commands[subevent].index(cmd))
                            # Since we reach this point only if given cmd has been processed exactly once, thus we have to break the cycle for now
                            break
            else:
                self.log.error("Received response can't be found in pending commands! (%s)", data.hex())
                break

            if last_data <= len(data):
                self.log.debug("Parsing PAwR response: %s in slot %d", response_data.hex(), response_slot)
                ResponseParser(response_data, sensor_info)
                if self.controller_command is not None:
                    if tag is not None:
                        self.notify_controller(self.controller_command, CONTROLLER_COMMAND_SUCCESS, tag.esl_id, tag.group_id, response_data)
            else:
                self.log.warning("Broken PAwR response chunk: %s in slot %d", data[data_index:].hex(), response_slot)
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
