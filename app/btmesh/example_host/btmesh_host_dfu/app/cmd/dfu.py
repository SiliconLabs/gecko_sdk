# Copyright 2023 Silicon Laboratories Inc. www.silabs.com
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

from pathlib import Path
from typing import List, Optional, Tuple, Union

import btmesh.util
from bgapix.bglibx import BGLibExtSyncSignalException
from btmesh.dfu import (FwReceiver, FwReceiverPhase, FwUpdateProgressEvent,
                        FwUpdateStatus, FwUpdateStep)
from btmesh.mbt import BlobTransferMode

from ..btmesh import app_btmesh
from ..cfg import app_cfg
from ..ui import AppUIColumnInfo, app_ui
from ..util.argparsex import ArgumentParserExt
from .cmd import BtmeshCmd


class BtmeshDfuCmd(BtmeshCmd):
    DFU_INFO_COLUMNS = {
        "elem": AppUIColumnInfo(header="Element", default=True),
        "fw_index": AppUIColumnInfo(header="FW Index", default=False),
        "status": AppUIColumnInfo(header="Status", default=True),
        "fwid": AppUIColumnInfo(header="FWID", default=True),
        "uri": AppUIColumnInfo(header="URI", default=False),
    }

    @property
    def parser(self) -> ArgumentParserExt:
        return self.dfu_parser

    @property
    def current_parser(self) -> Optional[ArgumentParserExt]:
        return getattr(self, "_current_parser", self.parser)

    def create_parser(self, subparsers) -> ArgumentParserExt:
        self.dfu_parser = subparsers.add_parser(
            "dfu",
            prog="dfu",
            help=(
                "Start standalone firmware update procedure on updating nodes "
                "and query FW information from updating nodes as initiator."
            ),
            description=(
                "Start standalone firmware update procedure on updating nodes "
                "or query FW information from updating nodes as initiator. "
            ),
            exit_on_error_ext=False,
        )
        self.dfu_subparser = self.dfu_parser.add_subparsers(
            dest="dfu_subcmd_name",
            title="Subcommands",
            required=True,
        )
        self.subparser_dict = dict(
            (
                self.create_dfu_info_parser(self.dfu_subparser),
                self.create_dfu_start_parser(self.dfu_subparser),
            )
        )
        return self.dfu_parser

    def add_appkey_index_arg(self, parser: ArgumentParserExt) -> None:
        parser.add_argument(
            "--appkey-idx",
            "-a",
            type=int,
            default=app_cfg.dfu_clt.appkey_index_default,
            help=(
                "Appkey index used for sending FW Update and BLOB Transfer "
                "messages. (default: %(default)s)"
            ),
        )

    def add_ttl_arg(self, parser: ArgumentParserExt) -> None:
        parser.add_argument(
            "--ttl",
            "-t",
            type=int,
            default=app_cfg.dfu_clt.ttl_default,
            help=(
                "TTL used for sending FW Update and BLOB Transfer messages. "
                "(default: %(default)s)"
            ),
        )

    def add_fwid_arg(
        self,
        parser: Union[ArgumentParserExt, object],
        required=True,
        help="Firmware identifier belonging to FW image.",
    ) -> None:
        parser.add_argument(
            "--fwid",
            "-f",
            metavar="<fwidspec>",
            type=self.parse_fwidspec,
            required=required,
            help=f"{help} {app_ui.FWIDSPEC_HELP}",
        )

    def add_metadata_arg(
        self,
        parser: ArgumentParserExt,
        required=False,
        help="Metadata belonging to FW image.",
    ) -> None:
        parser.add_argument(
            "--metadata",
            "-m",
            metavar="<metaspec>",
            type=self.parse_metaspec,
            required=required,
            default=bytes(),
            help=f"{help} {app_ui.METASPEC_HELP}",
        )

    def add_fw_idx_arg(
        self,
        parser: ArgumentParserExt,
        default=0,
        help="Index of the firmware on updating nodes.",
    ) -> None:
        parser.add_argument(
            "--fw-idx",
            type=int,
            default=default,
            help=help,
        )

    def create_dfu_info_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "info"
        self.dfu_info_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Query the FW information from selected Updating Nodes.",
            description=(
                "The firmware info command queries the Current Firmware ID and "
                "Update URI from the specified index of Firmware Information List "
                "on the selected updating nodes."
            ),
            exit_on_error_ext=False,
        )
        self.dfu_info_parser.set_defaults(dfu_subcmd=self.dfu_info_cmd)
        self.add_fw_idx_arg(
            self.dfu_info_parser,
            help=(
                "Target firmware index of Firmware Information Query procedure "
                "on selected Updating Nodes. "
                "(default: %(default)s)"
            ),
        )
        self.add_column_args(
            self.dfu_info_parser,
            table_name="FW information report",
            column_info_dict=self.DFU_INFO_COLUMNS,
        )
        self.add_appkey_index_arg(self.dfu_info_parser)
        self.add_ttl_arg(self.dfu_info_parser)
        self.add_btmesh_basic_retry_args(
            self.dfu_info_parser,
            retry_max_default=app_cfg.dfu_clt.dfu_retry_max_default,
            retry_interval_default=app_cfg.dfu_clt.dfu_retry_interval_default,
            retry_interval_lpn_default=app_cfg.dfu_clt.dfu_retry_interval_lpn_default,
            retry_max_help=(
                "Maximum number of additional Firmware Update Information Get "
                "messages which are sent until the corresponding status message "
                "is not received from the Firmware Update Server. "
                "(default: %(default)s)"
            ),
            retry_interval_help=(
                "Interval in seconds between Firmware Update Information Get "
                "messages when the corresponding status message is not received "
                "from the Firmware Update Server. "
                "(default: %(default)s)"
            ),
            retry_interval_lpn_help=(
                "Interval in seconds between Firmware Update Information Get "
                "messages when the corresponding status message is not received "
                "from the Firmware Update Server model of a Low Power Node. "
                "(default: %(default)s)"
            ),
        )
        self.add_group_nodes_args(
            self.dfu_info_parser,
            add_elem_arg=True,
            add_elem_addrs_arg=True,
            elem_default=0,
            group_addr_help=(
                f"Group address used for the FW Information Query procedure. "
                f"The FW Update Server shall be subscribed to the specified group "
                f"address. If it is unassigned address (0) then the FW Information "
                f"Get message is sent to each updating node one by one to the "
                f"element address of the FW Update Server model."
            ),
            group_help=(
                f"Select the app group which contains group address and updating "
                f"nodes which shall participate in the FW Information Query "
                f"procedure. The FW Information Get message is sent to the group "
                f"address of the app group. "
                f"For further details see {self.GROUP_ADDR_OPTS} option."
            ),
            nodes_help=(
                f"Select the updating nodes which shall participate in the "
                f"FW Information Query procedure. The FW Information Query "
                f"procedure requires the element (unicast) addresses of the "
                f"updating nodes. "
                f"Those element addresses shall be selected where the FW Update "
                f"Server model is located on the updating nodes. "
                f"The {self.NODES_OPTS} options selects nodes only so in order "
                f"to specify the proper element address the {self.ELEM_OPTS} "
                f"option shall be used as well. "
                f"The element addresses can be specified directly by the "
                f"{self.ELEM_ADDRS_OPTS} option."
            ),
            elem_help=(
                f"Select element on the updating nodes where the FW Update Server "
                f"model is located by element index. "
                f"This option is mandatory when {self.NODES_OPTS} or "
                f"{self.GROUP_OPTS} is used because those selects the nodes only."
            ),
            elem_addrs_help=(
                f"Select the updating nodes which shall participate in the "
                f"FW Information Query procedure by selecting the element "
                f"addresses of updating nodes with FW Update Server model. "
                f"If {self.ELEM_ADDRS_OPTS} is used then {self.NODES_OPTS} and "
                f"{self.GROUP_OPTS} and {self.ELEM_OPTS} shall not be used."
            ),
        )
        return SUBPARSER_NAME, self.dfu_info_parser

    def create_dfu_start_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "start"
        self.dfu_start_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Start Firmware Update procedure of specified FW image to the "
            "selected updating nodes.",
            description=(
                "Start Firmware Update procedure of specified FW image "
                "to the selected updating nodes. "
                "The FW update procedure includes the following steps: "
                "FW metadata check, FW update start, BLOB transfer, "
                "FW verification, FW application (install) and FW update "
                "result check. "
                "The result of metadata check determines whether the node "
                "becomes unprovisioned after the FW update or not. "
                "If the node becomes unprovisioned after a successful FW update "
                "then it is removed from the device database and from each app "
                "group automatically. The user is responsible for the "
                "reprovisioning and reconfiguration of the device. "
                "Note: number of elements and models might have changed so only "
                "the user has information how the device shall be configured."
            ),
            exit_on_error_ext=False,
        )
        self.dfu_start_parser.set_defaults(dfu_subcmd=self.dfu_start_cmd)
        self.dfu_start_parser.add_argument(
            "fw_image_path",
            type=Path,
            help="Path of FW image file which shall be used for FW update.",
        )
        self.add_fwid_arg(self.dfu_start_parser)
        self.add_metadata_arg(self.dfu_start_parser)
        self.dfu_start_parser.add_argument(
            "--timeout-base",
            "-T",
            type=int,
            default=app_cfg.dfu_clt.timeout_base_default,
            help=f"The timeout base used for Firmware Update and BLOB Transfer "
            f"procedures. {app_ui.DFU_CALC_TIMEOUT_HELP} "
            "(default: %(default)s)",
        )
        self.dfu_start_parser.add_argument(
            "--fw-idx",
            type=int,
            default=0,
            help=(
                "Index of the firmware on updating nodes which shall be updated."
                "(default: %(default)s)"
            ),
        )
        self.dfu_start_parser.add_argument(
            "--transfer-mode",
            default="push",
            choices=["push", "pull"],
            help="Transfer mode for the BLOB transfer phase of FW update. "
            "The LPN nodes usually use pull mode.",
        )
        self.add_chunk_size_arg(
            self.dfu_start_parser, default=app_cfg.dfu_clt.dfu_chunk_size_default
        )
        self.dfu_start_parser.add_argument(
            "--multicast-threshold",
            "--mct",
            type=int,
            default=app_cfg.dfu_clt.dfu_multicast_threshold_default,
            help=(
                "If the number of uncompleted servers (missing status messages) "
                "during any BLOB transfer procedure step exceeds or is equal to "
                "this number then the group address is used. "
                "Otherwise, servers are looped through one by one. "
                "Value of 0 disables the feature. "
                "(default: %(default)s)"
            ),
        )
        self.add_appkey_index_arg(self.dfu_start_parser)
        self.add_ttl_arg(self.dfu_start_parser)
        self.add_group_nodes_args(
            self.dfu_start_parser,
            add_elem_arg=True,
            add_elem_addrs_arg=True,
            elem_default=0,
            group_addr_help=(
                f"Group address used for the Firmware Update procedure. "
                f"The FW Update Server and BLOB Transfer Server models shall be "
                f"subscribed to the specified group address. If it is unassigned "
                f"address (0) then the FW Update and BLOB transfer messages are "
                f"sent to each updating node one by one to the element address "
                f"of the FW Update Server and BLOB Transfer Server models."
            ),
            group_help=(
                f"Select the app group which contains group address and updating "
                f"nodes which shall participate in the Firmware Update procedure. "
                f"The group address of the app group is used as the destination "
                f"address of FW Update and BLOB Transfer messages. "
                f"The nodes of the app group are the receivers of the FW image "
                f"in the FW Update procedure. "
                f"For further details see {self.GROUP_ADDR_OPTS} option."
            ),
            nodes_help=(
                f"Select the updating nodes which shall participate in the "
                f"firmware update. The FW Update procedure requires the element "
                f"(unicast) addresses of the updating nodes. "
                f"Those element addresses shall be selected where the FW Update "
                f"Server and BLOB Transfer Server models are located on the "
                f"updating nodes. "
                f"The {self.NODES_OPTS} option selects nodes only so in order "
                f"to specify the proper element address the {self.ELEM_OPTS} "
                f"option shall be used as well. "
                f"The element addresses can be specified directly by the "
                f"{self.ELEM_ADDRS_OPTS} option."
            ),
            elem_help=(
                f"Select element on the updating nodes where the FW Update Server "
                f"and BLOB Transfer Server models are located by element index. "
                f"This option is mandatory when {self.NODES_OPTS} or "
                f"{self.GROUP_OPTS} is used because those selects the nodes only."
            ),
            elem_addrs_help=(
                f"Select the updating nodes which shall participate in the "
                f"FW Update procedure by selecting the element addresses of "
                f"updating nodes with FW Update Server and BLOB Transfer "
                f"Server model. "
                f"If {self.ELEM_ADDRS_OPTS} is used then {self.NODES_OPTS} and "
                f"{self.GROUP_OPTS} and {self.ELEM_OPTS} shall not be used."
            ),
        )
        return SUBPARSER_NAME, self.dfu_start_parser

    def __call__(self, arg) -> bool:
        pargs = self.parser.parse_args(arg.split())
        self._current_parser = self.subparser_dict.get(
            pargs.dfu_subcmd_name, self.parser
        )
        pargs.dfu_subcmd(pargs)
        self._current_parser = self.parser
        return False

    def dfu_info_cmd(self, pargs):
        group_addr, nodes, elem_addrs = self.process_group_nodes_args(
            pargs,
            nodes_order_property="name",
            group_order_property="name",
        )
        retry_params_default = app_cfg.common.btmesh_retry_params_default
        retry_params = self.process_btmesh_retry_params(pargs, retry_params_default)
        fw_info_list = app_btmesh.dfu_clt.get_info(
            elem_index=app_cfg.dfu_clt.elem_index,
            server_addrs=elem_addrs,
            first_index=pargs.fw_idx,
            max_entries=1,
            group_addr=group_addr,
            appkey_index=pargs.appkey_idx,
            ttl=pargs.ttl,
            retry_params=retry_params,
        )
        rows = []
        columns = self.process_column_args(pargs, self.DFU_INFO_COLUMNS)
        for fw_info in fw_info_list:
            elem_str = app_ui.elem_str(fw_info.server_addr)
            fw_idx_str = str(pargs.fw_idx)
            status_str = fw_info.status.pretty_name
            if fw_info.status == FwUpdateStatus.SUCCESS:
                fwid_str = app_ui.fwid_str(fw_info.fwid)
                uri_str = fw_info.uri
            else:
                fwid_str = None
                uri_str = None
            rows.append(
                {
                    "elem": elem_str,
                    "fw_index": fw_idx_str,
                    "status": status_str,
                    "fwid": fwid_str,
                    "uri": uri_str,
                }
            )
        app_ui.table_info(rows, columns=columns)

    def dfu_start_cmd(self, pargs):
        self.last_progress = -1
        self.last_dfu_state = FwUpdateStep.UNKNOWN_VALUE
        if not pargs.fw_image_path.exists():
            self.current_parser.error(
                f'The FW image file does not exists on "{pargs.fw_image_path}" path.'
            )
        with open(pargs.fw_image_path, "rb") as content_file:
            fw_data = content_file.read()
        app_ui.info(
            f"FW data ({len(fw_data)} bytes) is loaded from " f"{pargs.fw_image_path}."
        )
        group_addr, nodes, elem_addrs = self.process_group_nodes_args(
            pargs,
            nodes_order_property="name",
            group_order_property="name",
        )
        retry_params_default = app_cfg.common.btmesh_retry_params_default
        retry_params = self.process_btmesh_retry_params(pargs, retry_params_default)
        fw_idxs = [pargs.fw_idx] * len(elem_addrs)
        receivers = [
            FwReceiver(addr, fw_idx) for addr, fw_idx in zip(elem_addrs, fw_idxs)
        ]
        if pargs.transfer_mode == "push":
            transfer_mode = BlobTransferMode.PUSH
        else:
            transfer_mode = BlobTransferMode.PULL
        fwid = pargs.fwid
        metadata = pargs.metadata
        timeout_base = pargs.timeout_base
        multicast_threshold = pargs.multicast_threshold
        appkey_index = pargs.appkey_idx
        ttl = pargs.ttl
        chunk_size_pref = pargs.chunk_size
        app_btmesh.subscribe(
            "btmesh_levt_dfu_fw_update_progress",
            self.handle_fw_update_progress,
        )
        try:
            dfu_state, receivers_info = app_btmesh.dfu_clt.fw_update(
                elem_index=app_cfg.dfu_clt.elem_index,
                group_addr=group_addr,
                receivers=receivers,
                fwid=fwid,
                metadata=metadata,
                fw_data=fw_data,
                timeout_base=timeout_base,
                transfer_mode=transfer_mode,
                chunk_size_pref=chunk_size_pref,
                virtual_addr=bytes(),
                multicast_threshold=multicast_threshold,
                appkey_index=appkey_index,
                ttl=ttl,
                retry_params=retry_params,
            )
            fwid_str = app_ui.fwid_str(fwid)
            if dfu_state == FwUpdateStep.IDLE:
                app_ui.info(
                    f"The FW Update procedure with {fwid_str} FWID is cancelled "
                    f"on the Initiator."
                )
            elif dfu_state in (FwUpdateStep.COMPLETED, FwUpdateStep.FAILED):
                app_ui.info(
                    f"The FW Update procedure with {fwid_str} FWID is "
                    f"{dfu_state.pretty_name} on the Initiator."
                )
                rows = []
                for rec_info in receivers_info:
                    rec_info_dict = {
                        "Address": f"0x{rec_info.server_addr:04X}",
                        "FW Idx": f"{rec_info.fw_index}",
                        "Phase": rec_info.phase.pretty_name,
                        "BLOB status": rec_info.mbt_status.pretty_name,
                        "DFU status": rec_info.dfu_status.pretty_name,
                    }
                    rows.append(rec_info_dict)
                app_ui.table_info(rows)
        except BGLibExtSyncSignalException:
            # If an updating node does not respond then the cancellation might
            # be as long as the FW update client timeout.
            client_timeout = round(
                btmesh.util.dfu_calc_client_timeout(
                    timeout_base=timeout_base,
                    ttl=ttl,
                )
            )
            app_ui.info(
                f"The FW Update cancellation procedure is started on Initiator. "
                f"The cancellation procedure might last for {client_timeout} "
                f"seconds."
            )
            app_btmesh.dfu_clt.cancel_fw_update(
                elem_index=app_cfg.dfu_clt.elem_index,
                timeout_base=timeout_base,
                ttl=ttl,
                retry_params=retry_params,
            )
            fwid_str = app_ui.fwid_str(fwid)
            app_ui.info(
                f"The FW Update procedure with {fwid_str} FWID is cancelled "
                f"on the Initiator."
            )
        finally:
            app_btmesh.unsubscribe(
                "btmesh_levt_dfu_fw_update_progress",
                self.handle_fw_update_progress,
            )

    def handle_fw_update_progress(self, event: FwUpdateProgressEvent):
        if (
            event.dfu_state != self.last_dfu_state
            and event.dfu_state == FwUpdateStep.TRANSFERRING_IMAGE
        ):
            # It looks better if the transfer active phase change is shown
            # before the fw update progress.
            app_ui.info(f"FW update state is changed to {event.dfu_state.pretty_name}.")
            self.last_dfu_state = event.dfu_state
        if event.dfu_state not in (
            FwUpdateStep.IDLE,
            FwUpdateStep.FAILED,
            FwUpdateStep.UNKNOWN_VALUE,
        ):
            active_receivers_progress = [
                r.progress
                for r in event.receivers_info
                if r.phase == FwReceiverPhase.TRANSFER_IN_PROGRESS
            ]
            if active_receivers_progress:
                progress = min(active_receivers_progress)
            elif 0 < self.last_progress:
                progress = 100
            else:
                progress = self.last_progress
            if progress != self.last_progress:
                app_ui.info(f"FW update progress: {progress:3d}%")
                self.last_progress = progress
        if (
            event.dfu_state != self.last_dfu_state
            and event.dfu_state != FwUpdateStep.TRANSFERRING_IMAGE
        ):
            app_ui.info(f"FW update state is changed to {event.dfu_state.pretty_name}.")
            self.last_dfu_state = event.dfu_state


dfu_cmd = BtmeshDfuCmd()
