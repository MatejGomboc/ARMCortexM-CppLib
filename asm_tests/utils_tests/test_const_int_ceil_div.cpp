#include "utils.hpp"
#include <limits>

////////////////////////////////////////////////////////////////////
// EDGE CASE: Basic positive division with remainder (unsigned types)

extern "C" unsigned long long test_const_int_ceil_div_1_1() {
    static constexpr unsigned long long result = Utils::intCeilDiv(10ull, 3ull);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_1_1>:
// CHECK-NEXT: movs r0, #4
// CHECK-NEXT: movs r1, #0
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" unsigned long test_const_int_ceil_div_1_2() {
    static constexpr unsigned long result = Utils::intCeilDiv(10ul, 3ul);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_1_2>:
// CHECK-NEXT: movs r0, #4
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" unsigned test_const_int_ceil_div_1_3() {
    static constexpr unsigned result = Utils::intCeilDiv(10u, 3u);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_1_3>:
// CHECK-NEXT: movs r0, #4
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Basic positive division with remainder (signed types)

extern "C" long long test_const_int_ceil_div_2_1() {
    static constexpr long long result = Utils::intCeilDiv(10ll, 3ll);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_2_1>:
// CHECK-NEXT: movs r0, #4
// CHECK-NEXT: movs r1, #0
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" long test_const_int_ceil_div_2_2() {
    static constexpr long result = Utils::intCeilDiv(10l, 3l);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_2_2>:
// CHECK-NEXT: movs r0, #4
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" int test_const_int_ceil_div_2_3() {
    static constexpr int result = Utils::intCeilDiv(10, 3);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_2_3>:
// CHECK-NEXT: movs r0, #4
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Both negative operands

extern "C" long long test_const_int_ceil_div_3_1() {
    static constexpr long long result = Utils::intCeilDiv(-10ll, -3ll);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_3_1>:
// CHECK-NEXT: movs r0, #4
// CHECK-NEXT: movs r1, #0
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" long test_const_int_ceil_div_3_2() {
    static constexpr long result = Utils::intCeilDiv(-10l, -3l);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_3_2>:
// CHECK-NEXT: movs r0, #4
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" int test_const_int_ceil_div_3_3() {
    static constexpr int result = Utils::intCeilDiv(-10, -3);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_3_3>:
// CHECK-NEXT: movs r0, #4
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Exact division (no remainder)

extern "C" unsigned test_const_int_ceil_div_4_1() {
    static constexpr unsigned result = Utils::intCeilDiv(12u, 3u);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_4_1>:
// CHECK-NEXT: movs r0, #4
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" int test_const_int_ceil_div_4_2() {
    static constexpr int result = Utils::intCeilDiv(12, 3);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_4_2>:
// CHECK-NEXT: movs r0, #4
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Division by 1

extern "C" unsigned test_const_int_ceil_div_5_1() {
    static constexpr unsigned result = Utils::intCeilDiv(42u, 1u);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_5_1>:
// CHECK-NEXT: movs r0, #42
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" int test_const_int_ceil_div_5_2() {
    static constexpr int result = Utils::intCeilDiv(-42, 1);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_5_2>:
// CHECK-NEXT: movs r0, #42
// CHECK-NEXT: negs r0, r0
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Zero dividend

extern "C" unsigned test_const_int_ceil_div_6_1() {
    static constexpr unsigned result = Utils::intCeilDiv(0u, 5u);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_6_1>:
// CHECK-NEXT: movs r0, #0
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" int test_const_int_ceil_div_6_2() {
    static constexpr int result = Utils::intCeilDiv(0, 5);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_6_2>:
// CHECK-NEXT: movs r0, #0
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Dividend less than divisor

extern "C" unsigned test_const_int_ceil_div_7_1() {
    static constexpr unsigned result = Utils::intCeilDiv(2u, 3u);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_7_1>:
// CHECK-NEXT: movs r0, #1
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" unsigned test_const_int_ceil_div_7_2() {
    static constexpr unsigned result = Utils::intCeilDiv(1u, 3u);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_7_2>:
// CHECK-NEXT: movs r0, #1
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Testing with exact std::numeric_limits<T>::min() values

extern "C" unsigned test_const_int_ceil_div_8_1() {
    static constexpr unsigned result = Utils::intCeilDiv(std::numeric_limits<unsigned>::min(), 1u); // 0 / 1
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_8_1>:
// CHECK-NEXT: movs r0, #0
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Mixed signs (positive/negative)

extern "C" int test_const_int_ceil_div_9_1() {
    static constexpr int result = Utils::intCeilDiv(10, -3);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_9_1>:
// CHECK-NEXT: movs r0, #3
// CHECK-NEXT: negs r0, r0
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" int test_const_int_ceil_div_9_2() {
    static constexpr int result = Utils::intCeilDiv(-10, 3);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_9_2>:
// CHECK-NEXT: movs r0, #3
// CHECK-NEXT: negs r0, r0
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Large values

extern "C" unsigned long long test_const_int_ceil_div_10_1() {
    static constexpr unsigned long long result = Utils::intCeilDiv(1000000000ull, 7ull);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_10_1>:
// CHECK-NEXT: ldr r0, [pc, #4]
// CHECK-NEXT: movs r1, #0
// CHECK-NEXT: bx lr
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0x0883d3b7
// CHECK-EMPTY:

extern "C" unsigned test_const_int_ceil_div_10_2() {
    static constexpr unsigned result = Utils::intCeilDiv(1000u, 33u);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_10_2>:
// CHECK-NEXT: movs r0, #31
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Division where dividend equals divisor (n/n = 1)

extern "C" unsigned test_const_int_ceil_div_11_1() {
    static constexpr unsigned result = Utils::intCeilDiv(5u, 5u);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_11_1>:
// CHECK-NEXT: movs r0, #1
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" int test_const_int_ceil_div_11_2() {
    static constexpr int result = Utils::intCeilDiv(-5, -5);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_11_2>:
// CHECK-NEXT: movs r0, #1
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Negative exact division

extern "C" int test_const_int_ceil_div_12_1() {
    static constexpr int result = Utils::intCeilDiv(-12, -3);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_12_1>:
// CHECK-NEXT: movs r0, #4
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Division by -1

extern "C" int test_const_int_ceil_div_13_1() {
    static constexpr int result = Utils::intCeilDiv(42, -1);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_13_1>:
// CHECK-NEXT: movs r0, #42
// CHECK-NEXT: negs r0, r0
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" int test_const_int_ceil_div_13_2() {
    static constexpr int result = Utils::intCeilDiv(-42, -1);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_13_2>:
// CHECK-NEXT: movs r0, #42
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: One as dividend

extern "C" unsigned test_const_int_ceil_div_14_1() {
    static constexpr unsigned result = Utils::intCeilDiv(1u, 2u);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_14_1>:
// CHECK-NEXT: movs r0, #1
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" unsigned test_const_int_ceil_div_14_2() {
    static constexpr unsigned result = Utils::intCeilDiv(1u, 10u);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_14_2>:
// CHECK-NEXT: movs r0, #1
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Boundary values for signed types

extern "C" int test_const_int_ceil_div_15_1() {
    static constexpr int result = Utils::intCeilDiv(std::numeric_limits<int>::max() - 7, 2); // Large int value that won't overflow
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_15_1>:
// CHECK-NEXT: ldr r0, [pc, #4]
// CHECK-NEXT: bx lr
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0x3ffffffc
// CHECK-EMPTY:

// Test the INT_MIN / -1 overflow case (now handled by saturation to INT_MAX)
extern "C" int test_const_int_ceil_div_15_2() {
    static constexpr int result = Utils::intCeilDiv(std::numeric_limits<int>::min(), -1); // INT_MIN / -1 saturates to INT_MAX
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_15_2>:
// CHECK-NEXT: ldr r0, [pc, #0]
// CHECK-NEXT: bx lr
// CHECK-NEXT: .word 0x7fffffff
// CHECK-EMPTY:

extern "C" int test_const_int_ceil_div_15_3() {
    static constexpr int result = Utils::intCeilDiv(std::numeric_limits<int>::min() + 8, -2); // Large negative value that won't overflow
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_15_3>:
// CHECK-NEXT: ldr r0, [pc, #0]
// CHECK-NEXT: bx lr
// CHECK-NEXT: .word 0x3ffffffc
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Large divisor with small dividend

extern "C" unsigned test_const_int_ceil_div_16_1() {
    static constexpr unsigned result = Utils::intCeilDiv(5u, 1000u);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_16_1>:
// CHECK-NEXT: movs r0, #1
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Consecutive values (tests off-by-one scenarios)

extern "C" unsigned test_const_int_ceil_div_17_1() {
    static constexpr unsigned result = Utils::intCeilDiv(11u, 3u); // Should be 4
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_17_1>:
// CHECK-NEXT: movs r0, #4
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" unsigned test_const_int_ceil_div_17_2() {
    static constexpr unsigned result = Utils::intCeilDiv(13u, 3u); // Should be 5
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_17_2>:
// CHECK-NEXT: movs r0, #5
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Explicit boundary value tests using std::numeric_limits

extern "C" unsigned test_const_int_ceil_div_18_1() {
    // Test with largest safe unsigned value that won't overflow
    static constexpr unsigned dividend = std::numeric_limits<unsigned>::max() - 15u;
    static constexpr unsigned result = Utils::intCeilDiv(dividend, 2u);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_18_1>:
// CHECK-NEXT: ldr r0, [pc, #0]
// CHECK-NEXT: bx lr
// CHECK-NEXT: .word 0x7ffffff8
// CHECK-EMPTY:

extern "C" unsigned long long test_const_int_ceil_div_18_2() {
    // Test with 64-bit boundary values
    static constexpr unsigned long long dividend = std::numeric_limits<unsigned long long>::max() / 2ull;
    static constexpr unsigned long long result = Utils::intCeilDiv(dividend, 3ull);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_18_2>:
// CHECK-NEXT: ldr r0, [pc, #4]
// CHECK-NEXT: ldr r1, [pc, #8]
// CHECK-NEXT: bx lr
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xaaaaaaab
// CHECK-NEXT: .word 0x2aaaaaaa
// CHECK-EMPTY:

////////////////////////////////////////////////////////////////////
// EDGE CASE: Near-overflow scenarios with unsigned types

extern "C" unsigned test_const_int_ceil_div_19_1() {
    static constexpr unsigned result = Utils::intCeilDiv(std::numeric_limits<unsigned>::max(), 2u); // UINT_MAX / 2
    // The implementation correctly avoids overflow by not using (dividend + divisor - 1) / divisor
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_19_1>:
// CHECK-NEXT: movs r0, #128
// CHECK-NEXT: lsls r0, r0, #24
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" unsigned test_const_int_ceil_div_19_2() {
    static constexpr unsigned result = Utils::intCeilDiv(std::numeric_limits<unsigned>::max() - 5u, 10u); // Near UINT_MAX
    // The implementation correctly handles this without overflow
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div_19_2>:
// CHECK-NEXT: ldr r0, [pc, #4]
// CHECK-NEXT: bx lr
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0x19999999
// CHECK-EMPTY:
