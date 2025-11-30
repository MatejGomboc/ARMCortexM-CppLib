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

// Forwarding header for flat include interface
// MPU is only available on Cortex-M0+, M3, and above

#if defined(ARM_CORTEX_M0PLUS)
#include "../../m0plus/mpu.hpp"
#elif defined(ARM_CORTEX_M3)
#include "../../m3/mpu.hpp"
#elif defined(ARM_CORTEX_M0) || defined(ARM_CORTEX_M1)
#error "MPU is not available on Cortex-M0 and Cortex-M1"
#else
#error "No ARM Cortex-M architecture defined. Define one of: ARM_CORTEX_M0, ARM_CORTEX_M0PLUS, ARM_CORTEX_M1, ARM_CORTEX_M3"
#endif
