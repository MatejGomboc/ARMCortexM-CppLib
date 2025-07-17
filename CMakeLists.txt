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

cmake_minimum_required(VERSION 3.12)

project(ARMCortexM
    LANGUAGES CXX
    VERSION 1.0.0
    DESCRIPTION "CMSIS-like C++ library for ARM Cortex-M microcontrollers"
    HOMEPAGE_URL "https://github.com/MatejGomboc/ARMCortexM-CppLib"
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

target_include_directories(${PROJECT_NAME} INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_sources(${PROJECT_NAME} INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp"
    # Cortex-M0 headers
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm0/barriers.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm0/exceptions.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm0/misc.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm0/nvic.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm0/scb.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm0/special_regs.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm0/systick.hpp"
    # Cortex-M0+ headers
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/barriers.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/exceptions.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/misc.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/mpu.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/nvic.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/scb.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/special_regs.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/systick.hpp"
    # Cortex-M1 headers
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm1/exceptions.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm1/nvic.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm1/scb.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm1/special_regs.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm1/systick.hpp"
    # Cortex-M3 headers
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm3/exceptions.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm3/mpu.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm3/nvic.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm3/scb.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm3/special_regs.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cortexm3/systick.hpp"
)

option(BUILD_ARM_CORTEX_M_TESTS "Build tests" ON)

if(BUILD_ARM_CORTEX_M_TESTS)
    enable_testing()
    add_subdirectory(asm_tests)
endif()
