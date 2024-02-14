#
#  Copyright (c) 2023, The OpenThread Authors.
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
#  1. Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#  3. Neither the name of the copyright holder nor the
#     names of its contributors may be used to endorse or promote products
#     derived from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
#  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
#  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
#  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
#  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
#  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
#  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
#  POSSIBILITY OF SUCH DAMAGE.
#

#[=======================================================================[.rst:
Findcpc
-------

Finds the cpc library.
For our vendor implementation, this module resolves the symbols to build
and link against the CPC library using a vendor agnostic CMake interface.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``cpc::cpc``
  CPC library and header files

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``cpc_FOUND``
  True if the system has the CPC resources.
``cpc_INCLUDE_DIRS``
  Include directories needed to use CPC.
``cpc_LIBRARIES``
  Libraries needed to link to CPC.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be used by the module if set:

``Cpc_INCLUDE_DIR``
  The directory containing ``sl_cpc.h``.
``Cpc_LIBRARY``
  The path to the cpc library.

#]=======================================================================]

include(FindPackageHandleStandardArgs)

find_package(PkgConfig)
pkg_check_modules(Libcpc QUIET IMPORTED_TARGET libcpc)

find_library(Cpc_LIBRARY
    NAMES cpc
    PATHS ${Libcpc_LIBRARY_DIRS}
)

find_path(Cpc_INCLUDE_DIR
    NAMES sl_cpc.h
    PATHS ${Libcpc_INCLUDE_DIRS}
)

find_package_handle_standard_args(cpc
    FOUND_VAR cpc_FOUND
    REQUIRED_VARS Cpc_LIBRARY Cpc_INCLUDE_DIR
)

if(cpc_FOUND AND NOT TARGET cpc::cpc)
    set(cpc_LIBRARIES ${Cpc_LIBRARY})
    set(cpc_INCLUDE_DIRS ${Cpc_INCLUDE_DIR})

    mark_as_advanced(
        Cpc_LIBRARY
        Cpc_INCLUDE_DIR
    )

    add_library(cpc::cpc UNKNOWN IMPORTED)
    set_target_properties(cpc::cpc PROPERTIES
        IMPORTED_LOCATION "${cpc_LIBRARIES}"
        INTERFACE_INCLUDE_DIRECTORIES "${cpc_INCLUDE_DIRS}"
    )

endif()
