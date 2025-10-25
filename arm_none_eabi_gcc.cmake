# Copyright (C) 2025 Matej Gomboc <https://github.com/MatejGomboc/ARMCortexM-CppLib>

# Licensed under the Apache Licence, Version 2.0 (the "Licence");
# you may not use this file except in compliance with the Licence.
# You may obtain a copy of the Licence at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the Licence is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the Licence for the specific language governing permissions and
# limitations under the Licence.

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

if(NOT DEFINED CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER arm-none-eabi-gcc)
endif()

if(NOT DEFINED CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
endif()

if(NOT DEFINED CMAKE_ASM_COMPILER)
    set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER} -x assembler-with-cpp)
endif()

if(NOT DEFINED CMAKE_AR)
    set(CMAKE_AR arm-none-eabi-gcc-ar)
endif()

if(NOT DEFINED CMAKE_RANLIB)
    set(CMAKE_RANLIB arm-none-eabi-gcc-ranlib)
endif()

if(NOT DEFINED CMAKE_ADDR2LINE)
    set(CMAKE_ADDR2LINE arm-none-eabi-addr2line)
endif()

if(NOT DEFINED CMAKE_LINKER)
    set(CMAKE_LINKER arm-none-eabi-ld)
endif()

if(NOT DEFINED CMAKE_STRIP)
    set(CMAKE_STRIP arm-none-eabi-strip)
endif()

if(NOT DEFINED CMAKE_NM)
    set(CMAKE_NM arm-none-eabi-nm)
endif()

if(NOT DEFINED CMAKE_OBJCOPY)
    set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
endif()

if(NOT DEFINED CMAKE_OBJDUMP)
    set(CMAKE_OBJDUMP arm-none-eabi-objdump)
endif()

if(NOT DEFINED CMAKE_SIZE)
    set(CMAKE_SIZE arm-none-eabi-size)
endif()

if(NOT DEFINED CMAKE_READELF)
    set(CMAKE_READELF arm-none-eabi-readelf)
endif()

set(CMAKE_ASM_FLAGS_DEBUG_INIT "-DDEBUG")
set(CMAKE_ASM_FLAGS_RELEASE_INIT "")
set(CMAKE_ASM_FLAGS_MINSIZEREL_INIT "")
set(CMAKE_ASM_FLAGS_RELWITHDEBINFO_INIT "")

set(CMAKE_C_FLAGS_DEBUG_INIT "-Og -ggdb3 -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE_INIT "-O2")
set(CMAKE_C_FLAGS_MINSIZEREL_INIT "-Os")
set(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-O2 -ggdb3")

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Og -ggdb3 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O2")
set(CMAKE_CXX_FLAGS_MINSIZEREL_INIT "-Os")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -ggdb3")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
