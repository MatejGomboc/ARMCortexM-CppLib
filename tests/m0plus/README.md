# Cortex-M0+ Library Tests with Renode

This directory contains comprehensive tests for the ARM Cortex-M0+ components of the ARMCortexM-CppLib library using the Renode simulation framework.

## Overview

The test suite covers all major Cortex-M0+ peripherals and features:

- **NVIC** (Nested Vectored Interrupt Controller)
  - IRQ enable/disable
  - Pending state management
  - Priority configuration

- **SCB** (System Control Block)
  - CPUID verification
  - Exception priority management
  - Vector table offset (VTOR)
  - PendSV and SysTick control

- **SysTick**
  - Timer configuration
  - Interrupt generation
  - Clock source selection
  - Calibration value reading

- **MPU** (Memory Protection Unit)
  - Region configuration
  - Access permissions
  - Enable/disable control

- **Special Registers**
  - PRIMASK (interrupt masking)
  - CONTROL register
  - MSP/PSP (stack pointers)
  - APSR/IPSR/xPSR (status registers)

## Prerequisites

1. **ARM GCC Toolchain**: arm-none-eabi-gcc (version 10.0 or later)
2. **CMake**: Version 3.12 or later
3. **Renode**: Version 1.13 or later
4. **Python**: Version 3.6 or later (for Robot Framework)
5. **Robot Framework**: Install with `pip install robotframework`

## Building the Tests

```bash
cd tests/m0plus
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../../arm_none_eabi_gcc.cmake
make
```

## Running Tests

### Manual Execution with Renode

```bash
cd tests/m0plus/renode
renode test_runner.resc
```

### Automated Testing with Robot Framework

```bash
cd tests/m0plus
robot robot/cortex_m0plus_tests.robot
```

## Test Structure

- **main.cpp**: Test harness and result tracking
- **test_*.cpp**: Individual test files for each component
- **startup.S**: Minimal startup code and vector table
- **linker_script.ld**: Memory layout definition
- **renode/**: Renode platform and scripts
  - **cortex_m0plus_test_platform.repl**: Hardware platform description
  - **test_runner.resc**: Main test execution script
- **robot/**: Robot Framework test cases

## Understanding Test Results

The test application outputs results through a mock UART peripheral at address 0x40000000. Each test reports:

- `[PASS]` - Test passed
- `[FAIL]` - Test failed (with expected vs actual values)
- `[INFO]` - Informational messages

At the end, a summary shows:
- Total number of tests
- Number of passed tests  
- Number of failed tests

## Extending the Tests

To add new tests:

1. Create a new `test_<component>.cpp` file
2. Implement test functions using the `assert_true()` and `assert_equals()` helpers
3. Add the test function declaration to main.cpp
4. Call the test function from main()
5. Add the new source file to CMakeLists.txt

## Debugging

Renode provides excellent debugging capabilities:

1. **GDB Integration**: 
   ```
   (monitor) machine StartGdbServer 3333
   ```
   Then connect with arm-none-eabi-gdb

2. **Execution Tracing**:
   ```
   (monitor) cpu LogFunctionNames true
   ```

3. **Peripheral Access Logging**:
   ```
   (monitor) sysbus LogPeripheralAccess nvic
   ```

## Known Limitations

- Some Cortex-M0+ implementations may not include all features (e.g., MPU, VTOR)
- The test platform uses a generic M0+ configuration
- Timing-dependent tests may behave differently in simulation vs hardware

## Contributing

When adding new tests, please:
1. Follow the existing code style
2. Add comprehensive test cases
3. Update this README if adding new components
4. Ensure all tests pass before submitting
