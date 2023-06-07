'''
ESL Key Library
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

from ctypes import c_ubyte, byref
import esl_lib
import esl_key_lib_wrapper as eklw

class Error(Exception):
    def __init__(self, status: int):
        super().__init__(f'ESL key lib status {status:#x}')

class Lib:
    '''ESL Key Library'''
    def __init__(self, file_name='bonding.db'):
        self.key_db_handle = eklw.db_handle_p()
        status = eklw.esl_key_lib_init_database(file_name, byref(self.key_db_handle))
        if status != 0:
            raise Error(status)

    def find_ltk(self, address: esl_lib.Address):
        '''Search for Long Term Key entry for the given address'''
        key_record = eklw.db_record_p()
        ble_address = eklw.bd_addr()
        ble_address.addr = (c_ubyte * 6).from_buffer_copy(address.addr)
        status = eklw.esl_key_lib_get_record_by_ble_address(self.key_db_handle, byref(ble_address), byref(key_record))
        if status == 0:
            ltk_key_out = eklw.aes_key_128()
            status = eklw.esl_key_lib_get_long_term_key(key_record, byref(ltk_key_out))
            eklw.esl_key_lib_free_record(key_record)
            if status == 0:
                return bytes(ltk_key_out.data)
        return None

    def add_ltk(self, address: esl_lib.Address, ltk: bytes):
        '''Add new Long Term Key entry for the given address'''
        key_record = eklw.db_record_p()
        ble_address = eklw.bd_addr()
        ble_address.addr = (c_ubyte * 6).from_buffer_copy(address.addr)
        ltk_key = eklw.aes_key_128()
        ltk_key.data = (c_ubyte * 16).from_buffer_copy(ltk)
        eklw.esl_key_lib_alloc_record(eklw.ESL_KEY_LIB_TAG_RECORD, byref(key_record))
        eklw.esl_key_lib_set_long_term_key(byref(ltk_key), key_record)
        eklw.esl_key_lib_set_ble_address(byref(ble_address), key_record)
        status = eklw.esl_key_lib_store_record(self.key_db_handle, key_record)
        eklw.esl_key_lib_free_record(key_record)
        if status != 0:
            raise Error(status)

    def delete_ltk(self, address: esl_lib.Address):
        '''Delete Long Term Key entry for the given address'''
        ble_address = eklw.bd_addr()
        ble_address.addr = (c_ubyte * 6).from_buffer_copy(address.addr)
        status = eklw.esl_key_lib_delete_record_by_ble_address(self.key_db_handle, byref(ble_address))
        if status != 0:
            raise Error(status)
