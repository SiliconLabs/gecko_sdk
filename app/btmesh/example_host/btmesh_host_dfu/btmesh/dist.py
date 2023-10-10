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

import copy
import dataclasses
import enum
import logging
import os
import struct
from typing import Callable, ClassVar, Iterable, List, Optional, Tuple

from bgapix.bglibx import BGLibExtRetryParams
from bgapix.slstatus import SlStatus

from . import util
from .conf import Configurator
from .core import BtmeshComponent, BtmeshCore
from .db import ModelID
from .dfu import (FWID, FwReceiver, FwReceiverInfo, FwReceiverPhase,
                  FwUpdateAdditionalInfo, FwUpdateClient, FwUpdateStatus)
from .errors import BtmeshError, BtmeshErrorCode
from .event import LocalEvent
from .mbt import (Blob, BlobTransferClient, BlobTransferMode, MBTProgressEvent,
                  MBTStatus)
from .mdl import NamedModelID
from .util import BtmeshMulticastRetryParams, BtmeshRetryParams

logger = logging.getLogger(__name__)


@enum.unique
class FwDistStatus(util.BtmeshIntEnum):
    SUCCESS = 0x00
    OUT_OF_RESOURCES = 0x01
    WRONG_PHASE = 0x02
    INTERNAL_ERROR = 0x03
    FWID_NOT_FOUND = 0x04
    INVALID_APPKEY_INDEX = 0x05
    RECEIVERS_LIST_EMPTY = 0x06
    BUSY_WITH_DISTRIBUTION = 0x07
    BUSY_WITH_UPLOAD = 0x08
    URI_NOT_SUPPORTED = 0x09
    URI_MALFORMED = 0x0A
    URI_UNREACHABLE = 0x0B
    NEW_FW_NOT_AVAILABLE = 0x0C
    SUSPEND_FAILED = 0x0D
    TIMEOUT = 0xFF
    UNKNOWN_VALUE = util.ENUM_UNKNOWN_VALUE


@enum.unique
class FwDistUploadPhase(util.BtmeshIntEnum):
    IDLE = 0x00
    TRANSFER_ACTIVE = 0x01
    TRANSFER_ERROR = 0x02
    TRANSFER_SUCCESS = 0x03
    UNKNOWN_VALUE = util.ENUM_UNKNOWN_VALUE


@enum.unique
class FwDistUploadType(util.BtmeshIntEnum):
    IN_BAND = 0x00
    OUT_OF_BAND = 0x01
    UNKNOWN_VALUE = util.ENUM_UNKNOWN_VALUE


@enum.unique
class FwDistOOB(util.BtmeshIntEnum):
    NOT_SUPPORTED = 0
    SUPPORTED = 1
    UNKNOWN_VALUE = util.ENUM_UNKNOWN_VALUE


@enum.unique
class FwUpdatePolicy(util.BtmeshIntEnum):
    VERIFY_ONLY = 0
    VERIFY_AND_APPLY = 1
    UNKNOWN_VALUE = util.ENUM_UNKNOWN_VALUE


@enum.unique
class FwDistPhase(util.BtmeshIntEnum):
    IDLE = 0
    TRANSFER_ACTIVE = 1
    TRANSFER_SUCCESS = 2
    APPLYING_UPDATE = 3
    COMPLETED = 4
    FAILED = 5
    CANCELING_UPDATE = 6
    TRANSFER_SUSPENDED = 7
    UNKNOWN_VALUE = util.ENUM_UNKNOWN_VALUE


@dataclasses.dataclass
class FwDistFwStatus:
    FW_IMG_DOES_NOT_EXIST: ClassVar[int] = 0xFFFF
    status: FwDistStatus
    num_entries: int
    index: int
    fwid: Optional[FWID]


@dataclasses.dataclass
class FwDistCapabilities:
    max_nodes_list_size: int
    max_fw_list_size: int
    max_fw_size: int
    max_upload_space: int
    remaining_upload_space: int
    oob_supported: FwDistOOB
    uri_scheme_names: bytes


@dataclasses.dataclass
class FwDistDistributionStatus:
    status: FwDistStatus
    phase: FwDistPhase
    group_addr: int
    appkey_index: int
    ttl: int
    timeout_base: int
    transfer_mode: BlobTransferMode
    update_policy: FwUpdatePolicy
    fw_list_index: int


@dataclasses.dataclass
class FwDistUploadProgressEvent(LocalEvent):
    name: ClassVar[str] = "btmesh_levt_dist_upload_progress"
    elem_index: int
    done_bytes: int
    fw_size: int


@dataclasses.dataclass
class FwDistDistributionProgressEvent(LocalEvent):
    name: ClassVar[str] = "btmesh_levt_dist_distribution_progress"
    elem_index: int
    dist_status: FwDistDistributionStatus
    receivers_info: Iterable[FwReceiverInfo]


class FwDistributionClient(BtmeshComponent):
    # The invalid state error code means unrecoverable error most of the time.
    # There is an important exception for segmented transfer.
    # The transport layer rejects to send two segmented message to the same
    # destination address simultaneously in accordance with the specification
    # and it returns invalid state error code in this specific case.
    RETRY_CMD_ERR_CODES = (SlStatus.NO_MORE_RESOURCE, SlStatus.INVALID_STATE)
    UNUSED_VIRTUAL_ADDRESS = b"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"

    @staticmethod
    def calc_retry_max(retry_interval: float, timeout_base: int, ttl: int) -> float:
        timeout = util.dfu_calc_client_timeout(timeout_base, ttl)
        # Multiplication by 1.2 is used to be on the safe side
        return round((1.2 * timeout) / retry_interval)

    @staticmethod
    def calc_retry_cmd_max(
        retry_cmd_interval: float, timeout_base: int, ttl: int
    ) -> float:
        timeout = util.dfu_calc_client_timeout(timeout_base, ttl)
        # Multiplication by 1.2 is used to be on the safe side
        return round((1.2 * timeout) / retry_cmd_interval)

    def __init__(
        self,
        core: BtmeshCore,
        conf: Configurator,
        mbt_clt: BlobTransferClient,
        dfu_clt: FwUpdateClient,
        retry_params_default: BtmeshMulticastRetryParams,
    ):
        super().__init__(core)
        self.conf = conf
        self.mbt_clt = mbt_clt
        self.dfu_clt = dfu_clt
        self.retry_params_default = retry_params_default

    def init(
        self, elem_index: int, retry_params_default: BtmeshMulticastRetryParams = None
    ):
        self.lib.btmesh.fw_dist_client.init(elem_index)
        self.set_retry_params_default(retry_params_default)

    def set_retry_params_default(self, retry_params: BtmeshMulticastRetryParams):
        if retry_params:
            assert isinstance(retry_params, BtmeshMulticastRetryParams)
            self.retry_params_default = copy.copy(retry_params)

    def validate_dist_addr(self, dist_addr: int) -> None:
        if not self.db.node_elem_addr_exist(dist_addr):
            raise BtmeshError(
                err=BtmeshErrorCode.DIST_SVR_ADDR_DOES_NOT_EXIST,
                message=f"Distributor with 0x{dist_addr:04X} does not exist.",
                dist_addr=dist_addr,
            )
        node = self.db.get_node_by_elem_addr(dist_addr)
        elem_index = node.get_elem_index(dist_addr)
        if node.dcd is not None:
            dist_mdl_id = NamedModelID.FIRMWARE_DISTRIBUTION_SERVER
            dist_mdl = ModelID(dist_mdl_id)
            if dist_mdl not in node.dcd.elements[elem_index].models:
                raise BtmeshError(
                    err=BtmeshErrorCode.DIST_SVR_MDL_DOES_NOT_EXIST,
                    message=(
                        f"The {dist_mdl_id.pretty_name} (0x{dist_mdl.model_id:04X}) "
                        f"model does not exist on 0x{dist_addr:04X} element."
                    ),
                    dist_addr=dist_addr,
                )

    def get_capabilities(
        self,
        elem_index: int,
        dist_addr: int,
        appkey_index: int = 0,
        ttl: int = 5,
        retry_params: Optional[BGLibExtRetryParams] = None,
    ) -> FwDistCapabilities:
        self.validate_dist_addr(dist_addr)
        util.validate_ttl(ttl)
        self.lib.btmesh.fw_dist_client.setup(elem_index, appkey_index, ttl)
        if retry_params is None:
            retry_params = self.retry_params_default
        # Query the FW Distribution server capabilities
        capabilities_evts = self.lib.retry_until(
            self.lib.btmesh.fw_dist_client.get_capabilities,
            elem_index,
            dist_addr,
            retry_params=retry_params,
            retry_cmd_err_code=self.RETRY_CMD_ERR_CODES,
            event_selector="btmesh_evt_fw_dist_client_capabilities_status",
            elem_index=elem_index,
            server_address=dist_addr,
        )
        capabilities_evt = capabilities_evts[0]
        # Create capabilities object
        capabilities = FwDistCapabilities(
            capabilities_evt.max_nodes_list_size,
            capabilities_evt.max_fw_list_size,
            capabilities_evt.max_fw_size,
            capabilities_evt.max_upload_space,
            capabilities_evt.remaining_upload_space,
            FwDistOOB.from_int(capabilities_evt.oob_supported),
            capabilities_evt.uri_scheme_names,
        )
        return capabilities

    def get_fw(
        self,
        elem_index: int,
        dist_addr: int,
        fwid: FWID,
        appkey_index: int = 0,
        ttl: int = 5,
        err_on_fw_miss: bool = True,
        retry_params: Optional[BGLibExtRetryParams] = None,
    ) -> FwDistFwStatus:
        self.validate_dist_addr(dist_addr)
        util.validate_ttl(ttl)
        self.lib.btmesh.fw_dist_client.setup(elem_index, appkey_index, ttl)
        if retry_params is None:
            retry_params = self.retry_params_default
        fw_status_evts = self.lib.retry_until(
            self.lib.btmesh.fw_dist_client.get_fw,
            elem_index,
            dist_addr,
            fwid.to_bytes(),
            retry_params=retry_params,
            retry_cmd_err_code=self.RETRY_CMD_ERR_CODES,
            event_selector="btmesh_evt_fw_dist_client_fw_status",
            elem_index=elem_index,
            server_address=dist_addr,
        )
        fw_status_evt = fw_status_evts[0]
        # Create FW status object
        fw_status = FwDistFwStatus(
            FwDistStatus.from_int(fw_status_evt.status),
            fw_status_evt.num_entries,
            fw_status_evt.index,
            FWID.from_bytes(fw_status_evt.fwid) if fw_status_evt.fwid else None,
        )
        if fw_status.status != FwDistStatus.SUCCESS and (
            err_on_fw_miss or fw_status.status != FwDistStatus.FWID_NOT_FOUND
        ):
            raise BtmeshError(
                err=BtmeshErrorCode.DIST_CLT_GET_FW_FAILED,
                message=f"Failed to query FW image from Distributor "
                f"(0x{dist_addr:04X}) by fwid due to "
                f'"{fw_status.status.pretty_name}" error.',
                dist_addr=dist_addr,
                fw_status=fw_status,
            )
        return fw_status

    def get_fw_by_index(
        self,
        elem_index: int,
        dist_addr: int,
        index: int,
        appkey_index: int = 0,
        ttl: int = 5,
        err_on_fw_miss: bool = True,
        retry_params: Optional[BGLibExtRetryParams] = None,
    ) -> FwDistFwStatus:
        self.validate_dist_addr(dist_addr)
        util.validate_ttl(ttl)
        self.lib.btmesh.fw_dist_client.setup(elem_index, appkey_index, ttl)
        if retry_params is None:
            retry_params = self.retry_params_default
        fw_status_evts = self.lib.retry_until(
            self.lib.btmesh.fw_dist_client.get_fw_by_index,
            elem_index,
            dist_addr,
            index,
            retry_params=retry_params,
            retry_cmd_err_code=self.RETRY_CMD_ERR_CODES,
            event_selector="btmesh_evt_fw_dist_client_fw_status",
            elem_index=elem_index,
            server_address=dist_addr,
        )
        fw_status_evt = fw_status_evts[0]
        # Create FW status object
        fw_status = FwDistFwStatus(
            FwDistStatus.from_int(fw_status_evt.status),
            fw_status_evt.num_entries,
            fw_status_evt.index,
            FWID.from_bytes(fw_status_evt.fwid) if fw_status_evt.fwid else None,
        )
        if fw_status.status != FwDistStatus.SUCCESS and (
            err_on_fw_miss or fw_status.status != FwDistStatus.FWID_NOT_FOUND
        ):
            raise BtmeshError(
                err=BtmeshErrorCode.DIST_CLT_GET_FW_BY_IDX_FAILED,
                message=f"Failed to query FW image from Distributor "
                f"(0x{dist_addr:04X}) by index ({index}) due to "
                f'"{fw_status.status.pretty_name}" error.',
                dist_addr=dist_addr,
                fw_status=fw_status,
            )
        return fw_status

    def upload(
        self,
        elem_index: int,
        dist_addr: int,
        fwid: FWID,
        metadata: bytes,
        fw_data: bytes,
        timeout_base: int = 2,
        chunk_size_pref: int = 53,
        appkey_index: int = 0,
        ttl: int = 5,
        retry_interval: Optional[float] = None,
        retry_cmd_interval: Optional[float] = None,
        on_bg_event: Optional[Callable] = None,
    ) -> None:
        self.validate_dist_addr(dist_addr)
        util.validate_ttl(ttl)
        if retry_cmd_interval is None:
            retry_cmd_interval = self.retry_params_default.retry_cmd_interval
        if retry_interval is None:
            retry_interval = self.retry_params_default.retry_interval
        retry_params = BGLibExtRetryParams(
            retry_max=self.calc_retry_max(retry_interval, timeout_base, ttl),
            retry_interval=retry_interval,
            retry_cmd_max=self.calc_retry_cmd_max(
                retry_cmd_interval, timeout_base, ttl
            ),
            retry_cmd_interval=retry_cmd_interval,
        )
        blob_id = os.urandom(Blob.BLOB_ID_LEN)
        blob = Blob(blob_id, fw_data)

        self.lib.btmesh.fw_dist_client.setup(elem_index, appkey_index, ttl)
        self.lib.btmesh.fw_dist_client.setup_upload(
            elem_index,
            dist_addr,
            ttl,
            timeout_base,
            blob.id,
            len(blob.data),
            fwid.to_bytes(),
        )
        self.lib.btmesh.fw_dist_client.set_upload_metadata(elem_index, metadata)
        # The btmesh_evt_fw_dist_client_upload_status is not filtered for FWID
        # because the Firmware Distribution Upload Status does not contain FWID
        # field when there is no space to upload the firmware to the Distributor
        # because the Distribution Server remains in Idle Upload Phase.
        # (e.g. FW size is greater than remaining upload space)
        upload_evt = self.lib.retry_until(
            self.lib.btmesh.fw_dist_client.start_upload,
            elem_index,
            retry_params=retry_params,
            retry_cmd_err_code=self.RETRY_CMD_ERR_CODES,
            event_selector=[
                "btmesh_evt_fw_dist_client_upload_status",
                "btmesh_evt_fw_dist_client_upload_failed",
            ],
            elem_index=elem_index,
            server_address=dist_addr,
        )[0]
        if upload_evt == "btmesh_evt_fw_dist_client_upload_status":
            upload_status_evt = upload_evt
            # There are three possibilities here:
            #   - If the firmware with specified FWID is already uploaded to the
            #     Distributor because the FWID is present in the FW Image List
            #     then the BT Mesh stack generates an additional
            #     btmesh_evt_fw_dist_client_upload_complete event.
            #   - If the FW upload start is rejected by the Distributor then the
            #     BT Mesh stack generates a btmesh_evt_fw_dist_client_upload_failed
            #     event. This can happen when the Distributor is busy with another
            #     (non-idempotent) firmware upload or there isn't enough space
            #     on the Distributor to upload the new firmware.
            #     See Max Firmware Images List Size, Max Firmware Image Size and
            #     Max Upload Space capabilities which results in these errors.
            #   - If the FW upload is started then no additional dist client
            #     events are expected and the MBT transfer can be started.
            upload_phase = FwDistUploadPhase.from_int(upload_status_evt.phase)
            final_events = list(
                self.lib.gen_events(
                    timeout=0.5,
                    event_selector=[
                        "btmesh_evt_fw_dist_client_upload_failed",
                        "btmesh_evt_fw_dist_client_upload_complete",
                    ],
                )
            )
        elif upload_evt == "btmesh_evt_fw_dist_client_upload_failed":
            # If btmesh_evt_fw_dist_client_upload_status event is not received
            # but the btmesh_evt_fw_dist_client_upload_failed event is received
            # then it means that upload timeout occurred because the Firmware
            # Distribution Upload Status message is not received from the
            # Distributor node.
            final_events=[upload_evt]

        if len(final_events) != 0:
            upload_evt = final_events[0]
            # The upload_evt.status_code contains the BLOB Transfer status code
            # but the BLOB transfer is not started yet
            if upload_evt == "btmesh_evt_fw_dist_client_upload_failed":
                dist_status = FwDistStatus.from_int(upload_evt.dist_status_code)
                mbt_status = MBTStatus.from_int(upload_evt.status_code)
                if dist_status != FwDistStatus.SUCCESS:
                    reason_str = dist_status.pretty_name
                else:
                    reason_str = mbt_status.pretty_name
                raise BtmeshError(
                    err=BtmeshErrorCode.DIST_CLT_UPLOAD_START_FAILED,
                    message=f"Failed to start FW upload to Distributor "
                    f'(0x{dist_addr:04X}) due to "{reason_str}" '
                    f"upload status error.",
                    dist_addr=dist_addr,
                    dist_status=dist_status,
                    fwid=fwid,
                )
            elif upload_evt == "btmesh_evt_fw_dist_client_upload_complete":
                if upload_phase == FwDistUploadPhase.TRANSFER_SUCCESS:
                    raise BtmeshError(
                        err=BtmeshErrorCode.DIST_CLT_UPLOAD_FWID_EXISTS,
                        message=f"Firmware is already uploaded to Distributor "
                        f"(0x{dist_addr:04X}).",
                        dist_addr=dist_addr,
                        fwid=fwid,
                    )
        self.evtbus.subscribe(
            event_name="btmesh_levt_mbt_transfer_progress",
            handler=self.handle_mbt_transfer_progress,
        )
        try:
            self.mbt_clt.transfer_blob(
                blob=blob,
                elem_index=elem_index,
                supported_transfer_modes=BlobTransferMode.BOTH,
                chunk_size_pref=chunk_size_pref,
                retry_interval=retry_interval,
                retry_cmd_interval=retry_cmd_interval,
                on_mbt_bg_event=on_bg_event,
            )
        except BtmeshError as e:
            if e.err != BtmeshErrorCode.MBT_TRANSFER_FAILED:
                raise
        finally:
            self.evtbus.unsubscribe(
                event_name="btmesh_levt_mbt_transfer_progress",
                handler=self.handle_mbt_transfer_progress,
            )
        upload_evt = self.lib.wait_event(
            event_selector=[
                "btmesh_evt_fw_dist_client_upload_complete",
                "btmesh_evt_fw_dist_client_upload_failed",
            ],
            elem_index=elem_index,
            server_address=dist_addr,
            fwid=fwid.to_bytes(),
        )
        if upload_evt == "btmesh_evt_fw_dist_client_upload_failed":
            mbt_status = MBTStatus.from_int(upload_evt.status_code)
            dist_status = FwDistStatus.from_int(upload_evt.dist_status_code)
            # The BT Mesh stack informs the upper layers about BLOB transfer
            # timeout in the dist_status_code variable but other BLOB transfer
            # errors are stored in status_code.
            if dist_status != FwDistStatus.SUCCESS:
                reason_str = dist_status.pretty_name
            else:
                reason_str = mbt_status.pretty_name
            raise BtmeshError(
                err=BtmeshErrorCode.DIST_CLT_UPLOAD_FAILED,
                message=f"Failed to upload firmware to Distributor "
                f'(0x{dist_addr:04X}) due to "{reason_str}" BLOB transfer error.',
                dist_addr=dist_addr,
                mbt_status=mbt_status,
                dist_status=dist_status,
            )
        elif upload_evt == "btmesh_evt_fw_dist_client_upload_complete":
            upload_status_evt = self.lib.retry_until(
                self.lib.btmesh.fw_dist_client.get_upload,
                elem_index,
                dist_addr,
                retry_params=retry_params,
                retry_cmd_err_code=self.RETRY_CMD_ERR_CODES,
                event_selector="btmesh_evt_fw_dist_client_upload_status",
                elem_index=elem_index,
                server_address=dist_addr,
            )[0]
            upload_phase = FwDistUploadPhase.from_int(upload_status_evt.phase)
            if upload_phase == FwDistUploadPhase.TRANSFER_ERROR:
                # This can happen in a corner case due to flash erase when the
                # Distributor fails with timeout and the Initiator continues.
                # This is possible because the timeout is calculated differently
                # on client and server sides.
                # Client timeout: (10000 * (timeout_base + 2)) + (100 * ttl) ms.
                # Server timeout: (10000 * (timeout_base + 1)) ms.
                # There is ~10s range when the server is already in timeout but
                # the client is still active. The MBT Server goes into suspended
                # state on timeout but Distribution Server upload state machine
                # goes into failed state.
                # The upload flash erase occurs during transfer start phase
                # which may cause enough delay to result in timeout.
                # Note: There is no flash erase during upload normally only when
                # the storage slot is not empty. (previous upload was cancelled)
                # Erase might take 5-25s based on the flash type and size.
                # Note: external SPI flash tends to be slower.
                # If the Distributor Client and MBT Client remain active then
                # the MBT Client sends the BLOB Transfer Start messages (retry)
                # which is able to restart the MBT Server (it was suspended only)
                # but the MBT Server is not able to start the Upload in the
                # Distribution Server inside the BT Mesh stack.
                # The problem can be mitigated by increasing the timeout_base to
                # guarantee that the server timeout is greater than the worst
                # case flash erase duration.
                raise BtmeshError(
                    err=BtmeshErrorCode.DIST_CLT_UPLOAD_FAILED,
                    message=f"Failed to upload firmware to Distributor "
                    f"(0x{dist_addr:04X}) due to timeout. "
                    "The timeout base might be too low.",
                    dist_addr=dist_addr,
                    mbt_status=MBTStatus.SUCCESS,
                    dist_status=FwDistStatus.TIMEOUT,
                )

    def handle_mbt_transfer_progress(self, event: MBTProgressEvent):
        levt = FwDistUploadProgressEvent(
            elem_index=event.elem_index,
            done_bytes=event.done_bytes,
            fw_size=event.blob_size,
        )
        self.evtbus.emit(levt)

    def cancel_upload(
        self,
        elem_index: int,
        dist_addr: int,
        appkey_index: int = 0,
        ttl: int = 5,
        retry_params: Optional[BGLibExtRetryParams] = None,
    ) -> None:
        self.validate_dist_addr(dist_addr)
        util.validate_ttl(ttl)
        self.lib.btmesh.fw_dist_client.setup(elem_index, appkey_index, ttl)
        if retry_params is None:
            retry_params = self.retry_params_default
        upload_status_evt = self.lib.retry_until(
            self.lib.btmesh.fw_dist_client.cancel_upload,
            elem_index,
            dist_addr,
            retry_params=retry_params,
            retry_cmd_err_code=self.RETRY_CMD_ERR_CODES,
            event_selector="btmesh_evt_fw_dist_client_upload_status",
            elem_index=elem_index,
            server_address=dist_addr,
        )[0]
        dist_status = FwDistStatus.from_int(upload_status_evt.status)
        if dist_status != FwDistStatus.SUCCESS:
            raise BtmeshError(
                err=BtmeshErrorCode.DIST_CLT_UPLOAD_CANCEL_FAILED,
                message=f"Failed to cancel FW upload to Distributor "
                f'(0x{dist_addr:04X}) due to "{dist_status.pretty_name}" error.',
                dist_addr=dist_addr,
                status=dist_status,
            )

    def _delete_fw_reset_dist_phase(
        self,
        elem_index: int,
        dist_addr: int,
        appkey_index: int = 0,
        ttl: int = 5,
        retry_params: Optional[BGLibExtRetryParams] = None,
    ) -> None:
        # The specification allows FW delete in Idle distribution phase only but
        # the distribution phase is set to Completed or Failed after a firmware
        # distribution. The distribution phase is set to Idle from Completed or
        # Failed state by cancel or delete receivers operations.
        # Delete receivers is preferred here because it fails when the firmware
        # distribution is still active so the accidental cancellation can be
        # avoided this way.
        try:
            self.delete_receivers(
                elem_index=elem_index,
                dist_addr=dist_addr,
                appkey_index=appkey_index,
                ttl=ttl,
                retry_params=retry_params,
            )
        except BtmeshError as e:
            # If delete all receivers procedure fails then it means that the
            # distribution is active. The error is caught here and the final
            # error is raised by the delete FW procedure.
            if e.err != BtmeshErrorCode.DIST_CLT_DELETE_RECEIVERS_FAILED:
                raise

    def delete_fw(
        self,
        elem_index: int,
        dist_addr: int,
        fwid: FWID,
        appkey_index: int = 0,
        ttl: int = 5,
        retry_params: Optional[BGLibExtRetryParams] = None,
    ) -> FwDistFwStatus:
        self.validate_dist_addr(dist_addr)
        util.validate_ttl(ttl)
        self.lib.btmesh.fw_dist_client.setup(elem_index, appkey_index, ttl)
        if retry_params is None:
            retry_params = self.retry_params_default
        self._delete_fw_reset_dist_phase(
            elem_index=elem_index,
            dist_addr=dist_addr,
            appkey_index=appkey_index,
            ttl=ttl,
            retry_params=retry_params,
        )
        fw_status_evts = self.lib.retry_until(
            self.lib.btmesh.fw_dist_client.delete_fw,
            elem_index,
            dist_addr,
            fwid.to_bytes(),
            retry_params=retry_params,
            retry_cmd_err_code=self.RETRY_CMD_ERR_CODES,
            event_selector="btmesh_evt_fw_dist_client_fw_status",
            elem_index=elem_index,
            server_address=dist_addr,
        )
        fw_status_evt = fw_status_evts[0]
        # Create FW status object
        fw_status = FwDistFwStatus(
            FwDistStatus.from_int(fw_status_evt.status),
            fw_status_evt.num_entries,
            fw_status_evt.index,
            FWID.from_bytes(fw_status_evt.fwid) if fw_status_evt.fwid else None,
        )
        if fw_status.status != FwDistStatus.SUCCESS:
            raise BtmeshError(
                err=BtmeshErrorCode.DIST_CLT_DELETE_FW_FAILED,
                message=f"Failed to delete FW image from Distributor "
                f'(0x{dist_addr:04X}) due to "{fw_status.status.pretty_name}" '
                f" error.",
                dist_addr=dist_addr,
                fw_status=fw_status,
            )
        return fw_status

    def delete_all_fw(
        self,
        elem_index: int,
        dist_addr: int,
        appkey_index: int = 0,
        ttl: int = 5,
        retry_params: Optional[BGLibExtRetryParams] = None,
    ) -> FwDistFwStatus:
        self.validate_dist_addr(dist_addr)
        util.validate_ttl(ttl)
        self.lib.btmesh.fw_dist_client.setup(elem_index, appkey_index, ttl)
        if retry_params is None:
            retry_params = self.retry_params_default
        self._delete_fw_reset_dist_phase(
            elem_index=elem_index,
            dist_addr=dist_addr,
            appkey_index=appkey_index,
            ttl=ttl,
            retry_params=retry_params,
        )
        fw_status_evts = self.lib.retry_until(
            self.lib.btmesh.fw_dist_client.delete_all_fw,
            elem_index,
            dist_addr,
            retry_params=retry_params,
            retry_cmd_err_code=self.RETRY_CMD_ERR_CODES,
            event_selector="btmesh_evt_fw_dist_client_fw_status",
            elem_index=elem_index,
            server_address=dist_addr,
        )
        fw_status_evt = fw_status_evts[0]
        # Create FW status object
        fw_status = FwDistFwStatus(
            FwDistStatus.from_int(fw_status_evt.status),
            fw_status_evt.num_entries,
            fw_status_evt.index,
            FWID.from_bytes(fw_status_evt.fwid) if fw_status_evt.fwid else None,
        )
        if fw_status.status != FwDistStatus.SUCCESS:
            raise BtmeshError(
                err=BtmeshErrorCode.DIST_CLT_DELETE_ALL_FW_FAILED,
                message=f"Failed to delete all FW images from Distributor "
                f'(0x{dist_addr:04X}) due to "{fw_status.status.pretty_name}" '
                f"error.",
                dist_addr=dist_addr,
                fw_status=fw_status,
            )
        return fw_status

    def delete_receivers(
        self,
        elem_index: int,
        dist_addr: int,
        appkey_index: int = 0,
        ttl: int = 5,
        retry_params: Optional[BGLibExtRetryParams] = None,
    ) -> None:
        self.validate_dist_addr(dist_addr)
        util.validate_ttl(ttl)
        self.lib.btmesh.fw_dist_client.setup(elem_index, appkey_index, ttl)
        if retry_params is None:
            retry_params = self.retry_params_default
        receiver_status_evts = self.lib.retry_until(
            self.lib.btmesh.fw_dist_client.delete_all_receivers,
            elem_index,
            dist_addr,
            retry_params=retry_params,
            retry_cmd_err_code=self.RETRY_CMD_ERR_CODES,
            event_selector="btmesh_evt_fw_dist_client_receivers_status",
            elem_index=elem_index,
            server_address=dist_addr,
        )
        receiver_status_evt = receiver_status_evts[0]
        status = FwDistStatus.from_int(receiver_status_evt.status)
        if status != FwDistStatus.SUCCESS:
            raise BtmeshError(
                err=BtmeshErrorCode.DIST_CLT_DELETE_RECEIVERS_FAILED,
                message=f"Failed to delete receivers from Distributor "
                f'(0x{dist_addr:04X}) due to "{status.pretty_name}" error.',
                dist_addr=dist_addr,
                status=status,
            )

    def add_receivers(
        self,
        elem_index: int,
        dist_addr: int,
        receivers: Iterable[FwReceiver],
        appkey_index: int = 0,
        receivers_per_msg: int = 3,
        ttl: int = 5,
        retry_params: Optional[BGLibExtRetryParams] = None,
    ) -> None:
        self.validate_dist_addr(dist_addr)
        util.validate_ttl(ttl)
        for receiver in receivers:
            util.validate_unicast_address(
                receiver.server_addr, "Invalid receiver address."
            )
        self.lib.btmesh.fw_dist_client.setup(elem_index, appkey_index, ttl)
        if retry_params is None:
            retry_params = self.retry_params_default
        n = receivers_per_msg
        receiver_chunks: Iterable[Iterable[FwReceiver]] = (
            receivers[i : i + n] for i in range(0, len(receivers), n)
        )
        for receiver_chunk in receiver_chunks:
            receiver_bytes_list = []
            for receiver in receiver_chunk:
                receiver_bytes_list.append(
                    struct.pack("<HB", receiver.server_addr, receiver.fw_index)
                )
            receivers_bytes = b"".join(receiver_bytes_list)
            receiver_status_evt = self.lib.retry_until(
                self.lib.btmesh.fw_dist_client.add_receivers,
                elem_index,
                dist_addr,
                receivers_bytes,
                retry_params=retry_params,
                retry_cmd_err_code=self.RETRY_CMD_ERR_CODES,
                event_selector="btmesh_evt_fw_dist_client_receivers_status",
                elem_index=elem_index,
                server_address=dist_addr,
            )[0]
            status = FwDistStatus.from_int(receiver_status_evt.status)
            if status != FwDistStatus.SUCCESS:
                raise BtmeshError(
                    err=BtmeshErrorCode.DIST_CLT_ADD_RECEIVERS_FAILED,
                    message=f"Failed to add receivers to Distributor "
                    f'(0x{dist_addr:04X}) due to "{status.pretty_name}" '
                    f"error.",
                    dist_addr=dist_addr,
                    status=status,
                )

    def get_receivers(
        self,
        elem_index: int,
        dist_addr: int,
        start_index: int,
        max_entries: int,
        receivers_per_msg: int = 10,
        appkey_index: int = 0,
        ttl: int = 5,
        retry_params: Optional[BGLibExtRetryParams] = None,
    ) -> List[FwReceiverInfo]:
        self.validate_dist_addr(dist_addr)
        util.validate_ttl(ttl)
        self.lib.btmesh.fw_dist_client.setup(elem_index, appkey_index, ttl)
        if retry_params is None:
            retry_params = self.retry_params_default
        start_idx = start_index
        end_idx = start_idx + max_entries
        chunk_size = receivers_per_msg
        receiver_chunks = []
        for idx in range(start_idx, end_idx, chunk_size):
            if idx + chunk_size < end_idx:
                receiver_chunks.append((idx, chunk_size))
            else:
                receiver_chunks.append((idx, end_idx - idx))
        event_selector = {
            "btmesh_evt_fw_dist_client_receivers_list": {
                "#final": False,
                "elem_index": elem_index,
                "server_address": dist_addr,
            },
            "btmesh_evt_fw_dist_client_receivers_list_end": {
                "#final": True,
                "elem_index": elem_index,
                "server_address": dist_addr,
            },
        }
        receiver_info_list = []
        for start_idx, max_entries in receiver_chunks:
            receiver_list_evts = self.lib.retry_until(
                self.lib.btmesh.fw_dist_client.get_receivers,
                elem_index,
                dist_addr,
                start_idx,
                max_entries,
                retry_params=retry_params,
                retry_cmd_err_code=self.RETRY_CMD_ERR_CODES,
                event_selector=event_selector,
            )
            for receiver_evt in receiver_list_evts:
                if receiver_evt == "btmesh_evt_fw_dist_client_receivers_list":
                    receiver_info = FwReceiverInfo(
                        index=receiver_evt.index,
                        receiver_count=receiver_evt.nodes_list_size,
                        server_addr=receiver_evt.address,
                        fw_index=receiver_evt.fw_index,
                        phase=FwReceiverPhase.from_int(receiver_evt.phase),
                        dfu_status=FwUpdateStatus.from_int(receiver_evt.update_status),
                        mbt_status=MBTStatus.from_int(receiver_evt.transfer_status),
                        progress=receiver_evt.progress,
                    )
                    receiver_info_list.append(receiver_info)
        return receiver_info_list

    def get_dist_status(
        self,
        elem_index: int,
        dist_addr: int,
        appkey_index: int = 0,
        ttl: int = 5,
        retry_params: Optional[BGLibExtRetryParams] = None,
    ) -> FwDistDistributionStatus:
        self.validate_dist_addr(dist_addr)
        util.validate_ttl(ttl)
        self.lib.btmesh.fw_dist_client.setup(elem_index, appkey_index, ttl)
        if retry_params is None:
            retry_params = self.retry_params_default
        dist_status_evt = self.lib.retry_until(
            self.lib.btmesh.fw_dist_client.get,
            elem_index,
            dist_addr,
            retry_params=retry_params,
            retry_cmd_err_code=self.RETRY_CMD_ERR_CODES,
            event_selector="btmesh_evt_fw_dist_client_distribution_status",
            elem_index=elem_index,
            server_address=dist_addr,
        )[0]
        dist_status = FwDistDistributionStatus(
            status=FwDistStatus.from_int(dist_status_evt.status),
            phase=FwDistPhase.from_int(dist_status_evt.phase),
            group_addr=dist_status_evt.group_address,
            appkey_index=dist_status_evt.appkey_index,
            ttl=dist_status_evt.distributor_ttl,
            timeout_base=dist_status_evt.timeout_base,
            transfer_mode=BlobTransferMode.from_int(dist_status_evt.transfer_mode),
            update_policy=FwUpdatePolicy.from_int(dist_status_evt.apply_immediately),
            fw_list_index=dist_status_evt.fw_list_index,
        )
        status = dist_status.status
        if status != FwDistStatus.SUCCESS:
            # The get distribution status operation should not fail.
            raise BtmeshError(
                err=BtmeshErrorCode.DIST_CLT_GET_DIST_FAILED,
                message=f"Failed to get distribution status from Distributor "
                f'(0x{dist_addr:04X}) due to "{status.pretty_name} error.',
                dist_addr=dist_addr,
                status=status,
            )
        return dist_status

    def start_distribution(
        self,
        elem_index: int,
        dist_addr: int,
        group_addr: int,
        fw_list_index: int,
        dist_timeout_base: int,
        dist_appkey_index: int,
        dist_ttl: int,
        transfer_mode: BlobTransferMode = BlobTransferMode.PUSH,
        appkey_index: int = 0,
        ttl: int = 5,
        retry_params: Optional[BGLibExtRetryParams] = None,
    ):
        self.validate_dist_addr(dist_addr)
        util.validate_ttl(ttl)
        self.lib.btmesh.fw_dist_client.setup(elem_index, appkey_index, ttl)
        if retry_params is None:
            retry_params = self.retry_params_default
        if (transfer_mode == BlobTransferMode.PULL) and (
            group_addr != util.UNASSIGNED_ADDR
        ):
            logger.warning(
                "Pull BLOB transfer mode is not recommended with group address "
                "during distribution because messages sent to group address "
                "are stored in the friend queues of friend nodes of each "
                "receiver low power target node. "
                "This is problematic during chunk transfer because the target "
                "nodes might request different chunks in BLOB Partial Block "
                "Report messages and the chunks of one Low Power Node might push "
                "out the chunks of the other node from the friend queues because "
                "friend queues keep the most recent message when they are full. "
                "The firmware update is possible in pull transfer mode with group "
                "address despite of the issues above but it is not optimal and "
                "it can be much slower."
            )
        dist_status_evt = self.lib.retry_until(
            self.lib.btmesh.fw_dist_client.start_distribution,
            elem_index,
            dist_addr,
            dist_appkey_index,
            dist_ttl,
            dist_timeout_base,
            transfer_mode.value,
            FwUpdatePolicy.VERIFY_AND_APPLY.value,
            fw_list_index,
            group_addr,
            self.UNUSED_VIRTUAL_ADDRESS,
            retry_params=retry_params,
            retry_cmd_err_code=self.RETRY_CMD_ERR_CODES,
            event_selector="btmesh_evt_fw_dist_client_distribution_status",
            elem_index=elem_index,
            server_address=dist_addr,
        )[0]
        status = FwDistStatus.from_int(dist_status_evt.status)
        if status != FwDistStatus.SUCCESS:
            raise BtmeshError(
                err=BtmeshErrorCode.DIST_CLT_START_DIST_FAILED,
                message=f"Failed to start distribution on Distributor "
                f'(0x{dist_addr:04X}) due to "{status.pretty_name}" error.',
                dist_addr=dist_addr,
                status=status,
            )

    def poll_distribution(
        self,
        elem_index: int,
        dist_addr: int,
        receivers: Iterable[FwReceiver],
        failed_receivers_info: Iterable[FwReceiverInfo],
        appkey_index: int = 0,
        ttl: int = 5,
        dist_poll_int: float = 5,
        retry_params: Optional[BGLibExtRetryParams] = None,
    ) -> Tuple[FwDistDistributionStatus, List[FwReceiverInfo]]:
        while True:
            self.lib.wait(max_time=dist_poll_int)
            dist_status = self.get_dist_status(
                elem_index=elem_index,
                dist_addr=dist_addr,
                appkey_index=appkey_index,
                ttl=ttl,
                retry_params=retry_params,
            )
            receivers_info = self.get_receivers(
                elem_index=elem_index,
                dist_addr=dist_addr,
                start_index=0,
                max_entries=len(receivers),
                appkey_index=appkey_index,
                ttl=ttl,
                retry_params=retry_params,
            )
            receiver_count = len(receivers) + len(failed_receivers_info)
            for rec_info in receivers_info:
                rec_info.receiver_count = receiver_count
            receivers_info.extend(failed_receivers_info)
            levt = FwDistDistributionProgressEvent(
                elem_index=elem_index,
                dist_status=dist_status,
                receivers_info=receivers_info,
            )
            self.evtbus.emit(levt)
            if dist_status.phase in (
                FwDistPhase.IDLE,
                FwDistPhase.COMPLETED,
                FwDistPhase.FAILED,
            ):
                break
        return dist_status, receivers_info

    def distribution(
        self,
        elem_index: int,
        dist_addr: int,
        group_addr: int,
        receivers: Iterable[FwReceiver],
        fw_list_index: int,
        dist_timeout_base: int,
        dist_appkey_index: int,
        dist_ttl: int,
        metadata: bytes = b"",
        transfer_mode: BlobTransferMode = BlobTransferMode.PUSH,
        appkey_index: int = 0,
        ttl: int = 5,
        dist_poll_int: float = 5,
        retry_params: Optional[BtmeshMulticastRetryParams] = None,
    ) -> Tuple[FwDistDistributionStatus, Iterable[FwReceiverInfo]]:
        for receiver in receivers:
            util.validate_unicast_address(
                receiver.server_addr, "Invalid receiver address."
            )
        if retry_params is None:
            retry_params = self.retry_params_default
        metadata_status_dict = self.dfu_clt.check_receivers_metadata(
            elem_index=elem_index,
            receivers=receivers,
            metadata=metadata,
            group_addr=group_addr,
            appkey_index=appkey_index,
            ttl=ttl,
            retry_params=retry_params,
        )
        active_receivers: List[FwReceiver] = []
        failed_receivers: List[FwReceiver] = []
        failed_receivers_info = []
        for receiver in receivers:
            addr = receiver.server_addr
            mds = metadata_status_dict[addr]
            if mds.status == FwUpdateStatus.SUCCESS:
                active_receivers.append(receiver)
            else:
                failed_receivers.append(receiver)
        index = len(active_receivers)
        receiver_count = len(receivers)
        for failed_receiver in failed_receivers:
            addr = failed_receiver.server_addr
            mds = metadata_status_dict[addr]
            receiver_info = FwReceiverInfo(
                index=index,
                receiver_count=receiver_count,
                server_addr=failed_receiver.server_addr,
                fw_index=failed_receiver.fw_index,
                phase=FwReceiverPhase.UNKNOWN,
                dfu_status=mds.status,
                mbt_status=MBTStatus.UNKNOWN,
                progress=0,
            )
            index += 1
            failed_receivers_info.append(receiver_info)
        if len(active_receivers) == 0:
            # All receivers failed during the metadata check
            dist_status = FwDistDistributionStatus(
                status=FwDistStatus.SUCCESS,
                phase=FwDistPhase.FAILED,
                group_addr=group_addr,
                appkey_index=dist_appkey_index,
                ttl=dist_ttl,
                timeout_base=dist_timeout_base,
                transfer_mode=transfer_mode,
                update_policy=FwUpdatePolicy.VERIFY_AND_APPLY,
                fw_list_index=fw_list_index,
            )
            receivers_info = failed_receivers_info
            return dist_status, receivers_info
        self.delete_receivers(
            elem_index=elem_index,
            dist_addr=dist_addr,
            appkey_index=appkey_index,
            ttl=ttl,
            retry_params=retry_params,
        )
        self.add_receivers(
            elem_index=elem_index,
            dist_addr=dist_addr,
            receivers=active_receivers,
            appkey_index=appkey_index,
            ttl=ttl,
            retry_params=retry_params,
        )
        self.start_distribution(
            elem_index=elem_index,
            dist_addr=dist_addr,
            group_addr=group_addr,
            fw_list_index=fw_list_index,
            dist_timeout_base=dist_timeout_base,
            dist_appkey_index=dist_appkey_index,
            dist_ttl=dist_ttl,
            transfer_mode=transfer_mode,
            appkey_index=appkey_index,
            ttl=ttl,
            retry_params=retry_params,
        )
        dist_status, receivers_info = self.poll_distribution(
            elem_index=elem_index,
            dist_addr=dist_addr,
            receivers=active_receivers,
            failed_receivers_info=failed_receivers_info,
            appkey_index=appkey_index,
            ttl=ttl,
            dist_poll_int=dist_poll_int,
            retry_params=retry_params,
        )
        for rec_info in receivers_info:
            addr = rec_info.server_addr
            additional_info = metadata_status_dict[addr].additional_info
            if (
                rec_info.phase == FwReceiverPhase.APPLY_SUCCESS
                and additional_info == FwUpdateAdditionalInfo.DEVICE_UNPROVISIONED
            ):
                node = self.db.get_node_by_elem_addr(addr)
                self.conf.reset_node(node=node, local=True)
        return dist_status, receivers_info

    def cancel_distribution(
        self,
        elem_index: int,
        dist_addr: int,
        appkey_index: int = 0,
        ttl: int = 5,
        dist_poll_int: float = 5,
        retry_params: Optional[BGLibExtRetryParams] = None,
    ):
        self.validate_dist_addr(dist_addr)
        util.validate_ttl(ttl)
        self.lib.btmesh.fw_dist_client.setup(elem_index, appkey_index, ttl)
        if retry_params is None:
            retry_params = self.retry_params_default
        # Cancel the FW Distribution
        dist_status_evt = self.lib.retry_until(
            self.lib.btmesh.fw_dist_client.cancel_distribution,
            elem_index,
            dist_addr,
            retry_params=retry_params,
            retry_cmd_err_code=self.RETRY_CMD_ERR_CODES,
            event_selector="btmesh_evt_fw_dist_client_distribution_status",
            elem_index=elem_index,
            server_address=dist_addr,
        )[0]
        status = FwDistStatus.from_int(dist_status_evt.status)
        phase = FwDistPhase.from_int(dist_status_evt.phase)
        if status != FwDistStatus.SUCCESS:
            raise BtmeshError(
                err=BtmeshErrorCode.DIST_CLT_CANCEL_DIST_FAILED,
                message=f"Failed to cancel FW Distribution on Distributor "
                f'(0x{dist_addr:04X}) due to "{status.pretty_name}" error.',
                dist_addr=dist_addr,
                status=status,
            )
        if phase == FwDistPhase.CANCELING_UPDATE:
            # The FW update shall cancelled on each target node which takes
            # some time so wait until the Distributor leaves the canceling
            # update phase.
            while True:
                self.lib.wait(max_time=dist_poll_int)
                dist_status = self.get_dist_status(
                    elem_index=elem_index,
                    dist_addr=dist_addr,
                    appkey_index=appkey_index,
                    ttl=ttl,
                    retry_params=retry_params,
                )
                if dist_status.phase != FwDistPhase.CANCELING_UPDATE:
                    break
