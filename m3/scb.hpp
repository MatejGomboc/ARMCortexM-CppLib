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

namespace Cortex::M3::Scb {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000ED00u;

    struct Registers
    {
        volatile uint32_t CPUID;
        volatile uint32_t ICSR;
        volatile uint32_t VTOR;
        volatile uint32_t AIRCR;
        volatile uint32_t SCR;
        volatile uint32_t CCR;
        volatile uint8_t SHPR[12];
        volatile uint32_t SHCSR;
        volatile uint32_t CFSR;
        volatile uint32_t HFSR;
        volatile uint32_t DFSR;
        volatile uint32_t MMFAR;
        volatile uint32_t BFAR;
        volatile uint32_t AFSR;
        volatile uint32_t ID_PFR[2];
        volatile uint32_t ID_DFR;
        volatile uint32_t ID_AFR;
        volatile uint32_t ID_MMFR[4];
        volatile uint32_t ID_ISAR[5];
        volatile uint32_t RESERVED0[5];
        volatile uint32_t CPACR;
        volatile uint32_t RESERVED3[93];
        volatile uint32_t STIR;
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
            uint32_t RESERVED0: 2;
            uint32_t RETTOBASE: 1;
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
            uint32_t VECTRESET: 1;
            uint32_t VECTCLRACTIVE: 1;
            uint32_t SYSRESETREQ: 1;
            uint32_t RESERVED0: 5;
            uint32_t PRIGROUP: 3;
            uint32_t RESERVED1: 4;
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
            uint32_t NONBASETHRDENA: 1;
            uint32_t USERSETMPEND: 1;
            uint32_t RESERVED0: 1;
            uint32_t UNALIGN_TRP: 1;
            uint32_t DIV_0_TRP: 1;
            uint32_t RESERVED1: 3;
            uint32_t BFHFNMIGN: 1;
            uint32_t STKALIGN: 1;
            uint32_t RESERVED2: 22;
        } bits;
        uint32_t value = 0;
        CCR() = default;
        CCR(uint32_t new_value) { value = new_value; }
    };

    union SHCSR {
        struct Bits {
            uint32_t MEMFAULTACT: 1;
            uint32_t BUSFAULTACT: 1;
            uint32_t RESERVED0: 1;
            uint32_t USGFAULTACT: 1;
            uint32_t RESERVED1: 3;
            uint32_t SVCALLACT: 1;
            uint32_t MONITORACT: 1;
            uint32_t RESERVED2: 1;
            uint32_t PENDSVACT: 1;
            uint32_t SYSTICKACT: 1;
            uint32_t USGFAULTPENDED: 1;
            uint32_t MEMFAULTPENDED: 1;
            uint32_t BUSFAULTPENDED: 1;
            uint32_t SVCALLPENDED: 1;
            uint32_t MEMFAULTENA: 1;
            uint32_t BUSFAULTENA: 1;
            uint32_t USGFAULTENA: 1;
            uint32_t RESERVED3: 13;
        } bits;
        uint32_t value = 0;
        SHCSR() = default;
        SHCSR(uint32_t new_value) { value = new_value; }
    };

    union CFSR {
        struct Bits {
            uint32_t IACCVIOL: 1;
            uint32_t DACCVIOL: 1;
            uint32_t RESERVED0: 1;
            uint32_t MUNSTKERR: 1;
            uint32_t MSTKERR: 1;
            uint32_t RESERVED1: 1;
            uint32_t RESERVED2: 1;
            uint32_t MMARVALID: 1;
            uint32_t IBUSERR: 1;
            uint32_t PRECISERR: 1;
            uint32_t IMPRECISERR: 1;
            uint32_t UNSTKERR: 1;
            uint32_t STKERR: 1;
            uint32_t RESERVED3: 1;
            uint32_t RESERVED4: 1;
            uint32_t BFARVALID: 1;
            uint32_t UNDEFINSTR: 1;
            uint32_t INVSTATE: 1;
            uint32_t INVPC: 1;
            uint32_t NOCP: 1;
            uint32_t RESERVED5: 4;
            uint32_t UNALIGNED: 1;
            uint32_t DIVBYZERO: 1;
            uint32_t RESERVED6: 6;
        } bits;
        uint32_t value = 0;
        CFSR() = default;
        CFSR(uint32_t new_value) { value = new_value; }
    };

    union HFSR {
        struct Bits {
            uint32_t RESERVED0: 1;
            uint32_t VECTTBL: 1;
            uint32_t RESERVED1: 28;
            uint32_t FORCED: 1;
            uint32_t DEBUGEVT: 1;
        } bits;
        uint32_t value = 0;
        HFSR() = default;
        HFSR(uint32_t new_value) { value = new_value; }
    };

    union DFSR {
        struct Bits {
            uint32_t HALTED: 1;
            uint32_t BKPT: 1;
            uint32_t DWTTRAP: 1;
            uint32_t VCATCH: 1;
            uint32_t EXTERNAL: 1;
            uint32_t RESERVED: 27;
        } bits;
        uint32_t value = 0;
        DFSR() = default;
        DFSR(uint32_t new_value) { value = new_value; }
    };
}

namespace Cortex::M3 {
    inline volatile Scb::Registers* const SCB = reinterpret_cast<volatile Scb::Registers*>(Scb::BASE_ADDRESS);
}

namespace Cortex::M3::Scb {
    [[gnu::noreturn]] static inline void systemReset()
    {
        asmDsb();

        AIRCR aircr { SCB->AIRCR };
        aircr.bits.VECTRESET = 0;
        aircr.bits.VECTCLRACTIVE = 0;
        aircr.bits.SYSRESETREQ = true;
        aircr.bits.VECTKEY = AIRCR::VECTKEY_VALUE;
        SCB->AIRCR = aircr.value;

        asmDsb();
        asmIsb();

        while(true);
    }

    static inline void setPriorityGrouping(uint32_t priority_group)
    {
        asmDsb();

        AIRCR aircr { SCB->AIRCR };
        aircr.bits.PRIGROUP = priority_group & 0x7;
        aircr.bits.VECTKEY = AIRCR::VECTKEY_VALUE;
        SCB->AIRCR = aircr.value;

        asmDsb();
        asmIsb();
    }

    static inline uint32_t getPriorityGrouping()
    {
        AIRCR aircr { SCB->AIRCR };
        return aircr.bits.PRIGROUP;
    }
}
