#!/usr/bin/env python3
'''
ESL Library Tester
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
import os
import queue
import sys
import threading
import time
from esl_lib import *
import ap_logger
from ap_ead import *
import datetime

class LibTest(threading.Thread):

    '''Tester class'''
    def __init__(self, config):
        super().__init__(daemon=True)
        self.event_handlers = []
        self.address_list = []
        self.rssi_threshold = -200
        self.connection_list = []
        self.max_connection_count = 8
        self.ltk = dict()
        self.gattdb = dict()
        self.image = bytearray.fromhex("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffbf5445ffffffffffffffffffffffffffab0000aafeffffffffffffffffffff7f052a82aad0ffffffffffffffffffff5fa940a85a45ffffffffffffffffffffb7008a4a5511ffffffffffffffffffff2b5551552b04fcffffffffffffffffffad88a4aa5601faffffffffffffffff7f2b25495d1500f0ffffffffffffffffff8448526b0100f0ffffffffffffffffbf529248950400c0ffffffffffffffff5f8414a12a0000c0ffffffffffffffff2f51552a01000880ffffffffffffffff1704080000800000ffffffffffffffff5729119000200000ffffffffffffffff8b02000200011000feffffffffffffffab54010000000200fcffffffffffffff55150a2800000000fcffffffffffffffd3aaa40200002000f8ffffffffffffffaaaa4a5400040802f8ffffffffffffffb5aa920a00000000f8ffffffffffffff6babaa5400000100f0ffffffffffffffaa56abaa00200000f8ffffffffffffffda6d555510040000f0ffffffffffffff6a5bdbaa02000000e0ffffffffffffffb6d6aaaa40004008e8ffffffffffffffdabdb65a00200000f0ffffffffffff7fbdd5aaa600040402e2ffffffffffffffd6b65d2d80000080f0ffffffffffffbf756d6b5501000000e0ffffffffffffffaebb5d5500200000e8ffffffffffff7ff576ab2a04000801e1ffffffffffffffadadb65581000008e8ffffffffffffbf767bad4a20200100f0ffffffffffffffddad559200002000e4ffffffffffff7f6b5fab2a00200042f0ffffffffffffffde75ad4401080800e4ffffffffffffff75abab1580000000f1ffffffffffff7fdb7e552501400204e0fffffffffffffff6d5560980000000f4ffffffffffffff5dbfb5aa02208040f0ffffffffffff7feb6a6515240a0900f2ffffffffffffffddff5a5509400010f0ffffffffffffff57d5d52a81080100f9ffffffffffff7fedbfaf4a15220004f8ffffffffffffffb76ad53642480140f8ffffffffffffffeeffb7cd14110000f9ffffffffffffff5b55ad2a494a0148fcfffffffffffffff7ffeb5625100201fcffffffffffffff5d555fad94ca0800feffffffffffffffb7ffb5ab52248290fcffffffffffffff7f556f6d95520804feffffffffffffffd7ffdd5b55a40200ffffffffffffffffbfaaab5629092940ffffffffffffffffef7f7fb54ab20089ffffffffffffffffbfeaaa6b954454c0ffffffffffffffffffdf6d5d559500c4ffffffffffffffff7fb55aab2a2a8af0ffffffffffffffffffedb5d64a4910f2ffffffffffffffffff5babad922485f8ffffffffffffffffffb75ab5264910fcffffffffffffffffff6fabaaa98284feffffffffffffffffffdf566b4a1421ffffffffffffffffffffbf5555954088ffffffffffffffffffff7fdbaa2a15e1f7ffffffffffffffffffff35555522d27effffffffffffffffff7f6b554989b8dbfbffffffffffffffffeb56555522aaf6defdffffffffffffff5fa5aa8a08a4daf7ffffffffffffff7fbb0a121040a9b67eefffffffffffffffd7524045154ad5edfffeffffffffffdfbe561588a0526dbbfdfffffffffffff76b55d52aadaadafeefefffffffffff7fdfdbaa6a55d5b66b7fffffffffffffff75adb75555adedfefbffffffffffffefff776d6fef7ab7effefbfefffffffffbdffeffbab5effdbddffffffffffffffffd6fdbefffde6ffffffffffffffffffffffb7f7fab7bfbf7fbfffffffffffffffffef7fbfffffffffefeffffffffffffbffffddffff7dfbdfffffffffffffffffffffffffdbefdffffffffffffffffffffffffffbfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff")
        self.lib = Lib(config)

    def wait_event(self, event_type, timeout=10, func=None):
        '''Wait until specific event arrives'''
        evt_prev = None
        timeout_abs = time.time() + timeout

        while True:
            try:
                evt = self.lib.event_queue.get(timeout=timeout)
                for handler in self.event_handlers:
                    try:
                        if handler(evt):
                            print('Event handled')
                    except KeyboardInterrupt:
                        sys.exit(-1)
                    except Exception as e:
                        print(f'Failed to execute event handler: {e}')
                if not (isinstance(evt, EventPawrDataRequest) and isinstance(evt_prev, EventPawrDataRequest)):
                    print(evt)
                evt_prev = evt
                if isinstance(evt, event_type):
                    if func == None:
                        return evt
                    if func(evt):
                        return evt
                if isinstance(evt, EventError):
                    raise Exception('Error event')
                if timeout_abs < time.time():
                    raise Exception(f'Error: wait {event_type.__name__} timeout')
            except KeyboardInterrupt:
                sys.exit(-1)
            except queue.Empty as err:
                raise Exception(f'Error: wait {event_type.__name__} timeout') from err

    def run(self):
        '''Auto tester logic'''
        try:
            self.wait_event(EventSystemBoot)
            print("************************** API TEST **************************")
            self.test_api()
            print("******************** MULTICONNECTION TEST ********************")
            self.test_multiconnection()
            print("*********************** AP CONTR. TEST ***********************")
            self.test_ap_control()
            print("**************************************************************")
            self.lib.stop()
            print('Test finished successfully')
        except KeyboardInterrupt:
            sys.exit(-1)
        except Exception as err:
            print(err)
    
    def add_event_handler(self, event_handler_func):
        self.event_handlers.append(event_handler_func)

    def remove_event_handler(self, event_handler_func):
        self.event_handlers.remove(event_handler_func)
    
    def disconnect_handler(self, evt):
        if isinstance(evt, EventConnectionClosed):
            for conn in self.connection_list:
                if conn.connection_handle == evt.connection_handle:
                    self.connection_list.remove(conn)
                    del self.bonidng_data[conn.address]
                    del self.gattdb[conn.address]
                    return True
        return False

    def test_multiconnection(self):
        '''Test sequence for multiconnection'''
        
        sync_key = bytes.fromhex("5ba4a65cae2fac6d725888c7795b82608c4bd1a769756482")
        response_key = bytes.fromhex("e3637ad2aab72e59131e0b21e03230edce44a2e93dfecdb1")

        # Create and set PAwR
        pawr_handle = self.lib.pawr_create()
        print(f'{pawr_handle:#x}')
        self.lib.pawr_configure(pawr_handle)
        self.lib.get_pawr_status(pawr_handle)
        self.wait_event(EventPawrStatus)
        self.lib.pawr_enable(pawr_handle)
        self.wait_event(EventPawrStatus)

        # Read status and enable scanning
        self.lib.get_scan_status()
        self.wait_event(EventScanStatus)
        self.lib.scan_enable()
        self.wait_event(EventScanStatus)

        # Connect all tags
        self.add_event_handler(self.disconnect_handler)
        
        if len(self.address_list) < 2:
            time_scan_begin = datetime.datetime.now()
            while (datetime.datetime.now() - time_scan_begin).total_seconds() < 30 and len(self.address_list) < self.max_connection_count:
                tag_found = self.wait_event(EventTagFound)
                if self.rssi_threshold is not None and tag_found.rssi >= self.rssi_threshold:
                    if tag_found.address not in self.address_list:
                        self.address_list.append(tag_found.address)

        # Disable scanning
        self.lib.scan_enable(False)
        self.wait_event(EventScanStatus)

        if len(self.address_list) < 2:
            print('Could not found enough tags.')
            print('Close PAwR')
            self.lib.pawr_enable(pawr_handle, False)
            self.wait_event(EventPawrStatus)
            self.lib.pawr_remove(pawr_handle)
            print('Exiting.')
            return
        
        tag_count = len(self.address_list)

        print(f'Found {tag_count} tags.')

        time_connect_begin = None

        while (len(self.connection_list) < tag_count):
            try:
                for address in self.address_list:
                    found = False
                    for connection in self.connection_list:
                        if connection.address == address:
                           found = True
                    if not found:
                        if time_connect_begin == None:
                                time_connect_begin = datetime.datetime.now()
                        print(f'Connecting to {address}')
                        self.lib.connect(address)
                        bonding_data = self.wait_event(EventBondingData)
                        conn = self.wait_event(EventConnectionOpened,30)
                        print(f'Connected to {tag_found.address}')
                        self.connection_list.append(conn)
                        self.ltk[conn.address] = bonding_data.ltk
                        self.gattdb[conn.address] = conn.gattdb_handles
            except Exception as err:
                print(f'Error during connection, error = {err}')
        time_connect_end = datetime.datetime.now()
        self.remove_event_handler(self.disconnect_handler)
        
        print(f'Successfully connected to {len(self.connection_list)} tags.')
        
        # Read tag info
        time_info_begin = datetime.datetime.now()
        for conn in self.connection_list:
            self.lib.get_tag_info(conn.connection_handle)
        for conn in self.connection_list:
            self.wait_event(EventTagInfo)
        time_info_end = datetime.datetime.now()
        
        # Write images
        time_it_begin = datetime.datetime.now()
        image = self.image
        for img_index in range(2):
            for conn in self.connection_list:
                if conn.gattdb_handles.services.ots != elw.ESL_LIB_INVALID_SERVICE_HANDLE:
                    self.lib.write_image(conn.connection_handle, img_index, bytes(image))
                    for index in range(len(image)):
                        image[index] ^= 0xFF
            for conn in self.connection_list:
                if conn.gattdb_handles.services.ots != elw.ESL_LIB_INVALID_SERVICE_HANDLE:
                    self.wait_event(EventImageTransferFinished)
        time_it_end = datetime.datetime.now()

        # Configure the tags
        time_config_begin = datetime.datetime.now()
        i = 0
        for conn in self.connection_list:
            esl_address = bytearray.fromhex("0000")
            esl_address[0] = i
            tlv_data = {elw.ESL_LIB_DATA_TYPE_GATT_ESL_ADDRESS: esl_address,
                        elw.ESL_LIB_DATA_TYPE_GATT_AP_SYNC_KEY: sync_key,
                        elw.ESL_LIB_DATA_TYPE_GATT_RESPONSE_KEY: response_key,
                        elw.ESL_LIB_DATA_TYPE_GATT_CURRENT_TIME: bytes.fromhex("00000000")}
            self.lib.configure_tag(conn.connection_handle, tlv_data)
            i = i + 1
        for conn in self.connection_list:
            self.wait_event(EventConfigureTagResponse)
            self.wait_event(EventConfigureTagResponse)
            self.wait_event(EventConfigureTagResponse)
            self.wait_event(EventConfigureTagResponse)

        # Display image
        i = 0
        for conn in self.connection_list:
            # Send display image 0 to CP
            display_image = bytearray.fromhex("20000000")
            display_image[1] = i
            self.lib.write_control_point(conn.connection_handle, display_image)
            i = i + 1
        for conn in self.connection_list:
            # Wait for notification only
            self.wait_event(EventControlPointNotification)

        # Send uptade complete events
        i = 0
        for conn in self.connection_list:
            # Send Update complete to CP
            update_complete = bytearray.fromhex("0400")
            update_complete[1] = i
            self.lib.write_control_point(conn.connection_handle, update_complete)
            i = i + 1
        for conn in self.connection_list:
            # Wait for response only
            self.wait_event(EventControlPointResponse)
        
        time_config_end = datetime.datetime.now()


        #initiate PAST
        time_past_begin = datetime.datetime.now()
        for conn in self.connection_list:
            # Initiate past
            self.lib.initiate_past(conn.connection_handle,pawr_handle)
        for conn in self.connection_list.copy():
            disc_event = self.wait_event(EventConnectionClosed)
            for conn_close in self.connection_list.copy():
                if conn_close.connection_handle == disc_event.connection_handle:
                    self.connection_list.remove(conn_close)
            print(f'Connection closed. {len(self.connection_list)} tags left.')

        time_past_end = datetime.datetime.now()
        
        print(f'Connection list length is {len(self.connection_list)}.')

      
        # Send ping through PAwR 5 times
        ping_command = bytearray([0])
        for i in range(tag_count):
            ping_command.append(0)
            ping_command.append(i)
        ping_encrypted = EAD().encrypt(data=ping_command, key_material=KeyMaterial(sync_key))

        print(f'Sending PAwR command {ping_command}, encrypted {ping_encrypted}.')
        
        for _ in range(5):
            self.wait_event(EventPawrDataRequest, 20, lambda x : (x.subevent_start + 3) % 28 < 4)
            print("Time to set PAwR data")
            # Send PAwR data
            self.lib.pawr_set_data(pawr_handle, 0, ping_encrypted)
            self.wait_event(EventPawrResponse)
            self.wait_event(EventPawrResponse)

        # Connect again throug PAwR
        print(f'Reconnecting to {tag_count} tags.')
        pawr_subevent = PAWRSubevent(pawr_handle, 0)
        for address in self.address_list:
            print(f'Reconnecting to {address} using {pawr_subevent} and key {self.ltk[address]}')
            self.lib.connect(address,
                             pawr_subevent,
                             gattdb=self.gattdb[address],
                             key_type=elw.ESL_LIB_KEY_TYPE_LTK,
                             key=self.ltk[address])
            conn = self.wait_event(EventConnectionOpened)
            self.connection_list.append(conn)
            print(f'Connected to {address}')

        # Unassociate tags
        print(f'Unassociating {len(self.connection_list)} tags.')
        i = 0
        for conn in self.connection_list:
            # Send Unassociate to CP
            unassociate = bytearray.fromhex("0100")
            unassociate[1] = i
            self.lib.write_control_point(conn.connection_handle, unassociate)
            i = i + 1
        for conn in self.connection_list.copy():
            # Wait for disconnection
            disc_event = self.wait_event(EventConnectionClosed)
            for conn_close in self.connection_list.copy():
                if conn_close.connection_handle == disc_event.connection_handle:
                    self.connection_list.remove(conn_close)
            print(f'Connection closed. {len(self.connection_list)} tags left.')


        print('Close PAwR')
        self.lib.pawr_enable(pawr_handle, False)
        self.wait_event(EventPawrStatus)
        self.lib.pawr_remove(pawr_handle)

        # Display timing info
        time_total = time_past_end - time_connect_begin
        time_connect = time_connect_end - time_connect_begin
        time_info = time_info_end - time_info_begin
        time_it = time_it_end - time_it_begin
        time_config = time_config_end - time_config_begin
        time_past = time_past_end - time_past_begin
        print('----------- < Summary > -----------------')
        print(f'Tag count           = {tag_count} tag. ')
        print(f'Total time          = {time_total.total_seconds() / tag_count} s / tag. ')
        print(f'Connection time     = {time_connect.total_seconds() / tag_count} s / tag. ')
        print(f'Tag info time       = {time_info.total_seconds() / tag_count} s / tag. ')
        print(f'Image transfer time = {time_it.total_seconds() / tag_count} s / tag. ')
        print(f'Config time         = {time_config.total_seconds() / tag_count} s / tag. ')
        print(f'PAST time           = {time_past.total_seconds() / tag_count} s / tag. ')
        print('-----------------------------------------')

    def test_api(self):
        '''Test sequence for public API'''
        pawr_handle = self.lib.pawr_create()
        print(f'{pawr_handle:#x}')
        self.lib.pawr_configure(pawr_handle)
        self.lib.get_pawr_status(pawr_handle)
        self.wait_event(EventPawrStatus)
        self.lib.pawr_enable(pawr_handle)
        self.wait_event(EventPawrStatus)
        self.lib.get_scan_status()
        self.wait_event(EventScanStatus)
        self.lib.scan_enable()
        self.wait_event(EventScanStatus)
        tag_found = self.wait_event(EventTagFound)
        self.lib.scan_enable(False)
        print(f'connect to {tag_found.address}')
        self.lib.connect(tag_found.address)
        self.wait_event(EventBondingData)
        conn = self.wait_event(EventConnectionOpened,30)
        gattdb_handles = conn.gattdb_handles
        self.lib.close_connection(conn.connection_handle)
        self.wait_event(EventConnectionClosed)
        # Reconnect with known GATT handles
        print(f'reconnect to {conn.address}')
        self.lib.connect(conn.address, gattdb=gattdb_handles)
        # Save bondig data
        bonding_data = self.wait_event(EventBondingData)
        conn = self.wait_event(EventConnectionOpened,60)
        self.lib.get_tag_info(conn.connection_handle)
        self.wait_event(EventTagInfo)
        tlv_data = {elw.ESL_LIB_DATA_TYPE_GATT_ESL_ADDRESS: bytes.fromhex("0000"),
                    elw.ESL_LIB_DATA_TYPE_GATT_AP_SYNC_KEY: bytes.fromhex("5ba4a65cae2fac6d725888c7795b82608c4bd1a769756482"),
                    elw.ESL_LIB_DATA_TYPE_GATT_RESPONSE_KEY: bytes.fromhex("e3637ad2aab72e59131e0b21e03230edce44a2e93dfecdb1"),
                    elw.ESL_LIB_DATA_TYPE_GATT_CURRENT_TIME: bytes.fromhex("00000000")}
        self.lib.configure_tag(conn.connection_handle, tlv_data)
        self.wait_event(EventConfigureTagResponse)
        self.wait_event(EventConfigureTagResponse)
        self.wait_event(EventConfigureTagResponse)
        self.wait_event(EventConfigureTagResponse)
        # Check OTS for Image Transfer
        if conn.gattdb_handles.services.ots != elw.ESL_LIB_INVALID_SERVICE_HANDLE:
            self.lib.get_image_type(conn.connection_handle, 1)
            self.wait_event(EventImageType)
            image = self.image
            self.lib.write_image(conn.connection_handle, 0, bytes(image))
            self.wait_event(EventImageTransferFinished)
            # Send display image 0 to CP
            display_image = bytes.fromhex("20000000")
            self.lib.write_control_point(conn.connection_handle, display_image)
            self.wait_event(EventControlPointResponse)
            self.wait_event(EventControlPointNotification)
        # Send Update complete to CP
        update_complete = bytes.fromhex("0400")
        self.lib.write_control_point(conn.connection_handle, update_complete)
        self.wait_event(EventControlPointResponse)
        # Initiate past
        self.lib.initiate_past(conn.connection_handle,pawr_handle)
        self.wait_event(EventConnectionClosed)
        for _ in range(5):
            self.wait_event(EventPawrDataRequest, 20, lambda x : (x.subevent_start + 3) % 28 < 4)
            print("Time to set PAwR data")
            # Send PAwR data
            self.lib.pawr_set_data(pawr_handle, 0, bytes.fromhex("0f31008533f1f2410668b95a86648b5f"))
            self.wait_event(EventPawrResponse)
        # Connect again throug PAwR
        pawr_subevent = PAWRSubevent(pawr_handle, 0)
        print(f'Reconnect to {tag_found.address} using {pawr_subevent} and key {bonding_data.ltk}')
        self.lib.connect(tag_found.address,
                         pawr_subevent,
                         gattdb=gattdb_handles,
                         key_type=elw.ESL_LIB_KEY_TYPE_LTK,
                         key=bonding_data.ltk)
        conn = self.wait_event(EventConnectionOpened)
        # Read tag info again
        self.lib.get_tag_info(conn.connection_handle)
        self.wait_event(EventTagInfo)
        # Unassociate
        unassociate = bytearray.fromhex("0100")
        self.lib.write_control_point(conn.connection_handle, unassociate)
        self.wait_event(EventControlPointResponse)
        self.wait_event(EventControlPointNotification)
        self.wait_event(EventConnectionClosed)
        # Disable PAwR
        self.lib.pawr_enable(pawr_handle, False)
        self.wait_event(EventPawrStatus)
        self.lib.pawr_remove(pawr_handle)

    def test_ap_control(self):
        '''Test sequence for AP control'''
        # Init GATT database
        self.lib.general_command(100)
        # Enable advertising
        self.lib.general_command(101, b'\x01')
        print('wait for client to connect')
        # Wait for status change (connection, notification)
        self.wait_event(EventGeneral, 120)
        print('wait for client to enable notifications to CP and IT')
        self.wait_event(EventGeneral, 120)
        # Disable advertising
        self.lib.general_command(101, b'\x00')
        # Control point response
        self.lib.general_command(102, b'CP test')
        # Image transfer response
        self.lib.general_command(103, b'IT test')
        # Wait 2 messages
        print('wait for client to send data to CP and IT')
        self.wait_event(EventGeneral, 120)
        self.wait_event(EventGeneral, 120)

def test(args):
    '''Test main entry point'''
    ap_logger.level = ap_logger.LEVELS['DEBUG']
    lib = LibTest(' '.join(args))
    lib.run()

if __name__ == '__main__':
    print('main pid:', os.getpid())
    test(sys.argv[1:])
