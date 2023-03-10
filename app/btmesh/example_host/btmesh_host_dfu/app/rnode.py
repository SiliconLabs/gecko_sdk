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

from btmesh.core import Btmesh
from btmesh.db import DCD, Node
from btmesh.util import BtmeshRetryParams

from .cfg import app_cfg


class RemoteNode:
    def __init__(
        self, btmesh: Btmesh, node: Node, retry_params: BtmeshRetryParams = None
    ):
        self.btmesh = btmesh
        self._node = node
        if retry_params:
            self.retry_params = retry_params
        else:
            self.retry_params = app_cfg.common.btmesh_retry_params_default

    @property
    def node(self) -> Node:
        return self._node

    def __getattr__(self, name):
        # Python calls the __getattr__ special method if it can't find the
        # attribute name in the object.
        # The RemoteNode class is a wrapper which adds dynamic behavior to the
        # Node class which is a pure data class. The getattr calls are forwarded
        # to the Node class which is quite useful because it is not necessary to
        # wrap each property and functions of the Node class only those which
        # are different.
        return getattr(self.node, name)

    @property
    def dcd(self) -> DCD:
        if self._node.dcd is None:
            # The get_dcd function updates the Node object in the database with
            # the DCD information
            self.btmesh.conf.get_dcd(
                self._node, update_db=True, retry_params=self.retry_params
            )
        return self._node.dcd
