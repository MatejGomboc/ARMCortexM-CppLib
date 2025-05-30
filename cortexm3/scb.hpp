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

namespace CortexM3::Scb {
    static uint32_t* const BASE_ADDR = reinterpret_cast<uint32_t*>(0xE000ED00);

    //! is a read-only register and contains the processor part number, version, and implementation information
    union Cpuid {
        struct Bits {
            uint32_t revision: 4; //!< the p value in the Rnpn product revision identifier, indicates patch release
            uint32_t part_no: 12; //!< part number of the processor (0xC23: Cortex-M3)
            uint32_t constant: 4; //!< constant that defines the architecture of the processor (0xF: ARMv7-M architecture)
            uint32_t variant: 4; //!< variant number: the r value in the Rnpn product revision identifier
            uint32_t implementer: 8; //!< implementer code (0x41: ARM)
        } bits;

        uint32_t value = 0;

        Cpuid() = default;

        Cpuid(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! interrupt control and state register
    union Icsr {
        struct Bits {
            uint32_t active_exception: 9; //!< exception number of the currently active exception
            uint32_t reserved0: 3;
            uint32_t pending_exception: 9; //!< exception number of the highest priority pending enabled exception
            uint32_t irq_is_pending: 1; //!< true if an external configurable, NVIC generated, interrupt is pending
            uint32_t exception_is_pending: 1; //!< true if a pending exception is serviced on exit from debug halt state
            uint32_t reserved1: 1;
            uint32_t pending_sys_tick_clear: 1; //!< removes the pending state from the SysTick exception
            uint32_t pending_sys_tick_set: 1; //!< changes SysTick exception state to pending
            uint32_t pending_sv_clear: 1; //!< removes the pending state from the PendSV exception
            uint32_t pending_sv_set: 1; //!< change PendSV exception state to pending
            uint32_t reserved2: 2;
            uint32_t nmi_pending_set: 1; //!< changes NMI exception state to pending
            uint32_t ret_to_base: 1; //!< indicates whether there are preempted active exceptions
        } bits;

        uint32_t value = 0;

        Icsr() = default;

        Icsr(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! vector table offset register
    union Vtor {
        struct Bits {
            uint32_t reserved: 9;
            uint32_t table_offset: 21; //!< vector table base offset field
            uint32_t table_base: 2; //!< determines whether the vector table is in code (0) or SRAM (1) region
        } bits;

        uint32_t value = 0;

        Vtor() = default;

        Vtor(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! enables system reset
    union Aircr {
        static constexpr uint16_t VECT_KEY = 0x05FA; //!< magic number used for enabling writing to Aircr

        struct Bits {
            uint32_t vect_reset: 1; //!< system reset bit
            uint32_t vect_clr_active: 1; //!< clears all active state information for exceptions
            uint32_t sys_reset_req: 1; //!< requests a system reset
            uint32_t reserved0: 5;
            uint32_t pri_group: 3; //!< interrupt priority grouping field
            uint32_t reserved1: 4;
            uint32_t endianness: 1; //!< reads as 0 - little endian
            uint32_t vect_key: 16; //!< on writes, VECT_KEY to this field, otherwise the write is ignored
        } bits;

        uint32_t value = 0;

        Aircr() = default;

        Aircr(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! controls features of entry to and exit from low power state
    union Scr {
        struct Bits {
            uint32_t reserved0: 1;
            uint32_t sleep_on_isr_exit: 1; //!< enter sleep or deep sleep on return from ISR
            uint32_t use_deep_sleep: 1; //!< use deep sleep as low power mode
            uint32_t reserved1: 1;

            //! 0: only enabled exceptions or events can wakeup the processor, disabled exceptions are excluded
            //! 1: enabled events and all exceptions, including disabled exceptions, can wakeup the processor
            uint32_t send_event_on_except_pending: 1;

            uint32_t reserved2: 27;
        } bits;

        uint32_t value = 0;

        Scr() = default;

        Scr(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! is a read-only register and indicates some aspects of the behaviour of the processor
    union Ccr {
        struct Bits {
            uint32_t non_base_thread_enable: 1; //!< configures how the processor enters Thread mode
            uint32_t user_set_pending_enable: 1; //!< enables unprivileged software access to STIR
            uint32_t reserved0: 1;
            uint32_t fault_on_unaligned_access: 1; //!< enables unaligned access traps
            uint32_t div_by_zero_trap_enable: 1; //!< enables divide by zero trap
            uint32_t reserved1: 3;
            uint32_t bfhf_nmign: 1; //!< enables handlers with priority -1 or -2 to ignore data bus faults
            uint32_t stack_alignment: 1; //!< configures stack alignment on exception entry
            uint32_t reserved2: 22;
        } bits;

        uint32_t value = 0;

        Ccr() = default;

        Ccr(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! sets the priority level of the exception handlers that have configurable priority (memory management, bus fault, usage fault)
    union Shpr1 {
        struct Bits {
            uint32_t mem_manage_priority: 8; //!< priority of memory management fault exception
            uint32_t bus_fault_priority: 8; //!< priority of bus fault exception
            uint32_t usage_fault_priority: 8; //!< priority of usage fault exception
            uint32_t reserved: 8;
        } bits;

        uint32_t value = 0;

        Shpr1() = default;

        Shpr1(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! sets the priority level of the exception handlers that have configurable priority (SVCall)
    union Shpr2 {
        struct Bits {
            uint32_t reserved0: 24;
            uint32_t sv_call_except_priority: 8; //!< priority of SVCall exception
        } bits;

        uint32_t value = 0;

        Shpr2() = default;

        Shpr2(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! sets the priority level of the exception handlers that have configurable priority (PendSV, SysTick)
    union Shpr3 {
        struct Bits {
            uint32_t reserved0: 16;
            uint32_t pend_sv_except_priority: 8; //!< priority of PendSV exception
            uint32_t sys_tick_except_priority: 8; //!< priority of SysTick exception
        } bits;

        uint32_t value = 0;

        Shpr3() = default;

        Shpr3(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! system handler control and state register
    union Shcsr {
        struct Bits {
            uint32_t mem_fault_active: 1; //!< memory management fault exception active
            uint32_t bus_fault_active: 1; //!< bus fault exception active
            uint32_t reserved0: 1;
            uint32_t usage_fault_active: 1; //!< usage fault exception active
            uint32_t reserved1: 3;
            uint32_t sv_call_active: 1; //!< SVCall active
            uint32_t monitor_active: 1; //!< debug monitor active
            uint32_t reserved2: 1;
            uint32_t pend_sv_active: 1; //!< PendSV exception active
            uint32_t sys_tick_active: 1; //!< SysTick exception active
            uint32_t usage_fault_pending: 1; //!< usage fault exception pending
            uint32_t mem_fault_pending: 1; //!< memory management fault exception pending
            uint32_t bus_fault_pending: 1; //!< bus fault exception pending
            uint32_t sv_call_pending: 1; //!< SVCall pending
            uint32_t mem_fault_enabled: 1; //!< memory management fault enable
            uint32_t bus_fault_enabled: 1; //!< bus fault enable
            uint32_t usage_fault_enabled: 1; //!< usage fault enable
            uint32_t reserved3: 13;
        } bits;

        uint32_t value = 0;

        Shcsr() = default;

        Shcsr(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! configurable fault status register
    union Cfsr {
        struct Bits {
            // Memory Management Fault Status Register (MMFSR)
            uint32_t iaccviol: 1; //!< instruction access violation
            uint32_t daccviol: 1; //!< data access violation
            uint32_t reserved0: 1;
            uint32_t munstkerr: 1; //!< memory management fault on unstacking
            uint32_t mstkerr: 1; //!< memory management fault on stacking
            uint32_t mlsperr: 1; //!< memory management fault during lazy FP state preservation
            uint32_t reserved1: 1;
            uint32_t mmarvalid: 1; //!< memory management fault address register valid
            
            // Bus Fault Status Register (BFSR)
            uint32_t ibuserr: 1; //!< instruction bus error
            uint32_t preciserr: 1; //!< precise data bus error
            uint32_t impreciserr: 1; //!< imprecise data bus error
            uint32_t unstkerr: 1; //!< bus fault on unstacking
            uint32_t stkerr: 1; //!< bus fault on stacking
            uint32_t lsperr: 1; //!< bus fault during lazy FP state preservation
            uint32_t reserved2: 1;
            uint32_t bfarvalid: 1; //!< bus fault address register valid
            
            // Usage Fault Status Register (UFSR)
            uint32_t undefinstr: 1; //!< undefined instruction
            uint32_t invstate: 1; //!< invalid state
            uint32_t invpc: 1; //!< invalid PC load
            uint32_t nocp: 1; //!< no coprocessor
            uint32_t reserved3: 4;
            uint32_t unaligned: 1; //!< unaligned access
            uint32_t divbyzero: 1; //!< divide by zero
            uint32_t reserved4: 6;
        } bits;

        uint32_t value = 0;

        Cfsr() = default;

        Cfsr(uint32_t new_value)
        {
            value = new_value;
        }
    };

    struct Registers
    {
        volatile uint32_t cpuid; //!< contains the processor part number, version, and implementation information
        volatile uint32_t icsr; //!< interrupt control and state register
        volatile uint32_t vtor; //!< vector table offset register
        volatile uint32_t aircr; //!< application interrupt and reset control register
        volatile uint32_t scr; //!< controls features of entry to and exit from low power state
        volatile uint32_t ccr; //!< configuration and control register
        volatile uint32_t shpr1; //!< system handlers priority register 1
        volatile uint32_t shpr2; //!< system handlers priority register 2
        volatile uint32_t shpr3; //!< system handlers priority register 3
        volatile uint32_t shcsr; //!< system handler control and state register
        volatile uint32_t cfsr; //!< configurable fault status register
        volatile uint32_t hfsr; //!< hard fault status register
        volatile uint32_t dfsr; //!< debug fault status register
        volatile uint32_t mmfar; //!< memory management fault address register
        volatile uint32_t bfar; //!< bus fault address register
        volatile uint32_t afsr; //!< auxiliary fault status register
    };

    static inline volatile Registers* registers()
    {
        return reinterpret_cast<volatile Registers*>(BASE_ADDR);
    }

    __attribute__((noreturn)) static inline void systemReset()
    {
        asm volatile("DSB" : : : "memory");

        Aircr aircr { registers()->aircr };

        aircr.bits.sys_reset_req = true;
        aircr.bits.vect_key = Aircr::VECT_KEY;

        registers()->aircr = aircr.value;

        asm volatile("DSB" : : : "memory");

        while(true);
    }

    static inline void setPriorityGrouping(uint32_t pri_group)
    {
        Aircr aircr { registers()->aircr };
        
        aircr.bits.pri_group = pri_group & 0x7;
        aircr.bits.vect_key = Aircr::VECT_KEY;
        
        registers()->aircr = aircr.value;
        
        asm volatile("DSB" : : : "memory");
        asm volatile("ISB" : : : "memory");
    }

    static inline uint32_t getPriorityGrouping()
    {
        Aircr aircr { registers()->aircr };
        return aircr.bits.pri_group;
    }
}
