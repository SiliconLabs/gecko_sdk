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

from ..btmesh import app_btmesh
from ..cfg import app_cfg
from ..db import app_db
from ..ui import app_ui
from ..util.argparsex import ArgumentParserExt
from .cmd import BtmeshCmd


class BtmeshNodeCmd(BtmeshCmd):
    @property
    def parser(self) -> ArgumentParserExt:
        return self.node_parser

    @property
    def current_parser(self) -> Optional[ArgumentParserExt]:
        return getattr(self, "_current_parser", self.parser)

    def create_parser(self, subparsers) -> ArgumentParserExt:
        self.node_parser: ArgumentParserExt = subparsers.add_parser(
            "node",
            prog="node",
            help="Provide information about the nodes in the BT Mesh database.",
            description="Provide information about the nodes in the BT Mesh database. "
            "The %(prog)s command can be used to list nodes or to provide detailed "
            "information about specific nodes.",
            exit_on_error_ext=False,
        )
        self.node_parser.set_defaults(node_subcmd=self.node_list_cmd)
        self.node_parser.set_defaults(node_subcmd_name="list")
        self.node_subparser = self.node_parser.add_subparsers(
            dest="node_subcmd_name",
            title="Subcommands",
            description="If no subcommand is provided then it defaults to 'list'.",
        )
        self.subparser_dict = dict(
            (
                self.create_node_list_parser(self.node_subparser),
                self.create_node_info_parser(self.node_subparser),
                self.create_node_rename_parser(self.node_subparser),
            )
        )
        return self.node_parser

    def create_node_list_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "list"
        self.node_list_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="List nodes from BT Mesh database.",
            description="List nodes from BT Mesh database.",
            exit_on_error_ext=False,
        )
        self.node_list_parser.set_defaults(node_subcmd=self.node_list_cmd)
        self.node_list_parser.add_argument(
            "--all",
            action="store_true",
            help="All node properties are listed.",
        )
        for node_col in app_ui.NODE_COLUMNS:
            arg_name = node_col.replace("_", "-")
            help_name = app_ui.NODE_COLUMNS[node_col].lower()
            self.node_list_parser.add_argument(
                f"--{arg_name}",
                dest="columns",
                action="append_const",
                const=f"{node_col}",
                help=f"The node {help_name} is listed.",
            )
        return SUBPARSER_NAME, self.node_list_parser

    def create_node_info_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "info"
        self.node_info_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Provide information about the specified node.",
            description="Provide information about the specified node.",
            exit_on_error_ext=False,
        )
        self.node_info_parser.set_defaults(node_subcmd=self.node_info_cmd)
        self.add_nodes_pos_arg(
            self.node_info_parser,
            help="The %(metavar)s selects nodes which shall appear in %(prog)s report.",
        )
        self.node_info_parser.add_argument(
            "--force",
            "-f",
            action="store_true",
            help="Force DCD read from nodes to avoid using cached DCD.",
        )
        self.add_btmesh_basic_retry_args(
            self.node_info_parser,
            retry_max_default=app_cfg.conf.conf_retry_max_default,
            retry_interval_default=app_cfg.conf.conf_retry_interval_default,
            retry_interval_lpn_default=app_cfg.conf.conf_retry_interval_lpn_default,
            retry_max_help=(
                "Maximum number of additional Config Composition Data Get "
                "messages are sent until the Config Composition Data Status "
                "message is not received from the Config Server. "
                "(default: %(default)s)"
            ),
            retry_interval_help=(
                "Interval in seconds between Config Composition Data Get messages "
                "when the Config Composition Data Status message is not received "
                "from the Config Server. "
                "(default: %(default)s)"
            ),
            retry_interval_lpn_help=(
                "Interval in seconds between Config Composition Data Get messages "
                "when the Config Composition Data Status message is not received "
                "from the Config Server model of a Low Power Node. "
                "(default: %(default)s)"
            ),
        )
        return SUBPARSER_NAME, self.node_info_parser

    def create_node_rename_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "rename"
        self.node_rename_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Rename the specified node.",
            description="Rename the specified node.",
            exit_on_error_ext=False,
        )
        self.node_rename_parser.add_argument(
            "nodespec",
            metavar="<nodespec>",
            help="Specifies the node which shall be renamed. " + app_ui.NODESPEC_HELP,
        )
        self.node_rename_parser.add_argument(
            "newname",
            help="New name of the specified node.",
        )
        self.node_rename_parser.set_defaults(node_subcmd=self.node_rename_cmd)
        return SUBPARSER_NAME, self.node_rename_parser

    def __call__(self, arg) -> bool:
        pargs = self.parser.parse_args(arg.split())
        self._current_parser = self.subparser_dict.get(
            pargs.node_subcmd_name, self.parser
        )
        pargs.node_subcmd(pargs)
        self._current_parser = self.parser
        return False

    def node_list_cmd(self, pargs):
        node_list = app_db.btmesh_db.get_node_list(order_property="name")
        # The node command defaults to node list which means the all and columns
        # arguments does not exist in pargs so show the default columns in case
        # of an empty node command
        if hasattr(pargs, "all") and pargs.all:
            columns = app_ui.NODE_COLUMNS.keys()
        elif hasattr(pargs, "columns") and pargs.columns:
            columns = pargs.columns
        else:
            columns = None
        app_ui.nodes_info(node_list, columns)

    def node_info_cmd(self, pargs):
        nodes = app_db.btmesh_db.get_node_list(order_property="name")
        selected_nodes = self.parse_nodespecs(pargs.nodespec, nodes)
        retry_params_default = app_cfg.common.btmesh_retry_params_default
        retry_params = self.process_btmesh_retry_params(pargs, retry_params_default)
        for node in selected_nodes:
            if pargs.force:
                dcd = app_btmesh.conf.get_dcd(
                    node, update_db=True, retry_params=retry_params
                )
            else:
                dcd = app_btmesh.conf.get_dcd_cached(node, retry_params=retry_params)

            relay_str = "Yes" if dcd.relay else "No"
            proxy_str = "Yes" if dcd.proxy else "No"
            friend_str = "Yes" if dcd.friend else "No"
            lpn_str = "Yes" if dcd.lpn else "No"
            app_ui.info(f"{node.name} node:")
            app_ui.info(f"  - Primary Address: 0x{node.prim_addr:04X}")
            app_ui.info(f"  - UUID: {node.uuid.hex()}")
            app_ui.info(f"  - Company ID: 0x{dcd.cid:04X}")
            app_ui.info(f"  - Product ID: 0x{dcd.pid:04X}")
            app_ui.info(f"  - Version ID: 0x{dcd.vid:04X}")
            app_ui.info(f"  - CRPL: {dcd.cid}")
            app_ui.info(f"  - Features:")
            app_ui.info(f"    - Relay: {relay_str}")
            app_ui.info(f"    - Proxy: {proxy_str}")
            app_ui.info(f"    - Friend: {friend_str}")
            app_ui.info(f"    - Low Power: {lpn_str}")
            app_ui.info(f"  - Elements: ({node.elem_count})")
            for elem in dcd.elements:
                sig_mdls = [mdl for mdl in elem.models if mdl.is_sig_model()]
                vendor_mdls = [mdl for mdl in elem.models if mdl.is_vendor_model()]
                app_ui.info(f"    - Element {elem.idx}:")
                app_ui.info(f"      - Loc: {elem.loc:04X}")
                if len(sig_mdls):
                    app_ui.info(f"      - SIG Models:")
                    for mdl in sig_mdls:
                        app_ui.info(f"        - {mdl.pretty_name()}")
                if len(vendor_mdls):
                    app_ui.info(f"      - Vendor Models:")
                    for mdl in vendor_mdls:
                        app_ui.info(f"        - {mdl.pretty_name()}")

    def node_rename_cmd(self, pargs):
        nodes = app_db.btmesh_db.get_node_list(order_property="name")
        node = self.parse_nodespecs(pargs.nodespec, nodes)[0]
        app_db.btmesh_db.rename_node(node, pargs.newname)


node_cmd = BtmeshNodeCmd()
