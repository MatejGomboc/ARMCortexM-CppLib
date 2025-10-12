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
            //! Indicates support for unified or separate instruction and date memory maps: 0 = Unified.
            uint32_t SEPARATE: 1;

            uint32_t RESERVED0: 7;

            //! Indicates the number of supported MPU data regions:
            //! 0x00 = Zero regions if the device does not include the MPU.
            //! 0x08 = Eight regions if the device includes the MPU.
            uint32_t DREGION: 8;

            //! Indicates the number of supported MPU instruction regions.
            //! Always contains 0x00. The MPU memory map is unified and is described by the DREGION field.
            uint32_t IREGION: 8;

            uint32_t RESERVED1: 8;
        } bits;

        uint32_t value = 0;
    };

    //! MPU control register.
    //! Enables the MPU.
    //! Enables the default memory map background region.
    //! Enables use of the MPU when in the HardFault or Non-Maskable Interrupt (NMI) handler.
    union CTRL {
        struct Bits {
            //! Enables the MPU.
            //! 0: MPU disabled.
            //! 1: MPU enabled.
            uint32_t ENABLE: 1;

            //! Enables the operation of MPU during HardFault and NMI handlers.
            //! When the MPU is enabled:
            //! 0 = MPU is disabled during HardFault and NMI handlers, regardless of the value of the ENABLE bit.
            //! 1 = the MPU is enabled during HardFault and NMI handlers.
            //! When the MPU is disabled, if this bit is set to 1 the behavior is Unpredictable.
            uint32_t HFNMIENA: 1;

            //! Enable privileged software access to default memory map.
            //! 0: If the MPU is enabled, disables use of the default memory map. Any memory access to a location not covered by any
            //! enabled region causes a fault.
            //! 1: If the MPU is enabled, enables use of the default memory map as a background region for privileged software accesses.
            //! When enabled, the background region acts as if it is region number -1. Any region that is defined and enabled has priority over
            //! this default map.
            //! If the MPU is disabled, the processor ignores this bit.
            uint32_t PRIVDEFENA: 1;

            uint32_t RESERVED: 29;
        } bits;

        uint32_t value = 0;
    };

    //! Region base address register.
    union RBAR {
        struct Bits {
            //! MPU region field.
            //! For the behavior on writes, see the description of the VALID field.
            //! On reads, returns the current region number, as specified by the MPU_RNR register.
            uint32_t REGION: 4;

            //! MPU region number valid.
            //! Write:
            //! 0: MPU_RNR register not changed, and the processor:
            //! Updates the base address for the region specified in the MPU_RNR.
            //! Ignores the value of the REGION field.
            //! 1: the processor:
            //! Updates the value of the MPU_RNR to the value of the REGION field.
            //! Updates the base address for the region specified in the REGION field.
            //! Read:
            //! Always read as zero.
            uint32_t VALID: 1;

            //! Region base address field.
            //! The value of N depends on the region size.
            uint32_t ADDR: 27;
        } bits;

        uint32_t value = 0;
    };

    //! Region attribute and size register.
    union RASR {
        //! Access permission field values.
        enum class AP : uint8_t {
            NO_ACCESS = 0b000, //!< no access for any privilege level
            PRIV_RW = 0b001, //!< privileged access only, read-write
            PRIV_RW_UNPRIV_RO = 0b010, //!< privileged read-write, unprivileged read-only
            RW = 0b011, //!< full read-write access
            RESERVED = 0b100, //!< reserved
            PRIV_RO = 0b101, //!< privileged read-only
            RO1 = 0b110, //!< read-only for all privilege levels
            RO2 = 0b111 //!< read-only for all privilege levels
        };

        //! Memory region type field values.
        enum class MemoryType : uint8_t {
            PERIPHERAL = 0b011, //!< device peripherals
            FLASH = 0b100, //!< flash memory
            INTERN_SRAM = 0b101, //!< internal SRAM
            EXTERN_SRAM = 0b111 //!< external SRAM
        };

        struct Bits {
            //! Enables the MPU protection region.
            //! 0 = Region disabled.
            //! 1 = Region enabled.
            uint32_t ENABLE: 1;

            //! Size of the MPU protection region.
            //! Specifies the size of the MPU region. The minimum permitted value is 7 (b00111).
            uint32_t SIZE: 5;

            uint32_t RESERVED0: 2;

            //! Subregion disable bits.
            //! For each bit in this field:
            //! 0 = Corresponding sub-region is enabled.
            //! 1 = Corresponding sub-region is disabled.
            uint32_t SRD: 8;

            //! Memory region type field.
            uint32_t TYPE: 3;

            uint32_t RESERVED1: 5;

            //! Access permission field.
            uint32_t AP: 3;

            uint32_t RESERVED2: 1;

            //! Instruction access disable bit:
            //! 0 = Instruction fetches enabled.
            //! 1 = Instruction fetches disabled.
            uint32_t XN: 1;

            uint32_t RESERVED3: 3;
        } bits;

        uint32_t value = 0;
    };
}

namespace Cortex::M0Plus {
    inline volatile Mpu::Registers* const MPU = reinterpret_cast<volatile Mpu::Registers*>(Mpu::BASE_ADDRESS);
}

namespace Cortex::M0Plus::Mpu {
    static inline void configureRegion(uint32_t idx, uint32_t base_addr, const RASR& attributes)
    {
        MPU->RNR = idx;

        RBAR base_addr_reg;
        base_addr_reg.bits.ADDR = base_addr & 0x7FFFFFF;
        MPU->RBAR = base_addr_reg.value;

        MPU->RASR = attributes.value;

        dataSyncBarrier();
        instrSyncBarrier();
    }
}
