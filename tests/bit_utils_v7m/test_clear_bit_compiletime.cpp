#include "armcortex/bit_utils.hpp"

// ============================================================================
// uint8_t tests
// ============================================================================

extern "C" [[gnu::naked]] uint8_t test_clear_bit_compiletime_8_0() {
    uint8_t value = 0xFF;
    ArmCortex::clearBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_8_0>:
// CHECK-NEXT: movs r0, #254 @ 0xfe
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint8_t test_clear_bit_compiletime_8_3() {
    uint8_t value = 0xFF;
    ArmCortex::clearBit(value, uint8_t{3});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_8_3>:
// CHECK-NEXT: movs r0, #247 @ 0xf7
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint8_t test_clear_bit_compiletime_8_7() {
    uint8_t value = 0xFF;
    ArmCortex::clearBit(value, uint8_t{7});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_8_7>:
// CHECK-NEXT: movs r0, #127 @ 0x7f
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint8_t test_clear_bit_compiletime_8_multiple() {
    uint8_t value = 0xFF;
    ArmCortex::clearBit(value, uint8_t{0});
    ArmCortex::clearBit(value, uint8_t{3});
    ArmCortex::clearBit(value, uint8_t{7});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_8_multiple>:
// CHECK-NEXT: movs r0, #118 @ 0x76
// CHECK-EMPTY:

// ============================================================================
// uint16_t tests
// ============================================================================

extern "C" [[gnu::naked]] uint16_t test_clear_bit_compiletime_16_0() {
    uint16_t value = 0xFFFF;
    ArmCortex::clearBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_16_0>:
// CHECK-NEXT: movw r0, #65534 @ 0xfffe
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint16_t test_clear_bit_compiletime_16_7() {
    uint16_t value = 0xFFFF;
    ArmCortex::clearBit(value, uint8_t{7});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_16_7>:
// CHECK-NEXT: movw r0, #65407 @ 0xff7f
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint16_t test_clear_bit_compiletime_16_15() {
    uint16_t value = 0xFFFF;
    ArmCortex::clearBit(value, uint8_t{15});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_16_15>:
// CHECK-NEXT: movw r0, #32767 @ 0x7fff
// CHECK-EMPTY:

// ============================================================================
// uint32_t tests
// ============================================================================

extern "C" [[gnu::naked]] uint32_t test_clear_bit_compiletime_32_0() {
    uint32_t value = 0xFFFFFFFF;
    ArmCortex::clearBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_32_0>:
// CHECK-NEXT: mvn.w r0, #1
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_clear_bit_compiletime_32_15() {
    uint32_t value = 0xFFFFFFFF;
    ArmCortex::clearBit(value, uint8_t{15});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_32_15>:
// CHECK-NEXT: mvn.w r0, #32768 @ 0x8000
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_clear_bit_compiletime_32_31() {
    uint32_t value = 0xFFFFFFFF;
    ArmCortex::clearBit(value, uint8_t{31});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_32_31>:
// CHECK-NEXT: mvn.w r0, #2147483648 @ 0x80000000
// CHECK-EMPTY:

// ============================================================================
// uint64_t tests
// ============================================================================

extern "C" [[gnu::naked]] uint64_t test_clear_bit_compiletime_64_0() {
    uint64_t value = 0xFFFFFFFFFFFFFFFF;
    ArmCortex::clearBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_64_0>:
// CHECK-NEXT: mvn.w r0, #1
// CHECK-NEXT: mov.w r1, #4294967295 @ 0xffffffff
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint64_t test_clear_bit_compiletime_64_31() {
    uint64_t value = 0xFFFFFFFFFFFFFFFF;
    ArmCortex::clearBit(value, uint8_t{31});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_64_31>:
// CHECK-NEXT: mvn.w r0, #2147483648 @ 0x80000000
// CHECK-NEXT: mov.w r1, #4294967295 @ 0xffffffff
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint64_t test_clear_bit_compiletime_64_63() {
    uint64_t value = 0xFFFFFFFFFFFFFFFF;
    ArmCortex::clearBit(value, uint8_t{63});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_64_63>:
// CHECK-NEXT: mov.w r0, #4294967295 @ 0xffffffff
// CHECK-NEXT: mvn.w r1, #2147483648 @ 0x80000000
// CHECK-EMPTY:
