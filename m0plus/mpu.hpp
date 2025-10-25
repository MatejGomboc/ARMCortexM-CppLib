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

#include "intrinsics/barriers.hpp"
#include <cstdint>

namespace Cortex::M0Plus::Mpu {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000ED90u;

    struct Registers {
        volatile uint32_t TYPE; //!< Indicates whether the MPU is present, and if so, how many regions it supports.
        volatile uint32_t CTRL; //!< MPU control register.
        volatile uint32_t RNR; //!< Region number register (selects a region to edit its attributes).
        volatile uint32_t RBAR; //!< Region base address register.
        volatile uint32_t RASR; //!< Region attribute and size register.
    };

    //! Indicates whether the MPU is present, and if so, how many regions it supports.
    union TYPE {
        struct Bits {
            uint32_t SEPARATE: 1; //!< Indicates support for unified or separate instruction and data memory (always 0).
            uint32_t RESERVED0: 7;
            uint32_t DREGION: 8; //!< Number of supported data regions.
            uint32_t IREGION: 8; //!< Number of supported instruction regions (always 0).
            uint32_t RESERVED1: 8;
        } bits;

        uint32_t value = 0;

        TYPE() = default;

        TYPE(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! MPU control register.
    union CTRL {
        struct Bits {
            uint32_t ENABLE: 1; //!< Enable MPU.
            uint32_t HFNMIENA: 1; //!< Enable MPU during HardFault and NMI.
            uint32_t PRIVDEFENA: 1; //!< Enable default memory map for privileged access.
            uint32_t RESERVED: 29;
        } bits;

        uint32_t value = 0;

        CTRL() = default;

        CTRL(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Region base address register.
    union RBAR {
        struct Bits {
            uint32_t REGION: 4; //!< Region number.
            uint32_t VALID: 1; //!< Region number valid (write 1 to update RNR).
            uint32_t ADDR: 27; //!< Region base address.
        } bits;

        uint32_t value = 0;

        RBAR() = default;

        RBAR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Region attribute and size register.
    union RASR {
        //! Access permission field values.
        enum class AP : uint8_t {
            NO_ACCESS = 0b000, //!< No access.
            PRIV_RW = 0b001, //!< Privileged read-write.
            PRIV_RW_UNPRIV_RO = 0b010, //!< Privileged read-write, unprivileged read-only.
            RW = 0b011, //!< Read-write.
            PRIV_RO = 0b101, //!< Privileged read-only.
            RO = 0b110, //!< Read-only.
            RO_ALT = 0b111 //!< Read-only (alternative encoding).
        };

        //! Memory attributes flags values.
        enum class SCB : uint8_t {
            PERIPHERAL = 0b011, //!< Device peripherals.
            FLASH = 0b100, //!< Flash memory.
            INTERN_SRAM = 0b101, //!< Internal SRAM.
            EXTERN_SRAM = 0b111 //!< External SRAM.
        };

        struct Bits {
            uint32_t ENABLE: 1; //!< Enable region.
            uint32_t SIZE: 5; //!< Region size (minimum value: 7).
            uint32_t RESERVED0: 2;
            uint32_t SRD: 8; //!< Subregion disable bits.
            uint32_t B: 1; //!< Bufferable attribute.
            uint32_t C: 1; //!< Cacheable attribute.
            uint32_t S: 1; //!< Shareable attribute.
            uint32_t TEX: 3; //!< Type extension field (must always be 0 on M0+).
            uint32_t RESERVED1: 2;
            uint32_t AP: 3; //!< Access permission.
            uint32_t RESERVED2: 1;
            uint32_t XN: 1; //!< Instruction access disable.
            uint32_t RESERVED3: 3;
        } bits;

        uint32_t value = 0;

        RASR() = default;

        RASR(uint32_t new_value)
        {
            value = new_value;
        }

        //! Helper method for setting S, C, B flags from SCB enum value.
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
