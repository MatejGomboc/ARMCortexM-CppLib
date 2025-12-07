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

namespace ArmCortex {
    //! Enable interrupts (clear PRIMASK).
    //! Enables all interrupts with configurable priority.
    [[gnu::always_inline]] static inline void asmCpsie()
    {
        asm volatile("cpsie i" : : : "memory");
    }

    //! Disable interrupts (set PRIMASK).
    //! Disables all interrupts with configurable priority.
    //! NMI and HardFault remain enabled.
    [[gnu::always_inline]] static inline void asmCpsid()
    {
        asm volatile("cpsid i" : : : "memory");
    }

    //! Enable faults (clear FAULTMASK).
    //! Enables all exceptions except NMI.
    //! \note Available on ARMv7-M (Cortex-M3, M4, M7) only.
    [[gnu::always_inline]] static inline void asmCpsieF()
    {
        asm volatile("cpsie f" : : : "memory");
    }

    //! Disable faults (set FAULTMASK).
    //! Disables all exceptions except NMI.
    //! Escalates all faults to HardFault which is then ignored.
    //! \note Available on ARMv7-M (Cortex-M3, M4, M7) only.
    [[gnu::always_inline]] static inline void asmCpsidF()
    {
        asm volatile("cpsid f" : : : "memory");
    }

    //! Supervisor Call.
    //! Triggers SVCall exception with immediate value for handler identification.
    //! \tparam value 8-bit immediate value (0-255) passed to SVCall handler.
    template<uint8_t value>
    [[gnu::always_inline]] static inline void asmSvc()
    {
        asm volatile("svc %0" : : "i" (static_cast<uint16_t>(value)));
    }
}
