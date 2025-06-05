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

namespace CortexM1::SpecialRegs {
    enum class Register : uint8_t {
        APSR = 0,
        IPSR = 5,
        EPSR = 6,
        IEPSR = 7,
        MSP = 8,
        PSP = 9,
        PRIMASK = 16,
        CONTROL = 20
    };

    enum class ControlSpSel : uint8_t {
        MSP = 0,
        PSP = 1
    };

    static inline uint32_t getApsr()
    {
        uint32_t result;
        asm volatile("MRS %0, APSR" : "=r" (result));
        return result;
    }

    static inline void setApsr(uint32_t value)
    {
        asm volatile("MSR APSR_nzcvq, %0" : : "r" (value) : "memory");
    }

    static inline uint32_t getIpsr()
    {
        uint32_t result;
        asm volatile("MRS %0, IPSR" : "=r" (result));
        return result;
    }

    static inline uint32_t getEpsr()
    {
        uint32_t result;
        asm volatile("MRS %0, EPSR" : "=r" (result));
        return result;
    }

    static inline uint32_t getMsp()
    {
        uint32_t result;
        asm volatile("MRS %0, MSP" : "=r" (result));
        return result;
    }

    static inline void setMsp(uint32_t value)
    {
        asm volatile("MSR MSP, %0" : : "r" (value) : "memory");
    }

    static inline uint32_t getPsp()
    {
        uint32_t result;
        asm volatile("MRS %0, PSP" : "=r" (result));
        return result;
    }

    static inline void setPsp(uint32_t value)
    {
        asm volatile("MSR PSP, %0" : : "r" (value) : "memory");
    }

    static inline uint32_t getPrimask()
    {
        uint32_t result;
        asm volatile("MRS %0, PRIMASK" : "=r" (result));
        return result;
    }

    static inline void setPrimask(uint32_t value)
    {
        asm volatile("MSR PRIMASK, %0" : : "r" (value) : "memory");
    }

    static inline void enableInterrupts()
    {
        asm volatile("CPSIE I" : : : "memory");
    }

    static inline void disableInterrupts()
    {
        asm volatile("CPSID I" : : : "memory");
    }

    static inline uint32_t getControl()
    {
        uint32_t result;
        asm volatile("MRS %0, CONTROL" : "=r" (result));
        return result;
    }

    static inline void setControl(uint32_t value)
    {
        asm volatile("MSR CONTROL, %0" : : "r" (value) : "memory");
        asm volatile("ISB" : : : "memory");
    }

    static inline ControlSpSel getStackPointerSelect()
    {
        return static_cast<ControlSpSel>((getControl() >> 1) & 0x1);
    }

    static inline void setStackPointerSelect(ControlSpSel sp_sel)
    {
        uint32_t control = getControl();
        control = (control & ~0x2) | (static_cast<uint32_t>(sp_sel) << 1);
        setControl(control);
    }

    static inline uint32_t getRegister(Register reg)
    {
        uint32_t result;
        switch (reg) {
            case Register::APSR:
                result = getApsr();
                break;
            case Register::IPSR:
                result = getIpsr();
                break;
            case Register::EPSR:
                result = getEpsr();
                break;
            case Register::MSP:
                result = getMsp();
                break;
            case Register::PSP:
                result = getPsp();
                break;
            case Register::PRIMASK:
                result = getPrimask();
                break;
            case Register::CONTROL:
                result = getControl();
                break;
            default:
                result = 0;
                break;
        }
        return result;
    }

    static inline void setRegister(Register reg, uint32_t value)
    {
        switch (reg) {
            case Register::APSR:
                setApsr(value);
                break;
            case Register::MSP:
                setMsp(value);
                break;
            case Register::PSP:
                setPsp(value);
                break;
            case Register::PRIMASK:
                setPrimask(value);
                break;
            case Register::CONTROL:
                setControl(value);
                break;
            default:
                break;
        }
    }
}
