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

namespace CortexM3 {
    //! the following values are saved into LR on exception entry
    enum class LrExceptionReturn : uint32_t {
        HANDLER = 0xFFFFFFF1, //!< return to handler mode, uses MSP after return
        THREAD_MSP = 0xFFFFFFF9, //!< return to thread mode, uses MSP after return
        THREAD_PSP = 0xFFFFFFFD //!< return to thread mode, uses PSP after return
    };

    //! program status register
    union PSR {
        struct Bits {
            uint32_t ISR: 9; //!< the exception type of the current executing exception (IPSR)
            uint32_t ICI_IT_1: 6; //!< interruptible-continuable instruction and if-then state (bits 15:10, 26:25)
            uint32_t RESERVED0: 1;
            uint32_t T: 1; //!< always 1, indicates the processor is executing Thumb instructions
            uint32_t RESERVED1: 3;
            uint32_t GE: 4; //!< greater than or equal flags on the results of instruction comparisons
            uint32_t ICI_IT_2: 2; //!< interruptible-continuable instruction and if-then state (bits 15:10, 26:25)
            uint32_t Q: 1; //!< saturation occurred during a DSP operation
            uint32_t V: 1; //!< overflow flag
            uint32_t C: 1; //!< carry or borrow flag
            uint32_t Z: 1; //!< zero flag
            uint32_t N: 1; //!< negative or less than flag
        } bits;

        uint32_t value = 0;

        PSR() = default;

        PSR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! priority mask register
    union PRIMASK {
        struct Bits {
            uint32_t PM: 1; //!< all exceptions except NMI and hard fault are disabled
            uint32_t RESERVED: 31;
        } bits;

        uint32_t value = 0;

        PRIMASK() = default;

        PRIMASK(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! fault mask register
    union FAULTMASK {
        struct Bits {
            uint32_t FM: 1; //!< 1 = all exceptions except NMI are masked
            uint32_t RESERVED: 31;
        } bits;

        uint32_t value = 0;

        FAULTMASK() = default;

        FAULTMASK(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! base priority register
    union BASEPRI {
        struct Bits {
            uint32_t BASEPRI: 8; //!< base priority for exception processing
            uint32_t RESERVED: 24;
        } bits;

        uint32_t value = 0;

        BASEPRI() = default;

        BASEPRI(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! control register
    union CONTROL {
        //! thread mode privilege level
        enum class ThreadModePrivilegeLevel : bool {
            PRIVILEGED = false, //!< privileged thread mode
            UNPRIVILEGED = true //!< unprivileged thread mode
        };

        //! currently used stack pointer
        enum class StackPointer : bool {
            MSP = false, //!< main stack pointer
            PSP = true //!< process stack pointer
        };

        struct Bits {
            uint32_t nPRIV: 1; //!< thread mode privilege level (0=privileged, 1=unprivileged)
            uint32_t SPSEL: 1; //!< currently used stack pointer (0=MSP, 1=PSP)
            uint32_t RESERVED1: 30;
        } bits;

        uint32_t value = 0;

        CONTROL() = default;

        CONTROL(uint32_t new_value)
        {
            value = new_value;
        }
    };

    static inline uint32_t getLr()
    {
        uint32_t value;
        asm volatile("MOV %0, LR" : "=r" (value) : : "cc");
        return value;
    }

    static inline PSR getApsrReg()
    {
        PSR psr;
        asm volatile("MRS %0, APSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    static inline PSR getIpsrReg()
    {
        PSR psr;
        asm volatile("MRS %0, IPSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    static inline PSR getEpsrReg()
    {
        PSR psr;
        asm volatile("MRS %0, EPSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    static inline PSR getIepsrReg()
    {
        PSR psr;
        asm volatile("MRS %0, IEPSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    static inline PSR getIapsrReg()
    {
        PSR psr;
        asm volatile("MRS %0, IAPSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    static inline PSR getEapsrReg()
    {
        PSR psr;
        asm volatile("MRS %0, EAPSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    static inline PSR getPsrReg()
    {
        PSR psr;
        asm volatile("MRS %0, PSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    static inline void setApsrReg(PSR psr)
    {
        asm volatile("MSR APSR, %0" : : "r" (psr.value) : "cc", "memory");
        instrSyncBarrier();
    }

    static inline uint32_t getMspReg()
    {
        uint32_t value;
        asm volatile("MRS %0, MSP" : "=r" (value) : : "cc");
        return value;
    }

    static inline void setMspReg(uint32_t value)
    {
        asm volatile("MSR MSP, %0" : : "r" (value) : "cc", "memory");
        instrSyncBarrier();
    }

    static inline uint32_t getPspReg()
    {
        uint32_t value;
        asm volatile("MRS %0, PSP" : "=r" (value) : : "cc");
        return value;
    }

    static inline void setPspReg(uint32_t value)
    {
        asm volatile("MSR PSP, %0" : : "r" (value) : "cc", "memory");
        instrSyncBarrier();
    }

    static inline PRIMASK getPrimaskReg()
    {
        PRIMASK primask;
        asm volatile("MRS %0, PRIMASK" : "=r" (primask.value) : : "cc");
        return primask;
    }

    static inline void setPrimaskReg(PRIMASK primask)
    {
        asm volatile("MSR PRIMASK, %0" : : "r" (primask.value) : "cc", "memory");
        instrSyncBarrier();
    }

    static inline FAULTMASK getFaultmaskReg()
    {
        FAULTMASK faultmask;
        asm volatile("MRS %0, FAULTMASK" : "=r" (faultmask.value) : : "cc");
        return faultmask;
    }

    static inline void setFaultmaskReg(FAULTMASK faultmask)
    {
        asm volatile("MSR FAULTMASK, %0" : : "r" (faultmask.value) : "cc", "memory");
        instrSyncBarrier();
    }

    static inline BASEPRI getBasepriReg()
    {
        BASEPRI basepri;
        asm volatile("MRS %0, BASEPRI" : "=r" (basepri.value) : : "cc");
        return basepri;
    }

    static inline void setBasepriReg(BASEPRI basepri)
    {
        asm volatile("MSR BASEPRI, %0" : : "r" (basepri.value) : "cc", "memory");
        instrSyncBarrier();
    }

    static inline void setBasepriMaxReg(BASEPRI basepri)
    {
        asm volatile("MSR BASEPRI_MAX, %0" : : "r" (basepri.value) : "cc", "memory");
        instrSyncBarrier();
    }

    static inline CONTROL getControlReg()
    {
        CONTROL control;
        asm volatile("MRS %0, CONTROL" : "=r" (control.value) : : "cc");
        return control;
    }

    static inline void setControlReg(CONTROL control)
    {
        asm volatile("MSR CONTROL, %0" : : "r" (control.value) : "cc", "memory");
        instrSyncBarrier();
    }
}
