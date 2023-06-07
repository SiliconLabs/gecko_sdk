"""
ESL AP Sensor.
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

from collections import namedtuple
from datetime import datetime as dt
from datetime import timedelta
from ap_constants import TLV_RESPONSE_READ_SENSOR

SENSOR_INFO_LENGTH_SHORT = 3
SENSOR_INFO_LENGTH_LONG = 5

# Supported sensor IDs
S_ID_PRESENT_INPUT_VOLTAGE                              = 0x0059    #Mesh type: Voltage
S_ID_PRESENT_DEVICE_OPERATING_TEMPERATURE               = 0x0054    #Mesh type: Temperature
S_ID_DEVICE_FIRMWARE_REVISION                           = 0x000E    #Mesh type: Fixed string 8
S_ID_DEVICE_DATE_OF_MANUFACTURE                         = 0x000C    #Mesh type: Date UTC
S_ID_DEVICE_OPERATING_TEMPERATURE_RANGE_SPECIFICATION   = 0x0013    #Mesh type: Temperature range
S_ID_PRESENT_AMBIENT_TEMPERATURE                        = 0x004F    #Mesh type: Temperature 8
S_ID_SILABS_SENSOR_1                                    = 0xCAFE02FF
S_ID_SILABS_SENSOR_BUTTON                               = 0xC0DE02FF

def sensor_type_voltage(data):
    """ Interpret sensor value based on GATT Specification Supplement:
        Type: Voltage   |   Chapter: 3.236
        Input type: uint16
        Resolution: 1/64 V
        Range: 0, 1022.0
        0xFFFF: Unknown
    """
    voltage = None
    if len(data) == 2:
        temp = int.from_bytes(data, "little")
        if temp == 0xFFFF:
            voltage = "unknown"
        else:
            voltage = temp/64
    return voltage

def sensor_type_temperature(data):
    """ Interpret sensor value based on GATT Specification Supplement:
        Type: Temperature   |   Chapter: 3.204
        Input type: sint16
        Resolution: 0.01 °C
        Range: -273.15, 327.67
        0x8000: Unknown
    """
    temperature = None
    if len(data) == 2:
        temp = int.from_bytes(data, "little", signed=True)
        if temp == -32768:              # check for special value
            temperature = "unknown"
        else:
            temperature = temp * 0.01
            if temperature < -273.15:   # boundary check
                temperature = -273.15
    return temperature

def sensor_type_temperature_range(data):
    """ Interpret sensor value based on GATT Specification Supplement:
        Type: Temperature Range |   Chapter: 3.209
        Input type: [min: sint16, max: sint16]
        Resolution: 0.01 °C
        Range: -273.15, 327.67
        0x8000: Unknown
    """
    temperature_min = sensor_type_temperature(data[0:2])
    temperature_max = sensor_type_temperature(data[2:])
    return [temperature_min, temperature_max]

def sensor_type_fixed_string_8(data):
    """ Interpret sensor value based on GATT Specification Supplement:
        Type: Fixed string 8    |   Chapter: 3.89
        Input type: uint8[8]
        Coding: UTF-8
    """
    fixed_str = None
    if len(data) == 8:
        fixed_str = data.decode("utf-8")
    return fixed_str

def sensor_type_date_utc(data):
    """ Interpret sensor value based on GATT Specification Supplement:
        Type: Date UTC  |   Chapter: 3.67
        Input type: uint24
        Resolution: 1 day, Epoch: 01.01.1970
        0x000000: Unknown
    """
    utc_date = None
    if len(data) == 3:
        temp = int.from_bytes(data, "little")
        if temp > 0:    # check for special value
            utc_date = dt(1970,1,1) + timedelta(days = temp)
            utc_date = utc_date.strftime("%d %B, %Y")
        else:
            utc_date = "unknown"
    return utc_date

def sensor_type_temperature_8(data):
    """ Interpret sensor value based on GATT Specification Supplement:
        Type: Temperature 8 |   Chapter: 3.205
        Input type: sint8
        Resolution: 0.5 °C
        Range: -64.0, 63.0
        0x7F: Unknown
    """
    temperature_8 = None
    if len(data) == 1:
        temp = int.from_bytes(data, "little", signed = True)
        if temp == -127:              # check for special value
            temperature_8 = "unknown"
        else:
            temperature_8 = temp * 0.5
    return temperature_8


def sensor_type_silabs_1(data):
    """ Interpret sensor value of silabs vendor specific sensor 1"""
    return str(data)

def sensor_type_silabs_button(data):
    """ Interpret sensor value of silabs button"""
    return data

SensorType = namedtuple("SensorType", ['from_bytes', 'desc'])

SENSOR_TYPES = {
    S_ID_PRESENT_INPUT_VOLTAGE: SensorType(sensor_type_voltage,
                                           "Present input voltage"),
    S_ID_PRESENT_DEVICE_OPERATING_TEMPERATURE: SensorType(sensor_type_temperature,
                                                          "Present device operating temperature"),
    S_ID_DEVICE_FIRMWARE_REVISION: SensorType(sensor_type_fixed_string_8,
                                              "Device firmware version"),
    S_ID_DEVICE_DATE_OF_MANUFACTURE: SensorType(sensor_type_date_utc,
                                                "Date of manufacture"),
    S_ID_DEVICE_OPERATING_TEMPERATURE_RANGE_SPECIFICATION: SensorType(sensor_type_temperature_range,
                                                                      "Device operating temperature range specification"),
    S_ID_PRESENT_AMBIENT_TEMPERATURE: SensorType(sensor_type_temperature_8,
                                                 "Present ambient temperature"),
    S_ID_SILABS_SENSOR_1: SensorType(sensor_type_silabs_1,
                                     "Silabs readout counter"),
    S_ID_SILABS_SENSOR_BUTTON: SensorType(sensor_type_silabs_button,
                                          "Silabs button")
}

def process_sensor_data_response(data: bytes, sensor_info, logging):
    """ Process and display ESL sensor data
        input:
            - data: Event data contains sensor information
            - sensor_info: ESL tag sensor information
            - logging: AP logging component
    """
    resp_code = data[0] & 0x0F
    resp_length = data[0] & 0xF0

    if resp_code == TLV_RESPONSE_READ_SENSOR:
        logging.info("Sensor data received: " + data.hex())
        if sensor_info is None:
            logging.info("Unknown sensor - raw response data: " + data.hex())
        elif data[1] < len(sensor_info):
            sensor_type = sensor_info[data[1]]
            if resp_length > 1:
                if sensor_type in SENSOR_TYPES:
                    from esl_tag import TAG_MIN_JUSTIFY_COLUMN
                    logging.print("Sensor type: " + SENSOR_TYPES[sensor_type].desc)
                    value = SENSOR_TYPES[sensor_type].from_bytes(data[2:])
                    logging.print("".ljust(TAG_MIN_JUSTIFY_COLUMN) + str(value))
                else:
                    logging.print("Sensor type " + str(sensor_type) +  " not supported")
            else:
                logging.info("No sensor data")
        else:
            logging.info("Invalid sensor type")
