#include "intrinsics/byte_reversing.hpp"

extern "C" [[gnu::naked]] uint32_t test_rev(uint32_t value) {
    return Cortex::asmRev(value);
}

// CHECK-LABEL: <test_rev>:

// DEBUG-CHECK-NEXT: movs r3, r0
// DEBUG-CHECK-NEXT: movs r4, r3
// DEBUG-CHECK-NEXT: rev r3, r4
// DEBUG-CHECK-NEXT: movs r4, r3
// DEBUG-CHECK-NEXT: movs r3, r4
// DEBUG-CHECK-NEXT: movs r0, r3

// RELEASE-CHECK-NEXT: rev r0, r0
// RELEASE-CHECK-NEXT: nop

// RELWITHDEBINFO-CHECK-NEXT: rev r0, r0
// RELWITHDEBINFO-CHECK-NEXT: nop

// MINSIZEREL-CHECK-NEXT: rev r0, r0

// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_rev16(uint32_t value) {
    return Cortex::asmRev16(value);
}

// CHECK-LABEL: <test_rev16>:

// DEBUG-CHECK-NEXT: movs r3, r0
// DEBUG-CHECK-NEXT: movs r4, r3
// DEBUG-CHECK-NEXT: rev16 r3, r4
// DEBUG-CHECK-NEXT: movs r4, r3
// DEBUG-CHECK-NEXT: movs r3, r4
// DEBUG-CHECK-NEXT: movs r0, r3

// RELEASE-CHECK-NEXT: rev16 r0, r0
// RELEASE-CHECK-NEXT: nop

// RELWITHDEBINFO-CHECK-NEXT: rev16 r0, r0
// RELWITHDEBINFO-CHECK-NEXT: nop

// MINSIZEREL-CHECK-NEXT: rev16 r0, r0

// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_revsh(uint32_t value) {
    return Cortex::asmRevsh(value);
}

// CHECK-LABEL: <test_revsh>:

// DEBUG-CHECK-NEXT: movs r3, r0
// DEBUG-CHECK-NEXT: movs r4, r3
// DEBUG-CHECK-NEXT: revsh r3, r4
// DEBUG-CHECK-NEXT: movs r4, r3
// DEBUG-CHECK-NEXT: movs r3, r4
// DEBUG-CHECK-NEXT: movs r0, r3

// RELEASE-CHECK-NEXT: revsh r0, r0
// RELEASE-CHECK-NEXT: nop

// RELWITHDEBINFO-CHECK-NEXT: revsh r0, r0
// RELWITHDEBINFO-CHECK-NEXT: nop

// MINSIZEREL-CHECK-NEXT: revsh r0, r0

// CHECK-EMPTY:
