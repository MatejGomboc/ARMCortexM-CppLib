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

namespace Cortex {
    //! Send Event.
    //! Signals an event to all processors in a multiprocessor system.
    //! Can be used to wake up processors waiting in WFE.
    [[gnu::always_inline]] static inline void asmSev()
    {
        asm volatile("sev" : : : "memory");
    }

    //! Wait For Event.
    //! Suspends execution until an event occurs.
    //! The processor enters a low-power state until woken by SEV, interrupt, or debug event.
    [[gnu::always_inline]] static inline void asmWfe()
    {
        asm volatile("wfe" : : : "memory");
    }

    //! Wait For Interrupt.
    //! Suspends execution until an interrupt or debug event occurs.
    //! The processor enters a low-power state (sleep or deep sleep depending on SCR.SLEEPDEEP).
    [[gnu::always_inline]] static inline void asmWfi()
    {
        asm volatile("wfi" : : : "memory");
    }
}
