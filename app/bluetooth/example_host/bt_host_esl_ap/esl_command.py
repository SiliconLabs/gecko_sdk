"""
ESL Command class.
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
from ap_constants import *
from ap_logger import getLogger
from datetime import datetime as dt

class ESLCommand():
    """ Class that encapsulates synchronization packet commands """
    def __init__(self, params, group_id, slot_num):
        self.opcode = params[0]
        self.esl_id = params[1]
        self.group_id = group_id
        self.slot_number = slot_num
        self.timestamp = dt.now().timestamp()
        self.params = params
        self.response_opcode = []
        self.calculate_expected_response()

    # Logger
    @property
    def log(self):
        return getLogger("CMD")

    def calculate_expected_response(self):
        """ Calculate possible response opcodes """
        if self.opcode == TLV_OPCODE_PING:
            self.response_opcode = [TLV_RESPONSE_BASIC_STATE]
        elif self.opcode == TLV_OPCODE_UNASSOCIATE:
            self.response_opcode = [TLV_RESPONSE_BASIC_STATE, TLV_RESPONSE_ERROR]
        elif self.opcode == TLV_OPCODE_SERVICE_RST:
            self.response_opcode = [TLV_RESPONSE_BASIC_STATE, TLV_RESPONSE_ERROR]
        elif self.opcode == TLV_OPCODE_FACTORY_RST:
            self.response_opcode = [TLV_RESPONSE_ERROR] # No expected response but can be INVALID_STATE error in Synchronized state
        elif self.opcode == TLV_OPCODE_UPDATE_COMPLETE:
            self.response_opcode = [TLV_RESPONSE_ERROR] # No expected response - but old ESLs may response 'Invalid Opcode error', or can be INVALID_STATE error in Synchronized state
        elif self.opcode == TLV_OPCODE_READ_SENSOR:
            # For sensor response opcode, only the lower 4 bit is used (0x_E)
            self.response_opcode = [TLV_RESPONSE_READ_SENSOR, TLV_RESPONSE_ERROR]
        elif self.opcode == TLV_OPCODE_REFRESH_DISPLAY:
            self.response_opcode = [TLV_RESPONSE_DISPLAY_STATE, TLV_RESPONSE_ERROR]
        elif self.opcode == TLV_OPCODE_DISPLAY_IMAGE:
            self.response_opcode = [TLV_RESPONSE_DISPLAY_STATE, TLV_RESPONSE_ERROR]
        elif self.opcode == TLV_OPCODE_DISPLAY_TIMED_IMAGE:
            self.response_opcode = [TLV_RESPONSE_DISPLAY_STATE, TLV_RESPONSE_ERROR]
        elif self.opcode == TLV_OPCODE_LED_CONTROL:
            self.response_opcode = [TLV_RESPONSE_LED_STATE, TLV_RESPONSE_ERROR]
        elif self.opcode == TLV_OPCODE_LED_TIMED_CONTROL:
            self.response_opcode = [TLV_RESPONSE_LED_STATE, TLV_RESPONSE_ERROR]
        elif self.opcode == TLV_OPCODE_SILABS_SKIP_SET:
            # For Silabs specific response example
            self.response_opcode = [TLV_RESPONSE_SILABS_SKIP, TLV_RESPONSE_ERROR]
        elif self.opcode & TLV_OPCODE_VENDOR_SPECIFIC == TLV_OPCODE_VENDOR_SPECIFIC:
            # For other (probably unknown) vendor specific response, only the lower 4 bit is used (0x_F)
            self.response_opcode = [TLV_RESPONSE_VENDOR_SPECIFIC, TLV_RESPONSE_ERROR]

    def opcode_valid(self, opcode):
        """ Check if response opcode is valid """
        valid = False
        if (opcode & 0x0F) == TLV_RESPONSE_READ_SENSOR:
            valid = True
        elif (opcode & 0x0F) == TLV_OPCODE_VENDOR_SPECIFIC:
            valid = True
        elif opcode in self.response_opcode:
            self.log.debug("Expected response received: 0x%02x", opcode)
            valid = True
        if not valid:
            self.log.warning("Unexpected response received: %d - expected: %s!", opcode, self.response_opcode)
        return valid

    def __str__(self):
        """ Command information """
        ret = "ESL command:\n"
        ret += f"opcode:      {self.opcode:#x}\n"
        ret += f"esl_id:      {self.esl_id}\n"
        ret += f"group_id:    {self.group_id}\n"
        ret += f"slot_number: {self.slot_number}\n"
        ret += f"timestamp:   {dt.fromtimestamp(self.timestamp).strftime('%d/%b %H:%M:%S.%f')[:-3]}\n"
        ret += f"params:      {self.params.hex()}"
        return ret
