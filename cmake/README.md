# CMake Configuration Files

This directory contains CMake template files that support package management and installation.

## Files

- **`ARMCortexM-CppLibConfig.cmake.in`**: Package configuration template that enables `find_package(ARMCortexM-CppLib)` support. This file is processed by CMake to create the final configuration file installed with the library.

- **`cmake_uninstall.cmake.in`**: Uninstall script template that allows users to cleanly remove installed files using `cmake --build . --target uninstall`.

## Usage

These files are automatically processed during the CMake configuration step. Users don't need to interact with them directly, but they enable:

1. **Package discovery**: Projects can find and link to ARMCortexM-CppLib using:
   ```cmake
   find_package(ARMCortexM-CppLib REQUIRED)
   target_link_libraries(my_target ARMCortexM-CppLib::ARMCortexM-CppLib)
   ```

2. **Clean uninstallation**: After installation, users can remove all installed files:
   ```bash
   cmake --build . --target uninstall
   ```

These templates follow modern CMake best practices for package management and distribution.
