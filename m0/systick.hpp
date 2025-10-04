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

namespace CortexM0::SysTick {
    inline constexpr uintptr_t BASE_ADDRESS = 0xE000E010u;

    struct Registers
    {
        volatile uint32_t CTRL; //!< control and status register
        volatile uint32_t LOAD; //!< reload value at the restart of counting
        volatile uint32_t VAL; //!< current counter value
        volatile uint32_t CALIB; //!< controls timer calibration
    };

    union CTRL {
        //! timer clock source
        enum class ClkSource : bool {
            EXTERNAL = false, //!< external reference clock
            CPU = true //!< processor clock
        };

        struct Bits {
            uint32_t ENABLE: 1; //!< enables counting
            uint32_t TICKINT: 1; //!< enables SysTick exception
            uint32_t CLKSOURCE: 1; //!< selects the timer clock source
            uint32_t RESERVED0: 13;
            uint32_t COUNTFLAG: 1; //!< '1' if counter reached 0 since last time this bit was read
            uint32_t RESERVED1: 15;
        } bits;

        uint32_t value = 0;

        CTRL() = default;

        CTRL(uint32_t new_value)
        {
            value = new_value;
        }
    };

    union CALIB {
        struct Bits {
            /*!
                Indicates the calibration value when the SysTick counter runs on HCLK max/8 as external clock.
                When HCLK is programmed at the maximum frequency, the SysTick period is 1ms.
            */
            uint32_t TENMS: 24;
            uint32_t RESERVED: 6;
            uint32_t SKEW: 1; //!< always '1'
            uint32_t NOREF: 1; //!< always '0', indicates that a separate reference clock is provided (HCLK/8)
        } bits;

        uint32_t value = 0;

        CALIB() = default;

        CALIB(uint32_t new_value)
        {
            value = new_value;
        }
    };
}

namespace CortexM0 {
    inline volatile SysTick::Registers* const SYS_TICK = reinterpret_cast<volatile SysTick::Registers*>(SysTick::BASE_ADDRESS);
}
