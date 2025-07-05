# Cortex-M0+ Test Application
cmake_minimum_required(VERSION 3.12)

project(CortexM0PlusTests
    LANGUAGES C CXX ASM
    VERSION 1.0.0
)

# Include the ARM toolchain file
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../../arm_none_eabi_gcc.cmake")

# Set MCU-specific flags
set(MCU_FLAGS "-mcpu=cortex-m0plus -mthumb")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MCU_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MCU_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${MCU_FLAGS}")

# Option to build for STM32G0
option(BUILD_FOR_STM32G0 "Build for STM32G0 target" OFF)

# Select linker script based on target
if(BUILD_FOR_STM32G0)
    set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/stm32g0_linker_script.ld")
    add_compile_definitions(TARGET_STM32G0)
    message(STATUS "Building for STM32G0 target")
else()
    set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/linker_script.ld")
    message(STATUS "Building for generic Cortex-M0+ target")
endif()

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${LINKER_SCRIPT} -nostartfiles -specs=nosys.specs")

# Add the main library
add_subdirectory(../.. armcortexm)

# Create test executable
add_executable(m0plus_tests
    main.cpp
    startup.S
    test_nvic.cpp
    test_scb.cpp
    test_systick.cpp
    test_mpu.cpp
    test_special_regs.cpp
)

# Link against the library
target_link_libraries(m0plus_tests PRIVATE ARMCortexM::ARMCortexM)

# Set C++ standard
target_compile_features(m0plus_tests PRIVATE cxx_std_17)

# Add compile options
target_compile_options(m0plus_tests PRIVATE
    -Wall
    -Wextra
    -g3
    -O0
    -ffunction-sections
    -fdata-sections
)

# Add linker options
target_link_options(m0plus_tests PRIVATE
    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_NAME}.map
)

# Generate binary and hex files
add_custom_command(TARGET m0plus_tests POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:m0plus_tests> ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:m0plus_tests> ${PROJECT_NAME}.hex
    COMMENT "Generating binary and hex files"
)

# Create STM32G0-specific build target
add_custom_target(stm32g0_tests
    COMMAND ${CMAKE_COMMAND} -DBUILD_FOR_STM32G0=ON ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Building tests for STM32G0 target"
)
