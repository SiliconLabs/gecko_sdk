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

import copy
import dataclasses
import enum
from typing import Iterable, List, Optional, Union

from bgapi.bglib import CommandError, CommandFailedError

from bgapix.bglibx import (BGLibExt, BGLibExtRetryParams,
                           BGLibExtWaitEventError, EventParamValues)
from bgapix.slstatus import SlStatus

from . import util
from .db import DCD, BtmeshDatabase, DCDElement, ModelID, Node
from .errors import BtmeshError, BtmeshErrorCode
from .event import LocalEventBus
from .util import BtmeshRetryParams


@enum.unique
class SilabsConfStatus(util.BtmeshIntEnum):
    SUCCESS = 0x00
    UNKNOWN_COMMAND = 0x01
    INVALID_PARAMETER = 0x02
    DOES_NOT_EXISTS = 0x03
    TIMEOUT = 0xFFFF
    UNKNOWN_VALUE = util.ENUM_UNKNOWN_VALUE


@enum.unique
class SilabsConfTxPhy(util.BtmeshIntEnum):
    LE_LEGACY = 0x00
    LE_1M = 0x01
    LE_2M = 0x02
    UNKNOWN_VALUE = util.ENUM_UNKNOWN_VALUE


@enum.unique
class SilabsConfTxOpt(util.BtmeshIntFlag):
    DEFAULT = 0
    # Short packets (non-segmented) over AE PHY
    AE_SHORT_PACKETS = 1
    # Disable relaying AE packets
    AE_NO_RELAY = 2


@dataclasses.dataclass
class SilabsConfBaseStatus:
    node: Node
    status: SilabsConfStatus

    @classmethod
    def from_event(cls, node: Node, event):
        raise NotImplementedError(f"The {cls.__name__} can't be instantiated.")

    @classmethod
    def create_status_timeout(cls, node):
        raise NotImplementedError(f"The {cls.__name__} can't be instantiated.")


@dataclasses.dataclass
class SilabsConfTxStatus(SilabsConfBaseStatus):
    tx_phy: Optional[SilabsConfTxPhy]
    tx_options: Optional[SilabsConfTxOpt]

    @classmethod
    def from_event(cls, node: Node, event):
        assert node.prim_addr == event.server
        return SilabsConfTxStatus(
            node=node,
            status=SilabsConfStatus.from_int(event.status),
            tx_phy=SilabsConfTxPhy.from_int(event.tx_phy),
            tx_options=SilabsConfTxOpt.from_int(event.tx_options_bitmap),
        )

    @classmethod
    def create_status_timeout(cls, node):
        return SilabsConfTxStatus(
            node=node,
            status=SilabsConfStatus.TIMEOUT,
            tx_phy=None,
            tx_options=None,
        )


@dataclasses.dataclass
class SilabsConfModelStatus(SilabsConfBaseStatus):
    elem_index: Optional[int]
    model: Optional[ModelID]
    enabled: Optional[bool]

    @classmethod
    def from_event(cls, node: Node, event):
        assert node.prim_addr == event.server
        return SilabsConfModelStatus(
            node=node,
            status=SilabsConfStatus.from_int(event.status),
            elem_index=event.elem_index,
            model=ModelID(event.model_id, event.vendor_id),
            enabled=event.value,
        )

    @classmethod
    def create_status_timeout(cls, node):
        return SilabsConfModelStatus(
            node=node,
            status=SilabsConfStatus.TIMEOUT,
            elem_index=None,
            model=None,
            enabled=None,
        )


@dataclasses.dataclass
class SilabsConfNetworkPduStatus(SilabsConfBaseStatus):
    pdu_max_size: Optional[int]

    @classmethod
    def from_event(cls, node: Node, event):
        assert node.prim_addr == event.server
        return SilabsConfNetworkPduStatus(
            node=node,
            status=SilabsConfStatus.from_int(event.status),
            pdu_max_size=event.pdu_max_size,
        )

    @classmethod
    def create_status_timeout(cls, node):
        return SilabsConfNetworkPduStatus(
            node=node,
            status=SilabsConfStatus.TIMEOUT,
            pdu_max_size=None,
        )


class Configurator:
    NETKEY_IDX = 0
    DCD_PAGE_0 = 0
    DCD_HEADER_LEN = 10
    DCD_ELEM_HEADER_LEN = 4
    DCD_SIG_MODEL_LEN = 2
    DCD_VENDOR_MODEL_LEN = 4
    DCD_MODEL_ID_LEN = 2
    DCD_VENDOR_ID_LEN = 2

    def __init__(
        self,
        lib: BGLibExt,
        db: BtmeshDatabase,
        evtbus: LocalEventBus,
        conf_retry_params_default: BtmeshRetryParams,
        silabs_retry_params_default: BtmeshRetryParams,
        reset_node_retry_params_default: BtmeshRetryParams,
    ):
        self.lib = lib
        self.db = db
        self.evtbus = evtbus
        self.conf_retry_params_default = conf_retry_params_default
        self.silabs_retry_params_default = silabs_retry_params_default
        self.reset_node_retry_params_default = reset_node_retry_params_default
        self.silabs_conf_svr_fail = False
        self.silabs_conf_clt_fail = False

    @property
    def silabs_conf_support(self) -> bool:
        return not (self.silabs_conf_clt_fail or self.silabs_conf_svr_fail)

    def set_conf_retry_params_default(self, retry_params: BtmeshRetryParams):
        if retry_params:
            self.conf_retry_params_default = copy.copy(retry_params)

    def set_silabs_retry_params_default(self, retry_params: BtmeshRetryParams):
        if retry_params:
            self.silabs_retry_params_default = copy.copy(retry_params)

    def set_reset_node_retry_params_default(self, retry_params: BtmeshRetryParams):
        if retry_params:
            self.reset_node_retry_params_default = copy.copy(retry_params)

    def any_lpn(self, nodes: Iterable[Node], skip_local: bool = True) -> bool:
        for node in nodes:
            if skip_local:
                rsp = self.lib.btmesh.node.get_uuid()
                prov_uuid = rsp.uuid
                if node.uuid == prov_uuid:
                    continue
            dcd = self.get_dcd_cached(node, retry_params=self.conf_retry_params_default)
            if dcd.lpn:
                return True
        return False

    def any_lpn_in_elem_addrs(
        self, elem_addrs: Iterable[int], skip_local: bool = True
    ) -> bool:
        nodes_dict = {}
        for addr in elem_addrs:
            util.validate_unicast_address(addr)
            node = self.db.get_node_by_elem_addr(addr)
            nodes_dict[node.prim_addr] = node
        return self.any_lpn(nodes_dict.values())

    def config_procedure(
        self,
        proc_name,
        cmd,
        node: Node,
        *args,
        final_event_name,
        output_event_names=[],
        retry_params: BtmeshRetryParams = None,
    ):
        if retry_params is None:
            retry_params = self.conf_retry_params_default
        if isinstance(output_event_names, str):
            output_event_names = [output_event_names]
        elif not output_event_names:
            output_event_names = [final_event_name]
        event_selector = {}
        retry_event_selector = {}
        for evt in output_event_names:
            if evt != final_event_name:
                event_selector[evt] = {
                    "#final": False,
                    "handle": "$handle",
                }
        event_selector[final_event_name] = {"handle": "$handle"}
        retry_event_selector[final_event_name] = {
            "result": SlStatus.TIMEOUT,
            "handle": "$handle",
        }
        rsp = self.lib.btmesh.config_client.get_default_timeout()
        orig_timeout_ms = rsp.timeout_ms
        orig_lpn_timeout_ms = rsp.lpn_timeout_ms
        try:
            self.lib.btmesh.config_client.set_default_timeout(
                round(1000 * retry_params.retry_interval),
                round(1000 * retry_params.retry_interval_lpn),
            )
            # The BT Mesh stack configuration client API guarantees that
            # the command specific event is emitted even in case of timeout.
            # A worst case timeout is calculated for retry_until function in
            # order to be on the safe side and to avoid waiting forever.
            # Note: an event might be lost if the processing of events is slower
            # than the generation of events and the event buffer is full.
            retry_interval_base = max(
                retry_params.retry_interval, retry_params.retry_interval_lpn
            )
            retry_params = BGLibExtRetryParams(
                retry_max=retry_params.retry_max,
                retry_interval=2 * retry_interval_base,
                retry_cmd_max=self.conf_retry_params_default.retry_cmd_max,
                retry_cmd_interval=self.conf_retry_params_default.retry_cmd_interval,
            )
            events = self.lib.retry_until(
                cmd,
                self.NETKEY_IDX,
                node.prim_addr,
                *args,
                **retry_params.to_dict(),
                retry_cmd_err_code=[SlStatus.NO_MORE_RESOURCE, SlStatus.INVALID_STATE],
                retry_event_selector=retry_event_selector,
                event_selector=event_selector,
            )
        finally:
            self.lib.btmesh.config_client.set_default_timeout(
                orig_timeout_ms, orig_lpn_timeout_ms
            )
        final_events = [evt for evt in events if evt == final_event_name]
        # There should be at least one and most probably only one end event due
        # to the retry_until function otherwise the retry_until raises
        # CommandFailedError or BGLibExtWaitEventError exception.
        final_evt = final_events[0]
        if final_evt.result != SlStatus.OK:
            result_value = final_evt.result
            result_name = SlStatus.get_name(final_evt.result)
            raise BtmeshError(
                BtmeshErrorCode.CONFIG_FAILED,
                f"{proc_name.capitalize()} procedure failed. "
                f"(0x{result_value:04X}-{result_name})",
                event=final_evt,
            )
        return [evt for evt in events if evt in output_event_names]

    def concat_config_event_bytes(self, attr, events, event_filter=lambda e: True):
        barr = bytearray()
        for evt in filter(event_filter, events):
            barr.extend(getattr(evt, attr))
        return bytes(barr)

    def get_dcd(
        self,
        node: Node,
        update_db: bool = True,
        retry_params: BtmeshRetryParams = None,
    ) -> DCD:
        rsp = self.lib.btmesh.node.get_uuid()
        prov_uuid = rsp.uuid
        if node.uuid == prov_uuid:
            # The DCD of the Provisioner can be queried by node command only.
            # No retry is necessary because it is a local command (no msg sent)
            self.lib.btmesh.node.get_local_dcd(self.DCD_PAGE_0)
            events = self.lib.wait_events(
                event_selector={
                    "btmesh_evt_node_local_dcd_data": {"#final": False},
                    "btmesh_evt_node_local_dcd_data_end": None,
                },
                max_time=1.0,
            )
            # The btmesh_evt_node_local_dcd_data_end is the final event so it is
            # guaranteed that it is the last element of the list
            local_dcd_data_end_evt = events[-1]
            get_local_dcd_result = local_dcd_data_end_evt.result
            if get_local_dcd_result != SlStatus.OK:
                result_value = get_local_dcd_result
                result_name = SlStatus.get_name(result_value)
                raise BtmeshError(
                    BtmeshErrorCode.CONFIG_FAILED,
                    f"DCD Local Get procedure failed. "
                    f"(0x{result_value:04X}-{result_name})",
                    event=local_dcd_data_end_evt,
                )
            events = events[:-1]
        else:
            events = self.config_procedure(
                "DCD Get",
                self.lib.btmesh.config_client.get_dcd,
                node,
                self.DCD_PAGE_0,
                final_event_name="btmesh_evt_config_client_dcd_data_end",
                output_event_names="btmesh_evt_config_client_dcd_data",
                retry_params=retry_params,
            )
        dcd_data = self.concat_config_event_bytes(
            attr="data", events=events, event_filter=lambda e: e.page == 0
        )
        dcd = self.parse_dcd(dcd_data)
        if update_db:
            node.dcd = dcd
        return dcd

    def parse_dcd(self, dcd_data):
        if len(dcd_data) < self.DCD_HEADER_LEN:
            raise BtmeshError(
                BtmeshErrorCode.INVALID_DCD,
                f"DCD data shall be min {self.DCD_HEADER_LEN} bytes long.",
                dcd_data=dcd_data,
            )
        cid = int.from_bytes(dcd_data[0:2], byteorder="little")
        pid = int.from_bytes(dcd_data[2:4], byteorder="little")
        vid = int.from_bytes(dcd_data[4:6], byteorder="little")
        crpl = int.from_bytes(dcd_data[6:8], byteorder="little")
        relay = bool(dcd_data[8] & 0x01)
        proxy = bool(dcd_data[8] & 0x02)
        friend = bool(dcd_data[8] & 0x04)
        lpn = bool(dcd_data[8] & 0x08)

        elements = self.parse_dcd_elements(dcd_data)

        dcd = DCD(
            cid=cid,
            pid=pid,
            vid=vid,
            crpl=crpl,
            relay=relay,
            proxy=proxy,
            friend=friend,
            lpn=lpn,
            elements=elements,
        )
        return dcd

    def parse_dcd_elements(self, dcd_data):
        dcd_data_elems = dcd_data[self.DCD_HEADER_LEN :]
        elements = []
        while 0 < len(dcd_data_elems):
            if len(dcd_data_elems) < self.DCD_ELEM_HEADER_LEN:
                raise BtmeshError(
                    BtmeshErrorCode.INVALID_DCD,
                    f"DCD element data shall be min {self.DCD_ELEM_HEADER_LEN} "
                    f"bytes long.",
                    dcd_data=dcd_data,
                )
            loc = int.from_bytes(dcd_data_elems[0:2], byteorder="little")
            num_s = dcd_data_elems[2]
            num_v = dcd_data_elems[3]
            elem_models_len = (
                num_s * self.DCD_SIG_MODEL_LEN + num_v * self.DCD_VENDOR_MODEL_LEN
            )
            elem_len = self.DCD_ELEM_HEADER_LEN + elem_models_len
            if len(dcd_data_elems) < elem_len:
                raise BtmeshError(
                    BtmeshErrorCode.INVALID_DCD,
                    f"DCD element data shall be {elem_len} bytes long.",
                    dcd_data=dcd_data,
                )
            dcd_model_data = dcd_data_elems[
                self.DCD_ELEM_HEADER_LEN : self.DCD_ELEM_HEADER_LEN + elem_len
            ]
            models = self.parse_dcd_models(
                num_s=num_s, num_v=num_v, dcd_model_data=dcd_model_data
            )
            element = DCDElement(len(elements), loc, models)
            elements.append(element)
            dcd_data_elems = dcd_data_elems[elem_len:]
        return elements

    def parse_dcd_models(self, num_s, num_v, dcd_model_data):
        sig_mdl_start = 0
        sig_mdl_end = sig_mdl_start + num_s * self.DCD_SIG_MODEL_LEN
        vendor_mdl_start = sig_mdl_end
        vendor_mdl_end = vendor_mdl_start + num_v * self.DCD_VENDOR_MODEL_LEN
        models = []
        for idx in range(sig_mdl_start, sig_mdl_end, self.DCD_SIG_MODEL_LEN):
            model_id_bytes = dcd_model_data[idx : idx + self.DCD_MODEL_ID_LEN]
            model_id = int.from_bytes(model_id_bytes, byteorder="little")
            mdl = ModelID(model_id)
            models.append(mdl)
        for idx in range(vendor_mdl_start, vendor_mdl_end, self.DCD_VENDOR_MODEL_LEN):
            vendor_id_start = idx
            vendor_id_end = vendor_id_start + self.DCD_VENDOR_ID_LEN
            mdl_id_start = vendor_id_end
            mdl_id_end = mdl_id_start + self.DCD_MODEL_ID_LEN
            vendor_id_bytes = dcd_model_data[vendor_id_start:vendor_id_end]
            model_id_bytes = dcd_model_data[mdl_id_start:mdl_id_end]
            vendor_id = int.from_bytes(vendor_id_bytes, byteorder="little")
            model_id = int.from_bytes(model_id_bytes, byteorder="little")
            mdl = ModelID(model_id, vendor_id)
            models.append(mdl)
        return models

    def get_dcd_cached(
        self,
        node: Node,
        retry_params: BtmeshRetryParams = None,
    ) -> DCD:
        if node.dcd is None:
            self.get_dcd(node, update_db=True, retry_params=retry_params)
        return node.dcd

    def add_appkey(
        self,
        node: Node,
        appkey_index: int,
        netkey_index: int,
        retry_params: BtmeshRetryParams = None,
    ):
        self.config_procedure(
            "Add Application Key",
            self.lib.btmesh.config_client.add_appkey,
            node,
            appkey_index,
            netkey_index,
            final_event_name="btmesh_evt_config_client_appkey_status",
            retry_params=retry_params,
        )
        # If the configuration fails then an exception is raised so it can be
        # assumed that the configuration was successful.
        node.add_appkey_index(appkey_index)

    def remove_appkey(
        self,
        node: Node,
        appkey_index: int,
        netkey_index: int,
        retry_params: BtmeshRetryParams = None,
    ):
        self.config_procedure(
            "Remove Application Key",
            self.lib.btmesh.config_client.remove_appkey,
            node,
            appkey_index,
            netkey_index,
            final_event_name="btmesh_evt_config_client_appkey_status",
            retry_params=retry_params,
        )
        # If the configuration fails then an exception is raised so it can be
        # assumed that the configuration was successful.
        if node.has_appkey_index(appkey_index):
            # The condition handles the corner case when there is inconsistency
            # between the cached appkey data in the database and state of the
            # remote node.
            node.remove_appkey_index(appkey_index)

    def bind_model(
        self,
        node: Node,
        elem_index: int,
        model: ModelID,
        appkey_index: int,
        retry_params: BtmeshRetryParams = None,
    ):
        self.config_procedure(
            "Bind Model",
            self.lib.btmesh.config_client.bind_model,
            node,
            elem_index,
            model.vendor_id,
            model.model_id,
            appkey_index,
            final_event_name="btmesh_evt_config_client_binding_status",
            retry_params=retry_params,
        )

    def unbind_model(
        self,
        node: Node,
        elem_index: int,
        model: ModelID,
        appkey_index: int,
        retry_params: BtmeshRetryParams = None,
    ):
        self.config_procedure(
            "Unbind Model",
            self.lib.btmesh.config_client.unbind_model,
            node,
            elem_index,
            model.vendor_id,
            model.model_id,
            appkey_index,
            final_event_name="btmesh_evt_config_client_binding_status",
            retry_params=retry_params,
        )

    def add_model_sub(
        self,
        node: Node,
        elem_index: int,
        model: ModelID,
        sub_address: int,
        retry_params: BtmeshRetryParams = None,
    ):
        self.config_procedure(
            "Add Model Subscription",
            self.lib.btmesh.config_client.add_model_sub,
            node,
            elem_index,
            model.vendor_id,
            model.model_id,
            sub_address,
            final_event_name="btmesh_evt_config_client_model_sub_status",
            retry_params=retry_params,
        )

    def remove_model_sub(
        self,
        node: Node,
        elem_index: int,
        model: ModelID,
        sub_address: int,
        retry_params: BtmeshRetryParams = None,
    ):
        self.config_procedure(
            "Remove Model Subscription",
            self.lib.btmesh.config_client.remove_model_sub,
            node,
            elem_index,
            model.vendor_id,
            model.model_id,
            sub_address,
            final_event_name="btmesh_evt_config_client_model_sub_status",
            retry_params=retry_params,
        )

    def set_model_pub(
        self,
        node: Node,
        elem_index: int,
        model: ModelID,
        pub_address: int,
        appkey_index: int,
        credentials: int,
        ttl: int,
        period_ms: int,
        retransmit_count: int,
        retransmit_interval_ms: int,
        retry_params: BtmeshRetryParams = None,
    ):
        self.config_procedure(
            "Add Model Publication",
            self.lib.btmesh.config_client.set_model_pub,
            node,
            elem_index,
            model.vendor_id,
            model.model_id,
            pub_address,
            appkey_index,
            credentials,
            ttl,
            period_ms,
            retransmit_count,
            retransmit_interval_ms,
            final_event_name="btmesh_evt_config_client_model_pub_status",
            retry_params=retry_params,
        )

    def reset_node(
        self,
        node: Node,
        local: bool = False,
        remove_node_on_retry_limit: bool = False,
        retry_params: BtmeshRetryParams = None,
    ):
        if node.uuid == self.db.prov_uuid:
            raise BtmeshError(
                err=BtmeshErrorCode.CONFIG_RESET_PROV_FORBIDDEN,
                message=f"Node reset is not allowed on the provisioner "
                f"(uuid: {node.uuid.hex()}).",
            )
        if not local:
            try:
                self.config_procedure(
                    "Node Reset",
                    self.lib.btmesh.config_client.reset_node,
                    node,
                    final_event_name="btmesh_evt_config_client_reset_status",
                    retry_params=retry_params,
                )
            except BtmeshError as e:
                if not (
                    remove_node_on_retry_limit
                    and (e.err == BtmeshErrorCode.CONFIG_FAILED)
                    and (e.event.result == SlStatus.TIMEOUT)
                ):
                    raise
        try:
            self.lib.btmesh.prov.delete_ddb_entry(node.uuid)
            evt = self.lib.wait_event(
                event_selector="btmesh_evt_prov_delete_ddb_entry_complete",
                uuid=node.uuid,
            )
            if evt.result != SlStatus.OK:
                raise BtmeshError(
                    err=BtmeshErrorCode.CONFIG_FAILED,
                    message=f"Failed to delete ddb entry with {node.uuid.hex()} "
                    f"uuid from device database due to "
                    f'"{SlStatus.get_name(evt.result)}" error.',
                    result=evt.result,
                )
        except CommandFailedError as e:
            if e.errorcode != SlStatus.BT_MESH_DOES_NOT_EXIST:
                raise
        self.db.remove_node(node)

    def bind_local_mdl(
        self, elem_index: int, model: ModelID, appkey_index: int
    ) -> None:
        self.lib.btmesh.test.bind_local_model_app(
            elem_index, appkey_index, model.vendor_id, model.model_id
        )

    def unbind_local_mdl(
        self, elem_index: int, model: ModelID, appkey_index: int
    ) -> None:
        self.lib.btmesh.test.unbind_local_model_app(
            elem_index, appkey_index, model.vendor_id, model.model_id
        )

    def list_local_bindings(self, elem_index: int, model: ModelID) -> List[int]:
        rsp = self.lib.btmesh.test.get_local_model_app_bindings(
            elem_index, model.vendor_id, model.model_id
        )
        appkey_indexes = util.bytes_to_int_list(rsp.appkeys, 2, byteorder="little")
        return appkey_indexes

    def silabs_conf_clt_init(self):
        try:
            self.lib.btmesh.silabs_config_client.init()
        except CommandError:
            self.silabs_conf_clt_fail = True
        else:
            self.silabs_conf_clt_fail = False

    def silabs_conf_svr_init(self):
        try:
            self.lib.btmesh.silabs_config_server.init()
        except CommandError:
            self.silabs_conf_svr_fail = True
        else:
            self.silabs_conf_svr_fail = False

    def silabs_conf_procedure(
        self,
        cmd,
        nodes: Union[Node, Iterable[Node]],
        group_addr: int,
        appkey_index: int,
        *args,
        final_event_name: str,
        silabs_conf_status_class: SilabsConfBaseStatus,
        retry_params: BtmeshRetryParams = None,
        **final_event_params,
    ):
        if isinstance(nodes, Node):
            nodes = [nodes]
        if retry_params is None:
            retry_params = self.silabs_retry_params_default
        # If there is at least one LPN in the nodes then the LPN specific retry
        # interval is used instead of the regular one.
        if retry_params.retry_interval != retry_params.retry_interval_lpn:
            any_lpn = self.any_lpn(nodes, skip_local=True)
            retry_params = retry_params.to_base(use_interval_lpn=any_lpn)
        else:
            retry_params = retry_params.to_base(use_interval_lpn=False)
        status_evt_list = []
        if group_addr is util.UNASSIGNED_ADDR:
            for node in nodes:
                try:
                    status_evt = self.lib.retry_until(
                        cmd,
                        node.prim_addr,
                        appkey_index,
                        *args,
                        **retry_params.to_dict(),
                        retry_cmd_err_code=[SlStatus.NO_MORE_RESOURCE],
                        event_selector=final_event_name,
                        server=node.prim_addr,
                        **final_event_params,
                    )[0]
                except BGLibExtWaitEventError as e:
                    continue
                status_evt_list.append(status_evt)
        else:
            util.validate_group_address(group_addr)
            event_selector = {
                final_event_name: {
                    "#unique": "server",
                    "server": EventParamValues(n.prim_addr for n in nodes),
                }
            }
            event_selector[final_event_name].update(final_event_params)
            try:
                status_evt_list = self.lib.retry_until(
                    cmd,
                    group_addr,
                    appkey_index,
                    *args,
                    retry_int_rst_on_evt=True,
                    **retry_params.to_dict(),
                    retry_cmd_err_code=[SlStatus.NO_MORE_RESOURCE],
                    event_selector=event_selector,
                    final_event_count=len(nodes),
                )
            except BGLibExtWaitEventError as e:
                status_evt_list = e.events
        status_list = []
        for node in nodes:
            for evt in status_evt_list:
                if node.prim_addr == evt.server:
                    status = silabs_conf_status_class.from_event(node, evt)
                    break
            else:
                status = silabs_conf_status_class.create_status_timeout(node)
            status_list.append(status)
        return status_list

    def silabs_set_tx(
        self,
        nodes: Union[Node, Iterable[Node]],
        tx_phy: SilabsConfTxPhy,
        tx_opt: SilabsConfTxOpt,
        group_addr: int = util.UNASSIGNED_ADDR,
        appkey_index: int = 0,
        retry_params: BtmeshRetryParams = None,
    ) -> List[SilabsConfTxStatus]:
        return self.silabs_conf_procedure(
            self.lib.btmesh.silabs_config_client.set_tx,
            nodes,
            group_addr,
            appkey_index,
            tx_phy.value,
            tx_opt.value,
            final_event_name="btmesh_evt_silabs_config_client_tx_status",
            silabs_conf_status_class=SilabsConfTxStatus,
            retry_params=retry_params,
        )

    def silabs_set_model_enable(
        self,
        nodes: Union[Node, Iterable[Node]],
        elem_index: int,
        model: ModelID,
        enable: bool,
        group_addr: int = util.UNASSIGNED_ADDR,
        appkey_index: int = 0,
        retry_params: BtmeshRetryParams = None,
    ) -> List[SilabsConfModelStatus]:
        return self.silabs_conf_procedure(
            self.lib.btmesh.silabs_config_client.set_model_enable,
            nodes,
            group_addr,
            appkey_index,
            elem_index,
            model.vendor_id,
            model.model_id,
            enable,
            final_event_name="btmesh_evt_silabs_config_client_model_status",
            silabs_conf_status_class=SilabsConfModelStatus,
            retry_params=retry_params,
            elem_index=elem_index,
            vendor_id=model.vendor_id,
            model_id=model.model_id,
        )

    def silabs_set_network_pdu(
        self,
        nodes: Union[Node, Iterable[Node]],
        pdu_max_size: int,
        group_addr: int = util.UNASSIGNED_ADDR,
        appkey_index: int = 0,
        retry_params: BtmeshRetryParams = None,
    ) -> List[SilabsConfNetworkPduStatus]:
        return self.silabs_conf_procedure(
            self.lib.btmesh.silabs_config_client.set_network_pdu,
            nodes,
            group_addr,
            appkey_index,
            pdu_max_size,
            final_event_name="btmesh_evt_silabs_config_client_network_pdu_status",
            silabs_conf_status_class=SilabsConfNetworkPduStatus,
            retry_params=retry_params,
        )

    def get_local_network_pdu_size(self):
        if self.silabs_conf_support:
            resp = self.lib.btmesh.silabs_config_server.get_network_pdu()
            return resp.max_size
        else:
            return util.STANDARD_NETWORK_PDU_SIZE
