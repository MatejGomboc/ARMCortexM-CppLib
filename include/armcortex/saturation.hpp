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
// Only available on ARMv7-M architectures (Cortex-M3 and above)

#if defined(ARM_CORTEX_M3) || defined(ARM_CORTEX_M4) || defined(ARM_CORTEX_M7)
#include "../../intrinsics/armv7m/saturation.hpp"
#else
#error "saturation.hpp is only available on ARMv7-M architectures (Cortex-M3 and above)"
#endif
