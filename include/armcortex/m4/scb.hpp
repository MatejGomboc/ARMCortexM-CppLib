/*
    Copyright (C) 2025 Matej Gomboc &lt;https://github.com/MatejGomboc/ARMCortexM-CppLib&gt;

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

#include &lt;arm_acle.h&gt;
#include &lt;cstdint&gt;

namespace ArmCortex::Scb {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000ED00u;

    struct Registers
    {
        volatile uint32_t CPUID; //!&lt; Processor part number, version, and implementation information.
        volatile uint32_t ICSR; //!&lt; Interrupt control and state register.
        volatile uint32_t VTOR; //!&lt; Vector table offset register.
        volatile uint32_t AIRCR; //!&lt; Application interrupt and reset control register.
        volatile uint32_t SCR; //!&lt; Low power state control.
        volatile uint32_t CCR; //!&lt; Configuration and control register.
        volatile uint8_t SHPR[12]; //!&lt; System handler priority registers.
        volatile uint32_t SHCSR; //!&lt; System handler control and state register.
        volatile uint32_t CFSR; //!&lt; Configurable fault status register.
        volatile uint32_t HFSR; //!&lt; HardFault status register.
        volatile uint32_t DFSR; //!&lt; Debug fault status register.
        volatile uint32_t MMFAR; //!&lt; MemManage fault address register.
        volatile uint32_t BFAR; //!&lt; BusFault address register.
        volatile uint32_t AFSR; //!&lt; Auxiliary fault status register.
        volatile uint32_t ID_PFR[2]; //!&lt; Processor feature registers.
        volatile uint32_t ID_DFR; //!&lt; Debug feature register.
        volatile uint32_t ID_AFR; //!&lt; Auxiliary feature register.
        volatile uint32_t ID_MMFR[4]; //!&lt; Memory model feature registers.
        volatile uint32_t ID_ISAR[5]; //!&lt; Instruction set attribute registers.
        volatile uint32_t RESERVED0[5];
        volatile uint32_t CPACR; //!&lt; Coprocessor access control register.
        volatile uint32_t RESERVED3[93];
        volatile uint32_t STIR; //!&lt; Software triggered interrupt register.
    };

    //! Processor part number, version, and implementation information.
    union CPUID {
        struct Bits {
            uint32_t REVISION: 4; //!&lt; Patch release (p in Rnpn).
            uint32_t PARTNO: 12; //!&lt; Part number (0xC24: Cortex-M4).
            uint32_t ARCHITECTURE: 4; //!&lt; Architecture (0xF: ARMv7E-M).
            uint32_t VARIANT: 4; //!&lt; Variant number (r in Rnpn).
            uint32_t IMPLEMENTER: 8; //!&lt; Implementer code (0x41: ARM).
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
            uint32_t VECTACTIVE: 9; //!&lt; Active exception number.
            uint32_t RESERVED0: 2;
            uint32_t RETTOBASE: 1; //!&lt; No preempted active exceptions.
            uint32_t VECTPENDING: 9; //!&lt; Highest priority pending exception number (0: none).
            uint32_t RESERVED1: 1;
            uint32_t ISRPENDING: 1; //!&lt; Interrupt pending (excluding NMI and faults).
            uint32_t ISRPREEMPT: 1; //!&lt; Preempted exception is active.
            uint32_t RESERVED2: 1;
            uint32_t PENDSTCLR: 1; //!&lt; Write 1 to clear SysTick pending state (write-only).
            uint32_t PENDSTSET: 1; //!&lt; SysTick pending (read), write 1 to set pending.
            uint32_t PENDSVCLR: 1; //!&lt; Write 1 to clear PendSV pending state (write-only).
            uint32_t PENDSVSET: 1; //!&lt; PendSV pending (read), write 1 to set pending.
            uint32_t RESERVED3: 2;
            uint32_t NMIPENDSET: 1; //!&lt; NMI pending (read), write 1 to set pending.
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
        static constexpr uint16_t VECTKEY_VALUE = 0x05FA; //!&lt; Write key to enable AIRCR writes.

        struct Bits {
            uint32_t VECTRESET: 1; //!&lt; System reset bit (deprecated, write 0).
            uint32_t VECTCLRACTIVE: 1; //!&lt; Clear all active state information for exceptions (write 0).
            uint32_t SYSRESETREQ: 1; //!&lt; System reset request.
            uint32_t RESERVED0: 5;
            uint32_t PRIGROUP: 3; //!&lt; Priority grouping (interrupt preemption level).
            uint32_t RESERVED1: 4;
            uint32_t ENDIANNESS: 1; //!&lt; Data endianness (0: little endian).
            uint32_t VECTKEY: 16; //!&lt; Write VECTKEY_VALUE to enable writes, otherwise ignored.
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
            uint32_t SLEEPONEXIT: 1; //!&lt; Enter sleep/deep sleep on ISR return to Thread mode.
            uint32_t SLEEPDEEP: 1; //!&lt; Use deep sleep instead of sleep.
            uint32_t RESERVED1: 1;
            uint32_t SEVONPEND: 1; //!&lt; Wake from WFE on any interrupt (including disabled).
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
            uint32_t NONBASETHRDENA: 1; //!&lt; Allow Thread mode with active exceptions.
            uint32_t USERSETMPEND: 1; //!&lt; Allow unprivileged software to access STIR.
            uint32_t RESERVED0: 1;
            uint32_t UNALIGN_TRP: 1; //!&lt; Trap on unaligned word/halfword access.
            uint32_t DIV_0_TRP: 1; //!&lt; Trap on divide by zero.
            uint32_t RESERVED1: 3;
            uint32_t BFHFNMIGN: 1; //!&lt; Handlers with priority -1 or -2 ignore data bus faults.
            uint32_t STKALIGN: 1; //!&lt; 8-byte stack alignment on exception entry.
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
            uint32_t MEMFAULTACT: 1; //!&lt; MemManage fault exception active.
            uint32_t BUSFAULTACT: 1; //!&lt; BusFault exception active.
            uint32_t RESERVED0: 1;
            uint32_t USGFAULTACT: 1; //!&lt; UsageFault exception active.
            uint32_t RESERVED1: 3;
            uint32_t SVCALLACT: 1; //!&lt; SVCall active.
            uint32_t MONITORACT: 1; //!&lt; Debug monitor active.
            uint32_t RESERVED2: 1;
            uint32_t PENDSVACT: 1; //!&lt; PendSV exception active.
            uint32_t SYSTICKACT: 1; //!&lt; SysTick exception active.
            uint32_t USGFAULTPENDED: 1; //!&lt; UsageFault exception pending.
            uint32_t MEMFAULTPENDED: 1; //!&lt; MemManage fault exception pending.
            uint32_t BUSFAULTPENDED: 1; //!&lt; BusFault exception pending.
            uint32_t SVCALLPENDED: 1; //!&lt; SVCall pending.
            uint32_t MEMFAULTENA: 1; //!&lt; MemManage fault enable.
            uint32_t BUSFAULTENA: 1; //!&lt; BusFault enable.
            uint32_t USGFAULTENA: 1; //!&lt; UsageFault enable.
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
    //! All status bits are W1C (write-1-to-clear).
    union CFSR {
        struct Bits {
            // MemManage Fault Status Register (MMFSR) - bits 0:7
            uint32_t IACCVIOL: 1; //!&lt; Instruction access violation.
            uint32_t DACCVIOL: 1; //!&lt; Data access violation.
            uint32_t RESERVED0: 1;
            uint32_t MUNSTKERR: 1; //!&lt; MemManage fault on unstacking.
            uint32_t MSTKERR: 1; //!&lt; MemManage fault on stacking.
            uint32_t MLSPERR: 1; //!&lt; MemManage fault during floating-point lazy state preservation.
            uint32_t RESERVED1: 1;
            uint32_t MMARVALID: 1; //!&lt; MemManage fault address register valid.

            // BusFault Status Register (BFSR) - bits 8:15
            uint32_t IBUSERR: 1; //!&lt; Instruction bus error.
            uint32_t PRECISERR: 1; //!&lt; Precise data bus error.
            uint32_t IMPRECISERR: 1; //!&lt; Imprecise data bus error.
            uint32_t UNSTKERR: 1; //!&lt; BusFault on unstacking.
            uint32_t STKERR: 1; //!&lt; BusFault on stacking.
            uint32_t LSPERR: 1; //!&lt; BusFault during floating-point lazy state preservation.
            uint32_t RESERVED2: 1;
            uint32_t BFARVALID: 1; //!&lt; BusFault address register valid.

            // UsageFault Status Register (UFSR) - bits 16:31
            uint32_t UNDEFINSTR: 1; //!&lt; Undefined instruction.
            uint32_t INVSTATE: 1; //!&lt; Invalid state (e.g., ARM mode).
            uint32_t INVPC: 1; //!&lt; Invalid PC load.
            uint32_t NOCP: 1; //!&lt; No coprocessor.
            uint32_t RESERVED3: 4;
            uint32_t UNALIGNED: 1; //!&lt; Unaligned access.
            uint32_t DIVBYZERO: 1; //!&lt; Divide by zero.
            uint32_t RESERVED4: 6;
        } bits;

        uint32_t value = 0;

        CFSR() = default;

        CFSR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! HardFault status register.
    //! All status bits are W1C (write-1-to-clear).
    union HFSR {
        struct Bits {
            uint32_t RESERVED0: 1;
            uint32_t VECTTBL: 1; //!&lt; Vector table read fault.
            uint32_t RESERVED1: 28;
            uint32_t FORCED: 1; //!&lt; Forced HardFault (escalated configurable fault).
            uint32_t DEBUGEVT: 1; //!&lt; Debug event HardFault.
        } bits;

        uint32_t value = 0;

        HFSR() = default;

        HFSR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Debug fault status register.
    //! All status bits are W1C (write-1-to-clear).
    union DFSR {
        struct Bits {
            uint32_t HALTED: 1; //!&lt; Halt request debug event.
            uint32_t BKPT: 1; //!&lt; Breakpoint debug event.
            uint32_t DWTTRAP: 1; //!&lt; Data Watchpoint and Trace (DWT) debug event.
            uint32_t VCATCH: 1; //!&lt; Vector catch debug event.
            uint32_t EXTERNAL: 1; //!&lt; External debug request.
            uint32_t RESERVED: 27;
        } bits;

        uint32_t value = 0;

        DFSR() = default;

        DFSR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Coprocessor access control register.
    //! Controls access to coprocessors CP0-CP15.
    //! On Cortex-M4 with FPU, CP10 and CP11 control access to the floating-point unit.
    union CPACR {
        //! Coprocessor access privilege values.
        enum class Access : uint8_t {
            DENIED = 0b00, //!&lt; Access denied (generates UsageFault).
            PRIVILEGED = 0b01, //!&lt; Privileged access only.
            RESERVED = 0b10, //!&lt; Reserved.
            FULL = 0b11 //!&lt; Full access.
        };

        struct Bits {
            uint32_t CP0: 2; //!&lt; Coprocessor 0 access.
            uint32_t CP1: 2; //!&lt; Coprocessor 1 access.
            uint32_t CP2: 2; //!&lt; Coprocessor 2 access.
            uint32_t CP3: 2; //!&lt; Coprocessor 3 access.
            uint32_t CP4: 2; //!&lt; Coprocessor 4 access.
            uint32_t CP5: 2; //!&lt; Coprocessor 5 access.
            uint32_t CP6: 2; //!&lt; Coprocessor 6 access.
            uint32_t CP7: 2; //!&lt; Coprocessor 7 access.
            uint32_t RESERVED0: 4;
            uint32_t CP10: 2; //!&lt; Coprocessor 10 access (FPU).
            uint32_t CP11: 2; //!&lt; Coprocessor 11 access (FPU).
            uint32_t RESERVED1: 4;
        } bits;

        uint32_t value = 0;

        CPACR() = default;

        CPACR(uint32_t new_value)
        {
            value = new_value;
        }
    };
}

namespace ArmCortex {
    inline volatile Scb::Registers* const SCB = reinterpret_cast&lt;volatile Scb::Registers*&gt;(Scb::BASE_ADDRESS);
}

namespace ArmCortex::Scb {
    [[gnu::noreturn, gnu::always_inline]] static inline void systemReset()
    {
        __dsb(0xF);

        AIRCR aircr { SCB-&gt;AIRCR };

        aircr.bits.VECTRESET = 0;
        aircr.bits.VECTCLRACTIVE = 0;
        aircr.bits.SYSRESETREQ = true;
        aircr.bits.VECTKEY = AIRCR::VECTKEY_VALUE;

        SCB-&gt;AIRCR = aircr.value;

        __dsb(0xF);
        __isb(0xF);

        while(true);
    }

    [[gnu::always_inline]] static inline void setPriorityGrouping(uint32_t priority_group)
    {
        __dsb(0xF);

        AIRCR aircr { SCB-&gt;AIRCR };

        aircr.bits.PRIGROUP = priority_group &amp; 0x7;
        aircr.bits.VECTKEY = AIRCR::VECTKEY_VALUE;

        SCB-&gt;AIRCR = aircr.value;

        __dsb(0xF);
        __isb(0xF);
    }

    [[gnu::always_inline]] static inline uint32_t getPriorityGrouping()
    {
        AIRCR aircr { SCB-&gt;AIRCR };
        return aircr.bits.PRIGROUP;
    }

    // =========================================================================
    // ICSR W1S/W1C Helper Functions
    // =========================================================================

    //! Check if SysTick exception is pending.
    [[gnu::always_inline]] static inline bool isSysTickPending()
    {
        ICSR icsr { SCB-&gt;ICSR };
        return icsr.bits.PENDSTSET;
    }

    //! Set SysTick exception pending. PENDSTSET is W1S (write-1-to-set).
    [[gnu::always_inline]] static inline void setSysTickPending()
    {
        constexpr uint32_t PENDSTSET_BIT = uint32_t{1} &lt;&lt; 26;
        SCB-&gt;ICSR = PENDSTSET_BIT;
    }

    //! Clear SysTick exception pending. PENDSTCLR is W1C (write-1-to-clear).
    [[gnu::always_inline]] static inline void clearSysTickPending()
    {
        constexpr uint32_t PENDSTCLR_BIT = uint32_t{1} &lt;&lt; 25;
        SCB-&gt;ICSR = PENDSTCLR_BIT;
    }

    //! Check if PendSV exception is pending.
    [[gnu::always_inline]] static inline bool isPendSVPending()
    {
        ICSR icsr { SCB-&gt;ICSR };
        return icsr.bits.PENDSVSET;
    }

    //! Set PendSV exception pending. PENDSVSET is W1S (write-1-to-set).
    [[gnu::always_inline]] static inline void setPendSV()
    {
        constexpr uint32_t PENDSVSET_BIT = uint32_t{1} &lt;&lt; 28;
        SCB-&gt;ICSR = PENDSVSET_BIT;
    }

    //! Clear PendSV exception pending. PENDSVCLR is W1C (write-1-to-clear).
    [[gnu::always_inline]] static inline void clearPendSV()
    {
        constexpr uint32_t PENDSVCLR_BIT = uint32_t{1} &lt;&lt; 27;
        SCB-&gt;ICSR = PENDSVCLR_BIT;
    }

    //! Check if NMI exception is pending.
    [[gnu::always_inline]] static inline bool isNMIPending()
    {
        ICSR icsr { SCB-&gt;ICSR };
        return icsr.bits.NMIPENDSET;
    }

    //! Trigger NMI exception. NMIPENDSET is W1S (write-1-to-set).
    //! \note NMI cannot be cleared by software once set.
    [[gnu::always_inline]] static inline void triggerNMI()
    {
        constexpr uint32_t NMIPENDSET_BIT = uint32_t{1} &lt;&lt; 31;
        SCB-&gt;ICSR = NMIPENDSET_BIT;
    }

    // =========================================================================
    // CFSR W1C Helper Functions (Configurable Fault Status)
    // =========================================================================

    //! Get the current configurable fault status.
    [[gnu::always_inline]] static inline CFSR getFaultStatus()
    {
        return CFSR { SCB-&gt;CFSR };
    }

    //! Clear all MemManage fault flags. All MMFSR bits are W1C.
    [[gnu::always_inline]] static inline void clearMemManageFaults()
    {
        constexpr uint32_t MMFSR_W1C_MASK = 0xBBu;  // bits 0,1,3,4,5,7
        SCB-&gt;CFSR = MMFSR_W1C_MASK;
    }

    //! Clear all BusFault flags. All BFSR bits are W1C.
    [[gnu::always_inline]] static inline void clearBusFaults()
    {
        constexpr uint32_t BFSR_W1C_MASK = 0xBF00u;  // bits 8,9,10,11,12,13,15
        SCB-&gt;CFSR = BFSR_W1C_MASK;
    }

    //! Clear all UsageFault flags. All UFSR bits are W1C.
    [[gnu::always_inline]] static inline void clearUsageFaults()
    {
        constexpr uint32_t UFSR_W1C_MASK = 0x030F0000u;  // bits 16,17,18,19,24,25
        SCB-&gt;CFSR = UFSR_W1C_MASK;
    }

    //! Clear all configurable fault flags (MemManage, BusFault, UsageFault).
    [[gnu::always_inline]] static inline void clearAllConfigurableFaults()
    {
        constexpr uint32_t CFSR_W1C_MASK = 0x030FBFBBu;  // all W1C bits
        SCB-&gt;CFSR = CFSR_W1C_MASK;
    }

    // =========================================================================
    // HFSR W1C Helper Functions (HardFault Status)
    // =========================================================================

    //! Get the current HardFault status.
    [[gnu::always_inline]] static inline HFSR getHardFaultStatus()
    {
        return HFSR { SCB-&gt;HFSR };
    }

    //! Clear all HardFault status flags. All HFSR status bits are W1C.
    [[gnu::always_inline]] static inline void clearHardFaultStatus()
    {
        constexpr uint32_t HFSR_W1C_MASK = 0xC0000002u;  // bits 1, 30, 31
        SCB-&gt;HFSR = HFSR_W1C_MASK;
    }

    // =========================================================================
    // DFSR W1C Helper Functions (Debug Fault Status)
    // =========================================================================

    //! Get the current debug fault status.
    [[gnu::always_inline]] static inline DFSR getDebugFaultStatus()
    {
        return DFSR { SCB-&gt;DFSR };
    }

    //! Clear all debug fault status flags. All DFSR bits are W1C.
    [[gnu::always_inline]] static inline void clearDebugFaultStatus()
    {
        constexpr uint32_t DFSR_W1C_MASK = 0x1Fu;  // bits 0-4
        SCB-&gt;DFSR = DFSR_W1C_MASK;
    }
}
