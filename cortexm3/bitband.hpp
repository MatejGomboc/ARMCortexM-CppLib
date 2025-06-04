/*
    Copyright (C) 2025 Matej Gomboc <https://github.com/MatejGomboc/ARMCortexM-CppLib>

    Licensed under the Apache License, Version 2.0 (the "Licence");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once

#include <cstdint>

namespace CortexM3::BitBand {
    // Bit-band regions
    static constexpr uint32_t SRAM_BASE = 0x20000000;
    static constexpr uint32_t SRAM_BB_BASE = 0x22000000;
    static constexpr uint32_t PERIPH_BASE = 0x40000000;
    static constexpr uint32_t PERIPH_BB_BASE = 0x42000000;
    
    // Region sizes
    static constexpr uint32_t REGION_SIZE = 0x00100000; // 1MB
    
    //! Get bit-band alias address for a specific bit in SRAM region
    template<typename T>
    static inline volatile uint32_t* sramBitBand(volatile T* addr, uint8_t bit)
    {
        uint32_t addr_val = reinterpret_cast<uint32_t>(addr);
        uint32_t bit_word_offset = (addr_val - SRAM_BASE) * 32 + bit * 4;
        return reinterpret_cast<volatile uint32_t*>(SRAM_BB_BASE + bit_word_offset);
    }
    
    //! Get bit-band alias address for a specific bit in peripheral region
    template<typename T>
    static inline volatile uint32_t* periphBitBand(volatile T* addr, uint8_t bit)
    {
        uint32_t addr_val = reinterpret_cast<uint32_t>(addr);
        uint32_t bit_word_offset = (addr_val - PERIPH_BASE) * 32 + bit * 4;
        return reinterpret_cast<volatile uint32_t*>(PERIPH_BB_BASE + bit_word_offset);
    }
    
    //! Set a bit using bit-banding (SRAM region)
    template<typename T>
    static inline void setSramBit(volatile T* addr, uint8_t bit)
    {
        *sramBitBand(addr, bit) = 1;
    }
    
    //! Clear a bit using bit-banding (SRAM region)
    template<typename T>
    static inline void clearSramBit(volatile T* addr, uint8_t bit)
    {
        *sramBitBand(addr, bit) = 0;
    }
    
    //! Read a bit using bit-banding (SRAM region)
    template<typename T>
    static inline bool readSramBit(volatile T* addr, uint8_t bit)
    {
        return *sramBitBand(addr, bit) & 1;
    }
    
    //! Set a bit using bit-banding (peripheral region)
    template<typename T>
    static inline void setPeriphBit(volatile T* addr, uint8_t bit)
    {
        *periphBitBand(addr, bit) = 1;
    }
    
    //! Clear a bit using bit-banding (peripheral region)
    template<typename T>
    static inline void clearPeriphBit(volatile T* addr, uint8_t bit)
    {
        *periphBitBand(addr, bit) = 0;
    }
    
    //! Read a bit using bit-banding (peripheral region)
    template<typename T>
    static inline bool readPeriphBit(volatile T* addr, uint8_t bit)
    {
        return *periphBitBand(addr, bit) & 1;
    }
}
