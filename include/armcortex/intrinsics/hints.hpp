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

namespace ArmCortex {
    //! No Operation.
    //! Does nothing, can be used for instruction alignment or timing.
    [[gnu::always_inline]] static inline void asmNop()
    {
        asm volatile("nop");
    }

    //! Yield.
    //! Hint that the current thread should yield to other threads.
    //! On ArmCortex-M0/M0+/M1 this is a NOP, on M3+ it's a hint to the processor.
    [[gnu::always_inline]] static inline void asmYield()
    {
        asm volatile("yield");
    }
}
