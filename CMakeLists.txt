cmake_minimum_required(VERSION 3.16...3.31.6)

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
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/exceptions.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/mpu.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/nvic.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/scb.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/special_regs.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/systick.hpp
)
