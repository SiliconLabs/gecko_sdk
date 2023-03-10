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
import math
from typing import Callable, ClassVar, Dict, List, Optional

from bgapi.bglib import BGEvent, CommandFailedError

from bgapix.bglibx import BGLibExt, BGLibExtRetryParams
from bgapix.slstatus import SlStatus

from . import util
from .conf import Configurator
from .db import BtmeshDatabase, Node
from .errors import BtmeshError, BtmeshErrorCode, BtmeshException
from .event import LocalEvent, LocalEventBus

logger = logging.getLogger(__name__)


class BtmeshMBTResumeException(BtmeshException):
    """BT Mesh MBT Resume exception restarts a suspended MBT transfer."""


@enum.unique
class BlobTransferMode(util.BtmeshIntEnum):
    NONE = 0x0
    PUSH = 0x1
    PULL = 0x2
    BOTH = 0x3
    UNKNOWN_VALUE = util.ENUM_UNKNOWN_VALUE


@enum.unique
class MBTStatus(util.BtmeshIntEnum):
    SUCCESS = 0x00
    INVALID_BLOCK_NUMBER = 0x01
    WRONG_BLOCK_SIZE = 0x02
    WRONG_CHUNK_SIZE = 0x03
    INVALID_STATE = 0x04
    INVALID_PARAMETER = 0x05
    WRONG_BLOB_ID = 0x06
    STORAGE_LIMIT = 0x07
    UNSUPPORTED_TRANSFER_MODE = 0x08
    INTERNAL_ERROR = 0x09
    INFORMATION_UNAVAILABLE = 0x0A
    MALFORMED_MESSAGE = 0xFE
    TIMEOUT = 0xFF
    UNKNOWN = 0xFFFF
    UNKNOWN_VALUE = util.ENUM_UNKNOWN_VALUE


class Blob:
    BLOB_ID_LEN = 8

    def __init__(self, id, data):
        self.id = id
        self.data = data

    @property
    def id(self):
        return self._id

    @id.setter
    def id(self, value):
        if len(value) != 8:
            raise ValueError(
                f"Invalid BLOB is size because it shall be {self.BLOB_ID_LEN} "
                f"bytes but it is {len(value)}."
            )
        self._id = value

    @property
    def data(self):
        return self._data

    @data.setter
    def data(self, value):
        self._data = value


@dataclasses.dataclass
class MBTServerFailedEvent(LocalEvent):
    name: ClassVar[str] = "btmesh_levt_mbt_server_failed"
    elem_index: int
    server_addr: int
    error: MBTStatus


@dataclasses.dataclass
class MBTProgressEvent(LocalEvent):
    name: ClassVar[str] = "btmesh_levt_mbt_transfer_progress"
    elem_index: int
    done_bytes: int
    blob_size: int


@dataclasses.dataclass
class MBTServerInfo:
    addr: int
    error: MBTStatus
    timeout: bool


class BlobTransferClient:
    INVALID_BLOCK_SIZE_LOG = 0xFF
    MAX_CHUNK_SIZE_LIMIT = 241
    RETRY_CMD_ERR_CODES = (SlStatus.BUSY, SlStatus.NO_MORE_RESOURCE)

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

    @staticmethod
    def calc_block_size_default(
        blob_size: int,
        blk_size_log_min: int,
        blk_size_log_max: int,
        blk_count_max: int,
        max_chunk_size_min: int,
        max_chunks_min: int,
    ):
        # The block size determine the number of block start and block query
        # phases during BLOB transfer. If the block size is high then it means
        # less block start and query phases (BLOB size / block size).
        # The block start and block query phases are time consuming because the
        # response of each server shall be waited which can be significant when
        # the number of servers is high. It is fairly good strategy to choose
        # the highest possible block size (allowed by servers) because it makes
        # the transfer much faster. The big blocks may lead to big chunks because
        # the minimum chunk size is limited by the selected block size and the
        # maximum number of chunks. If the chunk size is high then it may diminish
        # transfer speed in high noise environments.
        # Note 1: Block query phase is necessary for push transfer.
        # Note 2: The RAM consumption impact of high block size is far greater
        #   on the server side because each server needs to store a whole block
        #   in memory because the order of chunks is not guaranteed.
        blk_size_max_limit = max_chunk_size_min * max_chunks_min
        blk_size_min_limit = math.ceil(blob_size / blk_count_max)
        for blk_size_log in range(blk_size_log_max, blk_size_log_min - 1, -1):
            blk_size = 2**blk_size_log
            if blk_size <= blk_size_max_limit:
                break
        if blk_size < blk_size_min_limit or blk_size_max_limit < blk_size:
            return BlobTransferClient.INVALID_BLOCK_SIZE_LOG
        return blk_size_log

    @staticmethod
    def calc_chunk_size_default(
        blk_size_log: int,
        max_chunk_size_min: int,
        max_chunks_min: int,
        nw_pdu_size: int,
        chunk_size_pref: Optional[int] = 53,
    ):
        # There is a tradeoff between little and big chunks.
        # The normal (non-AE) segmented chunks are able to transfer 12 bytes per
        # advertisement minus the 1 byte opcode and 2 byte chunk number and 4
        # bytes of MIC. This means N regular advertisement is able to transfer
        # 12 x N - 7 bytes of chunk data. If N is a big number then the payload
        # per message converges to 12 but if N is low then the fix 7 byte penalty
        # becomes significant.
        # If there is noise and at least one segment is lost then the whole chunk
        # needs to be retransmitted. Probability of transfer failure is higher
        # for long segmented chunks and it takes more time to retransmit a long
        # chunk. The chunk size can't be arbitrarily low because the max number
        # of chunks per block multiplied by the chunk size shall be greater or
        # equal to block size. The low chunk size leads to more chunks per block
        # which has negative effects when the number of chunks per block exceeds
        # 40 because the BLOB Block Status message becomes segmented which means
        # all servers starts to respond with segmented messages which might have
        # significant impact on the transfer speed.
        # Chunk size with 5 segments is used as preferred chunk size because in
        # that case the (12 x N - 7) / (12 x N) = 88% of the ideal (non-noisy)
        # transfer speed is preserved and 40 x (12 x N - 7) = 2120 -> 2048 (2^N)
        # byte blocks can be used without BLOB Block Status message segmentation.

        # BLOB Chunk Transfer access message: Opcode (1byte) + Chunk number (2 byte)
        ACCESS_CHUNK_PROT_OVERHEAD = 3
        # Total protocol overhead of upper transport layer and access layer
        UPTP_ACCESS_PROT_OVERHEAD = util.UPTP_PROT_OVERHEAD + ACCESS_CHUNK_PROT_OVERHEAD
        # BLOB Chunk Transfer unsegmented access message data size
        ACCESS_CHUNK_DATA_PER_NON_SEG_MSG = (
            util.LOTP_PAYLOAD_PER_UNSEG_MSG - UPTP_ACCESS_PROT_OVERHEAD
        )
        # Total protocol overhead in NW PDU (unsegmented)
        TOTAL_UNSEG_PROT_OVERHEAD = (
            util.NW_MSG_PROT_OVERHEAD
            + util.LOTP_UNSEG_MSG_PROT_OVERHEAD
            + util.UPTP_PROT_OVERHEAD
            + ACCESS_CHUNK_PROT_OVERHEAD
        )
        max_chunk_size_min = min(
            max_chunk_size_min, BlobTransferClient.MAX_CHUNK_SIZE_LIMIT
        )
        blk_size = 2**blk_size_log
        min_chunk_size = math.ceil(blk_size / max_chunks_min)
        if max_chunk_size_min < min_chunk_size:
            # This should not happen if the BLOB transfer servers are configured
            # properly. The max_chunk_size_min is returned because it might work
            # for some servers when the configurations of BLOB transfer servers
            # are different.
            return max_chunk_size_min

        if util.STANDARD_NETWORK_PDU_SIZE < nw_pdu_size:
            # The Silicon Labs BT Mesh over Advertisement Extensions proprietary
            # feature is enabled so the chunk size is calculated to fit into a
            # single AE packet unless the calculated chunk size is not in the
            # allowed chunk size range.
            # The preferred chunk size is ignored if it is possible to send the
            # whole chunk in a single advertisement because it is superior to
            # segmented transmission.
            chunk_size = nw_pdu_size - TOTAL_UNSEG_PROT_OVERHEAD
            if min_chunk_size <= chunk_size <= max_chunk_size_min:
                return chunk_size
            elif max_chunk_size_min < chunk_size:
                return max_chunk_size_min
            else:
                # If AE packet can't be used then the chunk size calculation
                # falls back to standard BT Mesh 1.0 advertisements.
                pass

        if max_chunk_size_min <= (
            2 * util.LOTP_PAYLOAD_PER_SEG_MSG - UPTP_ACCESS_PROT_OVERHEAD
        ):
            if max_chunk_size_min <= ACCESS_CHUNK_DATA_PER_NON_SEG_MSG:
                # If max_chunk_size_min is less than chunk data size which fits
                # into a single segment then the max_chunk_size_min is used as
                # the chunk size.
                chunk_size = max_chunk_size_min
            else:
                # If the max chunk size does not make it possible to fill two
                # segments completely with data then it is not efficient to
                # send segmented messages so unsegmented chunks are used
                # if min_chunk_size makes it possible.
                if min_chunk_size <= ACCESS_CHUNK_DATA_PER_NON_SEG_MSG:
                    chunk_size = ACCESS_CHUNK_DATA_PER_NON_SEG_MSG
                else:
                    chunk_size = max_chunk_size_min
        elif chunk_size_pref < min_chunk_size:
            # If the preferred chunk size is less than the min_chunk_size then
            # chunk size is set to the closest value which results in full chunk
            # segments.
            chunk_size = (
                (
                    (min_chunk_size + UPTP_ACCESS_PROT_OVERHEAD)
                    + util.LOTP_PAYLOAD_PER_SEG_MSG
                    - 1
                )
                // util.LOTP_PAYLOAD_PER_SEG_MSG
            ) * util.LOTP_PAYLOAD_PER_SEG_MSG - UPTP_ACCESS_PROT_OVERHEAD
            if chunk_size < min_chunk_size or max_chunk_size_min < chunk_size:
                # If selected chunk size does not fit into the allowed chunk
                # size range then min_chunk_size is selected.
                chunk_size = min_chunk_size
        elif max_chunk_size_min < chunk_size_pref:
            # If the preferred chunk size is greater than the max_chunk_size_min
            # then chunk size is set to the closest value which results in full
            # chunk segments.
            chunk_size = (
                (max_chunk_size_min + UPTP_ACCESS_PROT_OVERHEAD)
                // util.LOTP_PAYLOAD_PER_SEG_MSG
            ) * util.LOTP_PAYLOAD_PER_SEG_MSG - UPTP_ACCESS_PROT_OVERHEAD
            if (chunk_size < min_chunk_size) or (max_chunk_size_min < chunk_size):
                # If selected chunk size does not fit into the allowed chunk
                # size range then max_chunk_size_min is selected.
                chunk_size = max_chunk_size_min
        else:
            # The preferred chunk size is selected if it fits into the allowed
            # chunk size range.
            chunk_size = chunk_size_pref
        return chunk_size

    def __init__(
        self,
        lib: BGLibExt,
        db: BtmeshDatabase,
        evtbus: LocalEventBus,
        conf: Configurator,
        retry_params_default: BGLibExtRetryParams,
    ):
        self.lib = lib
        self.db = db
        self.conf = conf
        self.evtbus = evtbus
        self.retry_params_default = retry_params_default
        self.calc_block_size = self.calc_block_size_default
        self.calc_chunk_size = self.calc_chunk_size_default
        self.server_infos: Dict[int, MBTServerInfo] = {}

    def set_calc_block_size(self, func):
        if func is None:
            self.calc_block_size = self.calc_block_size_default
        else:
            self.calc_block_size = func

    def set_calc_chunk_size(self, func):
        if func is None:
            self.calc_chunk_size = self.calc_chunk_size_default
        else:
            self.calc_chunk_size = func

    def init(
        self,
        elem_index=0,
        max_servers=8,
        max_blocks=1850,
        max_chunks_per_block=128,
        retry_params_default: BGLibExtRetryParams = None,
    ):
        self.max_servers = max_servers
        self.max_blocks = max_blocks
        self.max_chunks_per_block = max_chunks_per_block
        self.lib.btmesh.mbt_client.init(
            elem_index, max_servers, max_blocks, max_chunks_per_block
        )
        self.set_retry_params_default(retry_params_default)

    def set_retry_params_default(self, retry_params: BGLibExtRetryParams):
        if retry_params:
            self.retry_params_default = copy.copy(retry_params)

    def abort_transfer(self, elem_index: int):
        self.lib.btmesh.mbt_client.abort(elem_index)

    def mbt_procedure(
        self,
        command: Callable,
        *args,
        retry_params: BGLibExtRetryParams = None,
        event_selector: object = None,
        **event_selector_params,
    ):
        try:
            events = self.lib.retry_until(
                command,
                *args,
                **retry_params.to_dict(),
                retry_cmd_err_code=self.RETRY_CMD_ERR_CODES,
                event_selector=event_selector,
                **event_selector_params,
            )
        except CommandFailedError as e:
            # The BT Mesh stack events generated on the NCP node are delayed by
            # the NCP communication and host side processing (e.g. OS) so there
            # is a time interval when the MBT Client model in the BT Mesh stack
            # changed state but the MBT client host code (this script) is not
            # aware of that. If the host MBT Client tries to call the state
            # specific command again to send BT Mesh BLOB Transfer messages to
            # the BLOB Transfer Servers (retry) then the stack rejects it with
            # INVALID_STATE error because it has already changed state.
            # If the expected BT Mesh MBT state change (complete) event is
            # received after the INVALID_STATE error then the MBT transfer can
            # be continued.
            if e.errorcode == SlStatus.INVALID_STATE:
                events = self.lib.get_events(
                    timeout=None,
                    max_events=None,
                    max_time=retry_params.retry_interval,
                    final_event_count=1,
                    event_selector=event_selector,
                    **event_selector_params,
                )
                if not events:
                    raise
            else:
                raise
        return events

    def transfer_blob(
        self,
        blob: Blob,
        elem_index: int = 0,
        appkey_index: int = 0,
        ttl: int = 5,
        timeout_base: int = 3,
        supported_transfer_modes: BlobTransferMode = BlobTransferMode.PUSH,
        group_addr: int = 0,
        virtual_addr: bytes = bytes(),
        chunk_size_pref: int = 53,
        multicast_threshold: int = 2,
        servers: List[int] = None,
        retry_interval: Optional[float] = None,
        retry_cmd_interval: Optional[float] = None,
        on_mbt_bg_event: Optional[Callable] = None,
    ):
        if supported_transfer_modes == BlobTransferMode.NONE:
            err = BtmeshErrorCode.MBT_TRANSFER_MODE_INVALID
            raise BtmeshError(
                err=err,
                message=f"Supported transfer mode shall not be {err.name}.",
                transfer_mode=err,
            )
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
        # Make sure on_mbt_bg_event is a callable in order to avoid constant None
        # check during BLOB transfer.
        if on_mbt_bg_event is None:
            on_mbt_bg_event = lambda event: None

        # NCP Host MBT Client assumes that the MBT Client model is setup by
        # upper layer model on the NCP node when no servers are passed.
        # If the MBT Client model was setup by an upper layer model then the
        # setup API shall not be called.
        if servers:
            self.lib.btmesh.mbt_client.setup(
                elem_index,
                blob.id,
                len(blob.data),
                appkey_index,
                ttl,
                timeout_base,
                supported_transfer_modes,
                group_addr,
                virtual_addr,
                multicast_threshold,
                (addr.to_bytes(2, byteorder="little") for addr in servers),
            )
        else:
            server_idx = 0
            servers = []
            while True:
                try:
                    rsp = self.lib.btmesh.mbt_client.get_server_status(
                        elem_index, server_idx
                    )
                    servers.append(rsp.server_address)
                    server_idx += 1
                except CommandFailedError as e:
                    if e.errorcode == SlStatus.BT_MESH_DOES_NOT_EXIST:
                        break
                    else:
                        raise
        self.elem_index = elem_index
        self.server_infos = {}
        for svr in servers:
            self.server_infos[svr] = MBTServerInfo(svr, MBTStatus.SUCCESS, 0)
        try:
            self.lib.subscribe(
                "btmesh_evt_mbt_client_transfer_complete", self.on_transfer_completed
            )
            self.lib.subscribe(
                "btmesh_evt_mbt_client_server_failed", self.on_server_failed
            )
            self.transfer_blob_run(
                blob=blob,
                elem_index=elem_index,
                supported_transfer_modes=supported_transfer_modes,
                chunk_size_pref=chunk_size_pref,
                retry_params=retry_params,
                on_mbt_bg_event=on_mbt_bg_event,
            )
        finally:
            self.lib.unsubscribe(
                "btmesh_evt_mbt_client_server_failed", self.on_server_failed
            )
            self.lib.unsubscribe(
                "btmesh_evt_mbt_client_transfer_complete", self.on_transfer_completed
            )
        return self.server_infos

    def transfer_blob_run(
        self,
        blob: Blob,
        elem_index: int,
        supported_transfer_modes: BlobTransferMode,
        chunk_size_pref: int,
        retry_params: Optional[BGLibExtRetryParams],
        on_mbt_bg_event: Optional[Callable[[BGEvent], None]],
    ):
        query_evts = self.mbt_procedure(
            self.lib.btmesh.mbt_client.query_information,
            elem_index,
            retry_params=retry_params,
            event_selector="btmesh_evt_mbt_client_query_information_complete",
        )
        query_evt = query_evts[0]
        on_mbt_bg_event(query_evt)
        max_chunk_size_min = min(
            self.MAX_CHUNK_SIZE_LIMIT, query_evt.max_chunk_size_min
        )
        max_chunks_min = min(self.max_chunks_per_block, query_evt.max_chunks_min)
        blk_size_log = self.calc_block_size(
            len(blob.data),
            query_evt.block_size_log_min,
            query_evt.block_size_log_max,
            self.max_blocks,
            max_chunk_size_min,
            max_chunks_min,
        )
        if blk_size_log == self.INVALID_BLOCK_SIZE_LOG:
            blk_size_log = query_evt.block_size_log_max
        nw_pdu_size = self.conf.get_local_network_pdu_size()
        chunk_size = self.calc_chunk_size(
            blk_size_log=blk_size_log,
            max_chunk_size_min=max_chunk_size_min,
            max_chunks_min=max_chunks_min,
            nw_pdu_size=nw_pdu_size,
            chunk_size_pref=chunk_size_pref,
        )
        if supported_transfer_modes == BlobTransferMode.BOTH:
            if query_evt.common_transfer_modes == BlobTransferMode.PULL:
                transfer_mode = BlobTransferMode.PULL
            else:
                transfer_mode = BlobTransferMode.PUSH
        else:
            # It is guaranteed by previous checks that supported transfer
            # mode is not NONE.
            transfer_mode = supported_transfer_modes
        transfer_active = True
        progress_zero_reported = False
        while transfer_active:
            try:
                start_evts = self.mbt_procedure(
                    self.lib.btmesh.mbt_client.start_transfer,
                    elem_index,
                    blk_size_log,
                    transfer_mode.value,
                    retry_params=retry_params,
                    event_selector="btmesh_evt_mbt_client_start_transfer_complete",
                )
                start_evt = start_evts[0]
                logger.info(
                    f"BLOB Transfer is started (blk_size={2**blk_size_log}, "
                    f"transfer_mode={transfer_mode.name.lower()})."
                )
                on_mbt_bg_event(start_evt)
                if not progress_zero_reported:
                    progress_zero_reported = True
                    levt = MBTProgressEvent(elem_index, 0, len(blob.data))
                    self.evtbus.emit(levt)
                while transfer_active:
                    blk_comp = self.send_block(
                        blob=blob,
                        elem_index=elem_index,
                        blk_size_log=blk_size_log,
                        chunk_size=chunk_size,
                        retry_params=retry_params,
                        on_mbt_bg_event=on_mbt_bg_event,
                    )
                    if blk_comp.transfer_complete:
                        logger.info("BLOB transfer completed.")
                        transfer_active = False
            except BtmeshMBTResumeException:
                continue

    def send_block(
        self,
        blob: Blob,
        elem_index: int,
        blk_size_log: int,
        chunk_size: int,
        retry_params: Optional[BGLibExtRetryParams],
        on_mbt_bg_event: Optional[Callable[[BGEvent], None]],
    ):
        block_start_evts = self.mbt_procedure(
            self.lib.btmesh.mbt_client.start_block,
            elem_index,
            chunk_size,
            retry_params=retry_params,
            event_selector="btmesh_evt_mbt_client_start_block_complete",
        )
        block_start_evt = block_start_evts[0]
        logger.info(
            f"Block {block_start_evt.block_number} "
            f"({block_start_evt.block_size} bytes) is started."
        )
        blk_num = block_start_evt.block_number
        blk_size = 2**blk_size_log
        on_mbt_bg_event(block_start_evt)
        while True:
            self.send_chunks(blob, elem_index, on_mbt_bg_event)
            blk_complete_evts = self.mbt_procedure(
                self.lib.btmesh.mbt_client.query_block_status,
                elem_index,
                retry_params=retry_params,
                event_selector="btmesh_evt_mbt_client_query_block_status_complete",
            )
            blk_complete_evt = blk_complete_evts[0]
            blk_done = blk_complete_evt.block_complete
            transfer_done = blk_complete_evt.transfer_complete
            logger.info(
                f"Query block status complete (blk_done={blk_done}, "
                f"transfer_done={transfer_done})."
            )
            on_mbt_bg_event(blk_complete_evt)
            if blk_done:
                if transfer_done:
                    levt = MBTProgressEvent(elem_index, len(blob.data), len(blob.data))
                else:
                    levt = MBTProgressEvent(
                        elem_index, (blk_num + 1) * blk_size, len(blob.data)
                    )
                self.evtbus.emit(levt)
                return blk_complete_evt

    def send_chunks(
        self,
        blob: Blob,
        elem_index: int,
        on_mbt_bg_event: Optional[Callable[[BGEvent], None]],
    ):
        chunks_complete = False
        while not chunks_complete:
            events = self.lib.wait_events(
                event_selector=[
                    "btmesh_evt_mbt_client_send_chunk_request",
                    "btmesh_evt_mbt_client_send_chunks_complete",
                ],
            )
            for event in events:
                if event == "btmesh_evt_mbt_client_send_chunk_request":
                    start_pos = event.offset
                    end_pos = event.offset + event.length
                    logger.info(f"Send chunk [{start_pos},{end_pos})")
                    self.lib.btmesh.mbt_client.send_chunk_request_rsp(
                        elem_index, blob.data[start_pos:end_pos]
                    )
                else:
                    chunks_complete = True
                on_mbt_bg_event(event)

    def on_transfer_completed(self, event: BGEvent):
        if event.elem_index == self.elem_index:
            for info in self.server_infos.values():
                if info.error == MBTStatus.SUCCESS:
                    # If at least one server received the BLOB without errors
                    # then the BLOB transfer is considered successful.
                    return
            raise BtmeshError(
                err=BtmeshErrorCode.MBT_TRANSFER_FAILED,
                message="All BLOB transfer servers are failed.",
                server_infos=self.server_infos.values(),
            )

    def on_server_failed(self, event: BGEvent):
        if event.elem_index == self.elem_index:
            addr = event.server_address
            if addr in self.server_infos:
                mbt_status = MBTStatus.from_int(event.error)
                self.server_infos[addr].error = mbt_status
                self.server_infos[addr].timeout = event.timeout
                logger.warn(
                    f"BLOB Transfer Server 0x{addr:04X} is failed "
                    f"due to {mbt_status.pretty_name}."
                )
                levt = MBTServerFailedEvent(
                    elem_index=self.elem_index,
                    server_addr=addr,
                    error=mbt_status,
                )
                self.evtbus.emit(levt)
                if all(
                    (info.error != MBTStatus.SUCCESS) or (info.timeout != 0)
                    for info in self.server_infos.values()
                ):
                    raise BtmeshError(
                        err=BtmeshErrorCode.MBT_TRANSFER_FAILED,
                        message="All BLOB transfer servers are failed.",
                        server_infos=self.server_infos.values(),
                    )
            else:
                logger.error(f"The {addr} server failed but it does not exists.")
