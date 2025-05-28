/*
    Copyright (C) 2025 Matej Gomboc <https://github.com/MatejGomboc/ARMCortexM-CppLib>

    Licensed under the Apache License, Version 2.0 (the "Licence");
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

namespace CortexM0 {
    //! Cortex-M0 exceptions
    enum class Exception : uint8_t {
        RESET = 1, //!< reset exception
        NMI = 2, //!< non-maskable interrupt
        HARD_FAULT = 3, //!< hard fault exception
        RESERVED_4 = 4,
        RESERVED_5 = 5,
        RESERVED_6 = 6,
        RESERVED_7 = 7,
        RESERVED_8 = 8,
        RESERVED_9 = 9,
        RESERVED_10 = 10,
        SV_CALL = 11, //!< supervisor call exception
        RESERVED_12 = 12,
        RESERVED_13 = 13,
        PEND_SV = 14, //!< pendable service exception
        SYS_TICK = 15 //!< system tick exception
    };
}
