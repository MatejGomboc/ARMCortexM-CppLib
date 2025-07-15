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
        'mcpu': 'cortex-m0',
        'mfpu': 'none',
        'features': ['thumbv6m', 'cortex-m0'],
        'defines': {
            '__CM0_REV': '0x0000U',
            '__NVIC_PRIO_BITS': '2U'
        }
    },
    'CM0plus': {
        'arch': 'thumbv6m', 
        'triple': 'thumbv6m-none-eabi',
        'mcpu': 'cortex-m0plus',
        'mfpu': 'none',
        'features': ['thumbv6m', 'cortex-m0plus', 'mpu'],
        'defines': {
            '__CM0PLUS_REV': '0x0000U',
            '__MPU_PRESENT': '1U',
            '__NVIC_PRIO_BITS': '2U'
        }
    },
    'CM1': {
        'arch': 'thumbv6m',
        'triple': 'thumbv6m-none-eabi', 
        'mcpu': 'cortex-m1',
        'mfpu': 'none',
        'features': ['thumbv6m', 'cortex-m1'],
        'defines': {
            '__CM1_REV': '0x0000U',
            '__NVIC_PRIO_BITS': '2U'
        }
    },
    'CM3': {
        'arch': 'thumbv7m',
        'triple': 'thumbv7m-none-eabi',
        'mcpu': 'cortex-m3',
        'mfpu': 'none', 
        'features': ['thumbv7m', 'cortex-m3', 'mpu'],
        'defines': {
            '__CM3_REV': '0x0000U',
            '__MPU_PRESENT': '1U',
            '__NVIC_PRIO_BITS': '3U'
        }
    }
}

# Basic configuration
config.name = "ARMCortexM-CppLib"
config.test_format = lit.formats.ShTest()
config.suffixes = [".cpp", ".c"]
config.test_source_root = os.path.dirname(__file__)

# Get test parameters
toolchain = lit_config.params.get("toolchain", "GCC")
device = lit_config.params.get("device", "CM0")
optimize = lit_config.params.get("optimize", "none")

# Simple compiler setup
if toolchain == "GCC":
    cc = "arm-none-eabi-g++"
elif toolchain == "Clang":
    cc = "clang++"
else:
    cc = "gcc"

# Optimization flags
opt_flags = {
    'none': '-O0',
    'balanced': '-O2', 
    'speed': '-O3',
    'size': '-Os'
}

# Build compiler flags
device_config = DEVICES.get(device, DEVICES['CM0'])
ccflags = [
    f'-mcpu={device_config["mcpu"]}',
    '-mthumb',
    opt_flags[optimize],
    '-I', os.path.abspath('../'),
    '-std=c++17',
    '-c'
]

# Add device defines
for define, value in device_config['defines'].items():
    ccflags.extend(['-D', f'{define}={value}'])

# Set available features
for feature in device_config['features']:
    config.available_features.add(feature)

# Set up substitutions
config.substitutions.append(("%cc%", cc))
config.substitutions.append(("%ccflags%", ' '.join(ccflags)))
config.substitutions.append(("%ccout%", "-o"))
config.substitutions.append(("%mcpu%", device_config['mcpu']))
config.substitutions.append(("%prefixes%", "CHECK,CHECK-THUMB"))
config.substitutions.append(("objdump", "arm-none-eabi-objdump"))
