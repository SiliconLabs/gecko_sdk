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
import copy
import dataclasses
import io
import logging
import signal
from collections import UserList
from threading import Thread
from typing import Callable, Mapping, NamedTuple

from bgapi.bglib import BGEvent, BGLib, CommandFailedError

from bgapix.slstatus import SlStatus

logger = logging.getLogger(__name__)

BGLIBX_API = """<?xml version="1.0" encoding="UTF-8"?>
<api xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:noNamespaceSchemaLocation="api.xsd"
    device_id="0xff" device_name="bglibx">
    <types>
        <type name="errorcode" datatype="uint16" length="2">
            <description>
                SL_STATUS_OK if successful. Error code otherwise.
            </description>
        </type>
        <type datatype="int8" name="int8" length="1">
            <description>Signed 8-bit integer</description>
        </type>
        <type datatype="uint8" name="uint8" length="1">
            <description>Unsigned 8-bit integer</description>
        </type>
        <type datatype="int16" name="int16" length="2">
            <description>Signed 16-bit integer</description>
        </type>
        <type datatype="uint16" name="uint16" length="2">
            <description>Unsigned 16-bit integer</description>
        </type>
        <type datatype="int32" name="int32" length="4">
            <description>Signed 32-bit integer</description>
        </type>
        <type datatype="uint32" name="uint32" length="4">
            <description>Unsigned 32-bit integer</description>
        </type>
        <type datatype="int64" name="int64" length="8">
            <description>Signed 64-bit integer</description>
        </type>
        <type datatype="uint64" name="uint64" length="8">
            <description>Unsigned 64-bit integer</description>
        </type>
        <type datatype="uint8array" name="uint8array" length="1">
            <description>Variable length byte array. The first byte defines the length
            of data that follows, 0 - 255 bytes.</description>
        </type>
        <type datatype="uint16array" name="uint16array" length="2">
            <description>Variable length byte array. The first two bytes of uint16
            type define the length of data that follows, 0 - 65535 bytes.</description>
        </type>
    </types>
    <class name="signal" index="0x00" title="Host Signal class">
        <description>NCP Host signal processing API</description>
        <event name="sync_received" index="0x00">
            <description>Signal received by the NCP host synchronously.
            This event is used to synchronize the signal to the main thread
            event processing.</description>
            <params>
                <param name="signum" type="int32">
                  <description>Signal number of the received signal.</description>
                </param>
            </params>
        </event>
        <event name="async_received" index="0x01">
            <description>Signal received by the NCP host asynchronously.
            This event is not synchronized to main thread event processing so it
            can occur between any two instructions and therefore the NCP host
            shall terminate itself when an exception is raised in an event handler.
            If the event handler returns then the NCP host may not terminate.</description>
            <params>
                <param name="signum" type="int32">
                  <description>Signal number of the received signal.</description>
                </param>
            </params>
        </event>
    </class>
</api>
"""


class BGLibExtWaitEventError(Exception):
    def __init__(self, *args, events=[]):
        super().__init__(*args)
        self.events = events


class BGLibExtSyncSignalException(Exception):
    """Upper layer can raise sync signal exception from bglibx_signal_sync_received
    event handler. The advantage of this exception is that a uniform exception can
    be raised when a sync signal is received."""

    def __init__(self, signum, *args: object) -> None:
        super().__init__(*args)
        self.signum = signum


class EventList(UserList):
    def __init__(self, initlist=None, final_event_cnt=0):
        super().__init__(initlist=initlist)
        self._final_event_cnt = 0

    @property
    def final_event_cnt(self) -> int:
        return self._final_event_cnt

    @final_event_cnt.setter
    def final_event_cnt(self, value: int):
        self._final_event_cnt = value


class BGLibExt(BGLib):
    def is_iterable(obj):
        return hasattr(obj, "__iter__") or hasattr(obj, "__getitem__")

    @staticmethod
    def get_event_name(event):
        return event._str

    def __init__(
        self,
        connection,
        apis,
        event_handler=None,
        response_timeout=1,
        log_id=None,
        event_timeout_res=1,
        sync_signums=(signal.SIGINT,),
    ):
        if not isinstance(apis, (list, tuple)):
            apis = [apis]
        else:
            apis = apis[:]
        apis.append(io.StringIO(BGLIBX_API))
        super().__init__(connection, apis, event_handler, response_timeout, log_id)
        self.event_timeout_res = event_timeout_res
        self._event_name_handlers = {}
        if sync_signums:
            for signum in sync_signums:
                signal.signal(signum, self._signal_handler)

    def _signal_handler(self, signum: signal.Signals, frame):
        ASYNC_SIG_EVT_NAME = "bglibx_evt_signal_async_received"
        async_event = self._create_sig_async_rx_event(signum)
        if ASYNC_SIG_EVT_NAME in self._event_name_handlers:
            for event_handler in self._event_name_handlers.get(ASYNC_SIG_EVT_NAME, []):
                event_handler(async_event)
        sync_event = self._create_sig_sync_rx_event(signum)
        if self.event_handler is None:

            def put():
                self.event_queue.put(sync_event)

            # New thread is essential because signal handler runs on the main
            # thread and it is possible that the main thread is waiting for an
            # event (queue.get operation) when the signal handler is called by
            # the OS which means deadlock when the signal handler tries to put
            # the signal event into the event queue.
            thread = Thread(target=put, name="signal_thread")
            thread.start()
        else:
            self.event_handler(sync_event)

    def _create_sig_sync_rx_event(self, signum):
        apinode = self._get_api_class_event("bglibx", "signal", "sync_received")
        return BGEvent(apinode, [signum])

    def _create_sig_async_rx_event(self, signum):
        apinode = self._get_api_class_event("bglibx", "signal", "async_received")
        return BGEvent(apinode, [signum])

    def _get_api(self, api_name):
        return [a for a in self.apis if a.name == api_name][0]

    def _get_api_class(self, api_name, class_name):
        return self._get_api(api_name)[class_name]

    def _get_api_class_event(self, api_name, class_name, event_name):
        return self._get_api_class(api_name, class_name).events[event_name]

    def get_api_device_id(self, api_name):
        api = self._get_api(api_name)
        return api.device_id

    def get_api_class_index(self, api_name, class_name):
        return self._get_api_class(api_name, class_name).index

    def get_api_class_event_index(self, api_name, class_name, event_name):
        return self._get_api_class_event(api_name, class_name, event_name).index

    def get_api_class_event_ids(self, api_name, class_name, event_name):
        evt = self._get_api_class_event(api_name, class_name, event_name)
        return evt.api_class.api.device_id, evt.api_class.index, evt.index

    def get_event_id(self, api_name, class_name, event_name):
        dev_id, cls_idx, evt_idx = self.get_api_class_event_ids(
            api_name, class_name, event_name
        )
        # Event identifier
        # Bit       7: Event (1) or Command (0)
        # Bit  3 -  6: Device ID
        # Bit 16 - 23: Class index
        # Bit 24 - 32: Event index
        return (evt_idx & 0xFF) << 24 | (cls_idx & 0xFF) << 16 | 0x80 | (dev_id << 3)

    def subscribe(self, event_name, handler):
        handler_list = self._event_name_handlers.setdefault(event_name, [])
        if handler not in handler_list:
            handler_list.append(handler)

    def unsubscribe(self, event_name, handler):
        if (event_name in self._event_name_handlers) and (
            handler in self._event_name_handlers[event_name]
        ):
            self._event_name_handlers[event_name].remove(handler)

    def get_event(self, timeout=0):
        remaining_time = timeout
        while 0 <= remaining_time:
            # Avoid blocking for too long because it blocks signal handler
            if self.event_timeout_res < remaining_time:
                event = super().get_event(self.event_timeout_res)
                remaining_time -= self.event_timeout_res
            else:
                event = super().get_event(remaining_time)
                remaining_time = -1.0
            if event:
                break
        if event is not None:
            event_name = self.get_event_name(event)
            if event_name in self._event_name_handlers:
                for event_handler in self._event_name_handlers.get(event_name, []):
                    event_handler(event)
        return event

    def build_event_selector(
        self, raw_event_selector, param_subs={}, **event_selector_params
    ):
        # The wait_events API accepts any object is derived from EventSelector
        # base class or any object which event selector can be constructed from.
        if EventSelectorPassThrough.is_constructable_from(raw_event_selector):
            event_selector = EventSelectorPassThrough()
        elif isinstance(raw_event_selector, EventSelector):
            event_selector = raw_event_selector
        elif EventSelectorNameParam.is_constructable_from(raw_event_selector):
            event_selector = EventSelectorNameParam(
                raw_event_selector, param_subs=param_subs, **event_selector_params
            )
        elif EventSelectorCallable.is_constructable_from(raw_event_selector):
            event_selector = EventSelectorCallable(raw_event_selector)
        else:
            raise TypeError(f"Invalid event selector type: {type(raw_event_selector)}")
        return event_selector

    def get_events(
        self,
        timeout=0.0,
        max_events=None,
        max_time=None,
        event_selector=None,
        final_event_count=None,
        param_subs={},
        **event_selector_params,
    ):
        if timeout == None and max_events == None and max_time == None:
            raise Exception("One of the arguments has to be other than None")
        event_generator = self.gen_events(
            timeout=timeout,
            max_events=max_events,
            max_time=max_time,
            event_selector=event_selector,
            final_event_count=final_event_count,
            param_subs=param_subs,
            **event_selector_params,
        )
        return [event for event in event_generator]

    def gen_events(
        self,
        timeout=0.0,
        max_events=None,
        max_time=None,
        event_selector=None,
        final_event_count=None,
        param_subs={},
        **event_selector_params,
    ):
        selected_events = []
        current_final_event_count = 0
        evt_sel = self.build_event_selector(
            event_selector, param_subs=param_subs, **event_selector_params
        )
        for event in super().gen_events(
            timeout=timeout, max_events=max_events, max_time=max_time
        ):
            category = evt_sel.categorize(event, selected_events)
            if category in (EventSelector.SELECT_CONTINUE, EventSelector.SELECT_FINAL):
                if not evt_sel.stateless:
                    selected_events.append(event)
                yield event
                if category == EventSelector.SELECT_FINAL:
                    if final_event_count is not None:
                        current_final_event_count += 1
                        if final_event_count <= current_final_event_count:
                            break

    def wait(
        self,
        max_time,
        timeout=None,
        max_events=None,
    ):
        # Wait is a better alternative to sleep because it processes events
        # and calls the subscribed event handlers with the proper events so
        # the application remains responsive.
        # It consumes a bit more CPU cycles than the sleep but most of the
        # time it waits for events to process.
        for _ in self.gen_events(
            timeout=timeout, max_events=max_events, max_time=max_time
        ):
            pass

    def wait_events(
        self,
        event_selector,
        timeout=None,
        max_events=None,
        max_time=10,
        max_time_rst_on_evt=False,
        final_event_count=1,
        keep_all_events=False,
        param_subs={},
        selected_events=EventList(),
        **event_selector_params,
    ) -> EventList:
        if not selected_events:
            # Avoid the modification of default mutable parameter
            selected_events = EventList()
        evt_sel = self.build_event_selector(
            event_selector, param_subs=param_subs, **event_selector_params
        )
        gen_events_max_time = True
        while gen_events_max_time:
            gen_events_max_time = False
            for event in super().gen_events(
                timeout=timeout, max_events=max_events, max_time=max_time
            ):
                category = evt_sel.categorize(event, selected_events)
                if (
                    (category == EventSelector.SELECT_CONTINUE)
                    or (category == EventSelector.SELECT_FINAL)
                    or ((category == EventSelector.IGNORE) and keep_all_events)
                ):
                    selected_events.append(event)
                    if category == EventSelector.SELECT_CONTINUE:
                        if max_time_rst_on_evt:
                            logger.debug("Restart wait events max time.")
                            gen_events_max_time = True
                            break
                    elif category == EventSelector.SELECT_FINAL:
                        selected_events.final_event_cnt += 1
                        if selected_events.final_event_cnt < final_event_count:
                            if max_time_rst_on_evt:
                                logger.debug("Restart wait events max time.")
                                gen_events_max_time = True
                                break
                        else:
                            return selected_events
        # The execution reaches this point if the desired number of final events
        # are not encountered before the timeout or max_time elapsed.
        # If the awaited final event is not encountered then it means something
        # went wrong so an BGLibExtWaitEventError exception is raised.
        # Some events could be selected so those are added to the exception.
        raise BGLibExtWaitEventError(
            "Expected final event is missing.", events=selected_events
        )

    def wait_event(
        self,
        event_selector,
        timeout=None,
        max_events=None,
        max_time=10,
        param_subs={},
        **event_selector_params,
    ):
        return self.wait_events(
            event_selector=event_selector,
            timeout=timeout,
            max_events=max_events,
            max_time=max_time,
            max_time_rst_on_evt=False,
            final_event_count=1,
            keep_all_events=False,
            param_subs=param_subs,
            **event_selector_params,
        )[0]

    def retry_until(
        self,
        command,
        *args,
        retry_max=5,
        retry_interval=1.0,
        retry_int_rst_on_evt=False,
        retry_cmd_max=10,
        retry_cmd_interval=1.0,
        retry_cmd_err_code=[],
        retry_event_selector=None,
        event_selector=None,
        final_event_count=1,
        keep_all_events=False,
        **event_selector_params,
    ):
        if isinstance(retry_cmd_err_code, SlStatus):
            retry_cmd_err_code = [retry_cmd_err_code]
        elif not BGLibExt.is_iterable(retry_cmd_err_code):
            retry_cmd_err_code = [retry_cmd_err_code]
        selected_events = EventList()
        any_cmd_success = False
        last_cmd_failed = False
        prev_sel_evt_cnt = 0
        for retry_count in range(0, retry_max + 1):
            # The command itself might not be successful but it could mean
            # recoverable error so it could make sense to retry is a bit later.
            # For example memory allocation could fail in the stack.
            for retry_cmd_count in range(0, retry_cmd_max + 1):
                try:
                    # The command return value is not checked because an exception
                    # is thrown if it is not zero and the retries are maxed
                    # The arguments shall be packed into the command object
                    response = command(*args)
                    if event_selector is None:
                        # If no event was specified then only the command shall
                        # be repeated so the method shall return here.
                        # The command response is returned in this special case
                        # instead of events.
                        return response
                    # The command was successful so the response contains the
                    # value of command output parameters. A parameter value
                    # substitution dictionary is built from these values which
                    # can be used in event selector to wait for an event with
                    # substituted event parameter values.
                    if response is not None:
                        param_subs = {
                            field: getattr(response, field)
                            for field in response._fields
                        }
                    else:
                        param_subs = {}
                    # Build event_selector once after each successful command.
                    # The event_selector needs to be rebuilt because the
                    # parameter substitution changes when the command returns
                    # different response.
                    evt_selector = self.build_event_selector(
                        event_selector,
                        param_subs=param_subs,
                        **event_selector_params,
                    )
                    # Create an event list after each successful command if the
                    # event_selector is stateless.
                    # Corner case: first command successful but the expected
                    # event is missing or the received event means a recoverable
                    # error. The retry logic calls the command again but it returns
                    # a recoverable error. It is possible that the first command
                    # which was successful triggers some events later when the
                    # new command calls are failing and waiting for timeout.
                    # (retry_cmd_interval)
                    # The events since the last successful commands are kept and
                    # concatenated and therefore no new event list is created
                    # when the command fails.
                    if evt_selector.stateless:
                        selected_events = EventList()
                    any_cmd_success = True
                    last_cmd_failed = False
                    break
                except CommandFailedError as e:
                    last_cmd_failed = True
                    # If the last attempt to execute the command fails or the error
                    # is not recoverable then raise the command error instead of
                    # event error.
                    if (retry_cmd_max <= retry_cmd_count) or (
                        e.errorcode not in retry_cmd_err_code
                    ):
                        raise
                    if any_cmd_success:
                        # If at least one command succeeded before then the
                        # function shall wait for expected events during the
                        # command retry timeout (retry_cmd_interval).
                        # This is essential because the succeeded command might
                        # trigger events later when the retry logic calls the
                        # command again but retry command fails.
                        # This is a corner case when the command starts slow
                        # async processes in the stack but the retry interval
                        # is low enough to call the command again before the
                        # processes started by the last command is finished.
                        # Example: segmented message transfer
                        try:
                            prev_sel_evt_cnt = len(selected_events)
                            selected_events = self.wait_events(
                                evt_selector,
                                max_time=retry_cmd_interval,
                                max_time_rst_on_evt=retry_int_rst_on_evt,
                                final_event_count=final_event_count,
                                keep_all_events=keep_all_events,
                                param_subs=param_subs,
                                selected_events=selected_events,
                                **event_selector_params,
                            )
                            break
                        except BGLibExtWaitEventError as e:
                            # Some events are missing so command retry is required
                            logger.warning("Retry due to recoverable command error.")
                            continue
                    else:
                        # If the command error code is a recoverable error
                        # then wait some time before the command is called again
                        # (e.g. resource limitation)
                        self.wait(retry_cmd_interval)
                        logger.warning("Retry due to recoverable command error.")
                        continue
            if not last_cmd_failed:
                try:
                    prev_sel_evt_cnt = len(selected_events)
                    selected_events = self.wait_events(
                        evt_selector,
                        max_time=retry_interval,
                        max_time_rst_on_evt=retry_int_rst_on_evt,
                        final_event_count=final_event_count,
                        keep_all_events=keep_all_events,
                        param_subs=param_subs,
                        selected_events=selected_events,
                        **event_selector_params,
                    )
                except BGLibExtWaitEventError as e:
                    if retry_count < retry_max:
                        # The retry_until assumes recoverable error when no
                        # event is received, and consequently it performs a
                        # retry (e.g. the event is missing due to packet loss)
                        logger.warning("Retry due to missing events.")
                        selected_events = e.events
                        continue
                    else:
                        # Maximum number of retry is reached so the same exception
                        # is raised again
                        raise
            # If the event_selector is stateless then all events are new
            # events and prev_sel_evt_cnt is set to 0.
            new_events = selected_events[prev_sel_evt_cnt:]
            # If the expected events mean a recoverable error then it
            # shall be retried to receive the proper event with proper
            # parameters.
            # If the number of retry attempts are maxed but recoverable
            # error occurs again then the events are returned because a
            # final event was found so it is the responsibility of the
            # caller to evaluate it.
            # The recoverable error (retry_event_selector) detection shall
            # be performed over the new events only otherwise it could lead
            # to constants retry until the retry count is maxed because the
            # retry triggering event could be still in selected_events when
            # the event_selector is not stateless because events are
            # accumulated in each retry iteration.
            if (retry_event_selector is not None) and (retry_count < retry_max):
                retry_evt_sel = self.build_event_selector(
                    retry_event_selector, param_subs=param_subs
                )
                if any(
                    EventSelector.IGNORE != retry_evt_sel.categorize(event)
                    for event in new_events
                ):
                    logger.warning("Retry due to recoverable event error.")
                    continue
            # The required events are found which shall be returned
            return selected_events



@dataclasses.dataclass
class BGLibExtRetryParams:
    retry_max: int
    retry_interval: float
    retry_cmd_max: int
    retry_cmd_interval: float

    def to_dict(self):
        return dataclasses.asdict(self)

    def __post_init__(self):
        if self.retry_max < 0:
            raise ValueError(f"The retry max is negative.")
        if self.retry_interval < 0.0:
            raise ValueError(f"The retry interval is negative.")
        if self.retry_cmd_max < 0:
            raise ValueError(f"The retry command max is negative.")
        if self.retry_cmd_interval < 0.0:
            raise ValueError(f"The retry command interval is negative.")


class EventSelector(abc.ABC):
    SELECT_FINAL = 0
    SELECT_CONTINUE = 1
    IGNORE = 2

    @abc.abstractmethod
    def categorize(self, event, selected_events=[]):
        return self.SELECT_FINAL

    @abc.abstractproperty
    def stateless(self):
        return True


class EventParamValues(UserList):
    """Event selector parameter values. This class is created to avoid using
    common iterables in EventSelectorNameParam in order to differentiate multiple
    options from iterable values."""

    def __init__(self, initlist=None):
        super().__init__(initlist=initlist)


class EventSelectorNameParam(EventSelector):
    @staticmethod
    def is_constructable_from(raw_event_selector):
        if isinstance(raw_event_selector, str):
            return True
        elif BGLibExt.is_iterable(raw_event_selector):
            if all(isinstance(evt_name, str) for evt_name in raw_event_selector):
                if isinstance(raw_event_selector, Mapping):
                    for evt_name in raw_event_selector:
                        event_params = raw_event_selector[evt_name]
                        if event_params is None:
                            event_params = {}
                        if not isinstance(event_params, Mapping):
                            return False
                        elif not all(isinstance(name, str) for name in event_params):
                            return False
                    return True
                else:
                    return True
            else:
                return False
        else:
            return False

    @classmethod
    def is_param_name_keyword(cls, param_name: str):
        return param_name.startswith("#")

    def __init__(self, event_names, param_subs={}, **event_params):
        # It shall be guaranteed that the event_names is not modified in this
        # function to make it reusable for other calls as well. The parameter
        # substitutions could modify event_names parameter values so the content
        # of event_names is deep copied when param_subs is not empty.
        if param_subs:
            event_names = copy.deepcopy(event_names)
        self.event_name_dict = {}
        if not self.is_constructable_from(event_names):
            raise TypeError(
                f"{self.__class__.__name__} is not constructable "
                + f"from {event_names}."
            )
        if isinstance(event_names, str):
            self.event_name_dict[event_names] = event_params
        elif BGLibExt.is_iterable(event_names):
            if isinstance(event_names, Mapping):
                for evt_name in event_names:
                    evt_params = event_names[evt_name]
                    if evt_params:
                        self.event_name_dict[evt_name] = evt_params
                    else:
                        self.event_name_dict[evt_name] = {}
            else:
                for evt_name in event_names:
                    self.event_name_dict[evt_name] = event_params
        else:
            raise TypeError(
                f"{self.__class__.__name__} is not constructable "
                + f"from {event_names}."
            )
        self._stateless = True
        for evt_name, evt_params in self.event_name_dict.items():
            for param_name, param_values in evt_params.items():
                if self.is_param_name_keyword(param_name):
                    continue
                if not isinstance(param_values, EventParamValues):
                    evt_params[param_name] = EventParamValues((param_values,))
            if "#unique" in evt_params:
                self._stateless = False
                if isinstance(evt_params["#unique"], str):
                    evt_params["#unique"] = (evt_params["#unique"],)
                elif isinstance(evt_params["#unique"], tuple):
                    for unique_field in evt_params["#unique"]:
                        if not isinstance(unique_field, str):
                            raise TypeError(
                                f"The #unique parameter value of {evt_name} "
                                f"event in {self.__class__.__name__} shall be "
                                f"str or tuple[str]."
                            )
                else:
                    raise TypeError(
                        f"The #unique parameter value of {evt_name} "
                        f"event in {self.__class__.__name__} shall be "
                        f"str or tuple[str]."
                    )
        self.resolve_event_params(param_subs)

    @property
    def stateless(self):
        return self._stateless

    def resolve_event_params(self, param_subs):
        for event_name in self.event_name_dict:
            for param_name, param_values in self.event_name_dict[event_name].items():
                if self.is_param_name_keyword(param_name):
                    continue
                for idx, param_value in enumerate(param_values):
                    if isinstance(param_value, str):
                        param_value = param_value.strip()
                        if param_value[0] == "$":
                            param_value = param_subs[param_value[1:]]
                        self.event_name_dict[event_name][param_name][idx] = param_value

    def categorize(self, event, selected_events=[]):
        event_name = BGLibExt.get_event_name(event)
        # If the event name is not expected then it shall be ignored
        if event_name not in self.event_name_dict:
            return self.IGNORE
        # If no parameter values are specified for an event name then it is a
        # final selected event
        if not self.event_name_dict[event_name]:
            return self.SELECT_FINAL
        expected_event_params = self.event_name_dict[event_name]
        event_params_match_list = [
            (getattr(event, param_name) in param_values)
            for param_name, param_values in expected_event_params.items()
            if not self.is_param_name_keyword(param_name)
        ]
        # If there is only a single #final entry in the expected_event_params
        # then the event_params_match_list is an empty list but all() function
        # return True when it is called with an empty iterable which means the
        # event is selected
        if all(event_params_match_list):
            if expected_event_params.get("#final", True):
                unique_param_tuple = expected_event_params.get("#unique", None)
                if unique_param_tuple:
                    if self.is_duplicate_event(
                        event, unique_param_tuple, selected_events
                    ):
                        return self.IGNORE
                    else:
                        return self.SELECT_FINAL
                return self.SELECT_FINAL
            else:
                # If the special #final entry is added to the expected params
                # and it is false then the processed event is not the final one
                return self.SELECT_CONTINUE
        else:
            return self.IGNORE

    def is_duplicate_event(self, event, unique_param_tuple, selected_events):
        duplicate = False
        for sel_event in selected_events:
            event_name = BGLibExt.get_event_name(event)
            sel_event_name = BGLibExt.get_event_name(sel_event)
            if event_name == sel_event_name:
                duplicate = all(
                    getattr(event, unique_param_name)
                    == getattr(sel_event, unique_param_name)
                    for unique_param_name in unique_param_tuple
                )
                if duplicate:
                    break
        return duplicate

    def __repr__(self):
        return f"{self.__class__.__name__}({self.event_name_dict})"


class EventSelectorCallable(EventSelector):
    @staticmethod
    def is_constructable_from(raw_event_selector):
        return isinstance(raw_event_selector, Callable)

    def __init__(self, callable, *args, **kwargs):
        super().__init__()
        self.callable = callable
        self.args = args
        self.kwargs = kwargs

    @property
    def stateless(self):
        return False

    def categorize(self, event, selected_events=[]):
        return self.callable(event, selected_events, *self.args, *self.kwargs)


class EventSelectorPassThrough(EventSelector):
    @staticmethod
    def is_constructable_from(raw_event_selector):
        return raw_event_selector is None

    def __init__(self, *args, **kwargs):
        super().__init__()

    @property
    def stateless(self):
        return True

    def categorize(self, event, selected_events=[]):
        return self.SELECT_CONTINUE
