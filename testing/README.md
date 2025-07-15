# ARMCortexM-CppLib Testing Framework

This directory contains a comprehensive testing framework for the ARMCortexM-CppLib library using LLVM's `lit` (LLVM Integrated Tester) and a Python matrix runner for automated testing across multiple device, compiler, and optimization combinations.

## Overview

The testing framework provides:

- **Matrix-based testing** across multiple ARM Cortex-M devices, compilers, and optimization levels
- **Assembly verification** to ensure correct instruction generation
- **Cross-compiler compatibility** testing (GCC, Clang, ARM Compiler 6)
- **Performance and optimization** verification
- **Automated CI/CD** through GitHub Actions

## Quick Start

### Prerequisites

1. **Python 3.8+** with pip
2. **ARM toolchains** (automatically managed via vcpkg)
3. **LLVM tools** (lit, FileCheck, objdump)

### Installation

```bash
# Navigate to testing directory
cd testing

# Install Python dependencies
pip install -r requirements.txt

# Install ARM toolchains via vcpkg
vcpkg install
```

### Running Tests

```bash
# Run all tests with default configuration (GCC, CM0, no optimization)
python build.py lit

# Run tests for specific device
python build.py lit -d CM3

# Run tests with specific compiler
python build.py lit -c Clang

# Run tests with optimization
python build.py lit -o speed

# Run comprehensive test matrix
python build.py lit -d CM0 -d CM0plus -d CM3 -c GCC -c Clang -o none -o speed
```

## Architecture

### Matrix Runner (build.py)

The matrix runner orchestrates test execution across multiple dimensions:

- **Device Axis**: CM0, CM0plus, CM1, CM3, CM4, CM4FP, CM7, CM33, CM55, CM85, etc.
- **Compiler Axis**: GCC, Clang, ARM Compiler 6
- **Optimization Axis**: none (-O0), balanced (-O2), speed (-O3), size (-Os/-Oz)

### LIT Configuration (lit.cfg.py)

The lit configuration provides:

- **Device-specific compiler flags** and preprocessor definitions
- **Toolchain abstraction** for different compilers
- **Feature detection** for conditional test execution
- **Assembly verification** through objdump and FileCheck

### Test Structure

```
tests/
├── utils_test.cpp              # Utility function tests
├── cortexm0/                   # Cortex-M0 specific tests
│   ├── special_regs_test.cpp   # Special register access
│   ├── barriers_test.cpp       # Memory barriers
│   ├── nvic_test.cpp          # NVIC functionality
│   ├── systick_test.cpp       # SysTick timer
│   └── scb_test.cpp           # System Control Block
├── cortexm0plus/              # Cortex-M0+ specific tests
│   └── mpu_test.cpp           # Memory Protection Unit
├── cortexm3/                  # Cortex-M3 specific tests
│   └── mpu_test.cpp           # Enhanced MPU features
├── integration/               # Cross-device tests
│   └── cross_device_test.cpp  # Universal functionality
└── performance/               # Performance tests
    └── optimization_test.cpp  # Optimization verification
```

## Test Types

### Assembly Verification Tests

These tests verify that the library generates correct ARM assembly:

```cpp
void test_getMspReg() {
    // CHECK-LABEL: <{{.*test_getMspReg.*}}>:
    // CHECK: mrs {{r[0-9]+}}, msp
    volatile uint32_t msp = getMspReg();
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}
```

### Functionality Tests

These tests verify correct behavior and API usage:

```cpp
void test_psrBitfields() {
    Psr psr;
    psr.value = 0x81000000;  // Set N and T flags
    
    volatile bool thumb_mode = psr.bits.thumb_mode;
    volatile bool negative_flag = psr.bits.n;
    // Verify bitfield access works correctly
}
```

### Performance Tests

These tests ensure optimal code generation:

```cpp
void test_inline_efficiency() {
    InstrSyncBarrier();  // Should generate single ISB
    // CHECK: isb
    // CHECK-NEXT: {{(bx lr)|(pop {.*pc})}}
}
```

## Supported Configurations

### Devices

| Device | Architecture | FPU | MPU | Security | Status |
|--------|-------------|-----|-----|----------|--------|
| CM0    | Thumb-v6M   | ❌  | ❌  | ❌       | ✅     |
| CM0+   | Thumb-v6M   | ❌  | ✅  | ❌       | ✅     |
| CM1    | Thumb-v6M   | ❌  | ❌  | ❌       | ✅     |
| CM3    | Thumb-v7M   | ❌  | ✅  | ❌       | ✅     |
| CM4    | Thumb-v7EM  | ❌  | ✅  | ❌       | 🚧     |
| CM4FP  | Thumb-v7EM  | ✅  | ✅  | ❌       | 🚧     |
| CM33   | Thumb-v8M   | ✅  | ✅  | ✅       | 🚧     |
| CM55   | Thumb-v8.1M | ✅  | ✅  | ✅       | 🚧     |

### Compilers

| Compiler | Version | Status | Notes |
|----------|---------|--------|-------|
| GCC      | 14.2.1  | ✅     | Primary compiler |
| Clang    | 19.1.5  | ✅     | LLVM-based |
| AC6      | 6.23.0  | 🚧     | ARM Compiler 6 |

### Optimizations

| Level    | Flag | Description | Status |
|----------|------|-------------|--------|
| none     | -O0  | No optimization | ✅ |
| balanced | -O2  | Balanced performance/size | ✅ |
| speed    | -O3  | Maximum performance | ✅ |
| size     | -Os  | Minimum size | ✅ |

## Writing New Tests

### Test File Template

```cpp
// REQUIRES: cortex-m0
// RUN: %cc% %ccflags% %ccout% %T/%basename_t.o %s; objdump --mcpu=%mcpu% -d %T/%basename_t.o | FileCheck --allow-unused-prefixes --check-prefixes %prefixes% %s

#include "cortexm0/special_regs.hpp"

void test_new_functionality() {
    // CHECK-LABEL: <{{.*test_new_functionality.*}}>:
    
    // Your test code here
    auto result = someFunction();
    // CHECK: expected assembly pattern
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}
```

### Key Guidelines

1. **Use `REQUIRES:`** to specify required device features
2. **Include `CHECK-LABEL:`** for function boundaries
3. **Use regex patterns** `{{...}}` for flexible matching
4. **Test both positive and negative cases**
5. **Verify assembly instruction generation**
6. **Use volatile** to prevent unwanted optimization

### Available Features

Use in `REQUIRES:` directives:

- `cortex-m0`, `cortex-m0plus`, `cortex-m1`, `cortex-m3`
- `thumbv6m`, `thumbv7m`, `thumbv7em`, `thumbv8m`
- `fpu`, `mpu`, `dsp`
- `gcc`, `clang`, `ac6`

## CI/CD Integration

The framework includes GitHub Actions workflows that:

- **Test multiple configurations** automatically on push/PR
- **Generate test reports** with coverage information
- **Upload test artifacts** for debugging failures
- **Deploy documentation** for test results

### Local CI Simulation

```bash
# Simulate CI testing locally
for device in CM0 CM0plus CM1 CM3; do
  for compiler in GCC Clang; do
    for opt in none speed; do
      echo "Testing $device with $compiler at $opt optimization"
      python build.py lit -d $device -c $compiler -o $opt
    done
  done
done
```

## Troubleshooting

### Common Issues

1. **Toolchain not found**
   ```bash
   # Ensure vcpkg is properly configured
   vcpkg install
   # Set environment variables if needed
   export GCC_TOOLCHAIN_PATH=/path/to/gcc
   ```

2. **Test failures due to optimization**
   ```bash
   # Run with no optimization to isolate issues
   python build.py lit -o none
   ```

3. **Assembly pattern mismatches**
   ```bash
   # Examine actual assembly output
   objdump -d test_output.o
   ```

### Debug Mode

```bash
# Run tests with verbose output
python build.py lit --verbose

# Run specific test file
lit -v tests/cortexm0/special_regs_test.cpp
```

## Contributing

When adding new library features:

1. **Add corresponding tests** in appropriate device directory
2. **Update device configurations** in `lit.cfg.py` if needed
3. **Test across multiple compilers** and optimization levels
4. **Document test patterns** for complex assembly verification
5. **Update CI matrix** if new combinations are needed

For questions or issues, please open a GitHub issue with:
- Test command that failed
- Expected vs actual behavior
- Device/compiler/optimization combination
- Complete error output
