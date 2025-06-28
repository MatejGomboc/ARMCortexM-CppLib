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
    //! Send Event hint instruction
    //! Causes an event to be signaled to all processors within a multiprocessor system
    static inline void SendEvent()
    {
        asm volatile("sev" : : : "memory");
    }

    //! Wait For Event hint instruction
    //! If the event register is clear, the processor suspends execution until an event occurs
    static inline void WaitForEvent()
    {
        asm volatile("wfe" : : : "memory");
    }

    //! Wait For Interrupt hint instruction
    //! Suspends execution until an interrupt or debug event occurs
    static inline void WaitForInterrupt()
    {
        asm volatile("wfi" : : : "memory");
    }

    //! No Operation instruction
    //! Does nothing - can be used for timing or alignment purposes
    static inline void Nop()
    {
        asm volatile("nop");
    }

    //! Yield hint instruction
    //! Indicates that the current thread is performing a task that can be swapped out
    static inline void Yield()
    {
        asm volatile("yield" : : : "memory");
    }

    //! Breakpoint instruction
    //! Causes the processor to enter Debug state if halting debug is enabled
    //! @param value Immediate value (0-255) that can be used by debugger
    static inline void Breakpoint(uint8_t value = 0)
    {
        asm volatile("bkpt %0" : : "i" (value));
    }

    //! Reverse byte order in a word
    //! @param value Input value
    //! @return Value with bytes reversed (e.g., 0x12345678 -> 0x78563412)
    static inline uint32_t ReverseBytes(uint32_t value)
    {
        uint32_t result;
        asm volatile("rev %0, %1" : "=r" (result) : "r" (value));
        return result;
    }

    //! Reverse byte order in each halfword
    //! @param value Input value
    //! @return Value with bytes reversed in each 16-bit halfword
    static inline uint32_t ReverseBytes16(uint32_t value)
    {
        uint32_t result;
        asm volatile("rev16 %0, %1" : "=r" (result) : "r" (value));
        return result;
    }

    //! Reverse byte order in bottom halfword and sign extend
    //! @param value Input value (uses lower 16 bits)
    //! @return Sign-extended value with bytes reversed in the halfword
    static inline int32_t ReverseBytesSignedHalfword(int32_t value)
    {
        int32_t result;
        asm volatile("revsh %0, %1" : "=r" (result) : "r" (value));
        return result;
    }
}
