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
    //! Reverse byte order in a 32-bit word.
    //! Converts between little-endian and big-endian.
    //! \param value Input value.
    //! \return Value with bytes reversed: [A,B,C,D] -> [D,C,B,A]
    [[gnu::always_inline]] static inline uint32_t asmRev(uint32_t value)
    {
        uint32_t result;
        asm volatile("rev %0, %1" : "=r" (result) : "r" (value));
        return result;
    }

    //! Reverse byte order in each halfword independently.
    //! \param value Input value.
    //! \return Value with bytes reversed in each halfword: [A,B,C,D] -> [B,A,D,C]
    [[gnu::always_inline]] static inline uint32_t asmRev16(uint32_t value)
    {
        uint32_t result;
        asm volatile("rev16 %0, %1" : "=r" (result) : "r" (value));
        return result;
    }

    //! Reverse byte order in the low halfword and sign-extend to 32 bits.
    //! \param value Input value.
    //! \return Sign-extended result of reversing the low halfword bytes.
    [[gnu::always_inline]] static inline int32_t asmRevsh(int32_t value)
    {
        int32_t result;
        asm volatile("revsh %0, %1" : "=r" (result) : "r" (value));
        return result;
    }
}
