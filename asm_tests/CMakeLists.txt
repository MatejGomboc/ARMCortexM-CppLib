if(NOT CMAKE_BUILD_TYPE)
    message(FATAL_ERROR "CMake build type not set")
endif()

set(SUPPORTED_BUILD_TYPES
    Debug
    Release
    RelWithDebInfo
    MinSizeRel
)

if(NOT CMAKE_BUILD_TYPE IN_LIST SUPPORTED_BUILD_TYPES)
    message(FATAL_ERROR "Unsupported CMake build type: ${CMAKE_BUILD_TYPE}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(example STATIC
    example.cpp
)

target_link_libraries(example PRIVATE
    ARMCortexM
)

add_custom_target(example_asm
    ALL
    COMMAND "${CMAKE_OBJDUMP}" -d --no-show-raw-insn libexample.a > example.asm
    BYPRODUCTS example.asm
    VERBATIM
    DEPENDS example
)

add_test(
    NAME example
    COMMAND FileCheck "${CMAKE_CURRENT_SOURCE_DIR}/example.cpp" --input-file example.asm
)
