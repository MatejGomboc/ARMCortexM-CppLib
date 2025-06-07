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
  - Note: Gracefully skipped on STM32G0 (no MPU)

- **Special Registers**
  - PRIMASK (interrupt masking)
  - CONTROL register
  - MSP/PSP (stack pointers)
  - APSR/IPSR/xPSR (status registers)

## Platform Support

The test framework includes:

1. **Generic Cortex-M0+ Platform** (`cortex_m0plus_test_platform.repl`)
   - 256KB Flash at 0x00000000
   - 64KB RAM at 0x20000000
   - Generic configuration

2. **STM32G0 Platform** (`stm32g0_test_platform.repl`)
   - Based on STM32G071 configuration
   - 128KB Flash at 0x08000000
   - 36KB RAM at 0x20000000
   - 64 MHz CPU frequency
   - No MPU support
   - 2-bit interrupt priority (4 levels)

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

Or use the helper script:
```bash
cd tests/m0plus
./build_and_run.sh
```

## Running Tests

### Generic Cortex-M0+ Platform

#### Option 1: Standard Test Runner
```bash
cd tests/m0plus/renode
renode test_runner.resc
```

#### Option 2: Monitor Mode (Live Output)
```bash
cd tests/m0plus/renode
renode test_runner_monitor.resc
```

#### Option 3: Simple Mode (Debugging)
```bash
cd tests/m0plus/renode
renode test_runner_simple.resc
```

### STM32G0-Specific Platform

```bash
cd tests/m0plus/renode
renode test_runner_stm32g0.resc
```

This runs the same tests but on an STM32G0-specific platform configuration, which:
- Has no MPU (tests will detect and skip MPU tests)
- Uses 2-bit interrupt priority
- Runs at 64 MHz
- Has STM32G0 memory layout

### Automated Testing with Robot Framework

```bash
cd tests/m0plus
robot robot/cortex_m0plus_tests.robot
```

## Test Output

The test application outputs results through memory-mapped I/O:
- **Test output**: Written to address `0x40000000` (character by character)
- **Completion signal**: Write `0xDEADBEEF` to address `0x40001000`
- **Test results**: Stored in RAM (searched by Renode)

Each test reports:
- `[PASS]` - Test passed
- `[FAIL]` - Test failed (with expected vs actual values)
- `[INFO]` - Informational messages

Final summary shows:
- Total number of tests
- Number of passed tests  
- Number of failed tests

## Platform Differences

### Generic Platform
- May include MPU (depends on configuration)
- Generic memory layout
- 1 MHz SysTick for simple timing

### STM32G0 Platform  
- No MPU (typical for STM32G0)
- STM32-specific memory map
- 64 MHz CPU/SysTick frequency
- 2-bit interrupt priority (4 levels)
- Flash at 0x08000000 (aliased to 0x00000000)

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

4. **Memory Inspection**:
   ```
   (monitor) sysbus ReadDoubleWord 0x20000000
   ```

## Troubleshooting

### Tests don't run
- Ensure the ELF file exists: `build/m0plus_tests`
- Check that addresses in linker script match platform description
- For STM32G0: verify Flash is at 0x08000000

### No output visible
- Use `logLevel 3` commands in Renode
- Check test_output.txt file after run
- Try the monitor mode runner for live output

### MPU tests fail on STM32G0
- This is expected! STM32G0 has no MPU
- Tests should detect this and skip MPU tests
- Look for "[INFO] MPU not present" message

### Tests timeout
- Increase timeout in test runner scripts
- Check for infinite loops in test code
- Verify SysTick configuration if using delays

## Known Limitations

- Some Cortex-M0+ implementations may not include all features (e.g., MPU, VTOR)
- The test platform uses a generic M0+ configuration
- STM32G0 platform accurately reflects no MPU limitation
- Timing-dependent tests may behave differently in simulation vs hardware

## Contributing

When adding new tests, please:
1. Follow the existing code style
2. Add comprehensive test cases
3. Test on both generic and STM32G0 platforms
4. Update this README if adding new components
5. Ensure all tests pass before submitting
