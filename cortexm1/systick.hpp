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

namespace CortexM1::SysTick {
    static uint32_t* const BASE_ADDR = reinterpret_cast<uint32_t*>(0xE000E010);

    //! SysTick control and status register
    union CtrlStat {
        //! SysTick clock source
        enum class ClockSource : bool {
            EXTERNAL = false, //!< external reference clock
            PROCESSOR = true //!< processor clock
        };

        struct Bits {
            uint32_t enabled: 1; //!< enable the SysTick
            uint32_t irq_enabled: 1; //!< enable the SysTick interrupt
            uint32_t clock_source: 1; //!< SysTick clock source
            uint32_t reserved: 13;
            uint32_t count_flag: 1; //!< returns 1 if timer counted to 0 since the last time this was read
            uint32_t reserved2: 15;
        } bits;

        uint32_t value = 0;

        CtrlStat() = default;

        CtrlStat(uint32_t new_value)
        {
            value = new_value;
        }
    };

    struct Registers
    {
        volatile uint32_t ctrl_stat; //!< control and status register
        volatile uint32_t reload_val; //!< reload value register
        volatile uint32_t current_val; //!< current value register
        volatile uint32_t calib_val; //!< calibration value register
    };

    static inline volatile Registers* registers()
    {
        return reinterpret_cast<volatile Registers*>(BASE_ADDR);
    }

    static inline void setReloadValue(uint32_t value)
    {
        registers()->reload_val = value & 0x00FFFFFF;
    }

    static inline uint32_t getReloadValue()
    {
        return registers()->reload_val & 0x00FFFFFF;
    }

    static inline void setCurrentValue(uint32_t value)
    {
        registers()->current_val = value & 0x00FFFFFF;
    }

    static inline uint32_t getCurrentValue()
    {
        return registers()->current_val & 0x00FFFFFF;
    }

    static inline uint32_t getCalibrationValue()
    {
        return registers()->calib_val;
    }
}
