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

#include "barriers.hpp"
#include <cstdint>

namespace CortexM1::Scb {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000ED00u;

    struct Registers
    {
        volatile uint32_t CPUID; //!< contains the processor part number, version, and implementation information
        volatile uint32_t ICSR; //!< interrupt control and state register
        volatile uint32_t VTOR; //!< vector table offset register
        volatile uint32_t AIRCR; //!< enables system reset
        volatile uint32_t SCR; //!< controls features of entry to and exit from low power state
        volatile uint32_t CCR; //!< is a read-only register and indicates some aspects of the behaviour of the processor
        volatile uint32_t RESERVED1;
        volatile uint32_t SHPR2; //!< sets the priority level of the exception handlers that have configurable priority (SVCall)
        volatile uint32_t SHPR3; //!< sets the priority level of the exception handlers that have configurable priority (PendSV, SysTick)
    };

    //! is a read-only register and contains the processor part number, version, and implementation information
    union CPUID {
        struct Bits {
            uint32_t REVISION: 4; //!< the p value in the Rnpn product revision identifier, indicates patch release
            uint32_t PARTNO: 12; //!< part number of the processor (0xC61: Cortex-M1)
            uint32_t CONSTANT: 4; //!< constant that defines the architecture of the processor (0xC: ARMv6-M architecture)
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
            uint32_t RESERVED1: 1;
            uint32_t ISRPENDING: 1; //!< true if an external configurable, NVIC generated, interrupt is pending
            uint32_t ISRPREEMPT: 1; //!< true if a pending exception is serviced on exit from debug halt state
            uint32_t RESERVED2: 1;
            uint32_t PENDSTCLR: 1; //!< removes the pending state from the SysTick exception
            uint32_t PENDSTSET: 1; //!< changes SysTick exception state to pending
            uint32_t PENDSVCLR: 1; //!< removes the pending state from the PendSV exception
            uint32_t PENDSVSET: 1; //!< change PendSV exception state to pending
            uint32_t RESERVED3: 2;
            uint32_t NMIPENDSET: 1; //!< changes NMI exception state to pending
        } bits;

        uint32_t value = 0;

        ICSR() = default;

        ICSR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! enables system reset
    union AIRCR {
        static constexpr uint16_t VECTKEY_VALUE = 0x05FA; //!< magic number used for enabling writing to AIRCR

        struct Bits {
            uint32_t RESERVED0: 1;
            uint32_t VECTCLRACTIVE: 1; //!< reserved, write '0' to this bit
            uint32_t SYSRESETREQ: 1; //!< requests a system reset
            uint32_t RESERVED1: 12;
            uint32_t ENDIANESS: 1; //!< reads as 0 - little endian
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
            uint32_t RESERVED0: 3;
            uint32_t UNALIGN_TRP: 1; //!< always '1', indicates that all unaligned accesses generate a HardFault
            uint32_t RESERVED1: 4;
            uint32_t STKALIGN: 1; //!< always '1', indicates 8-byte stack alignment on exception entry
            uint32_t RESERVED2: 23;
        } bits;

        uint32_t value = 0;

        CCR() = default;

        CCR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! sets the priority level of the exception handlers that have configurable priority (SVCall)
    union SHPR2 {
        struct Bits {
            uint32_t RESERVED0: 24;
            uint32_t PRI_11: 8; //!< priority of SVCall exception (exception number 11)
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
            uint32_t PRI_14: 8; //!< priority of PendSV exception (exception number 14)
            uint32_t PRI_15: 8; //!< priority of SysTick exception (exception number 15)
        } bits;

        uint32_t value = 0;

        SHPR3() = default;

        SHPR3(uint32_t new_value)
        {
            value = new_value;
        }
    };
}

namespace CortexM1 {
    inline volatile Scb::Registers* const SCB = reinterpret_cast<volatile Scb::Registers*>(Scb::BASE_ADDRESS);
}

namespace CortexM1::Scb {
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
}
