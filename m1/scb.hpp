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

namespace Cortex::M1::Scb {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000ED00u;

    struct Registers
    {
        volatile uint32_t CPUID;
        volatile uint32_t ICSR;
        volatile uint32_t RESERVED0;
        volatile uint32_t AIRCR;
        volatile uint32_t SCR;
        volatile uint32_t CCR;
        volatile uint32_t RESERVED1;
        volatile uint32_t SHPR2;
        volatile uint32_t SHPR3;
        volatile uint32_t SHCSR;
    };

    union CPUID {
        struct Bits {
            uint32_t REVISION: 4;
            uint32_t PARTNO: 12;
            uint32_t ARCHITECTURE: 4;
            uint32_t VARIANT: 4;
            uint32_t IMPLEMENTER: 8;
        } bits;
        uint32_t value = 0;
        CPUID() = default;
        CPUID(uint32_t new_value) { value = new_value; }
    };

    union ICSR {
        struct Bits {
            uint32_t VECTACTIVE: 9;
            uint32_t RESERVED0: 3;
            uint32_t VECTPENDING: 9;
            uint32_t RESERVED1: 1;
            uint32_t ISRPENDING: 1;
            uint32_t ISRPREEMPT: 1;
            uint32_t RESERVED2: 1;
            uint32_t PENDSTCLR: 1;
            uint32_t PENDSTSET: 1;
            uint32_t PENDSVCLR: 1;
            uint32_t PENDSVSET: 1;
            uint32_t RESERVED3: 2;
            uint32_t NMIPENDSET: 1;
        } bits;
        uint32_t value = 0;
        ICSR() = default;
        ICSR(uint32_t new_value) { value = new_value; }
    };

    union AIRCR {
        static constexpr uint16_t VECTKEY_VALUE = 0x05FA;
        struct Bits {
            uint32_t RESERVED0: 1;
            uint32_t VECTCLRACTIVE: 1;
            uint32_t SYSRESETREQ: 1;
            uint32_t RESERVED1: 12;
            uint32_t ENDIANNESS: 1;
            uint32_t VECTKEY: 16;
        } bits;
        uint32_t value = 0;
        AIRCR() = default;
        AIRCR(uint32_t new_value) { value = new_value; }
    };

    union SCR {
        struct Bits {
            uint32_t RESERVED0: 1;
            uint32_t SLEEPONEXIT: 1;
            uint32_t SLEEPDEEP: 1;
            uint32_t RESERVED1: 1;
            uint32_t SEVONPEND: 1;
            uint32_t RESERVED2: 27;
        } bits;
        uint32_t value = 0;
        SCR() = default;
        SCR(uint32_t new_value) { value = new_value; }
    };

    union CCR {
        struct Bits {
            uint32_t RESERVED0: 3;
            uint32_t UNALIGN_TRP: 1;
            uint32_t RESERVED1: 5;
            uint32_t STKALIGN: 1;
            uint32_t RESERVED2: 22;
        } bits;
        uint32_t value = 0;
        CCR() = default;
        CCR(uint32_t new_value) { value = new_value; }
    };

    union SHPR2 {
        struct Bits {
            uint32_t RESERVED0: 24;
            uint32_t PRI_11: 8;
        } bits;
        uint32_t value = 0;
        SHPR2() = default;
        SHPR2(uint32_t new_value) { value = new_value; }
    };

    union SHPR3 {
        struct Bits {
            uint32_t RESERVED0: 16;
            uint32_t PRI_14: 8;
            uint32_t PRI_15: 8;
        } bits;
        uint32_t value = 0;
        SHPR3() = default;
        SHPR3(uint32_t new_value) { value = new_value; }
    };

    union SHCSR {
        struct Bits {
            uint32_t RESERVED0: 15;
            uint32_t SVCALLPENDED: 1;
            uint32_t RESERVED1: 16;
        } bits;
        uint32_t value = 0;
        SHCSR() = default;
        SHCSR(uint32_t new_value) { value = new_value; }
    };
}

namespace Cortex::M1 {
    inline volatile Scb::Registers* const SCB = reinterpret_cast<volatile Scb::Registers*>(Scb::BASE_ADDRESS);
}

namespace Cortex::M1::Scb {
    [[gnu::noreturn]] static inline void systemReset()
    {
        asmDsb();

        AIRCR aircr { SCB->AIRCR };
        aircr.bits.VECTCLRACTIVE = 0;
        aircr.bits.SYSRESETREQ = true;
        aircr.bits.VECTKEY = AIRCR::VECTKEY_VALUE;
        SCB->AIRCR = aircr.value;

        asmDsb();
        asmIsb();

        while(true);
    }
}
