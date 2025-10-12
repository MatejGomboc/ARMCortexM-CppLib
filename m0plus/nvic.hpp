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

namespace Cortex::M0Plus::Nvic {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000E100u;

    struct Registers
    {
        volatile uint32_t ISER; //!< Enables interrupts and shows which interrupts are enabled.
        volatile uint32_t RESERVED0[31];
        volatile uint32_t ICER; //!< Disables interrupts and shows which interrupts are disabled.
        volatile uint32_t RESERVED1[31];
        volatile uint32_t ISPR; //!< Forces interrupts into pending state and shows which interrupts are pending.
        volatile uint32_t RESERVED2[31];
        volatile uint32_t ICPR; //!< Removes pending state from interrupts and shows which interrupts are pending.
        volatile uint32_t RESERVED3[31];
        volatile uint32_t RESERVED4[64];
        volatile uint8_t IPR[32]; //!< Sets priority of interrupts (byte accessible).
    };
}

namespace Cortex::M0Plus {
    inline volatile Nvic::Registers* const NVIC = reinterpret_cast<volatile Nvic::Registers*>(Nvic::BASE_ADDRESS);
}

namespace Cortex::M0Plus::Nvic {
    static inline bool isIrqEnabled(uint8_t irq_number)
    {
        return Cortex::isBitSet(NVIC->ISER, irq_number);
    }

    static inline void enableIrq(uint8_t irq_number)
    {
        Cortex::setBit(NVIC->ISER, irq_number);
    }

    static inline void disableIrq(uint8_t irq_number)
    {
        Cortex::setBit(NVIC->ICER, irq_number);
    }

    static inline bool isIrqPending(uint8_t irq_number)
    {
        return Cortex::isBitSet(NVIC->ISPR, irq_number);
    }

    static inline void setPendingIrq(uint8_t irq_number)
    {
        Cortex::setBit(NVIC->ISPR, irq_number);
    }

    static inline void clearPendingIrq(uint8_t irq_number)
    {
        Cortex::setBit(NVIC->ICPR, irq_number);
    }
}
