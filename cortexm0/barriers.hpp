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

namespace CortexM0 {
    static inline void DataSyncBarrier()
    {
        asm volatile("dsb" : : : "memory");
    }

    static inline void InstrSyncBarrier()
    {
        asm volatile("isb" : : : "memory");
    }

    static inline void DataMemBarrier()
    {
        asm volatile("dmb" : : : "memory");
    }

    static inline void CompilerBarrier()
    {
        asm volatile( : : : "memory");
    }
}
