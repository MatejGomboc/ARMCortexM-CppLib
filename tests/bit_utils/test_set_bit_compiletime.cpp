#include "bit_utils.hpp"

// ============================================================================
// uint8_t tests
// ============================================================================

extern "C" [[gnu::naked]] uint8_t test_set_bit_compiletime_8_0() {
    uint8_t value = 0x00;
    Cortex::setBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_compiletime_8_0>:
// CHECK-NEXT: movs r0, #1
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint8_t test_set_bit_compiletime_8_3() {
    uint8_t value = 0x00;
    Cortex::setBit(value, uint8_t{3});
    return value;
}

// CHECK-LABEL: <test_set_bit_compiletime_8_3>:
// CHECK-NEXT: movs r0, #8
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint8_t test_set_bit_compiletime_8_7() {
    uint8_t value = 0x00;
    Cortex::setBit(value, uint8_t{7});
    return value;
}

// CHECK-LABEL: <test_set_bit_compiletime_8_7>:
// CHECK-NEXT: movs r0, #128
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint8_t test_set_bit_compiletime_8_multiple() {
    uint8_t value = 0x00;
    Cortex::setBit(value, uint8_t{0});
    Cortex::setBit(value, uint8_t{3});
    Cortex::setBit(value, uint8_t{7});
    return value;
}

// CHECK-LABEL: <test_set_bit_compiletime_8_multiple>:
// CHECK-NEXT: movs r0, #137
// CHECK-EMPTY:

// ============================================================================
// uint16_t tests
// ============================================================================

extern "C" [[gnu::naked]] uint16_t test_set_bit_compiletime_16_0() {
    uint16_t value = 0x0000;
    Cortex::setBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_compiletime_16_0>:
// CHECK-NEXT: movs r0, #1
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint16_t test_set_bit_compiletime_16_7() {
    uint16_t value = 0x0000;
    Cortex::setBit(value, uint8_t{7});
    return value;
}

// CHECK-LABEL: <test_set_bit_compiletime_16_7>:
// CHECK-NEXT: movs r0, #128
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint16_t test_set_bit_compiletime_16_15() {
    uint16_t value = 0x0000;
    Cortex::setBit(value, uint8_t{15});
    return value;
}

// CHECK-LABEL: <test_set_bit_compiletime_16_15>:
// CHECK-NEXT: movs r0, #128
// CHECK-NEXT: lsls r0, r0, #8
// CHECK-EMPTY:

// ============================================================================
// uint32_t tests
// ============================================================================

extern "C" [[gnu::naked]] uint32_t test_set_bit_compiletime_32_0() {
    uint32_t value = 0x00000000;
    Cortex::setBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_compiletime_32_0>:
// CHECK-NEXT: movs r0, #1
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_set_bit_compiletime_32_15() {
    uint32_t value = 0x00000000;
    Cortex::setBit(value, uint8_t{15});
    return value;
}

// CHECK-LABEL: <test_set_bit_compiletime_32_15>:
// CHECK-NEXT: movs r0, #128
// CHECK-NEXT: lsls r0, r0, #8
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_set_bit_compiletime_32_31() {
    uint32_t value = 0x00000000;
    Cortex::setBit(value, uint8_t{31});
    return value;
}

// CHECK-LABEL: <test_set_bit_compiletime_32_31>:
// CHECK-NEXT: movs r0, #128
// CHECK-NEXT: lsls r0, r0, #24
// CHECK-EMPTY:

// ============================================================================
// uint64_t tests
// ============================================================================

extern "C" [[gnu::naked]] uint64_t test_set_bit_compiletime_64_0() {
    uint64_t value = 0x0000000000000000;
    Cortex::setBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_compiletime_64_0>:
// CHECK-NEXT: movs r0, #1
// CHECK-NEXT: movs r1, #0
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint64_t test_set_bit_compiletime_64_31() {
    uint64_t value = 0x0000000000000000;
    Cortex::setBit(value, uint8_t{31});
    return value;
}

// CHECK-LABEL: <test_set_bit_compiletime_64_31>:
// CHECK-NEXT: movs r0, #128
// CHECK-NEXT: lsls r0, r0, #24
// CHECK-NEXT: movs r1, #0
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint64_t test_set_bit_compiletime_64_63() {
    uint64_t value = 0x0000000000000000;
    Cortex::setBit(value, uint8_t{63});
    return value;
}

// CHECK-LABEL: <test_set_bit_compiletime_64_63>:
// CHECK-NEXT: movs r0, #0
// CHECK-NEXT: movs r1, #128
// CHECK-NEXT: lsls r1, r1, #24
// CHECK-EMPTY:
