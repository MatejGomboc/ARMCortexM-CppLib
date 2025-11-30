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

namespace Cortex::Intrinsics::ARMv7M {
    //! Count Leading Zeros.
    //! Returns the number of consecutive zero bits starting from the MSB.
    //! \param value Input value.
    //! \return Number of leading zeros (0-32).
    [[gnu::always_inline]] static inline uint32_t clz(uint32_t value)
    {
        uint32_t result;
        asm volatile("clz %0, %1" : "=r" (result) : "r" (value));
        return result;
    }

    //! Reverse Bits.
    //! Reverses the bit order in a 32-bit word.
    //! \param value Input value.
    //! \return Value with all 32 bits reversed.
    [[gnu::always_inline]] static inline uint32_t rbit(uint32_t value)
    {
        uint32_t result;
        asm volatile("rbit %0, %1" : "=r" (result) : "r" (value));
        return result;
    }
}
