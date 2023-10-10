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

import functools
from typing import Optional, Tuple

import btmesh.util
from bgapix.bglibx import CommandFailedError
from bgapix.slstatus import SlStatus
from btmesh.conf import (BtmeshConfigError, FriendState, GattProxyState,
                         NodeIdentityState, RelayState, SilabsConfStatus,
                         SilabsConfTxOpt, SilabsConfTxPhy)
from btmesh.db import ModelID, Node
from btmesh.errors import BtmeshError
from btmesh.util import BtmeshRetryParams

from ..btmesh import app_btmesh
from ..cfg import app_cfg
from ..db import app_db
from ..ui import app_ui
from ..util.argparsex import ArgumentParserExt
from .cmd import BtmeshCmd


def conf_set_node_failed_handler(f):
    @functools.wraps(f)
    def conf_set_node_wrapper(*args, **kwargs):
        try:
            return f(*args, **kwargs)
        except BtmeshConfigError as e:
            app_ui.error(str(e))
            if e.result == SlStatus.TIMEOUT:
                # If there is a timeout error then all remaining configuration
                # operations targeting the same node shall be stopped because
                # it seems the node is not active or unreachable.
                # Same error is raised so the caller can continue with other nodes.
                raise
        except BtmeshError as e:
            app_ui.error(str(e))

    return conf_set_node_wrapper


class BtmeshConfCmd(BtmeshCmd):
    NETKEY_IDX = 0

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
                self.create_conf_set_parser(self.conf_subparser),
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
        self.add_nodes_pos_arg(
            self.conf_reset_parser,
            help=(
                "Target nodes of node reset procedure. The provisioner (NCP) "
                "shall be reset by factory reset explicitly so it can't be the "
                "target of this command."
            ),
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
        self.add_btmesh_basic_retry_args(
            self.conf_reset_parser,
            retry_max_default=app_cfg.conf.reset_node_retry_max_default,
            retry_interval_default=app_cfg.conf.reset_node_retry_interval_default,
            retry_interval_lpn_default=app_cfg.conf.reset_node_retry_interval_lpn_default,
            retry_max_help=(
                "Maximum number of additional Config Node Reset messages are "
                "sent until the Config Node Reset Status message is received "
                "from the remote node. "
                "(default: %(default)s)"
            ),
            retry_interval_help=(
                "Interval in seconds between Config Node Reset messages when "
                "the Config Node Reset Status message is not received from the "
                "remote node. "
                "(default: %(default)s)"
            ),
            retry_interval_lpn_help=(
                "Interval in seconds between Config Node Reset messages when "
                "the Config Node Reset Status message is not received from the "
                "remote Low Power Node. "
                "(default: %(default)s)"
            ),
        )
        return SUBPARSER_NAME, self.conf_reset_parser

    def create_conf_set_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "set"
        self.conf_set_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Set configuration states on specified nodes.",
            description=(
                "Set configuration states on specified nodes. "
                "The set subcommand enables the configuration of Configuration "
                "Server and SAR Configuration Server states on multiple nodes. "
                "Some configuration messages set multiple configuration states "
                "(e.g. composite state) so these states can be set in groups only. "
                "The set command provides two methods to update these related "
                "configuration states. "
                "Each command option has default value which refers to a "
                "configuration state that is updated atomically with others "
                "in the same configuration message. "
                "If some of these states aren't specified then the default "
                "value is used which can be set in the ini configuration file "
                "(default behavior). "
                "If --update option is specified then the set command reads the "
                "configuration states by the corresponding get messages and "
                "modifies the specified configuration states only. "
                "The configuration get operations leads to higher execution time. "
                "Those subcommand options which refers to configuration states "
                "that can be updated atomically with other configuration options "
                'are marked with "Config group: <group_name>" in help text.'
            ),
            exit_on_error_ext=False,
        )
        self.conf_set_parser.set_defaults(conf_subcmd=self.conf_set_cmd)
        self.conf_set_parser.add_argument(
            "--update",
            "-u",
            action="store_true",
            help=(
                "Some configuration messages set multiple related configuration "
                "states so these states can be set in groups only. "
                "The --update option affects configuration states which can be "
                "set atomically in the same configuration message. "
                "If --update option is used then the set command reads the "
                "related configuration states by the corresponding get message "
                "and it modifies the specified configuration states only."
            ),
        )
        self.conf_set_parser.add_argument(
            "--ttl",
            type=int,
            help=(
                "Default TTL determines TTL value used when sending messages. "
                "The Default TTL is applied by the access layer or by the "
                "upper transport layer unless the application or functionality "
                "specifies a TTL. "
                "Valid value range is from 2 to 127 for relayed PDUs, "
                "and 0 for non-relayed PDUs."
            ),
        )
        self.conf_set_parser.add_argument(
            "--relay",
            choices=["on", "off"],
            help=(
                "Set relay feature. Config group: RELAY. Other relay group "
                "options have effect only when the relay feature is turned on."
            ),
        )
        self.conf_set_parser.add_argument(
            "--relay-retx-cnt",
            type=int,
            help=(
                f"Default relay retransmit count controls the number of "
                f"retransmissions of Network PDUs relayed by the node. "
                f"Valid values range from 0 to 7. "
                f"Config group: RELAY. This option has an effect when relay "
                f"feature is turned on by --relay option. "
                f"(default: {app_cfg.conf.relay_retx_count_default})"
            ),
        )
        self.conf_set_parser.add_argument(
            "--relay-retx-int",
            type=int,
            help=(
                f"Default relay retransmit interval in milliseconds controls "
                f"the interval between retransmissions of Network PDUs relayed "
                f"by the node. "
                f"Valid values range from 10 ms to 320 ms, with a resolution of 10 ms. "
                f"Config group: RELAY. This option has an effect when relay "
                f"feature is turned on by --relay option. "
                f"(default: {app_cfg.conf.relay_retx_interval_ms_default})"
            ),
        )
        self.conf_set_parser.add_argument(
            "--proxy",
            choices=["on", "off"],
            help="Set proxy feature.",
        )
        self.conf_set_parser.add_argument(
            "--friend",
            choices=["on", "off"],
            help="Set friend feature.",
        )
        self.conf_set_parser.add_argument(
            "--identity",
            choices=["on", "off"],
            help="Set node identity advertising.",
        )
        self.conf_set_parser.add_argument(
            "--nw-tx-cnt",
            type=int,
            help=(
                f"Network Transmit Count controls the number of transmissions of "
                f"Network PDUs that originate from the node. "
                f"Valid values range from 1 to 8. "
                f"Config group: NWTX. "
                f"(default: {app_cfg.conf.network_tx_count_default})"
            ),
        )
        self.conf_set_parser.add_argument(
            "--nw-tx-int",
            type=int,
            help=(
                f"Network Transmit Interval Step in milliseconds between network "
                f"PDU transmissions which originates from the same nodes. "
                f"Valid values range from 10 ms to 320 ms, with a resolution of 10 ms. "
                f"Config group: NWTX. "
                f"(default: {app_cfg.conf.network_tx_interval_ms_default})"
            ),
        )
        self.conf_set_parser.add_argument(
            "--sar-tx-seg-int",
            type=int,
            help=(
                f"SAR Transmitter Segment Interval Step controls the interval "
                f"between transmissions of segments of a segmented message in "
                f"milliseconds. "
                f"The value is the range of 10ms to 160ms in 10ms steps, "
                f"intermediate values are rounded down to the nearest "
                f"multiple of 10. "
                f"Default value is 20ms in specification. "
                f"Config group: SAR_TX. "
                f"(default: {app_cfg.conf.sar_tx_segment_interval_step_default})"
            ),
        )
        self.conf_set_parser.add_argument(
            "--sar-tx-uc-retx-cnt",
            type=int,
            help=(
                f"SAR Transmitter Unicast Retransmission Count controls the "
                f"maximum number of transmissions of segments of segmented "
                f"messages to a unicast destination. "
                f"Valid range is 0 - 15, where 0 represents a single transmission. "
                f"The default value is 2 in specification, resulting in "
                f"3 transmissions total. "
                f"Config group: SAR_TX. "
                f"(default: {app_cfg.conf.sar_tx_unicast_retrans_count_default})"
            ),
        )
        self.conf_set_parser.add_argument(
            "--sar-tx-uc-retx-wo-prog-cnt",
            type=int,
            help=(
                f"SAR Transmitter Unicast Retransmissions Without Progress Count "
                f"controls the maximum number of retransmissions of segments of "
                f"segmented messages to a unicast destination without progress "
                f"(without marking newly marking any segments acknowledged). "
                f"Valid range is 0 - 15, where 0 represents a single transmission. "
                f"The default value is 2 in specification, resulting in "
                f"3 transmissions. "
                f"Value of this state should be set to a value greater by two or "
                f"more than the value of the SAR Receiver Acknowledgement "
                f"Retransmissions Count on a peer node. "
                f"This helps prevent the SAR Transmitter from abandoning the "
                f"SAR prematurely. "
                f"Config group: SAR_TX. "
                f"(default: {app_cfg.conf.sar_tx_unicast_retrans_wo_progress_count_default})"
            ),
        )
        self.conf_set_parser.add_argument(
            "--sar-tx-uc-retx-int-step",
            type=int,
            help=(
                f"SAR Transmitter Unicast Retransmissions Interval Step state "
                f"controls the minimum interval between retransmissions of "
                f"segments of a segmented message for a destination that is a "
                f"unicast address in 25ms steps. "
                f"Valid range is 25 - 400ms, intermediate values are rounded "
                f"down to the nearest multiple of 25. "
                f"Default value is 200ms in specification. "
                f"Config group: SAR_TX. "
                f"(default: {app_cfg.conf.sar_tx_unicast_retrans_interval_step_default})"
            ),
        )
        self.conf_set_parser.add_argument(
            "--sar-tx-uc-retx-int-inc",
            type=int,
            help=(
                f"SAR Transmitter Unicast Retransmissions Interval Increment "
                f"state controls the incremental component (TTL) of the interval "
                f"between retransmissions of segments of a segmented message "
                f"for a destination that is a unicast address in 25ms steps. "
                f"Valid range is 25 - 400ms, intermediate values are rounded "
                f"down to the nearest multiple of 25. "
                f"Default value is 50ms in specification. "
                f"Config group: SAR_TX. "
                f"(default: {app_cfg.conf.sar_tx_unicast_retrans_interval_increment_default})"
            ),
        )
        self.conf_set_parser.add_argument(
            "--sar-tx-mc-retx-cnt",
            type=int,
            help=(
                f"SAR Transmitter Multicast Retransmissions Count state controls "
                f"the maximum number of transmissions of segments of segmented "
                f"messages to a group address or a virtual address. "
                f"Valid range is 0 - 15, where 0 represents a single transmission. "
                f"The default value is 1 in specification, resulting in "
                f"2 transmissions. "
                f"WARNING! The BLOB Transfer procedure has a high-level "
                f"retransmission logic which detects missing chunks and "
                f"retransmits the missing ones. "
                f"It is recommended to disable multicast retransmissions in Lower "
                f"Transport layer in low noise environment because it slows down "
                f"the multicast BLOB Transfer significantly. "
                f"More multicast retransmissions can be beneficial during BLOB "
                f"Transfer for chunks with many segments in noisy environment "
                f"because one missing chunk segment leads to the loss of "
                f"whole BLOB Chunk Transfer access message. "
                f"Config group: SAR_TX. "
                f"(default: {app_cfg.conf.sar_tx_multicast_retrans_count_default})"
            ),
        )
        self.conf_set_parser.add_argument(
            "--sar-tx-mc-retx-int",
            type=int,
            help=(
                f"SAR Transmitter Multicast Retransmissions Interval Step state "
                f"controls the interval between retransmissions of segments of a "
                f"segmented message for a destination that is a group address or "
                f"a virtual address in 25ms steps. "
                f"Valid range is 25-400ms, intermediate values are rounded down "
                f"to the nearest multiple of 25. "
                f"Default values is 100ms in specification. "
                f"Config group: SAR_TX. "
                f"(default: {app_cfg.conf.sar_tx_multicast_retrans_interval_step_default})"
            ),
        )
        self.conf_set_parser.add_argument(
            "--sar-rx-seg-thr",
            type=int,
            help=(
                f"SAR Receiver Segments Threshold state represents the size of a "
                f"segmented message in number of segments above which the Segment "
                f"Acknowledgment messages are enabled. "
                f"Valid range is 0 - 31, the default value is 3 (segments) "
                f"in specification. "
                f"Config group: SAR_RX. "
                f"(default: {app_cfg.conf.sar_rx_segments_threshold_default})"
            ),
        )
        self.conf_set_parser.add_argument(
            "--sar-rx-ack-delay-inc",
            type=int,
            help=(
                f"Default SAR Receiver Acknowledgment Delay Increment state "
                f"control the interval between the reception of a new segment "
                f"of a segmented message for a destination that is a unicast "
                f"address and the transmission of the Segment Acknowledgment "
                f"for that message. "
                f"Formula: acknowledgment delay increment = "
                f"(SAR Acknowledgment Delay Increment + 1.5) "
                f"Valid range is 0 - 7, default is 2 in specification resulting "
                f"in 3.5 segment transmission interval steps. "
                f"Config group: SAR_RX. "
                f"(default: {app_cfg.conf.sar_rx_ack_delay_increment_default})"
            ),
        )
        self.conf_set_parser.add_argument(
            "--sar-rx-discard-timeout",
            type=int,
            help=(
                f"SAR Receiver Discard Timeout state controls the time that the "
                f"lower transport layer waits after receiving unique segments of "
                f"a segmented message before discarding that segmented message "
                f"in 5s steps. "
                f"Valid range is 5000 - 80000ms, intermediate values are rounded "
                f"down to the nearest multiple of 5s. "
                f"The default value is 10000ms in specification. "
                f"Config group: SAR_RX. "
                f"(default: {app_cfg.conf.sar_rx_discard_timeout_default})"
            ),
        )
        self.conf_set_parser.add_argument(
            "--sar-rx-seg-int",
            type=int,
            help=(
                f"SAR Receiver Segment Interval Step state indicates the interval "
                f"between received segments of a segmented message in milliseconds. "
                f"This is used to control rate of transmission of Segment "
                f"Acknowledgment messages. "
                f"Valid range is 10 - 160ms, intermediate values are rounded "
                f"down to the nearest multiple of 10. "
                f"The default value is 20ms in specification. "
                f"Config group: SAR_RX. "
                f"(default: {app_cfg.conf.sar_rx_segment_interval_step_default})"
            ),
        )
        self.conf_set_parser.add_argument(
            "--sar-rx-ack-retx-cnt",
            type=int,
            help=(
                f"SAR Receiver Acknowledgment Retransmissions Count state controls "
                f"the maximum number of retransmissions of Segment Acknowledgment "
                f"messages sent by the lower transport layer. "
                f"Valid range is 0 - 3. The default value is 1 in specification, "
                f"representing 1 retransmissions or 2 in total. "
                f"Config group: SAR_RX. "
                f"(default: {app_cfg.conf.sar_rx_ack_retrans_count_default})"
            ),
        )
        self.add_btmesh_basic_retry_args(
            self.conf_set_parser,
            retry_max_default=app_cfg.conf.conf_retry_max_default,
            retry_interval_default=app_cfg.conf.conf_retry_interval_default,
            retry_interval_lpn_default=app_cfg.conf.conf_retry_interval_lpn_default,
            retry_max_help=(
                "Maximum number of additional Config messages are sent until "
                "the corresponding Config Status message is received from the "
                "remote node. "
                "(default: %(default)s)"
            ),
            retry_interval_help=(
                "Interval in seconds between Config messages when the "
                "corresponding Config Status message is not received "
                "from the remote node. "
                "(default: %(default)s)"
            ),
            retry_interval_lpn_help=(
                "Interval in seconds between Config messages when the "
                "corresponding Config Status message is not received "
                "from the remote Low Power Node. "
                "(default: %(default)s)"
            ),
        )
        self.add_nodes_pos_arg(
            self.conf_set_parser,
            help=("Target nodes of configuration."),
        )
        return SUBPARSER_NAME, self.conf_set_parser

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
        self.add_btmesh_multicast_basic_retry_args(
            self.conf_ae_parser,
            retry_max_default=app_cfg.conf.silabs_retry_max_default,
            retry_interval_default=app_cfg.conf.silabs_retry_interval_default,
            retry_interval_lpn_default=app_cfg.conf.silabs_retry_interval_lpn_default,
            retry_multicast_threshold_default=(
                app_cfg.conf.silabs_retry_multicast_threshold_default
            ),
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
            retry_multicast_threshold_help=(
                "Multicast threshold used during Silabs Configuration procedures. "
                "If the number of uncompleted Silabs Config Servers with missing "
                "Silabs Config Status messages during the aforementioned Silabs "
                "Configuration procedures exceeds or is equal to this number "
                "then the group address is used. "
                "Otherwise, servers are looped through one by one. "
                "Zero value means unicast addressing. "
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

    def conf_set_cmd(self, pargs):
        nodes = app_db.btmesh_db.get_node_list(order_property="name")
        nodes = self.parse_nodespecs(pargs.nodespec, nodes)
        # The retry_cmd_max and retry_cmd_interval are used only because the
        # other parameters are overwritten by the arguments of conf set command
        retry_params_default = app_cfg.common.btmesh_retry_params_default
        retry_params = self.process_btmesh_retry_params(pargs, retry_params_default)
        update = pargs.update
        for node in nodes:
            try:
                self.conf_set_node_default_ttl(node, retry_params, pargs)
                self.conf_set_node_network_transmit(node, retry_params, update, pargs)
                self.conf_set_node_sar_transmitter(node, retry_params, update, pargs)
                self.conf_set_node_sar_receiver(node, retry_params, update, pargs)
                self.conf_set_node_relay(node, retry_params, update, pargs)
                self.conf_set_node_proxy(node, retry_params, pargs)
                self.conf_set_node_friend(node, retry_params, pargs)
                self.conf_set_node_identity(node, retry_params, pargs)
            except BtmeshConfigError as e:
                # The exception is raised when timeout error occurs in order to
                # skip further configuration operations targeting the same node.
                # The underlying assumption is that the node is powered down or
                # unreachable or removed from the network without the knowledge
                # of the provisioner etc.
                # Other non-timeout errors are not raised so those should not
                # reach this point, and therefore they shall be raised again.
                if e.result != SlStatus.TIMEOUT:
                    raise

    @conf_set_node_failed_handler
    def conf_set_node_default_ttl(
        self, node: Node, retry_params: BtmeshRetryParams, pargs
    ):
        ttl = pargs.ttl
        if ttl is None:
            return
        node_str = app_ui.node_str(node)
        default_ttl_status = app_btmesh.conf.set_default_ttl(
            node, ttl=ttl, retry_params=retry_params
        )
        app_ui.info(f"{node_str} node: Default TTL is set to {default_ttl_status.ttl}.")

    @conf_set_node_failed_handler
    def conf_set_node_relay(
        self, node: Node, retry_params: BtmeshRetryParams, update: bool, pargs
    ):
        relay_raw_state = pargs.relay
        if relay_raw_state is None:
            return
        if relay_raw_state == "on":
            relay_state = RelayState.ENABLED
        else:
            relay_state = RelayState.DISABLED
        retransmit_count = pargs.relay_retx_cnt
        retransmit_interval_ms = pargs.relay_retx_int
        if update and (retransmit_count is None or retransmit_interval_ms is None):
            relay_status = app_btmesh.conf.get_relay(node, retry_params=retry_params)
        if retransmit_count is None:
            if update:
                retransmit_count = relay_status.retransmit_count
            else:
                retransmit_count = app_cfg.conf.relay_retx_count_default
        if retransmit_interval_ms is None:
            if update:
                retransmit_interval_ms = relay_status.retransmit_interval_ms
            else:
                retransmit_interval_ms = app_cfg.conf.relay_retx_interval_ms_default
        relay_status = app_btmesh.conf.set_relay(
            node,
            state=relay_state,
            retransmit_count=retransmit_count,
            retransmit_interval_ms=retransmit_interval_ms,
        )
        node_str = app_ui.node_str(node)
        relay_state_str = relay_status.state.pretty_name
        if relay_state == RelayState.ENABLED:
            app_ui.info(f"{node_str} node: Relay feature is {relay_state_str}.")
            app_ui.info(
                f"{node_str} node: Relay Retransmit Count is set to "
                f"{relay_status.retransmit_count}."
            )
            app_ui.info(
                f"{node_str} node: Relay Retransmit Interval Steps is set to "
                f"{relay_status.retransmit_interval_ms}."
            )
        else:
            app_ui.info(f"{node_str} node: Relay feature is {relay_state_str}.")

    @conf_set_node_failed_handler
    def conf_set_node_proxy(self, node: Node, retry_params: BtmeshRetryParams, pargs):
        proxy_raw_state = pargs.proxy
        if proxy_raw_state is None:
            return
        if proxy_raw_state == "on":
            proxy_state = GattProxyState.ENABLED
        else:
            proxy_state = GattProxyState.DISABLED
        proxy_status = app_btmesh.conf.set_gatt_proxy(
            node,
            state=proxy_state,
            retry_params=retry_params,
        )
        node_str = app_ui.node_str(node)
        proxy_state_str = proxy_status.state.pretty_name
        app_ui.info(f"{node_str} node: Proxy feature is {proxy_state_str}.")

    @conf_set_node_failed_handler
    def conf_set_node_friend(self, node: Node, retry_params: BtmeshRetryParams, pargs):
        friend_raw_state = pargs.friend
        if friend_raw_state is None:
            return
        if friend_raw_state == "on":
            friend_state = FriendState.ENABLED
        else:
            friend_state = FriendState.DISABLED
        friend_status = app_btmesh.conf.set_friend(
            node,
            state=friend_state,
            retry_params=retry_params,
        )
        node_str = app_ui.node_str(node)
        friend_state_str = friend_status.state.pretty_name
        app_ui.info(f"{node_str} node: Friend feature is {friend_state_str}.")

    @conf_set_node_failed_handler
    def conf_set_node_identity(
        self, node: Node, retry_params: BtmeshRetryParams, pargs
    ):
        node_identity_raw_state = pargs.identity
        if node_identity_raw_state is None:
            return
        if node_identity_raw_state == "on":
            node_identity_state = NodeIdentityState.ENABLED
        else:
            node_identity_state = NodeIdentityState.DISABLED
        identity_status = app_btmesh.conf.set_node_identity(
            node,
            netkey_index=self.NETKEY_IDX,
            state=node_identity_state,
            retry_params=retry_params,
        )
        node_str = app_ui.node_str(node)
        identity_state_str = identity_status.state.pretty_name
        app_ui.info(
            f"{node_str} node: Node Identity Advertising is {identity_state_str}."
        )

    @conf_set_node_failed_handler
    def conf_set_node_network_transmit(
        self, node: Node, retry_params: BtmeshRetryParams, update: bool, pargs
    ):
        nettx_cnt = pargs.nw_tx_cnt
        nettx_int = pargs.nw_tx_int
        if nettx_cnt is None and nettx_int is None:
            # Command is called without any Network Transmit options so
            # it shall not be configured at all.
            return
        if update and (nettx_cnt is None or nettx_int is None):
            nettx_status = app_btmesh.conf.get_network_transmit(
                node, retry_params=retry_params
            )
        if nettx_cnt is None:
            if update:
                nettx_cnt = nettx_status.transmit_count
            else:
                nettx_cnt = app_cfg.conf.network_tx_count_default
        if nettx_int is None:
            if update:
                nettx_int = nettx_status.transmit_interval_ms
            else:
                nettx_int = app_cfg.conf.network_tx_interval_ms_default
        nettx_status = app_btmesh.conf.set_network_transmit(
            node,
            transmit_count=nettx_cnt,
            transmit_interval_ms=nettx_int,
            retry_params=retry_params,
        )
        node_str = app_ui.node_str(node)
        app_ui.info(
            f"{node_str} node: "
            f"Network Transmit Count is set to {nettx_status.transmit_count}."
        )
        app_ui.info(
            f"{node_str} node: "
            f"Network Transmit Interval Step is set to "
            f"{nettx_status.transmit_interval_ms} ms."
        )

    @conf_set_node_failed_handler
    def conf_set_node_sar_transmitter(
        self, node: Node, retry_params: BtmeshRetryParams, update: bool, pargs
    ):
        segment_interval_step = pargs.sar_tx_seg_int
        unicast_retrans_count = pargs.sar_tx_uc_retx_cnt
        unicast_retrans_wo_progress_count = pargs.sar_tx_uc_retx_wo_prog_cnt
        unicast_retrans_interval_step = pargs.sar_tx_uc_retx_int_step
        unicast_retrans_interval_increment = pargs.sar_tx_uc_retx_int_inc
        multicast_retrans_count = pargs.sar_tx_mc_retx_cnt
        multicast_retrans_interval_step = pargs.sar_tx_mc_retx_int
        sar_tx_args = (
            segment_interval_step,
            unicast_retrans_count,
            unicast_retrans_wo_progress_count,
            unicast_retrans_interval_step,
            unicast_retrans_interval_increment,
            multicast_retrans_count,
            multicast_retrans_interval_step,
        )
        if all(arg is None for arg in sar_tx_args):
            # Command is called without any SAR Transmitter options so
            # it shall not be configured at all.
            return
        if update and any(arg is None for arg in sar_tx_args):
            sar_tx_status = app_btmesh.conf.get_sar_transmitter(
                node,
                retry_params=retry_params,
            )
        if segment_interval_step is None:
            if update:
                segment_interval_step = sar_tx_status.segment_interval_step
            else:
                segment_interval_step = (
                    app_cfg.conf.sar_tx_segment_interval_step_default
                )
        if unicast_retrans_count is None:
            if update:
                unicast_retrans_count = sar_tx_status.unicast_retrans_count
            else:
                unicast_retrans_count = (
                    app_cfg.conf.sar_tx_unicast_retrans_count_default
                )
        if unicast_retrans_wo_progress_count is None:
            if update:
                unicast_retrans_wo_progress_count = (
                    sar_tx_status.unicast_retrans_wo_progress_count
                )
            else:
                unicast_retrans_wo_progress_count = (
                    app_cfg.conf.sar_tx_unicast_retrans_wo_progress_count_default
                )
        if unicast_retrans_interval_step is None:
            if update:
                unicast_retrans_interval_step = (
                    sar_tx_status.unicast_retrans_interval_step
                )
            else:
                unicast_retrans_interval_step = (
                    app_cfg.conf.sar_tx_unicast_retrans_interval_step_default
                )
        if unicast_retrans_interval_increment is None:
            if update:
                unicast_retrans_interval_increment = (
                    sar_tx_status.unicast_retrans_interval_increment
                )
            else:
                unicast_retrans_interval_increment = (
                    app_cfg.conf.sar_tx_unicast_retrans_interval_increment_default
                )
        if multicast_retrans_count is None:
            if update:
                multicast_retrans_count = sar_tx_status.multicast_retrans_count
            else:
                multicast_retrans_count = (
                    app_cfg.conf.sar_tx_multicast_retrans_count_default
                )
        if multicast_retrans_interval_step is None:
            if update:
                multicast_retrans_interval_step = (
                    sar_tx_status.multicast_retrans_interval_step
                )
            else:
                multicast_retrans_interval_step = (
                    app_cfg.conf.sar_tx_multicast_retrans_interval_step_default
                )
        sar_tx_status = app_btmesh.conf.set_sar_transmitter(
            node,
            segment_interval_step=segment_interval_step,
            unicast_retrans_count=unicast_retrans_count,
            unicast_retrans_wo_progress_count=unicast_retrans_wo_progress_count,
            unicast_retrans_interval_step=unicast_retrans_interval_step,
            unicast_retrans_interval_increment=unicast_retrans_interval_increment,
            multicast_retrans_count=multicast_retrans_count,
            multicast_retrans_interval_step=multicast_retrans_interval_step,
            retry_params=retry_params,
        )
        node_str = app_ui.node_str(node)
        app_ui.info(
            f"{node_str} node: "
            f"SAR Transmitter Segment Interval Step is set to "
            f"{sar_tx_status.segment_interval_step} ms."
        )
        app_ui.info(
            f"{node_str} node: "
            f"SAR Transmitter Unicast Retransmission Count is set to "
            f"{sar_tx_status.unicast_retrans_count}."
        )
        app_ui.info(
            f"{node_str} node: "
            f"SAR Transmitter Unicast Retransmissions Without Progress Count is set to "
            f"{sar_tx_status.unicast_retrans_wo_progress_count}."
        )
        app_ui.info(
            f"{node_str} node: "
            f"SAR Transmitter Unicast Retransmissions Interval Step is set to "
            f"{sar_tx_status.unicast_retrans_interval_step} ms."
        )
        app_ui.info(
            f"{node_str} node: "
            f"SAR Transmitter Unicast Retransmissions Interval Increment is set to "
            f"{sar_tx_status.unicast_retrans_interval_increment} ms."
        )
        app_ui.info(
            f"{node_str} node: "
            f"SAR Transmitter Multicast Retransmissions Count is set to "
            f"{sar_tx_status.multicast_retrans_count}."
        )
        app_ui.info(
            f"{node_str} node: "
            f"SAR Transmitter Multicast Retransmissions Interval Step is set to "
            f"{sar_tx_status.multicast_retrans_interval_step} ms."
        )

    @conf_set_node_failed_handler
    def conf_set_node_sar_receiver(
        self, node: Node, retry_params: BtmeshRetryParams, update: bool, pargs
    ):
        segments_threshold = pargs.sar_rx_seg_thr
        ack_delay_increment = pargs.sar_rx_ack_delay_inc
        discard_timeout = pargs.sar_rx_discard_timeout
        segment_interval_step = pargs.sar_rx_seg_int
        ack_retrans_count = pargs.sar_rx_ack_retx_cnt
        sar_rx_args = (
            segments_threshold,
            ack_delay_increment,
            discard_timeout,
            segment_interval_step,
            ack_retrans_count,
        )
        if all(arg is None for arg in sar_rx_args):
            # Command is called without any SAR Receiver options so
            # it shall not be configured at all.
            return
        if update and any(arg is None for arg in sar_rx_args):
            sar_rx_status = app_btmesh.conf.get_sar_receiver(
                node,
                retry_params=retry_params,
            )
        if segments_threshold is None:
            if update:
                segments_threshold = sar_rx_status.segments_threshold
            else:
                segments_threshold = app_cfg.conf.sar_rx_segments_threshold_default
        if ack_delay_increment is None:
            if update:
                ack_delay_increment = sar_rx_status.ack_delay_increment
            else:
                ack_delay_increment = app_cfg.conf.sar_rx_ack_delay_increment_default
        if discard_timeout is None:
            if update:
                discard_timeout = sar_rx_status.discard_timeout
            else:
                discard_timeout = app_cfg.conf.sar_rx_discard_timeout_default
        if segment_interval_step is None:
            if update:
                segment_interval_step = sar_rx_status.segment_interval_step
            else:
                segment_interval_step = (
                    app_cfg.conf.sar_rx_segment_interval_step_default
                )
        if ack_retrans_count is None:
            if update:
                ack_retrans_count = sar_rx_status.ack_retrans_count
            else:
                ack_retrans_count = app_cfg.conf.sar_rx_ack_retrans_count_default
        sar_rx_status = app_btmesh.conf.set_sar_receiver(
            node,
            segments_threshold=segments_threshold,
            ack_delay_increment=ack_delay_increment,
            discard_timeout=discard_timeout,
            segment_interval_step=segment_interval_step,
            ack_retrans_count=ack_retrans_count,
            retry_params=retry_params,
        )
        node_str = app_ui.node_str(node)
        app_ui.info(
            f"{node_str} node: "
            f"SAR Receiver Segments Threshold is set to "
            f"{sar_rx_status.segments_threshold}."
        )
        app_ui.info(
            f"{node_str} node: "
            f"SAR Receiver Acknowledgment Delay Increment is set to "
            f"{sar_rx_status.ack_delay_increment}."
        )
        app_ui.info(
            f"{node_str} node: "
            f"SAR Receiver Discard Timeout is set to "
            f"{sar_rx_status.discard_timeout} ms."
        )
        app_ui.info(
            f"{node_str} node: "
            f"SAR Receiver Segment Interval Step is set to "
            f"{sar_rx_status.segment_interval_step} ms."
        )
        app_ui.info(
            f"{node_str} node: "
            f"SAR Receiver Acknowledgment Retransmissions Count is set to "
            f"{sar_rx_status.ack_retrans_count}."
        )

    def conf_ae_cmd(self, pargs):
        appkey_idx = pargs.appkey_idx
        mdls: set[ModelID] = set()
        group_addr, nodes, _ = self.process_group_nodes_args(
            pargs,
            nodes_order_property="name",
            group_order_property="name",
        )
        # The retry_cmd_max, retry_cmd_interval and auto_unicast common retry
        # parameter configuration values are used only because the other retry
        # parameters are overwritten by the arguments of conf ae command.
        retry_params_default = app_cfg.common.btmesh_multicast_retry_params_default
        retry_params = self.process_btmesh_multicast_retry_params(
            pargs, retry_params_default
        )
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
