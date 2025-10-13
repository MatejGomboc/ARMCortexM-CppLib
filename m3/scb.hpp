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
        volatile uint32_t CPUID; //!< contains the processor part number, version, and implementation information
        volatile uint32_t ICSR; //!< interrupt control and state register
        volatile uint32_t VTOR; //!< vector table offset register
        volatile uint32_t AIRCR; //!< application interrupt and reset control register
        volatile uint32_t SCR; //!< controls features of entry to and exit from low power state
        volatile uint32_t CCR; //!< configuration and control register
        volatile uint32_t SHPR1; //!< system handlers priority register 1
        volatile uint32_t SHPR2; //!< system handlers priority register 2
        volatile uint32_t SHPR3; //!< system handlers priority register 3
        volatile uint32_t SHCSR; //!< system handler control and state register
        volatile uint32_t CFSR; //!< configurable fault status register
        volatile uint32_t HFSR; //!< hard fault status register
        volatile uint32_t DFSR; //!< debug fault status register
        volatile uint32_t MMFAR; //!< memory management fault address register
        volatile uint32_t BFAR; //!< bus fault address register
        volatile uint32_t AFSR; //!< auxiliary fault status register
    };

    //! is a read-only register and contains the processor part number, version, and implementation information
    union CPUID {
        struct Bits {
            uint32_t REVISION: 4; //!< the p value in the Rnpn product revision identifier, indicates patch release
            uint32_t PARTNO: 12; //!< part number of the processor (0xC23: Cortex-M3)
            uint32_t CONSTANT: 4; //!< constant that defines the architecture of the processor (0xF: ARMv7-M architecture)
            uint32_t VARIANT: 4; //!< variant number: the r value in the Rnpn product revision identifier
            uint32_t IMPLEMENTER: 8; //!< implementer code (0x41: ARM)
        } bits;

        uint32_t value = 0;

        CPUID() = default;

        CPUID(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! interrupt control and state register
    union ICSR {
        struct Bits {
            uint32_t VECTACTIVE: 9; //!< exception number of the currently active exception
            uint32_t RESERVED0: 3;
            uint32_t VECTPENDING: 9; //!< exception number of the highest priority pending enabled exception
            uint32_t ISRPENDING: 1; //!< true if an external configurable, NVIC generated, interrupt is pending
            uint32_t ISRPREEMPT: 1; //!< true if a pending exception is serviced on exit from debug halt state
            uint32_t RESERVED1: 1;
            uint32_t PENDSTCLR: 1; //!< removes the pending state from the SysTick exception
            uint32_t PENDSTSET: 1; //!< changes SysTick exception state to pending
            uint32_t PENDSVCLR: 1; //!< removes the pending state from the PendSV exception
            uint32_t PENDSVSET: 1; //!< change PendSV exception state to pending
            uint32_t RESERVED2: 2;
            uint32_t NMIPENDSET: 1; //!< changes NMI exception state to pending
            uint32_t RETTOBASE: 1; //!< indicates whether there are preempted active exceptions
        } bits;

        uint32_t value = 0;

        ICSR() = default;

        ICSR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! vector table offset register
    union VTOR {
        struct Bits {
            uint32_t RESERVED: 9;
            uint32_t TBLOFF: 23; //!< vector table base offset field
        } bits;

        uint32_t value = 0;

        VTOR() = default;

        VTOR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! enables system reset
    union AIRCR {
        static constexpr uint16_t VECTKEY_VALUE = 0x05FA; //!< magic number used for enabling writing to AIRCR

        struct Bits {
            uint32_t VECTRESET: 1; //!< system reset bit
            uint32_t VECTCLRACTIVE: 1; //!< clears all active state information for exceptions
            uint32_t SYSRESETREQ: 1; //!< requests a system reset
            uint32_t RESERVED0: 5;
            uint32_t PRIGROUP: 3; //!< interrupt priority grouping field
            uint32_t RESERVED1: 4;
            uint32_t ENDIANNESS: 1; //!< reads as 0 - little endian
            uint32_t VECTKEY: 16; //!< on writes, VECTKEY_VALUE to this field, otherwise the write is ignored
        } bits;

        uint32_t value = 0;

        AIRCR() = default;

        AIRCR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! controls features of entry to and exit from low power state
    union SCR {
        struct Bits {
            uint32_t RESERVED0: 1;
            uint32_t SLEEPONEXIT: 1; //!< enter sleep or deep sleep on return from ISR
            uint32_t SLEEPDEEP: 1; //!< use deep sleep as low power mode
            uint32_t RESERVED1: 1;

            //! 0: only enabled exceptions or events can wakeup the processor, disabled exceptions are excluded
            //! 1: enabled events and all exceptions, including disabled exceptions, can wakeup the processor
            uint32_t SEVONPEND: 1;

            uint32_t RESERVED2: 27;
        } bits;

        uint32_t value = 0;

        SCR() = default;

        SCR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! is a read-only register and indicates some aspects of the behaviour of the processor
    union CCR {
        struct Bits {
            uint32_t NONBASETHRDENA: 1; //!< configures how the processor enters Thread mode
            uint32_t USERSETMPEND: 1; //!< enables unprivileged software access to STIR
            uint32_t RESERVED0: 1;
            uint32_t UNALIGN_TRP: 1; //!< enables unaligned access traps
            uint32_t DIV_0_TRP: 1; //!< enables divide by zero trap
            uint32_t RESERVED1: 3;
            uint32_t BFHFNMIGN: 1; //!< enables handlers with priority -1 or -2 to ignore data bus faults
            uint32_t STKALIGN: 1; //!< configures stack alignment on exception entry
            uint32_t RESERVED2: 22;
        } bits;

        uint32_t value = 0;

        CCR() = default;

        CCR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! sets the priority level of the exception handlers that have configurable priority (memory management, bus fault, usage fault)
    union SHPR1 {
        struct Bits {
            uint32_t PRI_4: 8; //!< priority of memory management fault exception (exception 4)
            uint32_t PRI_5: 8; //!< priority of bus fault exception (exception 5)
            uint32_t PRI_6: 8; //!< priority of usage fault exception (exception 6)
            uint32_t RESERVED: 8;
        } bits;

        uint32_t value = 0;

        SHPR1() = default;

        SHPR1(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! sets the priority level of the exception handlers that have configurable priority (SVCall)
    union SHPR2 {
        struct Bits {
            uint32_t RESERVED0: 24;
            uint32_t PRI_11: 8; //!< priority of SVCall exception (exception 11)
        } bits;

        uint32_t value = 0;

        SHPR2() = default;

        SHPR2(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! sets the priority level of the exception handlers that have configurable priority (PendSV, SysTick)
    union SHPR3 {
        struct Bits {
            uint32_t RESERVED0: 16;
            uint32_t PRI_14: 8; //!< priority of PendSV exception (exception 14)
            uint32_t PRI_15: 8; //!< priority of SysTick exception (exception 15)
        } bits;

        uint32_t value = 0;

        SHPR3() = default;

        SHPR3(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! system handler control and state register
    union SHCSR {
        struct Bits {
            uint32_t MEMFAULTACT: 1; //!< memory management fault exception active
            uint32_t BUSFAULTACT: 1; //!< bus fault exception active
            uint32_t RESERVED0: 1;
            uint32_t USGFAULTACT: 1; //!< usage fault exception active
            uint32_t RESERVED1: 3;
            uint32_t SVCALLACT: 1; //!< SVCall active
            uint32_t MONITORACT: 1; //!< debug monitor active
            uint32_t RESERVED2: 1;
            uint32_t PENDSVACT: 1; //!< PendSV exception active
            uint32_t SYSTICKACT: 1; //!< SysTick exception active
            uint32_t USGFAULTPENDED: 1; //!< usage fault exception pending
            uint32_t MEMFAULTPENDED: 1; //!< memory management fault exception pending
            uint32_t BUSFAULTPENDED: 1; //!< bus fault exception pending
            uint32_t SVCALLPENDED: 1; //!< SVCall pending
            uint32_t MEMFAULTENA: 1; //!< memory management fault enable
            uint32_t BUSFAULTENA: 1; //!< bus fault enable
            uint32_t USGFAULTENA: 1; //!< usage fault enable
            uint32_t RESERVED3: 13;
        } bits;

        uint32_t value = 0;

        SHCSR() = default;

        SHCSR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! configurable fault status register
    union CFSR {
        struct Bits {
            // Memory Management Fault Status Register (MMFSR)
            uint32_t IACCVIOL: 1; //!< instruction access violation
            uint32_t DACCVIOL: 1; //!< data access violation
            uint32_t RESERVED0: 1;
            uint32_t MUNSTKERR: 1; //!< memory management fault on unstacking
            uint32_t MSTKERR: 1; //!< memory management fault on stacking
            uint32_t MLSPERR: 1; //!< memory management fault during lazy FP state preservation
            uint32_t RESERVED1: 1;
            uint32_t MMARVALID: 1; //!< memory management fault address register valid

            // Bus Fault Status Register (BFSR)
            uint32_t IBUSERR: 1; //!< instruction bus error
            uint32_t PRECISERR: 1; //!< precise data bus error
            uint32_t IMPRECISERR: 1; //!< imprecise data bus error
            uint32_t UNSTKERR: 1; //!< bus fault on unstacking
            uint32_t STKERR: 1; //!< bus fault on stacking
            uint32_t LSPERR: 1; //!< bus fault during lazy FP state preservation
            uint32_t RESERVED2: 1;
            uint32_t BFARVALID: 1; //!< bus fault address register valid

            // Usage Fault Status Register (UFSR)
            uint32_t UNDEFINSTR: 1; //!< undefined instruction
            uint32_t INVSTATE: 1; //!< invalid state
            uint32_t INVPC: 1; //!< invalid PC load
            uint32_t NOCP: 1; //!< no coprocessor
            uint32_t RESERVED3: 4;
            uint32_t UNALIGNED: 1; //!< unaligned access
            uint32_t DIVBYZERO: 1; //!< divide by zero
            uint32_t RESERVED4: 6;
        } bits;

        uint32_t value = 0;

        CFSR() = default;

        CFSR(uint32_t new_value)
        {
            value = new_value;
        }
    };
}

namespace Cortex::M3 {
    inline volatile Scb::Registers* const SCB = reinterpret_cast<volatile Scb::Registers*>(Scb::BASE_ADDRESS);
}

namespace Cortex::M3::Scb {
    [[noreturn]] static inline void systemReset()
    {
        dataSyncBarrier();

        AIRCR aircr { SCB->AIRCR };

        aircr.bits.SYSRESETREQ = true;
        aircr.bits.VECTKEY = AIRCR::VECTKEY_VALUE;

        SCB->AIRCR = aircr.value;

        dataSyncBarrier();
        instrSyncBarrier();

        while(true);
    }

    static inline void setPriorityGrouping(uint32_t pri_group)
    {
        AIRCR aircr { SCB->AIRCR };

        aircr.bits.PRIGROUP = pri_group & 0x7;
        aircr.bits.VECTKEY = AIRCR::VECTKEY_VALUE;

        SCB->AIRCR = aircr.value;

        dataSyncBarrier();
        instrSyncBarrier();
    }

    static inline uint32_t getPriorityGrouping()
    {
        AIRCR aircr { SCB->AIRCR };
        return aircr.bits.PRIGROUP;
    }
}
