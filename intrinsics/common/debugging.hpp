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
    //! Breakpoint.
    //! Causes the processor to enter Debug state if a debugger is attached.
    //! \tparam value 8-bit immediate value (0-255) for debugger identification.
    template<uint8_t value>
    [[gnu::always_inline]] static inline void asmBkpt()
    {
        asm volatile("bkpt %0" : : "i" (static_cast<uint16_t>(value)));
    }
}
