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

import math
from pathlib import Path
from typing import List, Optional, Tuple, Union

import btmesh.util
from bgapix.bglibx import BGLibExtSyncSignalException
from btmesh.dfu import FwReceiver
from btmesh.dist import (FwDistDistributionProgressEvent, FwDistFwStatus,
                         FwDistPhase, FwDistStatus, FwDistUploadProgressEvent,
                         FwReceiverPhase)
from btmesh.mbt import BlobTransferMode

from ..btmesh import app_btmesh
from ..cfg import app_cfg
from ..db import app_db
from ..ui import app_ui
from ..util.argparsex import ArgumentParserExt
from .cmd import BtmeshCmd


class BtmeshDistCmd(BtmeshCmd):
    @property
    def parser(self) -> ArgumentParserExt:
        return self.dist_parser

    @property
    def current_parser(self) -> Optional[ArgumentParserExt]:
        return getattr(self, "_current_parser", self.parser)

    def create_parser(self, subparsers) -> ArgumentParserExt:
        self.dist_parser = subparsers.add_parser(
            "dist",
            prog="dist",
            help="Upload, start distribution, delete FW images and query "
            "capabilities and FW list from distributor.",
            description="Upload, start distribution, delete FW images and query "
            "capabilities and FW list from distributor. "
            "The upload command transfers the FW image to the distributor node "
            "which stores it in its FW list. "
            "The delete and delete all commands remove the specified FW or all "
            "FW images from the FW list of the distributor. "
            "The start command initiates the distribution procedure on the "
            "distributor over the specified nodes to perform FW update. "
            "The info command queries and shows the capabilities and FW list "
            "of the distributor.",
            exit_on_error_ext=False,
        )
        self.dist_subparser = self.dist_parser.add_subparsers(
            dest="dist_subcmd_name",
            title="Subcommands",
            required=True,
        )
        self.subparser_dict = dict(
            (
                self.create_dist_info_parser(self.dist_subparser),
                self.create_dist_upload_parser(self.dist_subparser),
                self.create_dist_delete_parser(self.dist_subparser),
                self.create_dist_start_parser(self.dist_subparser),
            )
        )
        return self.dist_parser

    def add_appkey_index_arg(self, parser: ArgumentParserExt) -> None:
        parser.add_argument(
            "--appkey-idx",
            "-a",
            type=int,
            default=app_cfg.dist_clt.appkey_index_default,
            help="Appkey index used for sending FW Distribution messages. "
            "(default: %(default)s)",
        )

    def add_ttl_arg(self, parser: ArgumentParserExt) -> None:
        parser.add_argument(
            "--ttl",
            "-t",
            type=int,
            default=app_cfg.dist_clt.ttl_default,
            help="TTL used for sending FW Distribution messages. "
            "(default: %(default)s)",
        )

    def add_distributor_arg(self, parser: ArgumentParserExt) -> None:
        parser.add_argument(
            "--distributor",
            "-d",
            metavar="<elemspec>",
            required=True,
            help=f"Specifies the target distributor element address. "
            f"If the elemspec is resolved to multiple element addresses then "
            f"the first one is selected. "
            f"{app_ui.ELEMSPEC_HELP} {app_ui.NODESPEC_HELP}",
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

    def create_dist_info_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "info"
        self.dist_info_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Query the FW list and capabilities from the distributor.",
            description="Query the FW list and capabilities from the distributor.",
            exit_on_error_ext=False,
        )
        self.dist_info_parser.set_defaults(dist_subcmd=self.dist_info_cmd)
        self.dist_info_target_group = (
            self.dist_info_parser.add_mutually_exclusive_group(required=True)
        )
        self.dist_info_target_group.add_argument(
            "--capabilities",
            "-c",
            action="store_true",
            help="Query the FW Distribution Server capabilities.",
        )
        self.dist_info_target_group.add_argument(
            "--fw-list-idx",
            "-i",
            type=int,
            nargs="+",
            help="Distribution FW image list indexes which shall be queried.",
        )
        self.dist_info_target_group.add_argument(
            "--fw-list",
            "-l",
            action="store_true",
            help="Query the FW Distribution Server FW image list.",
        )
        self.add_distributor_arg(self.dist_info_parser)
        self.add_appkey_index_arg(self.dist_info_parser)
        self.add_ttl_arg(self.dist_info_parser)
        self.add_basic_retry_args(
            self.dist_info_parser,
            retry_max_default=app_cfg.dist_clt.dist_retry_max_default,
            retry_interval_default=app_cfg.dist_clt.dist_retry_interval_default,
            retry_max_help=(
                "Maximum number of additional Firmware Distribution Capabilities "
                "Get or Firmware Distribution Firmware Get by Index messages "
                "which are sent until the corresponding status message is not "
                "received from the Firmware Distribution Server. "
                "(default: %(default)s)"
            ),
            retry_interval_help=(
                "Interval in seconds between Firmware Distribution Capabilities "
                "Get or Firmware Distribution Firmware Get by Index messages "
                "when the corresponding status message is not received from the "
                "Firmware Distribution Server. "
                "(default: %(default)s)"
            ),
        )
        return SUBPARSER_NAME, self.dist_info_parser

    def create_dist_upload_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "upload"
        self.dist_upload_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Upload selected FW image to the Distributor.",
            description="Upload selected FW image to the Distributor. "
            "If a signal (Ctrl+C or Command+.) is raised by the user during the "
            "firmware upload then the upload is canceled.",
            exit_on_error_ext=False,
        )
        self.dist_upload_parser.set_defaults(dist_subcmd=self.dist_upload_cmd)
        self.dist_upload_parser.add_argument(
            "fw_image_path",
            type=Path,
            help="Path of FW image file which shall be uploaded.",
        )
        self.add_distributor_arg(self.dist_upload_parser)
        self.add_fwid_arg(self.dist_upload_parser)
        self.add_metadata_arg(self.dist_upload_parser)
        self.dist_upload_parser.add_argument(
            "--timeout-base",
            "-T",
            type=int,
            default=app_cfg.dist_clt.upload_timeout_base_default,
            help=f"The timeout base of FW upload including the upload start-status "
            f"timeout and BLOB Transfer timeout. {app_ui.DFU_CALC_TIMEOUT_HELP} "
            "(default: %(default)s)",
        )
        self.add_chunk_size_arg(
            self.dist_upload_parser, default=app_cfg.dist_clt.upload_chunk_size_default
        )
        self.add_appkey_index_arg(self.dist_upload_parser)
        self.add_ttl_arg(self.dist_upload_parser)
        self.add_retry_interval_arg(
            self.dist_upload_parser,
            default=app_cfg.dist_clt.dist_retry_interval_default,
            help=(
                "Interval in seconds between Firmware Distribution Upload Start "
                "or Firmware Distribution Upload Cancel messages when the "
                "corresponding status message is not received from the Firmware "
                "Distribution Server. "
                "This retry interval is used for BLOB Transfer phase of Firmware "
                "Upload procedure as the repetition rate of BLOB Transfer "
                "messages when the corresponding BLOB Transfer status message is "
                "not received from the BLOB Transfer Server on the Distributor. "
                "(default: %(default)s)"
            ),
        )
        return SUBPARSER_NAME, self.dist_upload_parser

    def create_dist_delete_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "delete"
        self.dist_delete_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Delete one or more FW image on a Distributor.",
            description="Delete one or more FW image on a Distributor. "
            "If no FWID is specified with --fwid option then all firmware "
            "images are deleted from the FW image list.",
            exit_on_error_ext=False,
        )
        self.dist_delete_parser.set_defaults(dist_subcmd=self.dist_delete_cmd)
        self.add_distributor_arg(self.dist_delete_parser)
        self.add_fwid_arg(
            self.dist_delete_parser,
            required=False,
            help="Firmware identifier of FW image which shall be deleted.",
        )
        self.add_appkey_index_arg(self.dist_delete_parser)
        self.add_ttl_arg(self.dist_delete_parser)
        self.add_basic_retry_args(
            self.dist_delete_parser,
            retry_max_default=app_cfg.dist_clt.delete_retry_max_default,
            retry_interval_default=app_cfg.dist_clt.delete_retry_interval_default,
            retry_max_help=(
                "Maximum number of additional Firmware Distribution Firmware "
                "Delete or Firmware Distribution Firmware Delete All messages "
                "which are sent until the corresponding status message is not "
                "received from the Firmware Distribution Server. "
                "(default: %(default)s)"
            ),
            retry_interval_help=(
                "Interval in seconds between Firmware Distribution Firmware "
                "Delete or Firmware Distribution Firmware Delete All messages "
                "when the corresponding status message is not received from the "
                "Firmware Distribution Server. "
                "(default: %(default)s)"
            ),
        )
        return SUBPARSER_NAME, self.dist_delete_parser

    def create_dist_start_parser(self, subparsers) -> Tuple[str, ArgumentParserExt]:
        SUBPARSER_NAME = "start"
        self.dist_start_parser: ArgumentParserExt = subparsers.add_parser(
            SUBPARSER_NAME,
            help="Start distribution of specified FW image to the selected nodes.",
            description="Start distribution of specified FW image to the selected nodes.",
            exit_on_error_ext=False,
        )
        self.dist_start_parser.set_defaults(dist_subcmd=self.dist_start_cmd)
        self.add_distributor_arg(self.dist_start_parser)
        self.dist_start_fw_group = self.dist_start_parser.add_mutually_exclusive_group(
            required=True
        )
        self.add_fwid_arg(
            self.dist_start_fw_group,
            required=False,
            help=(
                "Firmware identifier of the FW image in the firmware image list "
                "of the distributor which shall be used for FW update."
            ),
        )
        self.dist_start_fw_group.add_argument(
            "--fw-list-idx",
            "-i",
            type=int,
            help=(
                "Index of the FW image in the firmware image list of the "
                "distributor which shall be used for FW update."
            ),
        )
        self.dist_start_parser.add_argument(
            "--transfer-mode",
            "-m",
            default="push",
            choices=["push", "pull"],
            help="Transfer mode for the BLOB transfer phase of distribution. "
            "The LPN nodes usually use pull mode. "
            "(default: %(default)s)",
        )
        self.dist_start_parser.add_argument(
            "--timeout-base",
            "-T",
            type=int,
            default=app_cfg.dist_clt.dist_timeout_base_default,
            help=f"The timeout base used for FW distribution including FW update "
            f"message procedures and BLOB transfer. {app_ui.DFU_CALC_TIMEOUT_HELP} "
            "(default: %(default)s)",
        )
        self.dist_start_parser.add_argument(
            "--dist-appkey-idx",
            "-A",
            type=int,
            default=app_cfg.dist_clt.dist_appkey_index_default,
            help="Appkey index used for the communication between the "
            "Distributor and Updating Nodes. (default: %(default)s)",
        )
        self.dist_start_parser.add_argument(
            "--dist-ttl",
            type=int,
            default=app_cfg.dist_clt.dist_ttl_default,
            help="The TTL for the Distributor to use when communicating with "
            "the Updating Nodes. (default: %(default)s)",
        )
        self.add_appkey_index_arg(self.dist_start_parser)
        self.add_ttl_arg(self.dist_start_parser)
        self.dist_start_parser.add_argument(
            "--fw-idx",
            type=int,
            default=0,
            help=(
                "Index of the firmware on updating nodes which shall be updated."
                "(default: %(default)s)"
            ),
        )
        self.dist_start_parser.add_argument(
            "--poll-int",
            type=float,
            default=app_cfg.dist_clt.dist_poll_int_default,
            help=(
                "Poll interval for distribution progress reporting in seconds."
                "(default: %(default)s)"
            ),
        )
        self.add_btmesh_basic_retry_args(
            self.dist_start_parser,
            retry_max_default=app_cfg.dist_clt.dist_retry_max_default,
            retry_interval_default=app_cfg.dist_clt.dist_retry_interval_default,
            retry_interval_lpn_default=app_cfg.dist_clt.dist_retry_interval_lpn_default,
            retry_max_help=(
                "Maximum number of additional Firmware Distribution messages "
                "which are sent until the corresponding status message is not "
                "received from the Firmware Distribution Server. "
                "For example: FW Distribution Receivers Add/Delete All/Get or "
                "FW Distribution Start/Get/Cancel messages. "
                "This argument is used during Firmware Metadata Check procedure "
                "as well at the beginning of the Distribution and it determines "
                "the default maximum number of additional Firmware Update "
                "Firmware Metadata Check messages which are sent until the "
                "corresponding status messages are not received from each "
                "updating node. "
                "(default: %(default)s)"
            ),
            retry_interval_help=(
                "Interval in seconds between Firmware Distribution messages when "
                "the corresponding status message is not received from the "
                "Firmware Distribution Server. "
                "For example: FW Distribution Receivers Add/Delete All/Get or "
                "FW Distribution Start/Get/Cancel messages. "
                "This argument is used during Firmware Metadata Check procedure "
                "as well at the beginning of the Distribution. It determines "
                "the default interval in seconds between Firmware Update "
                "Firmware Metadata Check messages when the corresponding "
                "status messages are not received from each updating node. "
                "(default: %(default)s)"
            ),
            retry_interval_lpn_help=(
                "Interval in seconds between Firmware Update Firmware Metadata "
                "Check messages at the beginning of the Distribution when the "
                "corresponding status messages are not received from each "
                "updating node. "
                "Note: Distributor should not be Low Power Node so this argument "
                "doesn't affect the retransmission of Distribution messages. "
                "(default: %(default)s)"
            ),
        )
        self.add_group_nodes_args(
            self.dist_start_parser,
            add_elem_arg=True,
            add_elem_addrs_arg=True,
            elem_default=0,
            group_addr_help=(
                f"Group address used for the Firmware Distribution procedure. "
                f"The FW Update Server and BLOB Transfer Server models shall "
                f"be subscribed to specified group address. "
                f"If it is unassigned address (0) then the FW Distribution Server "
                f"sends FW Update and BLOB Transfer BT Mesh messages to each "
                f"updating node one by one to the element address of FW Update "
                f"Server and BLOB Transfer Server models."
            ),
            group_help=(
                f"Select the app group which contains group address and updating "
                f"nodes which shall participate in the firmware update. "
                f"The group address of the app group is used as the distribution "
                f"group address. For further details see {self.GROUP_ADDR_OPTS} "
                f"option. "
                f"The nodes of the app group are the receivers of the FW image "
                f"in the FW Distribution procedure. For further details see "
                f"{self.NODES_OPTS} option."
            ),
            nodes_help=(
                f"Select the updating nodes which shall participate in the "
                f"firmware update. The FW Distribution procedure requires the "
                f"receivers which are the element (unicast) addresses of the "
                f"updating nodes. Those element addresses shall be selected "
                f"where the FW Update Server and BLOB Transfer Server models "
                f"are located on the updating node. "
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
                f"Select the updating nodes which participate in the firmware "
                f"update by selecting the element addresses of the updating "
                f"nodes with FW Update Server and BLOB Transfer Server models. "
                f"If {self.ELEM_ADDRS_OPTS} is used then {self.NODES_OPTS} and "
                f"{self.GROUP_OPTS} and {self.ELEM_OPTS} shall not be used."
            ),
        )
        return SUBPARSER_NAME, self.dist_start_parser

    def __call__(self, arg) -> bool:
        pargs = self.parser.parse_args(arg.split())
        self._current_parser = self.subparser_dict.get(
            pargs.dist_subcmd_name, self.parser
        )
        pargs.dist_subcmd(pargs)
        self._current_parser = self.parser
        return False

    def dist_info_cmd(self, pargs):
        nodes = app_db.btmesh_db.get_node_list(order_property="name")
        dist_addr = self.parse_elemspecs(pargs.distributor, nodes)[0]
        # The retry_cmd_max and retry_cmd_interval are used only because the
        # other parameters are overwritten by the arguments of conf ae command
        retry_params_default = app_cfg.common.retry_params_default
        retry_params = self.process_retry_params(pargs, retry_params_default)
        if pargs.capabilities:
            capabilities = app_btmesh.dist_clt.get_capabilities(
                elem_index=app_cfg.dist_clt.elem_index,
                dist_addr=dist_addr,
                appkey_index=pargs.appkey_idx,
                ttl=pargs.ttl,
                retry_params=retry_params,
            )
            max_fw_size = capabilities.max_fw_size
            max_fw_size_kb = math.floor(max_fw_size / 1024)
            max_upload_space = capabilities.max_upload_space
            max_upload_space_kb = math.floor(max_upload_space / 1024)
            rem_upload_space = capabilities.remaining_upload_space
            rem_upload_space_kb = math.floor(rem_upload_space / 1024)
            app_ui.info(
                f"Max upload space: {max_upload_space} bytes "
                f"({max_upload_space_kb}kB)"
            )
            app_ui.info(
                f"Remaining upload space: {rem_upload_space} bytes "
                f"({rem_upload_space_kb}kB)"
            )
            app_ui.info(f"Max FW image size: {max_fw_size} bytes ({max_fw_size_kb}kB)")
            app_ui.info(f"Max FW image list size: {capabilities.max_fw_list_size}")
            app_ui.info(
                f"Max distribution receiver list size: "
                f"{capabilities.max_nodes_list_size}"
            )
            app_ui.info(
                f"OOB support: {capabilities.oob_supported.pretty_name.lower()}"
            )
        elif pargs.fw_list:
            fw_status = app_btmesh.dist_clt.get_fw_by_index(
                elem_index=app_cfg.dist_clt.elem_index,
                dist_addr=dist_addr,
                index=0,
                appkey_index=pargs.appkey_idx,
                ttl=pargs.ttl,
                err_on_fw_miss=False,
                retry_params=retry_params,
            )
            if fw_status.status == FwDistStatus.FWID_NOT_FOUND:
                app_ui.info("The FW image list is empty on the Distributor.")
            elif fw_status.status == FwDistStatus.SUCCESS:
                fw_img_status_list = [fw_status]
                for index in range(1, fw_status.num_entries):
                    # All FW image indexes of the loop shall exist on the FW
                    # Distribution Server because the iteration utilizes the
                    # Entry Count field of the just received FW Distribution
                    # FW Status message.
                    fw_status = app_btmesh.dist_clt.get_fw_by_index(
                        elem_index=app_cfg.dist_clt.elem_index,
                        dist_addr=dist_addr,
                        index=index,
                        appkey_index=pargs.appkey_idx,
                        ttl=pargs.ttl,
                        err_on_fw_miss=True,
                        retry_params=retry_params,
                    )
                    if fw_status.status == FwDistStatus.SUCCESS:
                        fw_img_status_list.append(fw_status)
                rows = []
                for fw_status in fw_img_status_list:
                    fwid_str = app_ui.fwid_str(fw_status.fwid)
                    rows.append({"Index": fw_status.index, "FWID": fwid_str})
                app_ui.table_info(rows)
        elif pargs.fw_list_idx:
            fw_img_status_list: List[FwDistFwStatus] = []
            for index in pargs.fw_list_idx:
                fw_status = app_btmesh.dist_clt.get_fw_by_index(
                    elem_index=app_cfg.dist_clt.elem_index,
                    dist_addr=dist_addr,
                    index=index,
                    appkey_index=pargs.appkey_idx,
                    ttl=pargs.ttl,
                    err_on_fw_miss=False,
                    retry_params=retry_params,
                )
                fw_img_status_list.append(fw_status)
            rows = []
            for fw_status in fw_img_status_list:
                if fw_status.status == FwDistStatus.SUCCESS:
                    fwid_str = app_ui.fwid_str(fw_status.fwid)
                else:
                    fwid_str = "None"
                status_str = fw_status.status.pretty_name
                rows.append(
                    {"Index": fw_status.index, "Status": status_str, "FWID": fwid_str}
                )
            app_ui.table_info(rows)

    def dist_upload_cmd(self, pargs):
        if not pargs.fw_image_path.exists():
            self.current_parser.error(
                f'The FW image file does not exists on "{pargs.fw_image_path}" path.'
            )
        with open(pargs.fw_image_path, "rb") as content_file:
            fw_data = content_file.read()
        app_ui.info(
            f"FW data ({len(fw_data)} bytes) is loaded from " f"{pargs.fw_image_path}."
        )
        nodes = app_db.btmesh_db.get_node_list(order_property="name")
        dist_addr = self.parse_elemspecs(pargs.distributor, nodes)[0]
        retry_params_default = app_cfg.common.retry_params_default
        retry_params = self.process_retry_params(pargs, retry_params_default)
        retry_params.retry_max = app_btmesh.dist_clt.calc_retry_max(
            retry_interval=retry_params.retry_interval,
            timeout_base=pargs.timeout_base,
            ttl=pargs.ttl,
        )
        retry_params.retry_cmd_max = app_btmesh.dist_clt.calc_retry_cmd_max(
            retry_cmd_interval=retry_params.retry_cmd_interval,
            timeout_base=pargs.timeout_base,
            ttl=pargs.ttl,
        )
        app_btmesh.subscribe(
            "btmesh_levt_dist_upload_progress",
            self.handle_dist_upload_progress,
        )
        try:
            app_btmesh.dist_clt.upload(
                elem_index=app_cfg.dist_clt.elem_index,
                dist_addr=dist_addr,
                fwid=pargs.fwid,
                fw_data=fw_data,
                metadata=pargs.metadata,
                timeout_base=pargs.timeout_base,
                chunk_size_pref=pargs.chunk_size,
                appkey_index=pargs.appkey_idx,
                ttl=pargs.ttl,
                retry_interval=retry_params.retry_interval,
                retry_cmd_interval=retry_params.retry_cmd_interval,
            )
            app_db.add_fwid_metadata_pair(pargs.fwid, pargs.metadata)
            app_ui.info(
                f"Firmware with {app_ui.fwid_str(pargs.fwid)} FWID is uploaded "
                f"to Distributor (0x{dist_addr:04X})."
            )
        except BGLibExtSyncSignalException as e:
            app_btmesh.dist_clt.cancel_upload(
                elem_index=app_cfg.dist_clt.elem_index,
                dist_addr=dist_addr,
                retry_params=retry_params,
            )
            app_ui.info("Firmware upload canceled.")
        finally:
            app_btmesh.unsubscribe(
                "btmesh_levt_dist_upload_progress",
                self.handle_dist_upload_progress,
            )

    def handle_dist_upload_progress(self, event: FwDistUploadProgressEvent):
        progress_percentage = 100 * event.done_bytes / event.fw_size
        app_ui.info(f"Upload progress: {progress_percentage:5.2f}%")

    def dist_delete_cmd(self, pargs):
        nodes = app_db.btmesh_db.get_node_list(order_property="name")
        dist_addr = self.parse_elemspecs(pargs.distributor, nodes)[0]
        retry_params_default = app_cfg.common.retry_params_default
        retry_params = self.process_retry_params(pargs, retry_params_default)
        if pargs.fwid:
            app_btmesh.dist_clt.delete_fw(
                elem_index=app_cfg.dist_clt.elem_index,
                dist_addr=dist_addr,
                fwid=pargs.fwid,
                appkey_index=pargs.appkey_idx,
                ttl=pargs.ttl,
                retry_params=retry_params,
            )
            app_ui.info(
                f"Firmware image with {app_ui.fwid_str(pargs.fwid)} FWID is "
                f"deleted on Distributor (0x{dist_addr:04X})"
            )
        else:
            app_btmesh.dist_clt.delete_all_fw(
                elem_index=app_cfg.dist_clt.elem_index,
                dist_addr=dist_addr,
                appkey_index=pargs.appkey_idx,
                ttl=pargs.ttl,
                retry_params=retry_params,
            )
            app_ui.info(
                f"All firmware images are deleted on Distributor (0x{dist_addr:04X})"
            )

    def dist_start_cmd(self, pargs):
        self.last_progress = -1
        self.last_dist_phase = FwDistPhase.UNKNOWN_VALUE
        nodes = app_db.btmesh_db.get_node_list(order_property="name")
        dist_addr = self.parse_elemspecs(pargs.distributor, nodes)[0]
        group_addr, nodes, elem_addrs = self.process_group_nodes_args(
            pargs,
            nodes_order_property="name",
            group_order_property="name",
        )
        retry_params_default = app_cfg.common.btmesh_retry_params_default
        retry_params = self.process_btmesh_retry_params(pargs, retry_params_default)
        fw_list_idx = pargs.fw_list_idx
        fwid = pargs.fwid
        if fwid:
            fw_status = app_btmesh.dist_clt.get_fw(
                elem_index=app_cfg.dist_clt.elem_index,
                dist_addr=dist_addr,
                fwid=fwid,
                appkey_index=pargs.appkey_idx,
                ttl=pargs.ttl,
                err_on_fw_miss=False,
                retry_params=retry_params.to_base(),
            )
            if fw_status.status == FwDistStatus.FWID_NOT_FOUND:
                raise ValueError(
                    f"The {app_ui.fwid_str(fw_status.fwid)} FWID does not exist in "
                    f"the FW image list of the Distributor (0x{dist_addr:04X})."
                )
            fw_list_idx = fw_status.index
        else:
            fw_status = app_btmesh.dist_clt.get_fw_by_index(
                elem_index=app_cfg.dist_clt.elem_index,
                dist_addr=dist_addr,
                index=fw_list_idx,
                appkey_index=pargs.appkey_idx,
                ttl=pargs.ttl,
                err_on_fw_miss=False,
                retry_params=retry_params.to_base(),
            )
            if fw_status.status == FwDistStatus.FWID_NOT_FOUND:
                raise ValueError(
                    f"The firmware with {fw_list_idx} FW list index does not exist "
                    f"in the FW image list of the Distributor (0x{dist_addr:04X})."
                )
            fwid = fw_status.fwid
        fw_idxs = [pargs.fw_idx] * len(elem_addrs)
        receivers = [
            FwReceiver(addr, fw_idx) for addr, fw_idx in zip(elem_addrs, fw_idxs)
        ]
        if pargs.transfer_mode == "push":
            transfer_mode = BlobTransferMode.PUSH
        else:
            transfer_mode = BlobTransferMode.PULL
        app_btmesh.subscribe(
            "btmesh_levt_dist_distribution_progress",
            self.handle_distribution_progress,
        )
        # The metadata is stored at upload and it is queried by the FWID.
        # This is important because there is a metadata check at the beginning
        # of the distribution in order to obtain additional information which
        # determines whether the node becomes unprovisioned after the FW update
        # or not. The metadata can't be queried from the distributor because the
        # Firmware Distribution Firmware Status message contains the FWID only.
        metadata = app_db.get_metadata_by_fwid(fwid=fwid, default=bytes())
        try:
            dist_status, receivers_info = app_btmesh.dist_clt.distribution(
                elem_index=app_cfg.dist_clt.elem_index,
                dist_addr=dist_addr,
                group_addr=group_addr,
                receivers=receivers,
                fw_list_index=fw_list_idx,
                dist_timeout_base=pargs.timeout_base,
                dist_appkey_index=pargs.dist_appkey_idx,
                dist_ttl=pargs.dist_ttl,
                metadata=metadata,
                transfer_mode=transfer_mode,
                appkey_index=pargs.appkey_idx,
                ttl=pargs.ttl,
                dist_poll_int=pargs.poll_int,
                retry_params=retry_params,
            )
            if dist_status.phase == FwDistPhase.IDLE:
                app_ui.info(
                    f"The FW distribution of {fw_list_idx} FW list index "
                    f"is cancelled on the Distributor (0x{dist_addr:04X})."
                )
            elif dist_status.phase in (FwDistPhase.COMPLETED, FwDistPhase.FAILED):
                app_ui.info(
                    f"The FW distribution of {fw_list_idx} FW list index is "
                    f"{dist_status.phase.pretty_name} on the Distributor "
                    f"(0x{dist_addr:04X})."
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
            # be as long as the distribution client timeout. The distributor is
            # poll interval might delay the detection of completed cancellation.
            client_timeout = btmesh.util.dfu_calc_client_timeout(
                timeout_base=pargs.timeout_base,
                ttl=pargs.dist_ttl,
            )
            cancel_max_duration = round(client_timeout + pargs.poll_int)
            app_ui.info(
                f"The FW distribution cancellation procedure is started on the "
                f"Distributor (0x{dist_addr:04X}). The cancellation procedure "
                f"might last for {cancel_max_duration} seconds."
            )
            app_btmesh.dist_clt.cancel_distribution(
                elem_index=app_cfg.dist_clt.elem_index,
                dist_addr=dist_addr,
                appkey_index=pargs.appkey_idx,
                ttl=pargs.ttl,
                dist_poll_int=pargs.poll_int,
                retry_params=retry_params.to_base(),
            )
            app_ui.info(
                f"The FW distribution of {fw_list_idx} FW list index "
                f"is cancelled on the Distributor (0x{dist_addr:04X})."
            )
        finally:
            app_btmesh.unsubscribe(
                "btmesh_levt_dist_distribution_progress",
                self.handle_distribution_progress,
            )

    def handle_distribution_progress(self, event: FwDistDistributionProgressEvent):
        if (
            event.dist_status.phase != self.last_dist_phase
            and event.dist_status.phase == FwDistPhase.TRANSFER_ACTIVE
        ):
            # It looks better if the transfer active phase change is shown
            # before the distribution progress.
            app_ui.info(
                f"Distribution phase is changed to "
                f"{event.dist_status.phase.pretty_name}."
            )
            self.last_dist_phase = event.dist_status.phase
        if event.dist_status.phase not in (FwDistPhase.IDLE, FwDistPhase.UNKNOWN_VALUE):
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
                app_ui.info(f"Distribution transfer progress: {progress:3d}%")
                self.last_progress = progress
        if (
            event.dist_status.phase != self.last_dist_phase
            and event.dist_status.phase != FwDistPhase.TRANSFER_ACTIVE
        ):
            app_ui.info(
                f"Distribution phase is changed to "
                f"{event.dist_status.phase.pretty_name}."
            )
            self.last_dist_phase = event.dist_status.phase


dist_cmd = BtmeshDistCmd()
