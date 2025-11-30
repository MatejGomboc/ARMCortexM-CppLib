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

#include "special_regs.hpp"
#include <cstdint>

namespace Cortex::M3 {
    enum class LrExceptionReturnValue : uint32_t {
        HANDLER = 0xFFFFFFF1,
        THREAD_MSP = 0xFFFFFFF9,
        THREAD_PSP = 0xFFFFFFFD
    };

    union PSR {
        struct Bits {
            uint32_t ISR: 9;
            uint32_t RESERVED0: 1;
            uint32_t ICI_IT_1: 6;
            uint32_t RESERVED1: 8;
            uint32_t T: 1;
            uint32_t ICI_IT_2: 2;
            uint32_t Q: 1;
            uint32_t V: 1;
            uint32_t C: 1;
            uint32_t Z: 1;
            uint32_t N: 1;
        } bits;
        uint32_t value = 0;
        PSR() = default;
        PSR(uint32_t new_value) { value = new_value; }
    };

    union PRIMASK {
        struct Bits {
            uint32_t PRIMASK: 1;
            uint32_t RESERVED: 31;
        } bits;
        uint32_t value = 0;
        PRIMASK() = default;
        PRIMASK(uint32_t new_value) { value = new_value; }
    };

    union FAULTMASK {
        struct Bits {
            uint32_t FAULTMASK: 1;
            uint32_t RESERVED: 31;
        } bits;
        uint32_t value = 0;
        FAULTMASK() = default;
        FAULTMASK(uint32_t new_value) { value = new_value; }
    };

    union BASEPRI {
        struct Bits {
            uint32_t BASEPRI: 8;
            uint32_t RESERVED: 24;
        } bits;
        uint32_t value = 0;
        BASEPRI() = default;
        BASEPRI(uint32_t new_value) { value = new_value; }
    };

    union CONTROL {
        enum class nPRIV : bool {
            PRIVILEGED = false,
            UNPRIVILEGED = true
        };
        enum class SPSEL : bool {
            MSP = false,
            PSP = true
        };
        struct Bits {
            uint32_t nPRIV: 1;
            uint32_t SPSEL: 1;
            uint32_t RESERVED: 30;
        } bits;
        uint32_t value = 0;
        CONTROL() = default;
        CONTROL(uint32_t new_value) { value = new_value; }
    };

    // Common register accessors
    static inline uint32_t getLr() { return asmGetLr(); }
    static inline PSR getApsrReg() { return PSR { asmGetApsr() }; }
    static inline PSR getIpsrReg() { return PSR { asmGetIpsr() }; }
    static inline PSR getEpsrReg() { return PSR { asmGetEpsr() }; }
    static inline PSR getIepsrReg() { return PSR { asmGetIepsr() }; }
    static inline PSR getIapsrReg() { return PSR { asmGetIapsr() }; }
    static inline PSR getEapsrReg() { return PSR { asmGetEapsr() }; }
    static inline PSR getPsrReg() { return PSR { asmGetPsr() }; }
    static inline uint32_t getMspReg() { return asmGetMsp(); }
    static inline void setMspReg(uint32_t value) { asmSetMsp(value); }
    static inline uint32_t getPspReg() { return asmGetPsp(); }
    static inline void setPspReg(uint32_t value) { asmSetPsp(value); }
    static inline PRIMASK getPrimaskReg() { return PRIMASK { asmGetPrimask() }; }
    static inline void setPrimaskReg(PRIMASK primask) { asmSetPrimask(primask.value); }
    static inline CONTROL getControlReg() { return CONTROL { asmGetControl() }; }
    static inline void setControlReg(CONTROL control) { asmSetControl(control.value); }

    // ARMv7-M specific registers
    static inline FAULTMASK getFaultmaskReg() { return FAULTMASK { asmGetFaultmask() }; }
    static inline void setFaultmaskReg(FAULTMASK faultmask) { asmSetFaultmask(faultmask.value); }
    static inline BASEPRI getBasepriReg() { return BASEPRI { asmGetBasepri() }; }
    static inline void setBasepriReg(BASEPRI basepri) { asmSetBasepri(basepri.value); }
    static inline void setBasepriMaxReg(BASEPRI basepri) { asmSetBasepriMax(basepri.value); }
}
