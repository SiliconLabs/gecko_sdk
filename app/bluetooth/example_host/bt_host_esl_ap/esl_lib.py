'''
ESL Library
'''

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

import ctypes
# True multiprocessing is temporarily disabled.
import multiprocessing.dummy as mp
from multiprocessing.connection import Connection
import os
import sys
import threading
import ap_logger
import esl_lib_wrapper as elw

SCAN_PHY_1M = 1
SCAN_PHY_CODED = 4
SCAN_PHY_1M_AND_CODED = 5
SCAN_DISCOVER_LIMITED = 0
SCAN_DISCOVER_GENERIC = 1
SCAN_DISCOVER_OBSERVATION = 2

def byref(x):
    '''Return the reference to an object, or None if the input is None'''
    if x is None:
        return None
    return ctypes.byref(x)

def bytes_to_array(source: bytes):
    if source is None:
        return None
    return (ctypes.c_ubyte * (1 + len(source)))(len(source), *source)

def array_to_bytes(source: elw.esl_lib_array_t):
    data = ctypes.cast(ctypes.addressof(source.data), ctypes.POINTER(ctypes.c_ubyte * source.len))
    return bytes(data.contents)

def array_p(array):
    if array is None:
        return None
    return ctypes.cast(ctypes.pointer(array), ctypes.POINTER(elw.esl_lib_array_t))

def bytes_to_long_array(source: bytes):
    if source is None:
        return None
    array = len(source).to_bytes(4, sys.byteorder) + source
    return (ctypes.c_ubyte * (4 + len(source)))(*array)

def long_array_to_bytes(source: elw.esl_lib_long_array_t):
    data = ctypes.cast(ctypes.addressof(source.data), ctypes.POINTER(ctypes.c_ubyte * source.len))
    return bytes(data.contents)

def long_array_p(array):
    if array is None:
        return None
    return ctypes.cast(ctypes.pointer(array), ctypes.POINTER(elw.esl_lib_long_array_t))

def get_enum(prefix, index):
    '''Return a dictionary from an enum'''
    try:
        return {getattr(elw, name): name for name in dir(elw) if name.startswith(prefix)}[index]
    except KeyError:
        return f'Unknown {index} ({hex(index)})'

def event_factory(evt_code: elw.esl_lib_evt_type_t, evt_data: elw.esl_lib_evt_data_t):
    '''Transform ctype object to specific class instance'''
    evt_class_list = [
        EventSystemBoot,
        EventScanStatus,
        EventTagFound,
        EventTagInfo,
        EventConfigureTagResponse,
        EventConnectionClosed,
        EventConnectionOpened,
        EventBondingData,
        EventPawrStatus,
        EventPawrResponse,
        EventPawrDataRequest,
        EventError,
        EventImageTransferFinished,
        EventImageType,
        EventControlPointResponse,
        EventControlPointNotification,
        EventGeneral
    ]
    for cls in evt_class_list:
        if cls.evt_code == evt_code:
            return cls(evt_data)
    raise Exception(f'Unknown ESL event: {evt_code}')

def get_node_id(node_id: elw.esl_lib_node_id_t):
    '''Convert node ID to a native Python object'''
    if node_id.type == elw.ESL_LIB_NODE_ID_TYPE_ADDRESS:
        return Address.from_ctype(node_id.id.address)
    if node_id.type == elw.ESL_LIB_NODE_ID_TYPE_CONNECTION:
        # Store pointer as an integer
        return int(node_id.id.connection_handle)
    if node_id.type == elw.ESL_LIB_NODE_ID_TYPE_PAWR:
        return PAWRSubevent.from_ctype(node_id.id.pawr)
    return None

class Address():
    '''Bluetooth address'''
    def __init__(self, address: bytes, address_type=None):
        if len(address) != 6:
            raise ValueError(f'Invalid address: {address}')
        self.addr = address
        if address_type is None:
            # use public device address type per default
            self.addr_type = 0
        else:
            self.addr_type = int(address_type)

    def __repr__(self) -> str:
        return ':'.join([f'{b:02X}' for b in iter(reversed(self.addr))])

    def __eq__(self, other):
        if other is None:
            return False
        if isinstance(other, Address):
            return (self.addr == other.addr) and (self.addr_type == other.addr_type)
        if len(other) >= 12:
            val_b = bytes.fromhex(other.replace(':', ''))[::-1]
            return val_b == self.addr
        return other == self.addr

    def __hash__(self):
        return hash((self.addr, self.addr_type))

    @classmethod
    def from_str(cls, address: str, address_type=None):
        '''Create new address instance from string object'''
        return cls(bytes.fromhex(address.replace(':', ''))[::-1], address_type)

    @classmethod
    def from_ctype(cls, address: elw.esl_lib_address_t):
        '''Create new address instance from ctype object'''
        return cls(bytes(address.addr), int(address.addr_type))

    def to_ctype(self) -> elw.esl_lib_address_t:
        '''Convert to ctype object'''
        return elw.esl_lib_address_t((ctypes.c_ubyte * 6).from_buffer_copy(self.addr), self.addr_type)

class PAWRSubevent():
    '''Wrapper for esl_lib_pawr_subevent_t'''
    def __init__(self, handle: int, subevent: int):
        self.handle = handle
        self.subevent = subevent

    def __repr__(self) -> str:
        return f'PAWR {self.handle} subevent {self.subevent}'

    @classmethod
    def from_ctype(cls, pawr: elw.esl_lib_pawr_subevent_t):
        '''Convert from ctype object'''
        # Store pointer as an integer
        return cls(pawr.handle, pawr.subevent)

    def to_ctype(self) -> elw.esl_lib_pawr_subevent_t:
        '''Convert to ctype object'''
        return elw.esl_lib_pawr_subevent_t(ctypes.c_void_p(self.handle), self.subevent)

class EventType(int):
    '''Wrapper for esl_lib_evt_type_t'''
    def __repr__(self) -> str:
        return get_enum('ESL_LIB_EVT_', self)

class EventSystemBoot():
    '''Wrapper for esl_lib_evt_system_boot_t'''
    evt_code = EventType(elw.ESL_LIB_EVT_SYSTEM_BOOT)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.address = Address.from_ctype(evt_data.evt_boot.address)
        self.radio_id = evt_data.evt_boot.radio_id
        self.status = evt_data.evt_boot.status

    def __repr__(self) -> str:
        return f'{self.evt_code}, {self.address}, {self.radio_id}, {self.status}'

class EventScanStatus():
    '''Wrapper for esl_lib_evt_scan_status_t'''
    evt_code = EventType(elw.ESL_LIB_EVT_SCAN_STATUS)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.enabled = bool(evt_data.evt_scan_status.enabled)
        self.configured = bool(evt_data.evt_scan_status.configured)
        self.parameters = evt_data.evt_scan_status.parameters

    def __repr__(self) -> str:
        return f'{self.evt_code}, {self.enabled}, {self.configured}, {self.parameters.mode}, {self.parameters.interval}, {self.parameters.window}, {self.parameters.scanning_phy}, {self.parameters.discover_mode}'

class EventTagFound():
    '''Wrapper for esl_lib_evt_tag_found_t'''
    evt_code = EventType(elw.ESL_LIB_EVT_TAG_FOUND)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.address = Address.from_ctype(evt_data.evt_tag_found.address)
        self.rssi = evt_data.evt_tag_found.rssi

    def __repr__(self) -> str:
        return f'{self.evt_code}, {self.address}, {self.rssi}'

class EventTagInfo():
    '''Wrapper for esl_lib_evt_tag_info_t'''
    evt_code = EventType(elw.ESL_LIB_EVT_TAG_INFO)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.connection_handle = evt_data.evt_tag_info.connection_handle
        tlv_data = long_array_to_bytes(evt_data.evt_tag_info.tlv_data)
        self.tlv_data = {}
        tlv_position = 0
        while tlv_position < len(tlv_data):
            tlv = elw.esl_lib_tlv_t.from_buffer_copy(tlv_data, tlv_position)
            tlv_position += ctypes.sizeof(tlv)
            value = tlv_data[tlv_position: tlv_position + tlv.data.len]
            self.tlv_data[tlv.type] = value
            tlv_position += len(value)

    def __repr__(self) -> str:
        tlv_data_str = ', '.join([f'{get_enum("ESL_LIB_DATA_TYPE_", key)}: {value.hex()}' for key, value in self.tlv_data.items()])
        return f'{self.evt_code}, {self.connection_handle:#x}, {tlv_data_str}'

class EventConfigureTagResponse():
    '''Wrapper for esl_lib_evt_configure_tag_response_t'''
    evt_code = EventType(elw.ESL_LIB_EVT_CONFIGURE_TAG_RESPONSE)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.connection_handle = evt_data.evt_configure_tag_response.connection_handle
        self.type = evt_data.evt_configure_tag_response.type
        self.status = evt_data.evt_configure_tag_response.status

    def __repr__(self) -> str:
        type_str = get_enum('ESL_LIB_DATA_TYPE_', self.type)
        status_str = get_enum('SL_STATUS_', self.status)
        return f'{self.evt_code}, {self.connection_handle:#x}, {type_str}, {status_str}'

class EventControlPointResponse():
    '''Wrapper for esl_lib_evt_control_point_response_t'''
    evt_code = EventType(elw.ESL_LIB_EVT_CONTROL_POINT_RESPONSE)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.connection_handle = evt_data.evt_control_point_response.connection_handle
        self.status = evt_data.evt_control_point_response.status
        self.data_sent = array_to_bytes(evt_data.evt_control_point_response.data_sent)

    def __repr__(self) -> str:
        status_str = get_enum('SL_STATUS_', self.status)
        return f'{self.evt_code}, {self.connection_handle:#x}, {status_str}, {self.data_sent.hex()}'

class EventControlPointNotification():
    '''Wrapper for esl_lib_evt_control_point_notification_t'''
    evt_code = EventType(elw.ESL_LIB_EVT_CONTROL_POINT_NOTIFICATION)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.connection_handle = evt_data.evt_control_point_notification.connection_handle
        self.data = array_to_bytes(evt_data.evt_control_point_notification.data)

    def __repr__(self) -> str:
        return f'{self.evt_code}, {self.connection_handle:#x}, {self.data.hex()}'

class EventConnectionOpened():
    '''Wrapper for esl_lib_evt_connection_opened_t'''
    evt_code = EventType(elw.ESL_LIB_EVT_CONNECTION_OPENED)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.connection_handle = evt_data.evt_connection_opened.connection_handle
        self.address = Address.from_ctype(evt_data.evt_connection_opened.address)
        self.gattdb_handles = elw.esl_lib_gattdb_handles_t.from_buffer_copy(evt_data.evt_connection_opened.gattdb_handles)

    def __repr__(self) -> str:
        gattdb_str = f'[{self.gattdb_handles.services.esl}, {self.gattdb_handles.services.ots}, {self.gattdb_handles.services.dis}]'
        return f'{self.evt_code}, {self.connection_handle:#x}, {self.address}, {gattdb_str}'

class EventConnectionClosed():
    '''Wrapper for esl_lib_evt_connection_closed_t'''
    evt_code = EventType(elw.ESL_LIB_EVT_CONNECTION_CLOSED)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.connection_handle = evt_data.evt_connection_closed.connection_handle
        self.address = Address.from_ctype(evt_data.evt_connection_closed.address)
        self.reason = evt_data.evt_connection_closed.reason

    def __repr__(self) -> str:
        reason_str = get_enum('SL_STATUS_', self.reason)
        return f'{self.evt_code}, {self.connection_handle:#x}, {self.address}, {reason_str}'

class EventBondingData():
    '''Wrapper for esl_lib_evt_bonding_data_t'''
    evt_code = EventType(elw.ESL_LIB_EVT_BONDING_DATA)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.connection_handle = evt_data.evt_bonding_data.connection_handle
        self.address = Address.from_ctype(evt_data.evt_bonding_data.address)
        self.ltk = bytes(evt_data.evt_bonding_data.ltk)

    def __repr__(self) -> str:
        return f'{self.evt_code}, {self.connection_handle:#x}, {self.address}, {self.ltk.hex()}'

class EventImageTransferFinished():
    '''Wrapper for esl_lib_evt_image_transfer_finished_t'''
    evt_code = EventType(elw.ESL_LIB_EVT_IMAGE_TRANSFER_FINISHED)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.connection_handle = evt_data.evt_image_transfer_finished.connection_handle
        self.img_index = evt_data.evt_image_transfer_finished.img_index
        self.status = evt_data.evt_image_transfer_finished.status

    def __repr__(self) -> str:
        status_str = get_enum('SL_STATUS_', self.status)
        return f'{self.evt_code}, {self.connection_handle:#x}, {self.img_index}, {status_str}'

class EventImageType():
    '''Wrapper for esl_lib_evt_image_type_t'''
    evt_code = EventType(elw.ESL_LIB_EVT_IMAGE_TYPE)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.connection_handle = evt_data.evt_image_type.connection_handle
        self.img_index = evt_data.evt_image_type.img_index
        self.type_data = long_array_to_bytes(evt_data.evt_image_type.type_data)

    def __repr__(self) -> str:
        return f'{self.evt_code}, {self.connection_handle:#x}, {self.img_index}, {self.type_data.hex()}'

class EventPawrStatus():
    '''Wrapper for esl_lib_evt_pawr_status_t'''
    evt_code = EventType(elw.ESL_LIB_EVT_PAWR_STATUS)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.pawr_handle = evt_data.evt_pawr_status.pawr_handle
        self.enabled = bool(evt_data.evt_pawr_status.enabled)
        self.configured = bool(evt_data.evt_pawr_status.configured)
        self.config = evt_data.evt_pawr_status.config

    def __repr__(self) -> str:
        return f'{self.evt_code}, {self.pawr_handle:#x}, {self.enabled}, {self.configured}, {self.config.adv_interval.min}, {self.config.adv_interval.max}, {self.config.subevent.count}, {self.config.subevent.interval}, {self.config.response_slot.delay}, {self.config.response_slot.spacing}, {self.config.response_slot.count}'

class EventPawrResponse():
    '''Wrapper for esl_lib_evt_pawr_response_t'''
    evt_code = EventType(elw.ESL_LIB_EVT_PAWR_RESPONSE)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.pawr_handle = evt_data.evt_pawr_response.pawr_handle
        self.response_slot = evt_data.evt_pawr_response.response_slot
        self.subevent = evt_data.evt_pawr_response.subevent
        self.data = long_array_to_bytes(evt_data.evt_pawr_response.data)

    def __repr__(self) -> str:
        return f'{self.evt_code}, {self.pawr_handle:#x}, {self.response_slot}, {self.subevent}, {self.data.hex()}'

class EventPawrDataRequest():
    '''Wrapper for esl_lib_evt_pawr_data_request_t'''
    evt_code = EventType(elw.ESL_LIB_EVT_PAWR_DATA_REQUEST)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.pawr_handle = evt_data.evt_pawr_data_request.pawr_handle
        self.subevent_start = evt_data.evt_pawr_data_request.subevent_start
        self.subevent_data_count = evt_data.evt_pawr_data_request.subevent_data_count

    def __repr__(self) -> str:
        return f'{self.evt_code}, {self.pawr_handle:#x}, {self.subevent_start}, {self.subevent_data_count}'

class EventError():
    '''Wrapper for esl_lib_evt_error_t'''
    evt_code = EventType(elw.ESL_LIB_EVT_ERROR)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.node_id = get_node_id(evt_data.evt_error.node_id)
        self.lib_status = evt_data.evt_error.lib_status
        self.sl_status = evt_data.evt_error.sl_status
        self.data = evt_data.evt_error.data.core_state

    def __repr__(self) -> str:
        lib_status_str = get_enum('ESL_LIB_STATUS_', self.lib_status)
        sl_status_str = get_enum('SL_STATUS_', self.sl_status)
        try:
            if isinstance(self.node_id, int):
                # Connection handle node ID type
                data_str = get_enum('ESL_LIB_CONNECTION_STATE_', self.data)
            elif isinstance(self.node_id, PAWRSubevent):
                # PAWR handle node ID type
                data_str = get_enum('ESL_LIB_PAWR_STATE_', self.data)
            else:
                data_str = get_enum('ESL_LIB_CORE_STATE_', self.data)
        except KeyError:
            data_str = str(self.data)
        return f'{self.evt_code}, {self.node_id}, {lib_status_str}, {sl_status_str}, {data_str}'

class EventGeneral():
    '''Wrapper for general events'''
    evt_code = EventType(elw.ESL_LIB_EVT_GENERAL)

    def __init__(self, evt_data: elw.esl_lib_evt_data_t):
        self.data = long_array_to_bytes(evt_data.evt_general)

    def __repr__(self) -> str:
        return f'{self.evt_code}, {self.data.hex()}'

class CommandFailedError(Exception):
    '''ESL Library command failed'''

class Lib():
    '''ESL library running in its own process'''
    def __init__(self, config):
        self.config = config
        self.event_queue = mp.Queue()
        self._command_lock = mp.Lock()
        self._conn, conn = mp.Pipe()
        self._process = mp.Process(target=self._process_run, args=(conn, ap_logger.stdout, ap_logger.level))
        self._process.daemon = True
        self._process.start()

    def _on_event(self, evt_code: elw.esl_lib_evt_type_t, evt_data: ctypes.POINTER(elw.esl_lib_evt_data_t)):
        '''ESL event callback'''
        event = event_factory(evt_code, evt_data.contents)
        self.event_queue.put(event)

    def _process_run(self, conn, stdout, level):
        '''Main method of the ESL lib process'''
        ap_logger.stdout = stdout
        ap_logger.level = level
        logger = ap_logger.getLogger('LIB')
        logger.debug('started pid: %u', os.getpid())
        threading.Thread(target=self._deserialize_command, daemon=True, args=(conn,)).start()
        # Instantiate callback function pointer
        on_event_func = elw.esl_lib_on_event_t(self._on_event)

        def log(level:int, module:str, log:str, file:str, line:int, function:str):
            """Logging callback for ESL lib instance"""
            LOG_LEVEL_DICT = {
                elw.ESL_LIB_LOG_LEVEL_DEBUG: logger.debug,
                elw.ESL_LIB_LOG_LEVEL_INFO: logger.info,
                elw.ESL_LIB_LOG_LEVEL_WARNING: logger.warning,
                elw.ESL_LIB_LOG_LEVEL_ERROR: logger.error,
                elw.ESL_LIB_LOG_LEVEL_CRITICAL: logger.critical,
            }
            filter_events = [b"PAwR response, data status = 255", b"Tag found"]
            if not any(flt in log for flt in filter_events):
                LOG_LEVEL_DICT[level](f'[{module}] {log.rstrip()} @ {file}:{line} in {function}')
        log_func = elw.esl_lib_log_callback_t(log)
        elw.esl_lib_start(self.config, on_event_func, log_func)
        logger.debug('terminated pid: %u', os.getpid())

    def _deserialize_command(self, conn: Connection):
        '''Deserialize command and serialize result'''
        while True:
            command, args = conn.recv()
            result = getattr(self, command)(*args)
            conn.send(result)

    def _serialize_command(self, command, args=None):
        '''Serialize command and deserialize result'''
        if args is None:
            # Use empty tuple for functions with void argument list
            args = ()
        with self._command_lock:
            try:
                self._conn.send((command, args))
                result = self._conn.recv()
            except BrokenPipeError as err:
                raise CommandFailedError('Lib process terminated unexpectedly') from err
            if result[0]:
                raise CommandFailedError(f'{command[1:]} failed {get_enum("SL_STATUS_", result[0])}')
            return result

    def stop(self, timeout=3):
        '''Public wrapper for esl_lib_stop'''
        self._serialize_command('_stop')
        # Wait for the process to terminate
        self._process.join(timeout=timeout)

    def _stop(self):
        '''Internal wrapper for esl_lib_stop'''
        status = elw.esl_lib_stop()
        return (status, )

    def scan_configure(self,
                       active_mode: bool=False,
                       interval_ms: float=10.0,
                       window_ms: float=10.0,
                       scanning_phy: int=SCAN_PHY_1M,
                       discover_mode: int=SCAN_DISCOVER_GENERIC):
        '''Public wrapper for esl_lib_scan_configure'''
        self._serialize_command('_scan_configure',
                                (active_mode, interval_ms, window_ms, scanning_phy, discover_mode))

    def _scan_configure(self,
                        active_mode: bool=False,
                        interval_ms: float=10.0,
                        window_ms: float=10.0,
                        scanning_phy: int=SCAN_PHY_1M,
                        discover_mode: int=SCAN_DISCOVER_GENERIC):
        '''Internal wrapper for esl_lib_scan_configure'''
        parameters = elw.esl_lib_scan_parameters_t(mode=active_mode,
                                                   interval=int(interval_ms / 0.625),
                                                   window=int(window_ms / 0.625),
                                                   scanning_phy=scanning_phy,
                                                   discover_mode=discover_mode)
        status = elw.esl_lib_scan_configure(byref(parameters))
        return (status, )

    def scan_enable(self, enable: bool=True):
        '''Public wrapper for esl_lib_scan_enable'''
        self._serialize_command('_scan_enable', (enable,))

    def _scan_enable(self, enable: bool):
        '''Internal wrapper for esl_lib_scan_enable'''
        status = elw.esl_lib_scan_enable(enable)
        return (status, )
    
    def get_scan_status(self):
        '''Public wrapper for esl_lib_get_scan_status'''
        self._serialize_command('_get_scan_status')

    def _get_scan_status(self):
        '''Internal wrapper for esl_lib_get_scan_status'''
        status = elw.esl_lib_get_scan_status()
        return (status, )

    def connect(self,
                address: Address,
                pawr=None,
                identity: Address=None,
                key_type: int=elw.ESL_LIB_KEY_TYPE_NO_KEY,
                key: bytes=None,
                gattdb=None):
        '''Public wrapper for esl_lib_connect'''
        self._serialize_command('_connect', (address, pawr, identity, key_type, key, gattdb))

    def _connect(self,
                 address: Address,
                 pawr: PAWRSubevent,
                 identity: Address,
                 key_type: int,
                 key: bytes,
                 gattdb):
        '''Internal wrapper for esl_lib_connect'''
        c_address = address.to_ctype()
        c_pawr = None
        if pawr is not None:
            c_pawr = pawr.to_ctype()
        c_identity = None
        if identity is not None:
            c_identity = identity.to_ctype()
        c_key = None
        if key is not None:
            c_key = bytes_to_array(key)
        status = elw.esl_lib_connect(c_address,
                                     byref(c_pawr),
                                     byref(c_identity),
                                     key_type,
                                     array_p(c_key),
                                     byref(gattdb))
        return (status, )

    def close_connection(self, connection_handle):
        '''Public wrapper for esl_lib_close_connection'''
        self._serialize_command('_close_connection', (connection_handle,))

    def _close_connection(self, connection_handle):
        '''Internal wrapper for esl_lib_close_connection'''
        status = elw.esl_lib_close_connection(connection_handle)
        return (status, )

    def get_tag_info(self, connection_handle):
        '''Public wrapper for esl_lib_get_tag_info'''
        self._serialize_command('_get_tag_info', (connection_handle,))

    def _get_tag_info(self, connection_handle):
        '''Internal wrapper for esl_lib_get_tag_info'''
        status = elw.esl_lib_get_tag_info(connection_handle)
        return (status, )

    def configure_tag(self, connection_handle, tlv_data: dict, att_response: bool=True):
        '''Public wrapper for esl_lib_configure_tag'''
        data = b''
        for key, value in tlv_data.items():
            data += int(key).to_bytes(ctypes.sizeof(elw.esl_lib_data_type_t), sys.byteorder)
            data += len(value).to_bytes(ctypes.sizeof(elw.uint32_t), sys.byteorder)
            data += value
        self._serialize_command('_configure_tag', (connection_handle, data, att_response))

    def _configure_tag(self, connection_handle, tlv_data: bytes, att_response: bool):
        '''Internal wrapper for esl_lib_configure_tag'''
        c_tlv_data = bytes_to_long_array(tlv_data)
        status = elw.esl_lib_configure_tag(connection_handle, long_array_p(c_tlv_data), att_response)
        return (status, )

    def write_control_point(self, connection_handle, data: bytes, att_response: bool=True):
        '''Public wrapper for esl_lib_write_control_point'''
        self._serialize_command('_write_control_point', (connection_handle, data, att_response))

    def _write_control_point(self, connection_handle, data: bytes, att_response: bool):
        '''Internal wrapper for esl_lib_write_control_point'''
        c_data = bytes_to_array(data)
        status = elw.esl_lib_write_control_point(connection_handle, array_p(c_data), att_response)
        return (status, )

    def pawr_create(self):
        '''Public wrapper for esl_lib_pawr_create'''
        (_, handle_out) = self._serialize_command('_pawr_create')
        return handle_out

    def _pawr_create(self):
        '''Internal wrapper for esl_lib_pawr_create'''
        handle_out = elw.esl_lib_pawr_handle_t()
        status = elw.esl_lib_pawr_create(byref(handle_out))
        return (status, handle_out.value)

    def pawr_remove(self, pawr_handle):
        '''Public wrapper for esl_lib_pawr_remove'''
        self._serialize_command('_pawr_remove', (pawr_handle,))

    def _pawr_remove(self, pawr_handle):
        '''Internal wrapper for esl_lib_pawr_remove'''
        status = elw.esl_lib_pawr_remove(pawr_handle)
        return (status, )

    def pawr_enable(self, pawr_handle, enable: bool=True):
        '''Public wrapper for esl_lib_pawr_enable'''
        self._serialize_command('_pawr_enable', (pawr_handle, enable))

    def _pawr_enable(self, pawr_handle, enable: bool):
        '''Internal wrapper for esl_lib_pawr_enable'''
        status = elw.esl_lib_pawr_enable(pawr_handle, enable)
        return (status, )

    def pawr_set_data(self, pawr_handle, subevent: int, payload: bytes):
        '''Public wrapper for esl_lib_pawr_set_data'''
        self._serialize_command('_pawr_set_data', (pawr_handle, subevent, payload))

    def _pawr_set_data(self, pawr_handle, subevent: int, payload: bytes):
        '''Internal wrapper for esl_lib_pawr_set_data'''
        c_payload = bytes_to_array(payload)
        status = elw.esl_lib_pawr_set_data(pawr_handle, subevent, array_p(c_payload))
        return (status, )

    def pawr_configure(self,
                       pawr_handle,
                       adv_interval_min=elw.ESL_LIB_PERIODIC_ADV_MIN_INTERVAL_DEFAULT,
                       adv_interval_max=elw.ESL_LIB_PERIODIC_ADV_MAX_INTERVAL_DEFAULT,
                       subevent_count=elw.ESL_LIB_PAWR_SUBEVENT_COUNT_DEFAULT,
                       subevent_interval=elw.ESL_LIB_PAWR_SUBEVENT_INTERVAL_DEFAULT,
                       response_slot_delay=elw.ESL_LIB_PAWR_RESPONSE_SLOT_DELAY_DEFAULT,
                       response_slot_spacing=elw.ESL_LIB_PAWR_RESPONSE_SLOT_SPACING_DEFAULT,
                       response_slot_count=elw.ESL_LIB_PAWR_RESPONSE_SLOT_COUNT_DEFAULT):
        '''Public wrapper for esl_lib_pawr_configure'''
        self._serialize_command('_pawr_configure',
                                (pawr_handle,
                                 adv_interval_min,
                                 adv_interval_max,
                                 subevent_count,
                                 subevent_interval,
                                 response_slot_delay,
                                 response_slot_spacing,
                                 response_slot_count))

    def _pawr_configure(self,
                        pawr_handle,
                        adv_interval_min,
                        adv_interval_max,
                        subevent_count,
                        subevent_interval,
                        response_slot_delay,
                        response_slot_spacing,
                        response_slot_count):
        '''Internal wrapper for esl_lib_pawr_configure'''
        pawr_config = elw.esl_lib_pawr_config_t(elw.struct_esl_lib_pawr_config_adv_interval_s(adv_interval_min, adv_interval_max),
                                                elw.struct_esl_lib_pawr_config_subevent_s(subevent_count, subevent_interval),
                                                elw.struct_esl_lib_pawr_config_response_slot_s(response_slot_delay, response_slot_spacing, response_slot_count))
        status = elw.esl_lib_pawr_configure(pawr_handle, byref(pawr_config))
        return (status, )
    
    def get_pawr_status(self, pawr_handle):
        '''Public wrapper for esl_lib_get_pawr_status'''
        self._serialize_command('_get_pawr_status', (pawr_handle,))

    def _get_pawr_status(self, pawr_handle):
        '''Internal wrapper for esl_lib_get_pawr_status'''
        status = elw.esl_lib_get_pawr_status(pawr_handle)
        return (status, )

    def initiate_past(self, connection_handle, pawr_handle):
        '''Public wrapper for esl_lib_initiate_past'''
        self._serialize_command('_initiate_past', (connection_handle, pawr_handle))

    def _initiate_past(self, connection_handle, pawr_handle):
        '''Internal wrapper for esl_lib_initiate_past'''
        status = elw.esl_lib_initiate_past(connection_handle, pawr_handle)
        return (status, )

    def write_image(self, connection_handle, img_index, img_data: bytes):
        '''Public wrapper for esl_lib_write_image'''
        self._serialize_command('_write_image', (connection_handle, img_index, img_data))

    def _write_image(self, connection_handle, img_index, img_data: bytes):
        '''Internal wrapper for esl_lib_write_image'''
        status = elw.esl_lib_write_image(connection_handle, img_index, len(img_data), img_data)
        return (status, )

    def get_image_type(self, connection_handle, img_index):
        '''Public wrapper for esl_lib_get_image_type'''
        self._serialize_command('_get_image_type', (connection_handle, img_index))

    def _get_image_type(self, connection_handle, img_index):
        '''Internal wrapper for esl_lib_get_image_type'''
        status = elw.esl_lib_get_image_type(connection_handle, img_index)
        return (status, )

    def general_command(self, cmd_code, data: bytes=None):
        '''Public wrapper for esl_lib_general_cmd'''
        self._serialize_command('_general_command', (cmd_code, data))

    def _general_command(self, cmd_code, data: bytes):
        '''Internal wrapper for esl_lib_general_cmd'''
        c_data = bytes_to_long_array(data)
        status = elw.esl_lib_general_cmd(cmd_code, long_array_p(c_data))
        return (status, )
