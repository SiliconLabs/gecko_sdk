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

import argparse
import os
import re
from string import Template

# Assigned models numbers copied from the specification pdf
SIG_MODEL_ASSIGNED_NUMBERS = """
Generic Admin Property Server 0x1011
Generic Battery Client 0x100D
Generic Battery Server 0x100C
Generic Client Property Server 0x1014
Generic Default Transition Time Client 0x1005
Generic Default Transition Time Server 0x1004
Generic Level Client 0x1003
Generic Level Server 0x1002
Generic Location Client 0x1010
Generic Location Server 0x100E
Generic Location Setup Server 0x100F
Generic Manufacturer Property Server 0x1012
Generic OnOff Client 0x1001
Generic OnOff Server 0x1000
Generic Power Level Client 0x100B
Generic Power Level Server 0x1009
Generic Power Level Setup Server 0x100A
Generic Power OnOff Client 0x1008
Generic Power OnOff Server 0x1006
Generic Power OnOff Setup Server 0x1007
Generic Property Client 0x1015
Generic User Property Server 0x1013
Light CTL Client 0x1305
Light CTL Server 0x1303
Light CTL Setup Server 0x1304
Light CTL Temperature Server 0x1306
Light HSL Client 0x1309
Light HSL Hue Server 0x130A
Light HSL Saturation Server 0x130B
Light HSL Server 0x1307
Light HSL Setup Server 0x1308
Light LC Client 0x1311
Light LC Server 0x130F
Light LC Setup Server 0x1310
Light Lightness Client 0x1302
Light Lightness Server 0x1300
Light Lightness Setup Server 0x1301
Light xyL Client 0x130E
Light xyL Server 0x130C
Light xyL Setup Server 0x130D
Scene Client 0x1205
Scene Server 0x1203
Scene Setup Server 0x1204
Scheduler Client 0x1208
Scheduler Server 0x1206
Scheduler Setup Server 0x1207
Sensor Client 0x1102
Sensor Server 0x1100
Sensor Setup Server 0x1101
Time Client 0x1202
Time Server 0x1200
Time Setup Server 0x1201
BLOB Transfer Client 0x1401
BLOB Transfer Server 0x1400
Firmware Distribution Client 0x1405
Firmware Distribution Server 0x1404
Firmware Update Client 0x1403
Firmware Update Server 0x1402
Bridge Configuration Client 0x0009
Bridge Configuration Server 0x0008
Configuration Client 0x0001
Configuration Server 0x0000
Directed Forwarding Configuration Client 0x0007
Directed Forwarding Configuration Server 0x0006
Health Client 0x0003
Health Server 0x0002
Large Composition Data Client 0x0013
Large Composition Data Server 0x0012
Mesh Private Beacon Client 0x000B
Mesh Private Beacon Server 0x000A
On-Demand Private Proxy Client 0x000D
On-Demand Private Proxy Server 0x000C
Opcodes Aggregator Client 0x0011
Opcodes Aggregator Server 0x0010
Remote Provisioning Client 0x0005
Remote Provisioning Server 0x0004
SAR Configuration Client 0x000F
SAR Configuration Server 0x000E
Solicitation PDU RPL Configuration Client 0x0015
Solicitation PDU RPL Configuration Server 0x0014
"""

VENDOR_MODEL_ASSIGNED_NUMBERS = """
Silabs Configuration Client 0x02FF 0xFFFC
Silabs Configuration Server 0x02FF 0xFFFD
"""

DEFAULT_OUT_PATH = os.path.abspath(
    os.path.join(
        os.path.dirname(__file__),
        "mdl.py",
    )
)

TEMPLATE_STR = """import enum

NAMED_MODEL_ID_TO_PRETTY_NAME = {
${id2pretty}
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

${enumvals}
"""


def enum_name(pretty_name: str):
    name = pretty_name.strip().upper()
    name = name.replace(" ", "_")
    name = name.replace("-", "_")
    return name


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Creates python NamedModelID from constant data in this script. "
        "The model name and identifier data shall be copied here from the BT Mesh "
        "specification (assigned numbers)."
    )
    parser.add_argument(
        "-o", "--out", default=DEFAULT_OUT_PATH, help="Path of generated out file."
    )
    parser.add_argument(
        "-i",
        "--indent",
        type=int,
        default=4,
        help="Indentation space count in generated file.",
    )
    args = parser.parse_args()
    models = []
    for line in SIG_MODEL_ASSIGNED_NUMBERS.split("\n"):
        line = line.strip()
        match = re.fullmatch(r"([-\w ]+)(0x[0-9a-fA-F]+)", line)
        if match:
            name = match.group(1).strip()
            model_id = int(match.group(2), 0)
            models.append({"name": name, "vendor_id": 0xFFFF, "model_id": model_id})
    for line in VENDOR_MODEL_ASSIGNED_NUMBERS.split("\n"):
        line = line.strip()
        match = re.fullmatch(r"([-\w ]+)(0x[0-9a-fA-F]+)\s+(0x[0-9a-fA-F]+)", line)
        if match:
            name = match.group(1).strip()
            vendor_id = int(match.group(2), 0)
            model_id = int(match.group(3), 0)
            models.append({"name": name, "vendor_id": vendor_id, "model_id": model_id})
    with open(args.out, mode="w") as out_file:
        template = Template(TEMPLATE_STR)
        enum_lines = []
        pretty_lines = []
        for mdl in models:
            mdl_pretty_name, vendor_id, mdl_id = (
                mdl["name"],
                mdl["vendor_id"],
                mdl["model_id"],
            )
            line = f"    {enum_name(mdl_pretty_name)} = (0x{vendor_id:04X}, 0x{mdl_id:04X})"
            enum_lines.append(line)
            line = f'    (0x{vendor_id:04X}, 0x{mdl_id:04X}): "{mdl_pretty_name}",'
            pretty_lines.append(line)
        text = template.substitute(
            enumvals="\n".join(enum_lines), id2pretty="\n".join(pretty_lines)
        )
        text = text.replace("    ", " " * args.indent)
        out_file.write(text)
        print(os.getcwd())
