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
import logging
from typing import ClassVar, Dict, Iterable, Iterator, Optional, Tuple

from bgapi.bglib import BGEvent, CommandFailedError
from bgapix.bglibx import BGLibExtWaitEventError
from bgapix.slstatus import SlStatus

from . import util
from .core import BtmeshComponent, BtmeshCore
from .db import (ConnectionInfo, ConnectionStep, GapAddrType, GapPhy, Node,
                 ProxyInfo, ProxyStep)
from .errors import BtmeshError, BtmeshErrorCode
from .event import LocalEvent
from .util import BleSecurityMode, ConnectionParams, ConnectionParamsRange

logger = logging.getLogger(__name__)


@dataclasses.dataclass
class ProxyDisconnectedEvent(LocalEvent):
    name: ClassVar[str] = "btmesh_levt_proxy_disconnected"
    node: Node
    reason: SlStatus


@dataclasses.dataclass
class ConnectionClosedEvent(LocalEvent):
    name: ClassVar[str] = "btmesh_levt_connection_closed"
    conn_handle: int
    reason: SlStatus


class Proxy(BtmeshComponent):
    NETKEY_IDX = 0

    def __init__(self, core: BtmeshCore):
        self._core = core

    @property
    def core(self) -> BtmeshCore:
        return self._core

    @core.setter
    def core(self, value) -> None:
        self._core = value
        if self.lib:
            self.lib.subscribe(
                "bt_evt_system_boot",
                self.on_system_boot,
            )
            self.lib.subscribe(
                "bt_evt_connection_parameters",
                self.on_connection_parameters,
            )
            self.lib.subscribe(
                "bt_evt_gatt_mtu_exchanged",
                self.on_gatt_mtu_exchanged,
            )
            self.lib.subscribe(
                "bt_evt_connection_closed",
                self.on_connection_closed,
            )
            self.lib.subscribe(
                "btmesh_evt_proxy_disconnected",
                self.on_proxy_disconnected,
            )

    def on_system_boot(self, event: BGEvent) -> None:
        self.db.clear_all_conns()

    def on_connection_parameters(self, event: BGEvent) -> None:
        conn_handle = event.connection
        if self.db.is_bt_conn_exists(conn_handle):
            interval_ms = event.interval * util.CONN_INTERVAL_MS_RES
            latency = event.latency
            timeout_ms = event.timeout * util.CONN_TIMEOUT_MS_RES
            security_mode = BleSecurityMode.from_int(event.security_mode)
            txsize = event.txsize
            conn_params = ConnectionParams(
                interval_ms=interval_ms,
                latency=latency,
                timeout_ms=timeout_ms,
                security_mode=security_mode,
                txsize=txsize,
            )
            conn_info = self.db.get_bt_conn_info_by_conn_handle(conn_handle)
            conn_info.conn_params = conn_params
        else:
            logger.warning(
                f"Connection parameter change for unknown bluetooth connection "
                f"with {conn_handle} connection handle."
            )

    def on_gatt_mtu_exchanged(self, event: BGEvent):
        conn_handle = event.connection
        if self.db.is_bt_conn_exists(conn_handle):
            conn_info = self.db.get_bt_conn_info_by_conn_handle(conn_handle)
            conn_info.mtu = event.mtu
        else:
            logger.warning(
                f"GATT MTU exchange for unknown bluetooth connection "
                f"with {conn_handle} connection handle."
            )

    def on_connection_closed(self, event: BGEvent) -> None:
        reason = SlStatus.from_int(event.reason)
        conn_handle: int = event.connection
        if self.db.is_bt_conn_exists(conn_handle):
            # If connection is closed then it is guaranteed that the proxy
            # connection is closed in the BT Mesh stack so no proxy related
            # activity shall be performed here.
            conn_info = self.get_bt_conn_info_by_conn_handle(conn_handle)
            if conn_info.step != ConnectionStep.CLOSING:
                levt = ConnectionClosedEvent(conn_handle=conn_handle, reason=reason)
                self.evtbus.emit(levt)
            self.db.remove_bt_conn_handle(conn_handle)

    def on_proxy_disconnected(self, event: BGEvent) -> None:
        proxy_handle = event.handle
        proxy_info = self.db.get_proxy_info_by_proxy_handle(proxy_handle)
        # Handle unexpected disconnections only.
        # If the proxy connection is terminated by upper layer then no local
        # event is generated.
        if (proxy_info is not None) and (proxy_info.step != ProxyStep.DISCONNECTING):
            self.db.remove_proxy_handle(proxy_handle)
            try:
                if self.db.node_uuid_exists(proxy_info.node_uuid):
                    node = self.db.get_node_by_uuid(proxy_info.node_uuid)
                    reason = SlStatus.from_int(event.reason)
                    levt = ProxyDisconnectedEvent(
                        node=node,
                        reason=reason,
                    )
                    self.evtbus.emit(levt)
                if self.db.is_bt_conn_exists(proxy_info.conn_handle):
                    self.bt_connection_close(proxy_info.conn_handle)
            except CommandFailedError as e:
                if self.db.node_uuid_exists(proxy_info.node_uuid):
                    node = self.db.get_node_by_uuid(proxy_info.node_uuid)
                    node_name = node.name
                else:
                    node_name = "UNKNOWN"
                logger.warning(
                    f"Close connection to {node_name} node failed "
                    f"with {SlStatus.get_name(e.errorcode)} error during "
                    f"proxy disconnection."
                )
                raise
            finally:
                if self.db.get_bt_conn_count() == 0:
                    self.lib.btmesh.test.set_adv_bearer_state(1)
        # Make sure that ADV Bearer is enabled when the last proxy connection
        # is terminated unexpectedly.
        if self.db.get_bt_conn_count() == 0:
            self.lib.btmesh.test.set_adv_bearer_state(1)

    def validate_conn_handle(self, conn_handle: int) -> None:
        if not self.db.is_bt_conn_exists(conn_handle):
            raise BtmeshError(
                err=BtmeshErrorCode.BT_CONN_DOES_NOT_EXIST,
                message=(
                    f"No active bluetooth connection is established "
                    f"with {conn_handle} connection handle."
                ),
                conn_handle=conn_handle,
            )

    def verify_active_connections(self):
        # It is possible that the NCP connection was closed (e.g. app shutdown)
        # and opened again without system reset.
        # It is important to check if the proxy and BLE connections in the
        # database are still active because the NCP node might have been reset
        # while the NCP communication was not active.
        # Local variable is created to avoid modifying underlying data structure
        # during iteration.
        proxy_info_list = list(self.proxy_conns)
        for proxy_info in proxy_info_list:
            # Remove dangling proxy connections without BLE connection
            conn_handle = proxy_info.conn_handle
            if not self.is_bt_conn_exists(conn_handle):
                self.db.remove_proxy_handle(proxy_info.proxy_handle)
                continue
        # Local variable is created to avoid modifying underlying data structure
        # during iteration.
        conn_info_list = list(self.bt_conns)
        for conn_info in conn_info_list:
            conn_handle = conn_info.conn_handle
            try:
                self.lib.bt.connection.get_rssi(conn_handle)
            except CommandFailedError as e:
                logger.error(
                    f"Bluetooth connection with {conn_handle} connection handle "
                    f"was terminated unexpectedly while the NCP communication "
                    f"was inactive."
                )
                proxy_info = self.get_proxy_info_by_bt_conn_handle(conn_handle)
                if proxy_info:
                    proxy_handle = proxy_info.proxy_handle
                    logger.error(
                        f"Proxy connection with {proxy_handle} proxy handle "
                        f"was terminated unexpectedly while the NCP communication "
                        f"was inactive."
                    )
                    node_uuid = proxy_info.node_uuid
                    if self.db.node_uuid_exists(node_uuid):
                        node = self.db.get_node_by_uuid(node_uuid)
                        levt = ProxyDisconnectedEvent(
                            node=node,
                            reason=SlStatus.BT_UNSPECIFIED,
                        )
                        self.evtbus.emit(levt)
                    self.db.remove_proxy_handle(proxy_handle)
                self.db.remove_bt_conn_handle(conn_handle)
        if self.get_proxy_count() == 0:
            self.lib.btmesh.test.set_adv_bearer_state(1)

    def bt_connection_open(
        self,
        bd_addr: str,
        bd_addr_type: GapAddrType,
        ini_phy: GapPhy = GapPhy.LE_1M,
        conn_open_timeout_ms: float = 5_000.0,
        conn_params_range: Optional[ConnectionParamsRange] = None,
    ) -> ConnectionInfo:
        sc, conn_handle = self.lib.bt.connection.open(bd_addr, bd_addr_type, ini_phy)
        # The bluetooth stack keeps trying to open the connection forever.
        # If the connection was not opened until the timeout then the
        # connection establishment process is stopped and the exception is
        # raised again.
        conn_info = ConnectionInfo(
            conn_handle=conn_handle,
            bd_addr=bd_addr,
            bd_addr_type=bd_addr_type,
            ini_phy=ini_phy,
            timeout_ms=0.0,
            mtu=0,
            step=ConnectionStep.OPENING,
        )
        self.db.add_bt_conn_info(conn_info)
        try:
            conn_params_event = self.lib.wait_event(
                event_selector="bt_evt_connection_parameters",
                max_time=conn_open_timeout_ms / 1000.0,
                connection=conn_handle,
            )
            conn_info.step = ConnectionStep.ACTIVE
        except Exception as e:
            # If any exception occurs then the connection establishment shall be
            # stopped or the active connection shall be closed.
            # Typical scenario: The target node is non-responsive so the timeout
            # mechanism makes sure the connection open procedure is stopped.
            self.bt_connection_close(conn_handle)
            raise
        conn_info.timeout_ms = conn_params_event.timeout * util.CONN_TIMEOUT_MS_RES
        if conn_params_range:
            # If custom connection parameters are provided then those are
            # configured in the BLE stack.
            try:
                self.bt_connection_set_params(conn_handle, conn_params_range)
            except Exception as e:
                self.bt_connection_close(bd_addr)
                raise
        return conn_info

    def bt_connection_set_params(
        self, conn_handle: int, conn_params_range: ConnectionParamsRange
    ) -> None:
        self.validate_conn_handle(conn_handle)
        conn_info = self.db.get_bt_conn_info_by_conn_handle(conn_handle)
        raw_conn_params_range = conn_params_range.to_raw()
        self.lib.bt.connection.set_parameters(
            conn_handle,
            raw_conn_params_range.min_interval,
            raw_conn_params_range.max_interval,
            raw_conn_params_range.latency,
            raw_conn_params_range.timeout,
            raw_conn_params_range.min_ce_length,
            raw_conn_params_range.max_ce_length,
        )
        self.lib.wait_event(
            "bt_evt_connection_parameters",
            max_time=conn_info.timeout_ms / 1000.0,
            connection=conn_handle,
        )

    def bt_connection_close(self, conn_handle: int) -> None:
        self.validate_conn_handle(conn_handle)
        conn_info = self.db.get_bt_conn_info_by_conn_handle(conn_handle)
        conn_info.step = ConnectionStep.CLOSING
        self.lib.bt.connection.close(conn_handle)
        self.lib.wait_event(
            event_selector="bt_evt_connection_closed",
            max_time=conn_info.timeout_ms / 1000.0,
            connection=conn_handle,
        )
        conn_info.step = ConnectionStep.INACTIVE
        self.db.remove_bt_conn_handle(conn_handle)

    def connect(
        self,
        node: Node,
        ini_phy: GapPhy = GapPhy.LE_1M,
        scan_time: float = 2.0,
        conn_open_timeout_ms: float = 5_000.0,
        conn_params_range: Optional[ConnectionParamsRange] = None,
    ) -> ProxyInfo:
        if self.db.is_proxy_conn_exists(node):
            raise BtmeshError(
                err=BtmeshErrorCode.PROXY_NODE_CONN_ALREADY_EXISTS,
                message=f"Proxy connection with {node.name} already exists.",
                node=node,
            )
        bd_addr, bd_addr_type = self.scan_for_proxy_node_bd_addr(
            node=node, scan_time=scan_time
        )
        conn_info = self.bt_connection_open(
            bd_addr=bd_addr,
            bd_addr_type=bd_addr_type,
            ini_phy=ini_phy,
            conn_open_timeout_ms=conn_open_timeout_ms,
            conn_params_range=conn_params_range,
        )
        sc, proxy_handle = self.lib.btmesh.proxy.connect(conn_info.conn_handle)
        proxy_info = ProxyInfo(
            proxy_handle=proxy_handle,
            conn_handle=conn_info.conn_handle,
            node_uuid=node.uuid,
            step=ProxyStep.CONNECTING,
        )
        self.db.add_proxy_info(proxy_info)
        try:
            self.lib.wait_event(
                event_selector="btmesh_evt_proxy_connected",
                max_time=conn_open_timeout_ms / 1000.0,
                handle=proxy_handle,
            )
        except BGLibExtWaitEventError as e:
            self.disconnect(node)
            raise BtmeshError(
                BtmeshErrorCode.PROXY_CONNECT_TIMEOUT,
                f"Proxy connection establishment timeout with {node.name} node.",
                node=node,
            ) from e
        self.lib.btmesh.test.set_adv_bearer_state(0)
        proxy_info.step = ProxyStep.ACTIVE
        return proxy_info

    def disconnect(self, node: Node) -> None:
        if not self.db.is_proxy_conn_exists(node):
            raise BtmeshError(
                err=BtmeshErrorCode.PROXY_NODE_CONN_DOES_NOT_EXIST,
                message=(
                    f"No active proxy connection is established "
                    f"with {node.name} node."
                ),
                node=node,
            )
        try:
            proxy_info = self.db.get_proxy_info_by_node(node)
            self.lib.btmesh.proxy.disconnect(proxy_info.proxy_handle)
            proxy_info.step = ProxyStep.DISCONNECTING
            conn_handle = proxy_info.conn_handle
            if self.is_bt_conn_exists(conn_handle):
                conn_info = self.get_bt_conn_info_by_conn_handle(conn_handle)
                max_time_ms = conn_info.timeout_ms
            else:
                max_time_ms = 10_000.0
                logger.warning(
                    f"Proxy connection with {proxy_info.proxy_handle} proxy "
                    f"handle refers to non-existent BLE connection with "
                    f"{conn_handle} connection handle."
                )
            self.lib.wait_event(
                event_selector="btmesh_evt_proxy_disconnected",
                max_time=max_time_ms / 1000.0,
                handle=proxy_info.proxy_handle,
            )
        finally:
            proxy_info.step = ProxyStep.INACTIVE
            self.db.remove_proxy_handle(proxy_info.proxy_handle)
            if self.db.get_proxy_count() == 0:
                self.lib.btmesh.test.set_adv_bearer_state(1)
            # The connection shall be closed because proxy disconnect doesn't
            # close the underlying BLE connection.
            self.bt_connection_close(proxy_info.conn_handle)

    def scan_for_proxy_node_bd_addr(
        self, node: Node, scan_time: float = 2.0
    ) -> Tuple[str, GapAddrType]:
        bd_addr = 0
        bd_addr_type = GapAddrType.UNKNOWN_VALUE
        # The gen_scan_reports method can yield legacy and extended advertisement
        # report scanner events.
        # All these events contain the advertisement data in the data attribute.
        for scan_report in self.gen_scan_reports(max_time=scan_time):
            sc, match = self.lib.btmesh.prov.test_identity(
                node.prim_addr, self.NETKEY_IDX, scan_report.data
            )
            if match:
                bd_addr = scan_report.address
                bd_addr_type = GapAddrType.from_int(scan_report.address_type)
                return bd_addr, bd_addr_type
        raise BtmeshError(
            BtmeshErrorCode.PROXY_CONNECT_SCAN_FAILED,
            f"No BT Mesh Proxy Service Advertisements are found from "
            f"{node.name} node.",
            node=node,
        )

    def gen_scan_reports(self, max_time: float = 2.0) -> Iterable[BGEvent]:
        try:
            # If the btmesh stack is initialized then the scanning is started
            # automatically however the scan reports are dropped by event filter
            # because it leads to high NCP traffic over serial port.
            # The BT scan report events are irrelevant for BT Mesh applications
            # most of the time because higher layer BT Mesh events are processed
            # by the application. (BT Mesh stack processes these internally)
            # The event filter shall be removed temporarily because the Proxy
            # Service Advertisements are available in Bluetooth Scan Reports.
            self.core.remove_scan_event_filters()
        except CommandFailedError as e:
            # The NOT_FOUND error is raised if the scanning filter is already
            # removed which is not an error in this case
            if e.errorcode != SlStatus.NOT_FOUND:
                raise
        try:
            for scan_report in self.lib.gen_events(
                event_selector=[
                    "bt_evt_scanner_legacy_advertisement_report",
                    "bt_evt_scanner_extended_advertisement_report",
                ],
                max_time=max_time,
                timeout=None,
            ):
                yield scan_report
        finally:
            # Turn on the event filtering again to spare NCP bandwidth
            self.core.add_scan_event_filters()

    @property
    def bt_conns(self) -> Iterator[ConnectionInfo]:
        yield from self.db.bt_conns

    @property
    def proxy_conns(self) -> Iterator[ProxyInfo]:
        yield from self.db.proxy_conns

    def get_bt_conn_count(self) -> int:
        return self.db.get_bt_conn_count()

    def get_proxy_count(self) -> int:
        return self.db.get_proxy_count()

    def get_bt_conn_info_by_conn_handle(
        self, conn_handle: int
    ) -> Optional[ConnectionInfo]:
        return self.db.get_bt_conn_info_by_conn_handle(conn_handle)

    def get_proxy_info_by_proxy_handle(self, proxy_handle: int) -> Optional[ProxyInfo]:
        return self.db.get_proxy_info_by_proxy_handle(proxy_handle)

    def get_proxy_info_by_node(self, node: Node) -> Optional[ProxyInfo]:
        return self.db.get_proxy_info_by_node(node)

    def get_proxy_info_by_bt_conn_handle(self, conn_handle: int):
        return self.db.get_proxy_info_by_bt_conn_handle(conn_handle)

    def get_bt_conn_handle_by_bd_addr(self, bd_addr: str) -> int:
        return self.db.get_bt_conn_handle_by_bd_addr(bd_addr)

    def is_bt_conn_exists(self, conn_handle: int) -> bool:
        return self.db.is_bt_conn_exists(conn_handle)

    def is_proxy_conn_exists(self, node: Node) -> bool:
        return self.db.is_proxy_conn_exists(node)

    def is_proxy_conn_with_conn_handle_exists(self, conn_handle: int) -> bool:
        return self.db.is_proxy_conn_with_conn_handle_exists(conn_handle)
