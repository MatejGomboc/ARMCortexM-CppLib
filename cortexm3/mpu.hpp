/*
    Copyright (C) 2025 Matej Gomboc <https://github.com/MatejGomboc/ARMCortexM-CppLib>

    Licensed under the Apache License, Version 2.0 (the "Licence");
    you may not use this file except in compliance with the Licence.
    You may obtain a copy of the Licence at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the Licence for the specific language governing permissions and
    limitations under the Licence.
*/

#pragma once

#include <cstdint>

namespace CortexM3::Mpu {
    static uint32_t* const BASE_ADDR = reinterpret_cast<uint32_t*>(0xE000ED90);

    union Type {
        struct Bits {
            uint32_t separate_regions: 1; //!< support for unified/separate instruction and data regions
            uint32_t reserved0: 7;
            uint32_t num_of_data_regions: 8; //!< number of supported data regions
            uint32_t num_of_instr_regions: 8; //!< number of supported instruction regions
            uint32_t reserved1: 8;
        } bits;

        uint32_t value = 0;
    };

    union Control {
        struct Bits {
            uint32_t enabled: 1; //!< enables the MPU
            uint32_t enabled_in_hardfault_nmi: 1; //!< enables MPU during hard fault and NMI exception handlers
            uint32_t enabled_default_map: 1; //!< enables use of the default memory map as a background region for privileged software accesses
            uint32_t reserved: 29;
        } bits;

        uint32_t value = 0;
    };

    union RegionBaseAddress {
        struct Bits {
            uint32_t region_idx: 4; //!< index of the selected region
            uint32_t use_region_idx: 1; //!< use the value of region_idx field to select the region and also update value of region index register
            uint32_t region_base_addr: 27; //!< base address of the selected region
        } bits;

        uint32_t value = 0;
    };

    union RegionAttributes {
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

        // Use the same simple memory type enum as CortexM0+
        enum class MemoryType : uint8_t {
            PERIPHERAL = 0b011, //!< device peripherals
            FLASH = 0b100, //!< flash memory
            INTERN_SRAM = 0b101, //!< internal SRAM
            EXTERN_SRAM = 0b111 //!< external SRAM
        };

        struct Bits {
            uint32_t enabled: 1; //!< region enabled
            uint32_t size_exp: 5; //!< region size exponent (size = 2^(size_exp + 1) bytes)
            uint32_t reserved0: 2;
            uint32_t disabled_subregions: 8; //!< bitmap of disabled sub-regions
            uint32_t bufferable: 1; //!< bufferable attribute
            uint32_t cacheable: 1; //!< cacheable attribute
            uint32_t shareable: 1; //!< shareable attribute
            uint32_t memory_type_ext: 3; //!< type extension field (used internally)
            uint32_t reserved1: 2;
            uint32_t access_permission: 3; //!< region access permission
            uint32_t reserved2: 1;
            uint32_t instrs_fetch_disabled: 1; //!< instruction fetches disabled
            uint32_t reserved3: 3;
        } bits;

        uint32_t value = 0;
    };

    struct Registers {
        volatile uint32_t type; //!< indicates whether the MPU is present, and if so, how many regions it supports
        volatile uint32_t control; //!< MPU control register
        volatile uint32_t region_idx; //!< region index register (selects a region to edit its attributes)
        volatile uint32_t region_base_address; //!< region base address register
        volatile uint32_t region_attributes; //!< region attributes register
    };

    static inline volatile Registers* registers()
    {
        return reinterpret_cast<volatile Registers*>(BASE_ADDR);
    }

    // Helper function to configure memory attributes based on simple memory type
    static inline void configureMemoryType(RegionAttributes& attr, RegionAttributes::MemoryType type)
    {
        switch (type) {
            case RegionAttributes::MemoryType::PERIPHERAL:
                // Device memory for peripherals: non-cacheable, bufferable, shareable
                attr.bits.bufferable = 1;
                attr.bits.cacheable = 0;
                attr.bits.shareable = 1;
                attr.bits.memory_type_ext = 0b001; // Device shareable
                break;
            
            case RegionAttributes::MemoryType::FLASH:
                // Flash memory: cacheable (read-only), non-bufferable
                attr.bits.bufferable = 0;
                attr.bits.cacheable = 1;
                attr.bits.shareable = 0;
                attr.bits.memory_type_ext = 0b010; // Normal, write-through
                break;
            
            case RegionAttributes::MemoryType::INTERN_SRAM:
                // Internal SRAM: fully cacheable with write-back
                attr.bits.bufferable = 1;
                attr.bits.cacheable = 1;
                attr.bits.shareable = 0;
                attr.bits.memory_type_ext = 0b011; // Normal, write-back
                break;
            
            case RegionAttributes::MemoryType::EXTERN_SRAM:
                // External SRAM: cacheable with write-back, shareable
                attr.bits.bufferable = 1;
                attr.bits.cacheable = 1;
                attr.bits.shareable = 1;
                attr.bits.memory_type_ext = 0b110; // Normal, write-back with allocate
                break;
        }
    }

    // Simplified region configuration function using the intuitive memory types
    static inline void configureRegion(uint32_t idx, uint32_t base_addr, uint32_t size_exp,
                                     RegionAttributes::MemoryType mem_type,
                                     RegionAttributes::AccessPermission access_perm,
                                     bool enable = true)
    {
        registers()->region_idx = idx;

        RegionBaseAddress base_addr_reg;
        base_addr_reg.bits.region_base_addr = base_addr >> 5; // Cortex-M3 requires alignment to region size
        registers()->region_base_address = base_addr_reg.value;

        RegionAttributes attr;
        attr.bits.enabled = enable ? 1 : 0;
        attr.bits.size_exp = size_exp;
        attr.bits.disabled_subregions = 0; // All subregions enabled by default
        attr.bits.access_permission = static_cast<uint8_t>(access_perm);
        attr.bits.instrs_fetch_disabled = 0; // Allow instruction fetches by default
        
        // Configure memory attributes based on simple type
        configureMemoryType(attr, mem_type);
        
        registers()->region_attributes = attr.value;

        asm volatile("DSB" : : : "memory");
        asm volatile("ISB" : : : "memory");
    }

    // Legacy function for backward compatibility (uses the original complex interface)
    static inline void configureRegion(uint32_t idx, uint32_t base_addr, const RegionAttributes& attributes)
    {
        registers()->region_idx = idx;

        RegionBaseAddress base_addr_reg;
        base_addr_reg.bits.region_base_addr = base_addr >> 5; // Cortex-M3 requires alignment to region size
        registers()->region_base_address = base_addr_reg.value;

        registers()->region_attributes = attributes.value;

        asm volatile("DSB" : : : "memory");
        asm volatile("ISB" : : : "memory");
    }

    // Advanced function for users who need fine control over cache attributes
    // (kept for backward compatibility, but most users should use the simplified configureRegion)
    static inline void setMemoryAttributes(uint32_t idx, bool bufferable, bool cacheable, bool shareable, uint8_t type_ext)
    {
        registers()->region_idx = idx;

        RegionAttributes attr { registers()->region_attributes };
        attr.bits.bufferable = bufferable;
        attr.bits.cacheable = cacheable;
        attr.bits.shareable = shareable;
        attr.bits.memory_type_ext = type_ext & 0x07;
        registers()->region_attributes = attr.value;

        asm volatile("DSB" : : : "memory");
        asm volatile("ISB" : : : "memory");
    }
}