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

#include "barriers.hpp"
#include <cstdint>

namespace Cortex::M0Plus::Mpu {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000ED90u;

    struct Registers
    {
        volatile uint32_t TYPE;
        volatile uint32_t CTRL;
        volatile uint32_t RNR;
        volatile uint32_t RBAR;
        volatile uint32_t RASR;
    };

    union TYPE {
        struct Bits {
            uint32_t SEPARATE: 1;
            uint32_t RESERVED0: 7;
            uint32_t DREGION: 8;
            uint32_t IREGION: 8;
            uint32_t RESERVED1: 8;
        } bits;
        uint32_t value = 0;
        TYPE() = default;
        TYPE(uint32_t new_value)
        {
            value = new_value;
        }
    };

    union CTRL {
        struct Bits {
            uint32_t ENABLE: 1;
            uint32_t HFNMIENA: 1;
            uint32_t PRIVDEFENA: 1;
            uint32_t RESERVED: 29;
        } bits;
        uint32_t value = 0;
        CTRL() = default;
        CTRL(uint32_t new_value)
        {
            value = new_value;
        }
    };

    union RBAR {
        struct Bits {
            uint32_t REGION: 4;
            uint32_t VALID: 1;
            uint32_t ADDR: 27;
        } bits;
        uint32_t value = 0;
        RBAR() = default;
        RBAR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    union RASR {
        enum class AP : uint8_t {
            NO_ACCESS = 0b000,
            PRIV_RW = 0b001,
            PRIV_RW_UNPRIV_RO = 0b010,
            RW = 0b011,
            PRIV_RO = 0b101,
            RO = 0b110,
            RO_ALT = 0b111
        };
        enum class SCB : uint8_t {
            PERIPHERAL = 0b011,
            FLASH = 0b100,
            INTERN_SRAM = 0b101,
            EXTERN_SRAM = 0b111
        };
        struct Bits {
            uint32_t ENABLE: 1;
            uint32_t SIZE: 5;
            uint32_t RESERVED0: 2;
            uint32_t SRD: 8;
            uint32_t B: 1;
            uint32_t C: 1;
            uint32_t S: 1;
            uint32_t TEX: 3;
            uint32_t RESERVED1: 2;
            uint32_t AP: 3;
            uint32_t RESERVED2: 1;
            uint32_t XN: 1;
            uint32_t RESERVED3: 3;
        } bits;
        uint32_t value = 0;
        RASR() = default;
        RASR(uint32_t new_value)
        {
            value = new_value;
        }
        void setScbFlags(SCB scb)
        {
            constexpr uint8_t SCB_BIT_POS = 16;
            value = (value & ~(0x7u << SCB_BIT_POS)) | (static_cast<uint32_t>(scb) << SCB_BIT_POS);
        }
    };
}

namespace Cortex::M0Plus {
    inline volatile Mpu::Registers* const MPU = reinterpret_cast<volatile Mpu::Registers*>(Mpu::BASE_ADDRESS);
}

namespace Cortex::M0Plus::Mpu {
    static inline void configureRegion(uint8_t region_number, uint32_t base_address, const RASR& region_attributes)
    {
        MPU->RNR = region_number;
        RBAR region_base;
        region_base.bits.ADDR = (base_address >> 5) & 0x7FFFFFF;
        MPU->RBAR = region_base.value;
        MPU->RASR = region_attributes.value;
        asmDsb();
        asmIsb();
    }
}
