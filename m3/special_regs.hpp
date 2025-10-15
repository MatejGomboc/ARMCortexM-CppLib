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

namespace Cortex::M3 {
    //! Exception return values saved to LR on exception entry.
    enum class LrExceptionReturnValue : uint32_t {
        HANDLER = 0xFFFFFFF1, //!< Return to Handler mode, use MSP.
        THREAD_MSP = 0xFFFFFFF9, //!< Return to Thread mode, use MSP.
        THREAD_PSP = 0xFFFFFFFD //!< Return to Thread mode, use PSP.
    };

    //! Program status register.
    union PSR {
        struct Bits {
            uint32_t ISR: 9; //!< Current exception number.
            uint32_t RESERVED0: 1;
            uint32_t ICI_IT_1: 6; //!< ICI/IT part 1.
            uint32_t RESERVED1: 8;
            uint32_t T: 1; //!< Thumb mode flag.
            uint32_t ICI_IT_2: 2; //!< ICI/IT part 2.
            uint32_t Q: 1; //!< Saturation flag.
            uint32_t V: 1; //!< Overflow flag.
            uint32_t C: 1; //!< Carry/borrow flag.
            uint32_t Z: 1; //!< Zero flag.
            uint32_t N: 1; //!< Negative flag.
        } bits;

        uint32_t value = 0;

        PSR() = default;

        PSR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Priority mask register.
    union PRIMASK {
        struct Bits {
            uint32_t PRIMASK: 1; //!< Disable all exceptions except NMI and HardFault.
            uint32_t RESERVED: 31;
        } bits;

        uint32_t value = 0;

        PRIMASK() = default;

        PRIMASK(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Fault mask register.
    union FAULTMASK {
        struct Bits {
            uint32_t FAULTMASK: 1; //!< Disable all exceptions except NMI.
            uint32_t RESERVED: 31;
        } bits;

        uint32_t value = 0;

        FAULTMASK() = default;

        FAULTMASK(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Base priority register.
    union BASEPRI {
        struct Bits {
            uint32_t BASEPRI: 8; //!< Base priority for exception processing.
            uint32_t RESERVED: 24;
        } bits;

        uint32_t value = 0;

        BASEPRI() = default;

        BASEPRI(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Control register.
    union CONTROL {
        //! Thread mode privilege level.
        enum class nPRIV : bool {
            PRIVILEGED = false, //!< Privileged thread mode.
            UNPRIVILEGED = true //!< Unprivileged thread mode.
        };

        //! Active stack pointer selection.
        enum class SPSEL : bool {
            MSP = false, //!< Main stack pointer.
            PSP = true //!< Process stack pointer.
        };

        struct Bits {
            uint32_t nPRIV: 1; //!< Thread mode privilege level (0: privileged, 1: unprivileged).
            uint32_t SPSEL: 1; //!< Active stack pointer (0: MSP, 1: PSP).
            uint32_t RESERVED: 30;
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

    static inline uint32_t getMspReg()
    {
        uint32_t value;
        asm volatile("MRS %0, MSP" : "=r" (value) : : "cc");
        return value;
    }

    static inline void setMspReg(uint32_t value)
    {
        asm volatile("MSR MSP, %0" : : "r" (value) : "cc", "memory");
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
    }

    static inline void setBasepriMaxReg(BASEPRI basepri)
    {
        asm volatile("MSR BASEPRI_MAX, %0" : : "r" (basepri.value) : "cc", "memory");
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
    }
}
