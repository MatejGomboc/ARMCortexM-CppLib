/*
    Copyright (C) 2025 Matej Gomboc <https://github.com/MatejGomboc/ARMCortexM-CppLib>

    Licensed under the Apache License, Version 2.0 (the "Licence");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once

#include <cstdint>

namespace CortexM0 {
    static inline void noOperation()
    {
        asm volatile("nop");
    }

    static inline void breakpoint(uint8_t value)
    {
        asm volatile("bkpt %0" : : "i" (value));
    }

    static inline uint32_t reverseBytes(uint32_t value)
    {
        uint32_t result;
        asm volatile("rev %0, %1" : "=r" (result) : "r" (value));
        return result;
    }

    static inline uint32_t reverseBytes16(uint32_t value)
    {
        uint32_t result;
        asm volatile("rev16 %0, %1" : "=r" (result) : "r" (value));
        return result;
    }

    static inline int32_t reverseBytesSignedHalfword(int32_t value)
    {
        int32_t result;
        asm volatile("revsh %0, %1" : "=r" (result) : "r" (value));
        return result;
    }
}
