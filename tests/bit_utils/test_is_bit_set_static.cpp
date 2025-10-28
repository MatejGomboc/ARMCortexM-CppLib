#include "bit_utils.hpp"

// ============================================================================
// uint8_t tests
// ============================================================================

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

extern "C" [[gnu::naked]] bool test_is_bit_set_static_8_3_false() {
    return Cortex::isBitSet(uint8_t{0x00}, uint8_t{3});
}

// CHECK-LABEL: <test_is_bit_set_static_8_3_false>:
// CHECK-NEXT: movs r0, #0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_8_3_true() {
    return Cortex::isBitSet(uint8_t{0x08}, uint8_t{3});
}

// CHECK-LABEL: <test_is_bit_set_static_8_3_true>:
// CHECK-NEXT: movs r0, #1
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_8_7_false() {
    return Cortex::isBitSet(uint8_t{0x00}, uint8_t{7});
}

// CHECK-LABEL: <test_is_bit_set_static_8_7_false>:
// CHECK-NEXT: movs r0, #0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_8_7_true() {
    return Cortex::isBitSet(uint8_t{0x80}, uint8_t{7});
}

// CHECK-LABEL: <test_is_bit_set_static_8_7_true>:
// CHECK-NEXT: movs r0, #1
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// ============================================================================
// uint16_t tests
// ============================================================================

extern "C" [[gnu::naked]] bool test_is_bit_set_static_16_0_false() {
    return Cortex::isBitSet(uint16_t{0x0000}, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_static_16_0_false>:
// CHECK-NEXT: movs r0, #0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_16_0_true() {
    return Cortex::isBitSet(uint16_t{0x0001}, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_static_16_0_true>:
// CHECK-NEXT: movs r0, #1
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_16_7_false() {
    return Cortex::isBitSet(uint16_t{0x0000}, uint8_t{7});
}

// CHECK-LABEL: <test_is_bit_set_static_16_7_false>:
// CHECK-NEXT: movs r0, #0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_16_7_true() {
    return Cortex::isBitSet(uint16_t{0x0080}, uint8_t{7});
}

// CHECK-LABEL: <test_is_bit_set_static_16_7_true>:
// CHECK-NEXT: movs r0, #1
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_16_15_false() {
    return Cortex::isBitSet(uint16_t{0x0000}, uint8_t{15});
}

// CHECK-LABEL: <test_is_bit_set_static_16_15_false>:
// CHECK-NEXT: movs r0, #0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_16_15_true() {
    return Cortex::isBitSet(uint16_t{0x8000}, uint8_t{15});
}

// CHECK-LABEL: <test_is_bit_set_static_16_15_true>:
// CHECK-NEXT: movs r0, #1
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// ============================================================================
// uint32_t tests
// ============================================================================

extern "C" [[gnu::naked]] bool test_is_bit_set_static_32_0_false() {
    return Cortex::isBitSet(uint32_t{0x00000000}, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_static_32_0_false>:
// CHECK-NEXT: movs r0, #0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_32_0_true() {
    return Cortex::isBitSet(uint32_t{0x00000001}, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_static_32_0_true>:
// CHECK-NEXT: movs r0, #1
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_32_15_false() {
    return Cortex::isBitSet(uint32_t{0x00000000}, uint8_t{15});
}

// CHECK-LABEL: <test_is_bit_set_static_32_15_false>:
// CHECK-NEXT: movs r0, #0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_32_15_true() {
    return Cortex::isBitSet(uint32_t{0x00008000}, uint8_t{15});
}

// CHECK-LABEL: <test_is_bit_set_static_32_15_true>:
// CHECK-NEXT: movs r0, #1
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_32_31_false() {
    return Cortex::isBitSet(uint32_t{0x00000000}, uint8_t{31});
}

// CHECK-LABEL: <test_is_bit_set_static_32_31_false>:
// CHECK-NEXT: movs r0, #0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_32_31_true() {
    return Cortex::isBitSet(uint32_t{0x80000000}, uint8_t{31});
}

// CHECK-LABEL: <test_is_bit_set_static_32_31_true>:
// CHECK-NEXT: movs r0, #1
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// ============================================================================
// uint64_t tests
// ============================================================================

extern "C" [[gnu::naked]] bool test_is_bit_set_static_64_0_false() {
    return Cortex::isBitSet(uint64_t{0x0000000000000000}, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_static_64_0_false>:
// CHECK-NEXT: movs r0, #0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_64_0_true() {
    return Cortex::isBitSet(uint64_t{0x0000000000000001}, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_static_64_0_true>:
// CHECK-NEXT: movs r0, #1
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_64_31_false() {
    return Cortex::isBitSet(uint64_t{0x0000000000000000}, uint8_t{31});
}

// CHECK-LABEL: <test_is_bit_set_static_64_31_false>:
// CHECK-NEXT: movs r0, #0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_64_31_true() {
    return Cortex::isBitSet(uint64_t{0x0000000080000000}, uint8_t{31});
}

// CHECK-LABEL: <test_is_bit_set_static_64_31_true>:
// CHECK-NEXT: movs r0, #1
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_64_63_false() {
    return Cortex::isBitSet(uint64_t{0x0000000000000000}, uint8_t{63});
}

// CHECK-LABEL: <test_is_bit_set_static_64_63_false>:
// CHECK-NEXT: movs r0, #0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_static_64_63_true() {
    return Cortex::isBitSet(uint64_t{0x8000000000000000}, uint8_t{63});
}

// CHECK-LABEL: <test_is_bit_set_static_64_63_true>:
// CHECK-NEXT: movs r0, #1
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:
