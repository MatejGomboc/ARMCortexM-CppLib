# -*- Python -*-

import os
import sys

import lit.formats
import lit.util

# Device configurations for ARM Cortex-M processors
DEVICES = {
    'CM0': {
        'arch': 'thumbv6m',
        'triple': 'thumbv6m-none-eabi',
        'abi': 'eabi',
        'mcpu': 'cortex-m0',
        'mfpu': 'none',
        'mpu': False,
        'features': ['thumbv6m', 'cortex-m0'],
        'header': 'cortexm0',
        'defines': {
            '__CM0_REV': '0x0000U',
            '__NVIC_PRIO_BITS': '2U',
            '__Vendor_SysTickConfig': '0U'
        }
    },
    'CM0plus': {
        'arch': 'thumbv6m',
        'triple': 'thumbv6m-none-eabi',
        'abi': 'eabi',
        'mcpu': 'cortex-m0plus',
        'mfpu': 'none',
        'mpu': True,
        'features': ['thumbv6m', 'cortex-m0plus'],
        'header': 'cortexm0plus',
        'defines': {
            '__CM0PLUS_REV': '0x0000U',
            '__MPU_PRESENT': '1U',
            '__VTOR_PRESENT': '1U',
            '__NVIC_PRIO_BITS': '2U',
            '__Vendor_SysTickConfig': '0U'
        }
    },
    'CM1': {
        'arch': 'thumbv6m',
        'triple': 'thumbv6m-none-eabi',
        'abi': 'eabi',
        'mcpu': 'cortex-m1',
        'mfpu': 'none',
        'mpu': False,
        'features': ['thumbv6m', 'cortex-m1'],
        'header': 'cortexm1',
        'defines': {
            '__CM1_REV': '0x0000U',
            '__NVIC_PRIO_BITS': '2U',
            '__Vendor_SysTickConfig': '0U'
        }
    },
    'CM3': {
        'arch': 'thumbv7m',
        'triple': 'thumbv7m-none-eabi',
        'abi': 'eabi',
        'mcpu': 'cortex-m3',
        'mfpu': 'none',
        'mpu': True,
        'features': ['thumbv6m', 'thumbv7m', 'thumb-2', 'sat', 'ldrex', 'clz', 'cortex-m3'],
        'header': 'cortexm3',
        'defines': {
            '__CM3_REV': '0x0000U',
            '__MPU_PRESENT': '1U',
            '__VTOR_PRESENT': '1U',
            '__NVIC_PRIO_BITS': '3U',
            '__Vendor_SysTickConfig': '0U'
        }
    }
}

# Configuration file for the 'lit' test runner.

# name: The name of this test suite.
config.name = "ARMCortexM-CppLib"

# testFormat: The test format to use to interpret tests.
config.test_format = lit.formats.ShTest()

# suffixes: A list of file extensions to treat as test files.
config.suffixes = [
    ".cpp", ".c"
]

# test_source_root: The root path where tests are located.
config.test_source_root = os.path.dirname(__file__)

# Get configuration parameters
toolchain = lit_config.params.get("toolchain", "GCC")
device = lit_config.params.get("device", "CM0")
optimize = lit_config.params.get("optimize", "none")

class Toolchain:
    def __init__(self, toolchain, device, optimize):
        self._toolchain = toolchain
        self.device = device
        self.optimize = optimize

    def get_root_from_env(self):
        keys = sorted((k for k in os.environ.keys() if k.startswith(f'{self._toolchain}_TOOLCHAIN_')), reverse=True)
        if not keys:
            # Try common environment variable names
            common_vars = {
                'GCC': ['ARM_NONE_EABI_GCC_PATH', 'GCC_ARM_PATH', 'ARM_GCC_PATH'],
                'CLANG': ['LLVM_PATH', 'CLANG_PATH'],
                'AC6': ['ARMCLANG_PATH', 'AC6_PATH']
            }
            for var in common_vars.get(self._toolchain, []):
                if var in os.environ:
                    return os.environ[var]
            
            print(f"Warning: Toolchain '{self._toolchain}' not found in environment!")
            return None
        return os.environ.get(keys[0])

    def get_root(self):
        return self.get_root_from_env()
