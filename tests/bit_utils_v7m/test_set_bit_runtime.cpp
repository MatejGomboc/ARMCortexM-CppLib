#include "armcortex/bit_utils.hpp"

// ============================================================================
// uint8_t tests
// ============================================================================

extern "C" [[gnu::naked]] uint8_t test_set_bit_runtime_u_8_0(uint8_t value) {
    ArmCortex::setBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_8_0>:
// CHECK-NEXT: orr.w r0, r0, #1
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint8_t test_set_bit_runtime_u_8_3(uint8_t value) {
    ArmCortex::setBit(value, uint8_t{3});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_8_3>:
// CHECK-NEXT: orr.w r0, r0, #8
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint8_t test_set_bit_runtime_u_8_7(uint8_t value) {
    ArmCortex::setBit(value, uint8_t{7});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_8_7>:
// CHECK-NEXT: orr.w r0, r0, #128
// CHECK-EMPTY:

// ============================================================================
// uint16_t tests
// ============================================================================

extern "C" [[gnu::naked]] uint16_t test_set_bit_runtime_u_16_0(uint16_t value) {
    ArmCortex::setBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_16_0>:
// CHECK-NEXT: orr.w r0, r0, #1
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint16_t test_set_bit_runtime_u_16_7(uint16_t value) {
    ArmCortex::setBit(value, uint8_t{7});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_16_7>:
// CHECK-NEXT: orr.w r0, r0, #128
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint16_t test_set_bit_runtime_u_16_15(uint16_t value) {
    ArmCortex::setBit(value, uint8_t{15});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_16_15>:
// CHECK-NEXT: orr.w r0, r0, #32768
// CHECK-EMPTY:

// ============================================================================
// uint32_t tests
// ============================================================================

extern "C" [[gnu::naked]] uint32_t test_set_bit_runtime_u_32_0(uint32_t value) {
    ArmCortex::setBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_32_0>:
// CHECK-NEXT: orr.w r0, r0, #1
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_set_bit_runtime_u_32_15(uint32_t value) {
    ArmCortex::setBit(value, uint8_t{15});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_32_15>:
// CHECK-NEXT: orr.w r0, r0, #32768
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_set_bit_runtime_u_32_31(uint32_t value) {
    ArmCortex::setBit(value, uint8_t{31});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_32_31>:
// CHECK-NEXT: orr.w r0, r0, #2147483648
// CHECK-EMPTY:

// ============================================================================
// uint64_t tests
// ============================================================================

extern "C" [[gnu::naked]] uint64_t test_set_bit_runtime_u_64_0(uint64_t value) {
    ArmCortex::setBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_64_0>:
// CHECK-NEXT: orr.w r0, r0, #1
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint64_t test_set_bit_runtime_u_64_31(uint64_t value) {
    ArmCortex::setBit(value, uint8_t{31});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_64_31>:
// CHECK-NEXT: orr.w r0, r0, #2147483648
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint64_t test_set_bit_runtime_u_64_63(uint64_t value) {
    ArmCortex::setBit(value, uint8_t{63});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_u_64_63>:
// CHECK-NEXT: orr.w r1, r1, #2147483648
// CHECK-EMPTY:

// ============================================================================
// int8_t tests
// ============================================================================

extern "C" [[gnu::naked]] int8_t test_set_bit_runtime_s_8_0(int8_t value) {
    ArmCortex::setBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_8_0>:
// CHECK-NEXT: orr.w r0, r0, #1
// CHECK-EMPTY:

extern "C" [[gnu::naked]] int8_t test_set_bit_runtime_s_8_3(int8_t value) {
    ArmCortex::setBit(value, uint8_t{3});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_8_3>:
// CHECK-NEXT: orr.w r0, r0, #8
// CHECK-EMPTY:

extern "C" [[gnu::naked]] int8_t test_set_bit_runtime_s_8_7(int8_t value) {
    ArmCortex::setBit(value, uint8_t{7});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_8_7>:
// CHECK-NEXT: orr.w r0, r0, #128
// CHECK-EMPTY:

// ============================================================================
// int16_t tests
// ============================================================================

extern "C" [[gnu::naked]] int16_t test_set_bit_runtime_s_16_0(int16_t value) {
    ArmCortex::setBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_16_0>:
// CHECK-NEXT: orr.w r0, r0, #1
// CHECK-EMPTY:

extern "C" [[gnu::naked]] int16_t test_set_bit_runtime_s_16_7(int16_t value) {
    ArmCortex::setBit(value, uint8_t{7});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_16_7>:
// CHECK-NEXT: orr.w r0, r0, #128
// CHECK-EMPTY:

extern "C" [[gnu::naked]] int16_t test_set_bit_runtime_s_16_15(int16_t value) {
    ArmCortex::setBit(value, uint8_t{15});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_16_15>:
// CHECK-NEXT: orr.w r0, r0, #32768
// CHECK-EMPTY:

// ============================================================================
// int32_t tests
// ============================================================================

extern "C" [[gnu::naked]] int32_t test_set_bit_runtime_s_32_0(int32_t value) {
    ArmCortex::setBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_32_0>:
// CHECK-NEXT: orr.w r0, r0, #1
// CHECK-EMPTY:

extern "C" [[gnu::naked]] int32_t test_set_bit_runtime_s_32_15(int32_t value) {
    ArmCortex::setBit(value, uint8_t{15});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_32_15>:
// CHECK-NEXT: orr.w r0, r0, #32768
// CHECK-EMPTY:

extern "C" [[gnu::naked]] int32_t test_set_bit_runtime_s_32_31(int32_t value) {
    ArmCortex::setBit(value, uint8_t{31});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_32_31>:
// CHECK-NEXT: orr.w r0, r0, #2147483648
// CHECK-EMPTY:

// ============================================================================
// int64_t tests
// ============================================================================

extern "C" [[gnu::naked]] int64_t test_set_bit_runtime_s_64_0(int64_t value) {
    ArmCortex::setBit(value, uint8_t{0});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_64_0>:
// CHECK-NEXT: orr.w r0, r0, #1
// CHECK-EMPTY:

extern "C" [[gnu::naked]] int64_t test_set_bit_runtime_s_64_31(int64_t value) {
    ArmCortex::setBit(value, uint8_t{31});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_64_31>:
// CHECK-NEXT: orr.w r0, r0, #2147483648
// CHECK-EMPTY:

extern "C" [[gnu::naked]] int64_t test_set_bit_runtime_s_64_63(int64_t value) {
    ArmCortex::setBit(value, uint8_t{63});
    return value;
}

// CHECK-LABEL: <test_set_bit_runtime_s_64_63>:
// CHECK-NEXT: orr.w r1, r1, #2147483648
// CHECK-EMPTY:
