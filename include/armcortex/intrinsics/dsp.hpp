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

//! \file dsp.hpp
//! \brief ARMv7E-M DSP extension intrinsics.
//! \note Available on Cortex-M4, Cortex-M7, Cortex-M33, etc. only.
//!       NOT available on Cortex-M0, M0+, M1, or M3.

namespace ArmCortex {

    // =========================================================================
    // Saturating 32-bit Arithmetic
    // =========================================================================

    //! Saturating Add.
    //! Returns the 32-bit saturating signed addition of a and b.
    //! Sets Q flag if saturation occurs.
    [[gnu::always_inline]] static inline int32_t asmQadd(int32_t a, int32_t b)
    {
        int32_t result;
        asm volatile("qadd %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    //! Saturating Subtract.
    //! Returns the 32-bit saturating signed subtraction of a - b.
    //! Sets Q flag if saturation occurs.
    [[gnu::always_inline]] static inline int32_t asmQsub(int32_t a, int32_t b)
    {
        int32_t result;
        asm volatile("qsub %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    //! Saturating Double and Add.
    //! Returns the 32-bit saturating signed addition of a and (b * 2).
    //! Sets Q flag if saturation occurs in either the doubling or addition.
    [[gnu::always_inline]] static inline int32_t asmQdadd(int32_t a, int32_t b)
    {
        int32_t result;
        asm volatile("qdadd %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    //! Saturating Double and Subtract.
    //! Returns the 32-bit saturating signed subtraction of a - (b * 2).
    //! Sets Q flag if saturation occurs in either the doubling or subtraction.
    [[gnu::always_inline]] static inline int32_t asmQdsub(int32_t a, int32_t b)
    {
        int32_t result;
        asm volatile("qdsub %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    // =========================================================================
    // Parallel Signed SIMD Arithmetic (Sets GE Flags)
    // =========================================================================

    //! Signed Add 8-bit (4 lanes).
    //! Adds four pairs of signed bytes. Sets GE flags for each byte lane.
    [[gnu::always_inline]] static inline uint32_t asmSadd8(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("sadd8 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    //! Signed Add 16-bit (2 lanes).
    //! Adds two pairs of signed halfwords. Sets GE flags for each halfword lane.
    [[gnu::always_inline]] static inline uint32_t asmSadd16(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("sadd16 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    //! Signed Subtract 8-bit (4 lanes).
    //! Subtracts four pairs of signed bytes. Sets GE flags for each byte lane.
    [[gnu::always_inline]] static inline uint32_t asmSsub8(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("ssub8 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    //! Signed Subtract 16-bit (2 lanes).
    //! Subtracts two pairs of signed halfwords. Sets GE flags for each halfword lane.
    [[gnu::always_inline]] static inline uint32_t asmSsub16(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("ssub16 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    //! Signed Add and Subtract with Exchange.
    //! Exchanges halfwords of b, then adds top halfwords and subtracts bottom halfwords.
    //! Sets GE flags.
    [[gnu::always_inline]] static inline uint32_t asmSasx(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("sasx %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    //! Signed Subtract and Add with Exchange.
    //! Exchanges halfwords of b, then subtracts top halfwords and adds bottom halfwords.
    //! Sets GE flags.
    [[gnu::always_inline]] static inline uint32_t asmSsax(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("ssax %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    // =========================================================================
    // Parallel Unsigned SIMD Arithmetic (Sets GE Flags)
    // =========================================================================

    //! Unsigned Add 8-bit (4 lanes).
    //! Adds four pairs of unsigned bytes. Sets GE flags for each byte lane.
    [[gnu::always_inline]] static inline uint32_t asmUadd8(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("uadd8 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    //! Unsigned Add 16-bit (2 lanes).
    //! Adds two pairs of unsigned halfwords. Sets GE flags for each halfword lane.
    [[gnu::always_inline]] static inline uint32_t asmUadd16(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("uadd16 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    //! Unsigned Subtract 8-bit (4 lanes).
    //! Subtracts four pairs of unsigned bytes. Sets GE flags for each byte lane.
    [[gnu::always_inline]] static inline uint32_t asmUsub8(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("usub8 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    //! Unsigned Subtract 16-bit (2 lanes).
    //! Subtracts two pairs of unsigned halfwords. Sets GE flags for each halfword lane.
    [[gnu::always_inline]] static inline uint32_t asmUsub16(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("usub16 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    //! Unsigned Add and Subtract with Exchange.
    //! Exchanges halfwords of b, then adds top halfwords and subtracts bottom halfwords.
    //! Sets GE flags.
    [[gnu::always_inline]] static inline uint32_t asmUasx(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("uasx %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    //! Unsigned Subtract and Add with Exchange.
    //! Exchanges halfwords of b, then subtracts top halfwords and adds bottom halfwords.
    //! Sets GE flags.
    [[gnu::always_inline]] static inline uint32_t asmUsax(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("usax %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    // =========================================================================
    // Saturating Signed SIMD Arithmetic
    // =========================================================================

    //! Saturating Signed Add 8-bit (4 lanes).
    //! Adds four pairs of signed bytes with saturation.
    [[gnu::always_inline]] static inline uint32_t asmQadd8(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("qadd8 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Saturating Signed Add 16-bit (2 lanes).
    //! Adds two pairs of signed halfwords with saturation.
    [[gnu::always_inline]] static inline uint32_t asmQadd16(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("qadd16 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Saturating Signed Subtract 8-bit (4 lanes).
    //! Subtracts four pairs of signed bytes with saturation.
    [[gnu::always_inline]] static inline uint32_t asmQsub8(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("qsub8 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Saturating Signed Subtract 16-bit (2 lanes).
    //! Subtracts two pairs of signed halfwords with saturation.
    [[gnu::always_inline]] static inline uint32_t asmQsub16(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("qsub16 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Saturating Signed Add and Subtract with Exchange.
    //! Exchanges halfwords of b, then adds/subtracts with saturation.
    [[gnu::always_inline]] static inline uint32_t asmQasx(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("qasx %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Saturating Signed Subtract and Add with Exchange.
    //! Exchanges halfwords of b, then subtracts/adds with saturation.
    [[gnu::always_inline]] static inline uint32_t asmQsax(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("qsax %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    // =========================================================================
    // Saturating Unsigned SIMD Arithmetic
    // =========================================================================

    //! Saturating Unsigned Add 8-bit (4 lanes).
    //! Adds four pairs of unsigned bytes with saturation.
    [[gnu::always_inline]] static inline uint32_t asmUqadd8(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("uqadd8 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Saturating Unsigned Add 16-bit (2 lanes).
    //! Adds two pairs of unsigned halfwords with saturation.
    [[gnu::always_inline]] static inline uint32_t asmUqadd16(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("uqadd16 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Saturating Unsigned Subtract 8-bit (4 lanes).
    //! Subtracts four pairs of unsigned bytes with saturation.
    [[gnu::always_inline]] static inline uint32_t asmUqsub8(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("uqsub8 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Saturating Unsigned Subtract 16-bit (2 lanes).
    //! Subtracts two pairs of unsigned halfwords with saturation.
    [[gnu::always_inline]] static inline uint32_t asmUqsub16(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("uqsub16 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Saturating Unsigned Add and Subtract with Exchange.
    //! Exchanges halfwords of b, then adds/subtracts with unsigned saturation.
    [[gnu::always_inline]] static inline uint32_t asmUqasx(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("uqasx %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Saturating Unsigned Subtract and Add with Exchange.
    //! Exchanges halfwords of b, then subtracts/adds with unsigned saturation.
    [[gnu::always_inline]] static inline uint32_t asmUqsax(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("uqsax %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    // =========================================================================
    // Parallel 16-bit Saturation Instructions
    // =========================================================================

    //! Signed Saturate 16-bit (2 lanes).
    //! Saturates two signed 16-bit values to a signed range of -2^(sat-1) to 2^(sat-1)-1.
    //! Sets Q flag if saturation occurs.
    //! \tparam sat Saturation bit position (1-16).
    template<uint8_t sat>
    [[gnu::always_inline]] static inline uint32_t asmSsat16(uint32_t a)
    {
        static_assert(sat >= 1 && sat <= 16, "SSAT16 saturation must be 1-16");
        uint32_t result;
        asm volatile("ssat16 %0, %1, %2" : "=r" (result) : "I" (sat), "r" (a) : "cc");
        return result;
    }

    //! Unsigned Saturate 16-bit (2 lanes).
    //! Saturates two signed 16-bit values to an unsigned range of 0 to 2^sat-1.
    //! Sets Q flag if saturation occurs.
    //! \tparam sat Saturation bit position (0-15).
    template<uint8_t sat>
    [[gnu::always_inline]] static inline uint32_t asmUsat16(uint32_t a)
    {
        static_assert(sat <= 15, "USAT16 saturation must be 0-15");
        uint32_t result;
        asm volatile("usat16 %0, %1, %2" : "=r" (result) : "I" (sat), "r" (a) : "cc");
        return result;
    }

    // =========================================================================
    // Halving Signed SIMD Arithmetic
    // =========================================================================

    //! Signed Halving Add 8-bit (4 lanes).
    //! Adds four pairs of signed bytes and halves the results.
    [[gnu::always_inline]] static inline uint32_t asmShadd8(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("shadd8 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Signed Halving Add 16-bit (2 lanes).
    //! Adds two pairs of signed halfwords and halves the results.
    [[gnu::always_inline]] static inline uint32_t asmShadd16(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("shadd16 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Signed Halving Subtract 8-bit (4 lanes).
    //! Subtracts four pairs of signed bytes and halves the results.
    [[gnu::always_inline]] static inline uint32_t asmShsub8(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("shsub8 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Signed Halving Subtract 16-bit (2 lanes).
    //! Subtracts two pairs of signed halfwords and halves the results.
    [[gnu::always_inline]] static inline uint32_t asmShsub16(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("shsub16 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Signed Halving Add and Subtract with Exchange.
    //! Exchanges halfwords of b, then adds/subtracts and halves.
    [[gnu::always_inline]] static inline uint32_t asmShasx(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("shasx %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Signed Halving Subtract and Add with Exchange.
    //! Exchanges halfwords of b, then subtracts/adds and halves.
    [[gnu::always_inline]] static inline uint32_t asmShsax(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("shsax %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    // =========================================================================
    // Halving Unsigned SIMD Arithmetic
    // =========================================================================

    //! Unsigned Halving Add 8-bit (4 lanes).
    //! Adds four pairs of unsigned bytes and halves the results.
    [[gnu::always_inline]] static inline uint32_t asmUhadd8(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("uhadd8 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Unsigned Halving Add 16-bit (2 lanes).
    //! Adds two pairs of unsigned halfwords and halves the results.
    [[gnu::always_inline]] static inline uint32_t asmUhadd16(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("uhadd16 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Unsigned Halving Subtract 8-bit (4 lanes).
    //! Subtracts four pairs of unsigned bytes and halves the results.
    [[gnu::always_inline]] static inline uint32_t asmUhsub8(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("uhsub8 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Unsigned Halving Subtract 16-bit (2 lanes).
    //! Subtracts two pairs of unsigned halfwords and halves the results.
    [[gnu::always_inline]] static inline uint32_t asmUhsub16(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("uhsub16 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Unsigned Halving Add and Subtract with Exchange.
    //! Exchanges halfwords of b, then adds/subtracts and halves.
    [[gnu::always_inline]] static inline uint32_t asmUhasx(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("uhasx %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Unsigned Halving Subtract and Add with Exchange.
    //! Exchanges halfwords of b, then subtracts/adds and halves.
    [[gnu::always_inline]] static inline uint32_t asmUhsax(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("uhsax %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    // =========================================================================
    // Byte Selection
    // =========================================================================

    //! Select bytes based on GE flags.
    //! For each byte lane, selects from a if GE flag is set, else from b.
    [[gnu::always_inline]] static inline uint32_t asmSel(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("sel %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    // =========================================================================
    // Sum of Absolute Differences
    // =========================================================================

    //! Unsigned Sum of Absolute Differences.
    //! Computes sum of absolute differences of four unsigned byte pairs.
    [[gnu::always_inline]] static inline uint32_t asmUsad8(uint32_t a, uint32_t b)
    {
        uint32_t result;
        asm volatile("usad8 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Unsigned Sum of Absolute Differences with Accumulate.
    //! Computes sum of absolute differences and adds to accumulator.
    [[gnu::always_inline]] static inline uint32_t asmUsada8(uint32_t a, uint32_t b, uint32_t acc)
    {
        uint32_t result;
        asm volatile("usada8 %0, %1, %2, %3" : "=r" (result) : "r" (a), "r" (b), "r" (acc));
        return result;
    }

    // =========================================================================
    // Packing Instructions
    // =========================================================================

    //! Pack Halfword Bottom Top.
    //! Combines bottom halfword of a with optionally shifted top halfword of b.
    //! \tparam shift Left shift amount for b (0-31).
    template<uint8_t shift = 0>
    [[gnu::always_inline]] static inline uint32_t asmPkhbt(uint32_t a, uint32_t b)
    {
        uint32_t result;
        if constexpr (shift == 0) {
            asm volatile("pkhbt %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        } else {
            asm volatile("pkhbt %0, %1, %2, lsl %3" : "=r" (result) : "r" (a), "r" (b), "I" (shift));
        }
        return result;
    }

    //! Pack Halfword Top Bottom.
    //! Combines top halfword of a with optionally shifted bottom halfword of b.
    //! \tparam shift Arithmetic right shift amount for b (1-32, 0 means 32).
    template<uint8_t shift = 0>
    [[gnu::always_inline]] static inline uint32_t asmPkhtb(uint32_t a, uint32_t b)
    {
        uint32_t result;
        if constexpr (shift == 0) {
            asm volatile("pkhtb %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        } else {
            asm volatile("pkhtb %0, %1, %2, asr %3" : "=r" (result) : "r" (a), "r" (b), "I" (shift));
        }
        return result;
    }

    // =========================================================================
    // Byte Extend Instructions (No Add)
    // =========================================================================

    //! Sign Extend Two Bytes to Two Halfwords.
    //! Sign-extends bytes [7:0] and [23:16] to halfwords [15:0] and [31:16].
    //! \tparam rotation Rotation amount: 0, 8, 16, or 24.
    template<uint8_t rotation = 0>
    [[gnu::always_inline]] static inline uint32_t asmSxtb16(uint32_t a)
    {
        uint32_t result;
        if constexpr (rotation == 0) {
            asm volatile("sxtb16 %0, %1" : "=r" (result) : "r" (a));
        } else {
            asm volatile("sxtb16 %0, %1, ror %2" : "=r" (result) : "r" (a), "I" (rotation));
        }
        return result;
    }

    //! Zero Extend Two Bytes to Two Halfwords.
    //! Zero-extends bytes [7:0] and [23:16] to halfwords [15:0] and [31:16].
    //! \tparam rotation Rotation amount: 0, 8, 16, or 24.
    template<uint8_t rotation = 0>
    [[gnu::always_inline]] static inline uint32_t asmUxtb16(uint32_t a)
    {
        uint32_t result;
        if constexpr (rotation == 0) {
            asm volatile("uxtb16 %0, %1" : "=r" (result) : "r" (a));
        } else {
            asm volatile("uxtb16 %0, %1, ror %2" : "=r" (result) : "r" (a), "I" (rotation));
        }
        return result;
    }

    // =========================================================================
    // Signed Extend and Add Instructions
    // =========================================================================

    //! Signed Extend and Add Byte.
    //! Sign-extends a byte from b (with optional rotation) and adds to a.
    //! \tparam rotation Rotation amount: 0, 8, 16, or 24.
    template<uint8_t rotation = 0>
    [[gnu::always_inline]] static inline int32_t asmSxtab(int32_t a, uint32_t b)
    {
        int32_t result;
        if constexpr (rotation == 0) {
            asm volatile("sxtab %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        } else {
            asm volatile("sxtab %0, %1, %2, ror %3" : "=r" (result) : "r" (a), "r" (b), "I" (rotation));
        }
        return result;
    }

    //! Signed Extend and Add Two Bytes.
    //! Sign-extends two bytes from b (with optional rotation) and adds to halfwords in a.
    //! \tparam rotation Rotation amount: 0, 8, 16, or 24.
    template<uint8_t rotation = 0>
    [[gnu::always_inline]] static inline uint32_t asmSxtab16(uint32_t a, uint32_t b)
    {
        uint32_t result;
        if constexpr (rotation == 0) {
            asm volatile("sxtab16 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        } else {
            asm volatile("sxtab16 %0, %1, %2, ror %3" : "=r" (result) : "r" (a), "r" (b), "I" (rotation));
        }
        return result;
    }

    //! Signed Extend and Add Halfword.
    //! Sign-extends a halfword from b (with optional rotation) and adds to a.
    //! \tparam rotation Rotation amount: 0, 8, 16, or 24.
    template<uint8_t rotation = 0>
    [[gnu::always_inline]] static inline int32_t asmSxtah(int32_t a, uint32_t b)
    {
        int32_t result;
        if constexpr (rotation == 0) {
            asm volatile("sxtah %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        } else {
            asm volatile("sxtah %0, %1, %2, ror %3" : "=r" (result) : "r" (a), "r" (b), "I" (rotation));
        }
        return result;
    }

    // =========================================================================
    // Unsigned Extend and Add Instructions
    // =========================================================================

    //! Unsigned Extend and Add Byte.
    //! Zero-extends a byte from b (with optional rotation) and adds to a.
    //! \tparam rotation Rotation amount: 0, 8, 16, or 24.
    template<uint8_t rotation = 0>
    [[gnu::always_inline]] static inline uint32_t asmUxtab(uint32_t a, uint32_t b)
    {
        uint32_t result;
        if constexpr (rotation == 0) {
            asm volatile("uxtab %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        } else {
            asm volatile("uxtab %0, %1, %2, ror %3" : "=r" (result) : "r" (a), "r" (b), "I" (rotation));
        }
        return result;
    }

    //! Unsigned Extend and Add Two Bytes.
    //! Zero-extends two bytes from b (with optional rotation) and adds to halfwords in a.
    //! \tparam rotation Rotation amount: 0, 8, 16, or 24.
    template<uint8_t rotation = 0>
    [[gnu::always_inline]] static inline uint32_t asmUxtab16(uint32_t a, uint32_t b)
    {
        uint32_t result;
        if constexpr (rotation == 0) {
            asm volatile("uxtab16 %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        } else {
            asm volatile("uxtab16 %0, %1, %2, ror %3" : "=r" (result) : "r" (a), "r" (b), "I" (rotation));
        }
        return result;
    }

    //! Unsigned Extend and Add Halfword.
    //! Zero-extends a halfword from b (with optional rotation) and adds to a.
    //! \tparam rotation Rotation amount: 0, 8, 16, or 24.
    template<uint8_t rotation = 0>
    [[gnu::always_inline]] static inline uint32_t asmUxtah(uint32_t a, uint32_t b)
    {
        uint32_t result;
        if constexpr (rotation == 0) {
            asm volatile("uxtah %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        } else {
            asm volatile("uxtah %0, %1, %2, ror %3" : "=r" (result) : "r" (a), "r" (b), "I" (rotation));
        }
        return result;
    }

    // =========================================================================
    // Signed Halfword Multiply Instructions (16×16 → 32)
    // =========================================================================

    //! Signed Multiply Bottom Bottom.
    //! Multiplies bottom halfwords of a and b.
    [[gnu::always_inline]] static inline int32_t asmSmulbb(uint32_t a, uint32_t b)
    {
        int32_t result;
        asm volatile("smulbb %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Signed Multiply Bottom Top.
    //! Multiplies bottom halfword of a with top halfword of b.
    [[gnu::always_inline]] static inline int32_t asmSmulbt(uint32_t a, uint32_t b)
    {
        int32_t result;
        asm volatile("smulbt %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Signed Multiply Top Bottom.
    //! Multiplies top halfword of a with bottom halfword of b.
    [[gnu::always_inline]] static inline int32_t asmSmultb(uint32_t a, uint32_t b)
    {
        int32_t result;
        asm volatile("smultb %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Signed Multiply Top Top.
    //! Multiplies top halfwords of a and b.
    [[gnu::always_inline]] static inline int32_t asmSmultt(uint32_t a, uint32_t b)
    {
        int32_t result;
        asm volatile("smultt %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    // =========================================================================
    // Signed Halfword Multiply Word Instructions (32×16 → 32, top 32 bits)
    // =========================================================================

    //! Signed Multiply Word Bottom.
    //! Multiplies 32-bit a with bottom halfword of b, returns top 32 bits.
    [[gnu::always_inline]] static inline int32_t asmSmulwb(int32_t a, uint32_t b)
    {
        int32_t result;
        asm volatile("smulwb %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Signed Multiply Word Top.
    //! Multiplies 32-bit a with top halfword of b, returns top 32 bits.
    [[gnu::always_inline]] static inline int32_t asmSmulwt(int32_t a, uint32_t b)
    {
        int32_t result;
        asm volatile("smulwt %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    // =========================================================================
    // Signed Halfword Multiply Accumulate Instructions (16×16 + 32 → 32)
    // =========================================================================

    //! Signed Multiply Accumulate Bottom Bottom.
    //! Multiplies bottom halfwords and adds to accumulator.
    //! Sets Q flag on overflow.
    [[gnu::always_inline]] static inline int32_t asmSmlabb(uint32_t a, uint32_t b, int32_t acc)
    {
        int32_t result;
        asm volatile("smlabb %0, %1, %2, %3" : "=r" (result) : "r" (a), "r" (b), "r" (acc) : "cc");
        return result;
    }

    //! Signed Multiply Accumulate Bottom Top.
    //! Multiplies bottom halfword of a with top halfword of b and adds to accumulator.
    //! Sets Q flag on overflow.
    [[gnu::always_inline]] static inline int32_t asmSmlabt(uint32_t a, uint32_t b, int32_t acc)
    {
        int32_t result;
        asm volatile("smlabt %0, %1, %2, %3" : "=r" (result) : "r" (a), "r" (b), "r" (acc) : "cc");
        return result;
    }

    //! Signed Multiply Accumulate Top Bottom.
    //! Multiplies top halfword of a with bottom halfword of b and adds to accumulator.
    //! Sets Q flag on overflow.
    [[gnu::always_inline]] static inline int32_t asmSmlatb(uint32_t a, uint32_t b, int32_t acc)
    {
        int32_t result;
        asm volatile("smlatb %0, %1, %2, %3" : "=r" (result) : "r" (a), "r" (b), "r" (acc) : "cc");
        return result;
    }

    //! Signed Multiply Accumulate Top Top.
    //! Multiplies top halfwords and adds to accumulator.
    //! Sets Q flag on overflow.
    [[gnu::always_inline]] static inline int32_t asmSmlatt(uint32_t a, uint32_t b, int32_t acc)
    {
        int32_t result;
        asm volatile("smlatt %0, %1, %2, %3" : "=r" (result) : "r" (a), "r" (b), "r" (acc) : "cc");
        return result;
    }

    // =========================================================================
    // Signed Halfword Multiply Accumulate Word Instructions (32×16 + 32 → 32)
    // =========================================================================

    //! Signed Multiply Accumulate Word Bottom.
    //! Multiplies 32-bit a with bottom halfword of b (top 32 bits) and adds to accumulator.
    //! Sets Q flag on overflow.
    [[gnu::always_inline]] static inline int32_t asmSmlawb(int32_t a, uint32_t b, int32_t acc)
    {
        int32_t result;
        asm volatile("smlawb %0, %1, %2, %3" : "=r" (result) : "r" (a), "r" (b), "r" (acc) : "cc");
        return result;
    }

    //! Signed Multiply Accumulate Word Top.
    //! Multiplies 32-bit a with top halfword of b (top 32 bits) and adds to accumulator.
    //! Sets Q flag on overflow.
    [[gnu::always_inline]] static inline int32_t asmSmlawt(int32_t a, uint32_t b, int32_t acc)
    {
        int32_t result;
        asm volatile("smlawt %0, %1, %2, %3" : "=r" (result) : "r" (a), "r" (b), "r" (acc) : "cc");
        return result;
    }

    // =========================================================================
    // Signed Halfword Multiply Accumulate Long Instructions (16×16 + 64 → 64)
    // =========================================================================

    //! Signed Multiply Accumulate Long Bottom Bottom.
    //! Multiplies bottom halfwords and adds to 64-bit accumulator.
    [[gnu::always_inline]] static inline int64_t asmSmlalbb(uint32_t a, uint32_t b, int64_t acc)
    {
        union {
            struct { uint32_t lo; uint32_t hi; } parts;
            int64_t value;
        } result;
        result.value = acc;
        asm volatile("smlalbb %0, %1, %2, %3"
            : "+r" (result.parts.lo), "+r" (result.parts.hi)
            : "r" (a), "r" (b));
        return result.value;
    }

    //! Signed Multiply Accumulate Long Bottom Top.
    //! Multiplies bottom halfword of a with top halfword of b and adds to 64-bit accumulator.
    [[gnu::always_inline]] static inline int64_t asmSmlalbt(uint32_t a, uint32_t b, int64_t acc)
    {
        union {
            struct { uint32_t lo; uint32_t hi; } parts;
            int64_t value;
        } result;
        result.value = acc;
        asm volatile("smlalbt %0, %1, %2, %3"
            : "+r" (result.parts.lo), "+r" (result.parts.hi)
            : "r" (a), "r" (b));
        return result.value;
    }

    //! Signed Multiply Accumulate Long Top Bottom.
    //! Multiplies top halfword of a with bottom halfword of b and adds to 64-bit accumulator.
    [[gnu::always_inline]] static inline int64_t asmSmlaltb(uint32_t a, uint32_t b, int64_t acc)
    {
        union {
            struct { uint32_t lo; uint32_t hi; } parts;
            int64_t value;
        } result;
        result.value = acc;
        asm volatile("smlaltb %0, %1, %2, %3"
            : "+r" (result.parts.lo), "+r" (result.parts.hi)
            : "r" (a), "r" (b));
        return result.value;
    }

    //! Signed Multiply Accumulate Long Top Top.
    //! Multiplies top halfwords and adds to 64-bit accumulator.
    [[gnu::always_inline]] static inline int64_t asmSmlaltt(uint32_t a, uint32_t b, int64_t acc)
    {
        union {
            struct { uint32_t lo; uint32_t hi; } parts;
            int64_t value;
        } result;
        result.value = acc;
        asm volatile("smlaltt %0, %1, %2, %3"
            : "+r" (result.parts.lo), "+r" (result.parts.hi)
            : "r" (a), "r" (b));
        return result.value;
    }

    // =========================================================================
    // Dual 16-bit Multiply Instructions
    // =========================================================================

    //! Signed Dual Multiply Add.
    //! Multiplies top halfwords together, multiplies bottom halfwords together, adds results.
    //! Sets Q flag on overflow.
    [[gnu::always_inline]] static inline int32_t asmSmuad(uint32_t a, uint32_t b)
    {
        int32_t result;
        asm volatile("smuad %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    //! Signed Dual Multiply Add Exchanged.
    //! Exchanges halfwords of b before multiply-add operation.
    //! Sets Q flag on overflow.
    [[gnu::always_inline]] static inline int32_t asmSmuadx(uint32_t a, uint32_t b)
    {
        int32_t result;
        asm volatile("smuadx %0, %1, %2" : "=r" (result) : "r" (a), "r" (b) : "cc");
        return result;
    }

    //! Signed Dual Multiply Subtract.
    //! Multiplies halfwords, subtracts products (top - bottom).
    [[gnu::always_inline]] static inline int32_t asmSmusd(uint32_t a, uint32_t b)
    {
        int32_t result;
        asm volatile("smusd %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Signed Dual Multiply Subtract Exchanged.
    //! Exchanges halfwords of b before multiply-subtract operation.
    [[gnu::always_inline]] static inline int32_t asmSmusdx(uint32_t a, uint32_t b)
    {
        int32_t result;
        asm volatile("smusdx %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    // =========================================================================
    // Dual 16-bit Multiply Accumulate Instructions
    // =========================================================================

    //! Signed Dual Multiply Add with Accumulate.
    //! Performs dual multiply-add and accumulates to 32-bit value.
    //! Sets Q flag on overflow.
    [[gnu::always_inline]] static inline int32_t asmSmlad(uint32_t a, uint32_t b, int32_t acc)
    {
        int32_t result;
        asm volatile("smlad %0, %1, %2, %3" : "=r" (result) : "r" (a), "r" (b), "r" (acc) : "cc");
        return result;
    }

    //! Signed Dual Multiply Add Exchanged with Accumulate.
    //! Exchanges halfwords of b before operation.
    //! Sets Q flag on overflow.
    [[gnu::always_inline]] static inline int32_t asmSmladx(uint32_t a, uint32_t b, int32_t acc)
    {
        int32_t result;
        asm volatile("smladx %0, %1, %2, %3" : "=r" (result) : "r" (a), "r" (b), "r" (acc) : "cc");
        return result;
    }

    //! Signed Dual Multiply Subtract with Accumulate.
    //! Performs dual multiply-subtract and accumulates to 32-bit value.
    [[gnu::always_inline]] static inline int32_t asmSmlsd(uint32_t a, uint32_t b, int32_t acc)
    {
        int32_t result;
        asm volatile("smlsd %0, %1, %2, %3" : "=r" (result) : "r" (a), "r" (b), "r" (acc));
        return result;
    }

    //! Signed Dual Multiply Subtract Exchanged with Accumulate.
    //! Exchanges halfwords of b before operation.
    [[gnu::always_inline]] static inline int32_t asmSmlsdx(uint32_t a, uint32_t b, int32_t acc)
    {
        int32_t result;
        asm volatile("smlsdx %0, %1, %2, %3" : "=r" (result) : "r" (a), "r" (b), "r" (acc));
        return result;
    }

    // =========================================================================
    // Dual 16-bit Multiply Accumulate Long Instructions (64-bit accumulator)
    // =========================================================================

    //! Signed Dual Multiply Add Long.
    //! Performs dual multiply-add and accumulates to 64-bit value.
    [[gnu::always_inline]] static inline int64_t asmSmlald(uint32_t a, uint32_t b, int64_t acc)
    {
        union {
            struct { uint32_t lo; uint32_t hi; } parts;
            int64_t value;
        } result;
        result.value = acc;
        asm volatile("smlald %0, %1, %2, %3"
            : "+r" (result.parts.lo), "+r" (result.parts.hi)
            : "r" (a), "r" (b));
        return result.value;
    }

    //! Signed Dual Multiply Add Long Exchanged.
    //! Exchanges halfwords of b before operation.
    [[gnu::always_inline]] static inline int64_t asmSmlaldx(uint32_t a, uint32_t b, int64_t acc)
    {
        union {
            struct { uint32_t lo; uint32_t hi; } parts;
            int64_t value;
        } result;
        result.value = acc;
        asm volatile("smlaldx %0, %1, %2, %3"
            : "+r" (result.parts.lo), "+r" (result.parts.hi)
            : "r" (a), "r" (b));
        return result.value;
    }

    //! Signed Dual Multiply Subtract Long.
    //! Performs dual multiply-subtract and accumulates to 64-bit value.
    [[gnu::always_inline]] static inline int64_t asmSmlsld(uint32_t a, uint32_t b, int64_t acc)
    {
        union {
            struct { uint32_t lo; uint32_t hi; } parts;
            int64_t value;
        } result;
        result.value = acc;
        asm volatile("smlsld %0, %1, %2, %3"
            : "+r" (result.parts.lo), "+r" (result.parts.hi)
            : "r" (a), "r" (b));
        return result.value;
    }

    //! Signed Dual Multiply Subtract Long Exchanged.
    //! Exchanges halfwords of b before operation.
    [[gnu::always_inline]] static inline int64_t asmSmlsldx(uint32_t a, uint32_t b, int64_t acc)
    {
        union {
            struct { uint32_t lo; uint32_t hi; } parts;
            int64_t value;
        } result;
        result.value = acc;
        asm volatile("smlsldx %0, %1, %2, %3"
            : "+r" (result.parts.lo), "+r" (result.parts.hi)
            : "r" (a), "r" (b));
        return result.value;
    }

    // =========================================================================
    // Signed Most Significant Word Multiply Instructions
    // =========================================================================

    //! Signed Most Significant Word Multiply.
    //! Returns the most significant 32 bits of the 64-bit signed multiplication.
    [[gnu::always_inline]] static inline int32_t asmSmmul(int32_t a, int32_t b)
    {
        int32_t result;
        asm volatile("smmul %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Signed Most Significant Word Multiply Rounded.
    //! Returns the most significant 32 bits with rounding.
    [[gnu::always_inline]] static inline int32_t asmSmmulr(int32_t a, int32_t b)
    {
        int32_t result;
        asm volatile("smmulr %0, %1, %2" : "=r" (result) : "r" (a), "r" (b));
        return result;
    }

    //! Signed Most Significant Word Multiply Accumulate.
    //! Multiplies and adds to accumulator, returns most significant 32 bits.
    [[gnu::always_inline]] static inline int32_t asmSmmla(int32_t a, int32_t b, int32_t acc)
    {
        int32_t result;
        asm volatile("smmla %0, %1, %2, %3" : "=r" (result) : "r" (a), "r" (b), "r" (acc));
        return result;
    }

    //! Signed Most Significant Word Multiply Accumulate Rounded.
    //! Multiplies and adds to accumulator with rounding.
    [[gnu::always_inline]] static inline int32_t asmSmmlar(int32_t a, int32_t b, int32_t acc)
    {
        int32_t result;
        asm volatile("smmlar %0, %1, %2, %3" : "=r" (result) : "r" (a), "r" (b), "r" (acc));
        return result;
    }

    //! Signed Most Significant Word Multiply Subtract.
    //! Subtracts product from accumulator, returns most significant 32 bits.
    [[gnu::always_inline]] static inline int32_t asmSmmls(int32_t a, int32_t b, int32_t acc)
    {
        int32_t result;
        asm volatile("smmls %0, %1, %2, %3" : "=r" (result) : "r" (a), "r" (b), "r" (acc));
        return result;
    }

    //! Signed Most Significant Word Multiply Subtract Rounded.
    //! Subtracts product from accumulator with rounding.
    [[gnu::always_inline]] static inline int32_t asmSmmlsr(int32_t a, int32_t b, int32_t acc)
    {
        int32_t result;
        asm volatile("smmlsr %0, %1, %2, %3" : "=r" (result) : "r" (a), "r" (b), "r" (acc));
        return result;
    }

}
