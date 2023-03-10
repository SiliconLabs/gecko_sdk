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

from typing import Optional

import btmesh.util

from ..btmesh import app_btmesh
from ..cfg import app_cfg
from ..ui import app_ui
from ..util.argparsex import ArgumentParserExt
from .cmd import BtmeshCmd


class BtmeshScanCmd(BtmeshCmd):
    @property
    def parser(self) -> ArgumentParserExt:
        return self.scan_parser

    @property
    def current_parser(self) -> Optional[ArgumentParserExt]:
        return self.current_parser

    def create_parser(self, subparsers) -> ArgumentParserExt:
        self.scan_parser = subparsers.add_parser(
            "scan",
            prog="scan",
            description="Scan for unprovisioned device beacons.",
            exit_on_error_ext=False,
        )
        self.scan_parser.add_argument(
            "--time",
            type=float,
            default=2.0,
            help="Scan duration in seconds (type: %(type)s, default: %(default)s).",
        )
        return self.scan_parser

    def __call__(self, arg) -> bool:
        pargs = self.parser.parse_args(arg.split())
        beacon_stats = self.scan(max_time=pargs.time, show_beacons=True)
        self.scan_show_stats(beacon_stats)
        return False

    def scan(self, show_beacons=False, max_time=2.0):
        # Parse the string arguments into pargs variable (parsed args)
        app_ui.info("Scanning for unprovisioned nodes...")
        beacon_stats = set()
        for beacon in app_btmesh.prov.scan_unprov_beacons_gen(max_time):
            beacon_static_data = (
                beacon.uuid,
                beacon.bearer,
                beacon.address,
                beacon.address_type,
            )
            beacon_stats.add(beacon_static_data)
            if show_beacons:
                ui_beacon_list = [
                    "uuid=" + beacon.uuid.hex(),
                    "bearer=" + btmesh.util.unprov_beacon_bearer_str(beacon.bearer),
                    "address=" + beacon.address,
                    "address_type=" + btmesh.util.bd_addr_type_str(beacon.address_type),
                    "rssi=" + str(beacon.rssi),
                ]
                app_ui.info("Unprovisioned beacon: " + " ".join(ui_beacon_list))
        stats = [
            {
                "uuid": b[0],
                "bearer": b[1],
                "address": b[2],
                "address_type": b[3],
            }
            for b in beacon_stats
        ]
        stats = sorted(stats, key=lambda bs_elem: bs_elem["uuid"])
        return stats

    def scan_show_stats(self, beacon_stats):
        beacon_stat_list = [
            {
                "idx": str(idx),
                "uuid": bs["uuid"].hex(),
                "bearer": btmesh.util.unprov_beacon_bearer_str(bs["bearer"]),
                "address": bs["address"],
                "address_type": btmesh.util.bd_addr_type_str(bs["address_type"]),
            }
            for idx, bs in enumerate(beacon_stats)
        ]
        if not len(beacon_stat_list):
            app_ui.info("No unprovisioned beacons are found.")
        else:
            app_ui.table_info(
                beacon_stat_list,
                columns={
                    "idx": "Idx",
                    "uuid": "UUID",
                    "bearer": "Bearer",
                    "address": "Address",
                    "address_type": "Address Type",
                },
            )

scan_cmd = BtmeshScanCmd()