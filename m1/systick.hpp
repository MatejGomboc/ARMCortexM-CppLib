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

namespace Cortex::M1::SysTick {
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
        enum class CLKSOURCE : bool {
            EXTERNAL = false, //!< external reference clock
            CPU = true //!< processor clock
        };

        struct Bits {
            //! Enables the counter. When ENABLE is set to 1, the counter starts counting down. On reaching 0, it sets the COUNTFLAG to
            //! 1 and optionally asserts the SysTick depending on the value of TICKINT. It then loads the RELOAD value again, and begins
            //! counting.
            //! 0: Counter disabled.
            //! 1: Counter enabled.
            uint32_t ENABLE: 1;

            //! SysTick exception request enable.
            //! 0: Counting down to zero does not assert the SysTick exception request.
            //! 1: Counting down to zero to assert the SysTick exception request.
            uint32_t TICKINT: 1;

            //! Selects the timer clock source.
            //! 0: External reference clock.
            //! 1: Processor clock.
            uint32_t CLKSOURCE: 1;

            uint32_t RESERVED0: 13;

            //! Returns 1 if timer counted to 0 since last time this was read.
            uint32_t COUNTFLAG: 1;

            uint32_t RESERVED1: 15;
        } bits;

        uint32_t value = 0;

        CTRL() = default;

        CTRL(uint32_t new_value)
        {
            value = new_value;
        }
    };

    //! The CALIB register indicates the SysTick calibration properties. If calibration information is not known, calculate
    //! the calibration value required from the frequency of the processor clock or external clock.
    union CALIB {
        struct Bits {
            // Calibration value. Reads as zero. Indicates that calibration value is not known.
            uint32_t TENMS: 24;

            uint32_t RESERVED: 6;

            //! Reads as one. Calibration value for the 10ms inexact timing is not known because TENMS is not
            //! known. This can affect the suitability of SysTick as a software real time clock.
            uint32_t SKEW: 1;

            //! Reads as one. Indicates that no separate reference clock is provided.
            uint32_t NOREF: 1;
        } bits;

        uint32_t value = 0;

        CALIB() = default;

        CALIB(uint32_t new_value)
        {
            value = new_value;
        }
    };
}

namespace Cortex::M1 {
    inline volatile SysTick::Registers* const SYS_TICK = reinterpret_cast<volatile SysTick::Registers*>(SysTick::BASE_ADDRESS);
}
