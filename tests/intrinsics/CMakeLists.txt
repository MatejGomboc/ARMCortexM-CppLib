add_subdirectory(common)

if(ARM_CORTEX_M_ARCH STREQUAL "M3" OR ARM_CORTEX_M_ARCH STREQUAL "M4" OR ARM_CORTEX_M_ARCH STREQUAL "M7")
    add_subdirectory(armv7m)
endif()
