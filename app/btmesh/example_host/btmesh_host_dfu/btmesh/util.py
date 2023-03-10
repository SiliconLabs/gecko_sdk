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

import dataclasses
import enum
import re
from typing import Callable, Optional

from bgapix.bglibx import BGLibExtRetryParams

UNKNOWN_VALUE_STR = "__UNKNOWN__"

# BT Mesh network PDU constants
LEGACY_NW_PDU_LEN = 29
NW_PDU_LEN_MIN = 29
NW_PDU_LEN_MAX = 227

# BT Mesh address constants
UNASSIGNED_ADDR = 0
UNICAST_ADDR_MIN = 0x0001
UNICAST_ADDR_MAX = 0x7FFF
VIRTUAL_ADDR_MIN = 0x8000
VIRTUAL_ADDR_MAX = 0xBFFF
GROUP_ADDR_MIN = 0xC000
GROUP_ADDR_MAX = 0xFFFF
MULTICAST_ADDR_MIN = VIRTUAL_ADDR_MIN
MULTICAST_ADDR_MAX = GROUP_ADDR_MAX
FIXED_GROUP_ADDR_BASE = 0xFF00
MAX_ADDR = 0xFFFF
VIRTUAL_LABEL_UUID_LEN = 16

# BT Mesh element constants
PRIM_ELEM_INDEX = 0

APPKEY_INDEX_MAX = 0xFFFF
MIN_FWID_LEN = 2
MAX_FWID_LEN = 108
MAX_FWID_VERSION_INFO_LEN = 106
COMPANY_ID_SIZE = 2
TTL_MAX = 0x7F
TTL_USE_DEFAULT = 0xFF
TTL_LOCAL_ELEMS = 0x01
PUB_CRED_NORMAL = 0
PUB_CRED_FRIENDSHIP = 1
PUB_PERIOD_MS_DISABLED = 0
PUB_PERIOD_MS_MIN = 100
PUB_PERIOD_MS_MAX = 63 * 10 * 60 * 1000
PUB_RETRANSMIT_COUNT_MAX = 7
PUB_RETRANSMIT_INT_MS_MIN = 50
PUB_RETRANSMIT_INT_MS_MAX = 1600
PUB_RETRANSMIT_INT_MS_DISABLED = 0
FW_INDEX_MAX = 0xFF

SEP_PATTERN = r"[-/:]"
INTEGER_PATTERN = r"\d+|0[bB][01]+|0[oO][0-7]+|0[xX][a-fA-F0-9]+"
INTEGER_PAIR_PATTERN = f"({INTEGER_PATTERN}){SEP_PATTERN}({INTEGER_PATTERN})"
ADDR_PATTERN = INTEGER_PATTERN
NAME_PATTERN = r"[a-zA-Z_]\w*"
UUID_PATTERN = r"[0-9a-fA-F]{32}"

ENUM_UNKNOWN_VALUE = 0xCAFEBABE

# The BT Mesh standard network PDU size belonging to non-connectable
# non-scannable advertisements
STANDARD_NETWORK_PDU_SIZE = 29
# The payload from Lower Transport Layer point of view.
# The upper layers add additional protocol overhead on top of this.
LOTP_PAYLOAD_PER_SEG_MSG = 12
LOTP_PAYLOAD_PER_UNSEG_MSG = 15
# Protocol overhead of Network Layer
# (IVI+NID) + (CTL+TTL) + SEQ + SRC + DST + NetMIC = 13 bytes
#    1      +     1     +  3  +  2  +  2  +   4    = 13 bytes
NW_MSG_PROT_OVERHEAD = 13
# Protocol overhead of Lower Transport Layer
# (SEG+AID+AKF) = 1 byte
LOTP_UNSEG_MSG_PROT_OVERHEAD = 1
# Protocol overhead of Upper Transport Layer: TransMIC (4 bytes)
UPTP_PROT_OVERHEAD = 4


@dataclasses.dataclass
class BtmeshRetryParams(BGLibExtRetryParams):
    retry_interval_lpn: Optional[float]

    def to_dict(self):
        return dataclasses.asdict(self)

    def to_base(self, use_interval_lpn: bool = False):
        if use_interval_lpn:
            retry_interval = self.retry_interval_lpn
        else:
            retry_interval = self.retry_interval
        return BGLibExtRetryParams(
            retry_max=self.retry_max,
            retry_interval=retry_interval,
            retry_cmd_max=self.retry_cmd_max,
            retry_cmd_interval=self.retry_cmd_interval,
        )

    def to_base_dict(self, use_interval_lpn: bool = False):
        return self.to_base(use_interval_lpn).to_dict()

    def __post_init__(self):
        super().__post_init__()
        if self.retry_interval_lpn is None:
            self.retry_interval_lpn = self.retry_interval
        if self.retry_interval_lpn < 0.0:
            raise ValueError(f"The retry interval LPN is negative.")


class BtmeshIntEnum(enum.IntEnum):
    @classmethod
    def from_int(cls, value):
        try:
            return cls(value)
        except ValueError:
            return cls(ENUM_UNKNOWN_VALUE)

    @property
    def pretty_name(self) -> str:
        return self.to_pretty_name()

    def to_pretty_name(self, sep: str = " ", prettifier: Callable = str.lower) -> str:
        return pretty_name(self.name, sep=sep, prettifier=prettifier)


class BtmeshIntFlag(enum.IntFlag):
    @classmethod
    def from_int(cls, value):
        return cls(value)

    @property
    def pretty_name(self) -> str:
        return self.to_pretty_name()

    def to_pretty_name(self, sep: str = " ", prettifier: Callable = str.lower) -> str:
        return pretty_name(self.name, sep=sep, prettifier=prettifier)


def join_text_lines(text):
    return re.sub(r"\s\s*", " ", text).strip()


def unknown_value(value):
    return UNKNOWN_VALUE_STR + f" ({value})"


def is_iterable(obj):
    return hasattr(obj, "__iter__") or hasattr(obj, "__getitem__")


def bytes_to_int_list(b: bytes, n: int, byteorder="little"):
    assert n != 0
    if len(b) % n != 0:
        raise ValueError(
            f"The length of bytes ({len(b)}) shall be "
            f"divisible by integer size ({n})."
        )
    byte_chunks = (b[i : i + n] for i in range(0, len(b), n))
    int_list = []
    for chunk in byte_chunks:
        value = int.from_bytes(chunk, byteorder="little")
        int_list.append(value)
    return int_list


def pretty_name(name: str, sep: str = " ", prettifier: Callable = str.lower):
    ABBREVIATIONS = set(("BLOB", "FW", "FWID", "ID", "URI"))
    name_parts = []
    for part in name.split("_"):
        if part in ABBREVIATIONS:
            name_parts.append(part.upper())
        else:
            name_parts.append(prettifier(part))
    return " ".join(name_parts)


def validation_error_msg(error_msg, error_hint, add_hint):
    sep = " " if error_msg else ""
    if add_hint:
        final_error_msg = f"{error_msg}{sep}{error_hint}"
    else:
        final_error_msg = f"{error_msg}"
    return final_error_msg


def addr_to_int(addr):
    if isinstance(addr, int):
        return addr
    elif isinstance(addr, str):
        if re.fullmatch(ADDR_PATTERN, addr):
            return int(addr, 0)
        else:
            return None
    else:
        raise TypeError("Address can be constructed from str and int only.")


def is_nw_pdu_size_valid(nw_pdu_size):
    return NW_PDU_LEN_MIN <= nw_pdu_size <= NW_PDU_LEN_MAX


def validate_nw_pdu_size(nw_pdu_size, error_msg="", add_hint=True):
    if not is_nw_pdu_size_valid(nw_pdu_size):
        error_hint = (
            f"Network PDU size shall be in [{NW_PDU_LEN_MIN},{NW_PDU_LEN_MAX}] "
            f"range but it is {nw_pdu_size}."
        )
        err_text = validation_error_msg(error_msg, error_hint, add_hint)
        raise ValueError(err_text)


def is_address_valid(
    addr,
    unassigned=True,
    unicast=True,
    virtual=True,
    group_general=True,
    group_fixed=True,
):
    addr = addr_to_int(addr)
    if addr is None:
        return False
    return (
        (unassigned and is_unassigned_address(addr))
        or (unicast and is_unicast_address(addr))
        or (virtual and is_virtual_address(addr))
        or (group_general and is_general_group_address(addr))
        or (group_fixed and is_fixed_group_address(addr))
    )


def is_unassigned_address(addr):
    addr = addr_to_int(addr)
    if addr is None:
        return False
    return addr == UNASSIGNED_ADDR


def is_unicast_address(addr):
    addr = addr_to_int(addr)
    if addr is None:
        return False
    return UNICAST_ADDR_MIN <= addr <= UNICAST_ADDR_MAX


def is_multicast_address(addr):
    addr = addr_to_int(addr)
    if addr is None:
        return False
    return is_virtual_address(addr) or is_group_address(addr)


def validate_unicast_address(addr, error_msg="", add_hint=True):
    if not is_unicast_address(addr):
        error_hint = (
            f"Unicast address shall be in [0x{UNICAST_ADDR_MIN:04X},"
            f"0x{UNICAST_ADDR_MAX:04X}] range but it is {addr}."
        )
        err_text = validation_error_msg(error_msg, error_hint, add_hint)
        raise ValueError(err_text)


def validate_multicast_address(addr, error_msg="", add_hint=True):
    if not is_multicast_address(addr):
        error_hint = (
            f"Multicast address shall be in [0x{MULTICAST_ADDR_MIN:04X},"
            f"0x{MULTICAST_ADDR_MAX:04X}] range but it is {addr}."
        )
        err_text = validation_error_msg(error_msg, error_hint, add_hint)
        raise ValueError(err_text)


def is_virtual_address(addr):
    addr = addr_to_int(addr)
    if addr is None:
        return False
    return VIRTUAL_ADDR_MIN <= addr < VIRTUAL_ADDR_MAX


def is_group_address(addr):
    addr = addr_to_int(addr)
    if addr is None:
        return False
    return GROUP_ADDR_MIN <= addr <= GROUP_ADDR_MAX


def validate_group_address(addr, error_msg="", add_hint=True):
    if not is_group_address(addr):
        error_hint = (
            f"Group address shall be in [0x{GROUP_ADDR_MIN:04X},"
            f"0x{GROUP_ADDR_MAX:04X}] range but it is {addr}."
        )
        err_text = validation_error_msg(error_msg, error_hint, add_hint)
        raise ValueError(err_text)


def is_general_group_address(addr):
    addr = addr_to_int(addr)
    if addr is None:
        return False
    return GROUP_ADDR_MIN <= addr < FIXED_GROUP_ADDR_BASE


def is_fixed_group_address(addr):
    addr = addr_to_int(addr)
    if addr is None:
        return False
    return FIXED_GROUP_ADDR_BASE <= addr <= MAX_ADDR


def is_virtual_label_uuid_valid(label_uuid: bytes):
    return isinstance(label_uuid, bytes) and (len(label_uuid) == VIRTUAL_LABEL_UUID_LEN)


def validate_virtual_label_uuid(label_uuid: bytes, error_msg="", add_hint=True):
    if not is_virtual_label_uuid_valid(label_uuid):
        error_hint = (
            f"Virtual address label UUID shall be {VIRTUAL_LABEL_UUID_LEN} bytes"
            f"long binary data but it is {label_uuid}."
        )
        err_text = validation_error_msg(error_msg, error_hint, add_hint)
        raise ValueError(err_text)


def is_appkey_index_valid(appkey_index):
    return 0 <= appkey_index <= APPKEY_INDEX_MAX


def validate_appkey_index(appkey_index, error_msg="", add_hint=True):
    if not is_appkey_index_valid(appkey_index):
        error_hint = (
            f"Appkey index shall be in [0,0x{APPKEY_INDEX_MAX:03x}] range "
            f"but it is {appkey_index}."
        )
        err_text = validation_error_msg(error_msg, error_hint, add_hint)
        raise ValueError(err_text)


def is_company_id_valid(cid):
    return 0 <= cid <= 0xFFFF


def validate_company_id(cid, error_msg="", add_hint=True):
    if not is_company_id_valid(cid):
        error_hint = f"Company ID shall be in [0,0xFFFF] range but it is 0x{cid:04X}."
        err_text = validation_error_msg(error_msg, error_hint, add_hint)
        raise ValueError(err_text)


def is_fwid_version_info_valid(version_info):
    if not isinstance(version_info, bytes):
        raise TypeError(
            f"The FWID version info shall be bytes but "
            f"it is {version_info.__class__.__name__}."
        )
    return len(version_info) <= MAX_FWID_VERSION_INFO_LEN


def validate_fwid_version_info(version_info, error_msg="", add_hint=True):
    if not is_fwid_version_info_valid(version_info):
        error_hint = (
            f"FWID version info shall not be longer than {MAX_FWID_VERSION_INFO_LEN} "
            f"but it is {len(version_info)} bytes."
        )
        err_text = validation_error_msg(error_msg, error_hint, add_hint)
        raise ValueError(err_text)


def is_raw_fwid_valid(fwid_bytes):
    if not isinstance(fwid_bytes, bytes):
        raise TypeError(
            f"The raw FWID shall have bytes type but "
            f"it is {fwid_bytes.__class__.__name__}."
        )
    return MIN_FWID_LEN <= len(fwid_bytes) <= MAX_FWID_LEN


def validate_raw_fwid(fwid_bytes, error_msg="", add_hint=True):
    if not is_raw_fwid_valid(fwid_bytes):
        error_hint = (
            f"The length of raw FWID shall be in [{MIN_FWID_LEN},{MAX_FWID_LEN}] "
            f"range but it is {len(fwid_bytes)} bytes."
        )
        err_text = validation_error_msg(error_msg, error_hint, add_hint)
        raise ValueError(err_text)


def is_ttl_valid(ttl):
    return (ttl == 0) or (2 <= ttl < TTL_MAX) or (ttl == TTL_USE_DEFAULT)


def validate_ttl(ttl, error_msg="", add_hint=True):
    if not is_ttl_valid(ttl):
        error_hint = (
            f"The TTL shall be 0 or in [2,0x{TTL_MAX:02x}] range or "
            f"it shall be {TTL_USE_DEFAULT} but it is {ttl}."
        )
        err_text = validation_error_msg(error_msg, error_hint, add_hint)
        raise ValueError(err_text)


def is_pub_credentials_valid(cred):
    return cred in (PUB_CRED_NORMAL, PUB_CRED_FRIENDSHIP)


def validate_pub_credentials(cred, error_msg="", add_hint=True):
    if not is_pub_credentials_valid(cred):
        error_hint = (
            f"The publication credential shall be 0 (normal) or 1 (friendship) "
            f"but it is {cred}."
        )
        err_text = validation_error_msg(error_msg, error_hint, add_hint)
        raise ValueError(err_text)


def is_pub_period_ms_valid(period_ms):
    return (period_ms == PUB_PERIOD_MS_DISABLED) or (
        (PUB_PERIOD_MS_MIN <= period_ms <= PUB_PERIOD_MS_MAX)
    )


def validate_pub_period_ms(period_ms, error_msg="", add_hint=True):
    if not is_pub_period_ms_valid(period_ms):
        error_hint = (
            f"The publication period (ms) shall be in [{PUB_PERIOD_MS_MIN},"
            f"{PUB_PERIOD_MS_MAX}] range or it shall be {PUB_PERIOD_MS_DISABLED} "
            f"but it is {period_ms}."
        )
        err_text = validation_error_msg(error_msg, error_hint, add_hint)
        raise ValueError(err_text)


def is_pub_retransmit_count_valid(pub_retransmit_count):
    return 0 <= pub_retransmit_count <= PUB_RETRANSMIT_COUNT_MAX


def validate_pub_retransmit_count(pub_retransmit_count, error_msg="", add_hint=True):
    if not is_pub_retransmit_count_valid(pub_retransmit_count):
        error_hint = (
            f"The publication retransmit count shall be in "
            f"[0,{PUB_RETRANSMIT_COUNT_MAX}] range but it is "
            f"{pub_retransmit_count}."
        )
        err_text = validation_error_msg(error_msg, error_hint, add_hint)
        raise ValueError(err_text)


def is_pub_retransmit_interval_ms_valid(retransmit_int_ms):
    return (retransmit_int_ms == PUB_RETRANSMIT_INT_MS_DISABLED) or (
        (PUB_RETRANSMIT_INT_MS_MIN <= retransmit_int_ms <= PUB_RETRANSMIT_INT_MS_MAX)
    )


def validate_pub_retransmit_interval_ms(
    pub_retransmit_int_ms, error_msg="", add_hint=True
):
    if not is_pub_retransmit_interval_ms_valid(pub_retransmit_int_ms):
        error_hint = (
            f"The publication retransmit interval (ms) shall be in "
            f"[{PUB_RETRANSMIT_INT_MS_MIN},{PUB_RETRANSMIT_INT_MS_MAX}] range "
            f"or it shall be {PUB_RETRANSMIT_INT_MS_DISABLED} "
            f"but it is {pub_retransmit_int_ms}."
        )
        err_text = validation_error_msg(error_msg, error_hint, add_hint)
        raise ValueError(err_text)


def is_name_valid(name):
    return re.fullmatch(NAME_PATTERN, name)


def validate_name(name, error_msg="", add_hint=True):
    if not is_name_valid(name):
        error_hint = (
            f"Name shall contain letter, underscore and numeric characters only"
            f'and it shall not start with a number but is is "{name}".'
        )
        err_text = validation_error_msg(error_msg, error_hint, add_hint)
        raise ValueError(err_text)


def is_uuid_valid(uuid):
    if isinstance(uuid, bytes):
        return len(uuid) == 16
    elif isinstance(uuid, str):
        return re.fullmatch(UUID_PATTERN, uuid)
    else:
        return False


def is_fw_index_valid(fw_index: int):
    return isinstance(fw_index, int) and (0 <= fw_index <= 0xFF)


def validate_fw_index(fw_index: int, error_msg="", add_hint=True):
    if not is_fw_index_valid(fw_index):
        error_hint = (
            f"Firmware index shall be in [0,0x{FW_INDEX_MAX:03x}] range "
            f"but it is {fw_index}."
        )
        err_text = validation_error_msg(error_msg, error_hint, add_hint)
        raise ValueError(err_text)


def unprov_beacon_bearer_str(bearer):
    if bearer == 0:
        return "PB-ADV"
    elif bearer == 1:
        return "PB-GATT"
    else:
        return unknown_value(bearer)


def bd_addr_type_str(addr_type):
    if addr_type == 1:
        return "Random"
    elif addr_type == 0:
        return "Public"
    else:
        return unknown_value(addr_type)


def prov_failure_reason_str(reason):
    reason2str = {
        0: "Link closed",
        1: "Invalid PDU",
        2: "Invalid PDU format",
        3: "Unexpected PDU",
        4: "Confirmation failed",
        5: "Out of resources",
        6: "Decryption failed",
        7: "Unexpected error",
        8: "Unable to assign address",
    }
    return reason2str.get(reason, unknown_value(reason))


def dfu_calc_client_timeout(timeout_base: int, ttl: int) -> float:
    return 10.0 * (timeout_base + 2) + 0.1 * ttl
