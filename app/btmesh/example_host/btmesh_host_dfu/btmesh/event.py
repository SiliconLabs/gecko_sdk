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
from typing import ClassVar


@dataclasses.dataclass
class LocalEvent:
    name: ClassVar[str] = "INVALID"

    def __eq__(self, other) -> bool:
        if isinstance(other, str):
            return self.name == other
        elif isinstance(other, self.__class__):
            return dataclasses.astuple(self) == dataclasses.astuple(other)
        else:
            return False

    def __post_init__(self, *args, **kwargs) -> None:
        if not self.name.startswith("btmesh_levt_"):
            raise ValueError('Local event name shall start with "btmesh_levt" prefix.')


class LocalEventBus:
    def __init__(self) -> None:
        self._local_event_handlers = {}

    def subscribe(self, event_name: str, handler) -> None:
        if not isinstance(event_name, str):
            raise TypeError("The event_name shall be str.")
        if event_name.startswith("btmesh_levt"):
            handler_list = self._local_event_handlers.setdefault(event_name, [])
            if handler not in handler_list:
                handler_list.append(handler)
        else:
            raise ValueError(
                f"Subscription to non-local event failed because "
                f"{self.__class__.__name__} processes (btmesh_levt) "
                f"local events only."
            )

    def unsubscribe(self, event_name: str, handler) -> None:
        if not isinstance(event_name, str):
            raise TypeError("The event_name shall be str.")
        if event_name.startswith("btmesh_levt"):
            if (event_name in self._local_event_handlers) and (
                handler in self._local_event_handlers[event_name]
            ):
                self._local_event_handlers[event_name].remove(handler)
        else:
            raise ValueError(
                f"Unsubscription from non-local event failed because "
                f"{self.__class__.__name__} processes (btmesh_levt) "
                f"local events only."
            )

    def emit(self, event: LocalEvent) -> None:
        if not isinstance(event, LocalEvent):
            raise TypeError("Local event bus can handle local events only.")
        for event_handler in self._local_event_handlers.get(event.name, []):
            event_handler(event)
