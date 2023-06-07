#!/usr/bin/env python3

import os
import queue
import sys
import threading
import time
from esl_lib import *
import ap_logger

class LibTest(threading.Thread):
    '''Tester class'''
    def __init__(self, config):
        super().__init__(daemon=True)
        self.lib = Lib(config)

    def wait_event(self, event_type, timeout=10, func=None):
        '''Wait until specific event arrives'''
        evt_prev = None
        timeout_abs = time.time() + timeout
        while True:
            try:
                evt = self.lib.event_queue.get(timeout=timeout)
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
            except queue.Empty as err:
                raise Exception(f'Error: wait {event_type.__name__} timeout') from err

    def run(self):
        '''Auto tester logic'''
        try:
            self.wait_event(EventSystemBoot)
            self.test_1()
            #self.test_2()
            self.lib.stop()
            print('test finished successfully')
        except Exception as err:
            print(err)

    def test_1(self):
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
        self.lib.close_connection(conn.connection_handle)
        self.wait_event(EventConnectionClosed)
        # Reconnect with known GATT handles
        print(f'reconnect to {conn.address}')
        self.lib.connect(conn.address, gattdb=conn.gattdb_handles)
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
            image = bytes.fromhex("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffbf5445ffffffffffffffffffffffffffab0000aafeffffffffffffffffffff7f052a82aad0ffffffffffffffffffff5fa940a85a45ffffffffffffffffffffb7008a4a5511ffffffffffffffffffff2b5551552b04fcffffffffffffffffffad88a4aa5601faffffffffffffffff7f2b25495d1500f0ffffffffffffffffff8448526b0100f0ffffffffffffffffbf529248950400c0ffffffffffffffff5f8414a12a0000c0ffffffffffffffff2f51552a01000880ffffffffffffffff1704080000800000ffffffffffffffff5729119000200000ffffffffffffffff8b02000200011000feffffffffffffffab54010000000200fcffffffffffffff55150a2800000000fcffffffffffffffd3aaa40200002000f8ffffffffffffffaaaa4a5400040802f8ffffffffffffffb5aa920a00000000f8ffffffffffffff6babaa5400000100f0ffffffffffffffaa56abaa00200000f8ffffffffffffffda6d555510040000f0ffffffffffffff6a5bdbaa02000000e0ffffffffffffffb6d6aaaa40004008e8ffffffffffffffdabdb65a00200000f0ffffffffffff7fbdd5aaa600040402e2ffffffffffffffd6b65d2d80000080f0ffffffffffffbf756d6b5501000000e0ffffffffffffffaebb5d5500200000e8ffffffffffff7ff576ab2a04000801e1ffffffffffffffadadb65581000008e8ffffffffffffbf767bad4a20200100f0ffffffffffffffddad559200002000e4ffffffffffff7f6b5fab2a00200042f0ffffffffffffffde75ad4401080800e4ffffffffffffff75abab1580000000f1ffffffffffff7fdb7e552501400204e0fffffffffffffff6d5560980000000f4ffffffffffffff5dbfb5aa02208040f0ffffffffffff7feb6a6515240a0900f2ffffffffffffffddff5a5509400010f0ffffffffffffff57d5d52a81080100f9ffffffffffff7fedbfaf4a15220004f8ffffffffffffffb76ad53642480140f8ffffffffffffffeeffb7cd14110000f9ffffffffffffff5b55ad2a494a0148fcfffffffffffffff7ffeb5625100201fcffffffffffffff5d555fad94ca0800feffffffffffffffb7ffb5ab52248290fcffffffffffffff7f556f6d95520804feffffffffffffffd7ffdd5b55a40200ffffffffffffffffbfaaab5629092940ffffffffffffffffef7f7fb54ab20089ffffffffffffffffbfeaaa6b954454c0ffffffffffffffffffdf6d5d559500c4ffffffffffffffff7fb55aab2a2a8af0ffffffffffffffffffedb5d64a4910f2ffffffffffffffffff5babad922485f8ffffffffffffffffffb75ab5264910fcffffffffffffffffff6fabaaa98284feffffffffffffffffffdf566b4a1421ffffffffffffffffffffbf5555954088ffffffffffffffffffff7fdbaa2a15e1f7ffffffffffffffffffff35555522d27effffffffffffffffff7f6b554989b8dbfbffffffffffffffffeb56555522aaf6defdffffffffffffff5fa5aa8a08a4daf7ffffffffffffff7fbb0a121040a9b67eefffffffffffffffd7524045154ad5edfffeffffffffffdfbe561588a0526dbbfdfffffffffffff76b55d52aadaadafeefefffffffffff7fdfdbaa6a55d5b66b7fffffffffffffff75adb75555adedfefbffffffffffffefff776d6fef7ab7effefbfefffffffffbdffeffbab5effdbddffffffffffffffffd6fdbefffde6ffffffffffffffffffffffb7f7fab7bfbf7fbfffffffffffffffffef7fbfffffffffefeffffffffffffbffffddffff7dfbdfffffffffffffffffffffffffdbefdffffffffffffffffffffffffffbfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff")
            self.lib.write_image(conn.connection_handle, 0, image)
            self.wait_event(EventImageTransferFinished)
            # Send display image 0 to CP
            display_image = bytes.fromhex("20000000")
            self.lib.write_control_point(conn.connection_handle, display_image)
            self.wait_event(EventControlPointResponse)
            self.wait_event(EventControlPointNotification)
        # Send Update complete to CP
        display_image = bytes.fromhex("0400")
        self.lib.write_control_point(conn.connection_handle, display_image)
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
                         gattdb=conn.gattdb_handles,
                         key_type=elw.ESL_LIB_KEY_TYPE_LTK,
                         key=bonding_data.ltk)
        conn = self.wait_event(EventConnectionOpened)
        # Read tag info again
        self.lib.get_tag_info(conn.connection_handle)
        self.wait_event(EventTagInfo)
        # Close connection
        self.lib.close_connection(conn.connection_handle)
        self.wait_event(EventConnectionClosed)
        # Disable PAwR
        self.lib.pawr_enable(pawr_handle, False)
        self.wait_event(EventPawrStatus)
        self.lib.pawr_remove(pawr_handle)

    def test_2(self):
        '''Test sequence for internal API'''
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

def test(connections):
    '''Test main entry point'''
    ap_logger.level = ap_logger.LEVELS['DEBUG']
    libs = [LibTest(connection) for connection in connections]
    for lib in libs:
        lib.start()
    for lib in libs:
        lib.join()

if __name__ == '__main__':
    print('main pid:', os.getpid())
    test(sys.argv[1:])
