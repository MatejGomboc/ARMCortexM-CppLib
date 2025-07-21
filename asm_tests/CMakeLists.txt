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

function(add_asm_test TEST_NAME)
    add_library(${TEST_NAME} STATIC
        ${TEST_NAME}.cpp
    )

    target_link_libraries(${TEST_NAME} PRIVATE
        ARMCortexM
    )

    add_custom_target(${TEST_NAME}_asm
        ALL
        COMMAND "${CMAKE_COMMAND}" -E rm -f ${TEST_NAME}.asm
        COMMAND "${CMAKE_OBJDUMP}" -d --no-show-raw-insn lib${TEST_NAME}.a > ${TEST_NAME}.asm
        BYPRODUCTS ${TEST_NAME}.asm
        VERBATIM
        DEPENDS ${TEST_NAME}
    )

    add_test(
        NAME ${TEST_NAME}
        COMMAND FileCheck "${CMAKE_CURRENT_SOURCE_DIR}/${TEST_NAME}.cpp" --input-file ${TEST_NAME}.asm
    )
endfunction()

add_subdirectory(utils_tests)
