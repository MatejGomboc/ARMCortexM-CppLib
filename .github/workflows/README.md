# GitHub Actions CI for ARMCortexM-CppLib

This directory contains the GitHub Actions workflow for continuous integration.

## CI Workflow (`ci.yml`)

The CI workflow automatically runs tests for the ARMCortexM-CppLib project whenever:
- Code is pushed to the `main` branch
- A pull request is opened targeting the `main` branch
- The workflow is manually triggered via the GitHub Actions UI

### Test Environment

- **Base OS**: Debian Bookworm (latest stable Debian release)
- **Container**: Runs in a Debian container for consistent environment
- **FileCheck**: Python-based FileCheck implementation installed via pip

### Test Matrix

The workflow uses a matrix strategy to test all combinations of:

#### ARM Cortex-M Architectures:
- **M0** (`arch: "0"`) - Cortex-M0
- **M0+** (`arch: "0+"`) - Cortex-M0+
- **M1** (`arch: "1"`) - Cortex-M1
- **M3** (`arch: "3"`) - Cortex-M3

#### Build Types:
- **Debug** - Full debugging symbols, no optimization
- **Release** - Optimized for performance
- **MinSizeRel** - Optimized for size
- **RelWithDebInfo** - Release with debug symbols

This results in **16 total test configurations** (4 architectures × 4 build types).

### Key Features

- **Ninja Multi-Config Generator**: Uses the `multi` preset exclusively for CI builds
- **Parallel Testing**: All configurations run in parallel for faster feedback
- **Comprehensive Toolchain**: Installs ARM GCC toolchain, CMake, Ninja, and Python FileCheck
- **Test Artifacts**: Uploads test results and generated assembly files on failure
- **Summary Job**: Provides a clear pass/fail status for the entire test suite

### Tools Installed

- `gcc-arm-none-eabi`: ARM cross-compiler
- `binutils-arm-none-eabi`: ARM binary utilities (objdump, etc.)
- `libnewlib-arm-none-eabi`: C library for embedded ARM
- `cmake`: Build system generator
- `ninja-build`: Fast build system
- `python3` & `pip3`: Python runtime and package manager
- `filecheck` (Python): Test verification tool installed via pip
- `git`: Version control (required for actions/checkout in container)

### Workflow Steps

1. **Checkout**: Get the latest code
2. **Install Dependencies**: Set up the Debian build environment
3. **Install FileCheck**: Install Python-based FileCheck via pip
4. **Configure**: Run CMake with the multi preset and specific architecture
5. **Build**: Compile using the appropriate multi-config preset
6. **Test**: Run CTest for the specific configuration
7. **Upload Artifacts**: Save test results if tests fail

### Local Testing

To replicate the CI environment locally on Debian:

```bash
# Install dependencies
sudo apt-get update
sudo apt-get install -y cmake ninja-build gcc-arm-none-eabi \
    binutils-arm-none-eabi libnewlib-arm-none-eabi python3 python3-pip
sudo pip3 install filecheck

# Configure for a specific architecture (e.g., Cortex-M3)
cmake --preset=multi -DARM_CORTEX_M_ARCH="3" -DBUILD_ARM_CORTEX_M_TESTS=ON

# Build for a specific configuration (e.g., Release)
cmake --build --preset=multi-release

# Run tests
cd build-multi
ctest -C Release --output-on-failure --verbose
```

### Docker Local Testing

To exactly replicate the CI environment using Docker:

```bash
# Run Debian Bookworm container
docker run -it --rm -v $(pwd):/workspace debian:bookworm

# Inside container, install dependencies and run tests
cd /workspace
apt-get update && apt-get install -y cmake ninja-build gcc-arm-none-eabi \
    binutils-arm-none-eabi libnewlib-arm-none-eabi python3 python3-pip git
pip3 install --break-system-packages filecheck
# Then follow the build steps above
```

### Troubleshooting

If tests fail in CI:
1. Check the test output in the workflow logs
2. Download the uploaded artifacts for detailed assembly output
3. Review the `LastTest.log` file for CTest details
4. Ensure all required tools are properly installed
5. Verify that FileCheck is accessible (Python version)
