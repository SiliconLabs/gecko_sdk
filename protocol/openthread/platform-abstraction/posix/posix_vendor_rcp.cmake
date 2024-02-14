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

set(CPCD_SOURCE_DIR "" CACHE PATH "path to directory containing cpcd CMakeLists.txt")

set(OT_POSIX_CONFIG_RCP_VENDOR_TARGET "cpc-interface")
set(CPC_LIB_TARGET "cpc")

if (NOT OT_PLATFORM_CONFIG)
    message(WARNING "OT_PLATFORM_CONFIG file which defines OT_VENDOR_RADIO_URL_HELP_BUS missing")
endif()

add_library(${OT_POSIX_CONFIG_RCP_VENDOR_TARGET} INTERFACE)

# If cpc target isn't already defined, run find_package to build
# library as subdirectory or locate pre-installed resources
# and add imported targets to cpc interface target
if (NOT TARGET cpc)
    if (CPCD_SOURCE_DIR)
        # Use cpc (lib) target directly and query header path from cpcd project
        add_subdirectory(${CPCD_SOURCE_DIR} build)
        get_target_property(CPC_HEADER cpc PUBLIC_HEADER)
        get_filename_component(CPC_INC ${CPC_HEADER} DIRECTORY)
        target_include_directories(${OT_POSIX_CONFIG_RCP_VENDOR_TARGET} INTERFACE ${CPC_INC})
    else()
        list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
        find_package(cpc REQUIRED)
        set(CPC_LIB_TARGET "cpc::cpc")
    endif()
endif()

target_link_libraries(${OT_POSIX_CONFIG_RCP_VENDOR_TARGET} 
    INTERFACE
        ${CPC_LIB_TARGET}
        ot-posix-config
)

target_include_directories(${OT_POSIX_CONFIG_RCP_VENDOR_TARGET}
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/core
        ${PROJECT_SOURCE_DIR}/src/posix/platform/
        ${PROJECT_SOURCE_DIR}/src/posix/platform/include
)
