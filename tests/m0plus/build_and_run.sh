#!/bin/bash
# Helper script to build and run tests

set -e

echo "Building Cortex-M0+ tests..."

# Create build directory
mkdir -p build
cd build

# Configure with CMake
cmake .. -DCMAKE_TOOLCHAIN_FILE=../../arm_none_eabi_gcc.cmake

# Build
make -j4

echo "Build complete!"

# Check if Renode is installed
if ! command -v renode &> /dev/null; then
    echo "Renode is not installed or not in PATH"
    echo "Please install Renode from: https://renode.io/"
    exit 1
fi

echo "Running tests in Renode..."
cd ../renode
renode --disable-xwt --console test_runner.resc
