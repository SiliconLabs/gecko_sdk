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

import logging
from typing import List, Optional

from bgapix.bglibx import BGLibExt

from .conf import Configurator
from .core import BtmeshComponent, BtmeshCore, DCDIf
from .db import DCD, BtmeshDatabase, Node
from .dfu import FwUpdateClient
from .dist import FwDistributionClient
from .event import LocalEventBus
from .mbt import BlobTransferClient
from .prov import Provisioner
from .proxy import Proxy
from .util import BtmeshMulticastRetryParams, BtmeshRetryParams

logger = logging.getLogger(__name__)


class Btmesh:
    def __init__(
        self,
        lib: BGLibExt = None,
        db: BtmeshDatabase = None,
        retry_params_default: BtmeshMulticastRetryParams = BtmeshMulticastRetryParams(
            retry_max=5,
            retry_interval=1.0,
            retry_cmd_max=10,
            retry_cmd_interval=0.5,
            retry_interval_lpn=30.0,
            multicast_threshold=2,
            auto_unicast=False,
        ),
    ):
        evtbus = LocalEventBus()
        self.core = BtmeshCore(lib, db, evtbus)
        self._retry_params_default = retry_params_default
        self.components: List[BtmeshComponent] = []

        # Proxy component
        self.proxy = Proxy(self.core)
        self.components.append(self.proxy)

        # Provisioner component
        self.prov = Provisioner(self.core, proxy=self.proxy)
        self.components.append(self.prov)

        # Configurator component
        self.conf = Configurator(
            self.core,
            conf_retry_params_default=retry_params_default.to_btmesh(),
            silabs_retry_params_default=retry_params_default,
            reset_node_retry_params_default=retry_params_default.to_btmesh(),
        )
        self.components.append(self.conf)

        # BLOB Transfer Client component
        self.mbt_clt = BlobTransferClient(
            self.core,
            conf=self.conf,
            retry_params_default=retry_params_default.to_base(),
        )

        # Firmware Update Client component
        self.components.append(self.mbt_clt)
        self.dfu_clt = FwUpdateClient(
            self.core,
            conf=self.conf,
            mbt_clt=self.mbt_clt,
            retry_params_default=retry_params_default,
        )
        self.components.append(self.dfu_clt)

        # Firmware Distribution Client component
        self.dist_clt = FwDistributionClient(
            self.core,
            conf=self.conf,
            mbt_clt=self.mbt_clt,
            dfu_clt=self.dfu_clt,
            retry_params_default=retry_params_default,
        )
        self.components.append(self.dist_clt)

        dcdif = DCDIf(self._get_dcd)
        self.core.dcdif = dcdif

    def _get_dcd(self, node: Node) -> DCD:
        return self.conf.get_dcd_cached(
            node, retry_params=self.conf.conf_retry_params_default
        )

    @property
    def lib(self) -> Optional[BGLibExt]:
        if self.core is None:
            return None
        else:
            return self.core.lib

    @property
    def db(self) -> Optional[BtmeshDatabase]:
        if self.core is None:
            return None
        else:
            return self.core.db

    @property
    def evtbus(self) -> Optional[LocalEventBus]:
        if self.core is None:
            return None
        else:
            return self.core.evtbus

    @property
    def retry_params_default(self) -> BtmeshRetryParams:
        return self._retry_params_default

    def setup(self, lib: BGLibExt, db: BtmeshDatabase):
        evtbus = LocalEventBus()
        dcdif = DCDIf(self._get_dcd)
        self.core = BtmeshCore(lib, db, evtbus)
        self.core.db.set_event_emitter(self.core.emit_local_event)
        self.core.dcdif = dcdif
        for component in self.components:
            component.core = self.core
