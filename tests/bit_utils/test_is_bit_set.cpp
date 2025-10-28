#include "bit_utils.hpp"

extern "C" [[gnu::naked]] bool test_is_bit_set_static_8_0_false() {
    return Cortex::isBitSet(uint8_t{0x00}, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_static_8_0_false>:
// CHECK-NEXT: movs r0, #0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_8_0_true() {
    return Cortex::isBitSet(uint8_t{0x01}, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_static_8_0_true>:
// CHECK-NEXT: movs r0, #1
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_8_4_false() {
    return Cortex::isBitSet(uint8_t{0x00}, uint8_t{3});
}

// CHECK-LABEL: <test_is_bit_set_static_8_4_false>:
// CHECK-NEXT: movs r0, #0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_8_4_true() {
    return Cortex::isBitSet(uint8_t{0x08}, uint8_t{3});
}

// CHECK-LABEL: <test_is_bit_set_static_8_4_true>:
// CHECK-NEXT: movs r0, #1
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:
