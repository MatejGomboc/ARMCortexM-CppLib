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
    //! Data Synchronization Barrier.
    //! Ensures completion of all explicit memory accesses before continuing.
    [[gnu::always_inline]] static inline void asmDsb()
    {
        asm volatile("dsb" : : : "memory");
    }

    //! Instruction Synchronization Barrier.
    //! Flushes the pipeline and ensures all previous instructions are completed.
    [[gnu::always_inline]] static inline void asmIsb()
    {
        asm volatile("isb" : : : "memory");
    }

    //! Data Memory Barrier.
    //! Ensures ordering of memory accesses.
    [[gnu::always_inline]] static inline void asmDmb()
    {
        asm volatile("dmb" : : : "memory");
    }

    //! Compiler memory barrier.
    //! Prevents compiler reordering of memory accesses across this point.
    [[gnu::always_inline]] static inline void asmCompilerBarrier()
    {
        asm volatile("" : : : "memory");
    }
}
