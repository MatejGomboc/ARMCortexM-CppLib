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

#include "utils.hpp"
#include <cstdint>

namespace CortexM1::Scb {
    static uint32_t* const BASE_ADDR = reinterpret_cast<uint32_t*>(0xE000ED00);

    enum class SleepMode : uint8_t {
        NORMAL = 0,
        DEEP = 1
    };

    enum class VectorTableBase : uint8_t {
        CODE = 0,
        SRAM = 1
    };

    struct Registers
    {
        volatile const uint32_t cpuid; //!< Contains the processor part number, version, and implementation information
        volatile uint32_t icsr; //!< Provides system exception numbers and states
        volatile uint32_t reserved0;
        volatile uint32_t aircr; //!< Application interrupt and reset control
        volatile uint32_t scr; //!< System control
        volatile uint32_t ccr; //!< Configuration and control
        volatile uint32_t reserved1;
        volatile uint32_t shpr2; //!< System handler priority register 2
        volatile uint32_t shpr3; //!< System handler priority register 3
    };

    static inline volatile Registers* registers()
    {
        return reinterpret_cast<volatile Registers*>(BASE_ADDR);
    }

    // CPUID register functions
    static inline uint32_t getCpuId()
    {
        return registers()->cpuid;
    }

    // ICSR register functions
    static inline bool isVectorActive()
    {
        return (registers()->icsr & 0x1FF) != 0;
    }

    static inline uint8_t getActiveVectorNumber()
    {
        return registers()->icsr & 0x1FF;
    }

    static inline bool isVectorPending()
    {
        return Utils::isBitSet(registers()->icsr, 22);
    }

    static inline uint8_t getPendingVectorNumber()
    {
        return (registers()->icsr >> 12) & 0x1FF;
    }

    static inline void setPendStClr()
    {
        Utils::setBit(registers()->icsr, 25);
    }

    static inline void setPendStSet()
    {
        Utils::setBit(registers()->icsr, 26);
    }

    static inline void setPendSvClr()
    {
        Utils::setBit(registers()->icsr, 27);
    }

    static inline void setPendSvSet()
    {
        Utils::setBit(registers()->icsr, 28);
    }

    static inline bool isNmiPending()
    {
        return Utils::isBitSet(registers()->icsr, 31);
    }

    static inline void setNmiPending()
    {
        Utils::setBit(registers()->icsr, 31);
    }

    // AIRCR register functions
    static inline void requestSystemReset()
    {
        asm volatile("DSB" : : : "memory");
        registers()->aircr = 0x05FA0004;
        asm volatile("DSB" : : : "memory");
        while (true) { asm volatile("NOP"); }
    }

    static inline bool isLittleEndian()
    {
        return !Utils::isBitSet(registers()->aircr, 15);
    }

    // SCR register functions
    static inline void setSleepMode(SleepMode mode)
    {
        if (mode == SleepMode::DEEP) {
            Utils::setBit(registers()->scr, 2);
        } else {
            Utils::clearBit(registers()->scr, 2);
        }
    }

    static inline void setSleepOnExit(bool enable)
    {
        if (enable) {
            Utils::setBit(registers()->scr, 1);
        } else {
            Utils::clearBit(registers()->scr, 1);
        }
    }

    static inline void setEventOnPending(bool enable)
    {
        if (enable) {
            Utils::setBit(registers()->scr, 4);
        } else {
            Utils::clearBit(registers()->scr, 4);
        }
    }

    // CCR register functions
    static inline void setUnalignedAccessTrap(bool enable)
    {
        if (enable) {
            Utils::setBit(registers()->ccr, 3);
        } else {
            Utils::clearBit(registers()->ccr, 3);
        }
    }

    static inline void setStackAlign8(bool enable)
    {
        if (enable) {
            Utils::setBit(registers()->ccr, 9);
        } else {
            Utils::clearBit(registers()->ccr, 9);
        }
    }

    // SHPR register functions
    static inline void setSvCallPriority(uint8_t priority)
    {
        registers()->shpr2 = (registers()->shpr2 & 0x00FFFFFF) | (static_cast<uint32_t>(priority) << 24);
    }

    static inline uint8_t getSvCallPriority()
    {
        return (registers()->shpr2 >> 24) & 0xFF;
    }

    static inline void setPendSvPriority(uint8_t priority)
    {
        registers()->shpr3 = (registers()->shpr3 & 0xFFFF00FF) | (static_cast<uint32_t>(priority) << 16);
    }

    static inline uint8_t getPendSvPriority()
    {
        return (registers()->shpr3 >> 16) & 0xFF;
    }

    static inline void setSysTickPriority(uint8_t priority)
    {
        registers()->shpr3 = (registers()->shpr3 & 0x00FFFFFF) | (static_cast<uint32_t>(priority) << 24);
    }

    static inline uint8_t getSysTickPriority()
    {
        return (registers()->shpr3 >> 24) & 0xFF;
    }
}
