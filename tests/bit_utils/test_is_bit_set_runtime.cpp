#include "bit_utils.hpp"

// ============================================================================
// uint8_t tests
// ============================================================================

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_8_0(uint8_t value) {
    return Cortex::isBitSet(value, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_runtime_8_0>:

// DEBUG-CHECK-NEXT: lsls r0, r0, #31
// DEBUG-CHECK-NEXT: lsrs r0, r0, #31

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: ands r0, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: ands r0, r3

// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_8_3(uint8_t value) {
    return Cortex::isBitSet(value, uint8_t{3});
}

// CHECK-LABEL: <test_is_bit_set_runtime_8_3>:
// CHECK-NEXT: lsls r0, r0, #28
// CHECK-NEXT: lsrs r0, r0, #31
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_8_7(uint8_t value) {
    return Cortex::isBitSet(value, uint8_t{7});
}

// CHECK-LABEL: <test_is_bit_set_runtime_8_7>:
// CHECK-NEXT: lsrs r0, r0, #7
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// ============================================================================
// uint16_t tests
// ============================================================================

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_16_0(uint16_t value) {
    return Cortex::isBitSet(value, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_runtime_16_0>:

// DEBUG-CHECK-NEXT: lsls r0, r0, #31
// DEBUG-CHECK-NEXT: lsrs r0, r0, #31

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: ands r0, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: ands r0, r3

// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_16_7(uint16_t value) {
    return Cortex::isBitSet(value, uint8_t{7});
}

// CHECK-LABEL: <test_is_bit_set_runtime_16_7>:
// CHECK-NEXT: lsls r0, r0, #24
// CHECK-NEXT: lsrs r0, r0, #31
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_16_15(uint16_t value) {
    return Cortex::isBitSet(value, uint8_t{15});
}

// CHECK-LABEL: <test_is_bit_set_runtime_16_15>:
// CHECK-NEXT: lsrs r0, r0, #15
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// ============================================================================
// uint32_t tests
// ============================================================================

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_32_0(uint32_t value) {
    return Cortex::isBitSet(value, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_runtime_32_0>:
// CHECK-NEXT: movs r3, #1
// CHECK-NEXT: ands r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_32_15(uint32_t value) {
    return Cortex::isBitSet(value, uint8_t{15});
}

// CHECK-LABEL: <test_is_bit_set_runtime_32_15>:
// CHECK-NEXT: lsls r0, r0, #16
// CHECK-NEXT: lsrs r0, r0, #31
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_32_31(uint32_t value) {
    return Cortex::isBitSet(value, uint8_t{31});
}

// CHECK-LABEL: <test_is_bit_set_runtime_32_31>:
// CHECK-NEXT: lsrs r0, r0, #31
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// ============================================================================
// uint64_t tests
// ============================================================================

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_64_0(uint64_t value) {
    return Cortex::isBitSet(value, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_runtime_64_0>:
// CHECK-NEXT: movs r3, #1
// CHECK-NEXT: ands r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_64_31(uint64_t value) {
    return Cortex::isBitSet(value, uint8_t{31});
}

// CHECK-LABEL: <test_is_bit_set_runtime_64_31>:
// CHECK-NEXT: lsrs r0, r0, #31
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_64_63(uint64_t value) {
    return Cortex::isBitSet(value, uint8_t{63});
}

// CHECK-LABEL: <test_is_bit_set_runtime_64_63>:
// CHECK-NEXT: lsrs r0, r1, #31
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:
