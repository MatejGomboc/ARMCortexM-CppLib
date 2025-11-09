#include "bit_utils.hpp"

// ============================================================================
// uint8_t tests
// ============================================================================

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_8_0(uint8_t value) {
    return Cortex::isBitSet(value, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_runtime_8_0>:
// CHECK-NEXT: movs r0, #0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:
