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

namespace CortexM3 {
    enum class Exception : uint8_t {
        RESET = 1, //!< reset
        NMI = 2, //!< non-maskable interrupt
        HARD_FAULT = 3, //!< hard fault
        MEM_MANAGE = 4, //!< memory management fault
        BUS_FAULT = 5, //!< bus fault
        USAGE_FAULT = 6, //!< usage fault
        RESERVED_7 = 7, //!< reserved
        RESERVED_8 = 8, //!< reserved
        RESERVED_9 = 9, //!< reserved
        RESERVED_10 = 10, //!< reserved
        SV_CALL = 11, //!< supervisor call
        DEBUG_MONITOR = 12, //!< debug monitor
        RESERVED_13 = 13, //!< reserved
        PEND_SV = 14, //!< pendable request for system service
        SYS_TICK = 15, //!< system tick timer
        IRQ_0 = 16, //!< external interrupt 0
        IRQ_1 = 17, //!< external interrupt 1
        // ... up to IRQ_239 (255 total)
    };
}
