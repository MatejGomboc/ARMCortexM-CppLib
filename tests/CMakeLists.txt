get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

set(SUPPORTED_BUILD_TYPES
    Debug
    MinSize
    MaxSpeed
)

set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_FLAGS_MINSIZE "-Os")
set(CMAKE_CXX_FLAGS_MAXSPEED "-O3")

if(IS_MULTI_CONFIG)
    set(CMAKE_CONFIGURATION_TYPES "${SUPPORTED_BUILD_TYPES}" CACHE STRING "" FORCE)
    set(CMAKE_DEFAULT_BUILD_TYPE "MinSize" CACHE STRING "" FORCE)

else()
    if(NOT CMAKE_BUILD_TYPE)
        message(FATAL_ERROR "CMake build type not set")
    endif()

    if(NOT CMAKE_BUILD_TYPE IN_LIST SUPPORTED_BUILD_TYPES)
        message(FATAL_ERROR "Unsupported CMake build type: ${CMAKE_BUILD_TYPE}")
    endif()
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

function(add_asm_test TEST_NAME)
    add_library(${TEST_NAME} STATIC
        ${TEST_NAME}.cpp
    )

    target_compile_features(${TEST_NAME} PRIVATE cxx_std_20)

    target_link_libraries(${TEST_NAME} PRIVATE
        ARMCortexM
    )

    add_custom_target(${TEST_NAME}_asm
        ALL
        WORKING_DIRECTORY "$<TARGET_FILE_DIR:${TEST_NAME}>"
        COMMAND "${CMAKE_COMMAND}" -E rm -f ${TEST_NAME}.asm
        COMMAND "${CMAKE_OBJDUMP}" -d --no-show-raw-insn ${CMAKE_STATIC_LIBRARY_PREFIX}${TEST_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX} > ${TEST_NAME}.asm
        BYPRODUCTS ${TEST_NAME}.asm
        VERBATIM
        DEPENDS ${TEST_NAME}
    )

    add_test(
        NAME ${TEST_NAME}
        COMMAND filecheck "${CMAKE_CURRENT_SOURCE_DIR}/${TEST_NAME}.cpp" --input-file "$<TARGET_FILE_DIR:${TEST_NAME}>/${TEST_NAME}.asm"
            --check-prefixes=CHECK,$<UPPER_CASE:$<CONFIG>>-CHECK --allow-unused-prefixes
    )
endfunction()

add_subdirectory(bit_utils)
add_subdirectory(intrinsics)
