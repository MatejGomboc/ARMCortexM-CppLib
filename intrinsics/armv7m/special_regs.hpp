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

namespace Cortex::Intrinsics::ARMv7M {
    //! Get BASEPRI register (raw value).
    //! Returns the current base priority mask for exception processing.
    [[gnu::always_inline]] static inline uint32_t getBasepri()
    {
        uint32_t value;
        asm volatile("MRS %0, BASEPRI" : "=r" (value) : : "cc");
        return value;
    }

    //! Set BASEPRI register (raw value).
    //! Sets the base priority mask for exception processing.
    //! Exceptions with priority >= BASEPRI are blocked.
    [[gnu::always_inline]] static inline void setBasepri(uint32_t value)
    {
        asm volatile("MSR BASEPRI, %0" : : "r" (value) : "cc", "memory");
    }

    //! Set BASEPRI_MAX register.
    //! Conditionally sets BASEPRI only if new value is higher priority (lower number)
    //! than current value. Use for raising priority level without risk of lowering it.
    [[gnu::always_inline]] static inline void setBasepriMax(uint32_t value)
    {
        asm volatile("MSR BASEPRI_MAX, %0" : : "r" (value) : "cc", "memory");
    }

    //! Get FAULTMASK register (raw value).
    //! Returns the fault mask that disables all exceptions except NMI.
    [[gnu::always_inline]] static inline uint32_t getFaultmask()
    {
        uint32_t value;
        asm volatile("MRS %0, FAULTMASK" : "=r" (value) : : "cc");
        return value;
    }

    //! Set FAULTMASK register (raw value).
    //! When set to 1, disables all exceptions except NMI.
    //! Automatically cleared on exception return.
    [[gnu::always_inline]] static inline void setFaultmask(uint32_t value)
    {
        asm volatile("MSR FAULTMASK, %0" : : "r" (value) : "cc", "memory");
    }
}
