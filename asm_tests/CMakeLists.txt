if(NOT CMAKE_BUILD_TYPE)
    message(FATAL_ERROR "CMake build type not set")
endif()

set(SUPPORTED_ARM_CORTEX_M_CMAKE_BUILD_TYPES
    Debug
    Release
    RelWithDebInfo
    MinSizeRel
)

if(NOT CMAKE_BUILD_TYPE IN_LIST SUPPORTED_ARM_CORTEX_M_CMAKE_BUILD_TYPES)
    message(FATAL_ERROR "Unsupported CMake build type: ${CMAKE_BUILD_TYPE}")
endif()

find_program(LIT_COMMAND lit)

if(NOT LIT_COMMAND)
    message(STATUS "LIT not found - install with: pip install lit")
    return()
endif()

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/lit.cfg.py.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/lit.cfg.py"
    @ONLY
)

add_test(
    NAME asm-tests
    COMMAND ${LIT_COMMAND} "${CMAKE_CURRENT_SOURCE_DIR}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
