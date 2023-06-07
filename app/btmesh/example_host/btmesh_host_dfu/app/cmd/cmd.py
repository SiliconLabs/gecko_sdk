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
from btmesh.util import (BtmeshMulticastRetryParams, BtmeshRetryParams,
                         ConnectionParamsRange)

from ..db import BtmeshDfuAppGroup, app_db
from ..ui import (AppUIColumnInfo, BtmeshDfuAppParseSpecError,
                  BtmeshDfuAppSpecName, app_ui)
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

    BD_ADDRS_OPT_LONG = "--bd-addrs"
    BD_ADDRS_OPTS = f"{BD_ADDRS_OPT_LONG}"
    BD_ADDRS_ATTR_NAME = BD_ADDRS_OPT_LONG[2:].replace("-", "_")

    BD_ADDR_OPT_LONG = "--bd-addr"
    BD_ADDR_OPTS = f"{BD_ADDR_OPT_LONG}"
    BD_ADDR_ATTR_NAME = BD_ADDR_OPT_LONG[2:].replace("-", "_")

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

    RETRY_MULCAST_THR_OPT_LONG = "--retry-multicast-thr"
    RETRY_MULCAST_THR_OPTS = f"{RETRY_MULCAST_THR_OPT_LONG}"
    RETRY_MULCAST_THR_ATTR_NAME = RETRY_MULCAST_THR_OPT_LONG[2:].replace("-", "_")

    RETRY_AUTO_UNICAST_OPT_LONG = "--retry-auto-unicast"
    RETRY_AUTO_UNICAST_OPTS = f"{RETRY_AUTO_UNICAST_OPT_LONG}"
    RETRY_AUTO_UNICAST_ATTR_NAME = RETRY_AUTO_UNICAST_OPT_LONG[2:].replace("-", "_")

    CONN_OPEN_TIMEOUT_OPT_LONG = "--conn-open-timeout"
    CONN_OPEN_TIMEOUT_ATTR_NAME = CONN_OPEN_TIMEOUT_OPT_LONG[2:].replace("-", "_")

    CONN_MIN_INTERVAL_OPT_LONG = "--conn-min-interval"
    CONN_MIN_INTERVAL_ATTR_NAME = CONN_MIN_INTERVAL_OPT_LONG[2:].replace("-", "_")

    CONN_MAX_INTERVAL_OPT_LONG = "--conn-max-interval"
    CONN_MAX_INTERVAL_ATTR_NAME = CONN_MAX_INTERVAL_OPT_LONG[2:].replace("-", "_")

    CONN_LATENCY_OPT_LONG = "--conn-latency"
    CONN_LATENCY_ATTR_NAME = CONN_LATENCY_OPT_LONG[2:].replace("-", "_")

    CONN_TIMEOUT_OPT_LONG = "--conn-timeout"
    CONN_TIMEOUT_ATTR_NAME = CONN_TIMEOUT_OPT_LONG[2:].replace("-", "_")

    CONN_MIN_CE_LENGTH_OPT_LONG = "--conn-min-ce-len"
    CONN_MIN_CE_LENGTH_ATTR_NAME = CONN_MIN_CE_LENGTH_OPT_LONG[2:].replace("-", "_")

    CONN_MAX_CE_LENGTH_OPT_LONG = "--conn-max-ce-len"
    CONN_MAX_CE_LENGTH_ATTR_NAME = CONN_MAX_CE_LENGTH_OPT_LONG[2:].replace("-", "_")

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

    RETRY_MULCAST_THR_HELP_DEFAULT = (
        "If the number of remaining node elements (element addresses) with "
        "missing status messages exceeds or equals to the retry multicast "
        "threshold then the group address is used to send BT Mesh messages, "
        "otherwise each element address is looped through one by one. "
        "Zero value means unicast addressing."
    )

    RETRY_AUTO_UNICAST_HELP_DEFAULT = (
        "If auto unicast retry feature is turned on and the multicast retry "
        "procedure fails before the number of remaining nodes elements (element "
        "addresses) with missing status messages goes below the retry "
        "multicast threshold then an additional unicast retry procedure is "
        "executed otherwise the remaining node elements fail with timeout."
    )

    CONN_OPEN_TIMEOUT_MS_HELP_DEFAULT = (
        "Bluetooth connection opening and proxy connection establishment "
        "timeout in milliseconds."
        "(default: %(default)s ms)"
    )

    CONN_MIN_INTERVAL_MS_HELP_DEFAULT = (
        f"Minimum value for the connection event interval in milliseconds. "
        f"Range: {btmesh.util.CONN_INTERVAL_MS_MIN} ms - "
        f"{btmesh.util.CONN_INTERVAL_MS_MAX} ms; "
        f"Resolution: {btmesh.util.CONN_INTERVAL_MS_RES} ms "
        "(default: %(default)s ms)"
    )

    CONN_MAX_INTERVAL_MS_HELP_DEFAULT = (
        f"Maximum value for the connection event interval in milliseconds. "
        f"Range: {btmesh.util.CONN_INTERVAL_MS_MIN} ms - "
        f"{btmesh.util.CONN_INTERVAL_MS_MAX} ms; "
        f"Resolution: {btmesh.util.CONN_INTERVAL_MS_RES} ms "
        "(default: %(default)s ms)"
    )

    CONN_LATENCY_HELP_DEFAULT = (
        f"Peripheral latency, which defines how many connection intervals the "
        f"peripheral can skip if it has no data to send. "
        f"Range: 0x{btmesh.util.CONN_LATENCY_MIN:04X}-"
        f"0x{btmesh.util.CONN_LATENCY_MAX:04X} "
        "(default: %(default)s ms)"
    )

    CONN_TIMEOUT_MS_HELP_DEFAULT = (
        f"Supervision timeout in milliseconds, which defines the time that the "
        f"connection is maintained although the devices can't communicate at the "
        f"currently configured connection intervals. "
        f"The supervision timeout value in milliseconds shall be larger than "
        f"(1 + latency) * max_interval * 2, where max_interval is given "
        f"in milliseconds. "
        f"Range: {btmesh.util.CONN_TIMEOUT_MS_MIN} ms - "
        f"{btmesh.util.CONN_TIMEOUT_MS_MAX} ms; "
        f"Resolution: {btmesh.util.CONN_TIMEOUT_MS_RES} ms "
        "(default: %(default)s ms)"
    )

    CONN_MIN_CE_LENGTH_MS_HELP_DEFAULT = (
        f"Minimum length of the connection event. "
        f"This value defines the minimum time that should be given to the "
        f"connection event in a situation where other tasks need to run "
        f"immediately after the connection event. When the value is very small, "
        f"the connection event still has at least one TX/RX operation. "
        f"If this value is increased, more time is reserved for the connection "
        f"event so it can transmit and receive more packets in a connection "
        f"interval. "
        f"Range: {btmesh.util.CONN_EVT_LEN_CNT_MIN} ms - "
        f"{btmesh.util.CONN_EVT_LEN_CNT_MAX} ms "
        f"(multiplied by {btmesh.util.CONN_EVT_LEN_MS_RES}) "
        f"Resolution: {btmesh.util.CONN_EVT_LEN_MS_RES} ms "
        "(default: %(default)s ms)"
    )

    CONN_MAX_CE_LENGTH_MS_HELP_DEFAULT = (
        f"Maximum length of the connection event. "
        f"This value is used for limiting the connection event length so that "
        f"a connection that has large amounts of data to transmit or receive "
        f"doesn't block other tasks. "
        f"Limiting the connection event is a hard stop. If there is no enough "
        f"time to send or receive a packet, the connection event will be closed. "
        f"If the value is set to 0, the connection event still has at least one "
        f"TX/RX operation. This is useful to limit power consumption or leave "
        f"more time to other tasks. "
        f"Range: {btmesh.util.CONN_EVT_LEN_CNT_MIN} ms - "
        f"{btmesh.util.CONN_EVT_LEN_CNT_MAX} ms "
        f"(multiplied by {btmesh.util.CONN_EVT_LEN_MS_RES}) "
        f"Resolution: {btmesh.util.CONN_EVT_LEN_MS_RES} ms "
        "(default: %(default)s ms)"
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

    def add_retry_multicast_threshold_arg(
        self,
        parser: ArgumentParserExt,
        default: Optional[int] = None,
        help: str = "",
    ) -> None:
        parser.add_argument(
            self.RETRY_MULCAST_THR_OPT_LONG,
            type=int,
            default=default,
            help=(help if help else self.RETRY_MULCAST_THR_HELP_DEFAULT),
        )

    def add_retry_auto_unicast_arg(
        self,
        parser: ArgumentParserExt,
        default: Optional[str] = "off",
        help: str = "",
    ) -> None:
        parser.add_argument(
            self.RETRY_AUTO_UNICAST_OPT_LONG,
            choices=["on", "off"],
            default=default,
            help=(help if help else self.RETRY_AUTO_UNICAST_HELP_DEFAULT),
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

    def add_btmesh_multicast_basic_retry_args(
        self,
        parser: ArgumentParserExt,
        retry_max_default: Optional[int] = None,
        retry_interval_default: Optional[float] = None,
        retry_interval_lpn_default: Optional[float] = None,
        retry_multicast_threshold_default: Optional[int] = None,
        retry_max_help: str = "",
        retry_interval_help: str = "",
        retry_interval_lpn_help: str = "",
        retry_multicast_threshold_help: str = "",
    ):
        self.add_btmesh_basic_retry_args(
            parser=parser,
            retry_max_default=retry_max_default,
            retry_interval_default=retry_interval_default,
            retry_interval_lpn_default=retry_interval_lpn_default,
            retry_max_help=retry_max_help,
            retry_interval_help=retry_interval_help,
            retry_interval_lpn_help=retry_interval_lpn_help,
        )
        self.add_retry_multicast_threshold_arg(
            parser=parser,
            default=retry_multicast_threshold_default,
            help=retry_multicast_threshold_help,
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

    def add_btmesh_multicast_retry_args(
        self,
        parser: ArgumentParserExt,
        retry_max_default: Optional[int] = None,
        retry_interval_default: Optional[float] = None,
        retry_interval_lpn_default: Optional[float] = None,
        retry_cmd_max_default: Optional[int] = None,
        retry_cmd_interval_default: Optional[float] = None,
        retry_multicast_threshold_default: Optional[int] = None,
        retry_auto_unicast_default: Optional[bool] = None,
        retry_max_help: str = "",
        retry_interval_help: str = "",
        retry_interval_lpn_help: str = "",
        retry_cmd_max_help: str = "",
        retry_cmd_interval_help: str = "",
        retry_multicast_threshold_help: str = "",
        retry_auto_unicast_help: str = "",
    ):
        self.add_btmesh_retry_args(
            parser,
            retry_max_default=retry_max_default,
            retry_interval_default=retry_interval_default,
            retry_interval_lpn_default=retry_interval_lpn_default,
            retry_cmd_max_default=retry_cmd_max_default,
            retry_cmd_interval_default=retry_cmd_interval_default,
            retry_max_help=retry_max_help,
            retry_interval_help=retry_interval_help,
            retry_interval_lpn_help=retry_interval_lpn_help,
            retry_cmd_max_help=retry_cmd_max_help,
            retry_cmd_interval_help=retry_cmd_interval_help,
        )
        self.add_retry_multicast_threshold_arg(
            parser,
            default=retry_multicast_threshold_default,
            help=retry_multicast_threshold_help,
        )
        self.add_retry_auto_unicast_arg(
            parser,
            default=retry_auto_unicast_default,
            help=retry_auto_unicast_help,
        )

    def process_retry_params(
        self, pargs, retry_params_default: BGLibExtRetryParams = None
    ) -> BGLibExtRetryParams:
        retry_max = getattr(pargs, self.RETRY_MAX_ATTR_NAME, None)
        retry_interval = getattr(pargs, self.RETRY_INT_ATTR_NAME, None)
        retry_cmd_max = getattr(pargs, self.RETRY_CMD_MAX_ATTR_NAME, None)
        retry_cmd_interval = getattr(pargs, self.RETRY_CMD_INT_ATTR_NAME, None)
        if retry_params_default:
            # The default retry parameter might a subclass of BGLibExtRetryParams
            # so make sure that the returned type is BGLibExtRetryParams.
            # The to_base() method creates a new object from the default which
            # is important in order to avoid modifying the method parameter.
            retry_params = retry_params_default.to_base()
            if retry_max is not None:
                retry_params.retry_max = retry_max
            if retry_interval is not None:
                retry_params.retry_interval = retry_interval
            if retry_cmd_max is not None:
                retry_params.retry_cmd_max = retry_cmd_max
            if retry_cmd_interval is not None:
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
        base_retry_params = self.process_retry_params(
            pargs, retry_params_default.to_base(use_interval_lpn=False)
        )
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

    def process_btmesh_multicast_retry_params(
        self, pargs, retry_params_default: BtmeshMulticastRetryParams = None
    ) -> BtmeshMulticastRetryParams:
        btmesh_retry_params = self.process_btmesh_retry_params(
            pargs, retry_params_default
        )
        retry_multicast_threshold = getattr(
            pargs, self.RETRY_MULCAST_THR_ATTR_NAME, None
        )
        retry_auto_unicast_raw = getattr(pargs, self.RETRY_AUTO_UNICAST_ATTR_NAME, None)
        if retry_auto_unicast_raw is None:
            retry_auto_unicast = None
        else:
            if retry_auto_unicast_raw == "on":
                retry_auto_unicast = True
            else:
                retry_auto_unicast = False
        if retry_params_default:
            if retry_multicast_threshold is None:
                retry_multicast_threshold = retry_params_default.multicast_threshold
            if retry_auto_unicast is None:
                retry_auto_unicast = retry_params_default.auto_unicast
        else:
            if retry_multicast_threshold is None:
                raise ValueError(f"The {self.RETRY_MULCAST_THR_OPTS} arg is missing.")
            if retry_auto_unicast is None:
                raise ValueError(f"The {self.RETRY_AUTO_UNICAST_OPTS} arg is missing.")
        retry_params = BtmeshMulticastRetryParams(
            retry_max=btmesh_retry_params.retry_max,
            retry_interval=btmesh_retry_params.retry_interval,
            retry_cmd_max=btmesh_retry_params.retry_cmd_max,
            retry_cmd_interval=btmesh_retry_params.retry_cmd_interval,
            retry_interval_lpn=btmesh_retry_params.retry_interval_lpn,
            multicast_threshold=retry_multicast_threshold,
            auto_unicast=retry_auto_unicast,
        )
        return retry_params

    def add_connection_open_timeout_arg(
        self,
        parser: ArgumentParserExt,
        default: float = 5_000.0,
        help: str = CONN_OPEN_TIMEOUT_MS_HELP_DEFAULT,
    ):
        parser.add_argument(
            self.CONN_OPEN_TIMEOUT_OPT_LONG,
            type=float,
            default=default,
            help=help,
        )

    def process_connection_open_timeout(self, pargs) -> float:
        open_timeout_ms = getattr(pargs, self.CONN_OPEN_TIMEOUT_ATTR_NAME, None)
        return open_timeout_ms

    def add_connection_params_range_args(
        self,
        parser: ArgumentParserExt,
        min_interval_ms_default: float = 7.5,
        max_interval_ms_default: float = 4_000.0,
        latency_default: int = 1,
        timeout_ms_default: float = 20_000.0,
        min_ce_length_ms_default: float = 0,
        max_ce_length_ms_default: float = 0xFFFF * 0.625,
        min_interval_ms_help: str = CONN_MIN_INTERVAL_MS_HELP_DEFAULT,
        max_interval_ms_help: str = CONN_MAX_INTERVAL_MS_HELP_DEFAULT,
        latency_help: str = CONN_LATENCY_HELP_DEFAULT,
        timeout_ms_help: str = CONN_TIMEOUT_MS_HELP_DEFAULT,
        min_ce_length_ms_help=CONN_MIN_CE_LENGTH_MS_HELP_DEFAULT,
        max_ce_length_ms_help=CONN_MAX_CE_LENGTH_MS_HELP_DEFAULT,
    ):
        parser.add_argument(
            self.CONN_MIN_INTERVAL_OPT_LONG,
            type=float,
            default=min_interval_ms_default,
            help=min_interval_ms_help,
        )
        parser.add_argument(
            self.CONN_MAX_INTERVAL_OPT_LONG,
            type=float,
            default=max_interval_ms_default,
            help=max_interval_ms_help,
        )
        parser.add_argument(
            self.CONN_LATENCY_OPT_LONG,
            type=int,
            default=latency_default,
            help=latency_help,
        )
        parser.add_argument(
            self.CONN_TIMEOUT_OPT_LONG,
            type=float,
            default=timeout_ms_default,
            help=timeout_ms_help,
        )
        parser.add_argument(
            self.CONN_MIN_CE_LENGTH_OPT_LONG,
            type=float,
            default=min_ce_length_ms_default,
            help=min_ce_length_ms_help,
        )
        parser.add_argument(
            self.CONN_MAX_CE_LENGTH_OPT_LONG,
            type=float,
            default=max_ce_length_ms_default,
            help=max_ce_length_ms_help,
        )

    def process_connection_params_range(
        self, pargs, conn_params_range_default: Optional[ConnectionParamsRange] = None
    ) -> ConnectionParamsRange:
        min_interval_ms = getattr(pargs, self.CONN_MIN_INTERVAL_ATTR_NAME, None)
        max_interval_ms = getattr(pargs, self.CONN_MAX_INTERVAL_ATTR_NAME, None)
        latency = getattr(pargs, self.CONN_LATENCY_ATTR_NAME, None)
        timeout_ms = getattr(pargs, self.CONN_TIMEOUT_ATTR_NAME, None)
        min_ce_length_ms = getattr(pargs, self.CONN_MIN_CE_LENGTH_ATTR_NAME, None)
        max_ce_length_ms = getattr(pargs, self.CONN_MAX_CE_LENGTH_ATTR_NAME, None)
        if conn_params_range_default:
            conn_params_range = copy.copy(conn_params_range_default)
            if min_interval_ms:
                conn_params_range.min_interval_ms = min_interval_ms
            if max_interval_ms:
                conn_params_range.max_interval_ms = max_interval_ms
            if latency:
                conn_params_range.latency = latency
            if timeout_ms:
                conn_params_range.timeout_ms = timeout_ms
            if min_ce_length_ms:
                conn_params_range.min_ce_length_ms = min_ce_length_ms
            if max_ce_length_ms:
                conn_params_range.max_ce_length_ms = max_ce_length_ms
            conn_params_range.validate()
        else:
            if min_interval_ms is None:
                raise ValueError(
                    f"The {self.CONN_MIN_INTERVAL_OPT_LONG} arg is missing."
                )
            if max_interval_ms is None:
                raise ValueError(
                    f"The {self.CONN_MAX_INTERVAL_OPT_LONG} arg is missing."
                )
            if latency is None:
                raise ValueError(f"The {self.CONN_LATENCY_OPT_LONG} arg is missing.")
            if timeout_ms is None:
                raise ValueError(f"The {self.CONN_TIMEOUT_OPT_LONG} arg is missing.")
            if min_ce_length_ms is None:
                raise ValueError(
                    f"The {self.CONN_MIN_CE_LENGTH_OPT_LONG} arg is missing."
                )
            if max_ce_length_ms is None:
                raise ValueError(
                    f"The {self.CONN_MAX_CE_LENGTH_OPT_LONG} arg is missing."
                )
            conn_params_range = ConnectionParamsRange(
                min_interval_ms=min_interval_ms,
                max_interval_ms=max_interval_ms,
                latency=latency,
                timeout_ms=timeout_ms,
                min_ce_length_ms=min_ce_length_ms,
                max_ce_length_ms=max_ce_length_ms,
            )
        return conn_params_range

    def add_bd_addrs_arg(self, parser: ArgumentParserExt, help: str = ""):
        parser.add_argument(
            self.BD_ADDRS_OPT_LONG,
            metavar="<bdaddrspec>",
            nargs="+",
            help=f"{help} {app_ui.BDADDRSPEC_HELP}",
        )

    def add_bd_addr_arg(self, parser: ArgumentParserExt, help: str = ""):
        parser.add_argument(
            self.BD_ADDR_OPT_LONG,
            metavar="<bdaddrspec>",
            help=f"{help} {app_ui.BDADDRSPEC_HELP}",
        )

    def process_bd_addrs_arg(self, pargs):
        bdaddrspecs = getattr(pargs, self.BD_ADDRS_ATTR_NAME)
        return self.parse_bdaddrspecs(bdaddrspecs)

    def process_bd_addr_arg(self, pargs):
        bdaddrspec = getattr(pargs, self.BD_ADDR_ATTR_NAME)
        return self.parse_bdaddrspec(bdaddrspec)

    def add_node_pos_arg(
        self,
        parser: ArgumentParserExt,
        required: bool = True,
        help: str = "",
    ):
        # The nargs with None value defaults to single argument
        nargs = None if required else "?"
        parser.add_argument(
            "nodespec",
            metavar="<nodespec>",
            nargs=nargs,
            help=f"{help} {app_ui.NODESPEC_HELP}",
        )

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
    def parse_bdaddrspecs(
        self, bdaddrspecs, filter_duplicates: bool = True
    ) -> List[str]:
        return app_ui.parse_bdaddrspecs(
            bdaddrspecs, filter_duplicates=filter_duplicates
        )

    @spec_parse_error_handler
    def parse_bdaddrspec(self, bdaddrspec, filter_duplicates: bool = True) -> str:
        return app_ui.parse_bdaddrspec(bdaddrspec, filter_duplicates=filter_duplicates)

    @spec_parse_error_handler
    def parse_nodespec(
        self, nodespec, node_list: Sequence[Node], filter_duplicates: bool = True
    ) -> List[Node]:
        nodes = app_ui.parse_nodespecs(nodespec, node_list, filter_duplicates)
        if len(nodes) != 1:
            raise BtmeshDfuAppParseSpecError(
                f"The nodespec shall specify one node only. ({nodespec}).",
                spec_name=BtmeshDfuAppSpecName.NODESPEC,
                spec_value=nodespec,
            )
        return nodes[0]

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
