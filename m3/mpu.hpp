/*
    Copyright (C) 2025 Matej Gomboc <https://github.com/MatejGomboc/ARMCortexM-CppLib>

    Licensed under the Apache Licence, Version 2.0 (the "Licence");
    you may not use this file except in compliance with the Licence.
    You may obtain a copy of the Licence at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the Licence is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the Licence for the specific language governing permissions and
    limitations under the Licence.
*/

#pragma once

#include <cstdint>

namespace Cortex::M3::Mpu {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000ED90u;

    struct Registers {
        volatile uint32_t TYPE; //!< indicates whether the MPU is present, and if so, how many regions it supports
        volatile uint32_t CTRL; //!< MPU control register
        volatile uint32_t RNR; //!< region number register (selects a region to edit its attributes)
        volatile uint32_t RBAR; //!< region base address register
        volatile uint32_t RASR; //!< region attribute and size register
    };

    union TYPE {
        struct Bits {
            uint32_t SEPARATE: 1; //!< support for unified/separate instruction and data regions
            uint32_t RESERVED0: 7;
            uint32_t DREGION: 8; //!< number of supported data regions
            uint32_t IREGION: 8; //!< number of supported instruction regions
            uint32_t RESERVED1: 8;
        } bits;

        uint32_t value = 0;
    };

    union CTRL {
        struct Bits {
            uint32_t ENABLE: 1; //!< enables the MPU
            uint32_t HFNMIENA: 1; //!< enables MPU during hard fault and NMI exception handlers
            uint32_t PRIVDEFENA: 1; //!< enables use of the default memory map as a background region for privileged software accesses
            uint32_t RESERVED: 29;
        } bits;

        uint32_t value = 0;
    };

    union RBAR {
        struct Bits {
            uint32_t REGION: 4; //!< index of the selected region
            uint32_t VALID: 1; //!< use the value of REGION field to select the region and also update value of region number register
            uint32_t ADDR: 27; //!< base address of the selected region
        } bits;

        uint32_t value = 0;
    };

    union RASR {
        enum class AccessPermission : uint8_t {
            NO_ACCESS = 0b000, //!< no access for any privilege level
            PRIV_RW = 0b001, //!< privileged access only, read-write
            PRIV_RW_UNPRIV_RO = 0b010, //!< privileged read-write, unprivileged read-only
            RW = 0b011, //!< full read-write access
            RESERVED = 0b100, //!< reserved
            PRIV_RO = 0b101, //!< privileged read-only
            RO1 = 0b110, //!< read-only for all privilege levels
            RO2 = 0b111 //!< read-only for all privilege levels
        };

        enum class MemoryType : uint8_t {
            STRONGLY_ORDERED = 0b000, //!< strongly ordered, shareable
            DEVICE_SHAREABLE = 0b001, //!< device, shareable
            NORMAL_WT_NO_WA = 0b010, //!< normal, write-through, no write allocate
            NORMAL_WB_NO_WA = 0b011, //!< normal, write-back, no write allocate
            NORMAL_NON_CACHEABLE = 0b100, //!< normal, non-cacheable
            RESERVED = 0b101, //!< reserved
            NORMAL_WB_WA = 0b110, //!< normal, write-back, write allocate
            DEVICE_NON_SHAREABLE = 0b111 //!< device, non-shareable
        };

        struct Bits {
            uint32_t ENABLE: 1; //!< region enabled
            uint32_t SIZE: 5; //!< region size exponent (size = 2^(SIZE + 1) bytes)
            uint32_t RESERVED0: 2;
            uint32_t SRD: 8; //!< sub-region disable bitmap
            uint32_t B: 1; //!< bufferable attribute
            uint32_t C: 1; //!< cacheable attribute
            uint32_t S: 1; //!< shareable attribute
            uint32_t TEX: 3; //!< type extension field
            uint32_t RESERVED1: 2;
            uint32_t AP: 3; //!< access permission
            uint32_t RESERVED2: 1;
            uint32_t XN: 1; //!< eXecute Never (instruction fetches disabled)
            uint32_t RESERVED3: 3;
        } bits;

        uint32_t value = 0;
    };
}

namespace Cortex::M3 {
    inline volatile Mpu::Registers* const MPU = reinterpret_cast<volatile Mpu::Registers*>(Mpu::BASE_ADDRESS);
}

namespace Cortex::M3::Mpu {
    static inline void configureRegion(uint32_t idx, uint32_t base_addr, const RASR& attributes)
    {
        MPU->RNR = idx;

        RBAR base_addr_reg;
        base_addr_reg.bits.ADDR = base_addr >> 5; // Cortex-M3 requires alignment to region size
        MPU->RBAR = base_addr_reg.value;

        MPU->RASR = attributes.value;

        dataSyncBarrier();
        instrSyncBarrier();
    }

    static inline void setMemoryAttributes(uint32_t idx, bool bufferable, bool cacheable, bool shareable, RASR::MemoryType type)
    {
        MPU->RNR = idx;

        RASR attr { MPU->RASR };
        attr.bits.B = bufferable;
        attr.bits.C = cacheable;
        attr.bits.S = shareable;
        attr.bits.TEX = static_cast<uint8_t>(type);
        MPU->RASR = attr.value;

        dataSyncBarrier();
        instrSyncBarrier();
    }
}
