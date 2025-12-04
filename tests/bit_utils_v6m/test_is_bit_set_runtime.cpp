#include "armcortex/bit_utils.hpp"

// ============================================================================
// uint8_t tests
// ============================================================================

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_u_8_0(uint8_t value) {
    return ArmCortex::isBitSet(value, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_runtime_u_8_0>:

// DEBUG-CHECK-NEXT: lsls r0, r0, #31
// DEBUG-CHECK-NEXT: lsrs r0, r0, #31

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: ands r0, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: ands r0, r3

// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_u_8_3(uint8_t value) {
    return ArmCortex::isBitSet(value, uint8_t{3});
}

// CHECK-LABEL: <test_is_bit_set_runtime_u_8_3>:
// CHECK-NEXT: lsls r0, r0, #28
// CHECK-NEXT: lsrs r0, r0, #31
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_u_8_7(uint8_t value) {
    return ArmCortex::isBitSet(value, uint8_t{7});
}

// CHECK-LABEL: <test_is_bit_set_runtime_u_8_7>:
// CHECK-NEXT: lsrs r0, r0, #7
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// ============================================================================
// uint16_t tests
// ============================================================================

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_u_16_0(uint16_t value) {
    return ArmCortex::isBitSet(value, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_runtime_u_16_0>:

// DEBUG-CHECK-NEXT: lsls r0, r0, #31
// DEBUG-CHECK-NEXT: lsrs r0, r0, #31

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: ands r0, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: ands r0, r3

// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_u_16_7(uint16_t value) {
    return ArmCortex::isBitSet(value, uint8_t{7});
}

// CHECK-LABEL: <test_is_bit_set_runtime_u_16_7>:
// CHECK-NEXT: lsls r0, r0, #24
// CHECK-NEXT: lsrs r0, r0, #31
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_u_16_15(uint16_t value) {
    return ArmCortex::isBitSet(value, uint8_t{15});
}

// CHECK-LABEL: <test_is_bit_set_runtime_u_16_15>:
// CHECK-NEXT: lsrs r0, r0, #15
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// ============================================================================
// uint32_t tests
// ============================================================================

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_u_32_0(uint32_t value) {
    return ArmCortex::isBitSet(value, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_runtime_u_32_0>:
// CHECK-NEXT: movs r3, #1
// CHECK-NEXT: ands r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_u_32_15(uint32_t value) {
    return ArmCortex::isBitSet(value, uint8_t{15});
}

// CHECK-LABEL: <test_is_bit_set_runtime_u_32_15>:
// CHECK-NEXT: lsls r0, r0, #16
// CHECK-NEXT: lsrs r0, r0, #31
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_u_32_31(uint32_t value) {
    return ArmCortex::isBitSet(value, uint8_t{31});
}

// CHECK-LABEL: <test_is_bit_set_runtime_u_32_31>:
// CHECK-NEXT: lsrs r0, r0, #31
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// ============================================================================
// uint64_t tests
// ============================================================================

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_u_64_0(uint64_t value) {
    return ArmCortex::isBitSet(value, uint8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_runtime_u_64_0>:
// CHECK-NEXT: movs r3, #1
// CHECK-NEXT: ands r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_u_64_31(uint64_t value) {
    return ArmCortex::isBitSet(value, uint8_t{31});
}

// CHECK-LABEL: <test_is_bit_set_runtime_u_64_31>:
// CHECK-NEXT: lsrs r0, r0, #31
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_u_64_63(uint64_t value) {
    return ArmCortex::isBitSet(value, uint8_t{63});
}

// CHECK-LABEL: <test_is_bit_set_runtime_u_64_63>:
// CHECK-NEXT: lsrs r0, r1, #31
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// ============================================================================
// int8_t tests
// ============================================================================

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_s_8_0(int8_t value) {
    return ArmCortex::isBitSet(value, int8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_runtime_s_8_0>:

// DEBUG-CHECK-NEXT: lsls r0, r0, #31
// DEBUG-CHECK-NEXT: lsrs r0, r0, #31

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: ands r0, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: ands r0, r3

// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_s_8_3(int8_t value) {
    return ArmCortex::isBitSet(value, int8_t{3});
}

// CHECK-LABEL: <test_is_bit_set_runtime_s_8_3>:
// CHECK-NEXT: lsls r0, r0, #28
// CHECK-NEXT: lsrs r0, r0, #31
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_s_8_7(int8_t value) {
    return ArmCortex::isBitSet(value, int8_t{7});
}

// CHECK-LABEL: <test_is_bit_set_runtime_s_8_7>:
// CHECK-NEXT: lsrs r0, r0, #31
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// ============================================================================
// int16_t tests
// ============================================================================

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_s_16_0(int16_t value) {
    return ArmCortex::isBitSet(value, int8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_runtime_s_16_0>:

// DEBUG-CHECK-NEXT: lsls r0, r0, #31
// DEBUG-CHECK-NEXT: lsrs r0, r0, #31

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: ands r0, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: ands r0, r3

// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_s_16_7(int16_t value) {
    return ArmCortex::isBitSet(value, int8_t{7});
}

// CHECK-LABEL: <test_is_bit_set_runtime_s_16_7>:
// CHECK-NEXT: lsls r0, r0, #24
// CHECK-NEXT: lsrs r0, r0, #31
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_s_16_15(int16_t value) {
    return ArmCortex::isBitSet(value, int8_t{15});
}

// CHECK-LABEL: <test_is_bit_set_runtime_s_16_15>:
// CHECK-NEXT: lsrs r0, r0, #31
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// ============================================================================
// int32_t tests
// ============================================================================

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_s_32_0(int32_t value) {
    return ArmCortex::isBitSet(value, int8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_runtime_s_32_0>:
// CHECK-NEXT: movs r3, #1
// CHECK-NEXT: ands r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_s_32_15(int32_t value) {
    return ArmCortex::isBitSet(value, int8_t{15});
}

// CHECK-LABEL: <test_is_bit_set_runtime_s_32_15>:
// CHECK-NEXT: lsls r0, r0, #16
// CHECK-NEXT: lsrs r0, r0, #31
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_s_32_31(int32_t value) {
    return ArmCortex::isBitSet(value, int8_t{31});
}

// CHECK-LABEL: <test_is_bit_set_runtime_s_32_31>:
// CHECK-NEXT: lsrs r0, r0, #31
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// ============================================================================
// int64_t tests
// ============================================================================

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_s_64_0(int64_t value) {
    return ArmCortex::isBitSet(value, int8_t{0});
}

// CHECK-LABEL: <test_is_bit_set_runtime_s_64_0>:
// CHECK-NEXT: movs r3, #1
// CHECK-NEXT: ands r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_s_64_31(int64_t value) {
    return ArmCortex::isBitSet(value, int8_t{31});
}

// CHECK-LABEL: <test_is_bit_set_runtime_s_64_31>:
// CHECK-NEXT: lsrs r0, r0, #31
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] bool test_is_bit_set_runtime_s_64_63(int64_t value) {
    return ArmCortex::isBitSet(value, int8_t{63});
}

// CHECK-LABEL: <test_is_bit_set_runtime_s_64_63>:
// CHECK-NEXT: lsrs r0, r1, #31
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:
