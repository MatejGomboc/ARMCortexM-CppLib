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

namespace Cortex::M3::Mpu {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000ED90u;

    struct Registers {
        volatile uint32_t TYPE; //!< Indicates whether the MPU is present, and if so, how many regions it supports.
        volatile uint32_t CTRL; //!< MPU control register.
        volatile uint32_t RNR; //!< Region number register (selects a region to edit its attributes).
        volatile uint32_t RBAR; //!< Region base address register.
        volatile uint32_t RASR; //!< Region attribute and size register.
        volatile uint32_t RBAR_A1; //!< Alias 1 region base address register.
        volatile uint32_t RASR_A1; //!< Alias 1 region attribute and size register.
        volatile uint32_t RBAR_A2; //!< Alias 2 region base address register.
        volatile uint32_t RASR_A2; //!< Alias 2 region attribute and size register.
        volatile uint32_t RBAR_A3; //!< Alias 3 region base address register.
        volatile uint32_t RASR_A3; //!< Alias 3 region attribute and size register.
    };

    //! Indicates whether the MPU is present, and if so, how many regions it supports.
    union TYPE {
        struct Bits {
            uint32_t SEPARATE: 1; //!< Indicates support for unified or separate instruction and data memory.
            uint32_t RESERVED0: 7;
            uint32_t DREGION: 8; //!< Number of supported data regions.
            uint32_t IREGION: 8; //!< Number of supported instruction regions.
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
            RESERVED = 0b100, //!< Reserved.
            PRIV_RO = 0b101, //!< Privileged read-only.
            RO = 0b110, //!< Read-only.
            RO_ALT = 0b111 //!< Read-only (alternative encoding).
        };

        //! Type extension, cache and shareable attributes.
        enum class TEX_C_B : uint8_t {
            STRONGLY_ORDERED = 0b00000, //!< Strongly-ordered, always shareable.
            DEVICE_SHAREABLE = 0b00001, //!< Device, shareable.
            NORMAL_WT_NO_WA_S = 0b00010, //!< Normal, write-through, no write allocate, shareable.
            NORMAL_WB_NO_WA_S = 0b00011, //!< Normal, write-back, no write allocate, shareable.
            NORMAL_NON_CACHEABLE_S = 0b00100, //!< Normal, non-cacheable, shareable.
            NORMAL_WB_WA_S = 0b00110, //!< Normal, write-back, write allocate, shareable.
            DEVICE_NON_SHAREABLE = 0b00111, //!< Device, non-shareable.
            NORMAL_WT_NO_WA = 0b01010, //!< Normal, write-through, no write allocate, non-shareable.
            NORMAL_WB_NO_WA = 0b01011, //!< Normal, write-back, no write allocate, non-shareable.
            NORMAL_NON_CACHEABLE = 0b01100, //!< Normal, non-cacheable, non-shareable.
            NORMAL_WB_WA = 0b01110 //!< Normal, write-back, write allocate, non-shareable.
        };

        struct Bits {
            uint32_t ENABLE: 1; //!< Enable region.
            uint32_t SIZE: 5; //!< Region size (size = 2^(SIZE+1) bytes, minimum SIZE value: 4 for 32 bytes).
            uint32_t RESERVED0: 2;
            uint32_t SRD: 8; //!< Subregion disable bits.
            uint32_t B: 1; //!< Bufferable attribute.
            uint32_t C: 1; //!< Cacheable attribute.
            uint32_t S: 1; //!< Shareable attribute.
            uint32_t TEX: 3; //!< Type extension field.
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

        //! Helper method to set TEX, C, B, S flags from TEX_C_B enum value.
        void setTexCbFlags(TEX_C_B tex_c_b)
        {
            constexpr uint8_t B_BIT_POS = 16;
            uint8_t flags = static_cast<uint8_t>(tex_c_b);
            value = (value & ~(0x1Fu << B_BIT_POS)) | (static_cast<uint32_t>(flags) << B_BIT_POS);
        }
    };
}

namespace Cortex::M3 {
    inline volatile Mpu::Registers* const MPU = reinterpret_cast<volatile Mpu::Registers*>(Mpu::BASE_ADDRESS);
}

namespace Cortex::M3::Mpu {
    static inline void configureRegion(uint8_t region_number, uint32_t base_address, const RASR& region_attributes)
    {
        MPU->RNR = region_number;

        RBAR region_base;
        region_base.bits.ADDR = (base_address >> 5) & 0x7FFFFFF;
        MPU->RBAR = region_base.value;

        MPU->RASR = region_attributes.value;

        dataSyncBarrier();
        instrSyncBarrier();
    }
}
