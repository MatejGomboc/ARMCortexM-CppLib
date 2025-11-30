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

namespace Cortex {
    //! Load-Exclusive Word.
    //! Loads a word from memory and marks the address for exclusive access.
    //! \param addr Pointer to the memory location (must be word-aligned).
    //! \return Value at the memory location.
    //! \note Available on ARMv7-M (Cortex-M3, M4, M7) only.
    [[gnu::always_inline]] static inline uint32_t asmLdrex(volatile uint32_t* addr)
    {
        uint32_t result;
        asm volatile("ldrex %0, [%1]" : "=r" (result) : "r" (addr) : "memory");
        return result;
    }

    //! Load-Exclusive Halfword.
    //! Loads a halfword from memory and marks the address for exclusive access.
    //! \param addr Pointer to the memory location (must be halfword-aligned).
    //! \return Value at the memory location (zero-extended to 32 bits).
    //! \note Available on ARMv7-M (Cortex-M3, M4, M7) only.
    [[gnu::always_inline]] static inline uint16_t asmLdrexh(volatile uint16_t* addr)
    {
        uint16_t result;
        asm volatile("ldrexh %0, [%1]" : "=r" (result) : "r" (addr) : "memory");
        return result;
    }

    //! Load-Exclusive Byte.
    //! Loads a byte from memory and marks the address for exclusive access.
    //! \param addr Pointer to the memory location.
    //! \return Value at the memory location (zero-extended to 32 bits).
    //! \note Available on ARMv7-M (Cortex-M3, M4, M7) only.
    [[gnu::always_inline]] static inline uint8_t asmLdrexb(volatile uint8_t* addr)
    {
        uint8_t result;
        asm volatile("ldrexb %0, [%1]" : "=r" (result) : "r" (addr) : "memory");
        return result;
    }

    //! Store-Exclusive Word.
    //! Attempts to store a word if exclusive access is still held.
    //! \param value Value to store.
    //! \param addr Pointer to the memory location (must be word-aligned).
    //! \return 0 if store succeeded, 1 if store failed (exclusive access lost).
    //! \note Available on ARMv7-M (Cortex-M3, M4, M7) only.
    [[gnu::always_inline]] static inline uint32_t asmStrex(uint32_t value, volatile uint32_t* addr)
    {
        uint32_t result;
        asm volatile("strex %0, %1, [%2]" : "=&r" (result) : "r" (value), "r" (addr) : "memory");
        return result;
    }

    //! Store-Exclusive Halfword.
    //! Attempts to store a halfword if exclusive access is still held.
    //! \param value Value to store.
    //! \param addr Pointer to the memory location (must be halfword-aligned).
    //! \return 0 if store succeeded, 1 if store failed (exclusive access lost).
    //! \note Available on ARMv7-M (Cortex-M3, M4, M7) only.
    [[gnu::always_inline]] static inline uint32_t asmStrexh(uint16_t value, volatile uint16_t* addr)
    {
        uint32_t result;
        asm volatile("strexh %0, %1, [%2]" : "=&r" (result) : "r" (value), "r" (addr) : "memory");
        return result;
    }

    //! Store-Exclusive Byte.
    //! Attempts to store a byte if exclusive access is still held.
    //! \param value Value to store.
    //! \param addr Pointer to the memory location.
    //! \return 0 if store succeeded, 1 if store failed (exclusive access lost).
    //! \note Available on ARMv7-M (Cortex-M3, M4, M7) only.
    [[gnu::always_inline]] static inline uint32_t asmStrexb(uint8_t value, volatile uint8_t* addr)
    {
        uint32_t result;
        asm volatile("strexb %0, %1, [%2]" : "=&r" (result) : "r" (value), "r" (addr) : "memory");
        return result;
    }

    //! Clear Exclusive.
    //! Clears the local exclusive access tag.
    //! Use after a failed exclusive sequence or when abandoning an exclusive access.
    //! \note Available on ARMv7-M (Cortex-M3, M4, M7) only.
    [[gnu::always_inline]] static inline void asmClrex()
    {
        asm volatile("clrex" : : : "memory");
    }
}
