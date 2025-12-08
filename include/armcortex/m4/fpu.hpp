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

#include <cstdint>

namespace ArmCortex::Fpu {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000EF34u;

    struct Registers {
        volatile uint32_t FPCCR; //!< Floating-point context control register.
        volatile uint32_t FPCAR; //!< Floating-point context address register.
        volatile uint32_t FPDSCR; //!< Floating-point default status control register.
        volatile uint32_t MVFR0; //!< Media and VFP feature register 0.
        volatile uint32_t MVFR1; //!< Media and VFP feature register 1.
    };

    //! Floating-point context control register.
    //! Controls lazy stacking behavior and indicates FPU state.
    union FPCCR {
        struct Bits {
            uint32_t LSPACT: 1; //!< Lazy state preservation active.
            uint32_t USER: 1; //!< User privilege level when LSPACT was set.
            uint32_t RESERVED0: 1;
            uint32_t THREAD: 1; //!< Thread mode when LSPACT was set.
            uint32_t HFRDY: 1; //!< HardFault ready for lazy stacking.
            uint32_t MMRDY: 1; //!< MemManage ready for lazy stacking.
            uint32_t BFRDY: 1; //!< BusFault ready for lazy stacking.
            uint32_t RESERVED1: 1;
            uint32_t MONRDY: 1; //!< Debug monitor ready for lazy stacking.
            uint32_t RESERVED2: 21;
            uint32_t LSPEN: 1; //!< Lazy state preservation enable (automatic on exception entry).
            uint32_t ASPEN: 1; //!< Automatic state preservation enable (CONTROL.FPCA set on FP instruction).
        } bits;

        uint32_t value = 0;

        FPCCR() = default;

        FPCCR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Floating-point context address register.
    //! Holds the address of the unpopulated floating-point register space on the stack.
    union FPCAR {
        struct Bits {
            uint32_t RESERVED: 3;
            uint32_t ADDRESS: 29; //!< Address of unpopulated FP register space (8-byte aligned).
        } bits;

        uint32_t value = 0;

        FPCAR() = default;

        FPCAR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Floating-point default status control register.
    //! Default values for FPSCR when lazy stacking initializes the FPU.
    union FPDSCR {
        //! Rounding mode.
        enum class RMode : uint8_t {
            NEAREST = 0b00, //!< Round to nearest (RN).
            PLUS_INFINITY = 0b01, //!< Round towards plus infinity (RP).
            MINUS_INFINITY = 0b10, //!< Round towards minus infinity (RM).
            ZERO = 0b11 //!< Round towards zero (RZ).
        };

        struct Bits {
            uint32_t RESERVED0: 22;
            uint32_t RMODE: 2; //!< Default rounding mode.
            uint32_t FZ: 1; //!< Default flush-to-zero mode.
            uint32_t DN: 1; //!< Default NaN mode.
            uint32_t AHP: 1; //!< Default alternative half-precision mode.
            uint32_t RESERVED1: 5;
        } bits;

        uint32_t value = 0;

        FPDSCR() = default;

        FPDSCR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Media and VFP feature register 0.
    //! Describes the features provided by the FPU.
    union MVFR0 {
        //! Single-precision support.
        enum class SinglePrecision : uint8_t {
            NOT_SUPPORTED = 0x0, //!< Not supported.
            SUPPORTED = 0x2 //!< Single-precision supported.
        };

        //! Double-precision support.
        enum class DoublePrecision : uint8_t {
            NOT_SUPPORTED = 0x0, //!< Not supported.
            SUPPORTED = 0x2 //!< Double-precision supported.
        };

        //! VFP exception trapping support.
        enum class VfpExceptionTrapping : uint8_t {
            NOT_SUPPORTED = 0x0 //!< Not supported.
        };

        //! Divide support.
        enum class Divide : uint8_t {
            NOT_SUPPORTED = 0x0, //!< Not supported.
            SUPPORTED = 0x1 //!< Divide supported.
        };

        //! Square root support.
        enum class SquareRoot : uint8_t {
            NOT_SUPPORTED = 0x0, //!< Not supported.
            SUPPORTED = 0x1 //!< Square root supported.
        };

        //! Short vector support.
        enum class ShortVectors : uint8_t {
            NOT_SUPPORTED = 0x0 //!< Not supported.
        };

        //! VFP rounding modes support.
        enum class VfpRoundingModes : uint8_t {
            NEAREST_ONLY = 0x0, //!< Only round-to-nearest mode supported.
            ALL_MODES = 0x1 //!< All rounding modes supported.
        };

        struct Bits {
            uint32_t A_SIMD_REGISTERS: 4; //!< A_SIMD registers (0x1: 16 x 64-bit registers).
            uint32_t SINGLE_PRECISION: 4; //!< Single-precision support.
            uint32_t DOUBLE_PRECISION: 4; //!< Double-precision support.
            uint32_t VFP_EXCEPTION_TRAPPING: 4; //!< VFP exception trapping support.
            uint32_t DIVIDE: 4; //!< Divide support.
            uint32_t SQUARE_ROOT: 4; //!< Square root support.
            uint32_t SHORT_VECTORS: 4; //!< Short vector support.
            uint32_t VFP_ROUNDING_MODES: 4; //!< VFP rounding modes support.
        } bits;

        uint32_t value = 0;

        MVFR0() = default;

        MVFR0(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! Media and VFP feature register 1.
    //! Describes additional features provided by the FPU.
    union MVFR1 {
        //! Flush-to-zero mode support.
        enum class FlushToZeroMode : uint8_t {
            NOT_SUPPORTED = 0x0, //!< Not supported.
            SUPPORTED = 0x1 //!< Flush-to-zero supported.
        };

        //! Default NaN mode support.
        enum class DefaultNaNMode : uint8_t {
            NOT_SUPPORTED = 0x0, //!< Not supported.
            SUPPORTED = 0x1 //!< Default NaN mode supported.
        };

        //! FP fused multiply-accumulate support.
        enum class FpFusedMac : uint8_t {
            NOT_SUPPORTED = 0x0, //!< Not supported.
            SUPPORTED = 0x1 //!< Fused MAC supported.
        };

        //! FP half-precision and double-precision support.
        enum class FpHpfp : uint8_t {
            NOT_SUPPORTED = 0x0, //!< Not supported.
            HALF_TO_SINGLE = 0x1, //!< Half-precision to single-precision conversion.
            HALF_TO_SINGLE_AND_DOUBLE = 0x2 //!< Half-precision to single and double conversion.
        };

        struct Bits {
            uint32_t FTZ_MODE: 4; //!< Flush-to-zero mode support.
            uint32_t D_NAN_MODE: 4; //!< Default NaN mode support.
            uint32_t RESERVED0: 16;
            uint32_t FP_HPFP: 4; //!< FP half-precision support.
            uint32_t FP_FUSED_MAC: 4; //!< FP fused multiply-accumulate support.
        } bits;

        uint32_t value = 0;

        MVFR1() = default;

        MVFR1(uint32_t new_value)
        {
            value = new_value;
        }
    };
}

namespace ArmCortex {
    inline volatile Fpu::Registers* const FPU = reinterpret_cast<volatile Fpu::Registers*>(Fpu::BASE_ADDRESS);
}

namespace ArmCortex::Fpu {
    //! Enable lazy stacking for floating-point context preservation.
    //! This allows automatic FPU state saving on exception entry without
    //! actually pushing the registers until they are needed.
    [[gnu::always_inline]] static inline void enableLazyStacking()
    {
        FPCCR fpccr { FPU->FPCCR };
        fpccr.bits.ASPEN = true;
        fpccr.bits.LSPEN = true;
        FPU->FPCCR = fpccr.value;
    }

    //! Disable lazy stacking for floating-point context preservation.
    //! FPU state will be saved immediately on exception entry.
    [[gnu::always_inline]] static inline void disableLazyStacking()
    {
        FPCCR fpccr { FPU->FPCCR };
        fpccr.bits.LSPEN = false;
        FPU->FPCCR = fpccr.value;
    }

    //! Disable automatic state preservation entirely.
    //! Use when manually managing FPU context in exception handlers.
    [[gnu::always_inline]] static inline void disableAutomaticStatePreservation()
    {
        FPCCR fpccr { FPU->FPCCR };
        fpccr.bits.ASPEN = false;
        fpccr.bits.LSPEN = false;
        FPU->FPCCR = fpccr.value;
    }

    //! Check if lazy state preservation is currently active.
    [[gnu::always_inline]] static inline bool isLazyStackingActive()
    {
        FPCCR fpccr { FPU->FPCCR };
        return fpccr.bits.LSPACT;
    }

    //! Get the address of the unpopulated floating-point register space.
    [[gnu::always_inline]] static inline uint32_t getLazyStackAddress()
    {
        return FPU->FPCAR;
    }

    //! Check if single-precision floating-point is supported.
    [[gnu::always_inline]] static inline bool isSinglePrecisionSupported()
    {
        MVFR0 mvfr0 { FPU->MVFR0 };
        return mvfr0.bits.SINGLE_PRECISION != 0;
    }

    //! Check if double-precision floating-point is supported.
    [[gnu::always_inline]] static inline bool isDoublePrecisionSupported()
    {
        MVFR0 mvfr0 { FPU->MVFR0 };
        return mvfr0.bits.DOUBLE_PRECISION != 0;
    }

    //! Check if fused multiply-accumulate is supported.
    [[gnu::always_inline]] static inline bool isFusedMacSupported()
    {
        MVFR1 mvfr1 { FPU->MVFR1 };
        return mvfr1.bits.FP_FUSED_MAC != 0;
    }
}
