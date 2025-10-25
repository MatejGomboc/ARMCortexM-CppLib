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
    VERSION 1.0.0
    DESCRIPTION "CMSIS-like C++ library for ARM Cortex-M microcontrollers"
    HOMEPAGE_URL "https://github.com/MatejGomboc/ARMCortexM-CppLib"
)

set(AVAILABLE_ARM_CORTEX_M_ARCHS
    "M0"
    "M0PLUS"
    "M1"
    "M3"
)

set(ARM_CORTEX_M_ARCH "" CACHE STRING "The target ARM Cortex-M architecture for which to build the ${PROJECT_NAME} library")
set_property(CACHE ARM_CORTEX_M_ARCH PROPERTY STRINGS ${AVAILABLE_ARM_CORTEX_M_ARCHS})

if(NOT ARM_CORTEX_M_ARCH)
    message(FATAL_ERROR "Missing target ARM Cortex-M architecture for which to build the ${PROJECT_NAME} library")
endif()

if(NOT ARM_CORTEX_M_ARCH IN_LIST AVAILABLE_ARM_CORTEX_M_ARCHS)
    message(FATAL_ERROR "Unsupported ARM Cortex-M architecture: ${ARM_CORTEX_M_ARCH}")
endif()

option(BUILD_ARM_CORTEX_M_TESTS "Build tests for ${PROJECT_NAME} library" OFF)

add_library(${PROJECT_NAME} INTERFACE)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

target_include_directories(${PROJECT_NAME} INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_sources(${PROJECT_NAME} INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/barriers.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/misc.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp"
)

target_compile_options(${PROJECT_NAME} INTERFACE
    -mthumb
    -mfloat-abi=soft
    -masm-syntax-unified
    -std=c++20
)

target_link_options(${PROJECT_NAME} INTERFACE
    -mfloat-abi=soft
    -mthumb
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
    enable_testing()
    add_subdirectory(tests)
endif()
