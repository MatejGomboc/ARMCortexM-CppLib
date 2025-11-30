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

namespace Cortex {
    //! Get Link Register value.
    [[gnu::always_inline]] static inline uint32_t asmGetLr()
    {
        uint32_t value;
        asm volatile("MOV %0, LR" : "=r" (value) : : "cc");
        return value;
    }

    //! Get Main Stack Pointer.
    [[gnu::always_inline]] static inline uint32_t asmGetMsp()
    {
        uint32_t value;
        asm volatile("MRS %0, MSP" : "=r" (value) : : "cc");
        return value;
    }

    //! Set Main Stack Pointer.
    [[gnu::always_inline]] static inline void asmSetMsp(uint32_t value)
    {
        asm volatile("MSR MSP, %0" : : "r" (value) : "cc", "memory");
    }

    //! Get Process Stack Pointer.
    [[gnu::always_inline]] static inline uint32_t asmGetPsp()
    {
        uint32_t value;
        asm volatile("MRS %0, PSP" : "=r" (value) : : "cc");
        return value;
    }

    //! Set Process Stack Pointer.
    [[gnu::always_inline]] static inline void asmSetPsp(uint32_t value)
    {
        asm volatile("MSR PSP, %0" : : "r" (value) : "cc", "memory");
    }

    //! Get PRIMASK register (raw value).
    [[gnu::always_inline]] static inline uint32_t asmGetPrimask()
    {
        uint32_t value;
        asm volatile("MRS %0, PRIMASK" : "=r" (value) : : "cc");
        return value;
    }

    //! Set PRIMASK register (raw value).
    [[gnu::always_inline]] static inline void asmSetPrimask(uint32_t value)
    {
        asm volatile("MSR PRIMASK, %0" : : "r" (value) : "cc", "memory");
    }

    //! Get CONTROL register (raw value).
    [[gnu::always_inline]] static inline uint32_t asmGetControl()
    {
        uint32_t value;
        asm volatile("MRS %0, CONTROL" : "=r" (value) : : "cc");
        return value;
    }

    //! Set CONTROL register (raw value).
    [[gnu::always_inline]] static inline void asmSetControl(uint32_t value)
    {
        asm volatile("MSR CONTROL, %0" : : "r" (value) : "cc", "memory");
    }

    //! Get Application Program Status Register (raw value).
    [[gnu::always_inline]] static inline uint32_t asmGetApsr()
    {
        uint32_t value;
        asm volatile("MRS %0, APSR" : "=r" (value) : : "cc");
        return value;
    }

    //! Get Interrupt Program Status Register (raw value).
    [[gnu::always_inline]] static inline uint32_t asmGetIpsr()
    {
        uint32_t value;
        asm volatile("MRS %0, IPSR" : "=r" (value) : : "cc");
        return value;
    }

    //! Get Execution Program Status Register (raw value).
    [[gnu::always_inline]] static inline uint32_t asmGetEpsr()
    {
        uint32_t value;
        asm volatile("MRS %0, EPSR" : "=r" (value) : : "cc");
        return value;
    }

    //! Get combined xPSR register (raw value).
    [[gnu::always_inline]] static inline uint32_t asmGetPsr()
    {
        uint32_t value;
        asm volatile("MRS %0, PSR" : "=r" (value) : : "cc");
        return value;
    }

    //! Get IEPSR (combined IPSR and EPSR) register (raw value).
    [[gnu::always_inline]] static inline uint32_t asmGetIepsr()
    {
        uint32_t value;
        asm volatile("MRS %0, IEPSR" : "=r" (value) : : "cc");
        return value;
    }

    //! Get IAPSR (combined IPSR and APSR) register (raw value).
    [[gnu::always_inline]] static inline uint32_t asmGetIapsr()
    {
        uint32_t value;
        asm volatile("MRS %0, IAPSR" : "=r" (value) : : "cc");
        return value;
    }

    //! Get EAPSR (combined EPSR and APSR) register (raw value).
    [[gnu::always_inline]] static inline uint32_t asmGetEapsr()
    {
        uint32_t value;
        asm volatile("MRS %0, EAPSR" : "=r" (value) : : "cc");
        return value;
    }
}
