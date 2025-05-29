/*
    Copyright (C) 2025 Matej Gomboc <https://github.com/MatejGomboc/ARMCortexM-CppLib>

    Licensed under the Apache License, Version 2.0 (the "Licence");
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

namespace CortexM3 {
    //! the set of processor core registers that are accessible when the processor is in Thread mode
    static inline uint32_t readMainStackPointer()
    {
        uint32_t result;
        asm volatile("MRS %0, MSP" : "=r" (result));
        return result;
    }

    static inline void writeMainStackPointer(uint32_t new_msp)
    {
        asm volatile("MSR MSP, %0" : : "r" (new_msp));
    }

    static inline uint32_t readProcessStackPointer()
    {
        uint32_t result;
        asm volatile("MRS %0, PSP" : "=r" (result));
        return result;
    }

    static inline void writeProcessStackPointer(uint32_t new_psp)
    {
        asm volatile("MSR PSP, %0" : : "r" (new_psp));
    }

    union ProgramStatusRegister {
        struct Bits {
            uint32_t exception: 9; //!< the exception type of the current executing exception
            uint32_t ici_it_1: 6; //!< interruptible-continuable instruction and if-then state
            uint32_t reserved0: 1;
            uint32_t thumb: 1; //!< always 1, indicates the processor is executing Thumb instructions
            uint32_t reserved1: 3;
            uint32_t gcc_1: 4; //!< greater than or equal flags on the results of instruction comparisons
            uint32_t ici_it_2: 2; //!< interruptible-continuable instruction and if-then state
            uint32_t q: 1; //!< saturation occurred during a DSP operation
            uint32_t gcc_2: 4; //!< condition code flags
            uint32_t apsr_valid: 1; //!< indicates a valid APSR value
        } bits;

        uint32_t value = 0;

        ProgramStatusRegister() = default;

        ProgramStatusRegister(uint32_t new_value)
        {
            value = new_value;
        }
    };

    static inline ProgramStatusRegister readProgramStatusRegister()
    {
        uint32_t result;
        asm volatile("MRS %0, PSR" : "=r" (result));
        return ProgramStatusRegister(result);
    }

    static inline ProgramStatusRegister readApplicationProgramStatusRegister()
    {
        uint32_t result;
        asm volatile("MRS %0, APSR" : "=r" (result));
        return ProgramStatusRegister(result);
    }

    static inline void writeApplicationProgramStatusRegister(const ProgramStatusRegister& new_apsr)
    {
        asm volatile("MSR APSR, %0" : : "r" (new_apsr.value));
    }

    static inline ProgramStatusRegister readInterruptProgramStatusRegister()
    {
        uint32_t result;
        asm volatile("MRS %0, IPSR" : "=r" (result));
        return ProgramStatusRegister(result);
    }

    static inline ProgramStatusRegister readExecutionProgramStatusRegister()
    {
        uint32_t result;
        asm volatile("MRS %0, EPSR" : "=r" (result));
        return ProgramStatusRegister(result);
    }

    union PriorityMask {
        struct Bits {
            uint32_t reserved: 24;
            uint32_t priority: 8; //!< priority level required for preemption
        } bits;

        uint32_t value = 0;

        PriorityMask() = default;

        PriorityMask(uint32_t new_value)
        {
            value = new_value;
        }
    };

    static inline PriorityMask readPriorityMask()
    {
        uint32_t result;
        asm volatile("MRS %0, PRIMASK" : "=r" (result));
        return PriorityMask(result);
    }

    static inline void writePriorityMask(const PriorityMask& new_primask)
    {
        asm volatile("MSR PRIMASK, %0" : : "r" (new_primask.value));
    }

    static inline void disableAllExceptions()
    {
        asm volatile("CPSID i" : : : "memory");
    }

    static inline void enableAllExceptions()
    {
        asm volatile("CPSIE i" : : : "memory");
    }

    union FaultMask {
        struct Bits {
            uint32_t enabled: 1; //!< 1 = all exceptions except NMI are masked
            uint32_t reserved: 31;
        } bits;

        uint32_t value = 0;

        FaultMask() = default;

        FaultMask(uint32_t new_value)
        {
            value = new_value;
        }
    };

    static inline FaultMask readFaultMask()
    {
        uint32_t result;
        asm volatile("MRS %0, FAULTMASK" : "=r" (result));
        return FaultMask(result);
    }

    static inline void writeFaultMask(const FaultMask& new_faultmask)
    {
        asm volatile("MSR FAULTMASK, %0" : : "r" (new_faultmask.value));
    }

    static inline void disableAllFaults()
    {
        asm volatile("CPSID f" : : : "memory");
    }

    static inline void enableAllFaults()
    {
        asm volatile("CPSIE f" : : : "memory");
    }

    union BasePriority {
        struct Bits {
            uint32_t reserved: 24;
            uint32_t priority: 8; //!< base priority for exception processing
        } bits;

        uint32_t value = 0;

        BasePriority() = default;

        BasePriority(uint32_t new_value)
        {
            value = new_value;
        }
    };

    static inline BasePriority readBasePriority()
    {
        uint32_t result;
        asm volatile("MRS %0, BASEPRI" : "=r" (result));
        return BasePriority(result);
    }

    static inline void writeBasePriority(const BasePriority& new_basepri)
    {
        asm volatile("MSR BASEPRI, %0" : : "r" (new_basepri.value));
    }

    static inline void writeBasePriorityMax(const BasePriority& new_basepri)
    {
        asm volatile("MSR BASEPRI_MAX, %0" : : "r" (new_basepri.value));
    }

    union Control {
        struct Bits {
            uint32_t thread_priv: 1; //!< thread mode privilege level (0=privileged, 1=unprivileged)
            uint32_t stack_pointer: 1; //!< stack pointer selection (0=MSP, 1=PSP)
            uint32_t reserved: 30;
        } bits;

        uint32_t value = 0;

        Control() = default;

        Control(uint32_t new_value)
        {
            value = new_value;
        }
    };

    static inline Control readControl()
    {
        uint32_t result;
        asm volatile("MRS %0, CONTROL" : "=r" (result));
        return Control(result);
    }

    static inline void writeControl(const Control& new_control)
    {
        asm volatile("MSR CONTROL, %0" : : "r" (new_control.value));
        asm volatile("ISB" : : : "memory");
    }
}
