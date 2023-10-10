"""
ESL Tag Database.
"""

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

import esl_lib
import esl_tag
from ap_constants import BROADCAST_ADDRESS

class TagDB:
    """ ESL tag database """
    def __init__(self):
        self.tags: list[esl_tag.Tag] = []

    def add(self, lib:esl_lib.Lib, address: esl_lib.Address, dummy=False):
        tag = self.find(address)
        if tag is None:
            tag = esl_tag.Tag(lib, address, dummy=dummy)
            self.tags.append(tag)
        return tag

    def remove(self, tag:esl_tag.Tag=None, address: esl_lib.Address=None):
        if address is not None:
            tag = self.find(address)
        if tag is not None:
            self.tags.remove(tag)

    def find(self, node_id):
        value = node_id
        if isinstance(node_id, (esl_lib.Address, str)):
            attr = 'ble_address'
        elif isinstance(node_id, esl_lib.ConnectionHandle):
            attr = 'connection_handle'
        elif isinstance(node_id, (tuple, list)):
            esl_id, group_id = node_id
            if esl_id == BROADCAST_ADDRESS:
                # Invalid ESL ID
                return None
            value = esl_id | (group_id << 8)
            attr = 'esl_address'
        else:
            return None # Unknown node ID type
        for tag in self.tags:
            if getattr(tag, attr) == value:
                return tag
        return None # Tag not found

    def all(self):
        return self.tags

    def list_group(self, group_id):
        return [tag for tag in self.tags if tag.group_id == group_id ]

    def list_state(self, state):
        if not isinstance(state, (list, tuple)):
            state = [state]
        return [tag for tag in self.tags if tag.state in state]

    def list_esl_state(self, esl_state):
        if not isinstance(esl_state, (list, tuple)):
            esl_state = [esl_state]
        return [tag for tag in self.tags if tag.esl_state in esl_state]

    def list_advertising(self):
        return [tag for tag in self.tags if tag.advertising]

    def list_blocked(self):
        return [tag for tag in self.tags if tag.blocked]
