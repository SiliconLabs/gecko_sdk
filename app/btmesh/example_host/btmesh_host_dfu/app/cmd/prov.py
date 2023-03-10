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

import re
from typing import Optional

from btmesh.errors import BtmeshError

from ..btmesh import app_btmesh
from ..ui import app_ui
from ..util.argparsex import ArgumentParserExt
from .cmd import BtmeshCmd
from .scan import scan_cmd


class BtmeshProvCmd(BtmeshCmd):
    @property
    def parser(self) -> ArgumentParserExt:
        return self.prov_parser

    @property
    def current_parser(self) -> Optional[ArgumentParserExt]:
        return self.current_parser

    def create_parser(self, subparsers) -> ArgumentParserExt:
        self.prov_parser = subparsers.add_parser(
            "prov",
            help="Provision the selected devices. The devices are selected by "
            "uuid or in an interactive provisioning session with scanning.",
            exit_on_error_ext=False,
        )
        self.prov_parser.add_argument(
            "--scan",
            type=float,
            metavar="TIME",
            help="Interactive provisioning which scans for unprovisioned beacons. "
            "The devices can be specified by their index or UUID. "
            "The TIME specifies the scan duration in seconds. (type: %(type)s)",
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
            self.current_parser.error(
                "Positional argument device shall be specified when the --scan "
                "option is not used.",
            )
        uuids = []
        try:
            uuids.extend(self._prov_parse_devices(pargs.device))
        except ValueError as e:
            self.current_parser.error(str(e))
        if pargs.scan:
            beacon_stats = scan_cmd.scan(max_time=pargs.scan, show_beacons=True)
            scan_cmd.scan_show_stats(beacon_stats)
            if not len(beacon_stats):
                # No unprovisioned beacons are found so provisioning is ended
                return False
            app_ui.info("Select devices to provision")
            app_ui.info("Comma/Space separated list of indexes, BT addresses or UUIDs")
            devices_input = app_ui.input("Devices:")
            try:
                uuids.extend(self._prov_parse_devices(devices_input, beacon_stats))
            except ValueError as e:
                app_ui.parser_error(self.parser, str(e))
                return False
        self._provision(uuids)
        return False

    def _prov_parse_devices(self, devices, beacon_stats=None):
        uuids = []
        if isinstance(devices, str):
            device_list = app_ui.split_text(devices)
        else:
            device_list = devices
        for device in device_list:
            device = device.strip()
            if re.fullmatch(r"[0-9a-fA-F]{32}", device):
                uuid = bytes.fromhex(device)
            elif beacon_stats and re.fullmatch(r"(?:[0-9a-fA-F]{2}\:?){6}", device):
                addr_uuid_map = {b["address"]: b["uuid"] for b in beacon_stats}
                if device not in addr_uuid_map:
                    raise ValueError(
                        f"BT Mesh device UUID could not be determined "
                        f"from {device} BT address."
                    )
                uuid = addr_uuid_map[device]
            elif beacon_stats and re.fullmatch(r"\d+", device):
                idx_uuid_map = {
                    f"{idx}": b["uuid"] for idx, b in enumerate(beacon_stats)
                }
                if device not in idx_uuid_map:
                    raise ValueError(
                        f"BT Mesh device UUID could not be determined "
                        f"from {device} index."
                    )
                uuid = idx_uuid_map[device]
            else:
                raise ValueError(
                    f"BT Mesh device UUID could not be determined from {device}."
                )
            uuids.append(uuid)
        # Remove duplicate entries from the list
        # Note: Dictionaries are ordered from Python 3.7 and the required python
        #       version is 3.7 as well so the dict can be considered ordered
        return list(dict.fromkeys(uuids))

    def _provision(self, uuids):
        if not isinstance(uuids, (list, tuple)):
            uuids = [uuids]
        for uuid in uuids:
            try:
                app_btmesh.prov.provision_adv_device(uuid)
                app_ui.info(f"The device with {uuid.hex()} UUID is provisioned.")
            except BtmeshError as e:
                app_ui.error(e.message)


prov_cmd = BtmeshProvCmd()
