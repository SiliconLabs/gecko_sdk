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


@enum.unique
class BtmeshErrorCode(enum.IntEnum):
    PROV_INIT_FAILED = enum.auto()
    PROVISIONING_FAILED = enum.auto()
    CONFIG_FAILED = enum.auto()
    CONFIG_RESET_PROV_FORBIDDEN = enum.auto()
    INVALID_DCD = enum.auto()
    MBT_TRANSFER_MODE_INVALID = enum.auto()
    MBT_TRANSFER_FAILED = enum.auto()
    DIST_SVR_ADDR_DOES_NOT_EXIST = enum.auto()
    DIST_SVR_MDL_DOES_NOT_EXIST = enum.auto()
    DIST_CLT_GET_FW_FAILED = enum.auto()
    DIST_CLT_GET_FW_BY_IDX_FAILED = enum.auto()
    DIST_CLT_UPLOAD_START_FAILED = enum.auto()
    DIST_CLT_UPLOAD_FAILED = enum.auto()
    DIST_CLT_UPLOAD_FWID_EXISTS = enum.auto()
    DIST_CLT_UPLOAD_CANCEL_FAILED = enum.auto()
    DIST_CLT_DELETE_FW_FAILED = enum.auto()
    DIST_CLT_DELETE_ALL_FW_FAILED = enum.auto()
    DIST_CLT_DELETE_RECEIVERS_FAILED = enum.auto()
    DIST_CLT_ADD_RECEIVERS_FAILED = enum.auto()
    DIST_CLT_START_DIST_FAILED = enum.auto()
    DIST_CLT_GET_DIST_FAILED = enum.auto()
    DIST_CLT_CANCEL_DIST_FAILED = enum.auto()
    DFU_CLT_ADD_RECEIVER_FAILED = enum.auto()
    DFU_CLT_CANCEL_DIST_FAILED = enum.auto()
    PROXY_CONNECT_SCAN_FAILED = enum.auto()
    PROXY_CONNECT_TIMEOUT = enum.auto()
    PROXY_NODE_CONN_DOES_NOT_EXIST = enum.auto()
    PROXY_NODE_CONN_ALREADY_EXISTS = enum.auto()
    BT_CONN_DOES_NOT_EXIST = enum.auto()


class BtmeshException(Exception):
    """Base Exception class of BT Mesh exceptions"""

class BtmeshError(BtmeshException):
    def __init__(self, err, message, *args, event=None, **kwargs):
        self.err = err
        self.message = message
        self.event = event
        self.params = kwargs
        super().__init__(message, *args)