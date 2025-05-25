cmake_minimum_required(VERSION 3.16)

project(ARMCortexM-CppLib
    VERSION 1.0.0
    DESCRIPTION "CMSIS-like C++ library for ARM Cortex-M microcontrollers"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(${PROJECT_NAME} INTERFACE
    utils.hpp
    cortexm0plus/exceptions.hpp
    cortexm0plus/mpu.hpp
    cortexm0plus/nvic.hpp
    cortexm0plus/scb.hpp
    cortexm0plus/special_regs.hpp
    cortexm0plus/systick.hpp
)
