#include "armcortex/intrinsics/saturation.hpp"

extern "C" [[gnu::naked]] int32_t test_ssat_8(int32_t value) {
    return ArmCortex::asmSsat<8>(value);
}

// CHECK-LABEL: <test_ssat_8>:
// CHECK-NEXT: ssat r0, #8, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] int32_t test_ssat_16(int32_t value) {
    return ArmCortex::asmSsat<16>(value);
}

// CHECK-LABEL: <test_ssat_16>:
// CHECK-NEXT: ssat r0, #16, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] int32_t test_ssat_32(int32_t value) {
    return ArmCortex::asmSsat<32>(value);
}

// CHECK-LABEL: <test_ssat_32>:
// CHECK-NEXT: ssat r0, #32, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_usat_7(int32_t value) {
    return ArmCortex::asmUsat<7>(value);
}

// CHECK-LABEL: <test_usat_7>:
// CHECK-NEXT: usat r0, #7, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_usat_15(int32_t value) {
    return ArmCortex::asmUsat<15>(value);
}

// CHECK-LABEL: <test_usat_15>:
// CHECK-NEXT: usat r0, #15, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_usat_31(int32_t value) {
    return ArmCortex::asmUsat<31>(value);
}

// CHECK-LABEL: <test_usat_31>:
// CHECK-NEXT: usat r0, #31, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:
