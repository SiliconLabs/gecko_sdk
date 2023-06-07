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

from typing import Optional, Tuple

from bgapix.bglibx import BGLibExtSyncSignalException
from btmesh.conf import NodeIdentityState
from btmesh.db import GapPhy, Node
from btmesh.proxy import ProxyDisconnectedEvent

from ..btmesh import app_btmesh
from ..cfg import app_cfg
from ..db import app_db
from ..ui import app_ui
from ..util.argparsex import ArgumentParserExt
from .cmd import BtmeshCmd


class BtmeshProxyDisconnected(Exception):
    def __init__(self, node: Optional[Node], *args: object) -> None:
        super().__init__(*args)
        self.node = node


class BtmeshProxyCmd(BtmeshCmd):
    NETKEY_IDX = 0

    @property
    def parser(self) -> ArgumentParserExt:
        return self.proxy_parser

    @property
    def current_parser(self) -> Optional[ArgumentParserExt]:
        return getattr(self, "_current_parser", self.parser)

    def create_parser(self, subparsers) -> ArgumentParserExt:
        self.proxy_parser = subparsers.add_parser(
            "proxy",
            prog="proxy",
            help="Handle connections with proxy servers.",
            description=(
                "Proxy commands supports the establishment of new connections "
                "with proxy servers and the termination of active connections. "
                "The active proxy connections can be listed and detailed "
                "information can be queried about active proxy connections. "
                "If there is at least one active proxy connection then the ADV "
                "bearer is disabled in order to use GATT bearer only. "
                "The proxy connection with a node is maintained until proxy "
                "disconnect command is called or until an unexpected termination "
                "of the proxy connection due to e.g. BLE connection supervision "
                "timeout."
            ),
            exit_on_error_ext=False,
        )
        self.proxy_subparser = self.proxy_parser.add_subparsers(
            dest="proxy_subcmd_name",
            title="Subcommands",
            required=True,
        )
        self.subparser_dict = dict(
            (
                self.create_proxy_connect_parser(self.proxy_subparser),
                self.create_proxy_disconnect_parser(self.proxy_subparser),
                self.create_proxy_list_parser(self.proxy_subparser),
                self.create_proxy_info_parser(self.proxy_subparser),
            )
        )
        return self.proxy_parser

    def __call__(self, arg) -> bool:
        pargs = self.parser.parse_args(arg.split())
        self._current_parser = self.subparser_dict.get(
            pargs.proxy_subcmd_name, self.parser
        )
        pargs.proxy_subcmd(pargs)
        self._current_parser = self.parser
        return False

    def create_proxy_connect_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "connect"
        self.proxy_connect_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Open proxy connection with specified node.",
            description=(
                "Open proxy connection with specified node. "
                "If a proxy connection is established then the ADV bearer "
                "is disabled in order to use GATT bearer only. "
                "If a signal (Ctrl+C or Command+.) is raised by the user during "
                "the connection establishment then the procedure is cancelled."
            ),
            exit_on_error_ext=False,
        )
        self.proxy_connect_parser.set_defaults(proxy_subcmd=self.proxy_connect_cmd)
        self.proxy_connect_parser.add_argument(
            "--conf-identity",
            "-i",
            action="store_true",
            help=(
                "Turn on node identity advertisement on target node. "
                "The default conf retry parameters are used during node identity "
                "configuration procedure."
            ),
        )
        self.proxy_connect_parser.add_argument(
            "--scan-timeout",
            type=float,
            metavar="TIME",
            default=app_cfg.proxy.scan_timeout_default,
            help=(
                "Scanning timeout for Proxy Service Advertisements "
                "with node identity in seconds."
                "(default: %(default)s)"
            )
        )
        self.add_node_pos_arg(
            self.proxy_connect_parser, help="Target node of proxy connection."
        )
        self.add_connection_open_timeout_arg(
            self.proxy_connect_parser,
            app_cfg.proxy.conn_open_timeout_ms_default,
        )
        self.add_connection_params_range_args(
            self.proxy_connect_parser,
            min_interval_ms_default=app_cfg.proxy.conn_min_interval_ms_default,
            max_interval_ms_default=app_cfg.proxy.conn_max_interval_ms_default,
            latency_default=app_cfg.proxy.conn_latency_default,
            timeout_ms_default=app_cfg.proxy.conn_timeout_ms_default,
            min_ce_length_ms_default=app_cfg.proxy.conn_min_ce_length_ms_default,
            max_ce_length_ms_default=app_cfg.proxy.conn_max_ce_length_ms_default,
        )
        return SUBPARSER_NAME, self.proxy_connect_parser

    def create_proxy_disconnect_parser(
        self, subparsers
    ) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "disconnect"
        self.proxy_disconnect_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Close active proxy connection with specified node.",
            description=(
                "Close active proxy connection with specified node. "
                "If the last proxy connection is terminated then the ADV bearer "
                "is enabled again."
            ),
            exit_on_error_ext=False,
        )
        self.proxy_disconnect_parser.set_defaults(
            proxy_subcmd=self.proxy_disconnect_cmd
        )
        self.proxy_disconnect_group = (
            self.proxy_disconnect_parser.add_mutually_exclusive_group(required=True)
        )
        self.proxy_disconnect_group.add_argument(
            "--all",
            action="store_true",
            help="All proxy connections shall be disconnected.",
        )
        self.add_node_pos_arg(
            self.proxy_disconnect_group,
            required=False,
            help="Node with active proxy connection.",
        )
        return SUBPARSER_NAME, self.proxy_disconnect_parser

    def create_proxy_list_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "list"
        self.proxy_list_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="List active proxy and BLE connections.",
            description="List active proxy and BLE connections.",
            exit_on_error_ext=False,
        )
        self.proxy_list_parser.set_defaults(proxy_subcmd=self.proxy_list_cmd)
        return SUBPARSER_NAME, self.proxy_list_parser

    def create_proxy_info_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "info"
        self.proxy_info_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Provide information about proxy connection with specified node.",
            description="Provide information about proxy connection with specified node.",
            exit_on_error_ext=False,
        )
        self.add_nodes_pos_arg(
            self.proxy_info_parser, help="Node with active proxy connection."
        )
        self.proxy_info_parser.set_defaults(proxy_subcmd=self.proxy_info_cmd)
        return SUBPARSER_NAME, self.proxy_info_parser

    def set_node_identity(self, node: Node, state: NodeIdentityState) -> None:
        # The default configuration retry parameters shall be used for the node
        # identity configuration in proxy command similarly to conf set command.
        # New BtmeshRetryParams instance is created during each property read
        # so it can be modified without overwriting the configuration value.
        btmesh_retry_params = app_cfg.common.btmesh_retry_params_default
        btmesh_retry_params.retry_max = app_cfg.conf.conf_retry_max_default
        btmesh_retry_params.retry_interval = app_cfg.conf.conf_retry_interval_default
        btmesh_retry_params.retry_interval_lpn = (
            app_cfg.conf.conf_retry_interval_lpn_default
        )
        app_btmesh.conf.set_node_identity(
            node=node,
            netkey_index=self.NETKEY_IDX,
            state=state,
            retry_params=btmesh_retry_params,
        )

    def proxy_connect_cmd(self, pargs):
        nodes = app_db.btmesh_db.get_node_list(order_property="name")
        node = self.parse_nodespec(pargs.nodespec, nodes)
        node_str = app_ui.node_str(node)
        conf_identity = pargs.conf_identity
        conn_open_timeout_ms = self.process_connection_open_timeout(pargs)
        conn_params_range = self.process_connection_params_range(
            pargs, app_cfg.proxy.conn_params_range
        )
        if conf_identity:
            self.set_node_identity(node=node, state=NodeIdentityState.ENABLED)
        try:
            app_btmesh.proxy.connect(
                node,
                ini_phy=GapPhy.LE_1M,
                scan_time=pargs.scan_timeout,
                conn_open_timeout_ms=conn_open_timeout_ms,
                conn_params_range=conn_params_range,
            )
            app_ui.info(f"Proxy connection is established with {node_str} node.")
            # The proxy disconnection handler is added at each successful proxy
            # connection but the first one has effect only because the same handler
            # is added to the subscription list once.
            app_btmesh.core.subscribe(
                "btmesh_levt_proxy_disconnected",
                self.on_proxy_disconnected,
            )
        except BGLibExtSyncSignalException as e:
            # The proxy connection establishment is canceled
            app_btmesh.proxy.disconnect(node)
            app_ui.info(
                f"Proxy connection establishment with {node_str} node is canceled."
            )

    def proxy_disconnect_cmd(self, pargs):
        if pargs.all:
            proxy_conns_list = list(app_btmesh.proxy.proxy_conns)
            for proxy_info in proxy_conns_list:
                node_uuid = proxy_info.node_uuid
                if app_db.btmesh_db.node_uuid_exists(node_uuid):
                    node = app_db.btmesh_db.get_node_by_uuid(node_uuid)
                    app_btmesh.proxy.disconnect(node)
                    node_str = app_ui.node_str(node)
                    app_ui.info(
                        f"Proxy connection is terminated with {node_str} node."
                    )
                else:
                    # There might be some nodes which are removed by configuration
                    # node reset but the proxy and BLE connection is not terminated
                    # because supervision timeout hasn't occurred yet.
                    # The proxy disconnect all should terminate each proxy
                    # and BLE connections so these should be removed from
                    # the database.
                    app_db.btmesh_db.remove_proxy_handle(proxy_info.proxy_handle)
                    app_db.btmesh_db.remove_bt_conn_handle(proxy_info.conn_handle)
        else:
            nodes = app_db.btmesh_db.get_node_list(order_property="name")
            node = self.parse_nodespec(pargs.nodespec, nodes)
            app_btmesh.proxy.disconnect(node)
            node_str = app_ui.node_str(node)
            app_ui.info(f"Proxy connection is terminated with {node_str} node.")

    def proxy_list_cmd(self, pargs):
        rows = []
        for proxy_info in app_btmesh.proxy.proxy_conns:
            if app_btmesh.proxy.is_bt_conn_exists(proxy_info.conn_handle):
                conn_info = app_btmesh.proxy.get_bt_conn_info_by_conn_handle(
                    proxy_info.conn_handle
                )
                bd_addr = conn_info.bd_addr
                bt_conn_step_str = conn_info.step.pretty_name
            else:
                bd_addr = "?"
                bt_conn_step_str = "?"
            if app_db.btmesh_db.node_uuid_exists(proxy_info.node_uuid):
                node = app_db.btmesh_db.get_node_by_uuid(proxy_info.node_uuid)
                node_str = app_ui.node_str(node)
            else:
                node_str = "?"
            proxy_dict = {}
            proxy_dict["Node"] = node_str
            proxy_dict["BLE Address"] = bd_addr
            proxy_dict["Proxy Connection"] = proxy_info.step.pretty_name
            proxy_dict["BLE Connection"] = bt_conn_step_str
            rows.append(proxy_dict)
        if 0 < len(rows):
            app_ui.table_info(rows)
        else:
            app_ui.info("No active proxy connections.")

    def proxy_info_cmd(self, pargs):
        nodes = app_db.btmesh_db.get_node_list(order_property="name")
        nodes = self.parse_nodespecs(pargs.nodespec, nodes)
        for node in nodes:
            if app_btmesh.proxy.is_proxy_conn_exists(node):
                continue
            node_str = app_ui.node_str(node)
            app_ui.error(
                f"No active proxy connection is established with {node_str} node."
            )
        for node in nodes:
            node_str = app_ui.node_str(node)
            if not app_btmesh.proxy.is_proxy_conn_exists(node):
                continue
            proxy_info = app_btmesh.proxy.get_proxy_info_by_node(node)
            app_ui.info(f"{node_str} node:")
            # Proxy Information
            proxy_handle = proxy_info.proxy_handle
            proxy_step_str = proxy_info.step.pretty_name
            # Bluetooth Connection Information
            conn_handle = proxy_info.conn_handle
            conn_info = app_btmesh.proxy.get_bt_conn_info_by_conn_handle(conn_handle)
            conn_bd_addr = "?"
            conn_bd_addr_type_str = "?"
            conn_ini_phy_str = "?"
            conn_params = "?"
            conn_interval_ms = "?"
            conn_latency = "?"
            conn_timeout_ms = "?"
            conn_security_mode_str = "?"
            conn_txsize = "?"
            conn_mtu = "?"
            conn_step_str = "?"
            if conn_info:
                conn_bd_addr = conn_info.bd_addr
                conn_bd_addr_type_str = conn_info.bd_addr_type.pretty_name
                conn_ini_phy_str = conn_info.ini_phy.pretty_name
                conn_step_str = conn_info.step.pretty_name
            if conn_info.conn_params:
                conn_params = conn_info.conn_params
                conn_interval_ms = conn_params.interval_ms
                conn_latency = conn_params.latency
                conn_timeout_ms = conn_params.timeout_ms
                conn_security_mode_str = conn_params.security_mode.pretty_name
                conn_txsize = conn_params.txsize
            if conn_info.mtu:
                conn_mtu = conn_info.mtu
            app_ui.info(f"  - Proxy handle: {proxy_handle}")
            app_ui.info(f"  - Proxy State: {proxy_step_str}")
            app_ui.info(f"  - BLE Connection: {conn_handle}")
            app_ui.info(f"    - Address: {conn_bd_addr}")
            app_ui.info(f"    - Address Type: {conn_bd_addr_type_str}")
            app_ui.info(f"    - IniPHY: {conn_ini_phy_str}")
            app_ui.info(f"    - Interval: {conn_interval_ms} ms")
            app_ui.info(f"    - Latency: {conn_latency}")
            app_ui.info(f"    - Timeout: {conn_timeout_ms} ms")
            app_ui.info(f"    - Security Mode: {conn_security_mode_str}")
            app_ui.info(f"    - TxSize: {conn_txsize}")
            app_ui.info(f"    - MTU: {conn_mtu}")
            app_ui.info(f"    - State: {conn_step_str}")

    # ProxyDisconnectedEvent is triggered on unexpected disconnection only.
    def on_proxy_disconnected(self, event: ProxyDisconnectedEvent):
        if event.node is None:
            # If the configuration node reset is performed then the node is
            # removed from the database so node is set to None in local event.
            node_str = "UNKNOWN"
        else:
            node_str = app_ui.node_str(event.node)
        raise BtmeshProxyDisconnected(
            event.node,
            f"Proxy connection to {node_str} node was terminated unexpectedly "
            f"with {event.reason.name} error."
        )


proxy_cmd = BtmeshProxyCmd()
