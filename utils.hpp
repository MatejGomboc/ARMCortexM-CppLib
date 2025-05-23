// Copyright (C) 2025 Matej Gomboc <https://github.com/MatejGomboc/ARMCortexM-CppLib>
// See the LICENSE file for the full license governing this code.

#pragma once

#include <cstdint>

namespace Utils {

//! Divides two integers and rounds the result up to the nearest multiple of divisor.
template<typename Tin, typename Tout>
static inline Tout intCeilDiv(Tin dividend, Tin divisor)
{
    return (dividend + divisor - 1) / divisor;
}

//! Check if the n-th bit is set in the value.
template<typename T>
static inline bool isBitSet(T value, uint8_t n)
{
    return (value >> n) & 1;
}

//! Sets the n-th bit in the value.
template<typename T>
static inline void setBit(T& value, uint8_t n)
{
    value |= 1 << n;
}

//! Clears the n-th bit in the value.
template<typename T>
static inline void clearBit(T& value, uint8_t n)
{
    value &= ~(1 << n);
}

}
