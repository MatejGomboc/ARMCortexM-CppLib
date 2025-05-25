cmake_minimum_required(VERSION 3.16...3.31.6)

project(ARMCortexM-CppLib
    VERSION 1.0.0
    DESCRIPTION "CMSIS-like C++ library for ARM Cortex-M microcontrollers"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    utils.hpp
    cortexm0plus/exceptions.hpp
    cortexm0plus/mpu.hpp
    cortexm0plus/nvic.hpp
    cortexm0plus/scb.hpp
    cortexm0plus/special_regs.hpp
    cortexm0plus/systick.hpp
)
