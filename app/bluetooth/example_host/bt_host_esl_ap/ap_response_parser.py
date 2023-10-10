"""
ESL AP response parser.
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
from ap_logger import getLogger,log
from ap_sensor import SensorResponseParser

class ResponseParser():
    def __init__(self, data, sensor_info):
        """ Parser class for ESL response
            input:
                - data: ESL response data
                - sensor_info: ESL tag sensor information
        """
        if data[0] == TLV_RESPONSE_ERROR:
            self.process_error_response(data)
        elif data[0] == TLV_RESPONSE_LED_STATE:
            self.process_led_state_response(data)
        elif data[0] == TLV_RESPONSE_BASIC_STATE:
            self.process_basic_state_response(data)
        elif data[0] == TLV_RESPONSE_DISPLAY_STATE:
            self.process_display_state_response(data)
        elif data[0] == TLV_RESPONSE_SILABS_SKIP:
            # Silabs vendor specific example
            self.process_silabs_skip_response(data)
        elif (data[0] & 0x0F) == TLV_RESPONSE_READ_SENSOR:
            # Mask upper 4 bit because sensor response can have vendor-specific values
            SensorResponseParser(data, sensor_info)
        else:
            self.log.warning("Unspecified response received" + " (0x" + str(data.hex()) + ")")

    # Logger
    @property
    def log(self):
        return getLogger("RSP")

    def process_error_response(self, data):
        """ Process error response """
        resp_param = data[1]
        if resp_param in ERROR_RESPONSE_STRINGS:
            if resp_param == ERROR_RESPONSE_RETRY:
                self.log.warning(RESPONSE_STRINGS[TLV_RESPONSE_ERROR] + ": " \
                                 + ERROR_RESPONSE_STRINGS[resp_param] + " (0x" + str(data.hex()) + ")")
            else:
                self.log.error(RESPONSE_STRINGS[TLV_RESPONSE_ERROR] + ": " \
                               + ERROR_RESPONSE_STRINGS[resp_param] + " (0x" + str(data.hex()) + ")")
        else:
            self.log.warning("Unspecified or vendor-specific error code" + " (0x" + str(data.hex()) + ")")

    def process_led_state_response(self, data):
        """ Process LED state response """
        self.log.info("Led State Response received")
        log(RESPONSE_STRINGS[TLV_RESPONSE_LED_STATE] + ": LED_Index: " \
                    + str(data[1]) + " (0x" + str(data.hex()) + ")")

    def process_basic_state_response(self, data):
        """ Process basic state response """
        self.log.info("Basic State Response received")
        bs_bitmap = int.from_bytes(data[1:], byteorder="little")
        bs_string = ", ".join([value for key, value in BASIC_STATE_STRINGS.items() if bs_bitmap & key])
        if len(bs_string) == 0:
            bs_string = "No Basic State flag is set"
        log(RESPONSE_STRINGS[TLV_RESPONSE_BASIC_STATE] + ": " + bs_string \
                    + " (0x" + str(data.hex()) + ")")

    def process_display_state_response(self, data):
        """ Process display state response """
        self.log.info("Display State Response received")
        display_idx = data[1]
        image_idx = data[2]
        log(RESPONSE_STRINGS[TLV_RESPONSE_DISPLAY_STATE] + ": Display_Index: " \
                    + str(display_idx) + " Image_Index: " + str(image_idx) \
                    + " (0x" + str(data.hex()) + ")")

    def process_silabs_skip_response(self, data):
        """ Process Silabs Skip (vendor opcode) response """
        self.log.info("Silabs PAwR Skip Response received")
        skip_value = data[1]
        log(RESPONSE_STRINGS[TLV_RESPONSE_SILABS_SKIP] + ": " \
                    + str(skip_value))
