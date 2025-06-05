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

#include "utils.hpp"
#include <cstdint>

namespace CortexM1::Systick {
    static uint32_t* const BASE_ADDR = reinterpret_cast<uint32_t*>(0xE000E010);

    enum class ClockSource : uint8_t {
        EXTERNAL = 0,
        PROCESSOR = 1
    };

    struct Registers
    {
        volatile uint32_t csr; //!< Control and status register
        volatile uint32_t rvr; //!< Reload value register
        volatile uint32_t cvr; //!< Current value register
        volatile const uint32_t calib; //!< Calibration value register
    };

    static inline volatile Registers* registers()
    {
        return reinterpret_cast<volatile Registers*>(BASE_ADDR);
    }

    static inline void enable()
    {
        Utils::setBit(registers()->csr, 0);
    }

    static inline void disable()
    {
        Utils::clearBit(registers()->csr, 0);
    }

    static inline bool isEnabled()
    {
        return Utils::isBitSet(registers()->csr, 0);
    }

    static inline void enableInterrupt()
    {
        Utils::setBit(registers()->csr, 1);
    }

    static inline void disableInterrupt()
    {
        Utils::clearBit(registers()->csr, 1);
    }

    static inline bool isInterruptEnabled()
    {
        return Utils::isBitSet(registers()->csr, 1);
    }

    static inline void setClockSource(ClockSource source)
    {
        if (source == ClockSource::PROCESSOR) {
            Utils::setBit(registers()->csr, 2);
        } else {
            Utils::clearBit(registers()->csr, 2);
        }
    }

    static inline ClockSource getClockSource()
    {
        return static_cast<ClockSource>(Utils::isBitSet(registers()->csr, 2) ? 1 : 0);
    }

    static inline bool hasCountedToZero()
    {
        return Utils::isBitSet(registers()->csr, 16);
    }

    static inline void setReloadValue(uint32_t value)
    {
        registers()->rvr = value & 0x00FFFFFF;
    }

    static inline uint32_t getReloadValue()
    {
        return registers()->rvr & 0x00FFFFFF;
    }

    static inline void setCurrentValue(uint32_t value)
    {
        registers()->cvr = value;
    }

    static inline uint32_t getCurrentValue()
    {
        return registers()->cvr & 0x00FFFFFF;
    }

    static inline uint32_t getCalibrationValue()
    {
        return registers()->calib & 0x00FFFFFF;
    }

    static inline bool isNoRef()
    {
        return Utils::isBitSet(registers()->calib, 31);
    }

    static inline bool isSkew()
    {
        return Utils::isBitSet(registers()->calib, 30);
    }
}
