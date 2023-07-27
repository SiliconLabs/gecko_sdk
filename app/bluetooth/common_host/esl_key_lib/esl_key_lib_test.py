#!/usr/bin/env python3

from ctypes import (c_ubyte,
                    byref)
import esl_key_lib

def test():
    dbhp = esl_key_lib.db_handle_p()
    s = esl_key_lib.esl_key_lib_init_database("test.db", byref(dbhp))
    if s != 0:
        raise Exception("esl_key_lib_init_database failed")

    t = esl_key_lib.ESL_KEY_LIB_TAG_RECORD
    dbrp = esl_key_lib.db_record_p()
    s = esl_key_lib.esl_key_lib_alloc_record(t, byref(dbrp))
    if s != 0:
        raise Exception("esl_key_lib_alloc_record failed")

    bta = esl_key_lib.bd_addr()
    bt_addr_t = c_ubyte * 6
    bta.addr = bt_addr_t(0, 1, 2, 3, 4, 5)
    s = esl_key_lib.esl_key_lib_set_ble_address(byref(bta), dbrp)
    if s != 0:
        raise Exception("esl_key_lib_set_ble_address failed")

    esla = esl_key_lib.esl_address_t()
    esla = 0x0102
    s = esl_key_lib.esl_key_lib_set_esl_address(esla, dbrp)
    if s != 0:
        raise Exception("esl_key_lib_set_esl_address failed")

    ltk = esl_key_lib.aes_key_128()
    ltk_t = c_ubyte * 16
    ltk.data = ltk_t(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)
    s = esl_key_lib.esl_key_lib_set_long_term_key(byref(ltk), dbrp)
    if s != 0:
        raise Exception("esl_key_lib_set_long_term_key failed")

    s = esl_key_lib.esl_key_lib_store_record(dbhp, dbrp)
    if s != 0:
        raise Exception("esl_key_lib_store_record failed")

    bta2 = esl_key_lib.bd_addr()
    bt_addr_t2 = c_ubyte * 6
    bta2.addr = bt_addr_t2(0, 1, 2, 3, 4, 5)
    dbrp2 = esl_key_lib.db_record_p()
    s = esl_key_lib.esl_key_lib_get_record_by_ble_address(dbhp, byref(bta2), byref(dbrp2))
    if s != 0:
        raise Exception("esl_key_lib_get_record_by_ble_address failed")

    dbrp3 = esl_key_lib.db_record_p()
    s = esl_key_lib.esl_key_lib_get_record_by_esl_address(dbhp, esl_key_lib.esl_address_t(0x0102), byref(dbrp3))
    if s != 0:
        raise Exception("esl_key_lib_get_record_by_esl_address failed")

    esl_key_lib.esl_key_lib_free_record(dbrp3)
    esl_key_lib.esl_key_lib_free_record(dbrp2)
    esl_key_lib.esl_key_lib_free_record(dbrp)

    s = esl_key_lib.esl_key_lib_deinit_database(dbhp)
    if s != 0:
        raise Exception("esl_key_lib_deinit_database failed")

    print("test finished successfully")

if __name__ == "__main__":
    test()
