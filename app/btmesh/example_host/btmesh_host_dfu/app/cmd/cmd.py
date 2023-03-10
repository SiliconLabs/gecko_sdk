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

import abc
import copy
import functools
from typing import Callable, Dict, List, Optional, Sequence, Tuple

import btmesh.util
from bgapix.bglibx import BGLibExtRetryParams
from btmesh.db import FWID, ModelID, Node
from btmesh.util import BtmeshRetryParams

from ..db import BtmeshDfuAppGroup, app_db
from ..ui import AppUIColumnInfo, BtmeshDfuAppParseSpecError, app_ui
from ..util.argparsex import ArgumentParserExt


def spec_parse_error_handler(func):
    @functools.wraps(func)
    def wrapper_spec_parse_error_handler(self, *args, **kwargs):
        try:
            return func(self, *args, **kwargs)
        except BtmeshDfuAppParseSpecError as e:
            self.current_parser.error(str(e))

    return wrapper_spec_parse_error_handler


class BtmeshCmd(abc.ABC):
    GROUP_ADDR_OPT_LONG = "--group-addr"
    GROUP_ADDR_OPT_SHORT = "-g"
    GROUP_ADDR_OPTS = f"{GROUP_ADDR_OPT_LONG}/{GROUP_ADDR_OPT_SHORT}"
    GROUP_OPT_LONG = "--group"
    GROUP_OPT_SHORT = "-G"
    GROUP_OPTS = f"{GROUP_OPT_LONG}/{GROUP_OPT_SHORT}"
    NODES_OPT_LONG = "--nodes"
    NODES_OPT_SHORT = "-n"
    NODES_OPTS = f"{NODES_OPT_LONG}/{NODES_OPT_SHORT}"
    ELEM_OPT_LONG = "--elem"
    ELEM_OPT_SHORT = "-e"
    ELEM_OPTS = f"{ELEM_OPT_LONG}/{ELEM_OPT_SHORT}"
    ELEM_ADDRS_OPT_LONG = "--addrs"
    ELEM_ADDRS_OPT_SHORT = ""
    ELEM_ADDRS_OPTS = f"{ELEM_ADDRS_OPT_LONG}"

    RETRY_MAX_OPT_LONG = "--retry-max"
    RETRY_MAX_OPTS = f"{RETRY_MAX_OPT_LONG}"
    RETRY_MAX_ATTR_NAME = RETRY_MAX_OPT_LONG[2:].replace("-", "_")

    RETRY_INT_OPT_LONG = "--retry-interval"
    RETRY_INT_OPTS = f"{RETRY_INT_OPT_LONG}"
    RETRY_INT_ATTR_NAME = RETRY_INT_OPT_LONG[2:].replace("-", "_")

    RETRY_INT_LPN_OPT_LONG = "--retry-interval-lpn"
    RETRY_INT_LPN_OPTS = f"{RETRY_INT_LPN_OPT_LONG}"
    RETRY_INT_LPN_ATTR_NAME = RETRY_INT_LPN_OPT_LONG[2:].replace("-", "_")

    RETRY_CMD_MAX_OPT_LONG = "--retry-cmd-max"
    RETRY_CMD_MAX_OPTS = f"{RETRY_CMD_MAX_OPT_LONG}"
    RETRY_CMD_MAX_ATTR_NAME = RETRY_CMD_MAX_OPT_LONG[2:].replace("-", "_")

    RETRY_CMD_INT_OPT_LONG = "--retry-cmd-interval"
    RETRY_CMD_INT_OPTS = f"{RETRY_CMD_INT_OPT_LONG}"
    RETRY_CMD_INT_ATTR_NAME = RETRY_CMD_INT_OPT_LONG[2:].replace("-", "_")

    RETRY_MAX_HELP_DEFAULT = (
        "Maximum command retry count when the expected event is not received "
        "or the received event means a recoverable error. "
        "If the maximum retry count is exceeded and the expected event is not "
        "found or the received event means the same recoverable error then "
        "an error is raised. "
        "Example: the response message of server is lost due to interference. "
    )

    RETRY_INTERVAL_HELP_DEFAULT = (
        "The retry interval is measured between commands in seconds during "
        "retry when the expected event is not received or the received event "
        "means a recoverable error. "
        "Example: keep some time between message transmissions to wait for "
        "the response message of the remote node. "
    )

    RETRY_INTERVAL_LPN_HELP_DEFAULT = (
        "The retry interval is measured between commands in seconds during "
        "retry when the expected event is not received or the received event "
        "means a recoverable error. "
        "This retry interval is used when the target node is a Low Power Node "
        "or the target element address belongs to a Low Power Node."
        "Example: keep some time between message transmissions to wait for "
        "the response message of the remote Low Power Node. "
    )

    RETRY_CMD_MAX_HELP_DEFAULT = (
        "Maximum command retry count when a command fails due to recoverable "
        "error. If the max command retry count is exceeded and the command "
        "still fails with the same error then an error is raised. "
        "Example for recoverable error: lack of dynamic memory in BT Mesh stack. "
    )

    RETRY_CMD_INTERVAL_HELP_DEFAULT = (
        "The retry command interval is measured between commands in seconds "
        "during retry when the command fails due to recoverable error. "
        "Example: keep time between commands to wait to free dynamic memory. "
    )

    COLUMNS_OPT_LONG = "--columns"
    COLUMNS_OPTS = f"{COLUMNS_OPT_LONG}"
    COLUMNS_ATTR_NAME = COLUMNS_OPT_LONG[2:].replace("-", "_")

    ALL_COLUMNS_OPT_LONG = "--all-columns"
    ALL_COLUMNS_OPTS = f"{ALL_COLUMNS_OPT_LONG}"
    ALL_COLUMNS_ATTR_NAME = ALL_COLUMNS_OPT_LONG[2:].replace("-", "_")

    @abc.abstractproperty
    def parser(self) -> ArgumentParserExt:
        raise NotImplementedError()

    @abc.abstractproperty
    def current_parser(self) -> Optional[ArgumentParserExt]:
        raise NotImplementedError()

    @abc.abstractmethod
    def create_parser(self, subparsers) -> ArgumentParserExt:
        raise NotImplementedError()

    @abc.abstractmethod
    def __call__(self, arg) -> bool:
        raise NotImplementedError()

    def help(self):
        app_ui.parser_help(self.parser)

    def add_retry_max_arg(
        self,
        parser: ArgumentParserExt,
        default: Optional[int] = None,
        help: str = "",
    ) -> None:
        parser.add_argument(
            self.RETRY_MAX_OPT_LONG,
            type=int,
            default=default,
            help=(help if help else self.RETRY_MAX_HELP_DEFAULT),
        )

    def add_retry_interval_arg(
        self,
        parser: ArgumentParserExt,
        default: Optional[float] = None,
        help: str = "",
    ) -> None:
        parser.add_argument(
            self.RETRY_INT_OPT_LONG,
            type=float,
            default=default,
            help=(help if help else self.RETRY_INTERVAL_HELP_DEFAULT),
        )

    def add_retry_interval_lpn_arg(
        self,
        parser: ArgumentParserExt,
        default: Optional[float] = None,
        help: str = "",
    ) -> None:
        parser.add_argument(
            self.RETRY_INT_LPN_OPT_LONG,
            type=float,
            default=default,
            help=(help if help else self.RETRY_INTERVAL_LPN_HELP_DEFAULT),
        )

    def add_retry_cmd_max_arg(
        self,
        parser: ArgumentParserExt,
        default: Optional[int] = None,
        help: str = "",
    ) -> None:
        parser.add_argument(
            self.RETRY_CMD_MAX_OPT_LONG,
            type=int,
            default=default,
            help=(help if help else self.RETRY_CMD_MAX_HELP_DEFAULT),
        )

    def add_retry_cmd_interval_arg(
        self,
        parser: ArgumentParserExt,
        default: Optional[float] = None,
        help: str = "",
    ) -> None:
        parser.add_argument(
            self.RETRY_CMD_INT_OPT_LONG,
            type=float,
            default=default,
            help=(help if help else self.RETRY_CMD_INTERVAL_HELP_DEFAULT),
        )

    def add_basic_retry_args(
        self,
        parser: ArgumentParserExt,
        retry_max_default: Optional[int] = None,
        retry_interval_default: Optional[float] = None,
        retry_max_help: str = "",
        retry_interval_help: str = "",
    ):
        self.add_retry_max_arg(
            parser=parser, default=retry_max_default, help=retry_max_help
        )
        self.add_retry_interval_arg(
            parser=parser, default=retry_interval_default, help=retry_interval_help
        )

    def add_btmesh_basic_retry_args(
        self,
        parser: ArgumentParserExt,
        retry_max_default: Optional[int] = None,
        retry_interval_default: Optional[float] = None,
        retry_interval_lpn_default: Optional[float] = None,
        retry_max_help: str = "",
        retry_interval_help: str = "",
        retry_interval_lpn_help: str = "",
    ):
        self.add_basic_retry_args(
            parser=parser,
            retry_max_default=retry_max_default,
            retry_interval_default=retry_interval_default,
            retry_max_help=retry_max_help,
            retry_interval_help=retry_interval_help,
        )
        self.add_retry_interval_lpn_arg(
            parser=parser,
            default=retry_interval_lpn_default,
            help=retry_interval_lpn_help,
        )

    def add_retry_args(
        self,
        parser: ArgumentParserExt,
        retry_max_default: Optional[int] = None,
        retry_interval_default: Optional[float] = None,
        retry_cmd_max_default: Optional[int] = None,
        retry_cmd_interval_default: Optional[float] = None,
        retry_max_help: str = "",
        retry_interval_help: str = "",
        retry_cmd_max_help: str = "",
        retry_cmd_interval_help: str = "",
    ):
        self.add_basic_retry_args(
            parser=parser,
            retry_max_default=retry_max_default,
            retry_interval_default=retry_interval_default,
            retry_max_help=retry_max_help,
            retry_interval_help=retry_interval_help,
        )
        self.add_retry_cmd_max_arg(
            parser=parser, default=retry_cmd_max_default, help=retry_cmd_max_help
        )
        self.add_retry_cmd_interval_arg(
            parser=parser,
            default=retry_cmd_interval_default,
            help=retry_cmd_interval_help,
        )

    def add_btmesh_retry_args(
        self,
        parser: ArgumentParserExt,
        retry_max_default: Optional[int] = None,
        retry_interval_default: Optional[float] = None,
        retry_interval_lpn_default: Optional[float] = None,
        retry_cmd_max_default: Optional[int] = None,
        retry_cmd_interval_default: Optional[float] = None,
        retry_max_help: str = "",
        retry_interval_help: str = "",
        retry_interval_lpn_help: str = "",
        retry_cmd_max_help: str = "",
        retry_cmd_interval_help: str = "",
    ):
        self.add_retry_args(
            parser=parser,
            retry_max_default=retry_max_default,
            retry_interval_default=retry_interval_default,
            retry_cmd_max_default=retry_cmd_max_default,
            retry_cmd_interval_default=retry_cmd_interval_default,
            retry_max_help=retry_max_help,
            retry_interval_help=retry_interval_help,
            retry_cmd_max_help=retry_cmd_max_help,
            retry_cmd_interval_help=retry_cmd_interval_help,
        )
        self.add_retry_interval_lpn_arg(
            parser=parser,
            default=retry_interval_lpn_default,
            help=retry_interval_lpn_help,
        )

    def process_retry_params(
        self, pargs, retry_params_default: BGLibExtRetryParams = None
    ) -> BGLibExtRetryParams:
        retry_max = getattr(pargs, self.RETRY_MAX_ATTR_NAME, None)
        retry_interval = getattr(pargs, self.RETRY_INT_ATTR_NAME, None)
        retry_cmd_max = getattr(pargs, self.RETRY_CMD_MAX_ATTR_NAME, None)
        retry_cmd_interval = getattr(pargs, self.RETRY_CMD_INT_ATTR_NAME, None)
        if retry_params_default:
            retry_params = copy.copy(retry_params_default)
            if retry_max:
                retry_params.retry_max = retry_max
            if retry_interval:
                retry_params.retry_interval = retry_interval
            if retry_cmd_max:
                retry_params.retry_cmd_max = retry_cmd_max
            if retry_cmd_interval:
                retry_params.retry_cmd_interval = retry_cmd_interval
        else:
            if retry_max is None:
                raise ValueError(f"The {self.RETRY_MAX_OPTS} arg is missing.")
            if retry_interval is None:
                raise ValueError(f"The {self.RETRY_INT_OPTS} arg is missing.")
            if retry_cmd_max is None:
                raise ValueError(f"The {self.RETRY_CMD_MAX_OPTS} arg is missing.")
            if retry_cmd_interval is None:
                raise ValueError(f"The {self.RETRY_CMD_INT_OPTS} arg is missing.")
            retry_params = BGLibExtRetryParams(
                retry_max=retry_max,
                retry_interval=retry_interval,
                retry_cmd_max=retry_cmd_max,
                retry_cmd_interval=retry_cmd_interval,
            )
        return retry_params

    def process_btmesh_retry_params(
        self, pargs, retry_params_default: BtmeshRetryParams = None
    ) -> BtmeshRetryParams:
        base_retry_params = self.process_retry_params(pargs, retry_params_default)
        retry_interval_lpn = getattr(pargs, self.RETRY_INT_LPN_ATTR_NAME, None)
        if retry_params_default:
            if retry_interval_lpn is None:
                retry_interval_lpn = retry_params_default.retry_interval_lpn
        else:
            if retry_interval_lpn is None:
                raise ValueError(f"The {self.RETRY_INT_LPN_OPTS} arg is missing.")
        retry_params = BtmeshRetryParams(
            retry_max=base_retry_params.retry_max,
            retry_interval=base_retry_params.retry_interval,
            retry_cmd_max=base_retry_params.retry_cmd_max,
            retry_cmd_interval=base_retry_params.retry_cmd_interval,
            retry_interval_lpn=retry_interval_lpn,
        )
        return retry_params

    def add_nodes_pos_arg(
        self,
        parser: ArgumentParserExt,
        help: str = "",
    ):
        parser.add_argument(
            "nodespec",
            metavar="<nodespec>",
            default=[],
            nargs="+",
            help=f"{help} {app_ui.NODESPEC_HELP}",
        )

    def add_nodes_arg(
        self,
        parser: ArgumentParserExt,
        help: str = "",
    ):
        parser.add_argument(
            self.NODES_OPT_LONG,
            self.NODES_OPT_SHORT,
            metavar="<nodespec>",
            default=[],
            nargs="+",
            help=f"{help} {app_ui.NODESPEC_HELP}",
        )

    def add_app_group_pos_arg(self, parser: ArgumentParserExt, help: str = ""):
        parser.add_argument(
            "groupspec",
            metavar="<groupspec>",
            default=[],
            nargs="+",
            help=f"{help} {app_ui.GROUPSPEC_HELP}",
        )

    def add_group_nodes_args(
        self,
        parser: ArgumentParserExt,
        add_elem_arg: bool = False,
        add_elem_addrs_arg: bool = False,
        elem_default: Optional[int] = None,
        group_addr_help: str = "",
        group_help: str = "",
        nodes_help: str = "",
        elem_help: str = "",
        elem_addrs_help: str = "",
    ) -> None:
        parser.add_argument(
            self.GROUP_ADDR_OPT_LONG,
            self.GROUP_ADDR_OPT_SHORT,
            help=f"{group_addr_help} The group address can be specified as a "
            f"binary (0b), octal(0o), decimal, hex (0x) integer.",
        )
        target_group = parser.add_mutually_exclusive_group(required=True)
        target_group.add_argument(
            self.GROUP_OPT_LONG,
            self.GROUP_OPT_SHORT,
            metavar="<groupspec>",
            help=f"{group_help} {app_ui.GROUPSPEC_HELP}",
        )
        target_group.add_argument(
            self.NODES_OPT_LONG,
            self.NODES_OPT_SHORT,
            metavar="<nodespec>",
            default=[],
            nargs="+",
            help=f"{nodes_help} {app_ui.NODESPEC_HELP}",
        )
        if add_elem_addrs_arg:
            target_group.add_argument(
                self.ELEM_ADDRS_OPT_LONG,
                metavar="<elemspec>",
                nargs="+",
                help=f"{elem_addrs_help} {app_ui.ELEMSPEC_HELP}",
            )
        if add_elem_arg:
            # Argparse documentation:
            # If the type keyword is used with the default keyword, the type
            # converter is only applied if the default is a string.
            # Conclusion: This means that None value is preserved so it can
            # be used to indicate that no default value is specified.
            if elem_default is None:
                elem_default_help = ""
            else:
                elem_default_help = " (default: %(default)s)"
            parser.add_argument(
                self.ELEM_OPT_LONG,
                self.ELEM_OPT_SHORT,
                type=int,
                default=elem_default,
                help=f"{elem_help} Element shall be specified as a decimal "
                f"integer value.{elem_default_help}",
            )

    def process_group_nodes_args(
        self,
        pargs,
        nodes_filter: Callable[[Node], bool] = None,
        nodes_order_property: str = None,
        nodes_reverse: bool = False,
        group_filter: Callable[[Node], bool] = None,
        group_order_property: str = None,
        group_reverse: bool = False,
        elem_addrs_filter: Callable[[int], bool] = None,
    ) -> Tuple[int, List[Node], Optional[List[int]]]:
        elem_addrs = None
        group_addr = btmesh.util.UNASSIGNED_ADDR
        # If the add_group_nodes_args was called with false add_elem_arg and
        # false add_elem_addrs_arg parameters then the elem and elem_addrs
        # arguments are not added to the parser which means the Namespace object
        # in pargs parameter doesn't have elem and elem_addrs attributes.
        elem_support = hasattr(pargs, "elem")
        elem_addr_support = hasattr(pargs, "addrs")
        # The --elem and --addrs are mutually exclusive. The --addrs provides
        # the element addresses directly while --elem determines the element
        # index and the element addresses are calculated from --elem and
        # --nodes/--group arguments. The --elem can have default value when
        # the elem_default parameter of add_group_nodes_args method is set to
        # an integer value so the condition below checks --nodes/--group and
        # --addrs arguments to make sure that the mutual exclusion of --elem
        # and --addrs arguments are respected.
        if (
            elem_support
            and elem_addr_support
            and not (
                ((not pargs.nodes) and (pargs.group is None)) or (pargs.addrs is None)
            )
        ):
            # Parser error raises an exception
            self.current_parser.error(
                f"argument {self.ELEM_OPTS}: not allowed with "
                f"argument {self.ELEM_ADDRS_OPTS}."
            )
        if elem_support and (pargs.elem is None) and (pargs.nodes or pargs.group):
            # Parser error raises an exception
            self.current_parser.error(
                f"argument {self.ELEM_OPTS}: mandatory when {self.NODES_OPTS} or "
                f"{self.GROUP_OPTS} is present."
            )
        # If --nodes or --group argument is used then it is mandatory to provide
        # --elem argument as well. If the --elem argument has default value then
        # it might be an integer even when the --addrs argument is used.
        # The --addrs check is essential in the condition to avoid false errors.
        if (
            (elem_support and pargs.elem is not None)
            and (elem_addr_support and pargs.addrs is None)
            and not (pargs.nodes or pargs.group)
        ):
            # Parser error raises an exception
            self.current_parser.error(
                f"argument {self.NODES_OPTS} or {self.GROUP_OPTS}: mandatory when "
                f"{self.ELEM_OPTS} is present."
            )

        if pargs.nodes:
            db_nodes = app_db.btmesh_db.get_node_list(
                nodefilter=nodes_filter,
                order_property=nodes_order_property,
                reverse=nodes_reverse,
            )
            nodes = self.parse_nodespecs(pargs.nodes, db_nodes)
        elif pargs.group:
            db_app_groups = app_db.get_app_group_list(
                groupfilter=group_filter,
                order_property=group_order_property,
                reverse=group_reverse,
            )
            app_group = self.parse_groupspec(pargs.group, db_app_groups)
            nodes = app_db.get_app_group_node_list(
                app_group.name,
                nodefilter=nodes_filter,
                order_property=nodes_order_property,
                reverse=nodes_reverse,
            )
            group_addr = app_group.group_addr
        elif elem_addr_support and pargs.addrs:
            identity = lambda n: n
            elem_addrs_filter = elem_addrs_filter if elem_addrs_filter else identity
            db_nodes = app_db.btmesh_db.get_node_list(
                nodefilter=nodes_filter,
                order_property=nodes_order_property,
                reverse=nodes_reverse,
            )
            elem_addrs = self.parse_elemspecs(pargs.addrs, db_nodes)
            elem_addrs = [addr for addr in elem_addrs if elem_addrs_filter(addr)]
            nodes_gen = (
                app_db.btmesh_db.get_node_by_elem_addr(addr) for addr in elem_addrs
            )
            # Remove duplicate entries from the list
            # Note: Dictionaries are ordered from Python 3.7 and the required
            # python version is 3.7 as well so the dict can be considered ordered
            nodes = list(dict.fromkeys(nodes_gen))
        else:
            raise KeyError(
                f"One of {self.NODES_OPTS} or {self.GROUP_OPTS} or "
                f"{self.ELEM_ADDRS_OPTS} options is mandatory."
            )
        if elem_support and not (elem_addr_support and pargs.addrs is not None):
            # The --elem and --addrs options are mutually exclusive so elem_addrs
            # is None when this condition is true
            elem_addrs = [
                addr for node in nodes for addr in node.get_elem_addrs(pargs.elem)
            ]

        if group_addr and pargs.group_addr:
            # Parser error raises an exception
            self.current_parser.error(
                f"argument {self.GROUP_ADDR_OPTS}: not allowed with argument "
                f"{self.GROUP_OPTS} when the app group specified by "
                f"{self.GROUP_OPTS} has non-zero group address"
            )
        if pargs.group_addr:
            btmesh.util.validate_group_address(pargs.group_addr)
            group_addr = btmesh.util.addr_to_int(pargs.group_addr)
        elif pargs.group_addr == 0:
            # It is allowed to pass an app group by --group option with
            # --group-addr 0 as unassigned address. This selects the nodes from
            # the app group but the BT Mesh messages are sent to the unicast
            # address of each node.
            group_addr = 0
        return group_addr, nodes, elem_addrs

    def add_chunk_size_arg(
        self, parser: ArgumentParserExt, default: int = None, help=""
    ):
        HELP_DEFAULT = (
            "Preferred chunk size during BLOB transfer. "
            "The maximum chunk size is limited by the Max Chunk Size capabilities "
            "of participating BLOB Transfer Servers. "
            "The minimum chunk size is limited by the calculated block size and "
            "Max Total chunk capabilities of participating BLOB Transfer Servers. "
            "The default chunk size calculation algorithm selects the preferred "
            "chunk size when it is in the range defined by min and max chunk "
            "size limits. Otherwise, the algorithm selects the nearest valid "
            "value which fills the BT Mesh messages. "
            "If Silabs BT Mesh over Advertisement Extensions proprietary feature "
            "is enabled then the network PDU size is selected as the chunk size "
            "unless the minimum chunk size is higher. "
            "The standard (non-AE) segmented chunks are able to transfer 12 bytes "
            "per advertisement minus the 1 byte opcode and 2 byte chunk number "
            "and 4 bytes of MIC. This means N advertisements are able to transfer "
            "12 x N - 7 bytes of chunk data. The standard unsegmented chunk is "
            "able to transfer 8 bytes of chunk data. "
            "(default: %(default)s)"
        )
        parser.add_argument(
            "--chunk-size",
            type=int,
            default=default,
            help=help if help else HELP_DEFAULT,
        )

    def add_column_args(
        self,
        parser: ArgumentParserExt,
        table_name: str,
        column_info_dict: Dict[str, AppUIColumnInfo],
    ):
        parser.add_argument(
            self.ALL_COLUMNS_OPT_LONG,
            action="store_true",
            help=f"All columns of {table_name} table are present.",
        )
        parser.add_argument(
            self.COLUMNS_OPT_LONG,
            nargs="+",
            choices=[column for column in column_info_dict.keys()],
            default=[
                column
                for column in column_info_dict.keys()
                if column_info_dict[column].default
            ],
            help=f"Select columns of {table_name} table.",
        )

    def process_column_args(
        self, pargs, column_info_dict: Dict[str, AppUIColumnInfo]
    ) -> Dict[str, str]:
        all_columns_arg = getattr(pargs, self.ALL_COLUMNS_ATTR_NAME)
        columns_arg = getattr(pargs, self.COLUMNS_ATTR_NAME)
        if all_columns_arg:
            columns = list(column_info_dict.keys())
        else:
            columns = columns_arg
        selected_columns = {col: column_info_dict[col].header for col in columns}
        return selected_columns

    @spec_parse_error_handler
    def parse_nodespecs(
        self, nodespecs, node_list: Sequence[Node], filter_duplicates: bool = True
    ) -> List[Node]:
        return app_ui.parse_nodespecs(nodespecs, node_list, filter_duplicates)

    @spec_parse_error_handler
    def parse_elemspecs(
        self, elemspecs, node_list: Sequence[Node], filter_duplicates: bool = True
    ) -> List[int]:
        return app_ui.parse_elemspecs(elemspecs, node_list, filter_duplicates)

    @spec_parse_error_handler
    def parse_mdlspecs(self, mdlspecs, filter_duplicates: bool = True) -> List[ModelID]:
        return app_ui.parse_mdlspecs(mdlspecs, filter_duplicates)

    @spec_parse_error_handler
    def parse_fwidspec(self, fwidspec) -> FWID:
        return app_ui.parse_fwidspec(fwidspec)

    @spec_parse_error_handler
    def parse_fwidspecs(self, fwidspecs, filter_duplicates: bool = True) -> List[FWID]:
        return app_ui.parse_fwidspecs(fwidspecs, filter_duplicates)

    @spec_parse_error_handler
    def parse_metaspec(self, metaspec) -> bytes:
        return app_ui.parse_metaspec(metaspec)

    @spec_parse_error_handler
    def parse_metaspecs(self, metaspecs, filter_duplicates: bool = True) -> List[bytes]:
        return app_ui.parse_metaspecs(metaspecs, filter_duplicates)

    @spec_parse_error_handler
    def parse_groupspec(
        self, groupspec, app_group_list: Sequence[BtmeshDfuAppGroup]
    ) -> BtmeshDfuAppGroup:
        return app_ui.parse_groupspec(groupspec, app_group_list)

    @spec_parse_error_handler
    def parse_groupspecs(
        self,
        groupspecs,
        app_group_list: Sequence[BtmeshDfuAppGroup],
        filter_duplicates: bool = True,
    ) -> List[BtmeshDfuAppGroup]:
        return app_ui.parse_groupspecs(groupspecs, app_group_list, filter_duplicates)
