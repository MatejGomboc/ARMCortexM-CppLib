#!/bin/bash
# Helper script to build and run tests for STM32G0 target

set -e

echo "Building Cortex-M0+ tests for STM32G0..."

# Create build directory
mkdir -p build
cd build

# Configure with CMake for STM32G0
cmake .. -DCMAKE_TOOLCHAIN_FILE=../../arm_none_eabi_gcc.cmake -DBUILD_FOR_STM32G0=ON

# Build
make -j4

echo "Build complete!"

# Check if Renode is installed
if ! command -v renode &> /dev/null; then
    echo "Renode is not installed or not in PATH"
    echo "Please install Renode from: https://renode.io/"
    exit 1
fi

echo "Running tests on STM32G0 platform in Renode..."
cd ../renode
renode --disable-xwt --console test_runner_stm32g0.resc
