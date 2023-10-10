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
from typing import (Callable, ClassVar, Dict, Iterable, List, Optional, Tuple,
                    Union)

from bgapi.bglib import BGEvent, CommandFailedError
from bgapix.bglibx import (BGLibExtRetryParams, BGLibExtWaitEventError,
                           EventParamValues)
from bgapix.slstatus import SlStatus

from . import util
from .conf import Configurator
from .core import (BtmeshAddressList, BtmeshBaseStatus, BtmeshComponent,
                   BtmeshCore, BtmeshStatusErrorClass)
from .db import FWID, BtmeshDatabase
from .errors import BtmeshError, BtmeshErrorCode
from .event import LocalEvent
from .mbt import (Blob, BlobTransferClient, BlobTransferMode, MBTProgressEvent,
                  MBTStatus)
from .util import BtmeshMulticastRetryParams, BtmeshRetryParams

logger = logging.getLogger(__name__)


@enum.unique
class FwReceiverPhase(util.BtmeshIntEnum):
    IDLE = 0x00
    TRANSFER_ERROR = 0x01
    TRANSFER_IN_PROGRESS = 0x02
    VERIFYING_UPDATE = 0x03
    VERIFICATION_SUCCESS = 0x04
    VERIFICATION_FAILED = 0x05
    APPLY_IN_PROGRESS = 0x06
    TRANSFER_CANCELLED = 0x07
    APPLY_SUCCESS = 0x08
    APPLY_FAILED = 0x09
    UNKNOWN = 0x0A
    UNKNOWN_VALUE = util.ENUM_UNKNOWN_VALUE


@enum.unique
class FwUpdatePhase(util.BtmeshIntEnum):
    IDLE = 0x00
    TRANSFER_ERROR = 0x01
    TRANSFER_IN_PROGRESS = 0x02
    VERIFYING_UPDATE = 0x03
    VERIFICATION_SUCCESS = 0x04
    VERIFICATION_FAILED = 0x05
    APPLY_IN_PROGRESS = 0x06
    UNKNOWN_VALUE = util.ENUM_UNKNOWN_VALUE


@enum.unique
class FwUpdateStatus(util.BtmeshIntEnum):
    SUCCESS = 0x00
    OUT_OF_RESOURCES = 0x01
    WRONG_PHASE = 0x02
    INTERNAL_ERROR = 0x03
    WRONG_FW_INDEX = 0x04
    METADATA_CHECK_FAILED = 0x05
    TEMPORARILY_UNABLE = 0x06
    BLOB_TRANSFER_BUSY = 0x07
    COMMAND_ERROR = 0xFE
    TIMEOUT = 0xFF
    UNKNOWN_VALUE = util.ENUM_UNKNOWN_VALUE


@enum.unique
class FwUpdateStep(util.BtmeshIntEnum):
    IDLE = 0x00
    STARTING_UPDATE = 0x01
    TRANSFERRING_IMAGE = 0x02
    CHECKING_VERIFICATION = 0x03
    WAITING_FOR_APPLY = 0x04
    APPLYING_UPDATE = 0x05
    CHECKING_UPDATE_RESULT = 0x06
    COMPLETED = 0x07
    FAILED = 0x08
    CANCELLING = 0x09
    SUSPENDED = 0x0A
    UNKNOWN_VALUE = util.ENUM_UNKNOWN_VALUE

    def is_active(self):
        return self not in (
            FwUpdateStep.IDLE,
            FwUpdateStep.COMPLETED,
            FwUpdateStep.FAILED,
        )


@enum.unique
class FwUpdateAdditionalInfo(util.BtmeshIntEnum):
    CD_UNCHANGED = 0
    CD_UNCHANGED_RPR_UNSUPPORTED = 1
    CD_UNCHANGED_RPR_SUPPORTED = 2
    DEVICE_UNPROVISIONED = 3
    UNKNOWN_VALUE = util.ENUM_UNKNOWN_VALUE


@dataclasses.dataclass
class FwReceiver:
    server_addr: int
    fw_index: int

    def __post_init__(self):
        util.validate_unicast_address(self.server_addr, "Invalid receiver address.")
        util.validate_fw_index(self.fw_index)


@dataclasses.dataclass
class FwReceiverInfo:
    index: int
    receiver_count: int
    server_addr: int
    fw_index: int
    phase: FwReceiverPhase
    dfu_status: FwUpdateStatus
    mbt_status: MBTStatus
    progress: int


@dataclasses.dataclass
class FwUpdateBaseStatus(BtmeshBaseStatus):
    server_addr: int
    status: FwUpdateStatus

    @classmethod
    def create_command_error(
        cls, db: BtmeshDatabase, addr: int, command_result: SlStatus
    ) -> "FwUpdateBaseStatus":
        return cls(
            command_result=command_result,
            server_addr=addr,
            status=FwUpdateStatus.COMMAND_ERROR,
        )

    @classmethod
    def create_timeout(cls, db: BtmeshDatabase, addr: int) -> "FwUpdateBaseStatus":
        return cls(
            command_result=SlStatus.OK,
            server_addr=addr,
            status=FwUpdateStatus.TIMEOUT,
        )

    def get_error_class(self) -> BtmeshStatusErrorClass:
        if self.command_result != SlStatus.OK:
            return BtmeshStatusErrorClass.COMMAND_ERROR
        elif self.status == FwUpdateStatus.TIMEOUT:
            return BtmeshStatusErrorClass.TIMEOUT
        elif self.status == FwUpdateStatus.SUCCESS:
            return BtmeshStatusErrorClass.SUCCESS
        else:
            return BtmeshStatusErrorClass.FAILURE

    def get_addr(self) -> int:
        return self.server_addr


@dataclasses.dataclass
class FwUpdateInfoStatus(FwUpdateBaseStatus):
    fw_index: Optional[int] = None
    fw_count: Optional[int] = None
    fwid: Optional[FWID] = None
    uri: Optional[str] = None

    @classmethod
    def raise_construction_error(cls):
        raise ValueError(
            f"The {cls.__name__} can be constructed only from "
            f"one btmesh_evt_fw_update_client_info_status_current_fwid and "
            f"one btmesh_evt_fw_update_client_info_status_update_uri event."
        )

    @classmethod
    def create_from_events(
        cls, db: BtmeshDatabase, events: Iterable[BGEvent]
    ) -> "FwUpdateInfoStatus":
        events = list(events)
        if len(events) != 2:
            cls.raise_construction_error()
        if events[0] == "btmesh_evt_fw_update_client_info_status_current_fwid":
            info_status_fwid_evt = events[0]
        elif events[1] == "btmesh_evt_fw_update_client_info_status_current_fwid":
            info_status_fwid_evt = events[1]
        else:
            cls.raise_construction_error()
        if events[0] == "btmesh_evt_fw_update_client_info_status_update_uri":
            info_status_uri_evt = events[0]
        elif events[1] == "btmesh_evt_fw_update_client_info_status_update_uri":
            info_status_uri_evt = events[1]
        else:
            cls.raise_construction_error()
        try:
            uri = info_status_uri_evt.update_uri.decode("utf-8")
        except UnicodeDecodeError:
            logger.error(
                f"Failed to decode FW information list update URI "
                f"({hex(info_status_uri_evt.update_uri)}) at "
                f"{info_status_uri_evt.index} index."
            )
            uri = ""
        return FwUpdateInfoStatus(
            command_result=SlStatus.OK,
            status=FwUpdateStatus.SUCCESS,
            server_addr=info_status_fwid_evt.server_address,
            fw_index=info_status_fwid_evt.index,
            fw_count=info_status_fwid_evt.count,
            fwid=FWID.from_bytes(info_status_fwid_evt.current_fwid),
            uri=uri,
        )


@dataclasses.dataclass
class FwUpdateMetadataStatus(FwUpdateBaseStatus):
    additional_info: Optional[FwUpdateAdditionalInfo] = None
    fw_index: Optional[int] = None

    @classmethod
    def create_from_events(
        cls, db: BtmeshDatabase, events: Iterable[BGEvent]
    ) -> "FwUpdateMetadataStatus":
        event = next(iter(events))
        return FwUpdateMetadataStatus(
            command_result=SlStatus.OK,
            server_addr=event.server_address,
            status=FwUpdateStatus.from_int(event.status),
            additional_info=FwUpdateAdditionalInfo.from_int(
                event.additional_information
            ),
            fw_index=event.fw_index,
        )


@dataclasses.dataclass
class FwUpdateProgressEvent(LocalEvent):
    name: ClassVar[str] = "btmesh_levt_dfu_fw_update_progress"
    elem_index: int
    dfu_state: FwUpdateStep
    receivers_info: Iterable[FwReceiverInfo]


class FwUpdateClient(BtmeshComponent):
    RETRY_CMD_ERR_CODES = (SlStatus.NO_MORE_RESOURCE,)
    UNUSED_VIRTUAL_ADDR = b"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    DFU_STATE_CHANGED_EVENT = "btmesh_evt_fw_standalone_updater_dist_state_changed"

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
        retry_params_default: BtmeshMulticastRetryParams,
    ):
        super().__init__(core)
        self.conf = conf
        self.mbt_clt = mbt_clt
        self.retry_params_default = retry_params_default

    def init(
        self,
        elem_index: int = 0,
        max_target_nodes: int = 8,
        retry_params_default: BtmeshMulticastRetryParams = None,
    ):
        self.lib.btmesh.fw_update_client.init(elem_index)
        self.lib.btmesh.fw_standalone_updater.init(elem_index, max_target_nodes)
        self.set_retry_params_default(retry_params_default)

    def set_retry_params_default(self, retry_params: BtmeshMulticastRetryParams):
        if retry_params:
            assert isinstance(retry_params, BtmeshMulticastRetryParams)
            self.retry_params_default = copy.copy(retry_params)

    def dfu_procedure(
        self,
        cmd,
        elem_index: int,
        server_addrs: Union[int, Iterable[int]],
        group_addr: int,
        virtual_addr: bytes,
        appkey_index: int,
        ttl: int,
        *args,
        event_selector,
        fw_update_status_class: FwUpdateBaseStatus,
        retry_params: BtmeshMulticastRetryParams = None,
        **final_event_params,
    ) -> Dict[int, FwUpdateBaseStatus]:
        if not util.is_iterable(server_addrs):
            server_addrs = [server_addrs]
        util.validate_ttl(ttl)
        for addr in server_addrs:
            util.validate_unicast_address(addr, "Invalid server address.")
        if group_addr != util.UNASSIGNED_ADDR:
            util.validate_multicast_address(group_addr)
        if virtual_addr:
            util.validate_virtual_label_uuid(virtual_addr)
        else:
            virtual_addr = self.UNUSED_VIRTUAL_ADDR
        if retry_params is None:
            retry_params = self.retry_params_default
        return self.core.send_until(
            cmd,
            elem_index,
            BtmeshAddressList(list(server_addrs), group_addr=group_addr),
            virtual_addr,
            appkey_index,
            ttl,
            *args,
            event_selector=event_selector,
            status_class=fw_update_status_class,
            retry_int_rst_on_evt=True,
            retry_params=retry_params,
            retry_cmd_err_code=[SlStatus.NO_MORE_RESOURCE],
            **final_event_params,
        )

    def get_info(
        self,
        elem_index: int,
        server_addrs: Union[int, Iterable[int]],
        first_index: int,
        max_entries: int,
        group_addr: int = util.UNASSIGNED_ADDR,
        virtual_addr: bytes = bytes(),
        appkey_index: int = 0,
        ttl: int = 5,
        retry_params: BtmeshMulticastRetryParams = None,
    ) -> Dict[int, FwUpdateInfoStatus]:
        raw_event_selector = {
            "btmesh_evt_fw_update_client_info_status_current_fwid": {"#final": False},
            "btmesh_evt_fw_update_client_info_status_update_uri": {"#final": True},
        }
        return self.dfu_procedure(
            self.lib.btmesh.fw_update_client.get_info,
            elem_index,
            server_addrs,
            group_addr,
            virtual_addr,
            appkey_index,
            ttl,
            first_index,
            max_entries,
            event_selector=raw_event_selector,
            fw_update_status_class=FwUpdateInfoStatus,
            retry_params=retry_params,
        )

    def check_metadata(
        self,
        elem_index: int,
        server_addrs: Union[int, Iterable[int]],
        fw_index: int,
        metadata: bytes,
        group_addr: int = util.UNASSIGNED_ADDR,
        virtual_addr: bytes = bytes(),
        appkey_index: int = 0,
        ttl: int = 5,
        retry_params: BtmeshMulticastRetryParams = None,
    ) ->  Dict[int, FwUpdateMetadataStatus]:
        return self.dfu_procedure(
            self.lib.btmesh.fw_update_client.check_metadata,
            elem_index,
            server_addrs,
            group_addr,
            virtual_addr,
            appkey_index,
            ttl,
            fw_index,
            metadata,
            event_selector="btmesh_evt_fw_update_client_metadata_status",
            fw_update_status_class=FwUpdateMetadataStatus,
            retry_params=retry_params,
        )

    def check_receivers_metadata(
        self,
        elem_index: int,
        receivers: Iterable[FwReceiver],
        metadata: bytes = b"",
        group_addr: int = util.UNASSIGNED_ADDR,
        virtual_addr: bytes = bytes(),
        appkey_index: int = 0,
        ttl: int = 5,
        retry_params: Optional[BtmeshMulticastRetryParams] = None,
    ) -> Dict[int, FwUpdateMetadataStatus]:
        util.validate_ttl(ttl)
        if retry_params is None:
            retry_params = self.retry_params_default
        fw_idx_set = set((receiver.fw_index for receiver in receivers))
        if len(fw_idx_set) == 1:
            addr_metadata_status_dict = self.check_metadata(
                elem_index=elem_index,
                server_addrs=[receiver.server_addr for receiver in receivers],
                fw_index=fw_idx_set.pop(),
                metadata=metadata,
                group_addr=group_addr,
                virtual_addr=virtual_addr,
                appkey_index=appkey_index,
                ttl=ttl,
                retry_params=retry_params,
            )
        else:
            addr_metadata_status_dict = {}
            for receiver in receivers:
                addr_metadata_status_pair_dict = self.check_metadata(
                    elem_index=elem_index,
                    server_addrs=receiver.server_addr,
                    fw_index=receiver.fw_index,
                    metadata=metadata,
                    group_addr=util.UNASSIGNED_ADDR,
                    virtual_addr=virtual_addr,
                    appkey_index=appkey_index,
                    ttl=ttl,
                    retry_params=retry_params,
                )
                addr_metadata_status_dict.update(addr_metadata_status_pair_dict)
        return addr_metadata_status_dict

    def _add_receivers(self, elem_index: int, receivers: Iterable[FwReceiver]) -> None:
        for idx, receiver in enumerate(receivers):
            try:
                self.lib.btmesh.fw_standalone_updater.add_receiver(
                    elem_index, receiver.server_addr, receiver.fw_index
                )
            except CommandFailedError as e:
                if e.errorcode == SlStatus.BT_MESH_LIMIT_REACHED:
                    raise BtmeshError(
                        BtmeshErrorCode.DFU_CLT_ADD_RECEIVER_FAILED,
                        f"Failed to add receiver (addr=0x{receiver.server_addr:04X}, "
                        f"fw_index={receiver.fw_index}) to FW receiver list because "
                        f"the FW receiver list is full. (max {idx} receivers)",
                    ) from e
                elif e.errorcode == SlStatus.BT_MESH_ALREADY_EXISTS:
                    continue
                else:
                    raise

    def _delete_all_receivers(self, elem_index: int) -> None:
        self.lib.btmesh.fw_standalone_updater.delete_all_receivers(elem_index)

    def _get_fw_standalone_updater_state(self, elem_index: int) -> FwUpdateStep:
        resp = self.lib.btmesh.fw_standalone_updater.get_state(elem_index)
        return FwUpdateStep.from_int(resp.state)

    def _wait_dfu_state_changed(self, timeout_base: int) -> FwUpdateStep:
        max_time = util.dfu_calc_client_timeout(timeout_base, 0)
        state_changed_event = self.lib.wait_event(
            event_selector=self.DFU_STATE_CHANGED_EVENT,
            max_time=max_time,
        )
        state = FwUpdateStatus.from_int(state_changed_event)
        return state

    def _execute_distribution_step(
        self, elem_index: int, retry_params: BGLibExtRetryParams
    ) -> None:
        # Process all events from the event queue to make sure no spurious
        # btmesh_evt_fw_standalone_updater_dist_state_changed events are present
        # in the event queue from previous FW Standalone Update API calls.
        self.lib.wait(0)
        try:
            self.lib.retry_until(
                self.lib.btmesh.fw_standalone_updater.execute_distribution_step,
                elem_index,
                retry_params=retry_params,
                event_selector=self.DFU_STATE_CHANGED_EVENT,
            )
        except CommandFailedError as e:
            # The BT Mesh stack events generated on the NCP node are delayed by
            # the NCP communication and host side processing (e.g. OS) so there
            # is a time interval when the FW Standalone Updater state machine in
            # the BT Mesh stack changed state but the DFU client host code
            # (this script) is not aware of that.
            # If the host tries to call the state specific command again to send
            # BT Mesh Firmware Update messages to the Firmware Update Servers
            # (retry) then the stack rejects it with INVALID_STATE error because
            # it has already changed state.
            if e.errorcode == SlStatus.INVALID_STATE:
                # Process the events in order to avoid leaving the state
                # changed event in the event queue which could interfere
                # with the execution of next distribution steps.
                self.lib.get_events(
                    timeout=None,
                    max_events=None,
                    max_time=retry_params.retry_interval,
                    final_event_count=1,
                    event_selector=self.DFU_STATE_CHANGED_EVENT,
                )
            # The BT Mesh stack processes timeout in the execute_distribution_step
            # calls which means if this function is not called then FW Standalone
            # Updater state machine is stuck. It is essential to continue the
            # processing until the BT Mesh stack FW Standalone Updater state
            # machine reaches a non-active state for example due to timeout.

    def _transfer_blob(
        self,
        elem_index: int,
        blob: Blob,
        chunk_size_pref: int,
        retry_params: BGLibExtRetryParams,
        on_bg_event: Optional[Callable] = None,
    ):
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
                retry_interval=retry_params.retry_interval,
                retry_cmd_interval=retry_params.retry_cmd_interval,
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

    def _start_fw_update(
        self,
        elem_index: int,
        group_addr: int,
        receivers: Iterable[FwReceiver],
        fwid: FWID,
        metadata: bytes,
        blob: Blob,
        timeout_base: int,
        transfer_mode: BlobTransferMode = BlobTransferMode.PUSH,
        virtual_addr: bytes = bytes(),
        multicast_threshold: int = 2,
        appkey_index: int = 0,
        ttl: int = 5,
    ) -> None:
        self.lib.btmesh.fw_standalone_updater.setup(
            elem_index, len(blob.data), blob.id, fwid.to_bytes()
        )
        self.lib.btmesh.fw_standalone_updater.set_metadata(elem_index, metadata)
        self.lib.btmesh.fw_standalone_updater.set_multicast_threshold(
            elem_index, multicast_threshold
        )
        self._delete_all_receivers(elem_index)
        self._add_receivers(elem_index, receivers)
        self.lib.btmesh.fw_standalone_updater.start(
            elem_index,
            appkey_index,
            ttl,
            timeout_base,
            transfer_mode,
            group_addr,
            virtual_addr,
        )

    def _run_fw_update(
        self,
        elem_index: int,
        receivers: Iterable[FwReceiver],
        failed_receivers_info: Iterable[FwReceiverInfo],
        blob: Blob,
        chunk_size_pref: int,
        timeout_base: int,
        ttl: int,
        retry_params: BtmeshRetryParams,
        on_bg_event: Optional[Callable] = None,
    ) -> Tuple[FwUpdateStep, List[FwReceiverInfo]]:
        # If there is at least one LPN in the nodes then the LPN specific retry
        # interval is used instead of the regular one.
        if retry_params.retry_interval != retry_params.retry_interval_lpn:
            server_addrs = [receiver.server_addr for receiver in receivers]
            any_lpn = self.core.any_lpn_in_elem_addrs(server_addrs, skip_local=True)
            retry_params_base = retry_params.to_base(use_interval_lpn=any_lpn)
        else:
            retry_params_base = retry_params.to_base(use_interval_lpn=False)
        retry_params_base.retry_cmd_max = self.calc_retry_cmd_max(
            retry_cmd_interval=retry_params_base.retry_cmd_interval,
            timeout_base=timeout_base,
            ttl=ttl,
        )
        retry_params_base.retry_max = self.calc_retry_max(
            retry_interval=retry_params_base.retry_interval,
            timeout_base=timeout_base,
            ttl=ttl,
        )
        state = self._get_fw_standalone_updater_state(elem_index)
        while state.is_active():
            try:
                if state == FwUpdateStep.TRANSFERRING_IMAGE:
                    self._transfer_blob(
                        elem_index=elem_index,
                        blob=blob,
                        chunk_size_pref=chunk_size_pref,
                        retry_params=retry_params_base,
                        on_bg_event=on_bg_event,
                    )
                    self._wait_dfu_state_changed(timeout_base)
                elif state == FwUpdateStep.WAITING_FOR_APPLY:
                    self.lib.btmesh.fw_standalone_updater.apply(elem_index)
                    self._wait_dfu_state_changed(timeout_base)
                else:
                    self._execute_distribution_step(
                        elem_index=elem_index, retry_params=retry_params_base
                    )
                state = self._get_fw_standalone_updater_state(elem_index)
            except (CommandFailedError, BGLibExtWaitEventError, BtmeshError) as e:
                # The FW Update is terminated abruptly and unexpectedly so the
                # FW Update shall be terminated in the BT Mesh stack as well in
                # order to terminate the FW Standalone Updater state machine.
                # This is essential because the FW Standalone Update state
                # machine of the BT Mesh stack detects timeout during the
                # execute_distribution_step calls in certain state so this API
                # needs to be called for timeout that is why there is an explicit
                # cancellation here.
                self.cancel_fw_update(
                    elem_index=elem_index,
                    timeout_base=timeout_base,
                    ttl=ttl,
                    retry_params=retry_params,
                )
                raise
        receiver_count = len(receivers) + len(failed_receivers_info)
        receivers_info = self.get_receivers(elem_index)
        for rec_info in receivers_info:
            rec_info.receiver_count = receiver_count
        receivers_info.extend(failed_receivers_info)
        state = self._get_fw_standalone_updater_state(elem_index)
        return state, receivers_info

    def fw_update(
        self,
        elem_index: int,
        group_addr: int,
        receivers: Iterable[FwReceiver],
        fwid: FWID,
        metadata: bytes,
        fw_data: bytes,
        timeout_base: int,
        transfer_mode: BlobTransferMode = BlobTransferMode.PUSH,
        chunk_size_pref: int = 53,
        virtual_addr: bytes = bytes(),
        appkey_index: int = 0,
        ttl: int = 5,
        retry_params: Optional[BtmeshMulticastRetryParams] = None,
        on_bg_event: Optional[Callable] = None,
    ) -> Tuple[FwUpdateStep, List[FwReceiverInfo]]:
        if not util.is_iterable(receivers):
            receivers: Iterable[FwReceiver] = [receivers]
        util.validate_ttl(ttl)
        util.validate_appkey_index(appkey_index)
        if virtual_addr:
            util.validate_virtual_label_uuid(virtual_addr)
        if group_addr != util.UNASSIGNED_ADDR:
            util.validate_multicast_address(group_addr)
        if retry_params is None:
            retry_params = self.retry_params_default
        blob_id = os.urandom(Blob.BLOB_ID_LEN)
        blob = Blob(blob_id, fw_data)
        metadata_status_dict = self.check_receivers_metadata(
            elem_index=elem_index,
            receivers=receivers,
            metadata=metadata,
            group_addr=group_addr,
            virtual_addr=virtual_addr,
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
            state = FwUpdateStep.FAILED
            receivers_info = failed_receivers_info
            return state, receivers_info
        self.lib.subscribe(
            self.DFU_STATE_CHANGED_EVENT, self.on_fw_update_state_changed
        )
        try:
            self._start_fw_update(
                elem_index=elem_index,
                group_addr=group_addr,
                receivers=active_receivers,
                fwid=fwid,
                metadata=metadata,
                blob=blob,
                timeout_base=timeout_base,
                transfer_mode=transfer_mode,
                virtual_addr=virtual_addr,
                multicast_threshold=retry_params.multicast_threshold,
                appkey_index=appkey_index,
                ttl=ttl,
            )
            state, receivers_info = self._run_fw_update(
                elem_index=elem_index,
                receivers=active_receivers,
                failed_receivers_info=failed_receivers_info,
                blob=blob,
                chunk_size_pref=chunk_size_pref,
                timeout_base=timeout_base,
                ttl=ttl,
                retry_params=retry_params,
                on_bg_event=on_bg_event,
            )
        finally:
            self.lib.unsubscribe(
                self.DFU_STATE_CHANGED_EVENT, self.on_fw_update_state_changed
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
        return state, receivers_info

    def on_fw_update_state_changed(self, event: BGEvent):
        state = self._get_fw_standalone_updater_state(event.elem_index)
        receivers_info = self.get_receivers(event.elem_index)
        levt = FwUpdateProgressEvent(
            elem_index=event.elem_index,
            dfu_state=state,
            receivers_info=receivers_info,
        )
        self.evtbus.emit(levt)

    def handle_mbt_transfer_progress(self, event: MBTProgressEvent):
        state = self._get_fw_standalone_updater_state(event.elem_index)
        receivers_info = self.get_receivers(event.elem_index)
        levt = FwUpdateProgressEvent(
            elem_index=event.elem_index,
            dfu_state=state,
            receivers_info=receivers_info,
        )
        self.evtbus.emit(levt)

    def get_receivers(self, elem_index: int) -> List[FwReceiverInfo]:
        resp = self.lib.btmesh.fw_standalone_updater.get_state(elem_index)
        receiver_count = resp.total_nodes
        receiver_info_list = []
        for receiver_index in range(receiver_count):
            resp = self.lib.btmesh.fw_standalone_updater.get_node_status_by_index(
                elem_index, receiver_index
            )
            receiver_info = FwReceiverInfo(
                index=receiver_index,
                receiver_count=receiver_count,
                server_addr=resp.address,
                fw_index=resp.fw_index,
                phase=FwReceiverPhase.from_int(resp.retrieved_phase),
                dfu_status=FwUpdateStatus.from_int(resp.update_server_status),
                mbt_status=MBTStatus.from_int(resp.mbt_server_status),
                progress=resp.transfer_progress,
            )
            receiver_info_list.append(receiver_info)
        return receiver_info_list

    def cancel_fw_update(
        self,
        elem_index: int,
        timeout_base: int = 28,
        ttl: int = 5,
        retry_params: Optional[BtmeshRetryParams] = None,
    ):
        state = self._get_fw_standalone_updater_state(elem_index)
        if state == FwUpdateStep.IDLE:
            # The FW Update has already been cancelled
            return
        if state != FwUpdateStep.CANCELLING:
            # If the FW Standalone Update is already in cancelling state then
            # the cancel API shall not be called and the distribution step
            # shall be executed.
            # It could happen if the last cancel operation was aborted unexpectedly
            # on the host side.
            try:
                self.lib.btmesh.fw_standalone_updater.cancel(elem_index)
                state = self._wait_dfu_state_changed(timeout_base)
            except CommandFailedError as e:
                status = SlStatus.from_int(e.errorcode)
                raise BtmeshError(
                    err=BtmeshErrorCode.DFU_CLT_CANCEL_DIST_FAILED,
                    message=(
                        f'Failed to cancel FW update due to "{status.name}" error.',
                    ),
                    errorcode=status,
                )
        if state == FwUpdateStep.IDLE:
            # If the state was COMPLETED or FAILED before the cancel call then
            # the FW Standalone Updater state machine moves into IDLE immediately.
            # Consequently, no distribution step shall be executed.
            return
        # The FW Standalone Updater state machine must be in CANCELLING state
        # and therefore the receiver list is not empty in the BT Mesh stack.
        receivers_info_list = self.get_receivers(elem_index)
        if retry_params is None:
            retry_params = self.retry_params_default
        if retry_params.retry_interval != retry_params.retry_interval_lpn:
            server_addrs = [
                receiver_info.server_addr for receiver_info in receivers_info_list
            ]
            any_lpn = self.core.any_lpn_in_elem_addrs(server_addrs, skip_local=True)
            retry_params_base = retry_params.to_base(use_interval_lpn=any_lpn)
        else:
            retry_params_base = retry_params.to_base(use_interval_lpn=False)
        retry_params_base.retry_cmd_max = self.calc_retry_cmd_max(
            retry_cmd_interval=retry_params_base.retry_cmd_interval,
            timeout_base=timeout_base,
            ttl=ttl,
        )
        retry_params_base.retry_max = self.calc_retry_max(
            retry_interval=retry_params_base.retry_interval,
            timeout_base=timeout_base,
            ttl=ttl,
        )
        self._execute_distribution_step(
            elem_index=elem_index, retry_params=retry_params_base
        )
        state = self._get_fw_standalone_updater_state(elem_index)
        if state != FwUpdateStep.IDLE:
            status = SlStatus.FAIL
            raise BtmeshError(
                err=BtmeshErrorCode.DFU_CLT_CANCEL_DIST_FAILED,
                message=(f'Failed to cancel FW update due to "{status.name}" error.',),
                errorcode=SlStatus.FAIL,
            )
