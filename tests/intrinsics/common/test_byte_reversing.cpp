#include "intrinsics/common/byte_reversing.hpp"

extern "C" [[gnu::naked]] uint32_t test_rev(uint32_t value) {
    return ArmCortex::asmRev(value);
}

// CHECK-LABEL: <test_rev>:
// CHECK-NEXT: rev r0, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_rev16(uint32_t value) {
    return ArmCortex::asmRev16(value);
}

// CHECK-LABEL: <test_rev16>:
// CHECK-NEXT: rev16 r0, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_revsh(uint32_t value) {
    return ArmCortex::asmRevsh(value);
}

// CHECK-LABEL: <test_revsh>:
// CHECK-NEXT: revsh r0, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:
