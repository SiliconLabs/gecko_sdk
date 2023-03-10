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

import dataclasses
import logging
import time
from typing import ClassVar

from bgapix.bglibx import BGLibExt

from .conf import Configurator
from .db import BtmeshDatabase
from .dfu import FwUpdateClient
from .dist import FwDistributionClient
from .event import LocalEvent, LocalEventBus
from .mbt import BlobTransferClient
from .prov import Provisioner
from .util import BtmeshRetryParams

logger = logging.getLogger(__name__)


@dataclasses.dataclass
class FactoryResetEvent(LocalEvent):
    name: ClassVar[str] = "btmesh_levt_factory_reset"


class Btmesh:
    def __init__(
        self,
        lib: BGLibExt = None,
        db: BtmeshDatabase = None,
        retry_params_default: BtmeshRetryParams = BtmeshRetryParams(
            retry_max=5,
            retry_interval=1.0,
            retry_cmd_max=10,
            retry_cmd_interval=0.5,
            retry_interval_lpn=30.0,
        ),
    ):
        self._lib = lib
        self._db = db
        self._retry_params_default = retry_params_default
        evtbus = LocalEventBus()
        self.evtbus = evtbus
        self.components = []
        self.prov = Provisioner(lib, db, evtbus)
        self.components.append(self.prov)
        self.conf = Configurator(
            lib,
            db,
            evtbus,
            conf_retry_params_default=retry_params_default,
            silabs_retry_params_default=retry_params_default,
            reset_node_retry_params_default=retry_params_default,
        )
        self.components.append(self.conf)
        self.mbt_clt = BlobTransferClient(
            lib, db, evtbus, self.conf, retry_params_default.to_base()
        )
        self.components.append(self.mbt_clt)
        self.dfu_clt = FwUpdateClient(
            lib, db, evtbus, self.conf, self.mbt_clt, retry_params_default
        )
        self.components.append(self.dfu_clt)
        self.dist_clt = FwDistributionClient(
            lib, db, evtbus, self.conf, self.mbt_clt, self.dfu_clt, retry_params_default
        )
        self.components.append(self.dist_clt)
        self._local_event_handlers = {}

    @property
    def lib(self):
        return self._lib

    @lib.setter
    def lib(self, value):
        self._lib = value
        for component in self.components:
            component.lib = value

    @property
    def db(self):
        return self._db

    @db.setter
    def db(self, value):
        self._db = value
        for component in self.components:
            component.db = value

    @property
    def retry_params_default(self):
        return self._retry_params_default

    def setup(self, lib: BGLibExt, db: BtmeshDatabase):
        self.lib = lib
        self.db = db

    def add_event_filter(self, api_name, class_name, event_name):
        EVT_FILTER_CMD_ADD_ID = b"\x00"
        event_id = self.lib.get_event_id(api_name, class_name, event_name)
        event_id_bytes = event_id.to_bytes(4, byteorder="little")
        evt_filter_cmd_bytes = EVT_FILTER_CMD_ADD_ID + event_id_bytes
        self.lib.bt.user.manage_event_filter(evt_filter_cmd_bytes)

    def remove_event_filter(self, api_name, class_name, event_name):
        EVT_FILTER_CMD_REMOVE_ID = b"\x01"
        event_id = self.lib.get_event_id(api_name, class_name, event_name)
        event_id_bytes = event_id.to_bytes(4, byteorder="little")
        evt_filter_cmd_bytes = EVT_FILTER_CMD_REMOVE_ID + event_id_bytes
        self.lib.bt.user.manage_event_filter(evt_filter_cmd_bytes)

    def reset_event_filter(self):
        EVT_FILTER_CMD_RESET_ID = b"\x02"
        self.lib.bt.user.manage_event_filter(EVT_FILTER_CMD_RESET_ID)

    def add_common_event_filters(self):
        # Filter frequent but non-relevant events to improve performance and
        # improve BG buffer utilization in the BT and BT Mesh stacks
        self.add_event_filter("bt", "scanner", "scan_report")
        self.add_event_filter("bt", "advertiser", "timeout")

    def subscribe(self, event_name: str, handler):
        if not isinstance(event_name, str):
            raise TypeError("The event_name shall be str.")
        if event_name.startswith("btmesh_levt"):
            self.evtbus.subscribe(event_name, handler)
        else:
            self.lib.subscribe(event_name, handler)

    def unsubscribe(self, event_name, handler):
        if not isinstance(event_name, str):
            raise TypeError("The event_name shall be str.")
        if event_name.startswith("btmesh_levt"):
            self.evtbus.unsubscribe(event_name, handler)
        else:
            self.lib.unsubscribe(event_name, handler)

    def emit_local_event(self, event: LocalEvent):
        self.evtbus.emit(event)

    def wait(self, timeout=None, max_events=None, max_time=10):
        self.lib.wait(timeout=timeout, max_events=max_events, max_time=max_time)

    def process_node_ddb(self):
        self.lib.btmesh.prov.ddb_list()

    def process_system_boot_event(self, boot_event):
        # Check Bluetooth stack version
        version = "{major}.{minor}.{patch}".format(**vars(boot_event))
        logger.info("Bluetooth stack booted: v%s-b%s", version, boot_event.build)
        if version != self.lib.bt.__version__:
            logger.warning(
                "BGAPI version mismatch: %s (target) != %s (host)",
                version,
                self.lib.bt.__version__,
            )

    def factory_reset(self, system_reset_delay_s=2.0):
        self.lib.btmesh.node.reset()
        self.lib.bt.nvm.erase_all()
        self.db.clear()
        time.sleep(system_reset_delay_s)
        self.system_reset()
        self.evtbus.emit(FactoryResetEvent())

    def system_reset(self):
        """Issues system reset command and waits for and returns the boot event"""
        self.lib.bt.system.reset(0)
        self.lib.wait_event("bt_evt_system_boot")

    def open(self):
        self.lib.open()
        # Reset event filters on the NCP device to avoid errors when the same
        # event filter is added multiple times and make sure the filters are
        # in a known state
        self.reset_event_filter()
        # It is important to filter frequent and unnecessary event before the
        # NCP device reset to minimize the chance of reset during event transmit
        self.add_common_event_filters()

    # The application or upper layer shall call this function when boot event
    # occurs in order to process the boot_event. The upper layer needs to handle
    # the boot event in order to decide how to stop its current activities when
    # unexpected system reset occurs and to initialize properly its internal state.
    def on_system_boot(self, boot_event):
        self.process_system_boot_event(boot_event)
        self.add_common_event_filters()

    def close(self):
        self.lib.close()
