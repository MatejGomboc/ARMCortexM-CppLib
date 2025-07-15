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

namespace CortexM0Plus {
    static constexpr uint8_t NUM_OF_IRQS = 32;

    enum class ExceptionNumber : uint8_t {
        THREAD_MODE = 0,
        RESET = 1,
        NMI = 2,
        HARD_FAULT = 3,
        SV_CALL = 11,
        PEND_SV = 14,
        SYS_TICK = 15,
        FIRST_IRQ = 16,
        LAST_IRQ = FIRST_IRQ + NUM_OF_IRQS - 1
    };

    static inline void enableExceptions()
    {
        asm volatile("cpsie i" : : : "memory");
        DataSyncBarrier();
        InstrSyncBarrier();
    }

    static inline void disableExceptions()
    {
        asm volatile("cpsid i" : : : "memory");
        DataSyncBarrier();
        InstrSyncBarrier();
    }

    static constexpr bool isIrqNumber(ExceptionNumber exception)
    {
        return (static_cast<uint8_t>(exception) >= static_cast<uint8_t>(ExceptionNumber::FIRST_IRQ) &&
            static_cast<uint8_t>(exception) <= static_cast<uint8_t>(ExceptionNumber::LAST_IRQ));
    }

    static inline void sendEvent()
    {
        asm volatile("sev" : : : "memory");
    }

    static inline void waitForEvent()
    {
        asm volatile("wfe" : : : "memory");
    }

    static inline void waitForIrq()
    {
        asm volatile("wfi" : : : "memory");
    }
}
