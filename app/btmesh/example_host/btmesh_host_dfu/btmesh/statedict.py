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
from typing import Callable, Mapping


class StateDictObject(abc.ABC):
    @staticmethod
    def to_bytes(raw):
        if isinstance(raw, bytes):
            return raw
        elif isinstance(raw, str):
            return bytes.fromhex(raw)
        else:
            # Handle iterable
            return bytes(raw)

    @staticmethod
    def elem_to_dict(elem):
        if isinstance(elem, StateDictObject):
            return elem.to_dict()
        elif isinstance(elem, str):
            return elem
        elif isinstance(elem, bytes):
            return elem.hex()
        elif isinstance(elem, Mapping):
            return {
                StateDictObject.elem_to_dict(k): StateDictObject.elem_to_dict(v)
                for k, v in elem.items()
            }
        elif hasattr(elem, "__iter__") or hasattr(elem, "__getitem__"):
            return [StateDictObject.elem_to_dict(e) for e in elem]
        else:
            return elem

    @staticmethod
    def property_name(attr_name):
        if (attr_name != "_") and (attr_name[0] == "_"):
            return attr_name[1:]
        else:
            return attr_name

    @classmethod
    def raise_construction_error(cls, attr_name, attr_value, hint="", type_error=False):
        if type_error:
            raise TypeError(
                f"{cls.__name__} {attr_name} is not constructible "
                f"from {type(attr_value).__name__} type. {hint}"
            )
        else:
            raise ValueError(
                f"{cls.__name__} {attr_name} is not constructible "
                f"from {attr_value} ({type(attr_value).__name__}). {hint}"
            )

    @classmethod
    def create_from_dict(cls, d):
        if isinstance(d, cls):
            # Handle gracefully if the d object is instance of the type which
            # needs to be created.
            return d
        else:
            obj = cls(**d)
            return obj

    def to_dict(self):
        return {
            self.property_name(attr_key): self.elem_to_dict(attr_value)
            for attr_key, attr_value in vars(self).items()
            if not isinstance(attr_value, Callable)
        }

    def from_dict(self, d):
        obj = self.create_from_dict(d)
        self.__dict__.update(vars(obj))

    def __repr__(self):
        params = ", ".join([f"{k}={v!r}" for k, v in vars(self).items()])
        return f"{self.__class__.__name__}({params})"
