cmake_minimum_required(VERSION 3.16...3.31.6)

# Include required modules
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Project configuration
project(ARMCortexM-CppLib
    VERSION 1.0.0
    DESCRIPTION "CMSIS-like C++ library for ARM Cortex-M microcontrollers"
    LANGUAGES CXX
)

# Build options for different Cortex-M variants
option(ARM_CORTEX_M0PLUS "Target ARM Cortex-M0+ processors" ON)
option(ARM_CORTEX_M3 "Target ARM Cortex-M3 processors" OFF)
option(ARM_CORTEX_M4 "Target ARM Cortex-M4 processors" OFF)
option(ARM_CORTEX_M7 "Target ARM Cortex-M7 processors" OFF)

# Embedded-specific options
option(ENABLE_EXCEPTIONS "Enable C++ exceptions (not recommended for embedded)" OFF)
option(ENABLE_RTTI "Enable C++ RTTI (not recommended for embedded)" OFF)

# Validate that at least one target is selected
if(NOT (ARM_CORTEX_M0PLUS OR ARM_CORTEX_M3 OR ARM_CORTEX_M4 OR ARM_CORTEX_M7))
    message(FATAL_ERROR "At least one ARM Cortex-M target must be enabled")
endif()

# C++ standard configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create the main interface library
add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Collect header files for better IDE integration
set(HEADER_FILES
    utils.hpp
    cortexm0plus/exceptions.hpp
    cortexm0plus/mpu.hpp
    cortexm0plus/nvic.hpp
    cortexm0plus/scb.hpp
    cortexm0plus/special_regs.hpp
    cortexm0plus/systick.hpp
)

# Associate header files with the target
target_sources(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/exceptions.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/mpu.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/nvic.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/scb.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/special_regs.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cortexm0plus/systick.hpp>
)

# Configure include directories
target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Target-specific compile definitions
if(ARM_CORTEX_M0PLUS)
    target_compile_definitions(${PROJECT_NAME} INTERFACE ARM_CORTEX_M0PLUS)
endif()
if(ARM_CORTEX_M3)
    target_compile_definitions(${PROJECT_NAME} INTERFACE ARM_CORTEX_M3)
endif()
if(ARM_CORTEX_M4)
    target_compile_definitions(${PROJECT_NAME} INTERFACE ARM_CORTEX_M4)
endif()
if(ARM_CORTEX_M7)
    target_compile_definitions(${PROJECT_NAME} INTERFACE ARM_CORTEX_M7)
endif()

# Embedded-specific compiler options
target_compile_options(${PROJECT_NAME} INTERFACE
    # GCC/Clang options for embedded development
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
        -ffreestanding
        $<$<NOT:$<BOOL:${ENABLE_EXCEPTIONS}>>:-fno-exceptions>
        $<$<NOT:$<BOOL:${ENABLE_RTTI}>>:-fno-rtti>
        -ffunction-sections
        -fdata-sections
    >
    # MSVC options (for development/testing on Windows)
    $<$<CXX_COMPILER_ID:MSVC>:
        $<$<NOT:$<BOOL:${ENABLE_EXCEPTIONS}>>:/EHs-c->
        $<$<NOT:$<BOOL:${ENABLE_RTTI}>>:/GR->
    >
)

# Warning configuration for better code quality
target_compile_options(${PROJECT_NAME} INTERFACE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
        -Wall -Wextra -Wpedantic
        -Wconversion -Wsign-conversion
        -Wold-style-cast
        -Wunused -Wundef
    >
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /WX
    >
)

# IDE source grouping for better organization
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})

# Installation rules
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    # Only install if this is the main project
    
    # Install the library target
    install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    
    # Install header files
    install(FILES utils.hpp
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    
    install(DIRECTORY cortexm0plus/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cortexm0plus
        FILES_MATCHING PATTERN "*.hpp"
    )
    
    # Install the export targets
    install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )
    
    # Create package configuration files
    configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
        NO_SET_AND_CHECK_MACRO
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
    )
    
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
        ARCH_INDEPENDENT
    )
    
    # Install package configuration files
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )
    
    # Create uninstall target (optional but helpful)
    if(NOT TARGET uninstall)
        configure_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
            IMMEDIATE @ONLY
        )
        
        add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
        )
    endif()
endif()

# Display configuration summary
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(STATUS "")
    message(STATUS "=== ${PROJECT_NAME} Configuration Summary ===")
    message(STATUS "Version: ${PROJECT_VERSION}")
    message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
    message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
    message(STATUS "")
    message(STATUS "Target processors:")
    message(STATUS "  ARM Cortex-M0+: ${ARM_CORTEX_M0PLUS}")
    message(STATUS "  ARM Cortex-M3:  ${ARM_CORTEX_M3}")
    message(STATUS "  ARM Cortex-M4:  ${ARM_CORTEX_M4}")
    message(STATUS "  ARM Cortex-M7:  ${ARM_CORTEX_M7}")
    message(STATUS "")
    message(STATUS "Embedded options:")
    message(STATUS "  Exceptions: ${ENABLE_EXCEPTIONS}")
    message(STATUS "  RTTI:       ${ENABLE_RTTI}")
    message(STATUS "")
    message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
    message(STATUS "==================================")
    message(STATUS "")
endif()
