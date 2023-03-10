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

import btmesh.util
from bgapix.bglibx import CommandFailedError
from bgapix.slstatus import SlStatus
from btmesh.conf import SilabsConfStatus, SilabsConfTxOpt, SilabsConfTxPhy
from btmesh.db import ModelID
from btmesh.errors import BtmeshError

from ..btmesh import app_btmesh
from ..cfg import app_cfg
from ..db import app_db
from ..ui import app_ui
from ..util.argparsex import ArgumentParserExt
from .cmd import BtmeshCmd


class BtmeshConfCmd(BtmeshCmd):
    @property
    def parser(self) -> ArgumentParserExt:
        return self.conf_parser

    @property
    def current_parser(self) -> Optional[ArgumentParserExt]:
        return getattr(self, "_current_parser", self.parser)

    def create_parser(self, subparsers) -> ArgumentParserExt:
        self.conf_parser = subparsers.add_parser(
            "conf",
            prog="conf",
            help="Configuration Client and Silabs Configuration Client commands.",
            description="Configuration Client and Silabs Configuration Client commands.",
            exit_on_error_ext=False,
        )
        self.conf_subparser = self.conf_parser.add_subparsers(
            dest="conf_subcmd_name",
            title="Subcommands",
            required=True,
        )
        self.subparser_dict = dict(
            (
                self.create_conf_reset_parser(self.conf_subparser),
                self.create_conf_ae_parser(self.conf_subparser),
            )
        )
        return self.conf_parser

    def add_mdl_profile_args(self, parser: ArgumentParserExt, sub_help=""):
        mdl_profile_choices = [mp.name for mp in app_cfg.appgroup.mdl_profiles]
        help_text = [
            f"Model profiles make it easier to select multiple models for "
            f"configuration. A model profile name refers to these model sets "
            f"from the configuration file."
        ]
        if sub_help:
            help_text.append(sub_help)
        for mp in app_cfg.appgroup.mdl_profiles:
            help_text.append(f"profile_{mp.name}: {mp.help}")
        parser.add_argument(
            "--profile",
            "-m",
            default=[],
            choices=mdl_profile_choices,
            nargs="+",
            help=" ".join(help_text),
        )

    def create_conf_reset_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "reset"
        self.conf_reset_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Perform node reset procedure on remote node to remove it from "
            "the BT Mesh network.",
            description="Perform node reset procedure on remote node to remove "
            "it from the BT Mesh network. It is possible to perform node reset "
            "locally which means no BT Mesh messages are sent but the node is "
            "removed from the database of the NCP node and from the database of "
            "the application.",
            exit_on_error_ext=False,
        )
        self.conf_reset_parser.set_defaults(conf_subcmd=self.conf_reset_cmd)
        self.conf_reset_parser.add_argument(
            "nodespec",
            nargs="+",
            metavar="<nodespec>",
            help=f"Target nodes of node reset procedure. The provisioner (NCP) "
            f"shall be reset by factory reset explicitly so it can't be the "
            f"target of this command. {app_ui.NODESPEC_HELP}",
        )
        self.conf_reset_parser.add_argument(
            "--local",
            "-l",
            action="store_true",
            help="Perform node reset locally only by removing the node from the "
            "NCP node (provisioner) device database and from the database of "
            "the application. "
            "Note: this is essential when the remote node was not reset by the "
            "provisioner for example node factory reset was initiated by the "
            "push buttons on the board.",
        )
        self.add_retry_max_arg(
            self.conf_reset_parser,
            app_cfg.conf.reset_node_retry_max_default,
            help=(
                "Maximum number of additional Config Node Reset messages are "
                "sent until the Config Node Reset Status message is received "
                "from the remote node. "
                "(default: %(default)s)"
            ),
        )
        self.add_retry_interval_arg(
            self.conf_reset_parser,
            app_cfg.conf.reset_node_retry_interval_default,
            help=(
                "Interval in seconds between Config Node Reset messages when "
                "the Config Node Reset Status message is not received from the "
                "remote node. "
                "(default: %(default)s)"
            ),
        )
        self.add_retry_interval_lpn_arg(
            self.conf_reset_parser,
            app_cfg.conf.reset_node_retry_interval_lpn_default,
            help=(
                "Interval in seconds between Config Node Reset messages when "
                "the Config Node Reset Status message is not received from the "
                "remote Low Power Node. "
                "(default: %(default)s)"
            ),
        )
        return SUBPARSER_NAME, self.conf_reset_parser

    def create_conf_ae_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "ae"
        self.conf_ae_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Activation of Silabs BT Mesh over Advertisement Extensions "
            "proprietary feature.",
            description="Activation of Silabs BT Mesh over Advertisement "
            "Extensions proprietary feature. The feature is not supported in "
            "Silabs BT Mesh SOC and NCP examples so some additional steps are "
            "necessary to add it to the embedded code. "
            "The NCP projects shall contain the following components: "
            "Silicon Labs Configuration Server Model, Silicon Labs Configuration "
            "Client Model and Proprietary Extended Advertiser. "
            "The SOC projects shall contain Advertisement Extension Server "
            "component which pulls in Silicon Labs Configuration Server Model "
            "and Proprietary Extended Advertiser components through dependencies. "
            "WARNING! If Proprietary Extended Advertiser component is added to "
            "the project then the BLE LL layer follows the AuxPtr in AE packets "
            "to secondary channels which means it does not scan primary channels "
            "in that time interval which lowers the scanning efficiency and "
            "makes the packet loss higher. This might be significant if there is "
            "considerable non-mesh related AE traffic due to other devices.",
            exit_on_error_ext=False,
        )
        self.conf_ae_parser.set_defaults(conf_subcmd=self.conf_ae_cmd)
        self.conf_ae_onoff_group = self.conf_ae_parser.add_mutually_exclusive_group()
        self.conf_ae_onoff_group.add_argument(
            "--en",
            action="store_true",
            help="Activate Silabs BT Mesh over Advertisement Extensions "
            "proprietary feature on specified models.",
        )
        self.conf_ae_onoff_group.add_argument(
            "--dis",
            action="store_true",
            help="Deactivate Silabs BT Mesh over Advertisement Extensions "
            "proprietary feature on specified models.",
        )
        self.conf_ae_parser.add_argument(
            "--appkey-idx",
            "-a",
            type=int,
            default=app_cfg.dist_clt.appkey_index_default,
            help="Appkey index used for sending Silicon Labs configuration "
            " messages. (default: %(default)s)",
        )
        # The tx_options is not implemented in BT Mesh stack so it is not
        # shown on the UI
        self.conf_ae_parser.add_argument(
            "--tx-phy",
            "-t",
            choices=["legacy", "1m", "2m"],
            help="TX PHY for long packets (packets that would be segmented).",
        )
        self.conf_ae_parser.add_argument(
            "--nw-pdu",
            "-p",
            type=int,
            help=f"Size of network PDU. The PDU size shall be in "
            f"[{btmesh.util.NW_PDU_LEN_MIN},{btmesh.util.NW_PDU_LEN_MAX}] range. "
            f"If it is greater than {btmesh.util.LEGACY_NW_PDU_LEN} then the "
            f"long packets which would be segmented in case of legacy advertiser "
            f"are sent in a single or multiple extended advertisements. "
            f"If the network PDU size is {btmesh.util.LEGACY_NW_PDU_LEN} then "
            f"the extended advertising packets are ignored by the BT Mesh stack.",
        )
        self.conf_ae_parser.add_argument(
            "--elems",
            "-e",
            type=int,
            default=[],
            nargs="+",
            help="List of node elements where the specified models shall be "
            "configured to enable or disable the transmission of long packets "
            "in extended advertisements.",
        )
        self.conf_ae_parser.add_argument(
            "--mdls",
            "-M",
            metavar="<mdlspec>",
            default=[],
            nargs="+",
            help=f"List of models which shall enable or disable transmission of "
            f"long packets in extended advertisement. If the AE feature is not "
            f"enabled for a model it uses legacy advertiser and segmentation for "
            f"long packets. {app_ui.MDLSPEC_HELP}",
        )
        self.add_mdl_profile_args(
            self.conf_ae_parser,
            sub_help=(
                "The transmission of long packets in extended advertisement is "
                "enabled or disabled for all models of the model profile."
            ),
        )
        self.add_btmesh_basic_retry_args(
            self.conf_ae_parser,
            retry_max_default=app_cfg.conf.silabs_retry_max_default,
            retry_interval_default=app_cfg.conf.silabs_retry_interval_default,
            retry_interval_lpn_default=app_cfg.conf.silabs_retry_interval_lpn_default,
            retry_max_help=(
                "Maximum number of additional Silabs Config Get or Set messages "
                "are sent until the Silabs Config Status message is not received "
                "from the Silabs Config Server. "
                "(default: %(default)s)"
            ),
            retry_interval_help=(
                "Interval in seconds between Silabs Config Get or Set messages "
                "when the Silabs Config Status message is not received from "
                "the Silabs Config Server. "
                "(default: %(default)s)"
            ),
            retry_interval_lpn_help=(
                "Interval in seconds between Silabs Config Get or Set messages "
                "when the Silabs Config Status message is not received from "
                "the Silabs Config Server model of a Low Power Node. "
                "(default: %(default)s)"
            ),
        )
        self.add_group_nodes_args(
            self.conf_ae_parser,
            add_elem_arg=False,
            add_elem_addrs_arg=False,
            elem_default=None,
            group_addr_help=(
                f"Subscription group address of Silicon Labs Configuration "
                f"Server on target nodes. If this option is present then the Silabs "
                f"configuration commands are sent to group address otherwise each "
                f"server is configured one by one in separate unicast messages. "
            ),
            group_help=(
                f"Specifies the app group which contains the nodes where the "
                f"Silicon Labs Configuration Server models shall be configured. "
                f"Note: the Silicon Labs Configuration Server shall be present on "
                f"primary element."
            ),
            nodes_help=(
                f"List of nodes where the Silicon Labs Configuration Server "
                f"models shall be configured. Note: the Silicon Labs Configuration "
                f"Server shall be present on the primary element."
            ),
        )
        return SUBPARSER_NAME, self.conf_ae_parser

    @classmethod
    def tx_phy_choice_to_enum(cls, choice):
        if choice == "1m":
            return SilabsConfTxPhy.LE_1M
        if choice == "2m":
            return SilabsConfTxPhy.LE_2M
        else:
            return SilabsConfTxPhy.LE_LEGACY

    def __call__(self, arg) -> bool:
        pargs = self.parser.parse_args(arg.split())
        self._current_parser = self.subparser_dict.get(
            pargs.conf_subcmd_name, self.parser
        )
        pargs.conf_subcmd(pargs)
        self._current_parser = self.parser
        return False

    def conf_reset_cmd(self, pargs):
        nodes = app_db.btmesh_db.get_node_list(order_property="name")
        nodes = self.parse_nodespecs(pargs.nodespec, nodes)
        # The retry_cmd_max and retry_cmd_interval are used only because the
        # other parameters are overwritten by the arguments of conf reset command
        retry_params_default = app_cfg.common.btmesh_retry_params_default
        retry_params = self.process_btmesh_retry_params(pargs, retry_params_default)
        remove_node_on_retry_limit = app_cfg.conf.reset_node_local_remove_on_retry_limit
        for node in nodes:
            try:
                app_btmesh.conf.reset_node(
                    node=node,
                    local=pargs.local,
                    remove_node_on_retry_limit=remove_node_on_retry_limit,
                    retry_params=retry_params,
                )
                if pargs.local:
                    app_ui.info(
                        f"Node 0x{node.prim_addr:04X} is removed from NCP node "
                        f"device database and from application database."
                    )
                else:
                    app_ui.info(
                        f"Node 0x{node.prim_addr:04X} is reset and removed "
                        f"from network."
                    )
            except CommandFailedError as e:
                status_name = SlStatus.get_name(e.errorcode)
                app_ui.error(str(e) + f" ({status_name})")
            except BtmeshError as e:
                app_ui.error(str(e))

    def conf_ae_cmd(self, pargs):
        appkey_idx = pargs.appkey_idx
        mdls: set[ModelID] = set()
        group_addr, nodes, _ = self.process_group_nodes_args(
            pargs,
            nodes_order_property="name",
            group_order_property="name",
        )
        # The retry_cmd_max and retry_cmd_interval are used only because the
        # other parameters are overwritten by the arguments of conf ae command
        retry_params_default = app_cfg.common.btmesh_retry_params_default
        retry_params = self.process_btmesh_retry_params(pargs, retry_params_default)
        if (pargs.mdls or pargs.elems or pargs.en or pargs.dis) and not (
            (pargs.mdls and pargs.elems) and (pargs.en or pargs.dis)
        ):
            if pargs.en or pargs.dis:
                # Parser error raises an exception
                self.current_parser.error(
                    "argument --mdls/-M and --elems/-e: mandatory when --en or "
                    "--dis is present."
                )
            else:
                # Parser error raises an exception
                self.current_parser.error(
                    "argument --en or --dis: mandatory when --mdls/-M and "
                    "--elems/-e are present."
                )
        mdls.update(self.parse_mdlspecs(pargs.mdls))
        # Model profile query should not fail because argparse makes sure that
        # a value from choices is selected and the choices are constructed
        # from configuration.
        for mp in app_cfg.appgroup.mdl_profiles:
            if mp.name in pargs.profile:
                mdls.update(mp.mdls)
        enable = pargs.en
        if pargs.tx_phy:
            tx_phy = self.tx_phy_choice_to_enum(pargs.tx_phy)
        else:
            tx_phy = None
        if pargs.nw_pdu:
            nw_pdu_size = pargs.nw_pdu
            btmesh.util.validate_nw_pdu_size(nw_pdu_size)
        else:
            nw_pdu_size = None
        if tx_phy is not None:
            status_list = app_btmesh.conf.silabs_set_tx(
                nodes=nodes,
                tx_phy=tx_phy,
                tx_opt=SilabsConfTxOpt.DEFAULT,
                group_addr=group_addr,
                appkey_index=appkey_idx,
                retry_params=retry_params,
            )
            for status in status_list:
                # The tx_options is not implemented in BT Mesh stack so
                # it is not shown on the UI
                if status.status == SilabsConfStatus.SUCCESS:
                    app_ui.info(
                        f"Node 0x{status.node.prim_addr:04X} TX PHY is set to "
                        f"{status.tx_phy.pretty_name}."
                    )
                else:
                    app_ui.error(
                        f"Node 0x{status.node.prim_addr:04X} TX PHY set "
                        f"({tx_phy.pretty_name}) procedure failed due to "
                        f'"{status.status.pretty_name}" error.'
                    )

        if pargs.en or pargs.dis:
            for elem_idx in pargs.elems:
                for mdl in mdls:
                    status_list = app_btmesh.conf.silabs_set_model_enable(
                        nodes=nodes,
                        elem_index=elem_idx,
                        model=mdl,
                        enable=enable,
                        group_addr=group_addr,
                        appkey_index=appkey_idx,
                        retry_params=retry_params,
                    )
                    for status in status_list:
                        if status.status == SilabsConfStatus.SUCCESS:
                            if status.enabled:
                                en_str = "enabled"
                            else:
                                en_str = "disabled"
                            app_ui.info(
                                f"Node 0x{status.node.prim_addr:04X} TX over AE "
                                f"is {en_str} for {status.model.pretty_name()} "
                                f"model on {status.elem_index} element."
                            )
                        else:
                            if enable:
                                en_str = "enable"
                            else:
                                en_str = "disable"
                            app_ui.error(
                                f"Node 0x{status.node.prim_addr:04X} TX over AE "
                                f"{en_str} for {mdl.pretty_name()} model "
                                f"on {elem_idx} element procedure failed due to "
                                f'"{status.status.pretty_name}" error.'
                            )
        if nw_pdu_size:
            status_list = app_btmesh.conf.silabs_set_network_pdu(
                nodes=nodes,
                pdu_max_size=nw_pdu_size,
                group_addr=group_addr,
                appkey_index=appkey_idx,
                retry_params=retry_params,
            )
            for status in status_list:
                if status.status == SilabsConfStatus.SUCCESS:
                    app_ui.info(
                        f"Node 0x{status.node.prim_addr:04X} network PDU max "
                        f"size is set to {status.pdu_max_size}."
                    )
                else:
                    app_ui.error(
                        f"Node 0x{status.node.prim_addr:04X} network PDU max "
                        f"size ({nw_pdu_size}) procedure failed due to "
                        f'"{status.status.pretty_name}" error.'
                    )


conf_cmd = BtmeshConfCmd()
