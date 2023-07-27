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

import enum
import re
from typing import Dict, Iterator, List, Optional, Union

import btmesh.util
from btmesh.db import GapAddrType, GapPhy, Node
from btmesh.errors import BtmeshError
from btmesh.prov import (UnprovDeviceBeacon, UnprovDeviceBeaconAddrType,
                         UnprovDeviceBeaconBearer)
from btmesh.util import ConnectionParamsRange

from ..btmesh import app_btmesh
from ..cfg import app_cfg
from ..ui import app_ui
from ..util.argparsex import ArgumentParserExt
from .cmd import BtmeshCmd
from .scan import scan_cmd


class PBArg(enum.Enum):
    ADV = "adv"
    GATT = "gatt"
    AUTO = "auto"


class BtmeshProvCmd(BtmeshCmd):
    @property
    def parser(self) -> ArgumentParserExt:
        return self.prov_parser

    @property
    def current_parser(self) -> Optional[ArgumentParserExt]:
        return self.parser

    def create_parser(self, subparsers) -> ArgumentParserExt:
        self.prov_parser = subparsers.add_parser(
            "prov",
            help="Provision the selected devices.",
            description=(
                "Provision the selected devices. The devices can be selected "
                "directly by UUID in case of ADV provisioning and by UUID and "
                "BLE address in case of GATT provisioning. "
                "The devices can be selected in an interactive provisioning "
                "session with scanning as well. "
                "If PB-GATT bearer is selected then the default connection "
                "parameter values are used from the proxy section of the "
                "application configuration."
            ),
            exit_on_error_ext=False,
        )
        self.prov_parser.add_argument(
            "--bearer",
            "-b",
            choices=[PBArg.ADV.value, PBArg.GATT.value, PBArg.AUTO.value],
            default=PBArg.AUTO.value,
            help=(
                f"Selects the bearer (PB-ADV or PB-GATT) to be used during "
                f"provisioning. "
                f"If {PBArg.AUTO.value} is selected then the command tries to "
                f"guess the provisioning bearer based on the passed options. "
                f"If {self.BD_ADDRS_OPT_LONG} option is used with the "
                f"{PBArg.AUTO.value} bearer then it defaults PB-GATT in "
                f"non-interactive provisioning. "
                f"If an unprovisioned device beacon with PB-GATT bearer is "
                f"selected with {PBArg.AUTO.value} bearer during interactive "
                f"provisioning (with scanning) then PB-GATT is used. "
                f"In every other cases the {PBArg.AUTO.value} bearer defaults "
                f"to PB-ADV. And therefore PB-ADV is selected by the "
                f"{PBArg.AUTO.value} bearer feature when an unprovisioned device "
                f"beacon is specified by UUID or BLE address or a beacon with "
                f"PB-ADV bearer is selected during interactive provisioning. "
                f"The PB-ADV bearer is selected by {PBArg.AUTO.value} bearer as "
                f"well when the devices to be provisioned are specified by UUID "
                f"only without the {self.BD_ADDRS_OPT_LONG} option during "
                f"non-interactive provisioning. "
                f"If bearer option is set to {PBArg.ADV.value} or "
                f"{PBArg.GATT.value} value and there are contradicting "
                f"parameters then an error is reported. "
                "(default: %(default)s)"
            ),
        )
        self.prov_parser.add_argument(
            "--bd-addr-type",
            "-t",
            choices=["public", "random"],
            default="public",
            help=(
                f"Specifies the BLE address type of bluetooth addresses "
                f"in {self.BD_ADDRS_OPT_LONG} option. "
                "(default: %(default)s)"
            ),
        )
        self.prov_parser.add_argument(
            "--scan",
            "-s",
            type=float,
            metavar="TIME",
            help="Interactive provisioning which scans for unprovisioned beacons. "
            "The devices can be specified by their index or UUID or BLE address. "
            "The TIME specifies the scan duration in seconds. (type: %(type)s)",
        )
        self.add_bd_addrs_arg(
            self.prov_parser,
            help=(
                "List of BLE addresses. It shall be present when the devices "
                "are provisioned over PB-GATT. "
                "The order of matching BLE addresses and UUIDs shall be same. "
                "No BLE address shall be added when --scan option is used."
            ),
        )
        self.add_connection_open_timeout_arg(
            self.prov_parser,
            app_cfg.proxy.conn_open_timeout_ms_default,
        )
        self.add_connection_params_range_args(
            self.prov_parser,
            min_interval_ms_default=app_cfg.proxy.conn_min_interval_ms_default,
            max_interval_ms_default=app_cfg.proxy.conn_max_interval_ms_default,
            latency_default=app_cfg.proxy.conn_latency_default,
            timeout_ms_default=app_cfg.proxy.conn_timeout_ms_default,
            min_ce_length_ms_default=app_cfg.proxy.conn_min_ce_length_ms_default,
            max_ce_length_ms_default=app_cfg.proxy.conn_max_ce_length_ms_default,
        )
        self.prov_parser.add_argument(
            "device",
            nargs="*",
            default=[],
            help="List of device UUIDs. "
            "No devices shall be added when --scan option is used.",
        )
        return self.prov_parser

    def __call__(self, arg) -> bool:
        pargs = self.parser.parse_args(arg.split())
        if (not pargs.device) and (not pargs.scan):
            # Parser error raises an exception
            self.current_parser.error(
                "Positional argument device shall be specified when the --scan "
                "option is not used.",
            )
        if pargs.device and pargs.scan:
            # Parser error raises an exception
            self.current_parser.error(
                f"argument --scan: not allowed with positional argument device."
            )
        if pargs.scan:
            return self._prov_interactive(pargs)
        else:
            return self._prov_target_devices(pargs)

    def _prov_target_devices(self, pargs) -> bool:
        bearer = PBArg(pargs.bearer)
        uuids: List[bytes] = []
        bd_addrs: Optional[List[str]] = []
        conn_open_timeout = self.process_connection_open_timeout(pargs)
        conn_params_range = self.process_connection_params_range(
            pargs, app_cfg.proxy.conn_params_range
        )
        if pargs.bd_addr_type == "public":
            bd_addr_type = GapAddrType.PUBLIC_ADDRESS
        else:
            bd_addr_type = GapAddrType.STATIC_ADDRESS
        uuidspecs = pargs.device
        if isinstance(uuidspecs, str):
            uuidspecs = app_ui.split_text(uuidspecs)
        for uuidspec in uuidspecs:
            uuidspec = uuidspec.strip()
            if re.fullmatch(btmesh.util.UUID_PATTERN, uuidspec):
                uuid = bytes.fromhex(uuidspec)
                uuids.append(uuid)
            else:
                # Parser error raises an exception
                self.parser.error(
                    f"The {uuidspec} device positional argument is not "
                    f"a valid UUID."
                )
        if pargs.bd_addrs:
            bd_addrs = self.process_bd_addrs_arg(pargs)
        else:
            bd_addrs = None
        if bearer == PBArg.ADV and bd_addrs:
            # Parser error raises an exception
            self.parser.error(
                f"argument {self.BD_ADDRS_OPT_LONG}: not allowed with argument "
                f"--bearer {PBArg.ADV.value}."
            )
        if bearer == PBArg.GATT and not bd_addrs:
            # Parser error raises an exception
            self.parser.error(
                f"argument {self.BD_ADDRS_OPT_LONG}: mandatory when "
                f"argument --bearer {PBArg.GATT.value} is present."
            )
        if bd_addrs:
            self._provision_gatt(
                uuids=uuids,
                bd_addrs=bd_addrs,
                bd_addrs_type=bd_addr_type,
                ini_phy=GapPhy.LE_1M,
                conn_open_timeout_ms=conn_open_timeout,
                conn_params_range=conn_params_range,
            )
        else:
            self._provision_adv(uuids)
        return False

    def _prov_interactive(self, pargs) -> bool:
        bearer = PBArg(pargs.bearer)
        scan_time: float = pargs.scan
        conn_open_timeout = self.process_connection_open_timeout(pargs)
        conn_params_range = self.process_connection_params_range(
            pargs, app_cfg.proxy.conn_params_range
        )
        if pargs.bd_addrs:
            # Parser error raises an exception
            self.current_parser.error(
                f"argument {self.BD_ADDRS_OPT_LONG}: not allowed with argument --scan."
            )
        beacon_stats = scan_cmd.scan(max_time=scan_time, show_beacons=True)
        if bearer == PBArg.AUTO:
            filtered_beacon_stats = beacon_stats
        else:
            if bearer == PBArg.GATT:
                expected_bearer = UnprovDeviceBeaconBearer.PB_GATT
            else:
                expected_bearer = UnprovDeviceBeaconBearer.PB_ADV
            filtered_beacon_stats = [
                b for b in beacon_stats if b.bearer == expected_bearer
            ]
        scan_cmd.scan_show_stats(filtered_beacon_stats)
        if not len(filtered_beacon_stats):
            # No unprovisioned beacons are found so provisioning is ended
            return False
        app_ui.info("Select devices to provision")
        app_ui.info("Comma/Space separated list of indexes, BT addresses or UUIDs")
        devicespecs = app_ui.input("Devices:")
        try:
            selected_beacon_stats = self._select_unprov_device_beacons(
                devicespecs, bearer, filtered_beacon_stats
            )
            for beacon in selected_beacon_stats:
                if beacon.bearer == UnprovDeviceBeaconBearer.PB_GATT:
                    if beacon.bd_addr_type == UnprovDeviceBeaconAddrType.PUBLIC:
                        bd_addr_type = GapAddrType.PUBLIC_ADDRESS
                    else:
                        bd_addr_type = GapAddrType.STATIC_ADDRESS
                    self._provision_gatt(
                        uuids=beacon.uuid,
                        bd_addrs=beacon.bd_addr,
                        bd_addrs_type=bd_addr_type,
                        ini_phy=GapPhy.LE_1M,
                        conn_open_timeout_ms=conn_open_timeout,
                        conn_params_range=conn_params_range,
                    )
                else:
                    self._provision_adv(beacon.uuid)
            return False
        except ValueError as e:
            app_ui.parser_error(self.parser, str(e))
            return False

    def _select_unprov_device_beacons(
        self,
        devicespecs: Union[str, List[str]],
        bearer: PBArg,
        beacons: List[UnprovDeviceBeacon],
    ) -> List[UnprovDeviceBeacon]:
        uuid_beacon_dict: Dict[bytes, UnprovDeviceBeacon] = {}
        if isinstance(devicespecs, str):
            devicespecs = app_ui.split_text(devicespecs)
        if bearer == PBArg.AUTO:
            bearer_err_text = ""
        else:
            if bearer == PBArg.GATT:
                bearer_err_text = " with PB-GATT bearer"
            else:
                bearer_err_text = " with PB-ADV bearer"
        for devicespec in devicespecs:
            devicespec = devicespec.strip()
            if re.fullmatch(btmesh.util.UUID_PATTERN, devicespec):
                uuid = bytes.fromhex(devicespec)
                beacon_list = [b for b in beacons if b.uuid == uuid]
                beacon = self._select_unprov_device_beacon_by_bearer(
                    bearer, beacon_list
                )
                if beacon:
                    uuid_beacon_dict[uuid] = beacon
                else:
                    raise ValueError(
                        f"The {uuid.hex()} UUID doesn't match any unprovisioned "
                        f"device beacons{bearer_err_text}."
                    )
            elif re.fullmatch(btmesh.util.BDADDR_PATTERN, devicespec):
                bd_addr = devicespec
                beacon_list = [b for b in beacons if bd_addr == b.bd_addr]
                beacon = self._select_unprov_device_beacon_by_bearer(
                    bearer, beacon_list
                )
                if beacon:
                    uuid_beacon_dict[beacon.uuid] = beacon
                else:
                    raise ValueError(
                        f"The {bd_addr} BLE address doesn't match any  "
                        f"unprovisioned device beacons{bearer_err_text}."
                    )
            elif re.fullmatch(r"\d+", devicespec):
                idx = int(devicespec)
                if 0 <= idx < len(beacons):
                    beacon = beacons[idx]
                    uuid_beacon_dict[beacon.uuid] = beacon
                else:
                    raise ValueError(
                        f"The {idx} index doesn't match any  "
                        f"unprovisioned device beacons{bearer_err_text}."
                    )
            else:
                raise ValueError(f"Invalid devicespec ({devicespec}).")
        return list(uuid_beacon_dict.values())

    def _select_unprov_device_beacon_by_bearer(
        self, bearer: PBArg, beacons: List[UnprovDeviceBeacon]
    ):
        if 1 < len(beacons):
            uuid = beacons[0].uuid
            for b in beacons[1:]:
                if b.uuid != uuid:
                    raise ValueError(
                        "Unprov device beacon selection by bearer shall run "
                        "over a list of beacons with same UUID."
                    )
        if bearer == PBArg.ADV:
            expected_bearer = UnprovDeviceBeaconBearer.PB_ADV
            beacon = next((b for b in beacons if b.bearer == expected_bearer), None)
        elif bearer == PBArg.GATT:
            expected_bearer = UnprovDeviceBeaconBearer.PB_GATT
            beacon = next((b for b in beacons if b.bearer == expected_bearer), None)
        else:
            expected_bearer = UnprovDeviceBeaconBearer.PB_ADV
            beacon = next((b for b in beacons if b.bearer == expected_bearer), None)
            if beacon is None:
                expected_bearer = UnprovDeviceBeaconBearer.PB_GATT
                beacon = next((b for b in beacons if b.bearer == expected_bearer), None)
        return beacon

    def _provision_adv(self, uuids: Union[Iterator[bytes], bytes]) -> None:
        if isinstance(uuids, bytes):
            uuids = [uuids]
        for uuid in uuids:
            try:
                node = app_btmesh.prov.provision_adv_device(uuid)
                app_ui.info(f"The device with {uuid.hex()} UUID is provisioned.")
                self._on_node_provisioned(node)
            except BtmeshError as e:
                app_ui.error(e.message)

    def _provision_gatt(
        self,
        uuids: Union[Iterator[bytes], bytes],
        bd_addrs: Union[Iterator[str], str],
        bd_addrs_type: GapAddrType,
        ini_phy: GapPhy = GapPhy.LE_1M,
        conn_open_timeout_ms: float = 5_000.0,
        conn_params_range: Optional[ConnectionParamsRange] = None,
    ) -> None:
        if isinstance(uuids, bytes):
            uuids = [uuids]
        if isinstance(bd_addrs, str):
            bd_addrs = [bd_addrs]
        if len(uuids) != len(bd_addrs):
            self.parser.error(
                f"The number of UUIDs ({len(uuids)}) and BLE addresses "
                f"({len(bd_addrs)}) doesn't match."
            )
        for uuid, bd_addr in zip(uuids, bd_addrs):
            try:
                node = app_btmesh.prov.provision_gatt_device(
                    uuid=uuid,
                    bd_addr=bd_addr,
                    bd_addr_type=bd_addrs_type,
                    ini_phy=ini_phy,
                    conn_open_timeout_ms=conn_open_timeout_ms,
                    conn_params_range=conn_params_range,
                )
                app_ui.info(f"The device with {uuid.hex()} UUID is provisioned.")
                self._on_node_provisioned(node)
            except BtmeshError as e:
                app_ui.error(e.message)

    def _on_node_provisioned(self, node: Node) -> None:
        # The app_cfg.common.btmesh_retry_params_default returns a new instance
        # so it can be modified without modifying the configuration values.
        retry_params = app_cfg.common.btmesh_retry_params_default
        retry_params.retry_max = app_cfg.conf.conf_retry_max_default
        retry_params.retry_interval = app_cfg.conf.conf_retry_interval_default
        retry_params.retry_interval_lpn = app_cfg.conf.conf_retry_interval_lpn_default
        # Node DCD auto query
        if app_cfg.conf.auto_conf_dcd_query:
            app_btmesh.conf.get_dcd(node, update_db=True, retry_params=retry_params)
            app_ui.info(
                f"Node ({node.uuid.hex()}) auto configuration: DCD is queried"
            )
        # Node Default TTL auto configuration
        if app_cfg.conf.auto_conf_default_ttl:
            ttl = app_cfg.conf.default_ttl_default
            try:
                app_btmesh.conf.set_default_ttl(
                    node, ttl=ttl, retry_params=retry_params
                )
                app_ui.info(
                    f"Node ({node.uuid.hex()}) auto configuration: "
                    f"Default TTL = {ttl}"
                )
            except BtmeshError as e:
                app_ui.error(str(e))
        # Node Network Transmit composite state auto configuration
        if app_cfg.conf.auto_conf_network_tx:
            nettx_cnt = app_cfg.conf.network_tx_count_default
            nettx_int = app_cfg.conf.network_tx_interval_ms_default
            try:
                app_btmesh.conf.set_network_transmit(
                    node,
                    transmit_count=nettx_cnt,
                    transmit_interval_ms=nettx_int,
                    retry_params=retry_params,
                )
                app_ui.info(
                    f"Node ({node.uuid.hex()}) auto configuration: "
                    f"Network Transmit Count = {nettx_cnt}"
                )
                app_ui.info(
                    f"Node ({node.uuid.hex()}) auto configuration: "
                    f"Network Transmit Interval = {nettx_int} ms"
                )
            except BtmeshError as e:
                app_ui.error(str(e))


prov_cmd = BtmeshProvCmd()
