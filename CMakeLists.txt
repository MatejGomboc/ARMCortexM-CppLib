# Copyright (C) 2025 Matej Gomboc <https://github.com/MatejGomboc/ARMCortexM-CppLib>

# Licensed under the Apache Licence, Version 2.0 (the "Licence");
# you may not use this file except in compliance with the Licence.
# You may obtain a copy of the Licence at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the Licence is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the Licence.

cmake_minimum_required(VERSION 3.13)

project(ARMCortexM
    LANGUAGES CXX
    VERSION 0.1.0
    DESCRIPTION "CMSIS-like C++ library for ARM Cortex-M microcontrollers"
    HOMEPAGE_URL "https://github.com/MatejGomboc/ARMCortexM-CppLib"
)

set(AVAILABLE_ARM_CORTEX_M_ARCHS
    "M0"
    "M0PLUS"
    "M1"
    "M3"
)

if(NOT DEFINED ARM_CORTEX_M_ARCH)
    set(ARM_CORTEX_M_ARCH "" CACHE STRING "The target ARM Cortex-M architecture for which to build the ${PROJECT_NAME} library")
    set_property(CACHE ARM_CORTEX_M_ARCH PROPERTY STRINGS ${AVAILABLE_ARM_CORTEX_M_ARCHS})
endif()

if(NOT ARM_CORTEX_M_ARCH)
    message(FATAL_ERROR "Missing target ARM Cortex-M architecture for which to build the ${PROJECT_NAME} library")
endif()

if(NOT ARM_CORTEX_M_ARCH IN_LIST AVAILABLE_ARM_CORTEX_M_ARCHS)
    message(FATAL_ERROR "Unsupported ARM Cortex-M architecture: ${ARM_CORTEX_M_ARCH}")
endif()

option(BUILD_ARM_CORTEX_M_TESTS "Build tests for ${PROJECT_NAME} library" OFF)

add_library(${PROJECT_NAME} INTERFACE)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

# Base include directory for architecture-specific files (m0/, m3/, etc.)
target_include_directories(${PROJECT_NAME} INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Common intrinsics - available on ALL Cortex-M architectures
# This enables flat includes: #include "barriers.hpp" instead of #include "intrinsics/common/barriers.hpp"
target_include_directories(${PROJECT_NAME} INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/intrinsics/common"
)

target_sources(${PROJECT_NAME} INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/bit_utils.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/intrinsics/common/barriers.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/intrinsics/common/byte_reversing.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/intrinsics/common/debugging.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/intrinsics/common/exceptions.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/intrinsics/common/hints.hpp"
)

if(ARM_CORTEX_M_ARCH STREQUAL "M0")
    target_sources(${PROJECT_NAME} INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/m0/exceptions.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m0/nvic.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m0/scb.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m0/special_regs.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m0/systick.hpp"
    )
    target_compile_definitions(${PROJECT_NAME} INTERFACE ARM_CORTEX_M0)
    target_compile_options(${PROJECT_NAME} INTERFACE -mcpu=cortex-m0)
    target_link_options(${PROJECT_NAME} INTERFACE -mcpu=cortex-m0)

elseif(ARM_CORTEX_M_ARCH STREQUAL "M0PLUS")
    target_sources(${PROJECT_NAME} INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/m0plus/exceptions.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m0plus/mpu.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m0plus/nvic.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m0plus/scb.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m0plus/special_regs.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m0plus/systick.hpp"
    )
    target_compile_definitions(${PROJECT_NAME} INTERFACE ARM_CORTEX_M0PLUS)
    target_compile_options(${PROJECT_NAME} INTERFACE -mcpu=cortex-m0plus)
    target_link_options(${PROJECT_NAME} INTERFACE -mcpu=cortex-m0plus)

elseif(ARM_CORTEX_M_ARCH STREQUAL "M1")
    target_sources(${PROJECT_NAME} INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/m1/exceptions.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m1/nvic.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m1/scb.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m1/special_regs.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m1/systick.hpp"
    )
    target_compile_definitions(${PROJECT_NAME} INTERFACE ARM_CORTEX_M1)
    target_compile_options(${PROJECT_NAME} INTERFACE -mcpu=cortex-m1)
    target_link_options(${PROJECT_NAME} INTERFACE -mcpu=cortex-m1)

elseif(ARM_CORTEX_M_ARCH STREQUAL "M3")
    # ARMv7-M intrinsics - available on M3, M4, M7
    # This enables flat includes: #include "bit_manipulation.hpp"
    target_include_directories(${PROJECT_NAME} INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/intrinsics/armv7m"
    )
    target_sources(${PROJECT_NAME} INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/intrinsics/armv7m/bit_manipulation.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/intrinsics/armv7m/exclusive_access.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/intrinsics/armv7m/saturation.hpp"
    )
    target_sources(${PROJECT_NAME} INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/m3/exceptions.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m3/mpu.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m3/nvic.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m3/scb.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m3/special_regs.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/m3/systick.hpp"
    )
    target_compile_definitions(${PROJECT_NAME} INTERFACE ARM_CORTEX_M3)
    target_compile_options(${PROJECT_NAME} INTERFACE -mcpu=cortex-m3)
    target_link_options(${PROJECT_NAME} INTERFACE -mcpu=cortex-m3)
endif()

if(BUILD_ARM_CORTEX_M_TESTS)
    include(CTest)
    add_subdirectory(tests)
endif()
