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
// CHECK-EMPTY:
