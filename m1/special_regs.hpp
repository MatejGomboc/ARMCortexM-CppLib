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

#include "intrinsics/common/special_regs.hpp"
#include <cstdint>

namespace Cortex::M1 {
    //! Exception return values saved to LR on exception entry.
    enum class LrExceptionReturnValue : uint32_t {
        HANDLER = 0xFFFFFFF1,
        THREAD_MSP = 0xFFFFFFF9,
        THREAD_PSP = 0xFFFFFFFD
    };

    union PSR {
        struct Bits {
            uint32_t ISR: 9;
            uint32_t RESERVED0: 15;
            uint32_t T: 1;
            uint32_t RESERVED1: 3;
            uint32_t V: 1;
            uint32_t C: 1;
            uint32_t Z: 1;
            uint32_t N: 1;
        } bits;

        uint32_t value = 0;

        PSR() = default;

        PSR(uint32_t new_value)
        {
            value = new_value;
        }
    };

    union PRIMASK {
        struct Bits {
            uint32_t PRIMASK: 1;
            uint32_t RESERVED: 31;
        } bits;

        uint32_t value = 0;

        PRIMASK() = default;

        PRIMASK(uint32_t new_value)
        {
            value = new_value;
        }
    };

    union CONTROL {
        enum class SPSEL : bool {
            MSP = false,
            PSP = true
        };

        struct Bits {
            uint32_t RESERVED0: 1;
            uint32_t SPSEL: 1;
            uint32_t RESERVED1: 30;
        } bits;

        uint32_t value = 0;

        CONTROL() = default;

        CONTROL(uint32_t new_value)
        {
            value = new_value;
        }
    };

    static inline uint32_t getLr()
    {
        return Intrinsics::getLr();
    }

    static inline PSR getApsrReg()
    {
        return PSR { Intrinsics::getApsr() };
    }

    static inline PSR getIpsrReg()
    {
        return PSR { Intrinsics::getIpsr() };
    }

    static inline PSR getEpsrReg()
    {
        return PSR { Intrinsics::getEpsr() };
    }

    static inline PSR getIepsrReg()
    {
        return PSR { Intrinsics::getIepsr() };
    }

    static inline PSR getIapsrReg()
    {
        return PSR { Intrinsics::getIapsr() };
    }

    static inline PSR getEapsrReg()
    {
        return PSR { Intrinsics::getEapsr() };
    }

    static inline PSR getPsrReg()
    {
        return PSR { Intrinsics::getPsr() };
    }

    static inline uint32_t getMspReg()
    {
        return Intrinsics::getMsp();
    }

    static inline void setMspReg(uint32_t value)
    {
        Intrinsics::setMsp(value);
    }

    static inline uint32_t getPspReg()
    {
        return Intrinsics::getPsp();
    }

    static inline void setPspReg(uint32_t value)
    {
        Intrinsics::setPsp(value);
    }

    static inline PRIMASK getPrimaskReg()
    {
        return PRIMASK { Intrinsics::getPrimask() };
    }

    static inline void setPrimaskReg(PRIMASK primask)
    {
        Intrinsics::setPrimask(primask.value);
    }

    static inline CONTROL getControlReg()
    {
        return CONTROL { Intrinsics::getControl() };
    }

    static inline void setControlReg(CONTROL control)
    {
        Intrinsics::setControl(control.value);
    }
}
