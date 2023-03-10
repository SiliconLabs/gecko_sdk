# Copyright 2022 Silicon Laboratories Inc. www.silabs.com
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

import enum

NAMED_MODEL_ID_TO_PRETTY_NAME = {
    (0xFFFF, 0x1011): "Generic Admin Property Server",
    (0xFFFF, 0x100D): "Generic Battery Client",
    (0xFFFF, 0x100C): "Generic Battery Server",
    (0xFFFF, 0x1014): "Generic Client Property Server",
    (0xFFFF, 0x1005): "Generic Default Transition Time Client",
    (0xFFFF, 0x1004): "Generic Default Transition Time Server",
    (0xFFFF, 0x1003): "Generic Level Client",
    (0xFFFF, 0x1002): "Generic Level Server",
    (0xFFFF, 0x1010): "Generic Location Client",
    (0xFFFF, 0x100E): "Generic Location Server",
    (0xFFFF, 0x100F): "Generic Location Setup Server",
    (0xFFFF, 0x1012): "Generic Manufacturer Property Server",
    (0xFFFF, 0x1001): "Generic OnOff Client",
    (0xFFFF, 0x1000): "Generic OnOff Server",
    (0xFFFF, 0x100B): "Generic Power Level Client",
    (0xFFFF, 0x1009): "Generic Power Level Server",
    (0xFFFF, 0x100A): "Generic Power Level Setup Server",
    (0xFFFF, 0x1008): "Generic Power OnOff Client",
    (0xFFFF, 0x1006): "Generic Power OnOff Server",
    (0xFFFF, 0x1007): "Generic Power OnOff Setup Server",
    (0xFFFF, 0x1015): "Generic Property Client",
    (0xFFFF, 0x1013): "Generic User Property Server",
    (0xFFFF, 0x1305): "Light CTL Client",
    (0xFFFF, 0x1303): "Light CTL Server",
    (0xFFFF, 0x1304): "Light CTL Setup Server",
    (0xFFFF, 0x1306): "Light CTL Temperature Server",
    (0xFFFF, 0x1309): "Light HSL Client",
    (0xFFFF, 0x130A): "Light HSL Hue Server",
    (0xFFFF, 0x130B): "Light HSL Saturation Server",
    (0xFFFF, 0x1307): "Light HSL Server",
    (0xFFFF, 0x1308): "Light HSL Setup Server",
    (0xFFFF, 0x1311): "Light LC Client",
    (0xFFFF, 0x130F): "Light LC Server",
    (0xFFFF, 0x1310): "Light LC Setup Server",
    (0xFFFF, 0x1302): "Light Lightness Client",
    (0xFFFF, 0x1300): "Light Lightness Server",
    (0xFFFF, 0x1301): "Light Lightness Setup Server",
    (0xFFFF, 0x130E): "Light xyL Client",
    (0xFFFF, 0x130C): "Light xyL Server",
    (0xFFFF, 0x130D): "Light xyL Setup Server",
    (0xFFFF, 0x1205): "Scene Client",
    (0xFFFF, 0x1203): "Scene Server",
    (0xFFFF, 0x1204): "Scene Setup Server",
    (0xFFFF, 0x1208): "Scheduler Client",
    (0xFFFF, 0x1206): "Scheduler Server",
    (0xFFFF, 0x1207): "Scheduler Setup Server",
    (0xFFFF, 0x1102): "Sensor Client",
    (0xFFFF, 0x1100): "Sensor Server",
    (0xFFFF, 0x1101): "Sensor Setup Server",
    (0xFFFF, 0x1202): "Time Client",
    (0xFFFF, 0x1200): "Time Server",
    (0xFFFF, 0x1201): "Time Setup Server",
    (0xFFFF, 0x1401): "BLOB Transfer Client",
    (0xFFFF, 0x1400): "BLOB Transfer Server",
    (0xFFFF, 0x1405): "Firmware Distribution Client",
    (0xFFFF, 0x1404): "Firmware Distribution Server",
    (0xFFFF, 0x1403): "Firmware Update Client",
    (0xFFFF, 0x1402): "Firmware Update Server",
    (0xFFFF, 0x0009): "Bridge Configuration Client",
    (0xFFFF, 0x0008): "Bridge Configuration Server",
    (0xFFFF, 0x0001): "Configuration Client",
    (0xFFFF, 0x0000): "Configuration Server",
    (0xFFFF, 0x0007): "Directed Forwarding Configuration Client",
    (0xFFFF, 0x0006): "Directed Forwarding Configuration Server",
    (0xFFFF, 0x0003): "Health Client",
    (0xFFFF, 0x0002): "Health Server",
    (0xFFFF, 0x0013): "Large Composition Data Client",
    (0xFFFF, 0x0012): "Large Composition Data Server",
    (0xFFFF, 0x000B): "Mesh Private Beacon Client",
    (0xFFFF, 0x000A): "Mesh Private Beacon Server",
    (0xFFFF, 0x000D): "On-Demand Private Proxy Client",
    (0xFFFF, 0x000C): "On-Demand Private Proxy Server",
    (0xFFFF, 0x0011): "Opcodes Aggregator Client",
    (0xFFFF, 0x0010): "Opcodes Aggregator Server",
    (0xFFFF, 0x0005): "Remote Provisioning Client",
    (0xFFFF, 0x0004): "Remote Provisioning Server",
    (0xFFFF, 0x000F): "SAR Configuration Client",
    (0xFFFF, 0x000E): "SAR Configuration Server",
    (0xFFFF, 0x0015): "Solicitation PDU RPL Configuration Client",
    (0xFFFF, 0x0014): "Solicitation PDU RPL Configuration Server",
    (0x02FF, 0xFFFC): "Silabs Configuration Client",
    (0x02FF, 0xFFFD): "Silabs Configuration Server",
}


@enum.unique
class NamedModelID(enum.Enum):
    @classmethod
    def is_value_valid(cls, value):
        value_valid = False
        if isinstance(value, cls):
            value_valid = True
        elif isinstance(value, tuple) and len(value) == 2:
            value_valid = True
        elif isinstance(value, int):
            value_valid = True
        return value_valid

    @classmethod
    def validate_value(cls, value):
        if not cls.is_value_valid(value):
            raise ValueError(
                f"Invalid {cls.__class__.__name__} value ({type(value.__name__)})."
            )

    @classmethod
    def value_to_tuple(cls, value):
        cls.validate_value(value)
        if isinstance(value, cls):
            return value.value
        if isinstance(value, tuple) and len(value) == 2:
            return value
        if isinstance(value, int):
            return (0xFFFF, value)

    @classmethod
    def value_exist(cls, value):
        cls.validate_value(value)
        value = cls.value_to_tuple(value)
        try:
            cls(value)
        except ValueError:
            return False
        return True

    @classmethod
    def get_pretty_name(cls, value, unknown_with_value=True):
        value = cls.value_to_tuple(value)
        if unknown_with_value:
            return NAMED_MODEL_ID_TO_PRETTY_NAME.get(value, f"UNKNOWN {value}")
        else:
            return NAMED_MODEL_ID_TO_PRETTY_NAME.get(value, f"UNKNOWN")

    @staticmethod
    def gen_pretty_name_id_pairs():
        for name, id in NAMED_MODEL_ID_TO_PRETTY_NAME.items():
            yield name, id

    @staticmethod
    def gen_pretty_names():
        for pretty_name in NAMED_MODEL_ID_TO_PRETTY_NAME.values():
            yield pretty_name

    @classmethod
    def is_name_valid(cls, name, ignore_case=True):
        if ignore_case:
            return (name.upper() in cls.__members__)
        else:
            return (name in cls.__members__)

    @classmethod
    def get_name(cls, value, unknown_with_value=True):
        try:
            value = cls.value_to_tuple(value)
            return cls(value).name
        except ValueError:
            if unknown_with_value:
                return f"UNKNOWN ({value})"
            else:
                return f"UNKNOWN"

    @classmethod
    def gen_names(cls):
        for name in cls.__members__.keys():
            yield name

    @classmethod
    def gen_name_id_pairs(cls):
        for name, enum_const in cls.__members__.items():
            yield name, enum_const.value

    @classmethod
    def get_id_by_name(cls, name, ignore_case=True):
        name = name.upper() if ignore_case else name
        return cls.__members__[name.upper()]

    @property
    def pretty_name(self):
        return NAMED_MODEL_ID_TO_PRETTY_NAME.get(self.value)

    GENERIC_ADMIN_PROPERTY_SERVER = (0xFFFF, 0x1011)
    GENERIC_BATTERY_CLIENT = (0xFFFF, 0x100D)
    GENERIC_BATTERY_SERVER = (0xFFFF, 0x100C)
    GENERIC_CLIENT_PROPERTY_SERVER = (0xFFFF, 0x1014)
    GENERIC_DEFAULT_TRANSITION_TIME_CLIENT = (0xFFFF, 0x1005)
    GENERIC_DEFAULT_TRANSITION_TIME_SERVER = (0xFFFF, 0x1004)
    GENERIC_LEVEL_CLIENT = (0xFFFF, 0x1003)
    GENERIC_LEVEL_SERVER = (0xFFFF, 0x1002)
    GENERIC_LOCATION_CLIENT = (0xFFFF, 0x1010)
    GENERIC_LOCATION_SERVER = (0xFFFF, 0x100E)
    GENERIC_LOCATION_SETUP_SERVER = (0xFFFF, 0x100F)
    GENERIC_MANUFACTURER_PROPERTY_SERVER = (0xFFFF, 0x1012)
    GENERIC_ONOFF_CLIENT = (0xFFFF, 0x1001)
    GENERIC_ONOFF_SERVER = (0xFFFF, 0x1000)
    GENERIC_POWER_LEVEL_CLIENT = (0xFFFF, 0x100B)
    GENERIC_POWER_LEVEL_SERVER = (0xFFFF, 0x1009)
    GENERIC_POWER_LEVEL_SETUP_SERVER = (0xFFFF, 0x100A)
    GENERIC_POWER_ONOFF_CLIENT = (0xFFFF, 0x1008)
    GENERIC_POWER_ONOFF_SERVER = (0xFFFF, 0x1006)
    GENERIC_POWER_ONOFF_SETUP_SERVER = (0xFFFF, 0x1007)
    GENERIC_PROPERTY_CLIENT = (0xFFFF, 0x1015)
    GENERIC_USER_PROPERTY_SERVER = (0xFFFF, 0x1013)
    LIGHT_CTL_CLIENT = (0xFFFF, 0x1305)
    LIGHT_CTL_SERVER = (0xFFFF, 0x1303)
    LIGHT_CTL_SETUP_SERVER = (0xFFFF, 0x1304)
    LIGHT_CTL_TEMPERATURE_SERVER = (0xFFFF, 0x1306)
    LIGHT_HSL_CLIENT = (0xFFFF, 0x1309)
    LIGHT_HSL_HUE_SERVER = (0xFFFF, 0x130A)
    LIGHT_HSL_SATURATION_SERVER = (0xFFFF, 0x130B)
    LIGHT_HSL_SERVER = (0xFFFF, 0x1307)
    LIGHT_HSL_SETUP_SERVER = (0xFFFF, 0x1308)
    LIGHT_LC_CLIENT = (0xFFFF, 0x1311)
    LIGHT_LC_SERVER = (0xFFFF, 0x130F)
    LIGHT_LC_SETUP_SERVER = (0xFFFF, 0x1310)
    LIGHT_LIGHTNESS_CLIENT = (0xFFFF, 0x1302)
    LIGHT_LIGHTNESS_SERVER = (0xFFFF, 0x1300)
    LIGHT_LIGHTNESS_SETUP_SERVER = (0xFFFF, 0x1301)
    LIGHT_XYL_CLIENT = (0xFFFF, 0x130E)
    LIGHT_XYL_SERVER = (0xFFFF, 0x130C)
    LIGHT_XYL_SETUP_SERVER = (0xFFFF, 0x130D)
    SCENE_CLIENT = (0xFFFF, 0x1205)
    SCENE_SERVER = (0xFFFF, 0x1203)
    SCENE_SETUP_SERVER = (0xFFFF, 0x1204)
    SCHEDULER_CLIENT = (0xFFFF, 0x1208)
    SCHEDULER_SERVER = (0xFFFF, 0x1206)
    SCHEDULER_SETUP_SERVER = (0xFFFF, 0x1207)
    SENSOR_CLIENT = (0xFFFF, 0x1102)
    SENSOR_SERVER = (0xFFFF, 0x1100)
    SENSOR_SETUP_SERVER = (0xFFFF, 0x1101)
    TIME_CLIENT = (0xFFFF, 0x1202)
    TIME_SERVER = (0xFFFF, 0x1200)
    TIME_SETUP_SERVER = (0xFFFF, 0x1201)
    BLOB_TRANSFER_CLIENT = (0xFFFF, 0x1401)
    BLOB_TRANSFER_SERVER = (0xFFFF, 0x1400)
    FIRMWARE_DISTRIBUTION_CLIENT = (0xFFFF, 0x1405)
    FIRMWARE_DISTRIBUTION_SERVER = (0xFFFF, 0x1404)
    FIRMWARE_UPDATE_CLIENT = (0xFFFF, 0x1403)
    FIRMWARE_UPDATE_SERVER = (0xFFFF, 0x1402)
    BRIDGE_CONFIGURATION_CLIENT = (0xFFFF, 0x0009)
    BRIDGE_CONFIGURATION_SERVER = (0xFFFF, 0x0008)
    CONFIGURATION_CLIENT = (0xFFFF, 0x0001)
    CONFIGURATION_SERVER = (0xFFFF, 0x0000)
    DIRECTED_FORWARDING_CONFIGURATION_CLIENT = (0xFFFF, 0x0007)
    DIRECTED_FORWARDING_CONFIGURATION_SERVER = (0xFFFF, 0x0006)
    HEALTH_CLIENT = (0xFFFF, 0x0003)
    HEALTH_SERVER = (0xFFFF, 0x0002)
    LARGE_COMPOSITION_DATA_CLIENT = (0xFFFF, 0x0013)
    LARGE_COMPOSITION_DATA_SERVER = (0xFFFF, 0x0012)
    MESH_PRIVATE_BEACON_CLIENT = (0xFFFF, 0x000B)
    MESH_PRIVATE_BEACON_SERVER = (0xFFFF, 0x000A)
    ON_DEMAND_PRIVATE_PROXY_CLIENT = (0xFFFF, 0x000D)
    ON_DEMAND_PRIVATE_PROXY_SERVER = (0xFFFF, 0x000C)
    OPCODES_AGGREGATOR_CLIENT = (0xFFFF, 0x0011)
    OPCODES_AGGREGATOR_SERVER = (0xFFFF, 0x0010)
    REMOTE_PROVISIONING_CLIENT = (0xFFFF, 0x0005)
    REMOTE_PROVISIONING_SERVER = (0xFFFF, 0x0004)
    SAR_CONFIGURATION_CLIENT = (0xFFFF, 0x000F)
    SAR_CONFIGURATION_SERVER = (0xFFFF, 0x000E)
    SOLICITATION_PDU_RPL_CONFIGURATION_CLIENT = (0xFFFF, 0x0015)
    SOLICITATION_PDU_RPL_CONFIGURATION_SERVER = (0xFFFF, 0x0014)
    SILABS_CONFIGURATION_CLIENT = (0x02FF, 0xFFFC)
    SILABS_CONFIGURATION_SERVER = (0x02FF, 0xFFFD)
