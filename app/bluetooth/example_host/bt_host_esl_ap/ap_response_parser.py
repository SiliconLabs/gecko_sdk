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
from ap_sensor import process_sensor_data_response

def parse_response_data(data, sensor_info, logging):
    """ Parse ESL response and sensor data
        input:
            - data: ESL response data
            - sensor_info: ESL tag sensor information
            - logging: AP logging component
    """
    if data[0] == TLV_RESPONSE_ERROR:
        process_error_response(data, logging)
    elif data[0] == TLV_RESPONSE_LED_STATE:
        process_led_state_response(data, logging)
    elif data[0] == TLV_RESPONSE_BASIC_STATE:
        process_basic_state_response(data, logging)
    elif data[0] == TLV_RESPONSE_DISPLAY_STATE:
        process_display_state_response(data, logging)
    elif data[0] == TLV_RESPONSE_SILABS_SKIP:
        # Silabs vendor specific example
        process_silabs_skip_response(data, logging)
    elif (data[0] & 0x0F) == TLV_RESPONSE_READ_SENSOR:
        # Mask upper 4 bit because sensor response can have vendor­-specific values
        process_sensor_data_response(data, sensor_info, logging)
    else:
        logging.warning("Unspecified response received" + " (0x" + str(data.hex()) + ")")

def process_error_response(data, logging):
    """ Process error response """
    resp_param = data[1]
    if resp_param in ERROR_RESPONSE_STRINGS:
        logging.warning(RESPONSE_STRINGS[TLV_RESPONSE_ERROR] + ": " \
                     + ERROR_RESPONSE_STRINGS[resp_param] + " (0x" + str(data.hex()) + ")")
    else:
        logging.warning("Unspecified or vendor-specific error code" + " (0x" + str(data.hex()) + ")")

def process_led_state_response(data, logging):
    """ Process LED state response """
    logging.info(RESPONSE_STRINGS[TLV_RESPONSE_LED_STATE] + ": LED_Index: " \
                 + str(data[1]) + " (0x" + str(data.hex()) + ")")

def process_basic_state_response(data, logging):
    """ Process basic state response """
    bs_bitmap = int.from_bytes(data[1:], byteorder="little")
    bs_string = ", ".join([value for key, value in BASIC_STATE_STRINGS.items() if bs_bitmap & key])
    if len(bs_string) == 0:
        bs_string = "No Basic State flag is set"
    logging.info(RESPONSE_STRINGS[TLV_RESPONSE_BASIC_STATE] + ": " + bs_string \
                 + " (0x" + str(data.hex()) + ")")

def process_display_state_response(data, logging):
    """ Process display state response """
    display_idx = data[1]
    image_idx = data[2]
    logging.info(RESPONSE_STRINGS[TLV_RESPONSE_DISPLAY_STATE] + ": Display_Index: " \
                 + str(display_idx) + " Image_Index: " + str(image_idx) \
                 + " (0x" + str(data.hex()) + ")")

def process_silabs_skip_response(data, logging):
    """ Process display state response """
    skip_value = data[1]
    logging.info(RESPONSE_STRINGS[TLV_RESPONSE_SILABS_SKIP] + ": " \
                 + str(skip_value))
