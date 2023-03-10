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
import json
import operator
from datetime import datetime
from pathlib import Path
from typing import ClassVar, Dict, Iterable, Mapping, Optional

import btmesh.util
from btmesh.db import FWID, BtmeshDatabase, ModelID
from btmesh.event import LocalEvent
from btmesh.statedict import StateDictObject
from btmesh.util import BtmeshRetryParams

from .btmesh import app_btmesh
from .cfg import app_cfg
from .rnode import RemoteNode


class BtmeshDfuAppDbLoadError(Exception):
    def __init__(self, json_path, *args: object):
        super().__init__(*args)
        self.json_path = json_path


@dataclasses.dataclass
class BtmeshDfuAppDbClearedEvent(LocalEvent):
    name: ClassVar[str] = "btmesh_levt_app_db_cleared"


class BtmeshDfuAppGroup(StateDictObject):
    @classmethod
    def validate_addr(cls, addrs_dict, addr, addrs_name, shall_exist=None):
        btmesh.util.validate_unicast_address(
            addr, f"Invalid app group {addrs_name} address."
        )
        if shall_exist is not None:
            if shall_exist and (addr not in addrs_dict):
                raise ValueError(
                    f"App group {addrs_name} address 0x{addr:04X} does not exists."
                )
            elif (not shall_exist) and (addr in addrs_dict):
                raise ValueError(
                    f"App group {addrs_name} address 0x{addr:04X} already exists."
                )

    @classmethod
    def add_addr(cls, addrs_dict, addr, addrs_name):
        cls.validate_addr(addrs_dict, addr, addrs_name, shall_exist=False)
        addrs_dict[addr] = set()

    @classmethod
    def remove_addr(cls, addrs_dict, addr, addrs_name):
        cls.validate_addr(addrs_dict, addr, addrs_name, shall_exist=True)
        return addrs_dict.pop(addr)

    @classmethod
    def has_addr_mdl(cls, addrs_dict, addr, mdl, addrs_name):
        cls.validate_addr(addrs_dict, addr, addrs_name, shall_exist=True)
        return mdl in addrs_dict[addr]

    @classmethod
    def add_addr_mdl(cls, addrs_dict, addr, mdl, addrs_name):
        cls.validate_addr(addrs_dict, addr, addrs_name, shall_exist=None)
        if addr not in addrs_dict:
            cls.add_addr(addrs_dict, addr, addrs_name)
        addrs_dict[addr].add(mdl)

    @classmethod
    def remove_addr_mdl(cls, addrs_dict, addr, mdl, addrs_name):
        cls.validate_addr(addrs_dict, addr, addrs_name, shall_exist=True)
        addrs_dict[addr].remove(mdl)
        if not len(addrs_dict[addr]):
            del addrs_dict[addr]

    @classmethod
    def gen_addr_mdls(cls, addrs_dict, addr, addrs_name) -> Iterable[ModelID]:
        cls.validate_addr(addrs_dict, addr, addrs_name, shall_exist=True)
        return (mdl for mdl in addrs_dict.get(addr, set()))

    def create_mdl(self, attr_name, raw_mdl):
        if isinstance(raw_mdl, Mapping):
            mdl = ModelID.create_from_dict(raw_mdl)
        elif isinstance(raw_mdl, ModelID):
            mdl = raw_mdl
        else:
            self.raise_construction_error(attr_name, raw_mdl, type_error=True)
        return mdl

    def __init__(
        self,
        name,
        group_addr=0,
        appkey_index=0,
        pub_ttl=5,
        pub_credentials=0,
        pub_period_ms=0,
        pub_retransmit_count=0,
        pub_retransmit_interval_ms=0,
        pub_addrs={},
        sub_addrs={},
        bind_addrs={},
    ) -> None:
        super().__init__()
        self.name = name
        self.group_addr = group_addr
        self.appkey_index = appkey_index
        self.pub_ttl = pub_ttl
        self.pub_credentials = pub_credentials
        self.pub_period_ms = pub_period_ms
        self.pub_retransmit_count = pub_retransmit_count
        self.pub_retransmit_interval_ms = pub_retransmit_interval_ms
        self._pub_addrs = {}
        self._sub_addrs = {}
        self._bind_addrs = {}
        pub_addrs = {
            btmesh.util.addr_to_int(addr): mdls for addr, mdls in pub_addrs.items()
        }
        sub_addrs = {
            btmesh.util.addr_to_int(addr): mdls for addr, mdls in sub_addrs.items()
        }
        bind_addrs = {
            btmesh.util.addr_to_int(addr): mdls for addr, mdls in bind_addrs.items()
        }
        for addr in pub_addrs:
            self.add_pub_addr(addr)
            for raw_mdl in pub_addrs[addr]:
                mdl = self.create_mdl(f"pub_addrs[0x{addr:04X}] mdl", raw_mdl)
                self.add_pub_addr_mdl(addr, mdl)
        for addr in sub_addrs:
            self.add_sub_addr(addr)
            for raw_mdl in sub_addrs[addr]:
                mdl = self.create_mdl(f"sub_addrs[0x{addr:04X}] mdl", raw_mdl)
                self.add_sub_addr_mdl(addr, mdl)
        for addr in bind_addrs:
            self.add_bind_addr(addr)
            for raw_mdl in bind_addrs[addr]:
                mdl = self.create_mdl(f"bind_addrs[0x{addr:04X}] mdl", raw_mdl)
                self.add_bind_addr_mdl(addr, mdl)

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, value):
        btmesh.util.validate_name(value, "Invalid app group name.")
        self._name = value

    @property
    def group_addr(self):
        return self._group_addr

    @group_addr.setter
    def group_addr(self, value):
        btmesh.util.validate_group_address(value, "Invalid app group address.")
        self._group_addr = btmesh.util.addr_to_int(value)

    @property
    def appkey_index(self):
        return self._appkey_index

    @appkey_index.setter
    def appkey_index(self, value):
        ERROR_MSG = "Invalid app group appkey index."
        btmesh.util.validate_appkey_index(value, ERROR_MSG)
        if app_cfg.network.appkey_cnt <= value:
            raise ValueError(
                f"{ERROR_MSG} Configured appkey count is {app_cfg.network.appkey_cnt} "
                f"but {value} appkey index is set for app group."
            )
        self._appkey_index = value

    @property
    def pub_ttl(self):
        return self._pub_ttl

    @pub_ttl.setter
    def pub_ttl(self, value):
        btmesh.util.validate_ttl(value, "Invalid app group pub TTL.")
        self._pub_ttl = value

    @property
    def pub_credentials(self):
        return self._pub_credentials

    @pub_credentials.setter
    def pub_credentials(self, value):
        btmesh.util.validate_pub_credentials(
            value, "Invalid app group pub credentials."
        )
        self._pub_credentials = value

    @property
    def pub_period_ms(self):
        return self._pub_period_ms

    @pub_period_ms.setter
    def pub_period_ms(self, value):
        btmesh.util.validate_pub_period_ms(value, "Invalid app group pub period.")
        self._pub_period_ms = value

    @property
    def pub_retransmit_count(self):
        return self._pub_retransmit_count

    @pub_retransmit_count.setter
    def pub_retransmit_count(self, value):
        btmesh.util.validate_pub_retransmit_count(
            value, "Invalid app group pub retransmit count."
        )
        self._pub_retransmit_count = value

    @property
    def pub_retransmit_interval_ms(self):
        return self._pub_retransmit_interval_ms

    @pub_retransmit_interval_ms.setter
    def pub_retransmit_interval_ms(self, value):
        btmesh.util.validate_pub_retransmit_interval_ms(
            value, "Invalid app group pub retransmit interval."
        )
        self._pub_retransmit_interval_ms = value

    # Publication element address methods
    @property
    def pub_addrs(self):
        return (addr for addr in self._pub_addrs)

    def has_pub_addr(self, addr):
        return addr in self._pub_addrs

    def add_pub_addr(self, addr):
        self.add_addr(self._pub_addrs, addr, "pub")

    def remove_pub_addr(self, addr):
        self.remove_addr(self._pub_addrs, addr, "pub")

    def has_pub_addr_mdl(self, addr, mdl):
        return self.has_addr_mdl(self._pub_addrs, addr, mdl, "pub")

    def add_pub_addr_mdl(self, addr, mdl):
        self.add_addr_mdl(self._pub_addrs, addr, mdl, "pub")

    def remove_pub_addr_mdl(self, addr, mdl):
        self.remove_addr_mdl(self._pub_addrs, addr, mdl, "pub")

    def gen_pub_addr_mdls(self, addr) -> Iterable[ModelID]:
        return self.gen_addr_mdls(self._pub_addrs, addr, "pub")

    # Subscription element address methods
    @property
    def sub_addrs(self):
        return (addr for addr in self._sub_addrs)

    def has_sub_addr(self, addr):
        return addr in self._sub_addrs

    def add_sub_addr(self, addr):
        self.add_addr(self._sub_addrs, addr, "sub")

    def remove_sub_addr(self, addr):
        self.remove_addr(self._sub_addrs, addr, "sub")

    def has_sub_addr_mdl(self, addr, mdl):
        return self.has_addr_mdl(self._sub_addrs, addr, mdl, "sub")

    def add_sub_addr_mdl(self, addr, mdl):
        self.add_addr_mdl(self._sub_addrs, addr, mdl, "sub")

    def remove_sub_addr_mdl(self, addr, mdl):
        self.remove_addr_mdl(self._sub_addrs, addr, mdl, "sub")

    def gen_sub_addr_mdls(self, addr) -> Iterable[ModelID]:
        return self.gen_addr_mdls(self._sub_addrs, addr, "sub")

    # Binding element address methods
    @property
    def bind_addrs(self):
        return (addr for addr in self._bind_addrs)

    def has_bind_addr(self, addr):
        return addr in self._bind_addrs

    def add_bind_addr(self, addr):
        self.add_addr(self._bind_addrs, addr, "bind")

    def remove_bind_addr(self, addr):
        self.remove_addr(self._bind_addrs, addr, "bind")

    def has_bind_addr_mdl(self, addr, mdl):
        return self.has_addr_mdl(self._bind_addrs, addr, mdl, "bind")

    def add_bind_addr_mdl(self, addr, mdl):
        self.add_addr_mdl(self._bind_addrs, addr, mdl, "bind")

    def remove_bind_addr_mdl(self, addr, mdl):
        self.remove_addr_mdl(self._bind_addrs, addr, mdl, "bind")

    def gen_bind_addr_mdls(self, addr) -> Iterable[ModelID]:
        return self.gen_addr_mdls(self._bind_addrs, addr, "bind")

    # Binding element address methods
    @property
    def addrs(self):
        # Remove duplicate values because an address might be in publication,
        # subscription and bind addresses as well
        addrs_set = set(self.pub_addrs)
        addrs_set.update(self.sub_addrs)
        addrs_set.update(self.bind_addrs)
        yield from addrs_set


class BtmeshDfuAppDatabase(StateDictObject):
    def __init__(self, btmesh_db=None, app_groups={}, fwid_metadata_cache={}):
        if isinstance(btmesh_db, BtmeshDatabase):
            self.btmesh_db = btmesh_db
        elif isinstance(btmesh_db, Mapping):
            self.btmesh_db = BtmeshDatabase.create_from_dict(btmesh_db)
        else:
            self.btmesh_db = BtmeshDatabase()
        self.app_groups: Dict[str, BtmeshDfuAppGroup] = {}
        for group in app_groups.values():
            if isinstance(group, Mapping):
                self.add_app_group(BtmeshDfuAppGroup.create_from_dict(group))
            elif isinstance(group, BtmeshDfuAppGroup):
                self.add_app_group(group)
            else:
                self.raise_construction_error("group", group, type_error=True)
        self.fwid_metadata_cache: Dict[bytes, bytes] = {}
        for raw_fwid, raw_metadata in fwid_metadata_cache.items():
            fwid_bytes = StateDictObject.to_bytes(raw_fwid)
            metadata = StateDictObject.to_bytes(raw_metadata)
            self.fwid_metadata_cache[fwid_bytes] = metadata
        self.btmesh_db.set_event_emitter(app_btmesh.emit_local_event)

    def clear(self):
        self.btmesh_db.clear()
        self.app_groups.clear()
        self.fwid_metadata_cache.clear()
        db_clr_event = BtmeshDfuAppDbClearedEvent()
        app_btmesh.emit_local_event(db_clr_event)

    def save(self, path=None):
        if path is None:
            json_path = app_cfg.persistence.path
        else:
            # Create path object from parameter to accept string as well.
            # Path class handles Path object parameter in its constructor
            # gracefully so it is not necessary to check for type.
            json_path = Path(path)
        with json_path.open("w") as json_file:
            json_dict = self.to_dict()
            json_text = json.dumps(json_dict, indent=4)
            json_file.write(json_text)

    def load(self, path=None):
        if path is None:
            json_path = app_cfg.persistence.path
        else:
            # Create path object from parameter to accept string as well.
            # Path class handles Path object parameter in its constructor
            # gracefully so it is not necessary to check for type.
            json_path = Path(path)
        if json_path.exists():
            with json_path.open() as json_file:
                json_text = json_file.read()
                try:
                    json_dict = json.loads(json_text)
                    self.from_dict(json_dict)
                except (json.JSONDecodeError, ValueError, TypeError) as e:
                    if app_cfg.persistence.default_on_failed_load:
                        if app_cfg.persistence.backup_on_failed_load:
                            p = json_path
                            date_str = f"_{datetime.now():%Y%m%d_%H%M%S}"
                            temp_folder_path = p.parent / "temp"
                            temp_folder_path.mkdir(exist_ok=True)
                            backup_path = temp_folder_path / Path(
                                p.stem + date_str + p.suffix + ".bak"
                            )
                            with backup_path.open("w") as backup_file:
                                backup_file.write(json_text)
                        self.clear()
                        self.save()
                    raise BtmeshDfuAppDbLoadError(
                        json_path,
                        f"Failed to load {json_path} persistent data. "
                        f"JSON load error reason: {e}",
                    ) from e
        else:
            self.clear()

    def add_app_group(self, app_group):
        if app_group.name in self.app_groups:
            raise ValueError(f'App group name "{app_group.name}" already exists.')
        self.app_groups[app_group.name] = app_group

    def remove_app_group(self, name):
        return self.app_groups.pop(name)

    def has_app_group(self, name):
        return name in self.app_groups

    def rename_app_group(self, current_name, new_name):
        if current_name not in self.app_groups:
            raise ValueError(f'App group with "{current_name}" does not exist.')
        if new_name in self.app_groups:
            raise ValueError(f'App group name "{new_name}" already exists.')
        # It is necessary to remove the app_group on rename because the key
        # in the dictionary is the name of the app_group
        app_group = self.remove_app_group(current_name)
        app_group.name = new_name
        self.add_app_group(app_group)

    def gen_app_groups(self):
        return (ag for ag in self.app_groups.values())

    def gen_app_group_names(self):
        return (ag for ag in self.app_groups.keys())

    def get_app_group_list(self, groupfilter=None, order_property=None, reverse=False):
        identity = lambda n: n
        groupfilter = groupfilter if groupfilter else identity
        app_group_gen = self.gen_app_groups()
        if order_property:
            key = operator.attrgetter(order_property)
            return sorted(app_group_gen, key=key, reverse=reverse)
        else:
            return list(app_group_gen)

    def get_app_group_by_name(self, name):
        if name not in self.app_groups:
            raise ValueError(f'App group with "{name}" does not exist.')
        return self.app_groups[name]

    def gen_app_group_nodes(self, app_group_name):
        app_group = self.get_app_group_by_name(app_group_name)
        node_dict = dict.fromkeys(
            (self.btmesh_db.get_node_by_elem_addr(addr) for addr in app_group.addrs)
        )
        yield from node_dict.keys()

    def get_app_group_node_list(
        self, app_group_name, nodefilter=None, order_property=None, reverse=False
    ):
        identity = lambda n: n
        nodefilter = nodefilter if nodefilter else identity
        node_gen = self.gen_app_group_nodes(app_group_name)
        if order_property:
            key = operator.attrgetter(order_property)
            return sorted(node_gen, key=key, reverse=reverse)
        else:
            return list(node_gen)

    def get_remote_node_by_name(self, name, retry_params: BtmeshRetryParams = None):
        node = self.btmesh_db.get_node_by_name(name)
        return RemoteNode(btmesh=app_btmesh, node=node, retry_params=retry_params)

    def get_remote_node_by_uuid(self, uuid, retry_params: BtmeshRetryParams = None):
        node = self.btmesh_db.get_node_by_uuid(uuid)
        return RemoteNode(btmesh=app_btmesh, node=node, retry_params=retry_params)

    def get_remote_node_by_prim_addr(
        self, prim_addr, retry_params: BtmeshRetryParams = None
    ):
        node = self.btmesh_db.get_node_by_prim_addr(prim_addr)
        return RemoteNode(btmesh=app_btmesh, node=node, retry_params=retry_params)

    def get_remote_node_by_elem_addr(
        self, elem_addr, retry_params: BtmeshRetryParams = None
    ):
        node = self.btmesh_db.get_node_by_elem_addr(elem_addr)
        return RemoteNode(btmesh=app_btmesh, node=node, retry_params=retry_params)

    def get_metadata_by_fwid(
        self, fwid: FWID, default: Optional[bytes] = None
    ) -> Optional[bytes]:
        return self.fwid_metadata_cache.get(fwid.to_bytes(), default)

    def add_fwid_metadata_pair(self, fwid: FWID, metadata: bytes) -> None:
        self.fwid_metadata_cache[fwid.to_bytes()] = metadata

    def clear_fwid_metadata_cache(self) -> None:
        self.fwid_metadata_cache.clear()


app_db = BtmeshDfuAppDatabase()
