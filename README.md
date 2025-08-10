# ARMCortexM-CppLib

CMSIS-like C++ library for ARM Cortex-M microcontrollers

## Supported Architectures

- ARM Cortex-M0
- ARM Cortex-M0+
- ARM Cortex-M1 (WIP)
- ARM Cortex-M3 (WIP)
- TODO...

## Prerequisites

- CMake 3.13 or higher
- Ninja build system
- VCPKG (with `VCPKG_ROOT` environment variable set)

### Installing Prerequisites

#### Ubuntu/Debian
```bash
sudo apt install cmake ninja-build
```

#### macOS
```bash
brew install cmake ninja
```

#### Windows
```bash
# Using chocolatey
choco install cmake ninja

# Or using scoop
scoop install cmake ninja
```

## Building

### First Time Setup
The ARM toolchain will be automatically downloaded via VCPKG on first configuration:

```bash
# Download and activate ARM toolchain locally (stored in .tools/)
vcpkg x-download-tools --x-artifacts-root=./.tools
eval $(vcpkg x-activate --x-artifacts-root=./.tools)  # Linux/macOS
# OR for Windows:
# vcpkg x-activate --x-artifacts-root=.\.tools > activate_env.bat && call activate_env.bat
```

### Configure and Build

```bash
# Configure project (select desired preset)
cmake --preset multi

# Build
cmake --build build-multi --config Debug
```

Available presets:
- `multi` - Ninja Multi-Config generator
- `single-debug` - Debug build
- `single-release` - Release build
- `single-minsizerel` - Minimum size release build
- `single-relwithdebinfo` - Release with debug info

## License

This library is licensed under the Apache Licence Version 2.0.  
Copyright (C) 2025 Matej Gomboc <https://github.com/MatejGomboc/ARMCortexM-CppLib>.  
See the attached [LICENCE](./LICENCE) file for more info.
