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

namespace CortexM0::Nvic {
    static uint32_t* const BASE_ADDR = reinterpret_cast<uint32_t*>(0xE000E100);

    struct Registers
    {
        volatile uint32_t iser; //!< enables interrupts, and shows which interrupts are enabled
        volatile uint32_t reserved0[31];
        volatile uint32_t icer; //!< disables interrupts, and shows which interrupts are enabled
        volatile uint32_t reserved1[31];
        volatile uint32_t ispr; //!< forces interrupts into pending state, and shows which interrupts are pending
        volatile uint32_t reserved2[31];
        volatile uint32_t icpr; //!< removes pending state from interrupts and shows which interrupts are pending
        volatile uint32_t reserved3[31];
        volatile uint32_t reserved4[64];
        volatile uint8_t ipr[32]; //!< sets priorities of interrupts
    };

    static inline volatile Registers* registers()
    {
        return reinterpret_cast<volatile Registers*>(BASE_ADDR);
    }

    static inline bool isIrqEnabled(uint8_t irq_number)
    {
        return Utils::isBitSet(registers()->iser, irq_number);
    }

    static inline void enableIrq(uint8_t irq_number)
    {
        Utils::setBit(registers()->iser, irq_number);
        asm volatile("DSB" : : : "memory");
        asm volatile("ISB" : : : "memory");
    }

    static inline void disableIrq(uint8_t irq_number)
    {
        Utils::setBit(registers()->icer, irq_number);
        asm volatile("DSB" : : : "memory");
        asm volatile("ISB" : : : "memory");
    }

    static inline bool isIrqPending(uint8_t irq_number)
    {
        return Utils::isBitSet(registers()->ispr, irq_number);
    }

    static inline void setPendingIrq(uint8_t irq_number)
    {
        Utils::setBit(registers()->ispr, irq_number);
        asm volatile("DSB" : : : "memory");
        asm volatile("ISB" : : : "memory");
    }

    static inline void clearPendingIrq(uint8_t irq_number)
    {
        Utils::setBit(registers()->icpr, irq_number);
        asm volatile("DSB" : : : "memory");
        asm volatile("ISB" : : : "memory");
    }
}
