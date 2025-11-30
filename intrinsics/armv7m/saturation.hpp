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

namespace Cortex {
    //! Signed Saturate.
    //! Saturates a signed value to a specified bit width.
    //! \tparam sat_bits Number of bits to saturate to (1-32).
    //! \param value Input value.
    //! \return Saturated value in range [-(2^(sat_bits-1)), 2^(sat_bits-1)-1].
    //! \note Available on ARMv7-M (Cortex-M3, M4, M7) only.
    template<uint8_t sat_bits>
    [[gnu::always_inline]] static inline int32_t asmSsat(int32_t value)
    {
        static_assert(sat_bits >= 1 && sat_bits <= 32, "sat_bits must be 1-32");
        int32_t result;
        asm volatile("ssat %0, %1, %2" : "=r" (result) : "I" (sat_bits), "r" (value));
        return result;
    }

    //! Unsigned Saturate.
    //! Saturates a signed value to an unsigned range.
    //! \tparam sat_bits Number of bits to saturate to (0-31).
    //! \param value Input value.
    //! \return Saturated value in range [0, 2^sat_bits-1].
    //! \note Available on ARMv7-M (Cortex-M3, M4, M7) only.
    template<uint8_t sat_bits>
    [[gnu::always_inline]] static inline uint32_t asmUsat(int32_t value)
    {
        static_assert(sat_bits >= 0 && sat_bits <= 31, "sat_bits must be 0-31");
        uint32_t result;
        asm volatile("usat %0, %1, %2" : "=r" (result) : "I" (sat_bits), "r" (value));
        return result;
    }
}
