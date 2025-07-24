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
#include <type_traits>
#include <limits>

namespace Utils {

//! Divides two integers and rounds the result up to the nearest multiple of divisor.
template<typename T>
static inline constexpr T intCeilDiv(T dividend, T divisor)
{
    static_assert(std::is_integral_v<T>, "intCeilDiv only works with integral types");

    if constexpr (std::is_unsigned_v<T>) {
        return (dividend / divisor) + (((dividend % divisor) != 0) ? 1 : 0);
    } else {
        // Handle potential overflow case: INT_MIN / -1
        if ((dividend == std::numeric_limits<T>::min()) && (divisor == -1)) {
            // Saturate to max value to avoid undefined behaviour.
            return std::numeric_limits<T>::max();
        }

        if ((dividend < 0) != (divisor < 0)) {
            return dividend / divisor;
        } else {
            return (dividend / divisor) + (((dividend % divisor) != 0) ? 1 : 0);
        }
    }
}

//! Check if the n-th bit is set in the value.
template<typename T>
static inline constexpr bool isBitSet(T value, uint8_t n)
{
    return (value >> n) & 1;
}

//! Sets the n-th bit in the value.
template<typename T>
static inline constexpr void setBit(T& value, uint8_t n)
{
    value |= T{1} << n;
}

//! Clears the n-th bit in the value.
template<typename T>
static inline constexpr void clearBit(T& value, uint8_t n)
{
    value &= ~(T{1} << n);
}

}
