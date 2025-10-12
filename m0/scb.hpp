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

namespace Cortex::M0::Scb {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000ED00u;

    struct Registers
    {
        volatile uint32_t CPUID; //!< Contains the processor part number, version, and implementation information.
        volatile uint32_t ICSR; //!< Interrupt control and state register.
        volatile uint32_t RESERVED0;
        volatile uint32_t AIRCR; //!< Application interrupt and reset control register.
        volatile uint32_t SCR; //!< Controls features of entry to and exit from low power state.
        volatile uint32_t CCR; //!< Read-only register that indicates some aspects of the behavior of the processor.
        volatile uint32_t RESERVED1;
        volatile uint32_t SHPR2; //!< Sets the priority level of the exception handlers that have configurable priority (SVCall).
        volatile uint32_t SHPR3; //!< Sets the priority level of the exception handlers that have configurable priority (PendSV, SysTick).
        volatile uint32_t SHCSR; //!< System handler control and state register.
    };

    //! Contains the processor part number, version, and implementation information.
    union CPUID {
        struct Bits {
            uint32_t REVISION: 4; //!< The p value in the Rnpn product revision identifier. Indicates the patch release.
            uint32_t PARTNO: 12; //!< Part number of the processor (0xC60: Cortex-M0).
            uint32_t ARCHITECTURE: 4; //!< Constant that defines the architecture of the processor (0xC: ARMv6-M architecture).
            uint32_t VARIANT: 4; //!< Variant number. The r value in the Rnpn product revision identifier.
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
    //! Provides:
    //! - A set-pending bit for the Non-Maskable Interrupt (NMI) exception.
    //! - Set-pending and clear-pending bits for the PendSV and SysTick exceptions.
    //! Indicates:
    //! - The exception number of the exception being processed.
    //! - Whether there are preempted active exceptions.
    //! - The exception number of the highest priority pending exception.
    //! - Whether any interrupts are pending.
    //! Caution: When you write to the ICSR, the effect is unpredictable if you:
    //! - Write 1 to the PENDSVSET bit and write 1 to the PENDSVCLR bit.
    //! - Write 1 to the PENDSTSET bit and write 1 to the PENDSTCLR bit.
    union ICSR {
        struct Bits {
            //! Active vector. Contains the active exception number.
            uint32_t VECTACTIVE: 9;

            uint32_t RESERVED0: 3;

            //! Pending vector. Indicates the exception number of the highest priority pending enabled exception.
            //! 0: No pending exceptions.
            //! Other values: The exception number of the highest priority pending enabled exception.
            uint32_t VECTPENDING: 9;

            uint32_t RESERVED1: 1;

            //! Interrupt pending flag, excluding NMI and Faults.
            //! 0: Interrupt not pending.
            //! 1: Interrupt pending.
            uint32_t ISRPENDING: 1;

            //! Preempted active exception indicator.
            //! 0: No preempted active exceptions.
            //! 1: A preempted exception is active.
            uint32_t ISRPREEMPT: 1;

            uint32_t RESERVED2: 1;

            //! SysTick exception clear-pending bit.
            //! Write-only. On a read, the value is unknown.
            //! 0: No effect.
            //! 1: Removes the pending state from the SysTick exception.
            uint32_t PENDSTCLR: 1;

            //! SysTick exception set-pending bit.
            //! Write:
            //! 0: No effect.
            //! 1: Change SysTick exception state to pending.
            //! Read:
            //! 0: SysTick exception is not pending.
            //! 1: SysTick exception is pending.
            uint32_t PENDSTSET: 1;

            //! PendSV clear-pending bit.
            //! This bit is write-only. On a read, the value is unknown.
            //! 0: No effect.
            //! 1: Removes the pending state from the PendSV exception.
            uint32_t PENDSVCLR: 1;

            //! PendSV set-pending bit.
            //! Write:
            //! 0: No effect.
            //! 1: Change PendSV exception state to pending.
            //! Read:
            //! 0: PendSV exception is not pending.
            //! 1: PendSV exception is pending.
            //! Writing 1 to this bit is the only way to set the PendSV exception state to pending.
            uint32_t PENDSVSET: 1;

            uint32_t RESERVED3: 2;

            //! NMI set-pending bit.
            //! Write:
            //! 0: No effect.
            //! 1: Change NMI exception state to pending.
            //! Read:
            //! 0: NMI exception is not pending.
            //! 1: NMI exception is pending.
            //! Because NMI is the highest-priority exception, normally the processor enters the NMI exception handler as soon as it registers
            //! a write of 1 to this bit, and entering the handler clears this bit to 0. A read of this bit by the NMI exception handler returns 1
            //! only if the NMI signal is reasserted while the processor is executing that handler.
            uint32_t NMIPENDSET: 1;
        } bits;

        uint32_t value = 0;

        ICSR() = default;

        ICSR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Provides endian status for data accesses and reset control of the system.
    union AIRCR {
        static constexpr uint16_t VECTKEY_VALUE = 0x05FA; //!< Magic number used for enabling writing to AIRCR.

        struct Bits {
            uint32_t RESERVED0: 1;
            uint32_t VECTCLRACTIVE: 1; //!< Reserved. Write '0' to this bit.
            uint32_t SYSRESETREQ: 1; //!< Asserts a signal to the outer system that requests a reset.
            uint32_t RESERVED1: 12;
            uint32_t ENDIANESS: 1; //!< Reads as 0 (little endian).
            uint32_t VECTKEY: 16; //!< On writes to AIRCR, write VECTKEY_VALUE to this field, otherwise the write to AIRCR is ignored.
        } bits;

        uint32_t value = 0;

        AIRCR() = default;

        AIRCR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Controls features of entry to and exit from low power state.
    union SCR {
        struct Bits {
            uint32_t RESERVED0: 1;

            //! Configures sleep-on-exit when returning from Handler mode to Thread mode. Setting this bit to 1 enables an interrupt-driven
            //! application to avoid returning to an empty main application.
            //! 0: Do not sleep when returning to Thread mode.
            //! 1: Enter sleep, or deep sleep, on return to Thread mode from an interrupt service routine.
            uint32_t SLEEPONEXIT: 1;

            //! Controls whether the processor uses sleep or deep sleep as its low power mode.
            //! 0: Sleep.
            //! 1: Deep sleep.
            uint32_t SLEEPDEEP: 1;

            uint32_t RESERVED1: 1;

            //! Send event on pending bit.
            //! When an event or interrupt enters pending state, the event signal wakes up the processor from WFE.
            //! If the processor is not waiting for an event, the event is registered and affects the next WFE.
            //! The processor also wakes up on execution of an SEV instruction or an external event.
            //! 0: Only enabled interrupts or events can wake up the processor. Disabled interrupts are excluded.
            //! 1: Enabled events and all interrupts, including disabled interrupts, can wake up the processor.
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

    //! Read-only register that indicates some aspects of the behavior of the processor.
    union CCR {
        struct Bits {
            uint32_t RESERVED0: 3;
            uint32_t UNALIGN_TRP: 1; //!< Always '1'. Indicates that all unaligned accesses generate a HardFault.
            uint32_t RESERVED1: 5;

            //! Always reads as one. Indicates 8-byte stack alignment on exception entry.
            //! On exception entry, the processor uses bit[9] of the stacked PSR to indicate the stack alignment. On return from the exception,
            //! it uses this stacked bit to restore the correct stack alignment.
            uint32_t STKALIGN: 1;

            uint32_t RESERVED2: 22;
        } bits;

        uint32_t value = 0;

        CCR() = default;

        CCR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Sets the priority level of the exception handlers that have configurable priority (SVCall).
    union SHPR2 {
        struct Bits {
            uint32_t RESERVED0: 24;
            uint32_t PRI_11: 8; //!< Priority of SVCall exception (exception number 11).
        } bits;

        uint32_t value = 0;

        SHPR2() = default;

        SHPR2(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Sets the priority level of the exception handlers that have configurable priority (PendSV, SysTick).
    union SHPR3 {
        struct Bits {
            uint32_t RESERVED0: 16;
            uint32_t PRI_14: 8; //!< Priority of PendSV exception (exception number 14).
            uint32_t PRI_15: 8; //!< Priority of SysTick exception (exception number 15).
        } bits;

        uint32_t value = 0;

        SHPR3() = default;

        SHPR3(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! System handler control and state register.
    union SHCSR {
        struct Bits {
            uint32_t RESERVED0: 15;

            //! SVCall pending bit.
            //! 0: SVCall is not pending.
            //! 1: SVCall is pending.
            uint32_t SVCALLPENDED: 1;

            uint32_t RESERVED1: 16;
        } bits;

        uint32_t value = 0;

        SHCSR() = default;

        SHCSR(uint32_t new_value)
        {
            value = new_value;
        }
    };
}

namespace Cortex::M0 {
    inline volatile Scb::Registers* const SCB = reinterpret_cast<volatile Scb::Registers*>(Scb::BASE_ADDRESS);
}

namespace Cortex::M0::Scb {
    [[noreturn]] static inline void systemReset()
    {
        dataSyncBarrier();

        AIRCR aircr { SCB->AIRCR };

        aircr.bits.VECTCLRACTIVE = 0;
        aircr.bits.SYSRESETREQ = true;
        aircr.bits.VECTKEY = AIRCR::VECTKEY_VALUE;

        SCB->AIRCR = aircr.value;

        dataSyncBarrier();
        instrSyncBarrier();

        while(true);
    }
}
