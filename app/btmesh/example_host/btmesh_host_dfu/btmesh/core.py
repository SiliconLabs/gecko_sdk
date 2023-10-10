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


import abc
import dataclasses
import functools
import logging
import time
from collections import UserList
from typing import Callable, Dict, Iterable, List, Optional, Type, Union

from bgapi.bglib import BGEvent, CommandFailedError
from bgapix.bglibx import (BGLibExt, BGLibExtWaitEventError, EventSelector,
                           EventSelectorComposite)
from bgapix.slstatus import SlStatus

from . import util
from .db import DCD, BtmeshDatabase, Node
from .event import (FactoryResetEvent, LocalEvent, LocalEventBus,
                    NCPComOpenEvent)
from .util import BtmeshIntEnum, BtmeshMulticastRetryParams

logger = logging.getLogger(__name__)


class BtmeshAddressList(UserList):
    def __init__(self, initlist=None, group_addr: Optional[int] = None):
        if not ((group_addr is None) or (group_addr == util.UNASSIGNED_ADDR)):
            util.validate_multicast_address(group_addr)
        super().__init__(initlist)
        for addr in self.data:
            util.validate_unicast_address(addr)
        if group_addr is None:
            self.group_addr = util.UNASSIGNED_ADDR
        else:
            self.group_addr = group_addr


class BtmeshStatusErrorClass(BtmeshIntEnum):
    SUCCESS = 0
    COMMAND_ERROR = 1
    TIMEOUT = 2
    FAILURE = 3
    RECOVERABLE_ERROR = 4


@dataclasses.dataclass
class BtmeshBaseStatus(abc.ABC):
    command_result: SlStatus

    @abc.abstractclassmethod
    def create_from_events(
        cls, db: BtmeshDatabase, events: Iterable[BGEvent]
    ) -> "BtmeshBaseStatus":
        raise NotImplementedError(
            f"The create_from_events method of {cls.__name__} is abstract."
        )

    @abc.abstractclassmethod
    def create_command_error(
        cls, db: BtmeshDatabase, addr: int, command_result: SlStatus
    ) -> "BtmeshBaseStatus":
        raise NotImplementedError(
            f"The create_command_error method of {cls.__name__} is abstract."
        )

    @abc.abstractclassmethod
    def create_timeout(cls, db: BtmeshDatabase, addr: int) -> "BtmeshBaseStatus":
        raise NotImplementedError(
            f"The create_timeout method of {cls.__name__} is abstract."
        )

    @abc.abstractmethod
    def get_error_class(self) -> BtmeshStatusErrorClass:
        raise NotImplementedError(
            f"The get_error_class method of {self.__class__.__name__} is abstract."
        )

    @abc.abstractmethod
    def get_addr(self) -> int:
        raise NotImplementedError(
            f"The get_addr method of {self.__class__.__name__} is abstract."
        )

    def is_success(self) -> bool:
        return self.get_error_class() == BtmeshStatusErrorClass.SUCCESS

    def is_command_error(self) -> bool:
        return self.get_error_class() == BtmeshStatusErrorClass.COMMAND_ERROR

    def is_timeout(self) -> bool:
        return self.get_error_class() == BtmeshStatusErrorClass.TIMEOUT

    def is_failure(self) -> bool:
        return self.get_error_class() == BtmeshStatusErrorClass.FAILURE

    def is_recoverable_error(self) -> bool:
        return self.get_error_class() == BtmeshStatusErrorClass.RECOVERABLE_ERROR

    def any_error(self) -> bool:
        return not self.is_success()


class EventSelectorMulticastComposite(EventSelectorComposite):
    def __init__(
        self,
        db: BtmeshDatabase,
        raw_child_event_selector,
        raw_child_event_selector_params: Dict,
        status_class: Type[BtmeshBaseStatus],
        remaining_addrs: List[int],
        addr_status_dict: Dict[int, BtmeshBaseStatus],
        addr_filter_list: List[int] = None,
    ):
        self.db = db
        super().__init__(
            raw_child_event_selector=raw_child_event_selector,
            raw_child_event_selector_params=raw_child_event_selector_params,
        )
        self.status_class = status_class
        self.remaining_addrs = remaining_addrs
        self.addr_status_dict = addr_status_dict
        if addr_filter_list is None:
            # Empty list is not a default parameter because the content of the
            # list is not modified between function calls.
            # Empty list means no filtering.
            self.addr_filter_list = []
        else:
            self.addr_filter_list = addr_filter_list

        self.status_events = []

    @property
    def stateless(self):
        # Stateless means that the event selector doesn't need the previous
        # selected events for categorization. The EventSelectorMulticastComposite
        # is stateful because it needs the previous event because some BT Mesh
        # status messages are reported in multiple events.
        return False

    def categorize(self, event, selected_events=[]):
        # The child_event_selector shall report SELECT_FINAL when all related
        # events which belong to the response from a specific source address is
        # processed.
        # Note: BT Mesh status message data might be reported in multiple events.
        category = self.child_event_selector.categorize(event, selected_events)
        if category == EventSelector.SELECT_FINAL:
            self.status_events.append(event)
            status: BtmeshBaseStatus = self.status_class.create_from_events(
                self.db,
                self.status_events,
            )
            self.status_events.clear()
            addr = status.get_addr()
            if self.addr_filter_list and (addr not in self.addr_filter_list):
                # The BT Mesh status message is not the expected one but the
                # SELECT_CONTINUE is returned to restart the retry timer because
                # a status message is received as response from a node element.
                return EventSelector.SELECT_CONTINUE
            if addr in self.addr_status_dict:
                prev_status = self.addr_status_dict[addr]
                if (
                    prev_status.is_recoverable_error()
                    or prev_status.is_timeout()
                    or (prev_status.any_error() and status.is_success())
                    or (prev_status.any_error() and status.is_failure())
                ):
                    self.addr_status_dict[addr] = status
            elif addr in self.remaining_addrs:
                # It is possible that many node element models are subscribed to
                # the same group address but only a subset of them is specified
                # as the target of the send_until procedure.
                # The send_until returns the status objects only for the specified
                # node elements otherwise it could lead inconsistencies because
                # the send_until can't guarantee to return status objects for
                # those node elements which aren't specified.
                self.addr_status_dict[addr] = status

            if addr in self.remaining_addrs and (
                status.is_success() or status.is_failure()
            ):
                # This is the first response from the specific source address.
                # The category isn't modified which means SELECT_FINAL is returned.
                self.remaining_addrs.remove(addr)
            else:
                # Multiple response from the same source address shall be counted
                # once, and therefore SELECT_CONTINUE is returned from the second
                # occurrence and onwards.
                # If the status from the source address means a recoverable error
                # or timeout then it shall be considered as a non-final event.
                # The selection is not essential in the wait_events function
                # because this EventSelector stores the events internally but
                # it is critical to return SELECT_CONTINUE to enable the
                # retry_int_rst_on_evt feature of wait_events.
                category = EventSelector.SELECT_CONTINUE
        elif category == EventSelector.SELECT_CONTINUE:
            # The child event selector is responsible to collect events which
            # belongs to the same BT Mesh status message and therefore the
            # the retry timer shall be restarted when the whole event is received.
            self.status_events.append(event)
            category = EventSelector.IGNORE
        return category


class DCDIf:
    def __init__(self, get_dcd: Callable[[Node], DCD]):
        self._get_dcd = get_dcd

    def get_dcd(self, node: Node) -> DCD:
        return self._get_dcd(node)


class BtmeshCore:
    def __init__(
        self,
        lib: BGLibExt,
        db: BtmeshDatabase,
        evtbus: LocalEventBus,
    ) -> None:
        self.lib = lib
        self.db = db
        self.evtbus = evtbus
        self._dcdif = None

    @property
    def dcdif(self) -> DCDIf:
        return self._dcdif

    @dcdif.setter
    def dcdif(self, value: DCDIf) -> None:
        self._dcdif = value

    def add_scan_event_filters(self):
        self.lib.add_event_filter("bt", "scanner", "scan_report")
        self.lib.add_event_filter("bt", "scanner", "legacy_advertisement_report")
        self.lib.add_event_filter("bt", "scanner", "extended_advertisement_report")

    def remove_scan_event_filters(self):
        self.lib.remove_event_filter("bt", "scanner", "scan_report")
        self.lib.remove_event_filter("bt", "scanner", "legacy_advertisement_report")
        self.lib.remove_event_filter("bt", "scanner", "extended_advertisement_report")

    def add_common_event_filters(self):
        # Filter frequent but non-relevant events to improve performance and
        # improve BG buffer utilization in the BT and BT Mesh stacks
        self.add_scan_event_filters()
        self.lib.add_event_filter("bt", "advertiser", "timeout")

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
        self.lib.reset_event_filter()
        # It is important to filter frequent and unnecessary event before the
        # NCP device reset to minimize the chance of reset during event transmit
        self.add_common_event_filters()
        # Emit NCP communication open event
        levt = NCPComOpenEvent()
        self.evtbus.emit(levt)

    def on_system_boot(self, boot_event):
        """The application or upper layer shall call this function when boot
        event occurs in order to process the boot_event. The upper layer needs
        to handle the boot event in order to decide how to stop its current
        activities when unexpected system reset occurs and to initialize
        properly its internal state.
        """
        self.process_system_boot_event(boot_event)
        self.add_common_event_filters()

    def close(self):
        self.lib.close()

    def is_lpn(self, node: Node):
        dcd = self.dcdif.get_dcd(node)
        return dcd.lpn

    def any_lpn(self, nodes: Iterable[Node], skip_local: bool = True) -> bool:
        for node in nodes:
            if skip_local:
                if node.uuid == self.db.prov_uuid:
                    continue
            if self.is_lpn(node):
                return True
        return False

    def any_lpn_in_elem_addrs(
        self, elem_addrs: Iterable[int], skip_local: bool = True
    ) -> bool:
        nodes_dict = {}
        for addr in elem_addrs:
            util.validate_unicast_address(addr)
            node = self.db.get_node_by_elem_addr(addr)
            nodes_dict[node.prim_addr] = node
        return self.any_lpn(nodes_dict.values(), skip_local=skip_local)

    def send_until(
        self,
        cmd: Callable,
        *args,
        event_selector,
        status_class: Type[BtmeshBaseStatus],
        retry_int_rst_on_evt: bool = True,
        retry_params: BtmeshMulticastRetryParams = None,
        retry_cmd_err_code: Union[SlStatus, List[SlStatus]] = [],
        raise_cmd_error: bool = True,
        **event_selector_params,
    ) -> Dict[int, BtmeshBaseStatus]:
        assert isinstance(retry_params, BtmeshMulticastRetryParams)
        if not util.is_iterable(retry_cmd_err_code):
            retry_cmd_err_code = [retry_cmd_err_code]
        if not issubclass(status_class, BtmeshBaseStatus):
            raise TypeError(
                f"The status_class parameter of send_until method shall be the "
                f"subclass of BtmeshBaseStatus but it is {status_class.__name__}."
            )
        addr_list_indexes = []
        addr_args_idx = 0
        addr_status_dict: Dict[int, BtmeshBaseStatus] = {}
        remaining_addrs: List[int] = []
        for idx, arg in enumerate(args):
            if isinstance(arg, BtmeshAddressList):
                addr_args_idx = idx
                addr_list_indexes.append(idx)
        if len(addr_list_indexes) != 1:
            if len(addr_list_indexes) == 0:
                err_msg_ext = "there is none"
            else:
                indexes_str = ", ".join(map(str, addr_list_indexes))
                err_msg_ext = f"there is more than one (indexes: {indexes_str})"
            raise TypeError(
                f"One and only one element of args parameter of send_until shall "
                f"have {BtmeshAddressList.__name__} type but {err_msg_ext}."
            )
        addr_list: BtmeshAddressList = args[addr_args_idx]
        remaining_addrs = list(addr_list)
        if not len(remaining_addrs):
            return {}
        multicast_event_selector = EventSelectorMulticastComposite(
            raw_child_event_selector=event_selector,
            raw_child_event_selector_params=event_selector_params,
            status_class=status_class,
            remaining_addrs=remaining_addrs,
            addr_status_dict=addr_status_dict,
            db=self.db,
        )
        if (
            addr_list.group_addr is not None
            and addr_list.group_addr != util.UNASSIGNED_ADDR
            and retry_params.multicast_threshold
            and retry_params.multicast_threshold <= len(remaining_addrs)
        ):
            # Shallow copy is enough because only one element is replaced.
            group_addr_args = list(args)
            group_addr_args[addr_args_idx] = addr_list.group_addr
            cmd_partial = functools.partial(cmd, *group_addr_args)

            unicast_retry_required = self._send_group_until(
                cmd_partial,
                addr_list=addr_list,
                multicast_event_selector=multicast_event_selector,
                retry_int_rst_on_evt=retry_int_rst_on_evt,
                retry_params=retry_params,
                retry_cmd_err_code=retry_cmd_err_code,
                raise_cmd_error=raise_cmd_error,
            )
            if not unicast_retry_required:
                return addr_status_dict
        self._send_each_until(
            cmd,
            args,
            addr_args_idx=addr_args_idx,
            multicast_event_selector=multicast_event_selector,
            retry_int_rst_on_evt=retry_int_rst_on_evt,
            retry_params=retry_params,
            retry_cmd_err_code=retry_cmd_err_code,
            raise_cmd_error=raise_cmd_error,
        )
        return addr_status_dict

    def _send_group_until(
        self,
        cmd_partial,
        addr_list: BtmeshAddressList,
        multicast_event_selector: EventSelectorMulticastComposite,
        retry_int_rst_on_evt: bool,
        retry_params: BtmeshMulticastRetryParams,
        retry_cmd_err_code: Union[SlStatus, List[SlStatus]],
        raise_cmd_error: bool = True,
    ) -> bool:
        remaining_addrs = multicast_event_selector.remaining_addrs
        addr_status_dict = multicast_event_selector.addr_status_dict
        status_class = multicast_event_selector.status_class

        unicast_retry_required = False
        # Sanity check for multicast threshold.
        # This function shall not be called when the multicast is disabled by
        # setting multicast_threshold to zero or when the number of remaining
        # addresses is less than the multicast_threshold.
        assert retry_params.multicast_threshold
        assert retry_params.multicast_threshold <= len(remaining_addrs)
        # If there is at least one LPN in the nodes then the LPN specific retry
        # interval is used instead of the regular one.
        if retry_params.retry_interval != retry_params.retry_interval_lpn:
            any_lpn = self.any_lpn_in_elem_addrs(remaining_addrs, skip_local=True)
            base_retry_params = retry_params.to_base(use_interval_lpn=any_lpn)
        else:
            base_retry_params = retry_params.to_base(use_interval_lpn=False)
        try:
            multicast_threshold = retry_params.multicast_threshold
            final_event_count = len(remaining_addrs)
            soft_final_event_count = len(remaining_addrs) - multicast_threshold + 1
            soft_final_event_proc_time = base_retry_params.retry_interval
            self.lib.retry_until(
                cmd_partial,
                retry_params=base_retry_params,
                retry_int_rst_on_evt=retry_int_rst_on_evt,
                retry_cmd_err_code=retry_cmd_err_code,
                event_selector=multicast_event_selector,
                final_event_count=final_event_count,
                soft_final_event_count=soft_final_event_count,
                soft_final_event_proc_time=soft_final_event_proc_time,
                keep_all_events=False,
            )
            if len(remaining_addrs):
                unicast_retry_required = True
        except CommandFailedError as e:
            if raise_cmd_error:
                raise
            for addr in addr_list:
                if addr not in addr_status_dict:
                    status = status_class.create_command_error(
                        self.db, addr, e.errorcode
                    )
                    addr_status_dict[addr] = status
        except BGLibExtWaitEventError as e:
            for addr in addr_list:
                if addr not in addr_status_dict:
                    status = status_class.create_timeout(self.db, addr)
                    addr_status_dict[addr] = status
            if retry_params.auto_unicast:
                unicast_retry_required = True
        return unicast_retry_required

    def _send_each_until(
        self,
        cmd,
        args,
        addr_args_idx: int,
        multicast_event_selector: EventSelectorMulticastComposite,
        retry_int_rst_on_evt: bool,
        retry_params: BtmeshMulticastRetryParams,
        retry_cmd_err_code: Union[SlStatus, List[SlStatus]],
        raise_cmd_error: bool = True,
    ) -> None:
        remaining_addrs = multicast_event_selector.remaining_addrs
        addr_status_dict = multicast_event_selector.addr_status_dict
        status_class = multicast_event_selector.status_class

        # The remaining_addrs is copied because the original is modified during
        # the iteration when response is received from an element address.
        for addr in list(remaining_addrs):
            unicast_addr_args = list(args)
            unicast_addr_args[addr_args_idx] = addr
            cmd_partial = functools.partial(cmd, *unicast_addr_args)
            # If the unicast address belongs to a Low Power Node then the LPN
            # specific retry interval is used instead of the regular one.
            if retry_params.retry_interval != retry_params.retry_interval_lpn:
                any_lpn = self.any_lpn_in_elem_addrs(remaining_addrs, skip_local=True)
                base_retry_params = retry_params.to_base(use_interval_lpn=any_lpn)
            else:
                base_retry_params = retry_params.to_base(use_interval_lpn=False)
            # The unicast send might follow the multicast send quite soon which
            # means some responses might be received sporadically because the
            # corresponding status message is sent later or it needs multiple
            # hops to be received.
            # The filter is set to process only the expected responses.
            multicast_event_selector.addr_filter_list.clear()
            multicast_event_selector.addr_filter_list.append(addr)
            try:
                self.lib.retry_until(
                    cmd_partial,
                    retry_params=base_retry_params,
                    retry_int_rst_on_evt=retry_int_rst_on_evt,
                    retry_cmd_err_code=retry_cmd_err_code,
                    event_selector=multicast_event_selector,
                    final_event_count=1,
                    soft_final_event_count=None,
                    soft_final_event_proc_time=None,
                    keep_all_events=False,
                )
            except CommandFailedError as e:
                if raise_cmd_error:
                    raise
                if addr not in addr_status_dict:
                    status = status_class.create_command_error(
                        self.db, addr, e.errorcode
                    )
                    addr_status_dict[addr] = status
            except BGLibExtWaitEventError as e:
                if addr not in addr_status_dict:
                    status = status_class.create_timeout(self.db, addr)
                    addr_status_dict[addr] = status


class BtmeshComponent:
    def __init__(self, core: BtmeshCore) -> None:
        self._core = core

    @property
    def core(self) -> Optional[BtmeshCore]:
        return self._core

    @core.setter
    def core(self, value) -> None:
        self._core = value

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
