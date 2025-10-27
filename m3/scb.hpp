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

#include "intrinsics/barriers.hpp"
#include <cstdint>

namespace Cortex::M3::Scb {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000ED00u;

    struct Registers
    {
        volatile uint32_t CPUID; //!< Processor part number, version, and implementation information.
        volatile uint32_t ICSR; //!< Interrupt control and state register.
        volatile uint32_t VTOR; //!< Vector table offset register.
        volatile uint32_t AIRCR; //!< Application interrupt and reset control register.
        volatile uint32_t SCR; //!< Low power state control.
        volatile uint32_t CCR; //!< Configuration and control register.
        volatile uint8_t SHPR[12]; //!< System handlers priority registers (4-7, 8-11, 12-15).
        volatile uint32_t SHCSR; //!< System handler control and state register.
        volatile uint32_t CFSR; //!< Configurable fault status register.
        volatile uint32_t HFSR; //!< HardFault status register.
        volatile uint32_t DFSR; //!< Debug fault status register.
        volatile uint32_t MMFAR; //!< MemManage fault address register.
        volatile uint32_t BFAR; //!< BusFault address register.
        volatile uint32_t AFSR; //!< Auxiliary fault status register.
        volatile uint32_t ID_PFR[2]; //!< Processor feature register.
        volatile uint32_t ID_DFR; //!< Debug feature register.
        volatile uint32_t ID_AFR; //!< Auxiliary feature register.
        volatile uint32_t ID_MMFR[4]; //!< Memory model feature register.
        volatile uint32_t ID_ISAR[5]; //!< Instruction set attributes register.
        volatile uint32_t RESERVED0[5];
        volatile uint32_t CPACR; //!< Coprocessor access control register.
        volatile uint32_t RESERVED3[93];
        volatile uint32_t STIR; //!< Software triggered interrupt register.
    };

    //! Processor part number, version, and implementation information.
    union CPUID {
        struct Bits {
            uint32_t REVISION: 4; //!< Patch release (p in Rnpn).
            uint32_t PARTNO: 12; //!< Part number (0xC23: Cortex-M3).
            uint32_t ARCHITECTURE: 4; //!< Architecture (0xF: ARMv7-M).
            uint32_t VARIANT: 4; //!< Variant number (r in Rnpn).
            uint32_t IMPLEMENTER: 8; //!< Implementer code (0x41: ARM).
        } bits;

        uint32_t value = 0;

        CPUID() = default;

        CPUID(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Interrupt control and state register.
    //! Provides set/clear-pending bits for PendSV and SysTick exceptions.
    //! Provides set-pending bit for NMI exception.
    //! Indicates active and pending exception numbers.
    //! \note Do not simultaneously set both set and clear bits for the same exception.
    union ICSR {
        struct Bits {
            uint32_t VECTACTIVE: 9; //!< Active exception number.
            uint32_t RESERVED0: 2;
            uint32_t RETTOBASE: 1; //!< Return to base level.
            uint32_t VECTPENDING: 9; //!< Highest priority pending exception number (0: none).
            uint32_t RESERVED1: 1;
            uint32_t ISRPENDING: 1; //!< Interrupt pending (excluding NMI and faults).
            uint32_t ISRPREEMPT: 1; //!< Preempted exception is active.
            uint32_t RESERVED2: 1;
            uint32_t PENDSTCLR: 1; //!< Write 1 to clear SysTick pending state (write-only).
            uint32_t PENDSTSET: 1; //!< SysTick pending (read), write 1 to set pending.
            uint32_t PENDSVCLR: 1; //!< Write 1 to clear PendSV pending state (write-only).
            uint32_t PENDSVSET: 1; //!< PendSV pending (read), write 1 to set pending.
            uint32_t RESERVED3: 2;
            uint32_t NMIPENDSET: 1; //!< NMI pending (read), write 1 to set pending.
        } bits;

        uint32_t value = 0;

        ICSR() = default;

        ICSR(uint32_t new_value)
        {
            value = new_value;
        }
    };


    //! Application interrupt and reset control register.
    union AIRCR {
        static constexpr uint16_t VECTKEY_VALUE = 0x05FA; //!< Write key to enable AIRCR writes.

        struct Bits {
            uint32_t VECTRESET: 1; //!< System reset bit (deprecated, write 0).
            uint32_t VECTCLRACTIVE: 1; //!< Clear all active state information for exceptions (write 0).
            uint32_t SYSRESETREQ: 1; //!< System reset request.
            uint32_t RESERVED0: 5;
            uint32_t PRIGROUP: 3; //!< Priority grouping field.
            uint32_t RESERVED1: 4;
            uint32_t ENDIANNESS: 1; //!< Data endianness (0: little endian).
            uint32_t VECTKEY: 16; //!< Write VECTKEY_VALUE to enable writes, otherwise ignored.
        } bits;

        uint32_t value = 0;

        AIRCR() = default;

        AIRCR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! System control register - low power state configuration.
    union SCR {
        struct Bits {
            uint32_t RESERVED0: 1;
            uint32_t SLEEPONEXIT: 1; //!< Enter sleep/deep sleep on ISR return to Thread mode.
            uint32_t SLEEPDEEP: 1; //!< Use deep sleep instead of sleep.
            uint32_t RESERVED1: 1;
            uint32_t SEVONPEND: 1; //!< Wake from WFE on any interrupt (including disabled).
            uint32_t RESERVED2: 27;
        } bits;

        uint32_t value = 0;

        SCR() = default;

        SCR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Configuration and control register.
    union CCR {
        struct Bits {
            uint32_t NONBASETHRDENA: 1; //!< How processor enters Thread mode.
            uint32_t USERSETMPEND: 1; //!< Enables unprivileged software access to STIR.
            uint32_t RESERVED0: 1;
            uint32_t UNALIGN_TRP: 1; //!< Unaligned access traps enabled.
            uint32_t DIV_0_TRP: 1; //!< Divide by zero trap enabled.
            uint32_t RESERVED1: 3;
            uint32_t BFHFNMIGN: 1; //!< Handlers with priority -1 or -2 ignore data bus faults.
            uint32_t STKALIGN: 1; //!< 8-byte stack alignment on exception entry.
            uint32_t RESERVED2: 22;
        } bits;

        uint32_t value = 0;

        CCR() = default;

        CCR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! System handler control and state register.
    union SHCSR {
        struct Bits {
            uint32_t MEMFAULTACT: 1; //!< MemManage fault exception active.
            uint32_t BUSFAULTACT: 1; //!< BusFault exception active.
            uint32_t RESERVED0: 1;
            uint32_t USGFAULTACT: 1; //!< UsageFault exception active.
            uint32_t RESERVED1: 3;
            uint32_t SVCALLACT: 1; //!< SVCall active.
            uint32_t MONITORACT: 1; //!< Debug monitor active.
            uint32_t RESERVED2: 1;
            uint32_t PENDSVACT: 1; //!< PendSV exception active.
            uint32_t SYSTICKACT: 1; //!< SysTick exception active.
            uint32_t USGFAULTPENDED: 1; //!< UsageFault exception pending.
            uint32_t MEMFAULTPENDED: 1; //!< MemManage fault exception pending.
            uint32_t BUSFAULTPENDED: 1; //!< BusFault exception pending.
            uint32_t SVCALLPENDED: 1; //!< SVCall pending.
            uint32_t MEMFAULTENA: 1; //!< MemManage fault enable.
            uint32_t BUSFAULTENA: 1; //!< BusFault enable.
            uint32_t USGFAULTENA: 1; //!< UsageFault enable.
            uint32_t RESERVED3: 13;
        } bits;

        uint32_t value = 0;

        SHCSR() = default;

        SHCSR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Configurable fault status register.
    //! Combines MemManage, BusFault, and UsageFault status registers.
    union CFSR {
        struct Bits {
            // MemManage Fault Status Register (MMFSR) - bits 0:7
            uint32_t IACCVIOL: 1; //!< Instruction access violation.
            uint32_t DACCVIOL: 1; //!< Data access violation.
            uint32_t RESERVED0: 1;
            uint32_t MUNSTKERR: 1; //!< MemManage fault on unstacking.
            uint32_t MSTKERR: 1; //!< MemManage fault on stacking.
            uint32_t RESERVED1: 1;
            uint32_t RESERVED2: 1;
            uint32_t MMARVALID: 1; //!< MemManage fault address register valid.

            // BusFault Status Register (BFSR) - bits 8:15
            uint32_t IBUSERR: 1; //!< Instruction bus error.
            uint32_t PRECISERR: 1; //!< Precise data bus error.
            uint32_t IMPRECISERR: 1; //!< Imprecise data bus error.
            uint32_t UNSTKERR: 1; //!< BusFault on unstacking.
            uint32_t STKERR: 1; //!< BusFault on stacking.
            uint32_t RESERVED3: 1;
            uint32_t RESERVED4: 1;
            uint32_t BFARVALID: 1; //!< BusFault address register valid.

            // UsageFault Status Register (UFSR) - bits 16:31
            uint32_t UNDEFINSTR: 1; //!< Undefined instruction.
            uint32_t INVSTATE: 1; //!< Invalid state.
            uint32_t INVPC: 1; //!< Invalid PC load.
            uint32_t NOCP: 1; //!< No coprocessor.
            uint32_t RESERVED5: 4;
            uint32_t UNALIGNED: 1; //!< Unaligned access.
            uint32_t DIVBYZERO: 1; //!< Divide by zero.
            uint32_t RESERVED6: 6;
        } bits;

        uint32_t value = 0;

        CFSR() = default;

        CFSR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! HardFault status register.
    union HFSR {
        struct Bits {
            uint32_t RESERVED0: 1;
            uint32_t VECTTBL: 1; //!< Vector table read fault.
            uint32_t RESERVED1: 28;
            uint32_t FORCED: 1; //!< Forced HardFault (escalated fault).
            uint32_t DEBUGEVT: 1; //!< Debug event HardFault.
        } bits;

        uint32_t value = 0;

        HFSR() = default;

        HFSR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Debug fault status register.
    union DFSR {
        struct Bits {
            uint32_t HALTED: 1; //!< Halt request debug event.
            uint32_t BKPT: 1; //!< Breakpoint debug event.
            uint32_t DWTTRAP: 1; //!< Data Watchpoint and Trace (DWT) debug event.
            uint32_t VCATCH: 1; //!< Vector catch debug event.
            uint32_t EXTERNAL: 1; //!< External debug request.
            uint32_t RESERVED: 27;
        } bits;

        uint32_t value = 0;

        DFSR() = default;

        DFSR(uint32_t new_value)
        {
            value = new_value;
        }
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
