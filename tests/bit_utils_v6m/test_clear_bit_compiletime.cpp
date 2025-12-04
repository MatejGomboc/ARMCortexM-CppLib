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
// CHECK-NEXT: movs r0, #254
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint8_t test_clear_bit_compiletime_8_3() {
    uint8_t value = 0xFF;
    ArmCortex::clearBit(value, uint8_t{3});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_8_3>:
// CHECK-NEXT: movs r0, #247
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint8_t test_clear_bit_compiletime_8_7() {
    uint8_t value = 0xFF;
    ArmCortex::clearBit(value, uint8_t{7});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_8_7>:
// CHECK-NEXT: movs r0, #127
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint8_t test_clear_bit_compiletime_8_multiple() {
    uint8_t value = 0xFF;
    ArmCortex::clearBit(value, uint8_t{0});
    ArmCortex::clearBit(value, uint8_t{3});
    ArmCortex::clearBit(value, uint8_t{7});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_8_multiple>:
// CHECK-NEXT: movs r0, #118
// MAXSPEED-CHECK-NEXT: nop
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
// CHECK-NEXT: ldr r0, [pc, #0]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0x0000fffe
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint16_t test_clear_bit_compiletime_16_7() {
    uint16_t value = 0xFFFF;
    ArmCortex::clearBit(value, uint8_t{7});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_16_7>:
// CHECK-NEXT: ldr r0, [pc, #0]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0x0000ff7f
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint16_t test_clear_bit_compiletime_16_15() {
    uint16_t value = 0xFFFF;
    ArmCortex::clearBit(value, uint8_t{15});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_16_15>:
// CHECK-NEXT: ldr r0, [pc, #0]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0x00007fff
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

// DEBUG-CHECK-NEXT: movs r0, #2
// DEBUG-CHECK-NEXT: negs r0, r0

// MINSIZE-CHECK-NEXT: movs r0, #2
// MINSIZE-CHECK-NEXT: negs r0, r0

// MAXSPEED-CHECK-NEXT: movs r0, #2
// MAXSPEED-CHECK-NEXT: negs r0, r0

// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_clear_bit_compiletime_32_15() {
    uint32_t value = 0xFFFFFFFF;
    ArmCortex::clearBit(value, uint8_t{15});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_32_15>:
// CHECK-NEXT: ldr r0, [pc, #0]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xffff7fff
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_clear_bit_compiletime_32_31() {
    uint32_t value = 0xFFFFFFFF;
    ArmCortex::clearBit(value, uint8_t{31});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_32_31>:
// CHECK-NEXT: ldr r0, [pc, #0]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0x7fffffff
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

// DEBUG-CHECK-NEXT: movs r0, #2
// DEBUG-CHECK-NEXT: negs r0, r0
// DEBUG-CHECK-NEXT: asrs r1, r0, #31

// MINSIZE-CHECK-NEXT: movs r0, #2
// MINSIZE-CHECK-NEXT: negs r0, r0
// MINSIZE-CHECK-NEXT: asrs r1, r0, #31

// MAXSPEED-CHECK-NEXT: movs r0, #2
// MAXSPEED-CHECK-NEXT: negs r0, r0
// MAXSPEED-CHECK-NEXT: asrs r1, r0, #31
// MAXSPEED-CHECK-NEXT: nop

// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint64_t test_clear_bit_compiletime_64_31() {
    uint64_t value = 0xFFFFFFFFFFFFFFFF;
    ArmCortex::clearBit(value, uint8_t{31});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_64_31>:

// DEBUG-CHECK-NEXT: ldr r0, [pc, #4]
// DEBUG-CHECK-NEXT: movs r1, #1
// DEBUG-CHECK-NEXT: negs r1, r1
// DEBUG-CHECK-NEXT: .word 0x7fffffff

// MINSIZE-CHECK-NEXT: movs r1, #1
// MINSIZE-CHECK-NEXT: ldr r0, [pc, #0]
// MINSIZE-CHECK-NEXT: negs r1, r1
// MINSIZE-CHECK-NEXT: .word 0x7fffffff

// MAXSPEED-CHECK-NEXT: movs r1, #1
// MAXSPEED-CHECK-NEXT: ldr r0, [pc, #4]
// MAXSPEED-CHECK-NEXT: negs r1, r1
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0x7fffffff

// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint64_t test_clear_bit_compiletime_64_63() {
    uint64_t value = 0xFFFFFFFFFFFFFFFF;
    ArmCortex::clearBit(value, uint8_t{63});
    return value;
}

// CHECK-LABEL: <test_clear_bit_compiletime_64_63>:

// DEBUG-CHECK-NEXT: movs r0, #1
// DEBUG-CHECK-NEXT: negs r0, r0
// DEBUG-CHECK-NEXT: ldr r1, [pc, #0]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0x7fffffff

// MINSIZE-CHECK-NEXT: movs r0, #1
// MINSIZE-CHECK-NEXT: ldr r1, [pc, #4]
// MINSIZE-CHECK-NEXT: negs r0, r0
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0x7fffffff

// MAXSPEED-CHECK-NEXT: movs r0, #1
// MAXSPEED-CHECK-NEXT: ldr r1, [pc, #4]
// MAXSPEED-CHECK-NEXT: negs r0, r0
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0x7fffffff

// CHECK-EMPTY:
