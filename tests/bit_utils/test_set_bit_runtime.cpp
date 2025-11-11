#include "bit_utils.hpp"

// ============================================================================
// uint8_t tests
// ============================================================================

extern "C" [[gnu::naked]] uint8_t test_set_bit_runtime_u_8_0(uint8_t value) {
    Cortex::setBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_8_0>:
// CHECK-NEXT: movs r3, #1
// CHECK-NEXT: orrs r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint8_t test_set_bit_runtime_u_8_3(uint8_t value) {
    Cortex::setBit(value, uint8_t{3});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_8_3>:
// CHECK-NEXT: movs r3, #8
// CHECK-NEXT: orrs r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint8_t test_set_bit_runtime_u_8_7(uint8_t value) {
    Cortex::setBit(value, uint8_t{7});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_8_7>:
// CHECK-NEXT: movs r3, #128
// CHECK-NEXT: orrs r0, r3
// CHECK-EMPTY:

// ============================================================================
// uint16_t tests
// ============================================================================

extern "C" [[gnu::naked]] uint16_t test_set_bit_runtime_u_16_0(uint16_t value) {
    Cortex::setBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_16_0>:
// CHECK-NEXT: movs r3, #1
// CHECK-NEXT: orrs r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint16_t test_set_bit_runtime_u_16_7(uint16_t value) {
    Cortex::setBit(value, uint8_t{7});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_16_7>:
// CHECK-NEXT: movs r3, #128
// CHECK-NEXT: orrs r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint16_t test_set_bit_runtime_u_16_15(uint16_t value) {
    Cortex::setBit(value, uint8_t{15});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_16_15>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: orrs r0, r3

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: lsls r3, r3, #15
// MINSIZE-CHECK-NEXT: orrs r0, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: lsls r3, r3, #15
// MAXSPEED-CHECK-NEXT: orrs r0, r3

// CHECK-EMPTY:

// ============================================================================
// uint32_t tests
// ============================================================================

extern "C" [[gnu::naked]] uint32_t test_set_bit_runtime_u_32_0(uint32_t value) {
    Cortex::setBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_32_0>:
// CHECK-NEXT: movs r3, #1
// CHECK-NEXT: orrs r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_set_bit_runtime_u_32_15(uint32_t value) {
    Cortex::setBit(value, uint8_t{15});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_32_15>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: orrs r0, r3

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: lsls r3, r3, #15
// MINSIZE-CHECK-NEXT: orrs r0, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: lsls r3, r3, #15
// MAXSPEED-CHECK-NEXT: orrs r0, r3

// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_set_bit_runtime_u_32_31(uint32_t value) {
    Cortex::setBit(value, uint8_t{31});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_32_31>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: orrs r0, r3

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: lsls r3, r3, #31
// MINSIZE-CHECK-NEXT: orrs r0, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: lsls r3, r3, #31
// MAXSPEED-CHECK-NEXT: orrs r0, r3

// CHECK-EMPTY:

// ============================================================================
// uint64_t tests
// ============================================================================

extern "C" [[gnu::naked]] uint64_t test_set_bit_runtime_u_64_0(uint64_t value) {
    Cortex::setBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_64_0>:
// CHECK-NEXT: movs r3, #1
// CHECK-NEXT: orrs r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint64_t test_set_bit_runtime_u_64_31(uint64_t value) {
    Cortex::setBit(value, uint8_t{31});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_64_31>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: orrs r0, r3

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: lsls r3, r3, #31
// MINSIZE-CHECK-NEXT: orrs r0, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: lsls r3, r3, #31
// MAXSPEED-CHECK-NEXT: orrs r0, r3

// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint64_t test_set_bit_runtime_u_64_63(uint64_t value) {
    Cortex::setBit(value, uint8_t{63});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_64_63>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: orrs r1, r3

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: lsls r3, r3, #31
// MINSIZE-CHECK-NEXT: orrs r1, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: lsls r3, r3, #31
// MAXSPEED-CHECK-NEXT: orrs r1, r3

// CHECK-EMPTY:

// ============================================================================
// int8_t tests
// ============================================================================

extern "C" [[gnu::naked]] int8_t test_set_bit_runtime_s_8_0(int8_t value) {
    Cortex::setBit(value, int8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_8_0>:
// CHECK-NEXT: movs r3, #1
// CHECK-NEXT: orrs r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] int8_t test_set_bit_runtime_s_8_3(int8_t value) {
    Cortex::setBit(value, int8_t{3});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_8_3>:
// CHECK-NEXT: movs r3, #8
// CHECK-NEXT: orrs r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] int8_t test_set_bit_runtime_s_8_7(int8_t value) {
    Cortex::setBit(value, int8_t{7});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_8_7>:
// CHECK-NEXT: movs r3, #128
// CHECK-NEXT: orrs r0, r3
// CHECK-EMPTY:

// ============================================================================
// int16_t tests
// ============================================================================

extern "C" [[gnu::naked]] int16_t test_set_bit_runtime_s_16_0(int16_t value) {
    Cortex::setBit(value, int8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_16_0>:
// CHECK-NEXT: movs r3, #1
// CHECK-NEXT: orrs r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] int16_t test_set_bit_runtime_s_16_7(int16_t value) {
    Cortex::setBit(value, int8_t{7});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_16_7>:
// CHECK-NEXT: movs r3, #128
// CHECK-NEXT: orrs r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] int16_t test_set_bit_runtime_s_16_15(int16_t value) {
    Cortex::setBit(value, int8_t{15});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_16_15>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: orrs r0, r3

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: lsls r3, r3, #15
// MINSIZE-CHECK-NEXT: orrs r0, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: lsls r3, r3, #15
// MAXSPEED-CHECK-NEXT: orrs r0, r3

// CHECK-EMPTY:

// ============================================================================
// int32_t tests
// ============================================================================

extern "C" [[gnu::naked]] int32_t test_set_bit_runtime_s_32_0(int32_t value) {
    Cortex::setBit(value, int8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_32_0>:
// CHECK-NEXT: movs r3, #1
// CHECK-NEXT: orrs r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] int32_t test_set_bit_runtime_s_32_15(int32_t value) {
    Cortex::setBit(value, int8_t{15});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_32_15>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: orrs r0, r3

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: lsls r3, r3, #15
// MINSIZE-CHECK-NEXT: orrs r0, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: lsls r3, r3, #15
// MAXSPEED-CHECK-NEXT: orrs r0, r3

// CHECK-EMPTY:

extern "C" [[gnu::naked]] int32_t test_set_bit_runtime_s_32_31(int32_t value) {
    Cortex::setBit(value, int8_t{31});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_32_31>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: orrs r0, r3

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: lsls r3, r3, #31
// MINSIZE-CHECK-NEXT: orrs r0, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: lsls r3, r3, #31
// MAXSPEED-CHECK-NEXT: orrs r0, r3

// CHECK-EMPTY:

// ============================================================================
// int64_t tests
// ============================================================================

extern "C" [[gnu::naked]] int64_t test_set_bit_runtime_s_64_0(int64_t value) {
    Cortex::setBit(value, int8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_64_0>:
// CHECK-NEXT: movs r3, #1
// CHECK-NEXT: orrs r0, r3
// CHECK-EMPTY:

extern "C" [[gnu::naked]] int64_t test_set_bit_runtime_s_64_31(int64_t value) {
    Cortex::setBit(value, int8_t{31});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_64_31>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: orrs r0, r3

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: lsls r3, r3, #31
// MINSIZE-CHECK-NEXT: orrs r0, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: lsls r3, r3, #31
// MAXSPEED-CHECK-NEXT: orrs r0, r3

// CHECK-EMPTY:

extern "C" [[gnu::naked]] int64_t test_set_bit_runtime_s_64_63(int64_t value) {
    Cortex::setBit(value, int8_t{63});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_64_63>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: orrs r1, r3

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: lsls r3, r3, #31
// MINSIZE-CHECK-NEXT: orrs r1, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: lsls r3, r3, #31
// MAXSPEED-CHECK-NEXT: orrs r1, r3

// CHECK-EMPTY:
