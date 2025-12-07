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

#include "armcortex/bit_utils.hpp"
#include <cstdint>

namespace ArmCortex::Nvic {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000E100u;

    struct Registers
    {
        volatile uint32_t ISER[8]; //!< Interrupt set-enable registers (W1S).
        volatile uint32_t RESERVED0[24];
        volatile uint32_t ICER[8]; //!< Interrupt clear-enable registers (W1C).
        volatile uint32_t RESERVED1[24];
        volatile uint32_t ISPR[8]; //!< Interrupt set-pending registers (W1S).
        volatile uint32_t RESERVED2[24];
        volatile uint32_t ICPR[8]; //!< Interrupt clear-pending registers (W1C).
        volatile uint32_t RESERVED3[24];
        volatile uint32_t IABR[8]; //!< Interrupt active bit registers.
        volatile uint32_t RESERVED4[56];
        volatile uint8_t IPR[240]; //!< Interrupt priority registers (byte-accessible).
        volatile uint32_t RESERVED5[644];
        volatile uint32_t STIR; //!< Software trigger interrupt register.
    };
}

namespace ArmCortex {
    inline volatile Nvic::Registers* const NVIC = reinterpret_cast<volatile Nvic::Registers*>(Nvic::BASE_ADDRESS);
}

namespace ArmCortex::Nvic {
    [[gnu::always_inline]] static inline bool isIrqEnabled(uint8_t irq_number)
    {
        return ArmCortex::isBitSet(NVIC->ISER[irq_number / 32], irq_number % 32);
    }

    //! Enable an interrupt. ISER is W1S (write-1-to-set).
    [[gnu::always_inline]] static inline void enableIrq(uint8_t irq_number)
    {
        NVIC->ISER[irq_number / 32] = uint32_t{1} << (irq_number % 32);
    }

    //! Disable an interrupt. ICER is W1C (write-1-to-clear).
    [[gnu::always_inline]] static inline void disableIrq(uint8_t irq_number)
    {
        NVIC->ICER[irq_number / 32] = uint32_t{1} << (irq_number % 32);
    }

    [[gnu::always_inline]] static inline bool isIrqPending(uint8_t irq_number)
    {
        return ArmCortex::isBitSet(NVIC->ISPR[irq_number / 32], irq_number % 32);
    }

    //! Set an interrupt pending. ISPR is W1S (write-1-to-set).
    [[gnu::always_inline]] static inline void setPendingIrq(uint8_t irq_number)
    {
        NVIC->ISPR[irq_number / 32] = uint32_t{1} << (irq_number % 32);
    }

    //! Clear a pending interrupt. ICPR is W1C (write-1-to-clear).
    [[gnu::always_inline]] static inline void clearPendingIrq(uint8_t irq_number)
    {
        NVIC->ICPR[irq_number / 32] = uint32_t{1} << (irq_number % 32);
    }

    [[gnu::always_inline]] static inline bool isIrqActive(uint8_t irq_number)
    {
        return ArmCortex::isBitSet(NVIC->IABR[irq_number / 32], irq_number % 32);
    }
}
