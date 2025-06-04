/*
    Copyright (C) 2025 Matej Gomboc <https://github.com/MatejGomboc/ARMCortexM-CppLib>

    Licensed under the Apache License, Version 2.0 (the "Licence");
    you may not use this file except in compliance with the Licence.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once

#include <cstdint>

namespace CortexM3 {
    //! the following values are saved into LR on exception entry
    enum class LrExceptionReturn : uint32_t {
        HANDLER = 0xFFFFFFF1, //!< return to handler mode, uses MSP after return
        THREAD_MSP = 0xFFFFFFF9, //!< return to thread mode, uses MSP after return
        THREAD_PSP = 0xFFFFFFFD //!< return to thread mode, uses PSP after return
    };

    //! program status register
    union Psr {
        struct Bits {
            uint32_t exception: 9; //!< the exception type of the current executing exception
            uint32_t ici_it_1: 6; //!< interruptible-continuable instruction and if-then state
            uint32_t reserved0: 1;
            uint32_t thumb: 1; //!< always 1, indicates the processor is executing Thumb instructions
            uint32_t reserved1: 3;
            uint32_t gcc_1: 4; //!< greater than or equal flags on the results of instruction comparisons
            uint32_t ici_it_2: 2; //!< interruptible-continuable instruction and if-then state
            uint32_t q: 1; //!< saturation occurred during a DSP operation
            uint32_t v: 1; //!< overflow flag
            uint32_t c: 1; //!< carry or borrow flag
            uint32_t z: 1; //!< zero flag
            uint32_t n: 1; //!< negative or less than flag
            uint32_t apsr_valid: 1; //!< indicates a valid APSR value
        } bits;

        uint32_t value = 0;

        Psr() = default;

        Psr(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! priority mask register
    union Primask {
        struct Bits {
            uint32_t exceptions_disabled: 1; //!< all exceptions except NMI and hard fault are disabled
            uint32_t reserved: 31;
        } bits;

        uint32_t value = 0;

        Primask() = default;

        Primask(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! fault mask register
    union Faultmask {
        struct Bits {
            uint32_t enabled: 1; //!< 1 = all exceptions except NMI are masked
            uint32_t reserved: 31;
        } bits;

        uint32_t value = 0;

        Faultmask() = default;

        Faultmask(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! base priority register
    union Basepri {
        struct Bits {
            uint32_t reserved: 24;
            uint32_t priority: 8; //!< base priority for exception processing
        } bits;

        uint32_t value = 0;

        Basepri() = default;

        Basepri(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! control register
    union Control {
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
            uint32_t thread_mode_privilege_level: 1; //!< thread mode privilege level
            uint32_t active_stack_pointer: 1; //!< currently used stack pointer
            uint32_t reserved1: 30;
        } bits;

        uint32_t value = 0;

        Control() = default;

        Control(uint32_t new_value)
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

    static inline Psr getApsrReg()
    {
        Psr psr;
        asm volatile("MRS %0, APSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    static inline Psr getIpsrReg()
    {
        Psr psr;
        asm volatile("MRS %0, IPSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    static inline Psr getEpsrReg()
    {
        Psr psr;
        asm volatile("MRS %0, EPSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    static inline Psr getIepsrReg()
    {
        Psr psr;
        asm volatile("MRS %0, IEPSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    static inline Psr getIapsrReg()
    {
        Psr psr;
        asm volatile("MRS %0, IAPSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    static inline Psr getEapsrReg()
    {
        Psr psr;
        asm volatile("MRS %0, EAPSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    static inline Psr getPsrReg()
    {
        Psr psr;
        asm volatile("MRS %0, PSR" : "=r" (psr.value) : : "cc");
        return psr;
    }

    static inline void setApsrReg(Psr psr)
    {
        asm volatile("MSR APSR, %0" : : "r" (psr.value) : "cc", "memory");
        asm volatile("ISB" : : : "memory");
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
        asm volatile("ISB" : : : "memory");
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
        asm volatile("ISB" : : : "memory");
    }

    static inline Primask getPrimaskReg()
    {
        Primask primask;
        asm volatile("MRS %0, PRIMASK" : "=r" (primask.value) : : "cc");
        return primask;
    }

    static inline void setPrimaskReg(Primask primask)
    {
        asm volatile("MSR PRIMASK, %0" : : "r" (primask.value) : "cc", "memory");
        asm volatile("ISB" : : : "memory");
    }

    static inline Faultmask getFaultmaskReg()
    {
        Faultmask faultmask;
        asm volatile("MRS %0, FAULTMASK" : "=r" (faultmask.value) : : "cc");
        return faultmask;
    }

    static inline void setFaultmaskReg(Faultmask faultmask)
    {
        asm volatile("MSR FAULTMASK, %0" : : "r" (faultmask.value) : "cc", "memory");
        asm volatile("ISB" : : : "memory");
    }

    static inline Basepri getBasepriReg()
    {
        Basepri basepri;
        asm volatile("MRS %0, BASEPRI" : "=r" (basepri.value) : : "cc");
        return basepri;
    }

    static inline void setBasepriReg(Basepri basepri)
    {
        asm volatile("MSR BASEPRI, %0" : : "r" (basepri.value) : "cc", "memory");
        asm volatile("ISB" : : : "memory");
    }

    static inline void setBasepriMaxReg(Basepri basepri)
    {
        asm volatile("MSR BASEPRI_MAX, %0" : : "r" (basepri.value) : "cc", "memory");
        asm volatile("ISB" : : : "memory");
    }

    static inline Control getControlReg()
    {
        Control control;
        asm volatile("MRS %0, CONTROL" : "=r" (control.value) : : "cc");
        return control;
    }

    static inline void setControlReg(Control control)
    {
        asm volatile("MSR CONTROL, %0" : : "r" (control.value) : "cc", "memory");
        asm volatile("ISB" : : : "memory");
    }

    static inline void disableAllExceptions()
    {
        asm volatile("CPSID i" : : : "memory");
    }

    static inline void enableAllExceptions()
    {
        asm volatile("CPSIE i" : : : "memory");
    }

    static inline void disableAllFaults()
    {
        asm volatile("CPSID f" : : : "memory");
    }

    static inline void enableAllFaults()
    {
        asm volatile("CPSIE f" : : : "memory");
    }
}