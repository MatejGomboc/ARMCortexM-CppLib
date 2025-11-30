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

namespace ArmCortex::ScnScb {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000E000u;

    struct Registers
    {
        volatile uint32_t RESERVED0[2]; //!< Reserved.
        volatile uint32_t ACTLR; //!< Auxiliary control register.
    };

    //! Auxiliary control register.
    //! Controls Instruction Tightly-Coupled Memory (TCM) alias enable features.
    union ACTLR {
        struct Bits {
            uint32_t RESERVED0: 3;
            uint32_t ITCMLAEN: 1; //!< Instruction TCM Lower Alias Enable.
            uint32_t ITCMUAEN: 1; //!< Instruction TCM Upper Alias Enable.
            uint32_t RESERVED1: 27;
        } bits;

        uint32_t value = 0;

        ACTLR() = default;

        ACTLR(uint32_t new_value)
        {
            value = new_value;
        }
    };
}

namespace ArmCortex {
    inline volatile ScnScb::Registers* const SCN_SCB = reinterpret_cast<volatile ScnScb::Registers*>(ScnScb::BASE_ADDRESS);
}
