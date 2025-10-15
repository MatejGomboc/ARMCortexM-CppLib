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

#include "utils.hpp"
#include <cstdint>

namespace Cortex::M3::Nvic {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000E100u;

    struct Registers
    {
        volatile uint32_t ISER[8]; //!< Interrupt set-enable registers.
        volatile uint32_t RESERVED0[24];
        volatile uint32_t ICER[8]; //!< Interrupt clear-enable registers.
        volatile uint32_t RESERVED1[24];
        volatile uint32_t ISPR[8]; //!< Interrupt set-pending registers.
        volatile uint32_t RESERVED2[24];
        volatile uint32_t ICPR[8]; //!< Interrupt clear-pending registers.
        volatile uint32_t RESERVED3[24];
        volatile uint32_t IABR[8]; //!< Interrupt active bit registers.
        volatile uint32_t RESERVED4[56];
        volatile uint8_t IPR[240]; //!< Interrupt priority registers (byte-accessible).
        volatile uint32_t RESERVED5[644];
        volatile uint32_t STIR; //!< Software trigger interrupt register.
    };
}

namespace Cortex::M3 {
    inline volatile Nvic::Registers* const NVIC = reinterpret_cast<volatile Nvic::Registers*>(Nvic::BASE_ADDRESS);
}

namespace Cortex::M3::Nvic {
    static inline bool isIrqEnabled(uint8_t irq_number)
    {
        uint8_t reg_idx = irq_number / 32;
        uint8_t bit_idx = irq_number % 32;
        return Cortex::isBitSet(NVIC->ISER[reg_idx], bit_idx);
    }

    static inline void enableIrq(uint8_t irq_number)
    {
        uint8_t reg_idx = irq_number / 32;
        uint8_t bit_idx = irq_number % 32;
        Cortex::setBit(NVIC->ISER[reg_idx], bit_idx);
    }

    static inline void disableIrq(uint8_t irq_number)
    {
        uint8_t reg_idx = irq_number / 32;
        uint8_t bit_idx = irq_number % 32;
        Cortex::setBit(NVIC->ICER[reg_idx], bit_idx);
    }

    static inline bool isIrqPending(uint8_t irq_number)
    {
        uint8_t reg_idx = irq_number / 32;
        uint8_t bit_idx = irq_number % 32;
        return Cortex::isBitSet(NVIC->ISPR[reg_idx], bit_idx);
    }

    static inline void setPendingIrq(uint8_t irq_number)
    {
        uint8_t reg_idx = irq_number / 32;
        uint8_t bit_idx = irq_number % 32;
        Cortex::setBit(NVIC->ISPR[reg_idx], bit_idx);
    }

    static inline void clearPendingIrq(uint8_t irq_number)
    {
        uint8_t reg_idx = irq_number / 32;
        uint8_t bit_idx = irq_number % 32;
        Cortex::setBit(NVIC->ICPR[reg_idx], bit_idx);
    }

    static inline bool isIrqActive(uint8_t irq_number)
    {
        uint8_t reg_idx = irq_number / 32;
        uint8_t bit_idx = irq_number % 32;
        return Cortex::isBitSet(NVIC->IABR[reg_idx], bit_idx);
    }
}
