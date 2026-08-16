#include "utils.hpp"

extern "C" bool test_is_bit_set(unsigned long value, uint8_t bit) {
    return Utils::isBitSet(value, bit);
}

// CHECK-LABEL: <test_is_bit_set>:
// CHECK: movs r0, #4
// CHECK: movs r1, #0
// CHECK-NEXT: bx lr
