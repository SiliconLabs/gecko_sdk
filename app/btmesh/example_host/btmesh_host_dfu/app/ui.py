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
import dataclasses
import enum
import io
import logging
import re
import sys
from typing import Dict, Iterable, List, Mapping, Sequence, Union

import btmesh.util
from btmesh.db import FWID, ModelID, Node
from btmesh.mdl import NamedModelID

from .cfg import app_cfg
from .db import BtmeshDfuAppGroup, app_db
from .util.tabletext import table_text_lines

logger = logging.getLogger(__name__)


class BtmeshDfuAppSpecName(enum.Enum):
    BDADDRSPEC = enum.auto()
    NODESPEC = enum.auto()
    ELEMSPEC = enum.auto()
    MDLSPEC = enum.auto()
    FWIDSPEC = enum.auto()
    METASPEC = enum.auto()
    GROUPSPEC = enum.auto()


class BtmeshDfuAppParseSpecError(ValueError):
    def __init__(self, msg, spec_name, spec_value):
        super().__init__(msg)
        self.msg = msg
        self.spec_name = spec_name
        self.spec_value = spec_value


@dataclasses.dataclass
class AppUIColumnInfo:
    header: str
    default: bool


class BtmeshDfuAppUI:
    SEP_PATTERN = btmesh.util.SEP_PATTERN
    TEXT_LIST_SEP = [",", ";", " "]

    NODE_COLUMNS = {
        "idx": "Idx",
        "uuid": "UUID",
        "devkey": "Device Key",
        "prim_addr": "Address",
        "elem_count": "Elements",
        "name": "Name",
        "cid": "CID",
        "pid": "PID",
        "vid": "VID",
        "crpl": "CRPL",
        "relay": "Relay",
        "proxy": "Proxy",
        "friend": "Friend",
        "lpn": "LPN",
    }

    APP_GROUP_COLUMNS = {
        "idx": AppUIColumnInfo(header="Idx", default=True),
        "name": AppUIColumnInfo(header="Name", default=True),
        "group_addr": AppUIColumnInfo(header="Group Address", default=True),
        "appkey_index": AppUIColumnInfo(header="Appkey Index", default=True),
        "pub_ttl": AppUIColumnInfo(header="Pub TTL", default=False),
        "pub_creds": AppUIColumnInfo(header="Pub Credentials", default=False),
        "pub_period_ms": AppUIColumnInfo(header="Pub Period", default=False),
        "pub_retx_count": AppUIColumnInfo(header="Pub ReTxCnt", default=False),
        "pub_retx_int_ms": AppUIColumnInfo(header="Pub ReTxInt", default=False),
    }

    BDADDRSPEC_HELP = (
        f"The <bdaddrspec> identifies BLE address and it can be 6 hex character "
        f"pairs separated by colons. "
        f"For example: C0:01:CA:FE:BA:BE."
    )

    NODESPEC_HELP = (
        f"The <nodespec> identifies nodes and it can be UUID, primary address, "
        f"node name or list index. "
        f"The UUID can be specified as a 32 character long hex string. "
        f"The primary address can be specified as a binary (0b), octal(0o), "
        f"decimal, hex (0x) integer. "
        f"The node name can be a string value with leading non-digit character. "
        f"Node name may be specified with globs to match any characters (* and ?). "
        f"The node list index can be an integer with a leading # sign. "
    )

    ELEMSPEC_HELP = (
        f"The <elemspec> identifies single or multiple elements of nodes so "
        f"these are resolved to unicast addresses. It can be unicast address, "
        f"<nodespec> or an indexed <nodespec>. "
        f"The unicast address can be specified as a binary (0b), octal(0o), "
        f"decimal, hex (0x) integer. "
        f"The <nodespec> identifies all elements of the specified node. "
        f"If the <nodespec> is not indexed then it can't be a primary address "
        f"because that is interpreted as an element address. "
        f"The indexed <nodespec> shall have the following form: <nodespec>[<elemidxspec>]. "
        f"The <elemidxspec> can be comma separated list of <elemrange> values. "
        f"The <elemrange> can be a single number or pair of numbers separated "
        f"by dash (-). A single number identifies a single element by its index "
        f"inside the node while the <j>-<k> range identifies the elements by their "
        f"indexes from <j> to <k> including the boundaries. "
        f"The node elements are indexed from zero. "
        f"Example: Node_1225[0,2-3] selects elements 0,2,3 on node with Node_1225 name."
    )

    MDLSPEC_HELP = (
        f"The <mdlspec> identifies single or multiple vendor or Bluetooth "
        f"SIG models. It can be a model identifier or model name. "
        f"The SIG model identifier can be specified as a binary (0b), octal(0o), "
        f"decimal, hex (0x) integer. The vendor model identifier can be "
        f"specified as a pair of binary (0b), octal(0o), decimal, hex (0x) "
        f"integers separated by any special character ({SEP_PATTERN}). "
        f"The SIG model name can be specified by special model name which "
        f"contains underscore (_) characters instead of spaces. "
        f"Model name may be specified with globs to match any characters (* and ?). "
    )

    FWIDSPEC_HELP = (
        f"The <fwidspec> identifies single or multiple firmware image. "
        f"It can be specified by a composite value containing the company "
        f"identifier, version information format and version information "
        f"separated by any special character ({SEP_PATTERN}). "
        f"The company ID identifier can be specified as a binary (0b), octal(0o), "
        f"decimal, hex (0x) integer. "
        f"The version information format can be 'h' for hex format and 's' for "
        f"string format and it controls how the version information is processed. "
        f"If hex format is used then the version information shall contain "
        f"hexadecimal characters only and the version information is converted "
        f"into a binary value from the provided hexadecimal characters. "
        f"If string format is used then the version information can contain any "
        f"characters and it is converted into a binary value by utf-8 encoding. "
        f"Examples: 0x02FF:h:74657374 or 0x02FF:s:test"
    )

    METASPEC_HELP = (
        f"The <metaspec> identifies the metadata belonging to a firmware image. "
        f"It can be specified by metadata format and metadata values separated "
        f"by any special character ({SEP_PATTERN}). "
        f"The metadata format can be 'h' for hex format and 's' for string "
        f"format and it controls how the metadata is processed. "
        f"If hex format is used then the metadata shall contain hexadecimal "
        f"characters only and the metadata is converted into a binary value "
        f"from the provided hexadecimal characters. "
        f"If string format is used then the metadata can contain any characters "
        f"and it is converted into a binary value by utf-8 encoding. "
        f"Examples: h:74657374 or s:test"
    )

    GROUPSPEC_HELP = (
        f"The <groupspec> identifies one or more app groups. It can be specified "
        f"by app group name or app group list index. The app group name can be a "
        f"string value with leading non-digit character. The app group name may "
        f"be specified with globs to match any characters (* and ?). "
        f"The app group list index can be an integer with a leading # sign. "
    )

    DFU_CALC_TIMEOUT_HELP = (
        "Client side timeout is (10000 * (timeout_base + 2)) + (100 * ttl) ms. "
        "Server side timeout is (10000 * (timeout_base + 1)) ms. "
    )

    INTEGER_PATTERN = btmesh.util.INTEGER_PATTERN
    INTEGER_PAIR_PATTERN = btmesh.util.INTEGER_PAIR_PATTERN
    LIST_INDEX_PATTERN = r"#\d+"
    GLOB_NAME_PATTERN = r"[a-zA-Z_\*\?][\w\*\?]*"
    NODESPEC_PATTERN = "|".join(
        [
            LIST_INDEX_PATTERN,
            GLOB_NAME_PATTERN,
            btmesh.util.UUID_PATTERN,
            btmesh.util.ADDR_PATTERN,
            btmesh.util.NAME_PATTERN,
        ]
    )
    ELEMSPEC_INDEX_PATTERN = r"\[([\d\s,-]+)\]"
    ELEMSPEC_NODESPEC_IDX_PATTERN = (
        "(" + NODESPEC_PATTERN + ")" + ELEMSPEC_INDEX_PATTERN
    )
    ELEMSPEC_PATTERN = "|".join(
        [btmesh.util.ADDR_PATTERN, ELEMSPEC_NODESPEC_IDX_PATTERN, NODESPEC_PATTERN]
    )
    FWIDSPEC_STR_PATTERN = f"({INTEGER_PATTERN}){SEP_PATTERN}s{SEP_PATTERN}(.*)"
    FWIDSPEC_HEX_PATTERN = (
        f"({INTEGER_PATTERN})"
        f"{SEP_PATTERN}"
        f"h"
        f"{SEP_PATTERN}"
        r"((?:[a-fA-F0-9]{2})*)"
    )
    METASPEC_STR_PATTERN = f"s{SEP_PATTERN}(.*)"
    METASPEC_HEX_PATTERN = f"h{SEP_PATTERN}" + r"((?:[a-fA-F0-9]{2})*)"

    @staticmethod
    def glob_to_regex_pattern(glob_pattern: str):
        regex_pattern = glob_pattern
        regex_pattern = regex_pattern.replace("*", r"\w*")
        regex_pattern = regex_pattern.replace("?", r"\w?")
        return regex_pattern

    @classmethod
    def is_indexed_nodespec(cls, elemspec):
        return bool(re.fullmatch(cls.ELEMSPEC_NODESPEC_IDX_PATTERN, elemspec))

    @classmethod
    def is_nodespec(cls, elemspec):
        return bool(re.fullmatch(cls.NODESPEC_PATTERN, elemspec))

    @staticmethod
    def to_int(s):
        try:
            return int(s, 0)
        except ValueError:
            return None

    @classmethod
    def split_text(cls, text):
        sep_map = {k: " " for k in cls.TEXT_LIST_SEP}
        text_fragments = str.translate(text, str.maketrans(sep_map)).split()
        return [tf.strip() for tf in text_fragments]

    def info(self, text, level=logging.INFO):
        text = str(text)
        print(text)
        logger.log(level, text)

    def error(self, text, level=logging.ERROR):
        text = str(text)
        print(text, file=sys.stderr)
        logger.log(level, text)

    def parser_error(self, parser, message, level=logging.ERROR):
        sio = io.StringIO()
        parser.print_usage(sio)
        self.error(sio.getvalue().strip(), level=level)
        sio = io.StringIO()
        parser.print_error(message, file=sio)
        self.error(sio.getvalue().strip())

    def parser_help(self, parser: argparse.ArgumentParser, level=logging.INFO):
        sio = io.StringIO()
        parser.print_help(sio)
        self.info(sio.getvalue().strip())

    def table_info(
        self,
        rows,
        headers_on=True,
        width=None,
        width_max=None,
        column_min_width=5,
        columns_rel_width=None,
        columns_abs_width=None,
        columns={},
        table_fmt="grid",
    ):
        if width is None:
            width = app_cfg.ui.table_width_default
        lines = table_text_lines(
            rows,
            headers_on=headers_on,
            width=width,
            width_max=width_max,
            column_min_width=column_min_width,
            columns_rel_width=columns_rel_width,
            columns_abs_width=columns_abs_width,
            columns=columns,
            table_fmt=table_fmt,
        )
        for line in lines:
            self.info(line)

    def nodes_info(self, nodes: Iterable[Node], columns: Sequence[str]):
        rows = []
        selected_columns = {}
        if not columns:
            columns = ["idx", "name", "uuid", "prim_addr", "elem_count"]
        for col in columns:
            if col not in self.NODE_COLUMNS:
                raise ValueError(f"Invalid node info column {col}.")
            selected_columns[col] = self.NODE_COLUMNS[col]
        # Dictionaries are ordered from Python 3.7 and the required python
        # version is 3.7 as well so the dict can be considered ordered so the
        # selected_columns will contain the columns in the correct order
        for idx, node in enumerate(nodes):
            node_dict = {}
            node_dict["idx"] = idx
            node_dict["uuid"] = node.uuid.hex()
            node_dict["devkey"] = node.devkey.hex()
            node_dict["prim_addr"] = f"0x{node.prim_addr:04X}"
            node_dict["elem_count"] = node.elem_count
            node_dict["name"] = node.name
            node_dict["cid"] = f"0x{node.dcd.cid:04X}" if node.dcd else None
            node_dict["pid"] = f"0x{node.dcd.pid:04X}" if node.dcd else None
            node_dict["vid"] = f"0x{node.dcd.vid:04X}" if node.dcd else None
            node_dict["crpl"] = node.dcd.crpl if node.dcd else None
            node_dict["relay"] = node.dcd.relay if node.dcd else None
            node_dict["proxy"] = node.dcd.proxy if node.dcd else None
            node_dict["friend"] = node.dcd.friend if node.dcd else None
            node_dict["lpn"] = node.dcd.lpn if node.dcd else None
            rows.append(node_dict)
        if 0 < len(rows):
            self.table_info(rows, columns=selected_columns)

    def app_group_table_info(
        self,
        app_groups: Sequence[BtmeshDfuAppGroup],
        columns: Union[Sequence[str], Dict[str, str]],
    ):
        rows = []
        if not columns:
            selected_columns = {
                column: self.APP_GROUP_COLUMNS[column].header
                for column in self.APP_GROUP_COLUMNS
                if self.APP_GROUP_COLUMNS[column].default
            }
        else:
            selected_columns = {}
            if isinstance(columns, Mapping):
                selected_columns = columns
            else:
                for column in columns:
                    if column not in self.APP_GROUP_COLUMNS:
                        raise ValueError(f"Invalid app group table column {column}.")
                    selected_columns[column] = self.APP_GROUP_COLUMNS[column]
        # Dictionaries are ordered from Python 3.7 and the required python
        # version is 3.7 as well so the dict can be considered ordered so the
        # selected_columns will contain the columns in the correct order
        for idx, app_group in enumerate(app_groups):
            idx_str = f"{idx}"
            name_str = app_group.name
            group_addr_str = f"0x{app_group.group_addr:04X}"
            appkey_index_str = f"{app_group.appkey_index}"
            pub_ttl_str = f"{app_group.pub_ttl}"
            if app_group.pub_credentials:
                pub_credentials_str = "friendship"
            else:
                pub_credentials_str = "normal"
            pub_period_ms_str = f"{app_group.pub_period_ms}ms"
            pub_retx_count_str = f"{app_group.pub_retransmit_count}"
            pub_retx_int_ms_str = f"{app_group.pub_retransmit_interval_ms}ms"
            rows.append(
                {
                    "idx": idx_str,
                    "name": name_str,
                    "group_addr": group_addr_str,
                    "appkey_index": appkey_index_str,
                    "pub_ttl": pub_ttl_str,
                    "pub_creds": pub_credentials_str,
                    "pub_period_ms": pub_period_ms_str,
                    "pub_retx_count": pub_retx_count_str,
                    "pub_retx_int_ms": pub_retx_int_ms_str,
                }
            )
        if 0 < len(rows):
            self.table_info(rows, columns=selected_columns)

    def app_group_info(self, app_group: BtmeshDfuAppGroup):
        pub_ttl_str = f"{app_group.pub_ttl}"
        if app_group.pub_credentials:
            pub_credentials_str = "friendship"
        else:
            pub_credentials_str = "normal"
        pub_period_ms_str = f"{app_group.pub_period_ms}ms"
        pub_retx_count_str = f"{app_group.pub_retransmit_count}"
        pub_retx_int_ms_str = f"{app_group.pub_retransmit_interval_ms}ms"
        self.info(f"{app_group.name} app group:")
        self.info(f"  - Group Address: 0x{app_group.group_addr:04X}")
        self.info(f"  - Appkey Index: {app_group.appkey_index}")
        self.info(f"  - Publication TTL: {pub_ttl_str}")
        self.info(f"  - Publication Credentials: {pub_credentials_str}")
        self.info(f"  - Publication Period: {pub_period_ms_str}")
        self.info(f"  - Publication Retransmit Count: {pub_retx_count_str}")
        self.info(f"  - Publication Retransmit Interval: {pub_retx_int_ms_str}")
        app_group_nodes = app_db.get_app_group_node_list(
            app_group.name, order_property="name"
        )
        for node in app_group_nodes:
            self.info(f"  - {node.name} node:")
            for idx, elem_addr in enumerate(node.elem_addrs):
                if elem_addr in app_group.pub_addrs:
                    pub_mdl_names = sorted(
                        mdl.pretty_name()
                        for mdl in app_group.gen_pub_addr_mdls(elem_addr)
                    )
                else:
                    pub_mdl_names = []
                if elem_addr in app_group.sub_addrs:
                    sub_mdl_names = sorted(
                        mdl.pretty_name()
                        for mdl in app_group.gen_sub_addr_mdls(elem_addr)
                    )
                else:
                    sub_mdl_names = []
                if elem_addr in app_group.bind_addrs:
                    bind_mdl_names = sorted(
                        mdl.pretty_name()
                        for mdl in app_group.gen_bind_addr_mdls(elem_addr)
                    )
                else:
                    bind_mdl_names = []
                if pub_mdl_names or sub_mdl_names or bind_mdl_names:
                    self.info(f"    - Element {idx}: (0x{elem_addr:04X})")
                    if pub_mdl_names:
                        self.info(f"      - Publication models:")
                        for mdl_name in pub_mdl_names:
                            self.info(f"        - {mdl_name}")
                    if sub_mdl_names:
                        self.info(f"      - Subscription models:")
                        for mdl_name in sub_mdl_names:
                            self.info(f"        - {mdl_name}")
                    if bind_mdl_names:
                        self.info(f"      - Bind models:")
                        for mdl_name in bind_mdl_names:
                            self.info(f"        - {mdl_name}")

    def node_str(self, node: Node) -> str:
        node_format = app_cfg.ui.node_format
        return node_format.format(
            name=node.name,
            uuid=node.uuid.hex(),
            prim_addr=node.prim_addr,
        )

    def elem_str(self, elem_addr: int) -> str:
        elem_format = app_cfg.ui.elem_format
        node = app_db.btmesh_db.get_node_by_elem_addr(elem_addr)
        elem_index = node.get_elem_index(elem_addr)
        return elem_format.format(
            name=node.name,
            uuid=node.uuid.hex(),
            prim_addr=node.prim_addr,
            elem_index=elem_index,
            elem_addr=elem_addr,
        )

    def fwid_str(self, fwid: FWID) -> str:
        cid_str = f"0x{fwid.company_id:04X}"
        if app_cfg.ui.fwid_format == "hex":
            version_info_str = fwid.version_info.hex()
        else:
            version_info_str = fwid.version_info.decode("utf-8")
        return f"{cid_str}:{version_info_str}"

    def metadata_str(self, metadata: bytes):
        if app_cfg.ui.metadata_format == "hex":
            return metadata.hex()
        else:
            return metadata.decode("utf-8")

    def log_user_input(self, user_input, level=logging.INFO):
        logger.log(level, "[USER] " + user_input)

    def input(self, prompt, level=logging.INFO):
        prompt = str(prompt)
        logger.log(level, prompt)
        input_text = input(prompt)
        self.log_user_input(input_text)
        return input_text

    def nodes_input(self, prompt, node_list, level=logging.INFO):
        nodespecs = app_ui.input(prompt, level=level)
        return self.parse_nodespecs(nodespecs, node_list)

    def parse_bdaddrspecs(
        self, bdaddrspecs, filter_duplicates: bool = True
    ) -> List[str]:
        sel_bd_addr_list = []
        if isinstance(bdaddrspecs, str):
            bdaddrspec_list = self.split_text(bdaddrspecs)
        else:
            bdaddrspec_list = bdaddrspecs
        for bdaddrspec in bdaddrspec_list:
            bdaddrspec = bdaddrspec.strip()
            hex_match = re.fullmatch(btmesh.util.BDADDR_PATTERN, bdaddrspec)
            if not hex_match:
                raise BtmeshDfuAppParseSpecError(
                    f"Invalid bdaddrspec ({bdaddrspec}).",
                    spec_name=BtmeshDfuAppSpecName.BDADDRSPEC,
                    spec_value=bdaddrspec,
                )
            sel_bd_addr_list.append(bdaddrspec)
        if filter_duplicates:
            # Remove duplicate entries from the list
            # Note: Dictionaries are ordered from Python 3.7 and the required
            # python version is 3.7 as well so the dict can be considered ordered
            sel_bd_addr_list = list(dict.fromkeys(sel_bd_addr_list))
        return sel_bd_addr_list

    def parse_bdaddrspec(self, bdaddrspec) -> str:
        sel_bd_addr_list = self.parse_bdaddrspecs(bdaddrspec)
        if 1 < len(sel_bd_addr_list):
            raise BtmeshDfuAppParseSpecError(
                f"The bdaddrspec is ambiguous. It is resolved to multiple "
                f"BLE addresses but it is expected to be a single "
                f"one. ({sel_bd_addr_list})",
                spec_name=BtmeshDfuAppSpecName.BDADDRSPEC,
                spec_value=bdaddrspec,
            )
        return sel_bd_addr_list[0]

    def parse_nodespecs(
        self, nodespecs, node_list: Sequence[Node], filter_duplicates: bool = True
    ) -> List[Node]:
        sel_node_list = []
        if isinstance(nodespecs, str):
            nodespec_list = self.split_text(nodespecs)
        else:
            nodespec_list = nodespecs
        for nodespec in nodespec_list:
            nodespec = nodespec.strip()
            nodes = []
            if Node.is_uuid_valid(nodespec):
                uuid = bytes.fromhex(nodespec)
                node = next((n for n in node_list if n.uuid == uuid), None)
                if node:
                    nodes.append(node)
            elif Node.is_addr_valid(nodespec):
                # If the nodespec is not uuid and it starts with a digit then
                # it is an integer constant. The second 0 parameter of int makes
                # it possible to accept hex (0x), dec, oct (0o) and binary (0b)
                # constants.
                addr = self.to_int(nodespec)
                if addr is None:
                    raise BtmeshDfuAppParseSpecError(
                        f"Invalid nodespec ({nodespec}).",
                        spec_name=BtmeshDfuAppSpecName.NODESPEC,
                        spec_value=nodespec,
                    )
                node = next((n for n in node_list if n.prim_addr == addr), None)
                if node:
                    nodes.append(node)
            elif re.fullmatch(self.LIST_INDEX_PATTERN, nodespec):
                idx = self.to_int(nodespec[1:])
                if idx is None:
                    raise BtmeshDfuAppParseSpecError(
                        f"Invalid nodespec ({nodespec}).",
                        spec_name=BtmeshDfuAppSpecName.NODESPEC,
                        spec_value=nodespec,
                    )
                if idx < len(node_list):
                    node = node_list[idx]
                    nodes.append(node)
            elif Node.is_name_valid(nodespec):
                name = nodespec
                node = next((n for n in node_list if n.name == name), None)
                if node:
                    nodes.append(node)
            elif re.fullmatch(self.GLOB_NAME_PATTERN, nodespec):
                node_name_pattern = self.glob_to_regex_pattern(nodespec)
                nodes = [
                    n for n in node_list if re.fullmatch(node_name_pattern, n.name)
                ]
            else:
                raise BtmeshDfuAppParseSpecError(
                    f"Invalid nodespec ({nodespec}).",
                    spec_name=BtmeshDfuAppSpecName.NODESPEC,
                    spec_value=nodespec,
                )
            if not nodes:
                raise BtmeshDfuAppParseSpecError(
                    f'Node with "{nodespec}" nodespec does not exist.',
                    spec_name=BtmeshDfuAppSpecName.NODESPEC,
                    spec_value=nodespec,
                )
            sel_node_list.extend(nodes)
        if filter_duplicates:
            # Remove duplicate entries from the list
            # Note: Dictionaries are ordered from Python 3.7 and the required
            # python version is 3.7 as well so the dict can be considered ordered
            sel_node_list = list(dict.fromkeys(sel_node_list))
        return sel_node_list

    def parse_elemspecs(
        self, elemspecs, node_list: Sequence[Node], filter_duplicates: bool = True
    ) -> List[int]:
        elem_addr_list = []
        if isinstance(elemspecs, str):
            elemspec_list = self.split_text(elemspecs)
        else:
            elemspec_list = elemspecs
        for elemspec in elemspec_list:
            elemspec = elemspec.strip()
            elem_addrs = []
            if Node.is_addr_valid(elemspec):
                # The second 0 parameter of int makes it possible to accept hex
                # (0x), dec, oct (0o) and binary (0b) constants.
                addr = self.to_int(elemspec)
                if addr is None:
                    raise BtmeshDfuAppParseSpecError(
                        f"Invalid elemspec ({elemspec}).",
                        spec_name=BtmeshDfuAppSpecName.ELEMSPEC,
                        spec_value=elemspec,
                    )
                node = next((n for n in node_list if n.is_elem_addr(addr)), None)
                if node:
                    elem_addrs.append(addr)
            elif self.is_indexed_nodespec(elemspec):
                addrs = self.parse_indexed_nodespec(
                    elemspec=elemspec, node_list=node_list
                )
                elem_addrs.extend(addrs)
            elif self.is_nodespec(elemspec):
                try:
                    nodes = self.parse_nodespecs(
                        nodespecs=elemspec, node_list=node_list
                    )
                except BtmeshDfuAppParseSpecError as e:
                    raise BtmeshDfuAppParseSpecError(
                        e.msg,
                        spec_name=BtmeshDfuAppSpecName.ELEMSPEC,
                        spec_value=e.spec_value,
                    ) from e
                for node in nodes:
                    elem_addrs.extend(node.elem_addrs)
            else:
                raise BtmeshDfuAppParseSpecError(
                    f"Invalid elemspec ({elemspec}).",
                    spec_name=BtmeshDfuAppSpecName.ELEMSPEC,
                    spec_value=elemspec,
                )
            if not elem_addrs:
                raise BtmeshDfuAppParseSpecError(
                    f'Element with "{elemspec}" elemspec does not exist.',
                    spec_name=BtmeshDfuAppSpecName.ELEMSPEC,
                    spec_value=elemspec,
                )
            elem_addr_list.extend(elem_addrs)
        if filter_duplicates:
            # Remove duplicate entries from the list
            # Note: Dictionaries are ordered from Python 3.7 and the required
            # python version is 3.7 as well so the dict can be considered ordered
            elem_addr_list = list(dict.fromkeys(elem_addr_list))
        return elem_addr_list

    def parse_indexed_nodespec(self, elemspec, node_list: List[Node]) -> List[Node]:
        elem_addrs = []
        match = re.fullmatch(self.ELEMSPEC_NODESPEC_IDX_PATTERN, elemspec)
        nodespec = match.group(1)
        elemidxspec = match.group(2)
        elem_idx_list = []
        elem_idx_ranges = elemidxspec.split(",")
        for elem_idx_range in elem_idx_ranges:
            if re.fullmatch(self.INTEGER_PATTERN, elem_idx_range):
                elem_idx = int(elem_idx_range, 0)
                elem_idx_list.append(elem_idx)
            else:
                elem_idx_range_fragments = elem_idx_range.split("-")
                if len(elem_idx_range_fragments) != 2:
                    raise BtmeshDfuAppParseSpecError(
                        f"Invalid elemspec ({elem_idx_range} part of {elemspec}).",
                        spec_name=BtmeshDfuAppSpecName.ELEMSPEC,
                        spec_value=elemspec,
                    )
                if all(
                    re.fullmatch(self.INTEGER_PATTERN, f)
                    for f in elem_idx_range_fragments
                ):
                    elem_idx_range_min = int(elem_idx_range_fragments[0], 0)
                    elem_idx_range_max = int(elem_idx_range_fragments[1], 0)
                    for idx in range(elem_idx_range_min, elem_idx_range_max + 1):
                        elem_idx_list.append(idx)
                else:
                    raise BtmeshDfuAppParseSpecError(
                        f"Invalid elemspec ({elem_idx_range} part of {elemspec}).",
                        spec_name=BtmeshDfuAppSpecName.ELEMSPEC,
                        spec_value=elemspec,
                    )
        try:
            nodes = self.parse_nodespecs(nodespecs=nodespec, node_list=node_list)
        except BtmeshDfuAppParseSpecError as e:
            raise BtmeshDfuAppParseSpecError(
                e.msg,
                spec_name=BtmeshDfuAppSpecName.ELEMSPEC,
                spec_value=e.spec_value,
            ) from e
        for node in nodes:
            try:
                addrs = node.get_elem_addrs(elem_idx_list)
            except ValueError as e:
                raise BtmeshDfuAppParseSpecError(
                    f'Element with "{elemspec}" elemspec does not exist. ' + str(e),
                    spec_name=BtmeshDfuAppSpecName.ELEMSPEC,
                    spec_value=elemspec,
                ) from e
            elem_addrs.extend(addrs)
        return elem_addrs

    def _create_model_id(
        self, mdlspec, model_id, vendor_id=ModelID.SIG_MODEL_VENDOR_ID
    ):
        if (model_id is None) or (vendor_id is None):
            raise BtmeshDfuAppParseSpecError(
                f"Invalid mdlspec ({mdlspec}).",
                spec_name=BtmeshDfuAppSpecName.MDLSPEC,
                spec_value=mdlspec,
            )
        try:
            if isinstance(model_id, NamedModelID):
                model_id = model_id.value
            mdl = ModelID(model_id=model_id, vendor_id=vendor_id)
        except ValueError as e:
            raise BtmeshDfuAppParseSpecError(
                f"Invalid mdlspec ({mdlspec}). " + str(e),
                spec_name=BtmeshDfuAppSpecName.MDLSPEC,
                spec_value=mdlspec,
            ) from e
        return mdl

    def parse_mdlspecs(self, mdlspecs, filter_duplicates: bool = True) -> List[ModelID]:
        sel_model_list = []
        if isinstance(mdlspecs, str):
            mdlspec_list = self.split_text(mdlspecs)
        else:
            mdlspec_list = mdlspecs
        for mdlspec in mdlspec_list:
            mdlspec = mdlspec.strip()
            models = []
            if re.fullmatch(self.INTEGER_PATTERN, mdlspec):
                mdl_id = int(mdlspec, 0)
                mdl = self._create_model_id(mdlspec=mdlspec, model_id=mdl_id)
                models.append(mdl)
            elif re.fullmatch(self.INTEGER_PAIR_PATTERN, mdlspec):
                match = re.fullmatch(self.INTEGER_PAIR_PATTERN, mdlspec)
                vendor_id = int(match.group(1), 0)
                mdl_id = int(match.group(2), 0)
                mdl = self._create_model_id(
                    mdlspec=mdlspec, model_id=mdl_id, vendor_id=vendor_id
                )
                models.append(mdl)
            elif NamedModelID.is_name_valid(mdlspec):
                mdl_id = NamedModelID.get_id_by_name(mdlspec)
                mdl = self._create_model_id(mdlspec=mdlspec, model_id=mdl_id)
                models.append(mdl)
            elif re.fullmatch(self.GLOB_NAME_PATTERN, mdlspec):
                mdl_name_pattern = self.glob_to_regex_pattern(mdlspec.upper())
                for mdl_name, mdl_id in NamedModelID.gen_name_id_pairs():
                    if re.fullmatch(mdl_name_pattern, mdl_name.upper()):
                        mdl = self._create_model_id(mdlspec=mdlspec, model_id=mdl_id)
                        models.append(mdl)
            else:
                raise BtmeshDfuAppParseSpecError(
                    f"Invalid mdlspec ({mdlspec}).",
                    spec_name=BtmeshDfuAppSpecName.MDLSPEC,
                    spec_value=mdlspec,
                )
            if not models:
                raise BtmeshDfuAppParseSpecError(
                    f'Model with "{mdlspec}" mdlspec does not exist.',
                    spec_name=BtmeshDfuAppSpecName.MDLSPEC,
                    spec_value=mdlspec,
                )
            sel_model_list.extend(models)
        if filter_duplicates:
            # Remove duplicate entries from the list
            # Note: Dictionaries are ordered from Python 3.7 and the required
            # python version is 3.7 as well so the dict can be considered ordered
            sel_model_list = list(dict.fromkeys(sel_model_list))
        return sel_model_list

    def parse_fwidspec(self, fwidspec) -> FWID:
        fwid_list = self.parse_fwidspecs(fwidspecs=fwidspec)
        if 1 < len(fwid_list):
            fwid_list_str = ",".join((app_ui.fwid_str(fwid) for fwid in fwid_list))
            raise BtmeshDfuAppParseSpecError(
                f"The fwidspec is ambiguous. It is resolved to multiple FWIDs "
                f"but it is expected to be a single one. ({fwid_list_str})",
                spec_name=BtmeshDfuAppSpecName.FWIDSPEC,
                spec_value=fwidspec,
            )
        return fwid_list[0]

    def parse_fwidspecs(self, fwidspecs, filter_duplicates: bool = True) -> List[FWID]:
        sel_fwid_list = []
        if isinstance(fwidspecs, str):
            fwidspec_list = self.split_text(fwidspecs)
        else:
            fwidspec_list = fwidspecs
        for fwidspec in fwidspec_list:
            fwidspec = fwidspec.strip()
            hex_match = re.fullmatch(self.FWIDSPEC_HEX_PATTERN, fwidspec)
            if hex_match:
                cid = int(hex_match.group(1), 0)
                version_info_str = hex_match.group(2)
                version_info = bytes.fromhex(version_info_str)
                fwid = FWID(company_id=cid, version_info=version_info)
                sel_fwid_list.append(fwid)
            else:
                str_match = re.fullmatch(self.FWIDSPEC_STR_PATTERN, fwidspec)
                if str_match:
                    cid = int(str_match.group(1), 0)
                    version_info_str = str_match.group(2)
                    version_info = version_info_str.encode("utf-8")
                    fwid = FWID(company_id=cid, version_info=version_info)
                    sel_fwid_list.append(fwid)
                else:
                    raise BtmeshDfuAppParseSpecError(
                        f"Invalid fwidspec ({fwidspec}).",
                        spec_name=BtmeshDfuAppSpecName.FWIDSPEC,
                        spec_value=fwidspec,
                    )
        if filter_duplicates:
            # Remove duplicate entries from the list
            # Note: Dictionaries are ordered from Python 3.7 and the required
            # python version is 3.7 as well so the dict can be considered ordered
            sel_fwid_list = list(dict.fromkeys(sel_fwid_list))
        return sel_fwid_list

    def parse_metaspec(self, metaspec) -> bytes:
        metadata_list = self.parse_metaspecs(metaspecs=metaspec)
        if 1 < len(metadata_list):
            metadata_list_str = ",".join(
                (app_ui.metadata_str(md) for md in metadata_list)
            )
            raise BtmeshDfuAppParseSpecError(
                f"The metaspec is ambiguous. It is resolved to multiple metadata "
                f"but it is expected to be a single one. ({metadata_list_str})",
                spec_name=BtmeshDfuAppSpecName.METASPEC,
                spec_value=metaspec,
            )
        return metadata_list[0]

    def parse_metaspecs(self, metaspecs, filter_duplicates: bool = True) -> List[bytes]:
        sel_metadata_list = []
        if isinstance(metaspecs, str):
            metaspec_list = self.split_text(metaspecs)
        else:
            metaspec_list = metaspecs
        for metaspec in metaspec_list:
            metaspec = metaspec.strip()
            hex_match = re.fullmatch(self.METASPEC_HEX_PATTERN, metaspec)
            if hex_match:
                metadata_str = hex_match.group(1)
                metadata = bytes.fromhex(metadata_str)
                sel_metadata_list.append(metadata)
            else:
                str_match = re.fullmatch(self.METASPEC_STR_PATTERN, metaspec)
                if str_match:
                    metadata_str = str_match.group(1)
                    metadata = metadata_str.encode("utf-8")
                    sel_metadata_list.append(metadata)
                else:
                    raise BtmeshDfuAppParseSpecError(
                        f"Invalid metaspec ({metaspec}).",
                        spec_name=BtmeshDfuAppSpecName.METASPEC,
                        spec_value=metaspec,
                    )
        if filter_duplicates:
            # Remove duplicate entries from the list
            # Note: Dictionaries are ordered from Python 3.7 and the required
            # python version is 3.7 as well so the dict can be considered ordered
            sel_metadata_list = list(dict.fromkeys(sel_metadata_list))
        return sel_metadata_list

    def parse_groupspec(
        self, groupspec, app_group_list: Sequence[BtmeshDfuAppGroup]
    ) -> BtmeshDfuAppGroup:
        app_group_list = self.parse_groupspecs(groupspec, app_group_list)
        if 1 < len(app_group_list):
            app_group_list_str = ",".join(g.name for g in app_group_list)
            raise BtmeshDfuAppParseSpecError(
                f"The groupspec is ambiguous. It is resolved to multiple app groups "
                f"but it is expected to be a single one. ({app_group_list_str})",
                spec_name=BtmeshDfuAppSpecName.GROUPSPEC,
                spec_value=groupspec,
            )
        return app_group_list[0]

    def parse_groupspecs(
        self,
        groupspecs,
        app_group_list: Sequence[BtmeshDfuAppGroup],
        filter_duplicates: bool = True,
    ) -> List[BtmeshDfuAppGroup]:
        sel_app_group_list = []
        if isinstance(groupspecs, str):
            groupspec_list = self.split_text(groupspecs)
        else:
            groupspec_list = groupspecs
        for groupspec in groupspec_list:
            groupspec = groupspec.strip()
            app_groups = []
            if btmesh.util.is_name_valid(groupspec):
                name = groupspec
                app_group = next((g for g in app_group_list if g.name == name), None)
                if app_group:
                    app_groups.append(app_group)
            elif re.fullmatch(self.GLOB_NAME_PATTERN, groupspec):
                app_group_name_pattern = self.glob_to_regex_pattern(groupspec)
                app_groups = [
                    app_group
                    for app_group in app_group_list
                    if re.fullmatch(app_group_name_pattern, app_group.name)
                ]
            elif re.fullmatch(self.LIST_INDEX_PATTERN, groupspec):
                idx = self.to_int(groupspec[1:])
                if idx is None:
                    raise BtmeshDfuAppParseSpecError(
                        f"Invalid groupspec ({groupspec}).",
                        spec_name=BtmeshDfuAppSpecName.GROUPSPEC,
                        spec_value=groupspec,
                    )
                if idx < len(app_group_list):
                    app_group = app_group_list[idx]
                    app_groups.append(app_group)
            else:
                raise BtmeshDfuAppParseSpecError(
                    f"Invalid groupspec ({groupspec}).",
                    spec_name=BtmeshDfuAppSpecName.GROUPSPEC,
                    spec_value=groupspec,
                )
            if not app_groups:
                raise BtmeshDfuAppParseSpecError(
                    f'App group with "{groupspec}" groupspec does not exist.',
                    spec_name=BtmeshDfuAppSpecName.GROUPSPEC,
                    spec_value=groupspec,
                )
            sel_app_group_list.extend(app_groups)
        if filter_duplicates:
            # Remove duplicate entries from the list
            # Note: Dictionaries are ordered from Python 3.7 and the required
            # python version is 3.7 as well so the dict can be considered ordered
            sel_app_group_list = list(dict.fromkeys(sel_app_group_list))
        return sel_app_group_list


app_ui = BtmeshDfuAppUI()
