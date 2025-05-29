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

namespace CortexM3::SysTick {
    static uint32_t* const BASE_ADDR = reinterpret_cast<uint32_t*>(0xE000E010);

    union Control {
        struct Bits {
            uint32_t enabled: 1; //!< enables the counter
            uint32_t exception_enabled: 1; //!< enables exception request
            uint32_t use_processor_clock: 1; //!< clock source (0 = external, 1 = processor clock)
            uint32_t reserved: 13;
            uint32_t count_flag: 1; //!< true if timer counted to 0 since last time this was read
            uint32_t reserved2: 15;
        } bits;

        uint32_t value = 0;

        Control() = default;

        Control(uint32_t new_value)
        {
            value = new_value;
        }
    };

    union Calibration {
        struct Bits {
            uint32_t ten_ms: 24; //!< calibration value
            uint32_t reserved: 6;
            uint32_t skew: 1; //!< true if calibration value is inexact
            uint32_t no_ref: 1; //!< true if reference clock is not provided
        } bits;

        uint32_t value = 0;

        Calibration() = default;

        Calibration(uint32_t new_value)
        {
            value = new_value;
        }
    };

    struct Registers {
        volatile uint32_t control; //!< SysTick control and status
        volatile uint32_t reload; //!< reload value
        volatile uint32_t current; //!< current value
        volatile uint32_t calibration; //!< calibration value
    };

    static inline volatile Registers* registers()
    {
        return reinterpret_cast<volatile Registers*>(BASE_ADDR);
    }

    static inline void setReloadValue(uint32_t reload_value)
    {
        registers()->reload = reload_value & 0x00FFFFFF;
    }

    static inline uint32_t getReloadValue()
    {
        return registers()->reload & 0x00FFFFFF;
    }

    static inline uint32_t getCurrentValue()
    {
        return registers()->current & 0x00FFFFFF;
    }

    static inline void clearCurrentValue()
    {
        registers()->current = 0;
    }

    static inline bool hasCountedToZero()
    {
        Control ctrl { registers()->control };
        return ctrl.bits.count_flag;
    }
}
